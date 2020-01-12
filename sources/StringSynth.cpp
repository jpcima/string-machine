#include "StringSynth.h"
#include "StringSynthDefs.h"
#include "MidiDefs.h"
#include <cmath>
#include <cstring>

using StringSynthDefs::BufferLimit;
using StringSynthDefs::PolyphonyLimit;

///
#if 0
#   define TRACE_ALLOC(fmt, ...) fprintf(stderr, "[Voices] " fmt "\n", ##__VA_ARGS__);
#else
#   define TRACE_ALLOC(fmt, ...)
#endif

///
StringSynth::StringSynth()
    : fVoicesReserved{new Voice[PolyphonyLimit]{}},
      fVoicesUsed{PolyphonyLimit},
      fVoicesFree{PolyphonyLimit}
{
    for (unsigned i = 0; i < PolyphonyLimit; ++i)
        fVoicesReserved[i].id = i;
}

StringSynth::~StringSynth()
{
}

void StringSynth::init(double sampleRate)
{
    fDetuneLFO[0].init(sampleRate);
    fDetuneLFO[0].set_frequency(69.0);
    fDetuneLFO[1].init(sampleRate);
    fDetuneLFO[1].set_frequency(60.0);

    fLastDetuneUpper = 0.0;
    fLastDetuneLower = 0.0;

    Voice *voicesReserved = fVoicesReserved.get();
    auto &voicesFree = fVoicesFree;
    auto &voicesUsed = fVoicesUsed;

    voicesFree.clear();
    voicesUsed.clear();

    for (unsigned i = 0; i < PolyphonyLimit; ++i) {
        Voice &voice = voicesReserved[i];

        voice.channel = 0;
        voice.note = 0;
        voice.bend = 1.0;

        voice.env.init(&fEnvSettings, sampleRate);
        voice.osc.init(&fOscSettings, sampleRate);
        voice.flt.init(&fFltSettings, sampleRate);

        voicesFree.push_back(&voice);
    }

    fChorus.init(sampleRate);

    for (unsigned ch = 0; ch < 16; ++ch)
        resetAllControllers(ch);
}

void StringSynth::handleMessage(const uint8_t *msg)
{
    unsigned status = msg[0];
    unsigned channel = status & 0x0f;
    unsigned d1 = msg[1] & 0x7f;
    unsigned d2 = msg[2] & 0x7f;
    Controllers &ctl = fControllers[channel];

    switch (status & 0xf0) {
    case kStatusNoteOn:
        if (d2 != 0) {
            noteOn(channel, d1, d2);
            break;
        }
        // fall through
    case kStatusNoteOff:
        noteOff(channel, d1, d2);
        break;
    case kStatusControllerChange:
        switch (d1) {
        case kCcDataMsb: {
            RpnIdentifier id = ctl.rpnIdentifier;
            if (id.registered && id.lsb == 0 && id.msb == 0)
                ctl.pitchBendSensitivity = d2;
            break;
        }
        case kCcVolumeMsb:
            ctl.volume14bit = (ctl.volume14bit & 127) | (d2 << 7);
            break;
        case kCcVolumeLsb:
            ctl.volume14bit = (ctl.volume14bit & (127 << 7)) | d2;
            break;
        case kCcExpressionMsb:
            ctl.expression14bit = (ctl.expression14bit & 127) | (d2 << 7);
            break;
        case kCcExpressionLsb:
            ctl.expression14bit = (ctl.expression14bit & (127 << 7)) | d2;
            break;
        case kCcNrpnLsb:
        case kCcRpnLsb:
            ctl.rpnIdentifier.lsb = d2;
            ctl.rpnIdentifier.registered = d1 == kCcRpnLsb;
            break;
        case kCcNrpnMsb:
        case kCcRpnMsb:
            ctl.rpnIdentifier.msb = d2;
            ctl.rpnIdentifier.registered = d1 == kCcRpnMsb;
            break;
        case kCcSoundOff:
            allSoundOff(channel);
            break;
        case kCcResetControllers:
            resetAllControllers(channel);
            break;
        case kCcNotesOff:
        case kCcOmniOff:
        case kCcOmniOn:
        case kCcMonoOn:
        case kCcPolyOn:
            allNotesOff(channel);
            break;
        }
        break;
    case kStatusPitchBend:
        ctl.pitchBend = ((int)(d1 | (d2 << 7)) - 8192) * (1.0f / 8191.0f);
        break;
    }
}

void StringSynth::resetAllControllers(unsigned channel)
{
    Controllers &ctl = fControllers[channel];
    ctl.pitchBend = 0.0;
    ctl.pitchBendSensitivity = 2.0;
    ctl.volume14bit = 100u << 7;
    ctl.expression14bit = 127u << 7;
    ctl.rpnIdentifier.registered = 1;
    ctl.rpnIdentifier.msb = 0;
    ctl.rpnIdentifier.lsb = 0;
}

void StringSynth::generate(float *outputs[2], unsigned count)
{
    auto &voicesUsed = fVoicesUsed;
    auto &voicesFree = fVoicesFree;
    float detuneAmount = fDetuneAmount;

#if 0
    bool gate = false;
    for (auto it = voicesUsed.begin(), end = voicesUsed.end(); it != end && !gate; ++it) {
        if (it->env.isTriggered())
            gate = true;
    }
#endif

    float *outL = outputs[0];
    float *outR = outputs[1];
    memset(outL, 0, count * sizeof(float));

    float detuneUpper[BufferLimit];
    float detuneLower[BufferLimit];

    if (!voicesUsed.empty()) {
        NoiseLFO &lfoUpper = fDetuneLFO[0];
        NoiseLFO &lfoLower = fDetuneLFO[1];
        float lastDetuneLower = fLastDetuneLower;
        float lastDetuneUpper = fLastDetuneUpper;

        float lfoOutputUpper[BufferLimit];
        float lfoOutputLower[BufferLimit];

        lfoUpper.process(lfoOutputUpper, count);
        for (unsigned i = 0; i < count; ++i) {
            lastDetuneUpper = detuneAmount * 0.5f * lfoOutputUpper[i];
            detuneUpper[i] = std::exp2(lastDetuneUpper * (1.0f / 12.0f));
        }
        lfoLower.process(lfoOutputLower, count);
        for (unsigned i = 0; i < count; ++i) {
            lastDetuneLower = detuneAmount * 0.5f * lfoOutputLower[i];
            detuneLower[i] = std::exp2(lastDetuneLower * (1.0f / 12.0f));
        }

        fLastDetuneLower = lastDetuneLower;
        fLastDetuneUpper = lastDetuneUpper;
    }

    for (auto it = voicesUsed.begin(), end = voicesUsed.end(); it != end;) {
        Voice &voice = *it->value;
        float *detune[2] = {detuneUpper, detuneLower};

        unsigned channel = voice.channel;
        const Controllers &ctl = fControllers[channel];
        float bend = std::exp2(ctl.pitchBend * ctl.pitchBendSensitivity * (1.0f / 12.0f));
        float volume = MidiGetVolume14bit((ctl.volume14bit * ctl.expression14bit) >> 14);

        bool finished = generateVoiceAdding(voice, outL, detune, bend, volume, count);
        if (!finished)
            ++it;
        else {
            TRACE_ALLOC("Finish %u note=%s", voice.id, MidiNoteName[voice.note]);
            voicesUsed.erase(it++);
            voicesFree.push_back(&voice);
        }
    }

    float outMono[BufferLimit];
    float *chorusOutputs[] = {outL, outR, outMono};
    fChorus.process(outL, chorusOutputs, count);

    float finalGain = std::pow(10.0f, 0.05 * (fMasterGain - 12.0f));
    for (unsigned i = 0; i < count; ++i) {
        outL[i] *= finalGain;
        outR[i] *= finalGain;
    }
}

void StringSynth::setPolyphony(int value)
{
    value = (value < 1) ? 1 : value;
    value = (value > PolyphonyLimit) ? PolyphonyLimit : value;

    if (fPolyphony == (unsigned)value)
        return;

    fPolyphony = value;
    allSoundOffAllChannels();
}

void StringSynth::noteOn(unsigned channel, unsigned note, unsigned vel)
{
    // TODO the key-on velocity
    (void)vel;

    Voice &voice = allocNewVoice();
    TRACE_ALLOC("Play %u note=%s", voice.id, MidiNoteName[note]);

    voice.channel = channel;
    voice.note = note;
    voice.osc.setFrequency(MidiPitch[note]);
    voice.env.trigger();
    voice.release = 0;
}

void StringSynth::noteOff(unsigned channel, unsigned note, unsigned vel)
{
    (void)vel;

    Voice *voice = findVoiceKeyedOn(channel, note);
    if (!voice)
        return;

    voice->env.release();
}

void StringSynth::allNotesOff(unsigned channel)
{
    for (pl_cell<Voice *> &cell : fVoicesUsed) {
        Voice &voice = *cell.value;
        if (voice.channel == channel && !voiceHasReleased(voice))
            voice.env.release();
    }
}

void StringSynth::allSoundOff(unsigned channel)
{
    auto &voicesUsed = fVoicesUsed;
    auto &voicesFree = fVoicesFree;

    auto it = voicesUsed.begin();
    while (!it.is_end()) {
        Voice &voice = *it->value;
        if (voice.channel != channel) {
            ++it;
            continue;
        }
        clearFinishedVoice(voice);
        voicesUsed.erase(it++);
        voicesFree.push_back(&voice);
    }
}

void StringSynth::allSoundOffAllChannels()
{
    auto &voicesUsed = fVoicesUsed;
    auto &voicesFree = fVoicesFree;

    while (!voicesUsed.empty()) {
        pl_cell<Voice *> &cell = voicesUsed.front();
        Voice &voice = *cell.value;
        clearFinishedVoice(voice);
        voicesUsed.pop_front();
        voicesFree.push_back(&voice);
    }
}

auto StringSynth::allocNewVoice() -> Voice &
{
    auto &voicesUsed = fVoicesUsed;
    auto &voicesFree = fVoicesFree;

    Voice *voice;

    if (voicesUsed.size() < fPolyphony) {
        voice = voicesFree.front().value;
        TRACE_ALLOC("Allocate %u", voice->id);
        voicesFree.pop_front();
        voicesUsed.push_back(voice); // new voices at the back
    }
    else {
        TRACE_ALLOC("Exceed polyphony");

        // elect a voice that will be replaced
        pl_cell<Voice *> *elected = &voicesUsed.front(); // old voices at the front

        // search for the voice which has been released for the longest time
        // TODO optimize this O(n)?
        for (pl_cell<Voice *> &cell : voicesUsed) {
            TRACE_ALLOC(" * Candidate %u: release=%u", cell.value->id, cell.value->release);
            if (cell.value->release > elected->value->release)
                elected = &cell;
        }

        voice = elected->value;
        TRACE_ALLOC("Override %u note=%s", voice->id, MidiNoteName[voice->note]);

        // push it to the back
        voicesUsed.erase(pl_iterator<pl_cell<Voice *>>{elected});
        voicesUsed.push_back(voice);
    }

    return *voice;
}

auto StringSynth::findVoiceKeyedOn(unsigned channel, unsigned note) -> Voice *
{
    // TODO worth optimizing this O(n)? bounded by the maximum polyphony
    //      also I now support multiple voices per midi note (if I ever add MPE)

    for (pl_cell<Voice *> &cell : fVoicesUsed) {
        Voice &voice = *cell.value;
        if (voice.channel == channel && voice.note == note) {
            if (!voiceHasReleased(voice))
                return &voice;
        }
    }
    return nullptr;
}

bool StringSynth::generateVoiceAdding(Voice &voice, float *output, const float *const detune[2], float bend, float addGain, unsigned count)
{
    // stop handling pitch bend after release
    if (voiceHasReleased(voice))
        bend = voice.bend;
    else
        voice.bend = bend;

    float oscOutputUpper[BufferLimit];
    float oscOutputLower[BufferLimit];
    float *oscOutputs[] = {oscOutputUpper, oscOutputLower};
    voice.osc.process(oscOutputs, detune, bend, count);

    float fltOutputUpper[BufferLimit];
    float fltOutputLower[BufferLimit];
    float fltOutputBrass[BufferLimit];
    float *fltOutputs[] = {fltOutputUpper, fltOutputLower, fltOutputBrass};
    voice.flt.process(oscOutputs, fltOutputs, MidiPitch[voice.note] * bend, count);

    float env[BufferLimit];
    voice.env.process(env, count);

    float mixGainUpper = std::pow(10.0f, 0.05f * fMixGainUpper);
    float mixGainLower = std::pow(10.0f, 0.05f * fMixGainLower);
    for (unsigned i = 0; i < count; ++i) {
        output[i] += addGain * env[i] * (mixGainUpper * fltOutputUpper[i] +
                                         mixGainLower * fltOutputLower[i]);
    }

    // accumulate release time
    if (voiceHasReleased(voice))
        voice.release += count;

    // clean finished notes
    bool finished = false;
    if (voiceHasFinished(voice)) {
        clearFinishedVoice(voice);
        finished = true;
    }

    return finished;
}

void StringSynth::clearFinishedVoice(Voice &voice)
{
    voice.env.release();
    voice.env.clear();
    voice.osc.clear();
    voice.bend = 1.0;
}

bool StringSynth::voiceHasReleased(const Voice &voice)
{
    return !voice.env.isTriggered();
}

bool StringSynth::voiceHasFinished(const Voice &voice)
{
    return !voice.env.isTriggered() && voice.env.getCurrentLevel() < 1e-4f;
}
