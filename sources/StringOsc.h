#pragma once
#include "dsp/OnePoleFilter.h"
#include "OscillatorBlepRect.h"

class StringOsc {
public:
    struct Settings {
        float highpassUpperCutoff = 0;
        float highpassLowerCutoff = 0;
    };

    void init(const Settings *settings, double sampleRate);

    void setFrequency(float frequency);
    void process(float *const outputs[2], const float *const detune[2], float bend, unsigned count);
    void clear();

private:
    float fSampleRate = 0;
    const Settings *fSettings = nullptr;
    float fFrequency[2] = {};
    OscillatorBlepRect fOscillator[2];
    OnePoleHPF fFilter[2];
};
