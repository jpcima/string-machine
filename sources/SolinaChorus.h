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
    class AntialiasFilter {
    public:
        void init(double sampleRate);
        void clear();
        void process(const float *input, float *output, unsigned count);

    private:
        float fConst0;
        float fConst1;
        float fConst2;
        float fConst3;
        float fConst4;
        float fConst5;
        float fConst6;
        float fConst7;
        float fConst8;
        float fConst9;
        float fConst10;
        float fConst11;
        float fConst12;
        float fConst13;
        float fConst14;
        float fConst15;
        float fConst16;
        float fConst17;
        float fRec0[3];
        float fRec1[3];
        float fRec2[3];
    };

private:
    bool fEnabled;
    AntialiasFilter fFilter;
    LFO3PhaseDual fLfo;
    Delay3Phase fDelay;
};
