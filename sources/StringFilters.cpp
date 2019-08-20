#include "StringFilters.h"
#include <algorithm>
#include <cmath>

void StringFilters::init(const Settings *settings, double sampleRate)
{
    fSampleRate = sampleRate;
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
    float nyquistFreq = 0.5 * fSampleRate;

    OnePoleLPF &lowpassUpper = fLowpassUpper;
    OnePoleHPF &highpassUpper = fHighpassUpper;
    OnePoleLPF &lowpassLower = fLowpassLower;
    OnePoleHPF &highpassLower = fHighpassLower;
    HighshelfFilter &highshelfEq = fHighshelfEq;

    float upperFreq = noteFreq + noteFreq;

    double cutoffMin = 10.0;
    double cutoffMax = 0.9 * nyquistFreq;

    auto limitCutoff = [cutoffMin, cutoffMax](double f) -> double
                           {
                               f = (f > cutoffMin) ? f : cutoffMin;
                               f = (f < cutoffMax) ? f : cutoffMax;
                               return f;
                           };

    lowpassUpper.setCutoff(limitCutoff(upperFreq * std::exp2(settings.lowpassUpperCutoff * (1.0f / 12.0f))));
    highpassUpper.setCutoff(limitCutoff(upperFreq * std::exp2(settings.highpassUpperCutoff * (1.0f / 12.0f))));
    lowpassLower.setCutoff(limitCutoff(noteFreq * std::exp2(settings.lowpassLowerCutoff * (1.0f / 12.0f))));
    highpassLower.setCutoff(limitCutoff(upperFreq * std::exp2(settings.highpassLowerCutoff * (1.0f / 12.0f))));
    highshelfEq.setCutoff(limitCutoff(upperFreq * std::exp2(settings.highshelfEqCutoff * (1.0f / 12.0f))));
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

///
#include "dsp/StringFiltersHighshelfDsp.cpp"

StringFilters::HighshelfFilter::HighshelfFilter()
    : fDsp(new StringFiltersHighshelfDsp)
{
}

StringFilters::HighshelfFilter::~HighshelfFilter()
{
}

void StringFilters::HighshelfFilter::init(double sampleRate)
{
    fDsp->classInit(sampleRate);
    fDsp->instanceConstants(sampleRate);

    clear();
}

void StringFilters::HighshelfFilter::clear()
{
    fDsp->instanceClear();
}

void StringFilters::HighshelfFilter::process(const float *input, float *output, unsigned count)
{
    float *inputs[] = {(float *)input};
    float *outputs[] = {(float *)output};
    fDsp->compute(count, inputs, outputs);
}

void StringFilters::HighshelfFilter::setCutoff(float value)
{
    StringFiltersHighshelfDsp_meta::set_Cutoff(*fDsp, value);
}

void StringFilters::HighshelfFilter::setGain(float value)
{
    StringFiltersHighshelfDsp_meta::set_Gain(*fDsp, value);
}
