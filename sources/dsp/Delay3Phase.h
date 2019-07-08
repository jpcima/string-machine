#pragma once

class Delay3Phase {
public:
    void init(double sampleRate);
    void clear();
    void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

private:
    int fSamplingFreq;
    int IOTA;
    float fConst0;
    int iConst1;
    float fVec0[16384];
};
