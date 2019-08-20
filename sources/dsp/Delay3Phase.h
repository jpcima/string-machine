#pragma once
#include "bbd/bbd_line.h"
#include <memory>

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

    class DigitalDelay {
    public:
        DigitalDelay();
        ~DigitalDelay();
        void init(double sampleRate);
        void clear();
        void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

    private:
        std::unique_ptr<Delay3PhaseDigitalDsp> fDsp;
    };

private:
    bool fAnalogMode = true;
    AnalogDelay fAnalog;
    DigitalDelay fDigital;
};
