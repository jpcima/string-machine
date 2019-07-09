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
        float phase;
        float phase0;
    };

    struct RowLFOs {
        float rate;
        float depth;
        SingleLFO lfos[3];
    };

    float fSampleTime;
    float fDepth;
    RowLFOs fRowsLFO[2];
    SmoothFilter fSmoothOutput[3];
};
