#pragma once
#include "dsp/LFO3PhaseDual.hpp"
#include "dsp/Delay3PhaseStereo.h"

class SolinaChorusStereo {
public:
    void init(double sampleRate);
    void clear() { fDelay.clear(); }
    void process(const float *inputs[2], float *const outputs[2], unsigned count);

    bool getEnabled() const { return fEnabled; }
    void setEnabled(bool enabled) { fEnabled = enabled; }

    const LFO3PhaseDual &getLfo() const { return fLfo; }
    LFO3PhaseDual &getLfo() { return fLfo; }

    float getPhase1() const { return fLfo.get_phase1(); }
    float getPhase2() const { return fLfo.get_phase2(); }

    bool getAnalogMode() const { return fDelay.getAnalogMode(); }
    void setAnalogMode(bool analog) { fDelay.setAnalogMode(analog); }

private:
    bool fEnabled = false;
    LFO3PhaseDual fLfo;
    Delay3PhaseStereo fDelay;
};
