#pragma once
#include "DelayAntialiasFilter.h"
#include "bbd/bbd_line.h"

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

    class DigitalDelay {
    public:
        void init(double sampleRate);
        void clear();
        void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

    private:
        DelayAntialiasFilter fAntialiasFilter;
        int IOTA = 0;
        float fConst0 = 0;
        int iConst1 = 0;
        float fVec0[16384] = {};
    };

private:
    bool fAnalogMode = true;
    AnalogDelay fAnalog;
    DigitalDelay fDigital;
};
