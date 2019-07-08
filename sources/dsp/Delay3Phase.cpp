#include "Delay3Phase.h"
#include <algorithm>
#include <cmath>

void Delay3Phase::init(double sampleRate)
{
    fSamplingFreq = sampleRate;
    fConst0 = float(sampleRate);
    iConst1 = int(std::ceil((0.0500000007f * fConst0)));

    clear();
}

void Delay3Phase::clear()
{
    IOTA = 0;
    for (int l0 = 0; (l0 < 16384); l0 = (l0 + 1)) {
        fVec0[l0] = 0.0f;
    }
}

void Delay3Phase::process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count)
{
    const float* input0 = input;
    const float* input1 = mods[0];
    const float* input2 = mods[1];
    const float* input3 = mods[2];
    float* output0 = outputs[0];
    float* output1 = outputs[1];
    float* output2 = outputs[2];

    for (int i = 0; (i < count); i = (i + 1)) {
        float fTemp0 = (fConst0 * ((0.00100000005f * float(input2[i])) + 0.00499999989f));
        float fTemp1 = (fTemp0 + 4.99999987e-06f);
        float fTemp2 = std::floor(fTemp1);
        float fTemp3 = float(input0[i]);
        fVec0[(IOTA & 16383)] = fTemp3;
        int iTemp4 = int(fTemp1);
        float fTemp5 = ((fTemp0 - fTemp2) * fVec0[((IOTA - std::min<int>(iConst1, std::max<int>(0, (iTemp4 + 1)))) & 16383)]);
        float fTemp6 = (fConst0 * ((0.00100000005f * float(input1[i])) + 0.00499999989f));
        float fTemp7 = (fTemp6 + 4.99999987e-06f);
        int iTemp8 = int(fTemp7);
        float fTemp9 = std::floor(fTemp7);
        float fTemp10 = ((fVec0[((IOTA - std::min<int>(iConst1, std::max<int>(0, iTemp8))) & 16383)] * (0.0f - (fTemp6 + (-1.0f - fTemp9)))) + ((fTemp6 - fTemp9) * fVec0[((IOTA - std::min<int>(iConst1, std::max<int>(0, (iTemp8 + 1)))) & 16383)]));
        float fTemp11 = (fVec0[((IOTA - std::min<int>(iConst1, std::max<int>(0, iTemp4))) & 16383)] * (0.0f - (fTemp0 + (-1.0f - fTemp2))));
        float fTemp12 = (fTemp5 + (fTemp10 + fTemp11));
        float fTemp13 = (fConst0 * ((0.00100000005f * float(input3[i])) + 0.00499999989f));
        float fTemp14 = (fTemp13 + 4.99999987e-06f);
        int iTemp15 = int(fTemp14);
        float fTemp16 = std::floor(fTemp14);
        float fTemp17 = (fVec0[((IOTA - std::min<int>(iConst1, std::max<int>(0, iTemp15))) & 16383)] * (0.0f - (fTemp13 + (-1.0f - fTemp16))));
        float fTemp18 = ((fTemp13 - fTemp16) * fVec0[((IOTA - std::min<int>(iConst1, std::max<int>(0, (iTemp15 + 1)))) & 16383)]);
        output0[i] = float((fTemp12 - (fTemp17 + fTemp18)));
        output1[i] = float((fTemp10 - (fTemp18 + ((fTemp11 + fTemp5) + fTemp17))));
        output2[i] = float((fTemp18 + (fTemp12 + fTemp17)));
        IOTA = (IOTA + 1);
    }
}

/**
import("stdfaust.lib");

process(x, mod1, mod2, mod3) =
  L, R, Mono
with {
  line(x, mod) = de.fdelayltv(1, delaybufsize, delay, x) with {
    delaybufsize = int(ceil(50e-3 * ma.SR));
    delay = (5e-3 + (1e-3 * mod)) * ma.SR;
  };

  line1 = line(x, mod1);
  line2 = line(x, mod2);
  line3 = line(x, mod3);

  L = line1 + line2 - line3;
  R = line1 - line2 - line3;
  Mono = line1 + line2 + line3;
};
*/
