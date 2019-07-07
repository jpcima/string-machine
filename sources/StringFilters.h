#pragma once
#include "dsp/OnePoleFilter.h"

class StringFilters {
public:
    struct Settings {
        float lowpassUpperCutoff;
        float highpassUpperCutoff;
        float lowpassLowerCutoff;
        float highpassLowerCutoff;
        float highshelfEqCutoff;
        float highshelfEqBoost;
    };

    void init(const Settings *settings, double sampleRate);

    void process(const float *const inputs[2], float *const outputs[3], float noteFreq, unsigned count);

private:
    float fSampleTime;

    const Settings *fSettings;

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
        float fHslider0;
        float fHslider1;
        float fConst0;
        float fRec0[3];
    };

    HighshelfFilter fHighshelfEq;
};
