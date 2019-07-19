#pragma once
#include "SmoothFilter.h"

class LFO3PhaseDual {
public:
    void init(double sampleRate);

    void process(float *outputs[3], unsigned count);

    float getDepth() const { return fDepth; }
    void setDepth(float value) { fDepth = value; }

    float getDepth1() const { return fRowsLFO[0].depth; }
    void setDepth1(float value) { fRowsLFO[0].depth = value; }
    float getDepth2() const { return fRowsLFO[1].depth; }
    void setDepth2(float value) { fRowsLFO[1].depth = value;}

    float getRate1() const { return fRowsLFO[0].rate; }
    void setRate1(float value) { fRowsLFO[0].rate = value; }
    float getRate2() const { return fRowsLFO[1].rate; }
    void setRate2(float value) { fRowsLFO[1].rate = value;}

    float getPhase1() const { return fRowsLFO[0].lfos[0].phase; }
    float getPhase2() const { return fRowsLFO[1].lfos[0].phase; }

private:
    static float getLfoSine(float phase);
    static float wrapPhase(float phase);

private:
    struct SingleLFO {
        float phase = 0;
        float phase0 = 0;
    };

    struct RowLFOs {
        float rate = 0;
        float depth = 0;
        SingleLFO lfos[3];
    };

    float fSampleTime = 0;
    float fDepth = 0;
    RowLFOs fRowsLFO[2];
    SmoothFilter fSmoothOutput[3];
};
