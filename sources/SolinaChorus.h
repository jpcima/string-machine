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

    float getPhase1() const { return fLfo.getPhase1(); }
    float getPhase2() const { return fLfo.getPhase2(); }

private:
    class AntialiasFilter {
    public:
        void init(double sampleRate);
        void clear();
        void process(const float *input, float *output, unsigned count);

    private:
        float fConst0 = 0;
        float fConst1 = 0;
        float fConst2 = 0;
        float fConst3 = 0;
        float fConst4 = 0;
        float fConst5 = 0;
        float fConst6 = 0;
        float fConst7 = 0;
        float fConst8 = 0;
        float fConst9 = 0;
        float fConst10 = 0;
        float fConst11 = 0;
        float fConst12 = 0;
        float fConst13 = 0;
        float fConst14 = 0;
        float fConst15 = 0;
        float fConst16 = 0;
        float fConst17 = 0;
        float fRec0[3] = {};
        float fRec1[3] = {};
        float fRec2[3] = {};
    };

private:
    bool fEnabled = false;
    AntialiasFilter fFilter;
    LFO3PhaseDual fLfo;
    Delay3Phase fDelay;
};
