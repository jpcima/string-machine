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

///
#include "dsp/Delay3PhaseDigitalDsp.cpp"

Delay3Phase::DigitalDelay::DigitalDelay()
    : fDsp(new Delay3PhaseDigitalDsp)
{
    fDsp->instanceResetUserInterface();
}

Delay3Phase::DigitalDelay::~DigitalDelay()
{
}

void Delay3Phase::DigitalDelay::init(double sampleRate)
{
    fDsp->classInit(sampleRate);
    fDsp->instanceConstants(sampleRate);

    clear();
}

void Delay3Phase::DigitalDelay::clear()
{
    fDsp->instanceClear();
}

void Delay3Phase::DigitalDelay::process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count)
{
    float *inputs[] = {(float *)input, (float *)mods[0], (float *)mods[1], (float *)mods[2]};
    fDsp->compute(count, inputs, (float **)outputs);
}
