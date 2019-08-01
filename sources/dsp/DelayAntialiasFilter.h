#pragma once

class DelayAntialiasFilter {
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
