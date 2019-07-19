#pragma once

class Delay3Phase {
public:
    void init(double sampleRate);
    void clear();
    void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

private:
    int IOTA = 0;
    float fConst0 = 0;
    int iConst1 = 0;
    float fVec0[16384] = {};
};
