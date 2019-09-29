#include "StringSynth.h"
#include "StringSynthDefs.h"
#include <cmath>
#include <cstring>

using StringSynthDefs::BufferLimit;

StringSynth::StringSynth()
    : fVoices(new Voice[128])
{
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

    Voice *voices = fVoices.get();

    for (unsigned i = 0; i < 128; ++i) {
        Voice &voice = voices[i];
        voice.active = false;
        voice.note = i;
        voice.pitch = 440.0 * std::pow(2.0, (i - 69.0) * (1.0 / 12.0));
        voice.bend = 1.0;

        voice.env.init(&fEnvSettings, sampleRate);

        voice.osc.init(&fOscSettings, sampleRate);
        voice.osc.setFrequency(voice.pitch);

        voice.flt.init(&fFltSettings, sampleRate);
    }

    fChorus.init(sampleRate);

    resetAllControllers();
}

void StringSynth::handleMessage(const uint8_t *msg)
{
    unsigned status = msg[0];
    unsigned d1 = msg[1] & 0x7f;
    unsigned d2 = msg[2] & 0x7f;

    switch (status & 0xf0) {
    case 0x90:
        if (d2 != 0) {
            noteOn(d1, d2);
            break;
        }
        // fall through
    case 0x80:
        noteOff(d1, d2);
        break;
    case 0xb0:
        switch (d1) {
        case 6: {
            RpnIdentifier id = fCtlRpnIdentifier;
            if (id.registered && id.lsb == 0 && id.msb == 0)
                fCtlPitchBendSensitivity = d2;
            break;
        }
        case 98:
        case 100:
            fCtlRpnIdentifier.lsb = d2;
            fCtlRpnIdentifier.registered = d1 == 100;
            break;
        case 99:
        case 101:
            fCtlRpnIdentifier.msb = d2;
            fCtlRpnIdentifier.registered = d1 == 101;
            break;
        case 120:
            allSoundOff();
            break;
        case 121:
            resetAllControllers();
            break;
        case 123:
        case 124: case 125:
        case 126: case 127:
            allNotesOff();
            break;
        }
        break;
    case 0xe0:
        fCtlPitchBend = ((int)(d1 | (d2 << 7)) - 8192) * (1.0f / 8191.0f);
        break;
    }
}

void StringSynth::resetAllControllers()
{
    fCtlPitchBend = 0.0;
    fCtlPitchBendSensitivity = 2.0;
    fCtlRpnIdentifier.registered = 1;
    fCtlRpnIdentifier.msb = 0;
    fCtlRpnIdentifier.lsb = 0;
}

void StringSynth::generate(float *outputs[2], unsigned count)
{
    auto &activeVoices = fActiveVoices;
    float detuneAmount = fDetuneAmount;

#if 0
    bool gate = false;
    for (auto it = activeVoices.begin(), end = activeVoices.end(); it != end && !gate; ++it) {
        if (it->env.isTriggered())
            gate = true;
    }
#endif

    float *outL = outputs[0];
    float *outR = outputs[1];
    memset(outL, 0, count * sizeof(float));

    float detuneUpper[BufferLimit];
    float detuneLower[BufferLimit];

    if (!activeVoices.empty()) {
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

    float bend = std::exp2(fCtlPitchBend * fCtlPitchBendSensitivity * (1.0f / 12.0f));

    for (auto it = activeVoices.begin(), end = activeVoices.end(); it != end;) {
        Voice &voice = *it;
        float *detune[2] = {detuneUpper, detuneLower};
        bool finished = generateVoiceAdding(voice, outL, detune, bend, count);
        if (finished) activeVoices.erase(it++); else ++it;
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

void StringSynth::noteOn(unsigned note, unsigned vel)
{
    // TODO the key-on velocity
    (void)vel;

    Voice &voice = fVoices[note];

    if (!voice.active) {
        voice.active = true;
        fActiveVoices.push_front(voice);
    }
    voice.env.trigger();
}

void StringSynth::noteOff(unsigned note, unsigned vel)
{
    (void)vel;

    Voice &voice = fVoices[note];

    if (voice.active)
        voice.env.release();
}

void StringSynth::allNotesOff()
{
    for (Voice &voice : fActiveVoices)
        noteOff(voice.note, 0);
}

void StringSynth::allSoundOff()
{
    auto &activeVoices = fActiveVoices;

    while (!activeVoices.empty()) {
        Voice &voice = activeVoices.front();
        clearFinishedVoice(voice);
        activeVoices.pop_front();
    }
}

bool StringSynth::generateVoiceAdding(Voice &voice, float *output, const float *const detune[2], float bend, unsigned count)
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
    voice.flt.process(oscOutputs, fltOutputs, voice.pitch * bend, count);

    float env[BufferLimit];
    voice.env.process(env, count);

    float mixGainUpper = std::pow(10.0f, 0.05f * fMixGainUpper);
    float mixGainLower = std::pow(10.0f, 0.05f * fMixGainLower);
    for (unsigned i = 0; i < count; ++i)
        output[i] += env[i] * (mixGainUpper * fltOutputUpper[i] +
                               mixGainLower * fltOutputLower[i]);

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
    voice.active = false;
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
