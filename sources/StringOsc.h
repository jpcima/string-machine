#pragma once
#include "dsp/OnePoleFilter.h"
#include "dsp/PwmOscillator.hpp"
#include "dsp/AsymWaveshaper.hpp"

class StringOsc {
public:
    struct Settings {
        float highpassUpperCutoff = 0;
        float highpassLowerCutoff = 0;
        float pwmDepth = 0;
        float pwmFrequency = 0;
        float enhance = 0;
    };

    void init(const Settings *settings, double sampleRate);

    void setFrequency(float frequency);
    void process(float *const outputs[2], const float *const detune[2], float bend, unsigned count);
    void clear();

private:
    float fSampleRate = 0;
    const Settings *fSettings = nullptr;
    float fFrequency[2] = {};
    PwmOscillator fOscillator[2];
    OnePoleHPF fFilter[2];
    AsymWaveshaper fShaper[2];
};
