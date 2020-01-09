#include "StringOsc.h"
#include "StringSynthDefs.h"
#include <cstdio>

using StringSynthDefs::BufferLimit;

void StringOsc::init(const Settings *settings, double sampleRate)
{
    fSampleRate = sampleRate;
    fSettings = settings;

    for (unsigned osc = 0; osc < 2; ++osc) {
        fOscillator[osc].init(sampleRate);
        fFilter[osc].init(sampleRate);
        fShaper[osc].init(sampleRate);
    }
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
    float nyquistFreq = 0.5 * fSampleRate;
    float hpCutoff[] = {settings.highpassUpperCutoff, settings.highpassLowerCutoff};

    double cutoffMin = 10.0;
    double cutoffMax = 0.9 * nyquistFreq;

    auto limitCutoff = [cutoffMin, cutoffMax](double f) -> double
                           {
                               f = (f > cutoffMin) ? f : cutoffMin;
                               f = (f < cutoffMax) ? f : cutoffMax;
                               return f;
                           };

    for (unsigned osc = 0; osc < 2; ++osc) {
        float baseFrequency = fFrequency[osc] * bend;
        const float *detuneRatio = detune[osc];

        for (unsigned i = 0; i < count; ++i)
            freqs[i] = baseFrequency * detuneRatio[i];

        float *output = outputs[osc];

        PwmOscillator &oscillator = fOscillator[osc];
        oscillator.set_mod_depth(settings.pwmDepth);
        oscillator.set_mod_frequency(settings.pwmFrequency);
        oscillator.process(freqs, output, count);

        OnePoleHPF &filter = fFilter[osc];
        float cutoffRatio = std::exp2(hpCutoff[osc] * (1.0f / 12.0f));
        for (unsigned i = 0; i < count; ++i) {
            float freq = freqs[i];
            filter.setCutoff(limitCutoff(cutoffRatio * freq));
            output[i] = filter.process(output[i]);
        }

        if (1) {
            AsymWaveshaper &shaper = fShaper[osc];
            shaper.set_amount(1.0f - settings.enhance);
            shaper.process(output, output, count);
        }
        else {
            // old hard clipper, not band-limited
            for (unsigned i = 0; i < count; ++i) {
                float x = output[i];
                x = (x < 0.0f) ? 0.0f : x;
                x -= 0.5f;
                output[i] = x;
            }
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
