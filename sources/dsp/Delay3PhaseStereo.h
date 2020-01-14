#pragma once
#include "bbd/bbd_line.h"
#include "dsp/Delay3PhaseDigitalStereo.hpp"

class Delay3PhaseStereo {
public:
    void init(double sampleRate);
    void clear();
    void process(const float *const inputs[2], const float *const mods[3], float *const outputs[2], unsigned count);

    bool getAnalogMode() const { return fAnalogMode; }
    void setAnalogMode(bool analog);

private:
    struct AnalogDelay {
    public:
        void init(double sampleRate);
        void clear();
        void process(const float *const inputs[2], const float *const mods[3], float *const outputs[6], unsigned count);

    private:
        float fSampleTime = 0;
        BBD_Line<2> fDelayLine[3];
    };

private:
    bool fAnalogMode = true;
    AnalogDelay fAnalog;
    Delay3PhaseDigitalStereo fDigital;
};
