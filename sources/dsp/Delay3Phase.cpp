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
        fDigital.process(input, mods[0], mods[1], mods[2], outputs[0], outputs[1], outputs[2], count);
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

void Delay3Phase::AnalogDelay::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;

    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].setup(sampleRate, NumAnalogBBDStages, bbd_fin_j60, bbd_fout_j60);

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

    ///
    float avgDelay = 5e-3f;
    float varDelay = 1e-3f;
    float delayClockLo = BBD_Line::hz_rate_for_delay(avgDelay - varDelay, NumAnalogBBDStages) * sampleTime;
    float delayClockHi = BBD_Line::hz_rate_for_delay(avgDelay + varDelay, NumAnalogBBDStages) * sampleTime;

    ///
    for (unsigned l = 0; l < 3; ++l) {
        BBD_Line &line = fDelayLine[l];
        float *lineOutput = lineOutputs[l];
        const float *mod = mods[l];

        float clock[BufferLimit];
        for (unsigned i = 0; i < count; ++i)
            clock[i] = delayClockLo + (delayClockHi - delayClockLo) * 0.5f * (1.0f + mod[i]);

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
