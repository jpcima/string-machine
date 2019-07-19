#include "StringOsc.h"
#include "StringSynthDefs.h"
#include <cstdio>

using StringSynthDefs::BufferLimit;

void StringOsc::init(const Settings *settings, double sampleRate)
{
    fSettings = settings;

    fOscillator[0].init(sampleRate);
    fOscillator[1].init(sampleRate);

    fFilter[0].init(sampleRate);
    fFilter[1].init(sampleRate);
}

void StringOsc::setFrequency(float frequency)
{
    fFrequency[0] = frequency + frequency;
    fFrequency[1] = frequency;
}

void StringOsc::process(float *const outputs[2], const float *const detune[2], float bend, unsigned count)
{
    float freqs[BufferLimit];

    Settings settings = *fSettings;
    float hpCutoff[] = {settings.highpassUpperCutoff, settings.highpassLowerCutoff};

    for (unsigned osc = 0; osc < 2; ++osc) {
        float baseFrequency = fFrequency[osc] * bend;
        const float *detuneRatio = detune[osc];

        for (unsigned i = 0; i < count; ++i)
            freqs[i] = baseFrequency * detuneRatio[i];

        float *output = outputs[osc];
        fOscillator[osc].process(output, freqs, count);

        OnePoleHPF &filter = fFilter[osc];
        float cutoffRatio = std::exp2(hpCutoff[osc] * (1.0f / 12.0f));
        for (unsigned i = 0; i < count; ++i) {
            float freq = freqs[i];
            filter.setCutoff(cutoffRatio * freq);
            output[i] = filter.process(output[i]);
        }

        #pragma message("TODO: hard clipper not band-limited")
        for (unsigned i = 0; i < count; ++i) {
            float x = output[i];
            x = (x < 0.0f) ? 0.0f : x;
            x -= 0.5f;
            output[i] = x;
        }
    }
}

void StringOsc::clear()
{
    fOscillator[0].clear();
    fOscillator[1].clear();

    fFilter[0].clear();
    fFilter[1].clear();
}
