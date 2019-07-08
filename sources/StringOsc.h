#pragma once
#include "dsp/OnePoleFilter.h"
#include "OscillatorBlepRect.h"

class StringOsc {
public:
    struct Settings {
        float highpassUpperCutoff;
        float highpassLowerCutoff;
    };

    void init(const Settings *settings, double sampleRate);

    void setFrequency(float frequency);
    void process(float *const outputs[2], const float *const detune[2], unsigned count);
    void clear();

private:
    const Settings *fSettings;
    float fFrequency[2];
    OscillatorBlepRect fOscillator[2];
    OnePoleHPF fFilter[2];
};
