#include "StringFilters.h"
#include <algorithm>
#include <cmath>

void StringFilters::init(const Settings *settings, double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;

    fSettings = settings;

    fLowpassUpper.init(sampleRate);
    fHighpassUpper.init(sampleRate);
    fLowpassLower.init(sampleRate);
    fHighpassLower.init(sampleRate);
    fHighshelfEq.init(sampleRate);
}

void StringFilters::process(const float *const inputs[2], float *const outputs[3], float noteFreq, unsigned count)
{
    Settings settings = *fSettings;

    OnePoleLPF &lowpassUpper = fLowpassUpper;
    OnePoleHPF &highpassUpper = fHighpassUpper;
    OnePoleLPF &lowpassLower = fLowpassLower;
    OnePoleHPF &highpassLower = fHighpassLower;
    HighshelfFilter &highshelfEq = fHighshelfEq;

    lowpassUpper.setCutoff(noteFreq * 2 + std::exp2(settings.lowpassUpperCutoff * (1.0f / 12.0f)));
    highpassUpper.setCutoff(noteFreq * 2 + std::exp2(settings.highpassUpperCutoff * (1.0f / 12.0f)));
    lowpassLower.setCutoff(noteFreq + std::exp2(settings.lowpassLowerCutoff * (1.0f / 12.0f)));
    highpassLower.setCutoff(noteFreq * 2 + std::exp2(settings.highpassLowerCutoff * (1.0f / 12.0f)));
    highshelfEq.setCutoff(noteFreq * 2 + std::exp2(settings.highshelfEqCutoff * (1.0f / 12.0f)));
    highshelfEq.setGain(settings.highshelfEqBoost);

    const float *inputUpper = inputs[0];
    const float *inputLower = inputs[1];
    float *outputUpper = outputs[0];
    float *outputLower = outputs[1];
    float *outputBrass = outputs[2];

    for (unsigned i = 0; i < count; ++i)
        outputUpper[i] = lowpassUpper.process(inputUpper[i]);
    for (unsigned i = 0; i < count; ++i)
        outputUpper[i] = highpassUpper.process(outputUpper[i]);
    highshelfEq.process(outputUpper, outputUpper, count);

    for (unsigned i = 0; i < count; ++i)
        outputBrass[i] = lowpassLower.process(inputLower[i]);
    for (unsigned i = 0; i < count; ++i)
        outputLower[i] = highpassLower.process(outputBrass[i]);
}

void StringFilters::HighshelfFilter::init(double sampleRate)
{
    fConst0 = (6.28318548f / float(sampleRate));

    fHslider0 = float(0.0f);
    fHslider1 = float(0.0f);

    clear();
}

void StringFilters::HighshelfFilter::clear()
{
    for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
        fRec0[l0] = 0.0f;
    }
}

void StringFilters::HighshelfFilter::process(const float *input, float *output, unsigned count)
{
    const float* input0 = input;
    float* output0 = output;
    float fSlow0 = std::pow(10.0f, (0.0250000004f * float(fHslider0)));
    float fSlow1 = (fConst0 * std::max<float>(0.0f, float(fHslider1)));
    float fSlow2 = (1.41421354f * (std::sqrt(fSlow0) * std::sin(fSlow1)));
    float fSlow3 = std::cos(fSlow1);
    float fSlow4 = ((fSlow0 + -1.0f) * fSlow3);
    float fSlow5 = (1.0f / ((fSlow0 + fSlow2) + (1.0f - fSlow4)));
    float fSlow6 = (fSlow4 + fSlow0);
    float fSlow7 = (((fSlow6 + fSlow2) + 1.0f) * fSlow0);
    float fSlow8 = (fSlow0 + (1.0f - (fSlow4 + fSlow2)));
    float fSlow9 = ((fSlow0 + 1.0f) * fSlow3);
    float fSlow10 = (2.0f * (fSlow0 + (-1.0f - fSlow9)));
    float fSlow11 = ((0.0f - (2.0f * fSlow0)) * ((fSlow9 + fSlow0) + -1.0f));
    float fSlow12 = ((fSlow6 + (1.0f - fSlow2)) * fSlow0);
    for (unsigned i = 0; (i < count); i = (i + 1)) {
        fRec0[0] = (float(input0[i]) - (fSlow5 * ((fSlow8 * fRec0[2]) + (fSlow10 * fRec0[1]))));
        output0[i] = float((fSlow5 * (((fSlow7 * fRec0[0]) + (fSlow11 * fRec0[1])) + (fSlow12 * fRec0[2]))));
        fRec0[2] = fRec0[1];
        fRec0[1] = fRec0[0];
    }
}

/**
import("stdfaust.lib");
msp = library("maxmsp.lib");

process(x) = msp.highShelf(x, cutoff, gain, 1./sqrt(2.)) with {
  cutoff = hslider("[1]Cutoff [unit:Hz]", 1000., 10., 10000., 1.);
  gain = hslider("[2]Gain [unit:dB]", 3., 1., 10., 0.1);
};
*/
