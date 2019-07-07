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
    fDetuneAmount = 0.0;

    fDetuneLFO[0].init(sampleRate);
    fDetuneLFO[0].setFrequency(69.0);
    fDetuneLFO[1].init(sampleRate);
    fDetuneLFO[1].setFrequency(60.0);

    fMixGainUpper = 0.0;
    fMixGainLower = 0.0;

    fOscSettings.highpassUpperCutoff = 0.0;
    fOscSettings.highpassLowerCutoff = 0.0;

    fEnvSettings.attack = 1.0;
    fEnvSettings.decay = 1.0;
    fEnvSettings.sustain = 1.0;
    fEnvSettings.release = 1.0;

    fFltSettings.lowpassUpperCutoff = 0.0;
    fFltSettings.highpassUpperCutoff = 0.0;
    fFltSettings.lowpassLowerCutoff = 0.0;
    fFltSettings.highpassLowerCutoff = 0.0;
    fFltSettings.highshelfEqCutoff = 0.0;
    fFltSettings.highshelfEqBoost = 0.0;

    Voice *voices = fVoices.get();

    for (unsigned i = 0; i < 128; ++i) {
        Voice &voice = voices[i];
        voice.active = false;
        voice.note = i;
        voice.pitch = 440.0 * std::pow(2.0, (i - 69.0) * (1.0 / 12.0));

        voice.env.init(&fEnvSettings, sampleRate);

        voice.osc.init(&fOscSettings, sampleRate);
        voice.osc.setFrequency(voice.pitch);

        voice.flt.init(&fFltSettings, sampleRate);
    }

    fChorus.init(sampleRate);

    fMasterGain = 0.0;
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
        case 120:
            allSoundOff();
            break;
        // case 121:
        //     resetAllControllers();
        //     break;
        case 123:
        case 124: case 125:
        case 126: case 127:
            allNotesOff();
            break;
        }
        break;
    }
}

void StringSynth::generate(float *outputs[2], unsigned count)
{
    auto &activeVoices = fActiveVoices;
    float detuneAmount = fDetuneAmount;

    float *outL = outputs[0];
    float *outR = outputs[1];
    memset(outL, 0, count * sizeof(float));

    float detuneUpper[BufferLimit];
    float detuneLower[BufferLimit];
    TriangleLFO &lfoUpper  = fDetuneLFO[0];
    TriangleLFO &lfoLower  = fDetuneLFO[1];

    for (unsigned i = 0; i < count; ++i) {
        float detuneMod = detuneAmount * lfoUpper.process();
        detuneUpper[i] = std::exp2(detuneMod * (1.0f / 12.0f));
    }
    for (unsigned i = 0; i < count; ++i) {
        float detuneMod = detuneAmount * lfoLower.process();
        detuneLower[i] = std::exp2(detuneMod * (1.0f / 12.0f));
    }

    float *detune[2] = {detuneUpper, detuneLower};

    for (auto it = activeVoices.begin(), end = activeVoices.end(); it != end;) {
        Voice &voice = *it;
        bool finished = generateVoiceAdding(voice, outL, detune, count);
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
    Voice &voice = fVoices[note];

    if (!voice.active) {
        voice.active = true;
        fActiveVoices.push_front(voice);
    }
    voice.env.trigger();
}

void StringSynth::noteOff(unsigned note, unsigned vel)
{
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
        voice.active = false;
        voice.env.release();
        voice.env.clear();
        voice.osc.clear();
        activeVoices.pop_front();
    }
}

bool StringSynth::generateVoiceAdding(Voice &voice, float *output, const float *const detune[2], unsigned count)
{
    float oscOutputUpper[BufferLimit];
    float oscOutputLower[BufferLimit];
    float *oscOutputs[] = {oscOutputUpper, oscOutputLower};
    voice.osc.process(oscOutputs, detune, count);

    float fltOutputUpper[BufferLimit];
    float fltOutputLower[BufferLimit];
    float fltOutputBrass[BufferLimit];
    float *fltOutputs[] = {fltOutputUpper, fltOutputLower, fltOutputBrass};
    voice.flt.process(oscOutputs, fltOutputs, voice.pitch, count);

    float env[BufferLimit];
    voice.env.process(env, count);

    float mixGainUpper = std::pow(10.0f, 0.05f * fMixGainUpper);
    float mixGainLower = std::pow(10.0f, 0.05f * fMixGainLower);
    for (unsigned i = 0; i < count; ++i)
        output[i] += env[i] * (mixGainUpper * fltOutputUpper[i] +
                               mixGainLower * fltOutputLower[i]);

    // clean finished notes
    bool finished = false;
    if (!voice.env.isTriggered() && voice.env.getCurrentLevel() < 1e-4f) {
        voice.active = false;
        voice.env.release();
        voice.env.clear();
        voice.osc.clear();
        finished = true;
    }

    return finished;
}
