#pragma once
#include "dsp/LFO3PhaseDual.h"
#include "dsp/Delay3Phase.h"

class SolinaChorus {
public:
    void init(double sampleRate);
    void clear() { fDelay.clear(); }
    void process(const float *input, float *const outputs[3], unsigned count);

    bool getEnabled() const { return fEnabled; }
    void setEnabled(bool enabled) { fEnabled = enabled; }

    const LFO3PhaseDual &getLfo() const { return fLfo; }
    LFO3PhaseDual &getLfo() { return fLfo; }

    float getPhase1() const { return fLfo.getPhase1(); }
    float getPhase2() const { return fLfo.getPhase2(); }

    bool getAnalogMode() const { return fDelay.getAnalogMode(); }
    void setAnalogMode(bool analog) { fDelay.setAnalogMode(analog); }

private:
    bool fEnabled = false;
    LFO3PhaseDual fLfo;
    Delay3Phase fDelay;
};
