#include "Delay3PhaseStereo.h"
#include "bbd/bbd_filter.h"
#include "../StringSynthDefs.h"
#include <algorithm>
#include <cmath>

using StringSynthDefs::BufferLimit;

///
void Delay3PhaseStereo::init(double sampleRate)
{
    fAnalog.init(sampleRate);
    fDigital.init(sampleRate);
}

void Delay3PhaseStereo::clear()
{
    if (fAnalogMode)
        fAnalog.clear();
    else
        fDigital.clear();
}

void Delay3PhaseStereo::process(const float *const inputs[2], const float *const mods[3], float *const outputs[2], unsigned count)
{
    float line1L[BufferLimit];
    float line2L[BufferLimit];
    float line3L[BufferLimit];
    float line1R[BufferLimit];
    float line2R[BufferLimit];
    float line3R[BufferLimit];

    if (fAnalogMode) {
        float *lines[] = {line1L, line2L, line3L, line1R, line2R, line3R};
        fAnalog.process(inputs, mods, lines, count);
    }
    else
        fDigital.process(inputs[0], inputs[1], mods[0], mods[1], mods[2], line1L, line2L, line3L, line1R, line2R, line3R, count);

    float *outputL = outputs[0];
    for (unsigned i = 0; i < count; ++i)
        outputL[i] = line1L[i] + line2L[i] - line3L[i];

    float *outputR = outputs[1];
    for (unsigned i = 0; i < count; ++i)
        outputR[i] = line1R[i] - line2R[i] - line3R[i];
}

void Delay3PhaseStereo::setAnalogMode(bool analog)
{
    if (fAnalogMode == analog)
        return;

    fAnalogMode = analog;
    clear();
}

///
static constexpr unsigned NumAnalogBBDStages = 185; // the TCA-350-Y IC

void Delay3PhaseStereo::AnalogDelay::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;

    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].setup(sampleRate, NumAnalogBBDStages, bbd_fin_j60, bbd_fout_j60);

    clear();
}

void Delay3PhaseStereo::AnalogDelay::clear()
{
    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].clear();
}

void Delay3PhaseStereo::AnalogDelay::process(const float *const inputs[2], const float *const mods[3], float *const outputs[6], unsigned count)
{
    float sampleTime = fSampleTime;

    ///
    float avgDelay = 5e-3f;
    float varDelay = 1e-3f;
    float delayClockLo = BBD_Line<1>::hz_rate_for_delay(avgDelay - varDelay, NumAnalogBBDStages) * sampleTime;
    float delayClockHi = BBD_Line<1>::hz_rate_for_delay(avgDelay + varDelay, NumAnalogBBDStages) * sampleTime;

    ///
    for (unsigned l = 0; l < 3; ++l) {
        BBD_Line<2> &line = fDelayLine[l];
        float *outputL = outputs[l];
        float *outputR = outputs[l + 3];
        const float *mod = mods[l];

        float clock[BufferLimit];
        for (unsigned i = 0; i < count; ++i)
            clock[i] = delayClockLo + (delayClockHi - delayClockLo) * 0.5f * (1.0f + mod[i]);

        float *bbdOutputs[] = {outputL, outputR};
        line.process(count, inputs, bbdOutputs, clock);
    }
}
