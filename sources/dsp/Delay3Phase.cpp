#include "Delay3Phase.h"
#include "bbd/bbd_filter.h"
#include "../StringSynthDefs.h"
#include <algorithm>
#include <cmath>

using StringSynthDefs::BufferLimit;

///
void Delay3Phase::init(double sampleRate)
{
    fAnalog.init(sampleRate);
    fDigital.init(sampleRate);
}

void Delay3Phase::clear()
{
    if (fAnalogMode)
        fAnalog.clear();
    else
        fDigital.clear();
}

void Delay3Phase::process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count)
{
    if (fAnalogMode)
        fAnalog.process(input, mods, outputs, count);
    else
        fDigital.process(input, mods, outputs, count);
}

void Delay3Phase::setAnalogMode(bool analog)
{
    if (fAnalogMode == analog)
        return;

    fAnalogMode = analog;
    clear();
}

///
static constexpr unsigned NumAnalogBBDStages = 185; // the TCA-350-Y IC
extern const BBD_Filter_Spec bbd_fout_custom;

void Delay3Phase::AnalogDelay::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;

    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].setup(sampleRate, NumAnalogBBDStages, bbd_fin_j60, bbd_fout_custom);

    clear();
}

void Delay3Phase::AnalogDelay::clear()
{
    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].clear();
}

void Delay3Phase::AnalogDelay::process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count)
{
    float sampleTime = fSampleTime;

    float lineOutputs[3][BufferLimit];

    for (unsigned l = 0; l < 3; ++l) {
        BBD_Line &line = fDelayLine[l];
        float *lineOutput = lineOutputs[l];
        const float *mod = mods[l];

        float clock[BufferLimit];
        for (unsigned i = 0; i < count; ++i)
            clock[i] = BBD_Line::hz_rate_for_delay(5e-3f + (1e-3f * mod[i]), NumAnalogBBDStages) * sampleTime;

        line.process(count, input, lineOutput, clock);
    }

    float *outputL = outputs[0];
    for (unsigned i = 0; i < count; ++i)
        outputL[i] = lineOutputs[0][i] + lineOutputs[1][i] - lineOutputs[2][i];

    float *outputR = outputs[1];
    for (unsigned i = 0; i < count; ++i)
        outputR[i] = lineOutputs[0][i] - lineOutputs[1][i] - lineOutputs[2][i];

    float *outputMono = outputs[2];
    for (unsigned i = 0; i < count; ++i)
        outputMono[i] = lineOutputs[0][i] + lineOutputs[1][i] + lineOutputs[2][i];
}

namespace BBDOut {

// 5th order Butterworth 8 kHz

/*
[b,a]=butter(5,2*pi*8000,'low','s');
[r,p,k]=residue(b,a)
*/

static constexpr unsigned M = 5;

static constexpr cdouble R[M] = {
    {95224.2967360951, -5.093170329928398e-11},
    {-6946.518829526461, 21379.18664231187},
    {-6946.518829526442, -21379.18664231189},
    {-40665.62953852107, -55971.43728140101},
    {-40665.62953852112, 55971.43728140108},
};

static constexpr cdouble P[M] = {
    {-50265.48245743721, 0},
    {-15532.88830980377, 47805.31463586497},
    {-15532.88830980377, -47805.31463586497},
    {-40665.62953852185, 29545.30928784726},
    {-40665.62953852185, -29545.30928784726},
};

} // namespace BBDOut

const BBD_Filter_Spec bbd_fout_custom = {BBD_Filter_Kind::Input, BBDOut::M, BBDOut::R, BBDOut::P};

///
void Delay3Phase::DigitalDelay::init(double sampleRate)
{
    fAntialiasFilter.init(sampleRate);

    fConst0 = float(sampleRate);
    iConst1 = int(std::ceil((0.0500000007f * fConst0)));

    clear();
}

void Delay3Phase::DigitalDelay::clear()
{
    fAntialiasFilter.clear();

    IOTA = 0;
    for (int l0 = 0; (l0 < 16384); l0 = (l0 + 1)) {
        fVec0[l0] = 0.0f;
    }
}

void Delay3Phase::DigitalDelay::process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count)
{
    float input0[BufferLimit];
    fAntialiasFilter.process(input, input0, count);

    const float* input1 = mods[0];
    const float* input2 = mods[1];
    const float* input3 = mods[2];
    float* output0 = outputs[0];
    float* output1 = outputs[1];
    float* output2 = outputs[2];

    for (unsigned i = 0; (i < count); i = (i + 1)) {
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
