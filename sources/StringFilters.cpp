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
    fFormant.init(sampleRate);
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
    FormantFilter &formant = fFormant;

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
    formant.setCutoff(limitCutoff(noteFreq * std::exp2(settings.formantCutoff * (1.0f / 12.0f))));

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
        outputLower[i] = highpassLower.process(lowpassLower.process(inputLower[i]));

    for (unsigned i = 0; i < count; ++i)
        outputBrass[i] = inputUpper[i] + inputLower[i];
    formant.process(outputBrass, outputBrass, count);
}

void StringFilters::HighshelfFilter::init(double sampleRate)
{
    fConst0 = (6.28318548f / float(sampleRate));

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

void StringFilters::FormantFilter::init(double sampleRate)
{
    fConst0 = (6.28318548f / float(sampleRate));
}

void StringFilters::FormantFilter::clear()
{
    for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
        fRec1[l0] = 0.0f;
    }
    for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
        fRec0[l1] = 0.0f;
    }
}

void StringFilters::FormantFilter::process(const float *input, float *output, unsigned count)
{
    const float* input0 = input;
    float* output0 = output;
    float fSlow0 = float(fHslider0);
    float fSlow1 = (fConst0 * std::max<float>(0.0f, (0.0666666701f * fSlow0)));
    float fSlow2 = std::sin(fSlow1);
    float fSlow3 = (1.25f * fSlow2);
    float fSlow4 = (fSlow3 + 1.0f);
    float fSlow5 = (1.25f * (fSlow2 / fSlow4));
    float fSlow6 = (fConst0 * std::max<float>(0.0f, fSlow0));
    float fSlow7 = std::sin(fSlow6);
    float fSlow8 = (0.125f * fSlow7);
    float fSlow9 = (fSlow8 + 1.0f);
    float fSlow10 = (0.125f * (fSlow7 / fSlow9));
    float fSlow11 = (1.0f / fSlow9);
    float fSlow12 = (0.0f - (2.0f * std::cos(fSlow6)));
    float fSlow13 = (1.0f - fSlow8);
    float fSlow14 = (0.0f - fSlow10);
    float fSlow15 = (1.0f / fSlow4);
    float fSlow16 = (0.0f - (2.0f * std::cos(fSlow1)));
    float fSlow17 = (1.0f - fSlow3);
    float fSlow18 = (0.0f - fSlow5);
    for (unsigned i = 0; (i < count); i = (i + 1)) {
        fRec1[0] = (float(input0[i]) - (fSlow11 * ((fSlow12 * fRec1[1]) + (fSlow13 * fRec1[2]))));
        fRec0[0] = (((fSlow10 * fRec1[0]) + (fSlow14 * fRec1[2])) - (fSlow15 * ((fSlow16 * fRec0[1]) + (fSlow17 * fRec0[2]))));
        output0[i] = float((7.94328213f * ((fSlow5 * fRec0[0]) + (fSlow18 * fRec0[2]))));
        fRec1[2] = fRec1[1];
        fRec1[1] = fRec1[0];
        fRec0[2] = fRec0[1];
        fRec0[1] = fRec0[0];
    }
}

/**
import("stdfaust.lib");
mm = library("maxmsp.lib");

baseFreq = hslider("Cutoff [unit:Hz]", 1200.0, 0.0, 5000.0, 1.0);

freq1Ratio = 1.0;
freq2Ratio = 1.0 / 15.0;

bp1Cutoff = baseFreq * freq1Ratio;
bp1Q = 4.0; //hslider("BP1 Q", 4.0, 0.1, 20.0, 0.1);

bp2Cutoff = baseFreq * freq2Ratio;
bp2Q = 0.4; //hslider("BP2 Q", 0.4, 0.1, 20.0, 0.1);

gain = ba.db2linear(18.0); //hslider("Gain", 18.0, 0.0, +40.0, 1.0) : ba.db2linear;

process = bp1 : bp2 : *(gain) with {
  bp1(x) = mm.BPF(x, bp1Cutoff, 0., bp1Q);
  bp2(x) = mm.BPF(x, bp2Cutoff, 0., bp2Q);
};
 */
