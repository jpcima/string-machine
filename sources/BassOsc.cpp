#include "BassOsc.h"
#include "StringSynthDefs.h"
#include <cstdio>

using StringSynthDefs::BufferLimit;

void BassOsc::init(const Settings *settings, double sampleRate)
{
    fSampleRate = sampleRate;
    fSettings = settings;

    fOscillator.init(sampleRate);
    fFilter.init(sampleRate);
    fShaper.init(sampleRate);
}

void BassOsc::setFrequency(float frequency)
{
    fFrequency = 0.5f * frequency;
}

void BassOsc::process(float *const output, const float *const detune, float bend, unsigned count)
{
    float freqs[BufferLimit];

    Settings settings = *fSettings;
    float nyquistFreq = 0.5 * fSampleRate;
    float hpCutoff = settings.highpassCutoff;
    float enhance = settings.enhance;

    double cutoffMin = 10.0;
    double cutoffMax = 0.9 * nyquistFreq;

    auto limitCutoff = [cutoffMin, cutoffMax](double f) -> double
                           {
                               f = (f > cutoffMin) ? f : cutoffMin;
                               f = (f < cutoffMax) ? f : cutoffMax;
                               return f;
                           };

    float baseFrequency = fFrequency * bend;

    for (unsigned i = 0; i < count; ++i)
        freqs[i] = baseFrequency * detune[i];

    PwmOscillator &oscillator = fOscillator;
    oscillator.set_mod_depth(settings.pwmDepth);
    oscillator.set_mod_frequency(settings.pwmFrequency);
    oscillator.process(freqs, output, count);

    OnePoleHPF &filter = fFilter;
    float cutoffRatio = std::exp2(hpCutoff * (1.0f / 12.0f));
    for (unsigned i = 0; i < count; ++i) {
        float freq = freqs[i];
        filter.setCutoff(limitCutoff(cutoffRatio * freq));
        output[i] = filter.process(output[i]);
    }

    if (1) {
        AsymWaveshaper &shaper = fShaper;
        shaper.set_amount(1.0f - enhance);
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

void BassOsc::clear()
{
    fOscillator.clear();

    fFilter.clear();
}
