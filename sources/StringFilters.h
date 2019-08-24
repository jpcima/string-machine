#pragma once
#include "dsp/OnePoleFilter.h"
#include "dsp/StringFiltersHighshelf.hpp"
#include <memory>

class StringFiltersHighshelfDsp;

///
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
    StringFiltersHighshelf fHighshelfEq;
};
