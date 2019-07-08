#pragma once
#include "bbd/bbd_line.h"

class Delay3Phase {
public:
    void init(double sampleRate);
    void clear();
    void process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count);

private:
    float fSampleTime;
    BBD_Line fDelayLine[3];
};
