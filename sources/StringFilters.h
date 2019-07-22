#pragma once
#include "dsp/OnePoleFilter.h"

class StringFilters {
public:
    struct Settings {
        float lowpassUpperCutoff = 0;
        float highpassUpperCutoff = 0;
        float lowpassLowerCutoff = 0;
        float highpassLowerCutoff = 0;
        float highshelfEqCutoff = 0;
        float highshelfEqBoost = 0;
    };

    void init(const Settings *settings, double sampleRate);

    void process(const float *const inputs[2], float *const outputs[3], float noteFreq, unsigned count);

private:
    float fSampleRate = 0;
    float fSampleTime = 0;

    const Settings *fSettings = nullptr;

    OnePoleLPF fLowpassUpper;
    OnePoleHPF fHighpassUpper;
    OnePoleLPF fLowpassLower;
    OnePoleHPF fHighpassLower;

    class HighshelfFilter {
    public:
        void init(double sampleRate);
        void clear();
        void process(const float *input, float *output, unsigned count);

        void setCutoff(float value) { fHslider1 = value; }
        void setGain(float value) { fHslider0 = value; }

    private:
        float fHslider0 = 0;
        float fHslider1 = 0;
        float fConst0 = 0;
        float fRec0[3] = {};
    };

    HighshelfFilter fHighshelfEq;
};
