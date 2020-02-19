#pragma once
#include "dsp/OnePoleFilter.h"
#include "dsp/PwmOscillator.hpp"
#include "dsp/AsymWaveshaper.hpp"

class BassOsc {
public:
    struct Settings {
        float highpassCutoff = 0;
        float pwmDepth = 0;
        float pwmFrequency = 0;
        float enhance = 0;
    };

    void init(const Settings *settings, double sampleRate);

    void setFrequency(float frequency);
    void process(float *const output, const float *const detune, float bend, unsigned count);
    void clear();

private:
    float fSampleRate = 0;
    const Settings *fSettings = nullptr;
    float fFrequency = 0;
    PwmOscillator fOscillator;
    OnePoleHPF fFilter;
    AsymWaveshaper fShaper;
};
