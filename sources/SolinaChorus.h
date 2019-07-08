#pragma once
#include "dsp/LFO3PhaseDual.h"
#include "dsp/Delay3Phase.h"

class SolinaChorus {
public:
    void init(double sampleRate);
    void process(const float *input, float *const outputs[3], unsigned count);

    bool getEnabled() const { return fEnabled; }
    void setEnabled(bool enabled) { fEnabled = enabled; }

    const LFO3PhaseDual &getLfo() const { return fLfo; }
    LFO3PhaseDual &getLfo() { return fLfo; }

private:
    bool fEnabled;
    LFO3PhaseDual fLfo;
    Delay3Phase fDelay;
};
