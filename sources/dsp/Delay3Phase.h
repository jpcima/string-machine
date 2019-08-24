#pragma once
#include "bbd/bbd_line.h"
#include "dsp/Delay3PhaseDigital.hpp"

class Delay3PhaseDigitalDsp;

///
class Delay3Phase {
public:
    void init(double sampleRate);
    void clear();
    void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

    bool getAnalogMode() const { return fAnalogMode; }
    void setAnalogMode(bool analog);

private:
    struct AnalogDelay {
    public:
        void init(double sampleRate);
        void clear();
        void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

    private:
        float fSampleTime = 0;
        BBD_Line fDelayLine[3];
    };

private:
    bool fAnalogMode = true;
    AnalogDelay fAnalog;
    Delay3PhaseDigital fDigital;
};
