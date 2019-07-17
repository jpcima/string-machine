#include "SolinaChorus.h"
#include "StringSynthDefs.h"
#include <cmath>
#include <cstring>

using StringSynthDefs::BufferLimit;

void SolinaChorus::init(double sampleRate)
{
    fFilter.init(sampleRate);
    fLfo.init(sampleRate);
    fDelay.init(sampleRate);
    fEnabled = false;
}

void SolinaChorus::process(const float *input, float *const outputs[3], unsigned count)
{
    float lfoOut0[BufferLimit];
    float lfoOut120[BufferLimit];
    float lfoOut240[BufferLimit];
    float *lfoOuts[] = {lfoOut0, lfoOut120, lfoOut240};

    fLfo.process(lfoOuts, count);

    float inputAA[BufferLimit];
    fFilter.process(input, inputAA, count);

    if (fEnabled)
        fDelay.process(inputAA, lfoOuts, outputs, count);
    else {
        float discardBuffer[3][BufferLimit];
        float *discardOutputs[] = {discardBuffer[0], discardBuffer[1], discardBuffer[2]};
        fDelay.process(input, lfoOuts, discardOutputs, count);

        float *output0 = outputs[0];
        for (unsigned i = 0; i < count; ++i)
            output0[i] = 2.0 * input[i];
        for (unsigned c = 1; c < 3; ++c)
            memcpy(outputs[c], output0, count * sizeof(float));
    }
}

void SolinaChorus::AntialiasFilter::init(double sampleRate)
{
    fConst0 = float(sampleRate);
    fConst1 = (36137.0f / fConst0);
    fConst2 = std::cos(fConst1);
    fConst3 = (0.460000008f * std::sin(fConst1));
    fConst4 = (fConst3 + 1.0f);
    fConst5 = ((1.0f - fConst2) / fConst4);
    fConst6 = (60076.8906f / fConst0);
    fConst7 = std::cos(fConst6);
    fConst8 = (1.0f - fConst7);
    fConst9 = (0.340000004f * std::sin(fConst6));
    fConst10 = (fConst9 + 1.0f);
    fConst11 = (fConst8 / fConst10);
    fConst12 = (1.0f / fConst10);
    fConst13 = (0.0f - (2.0f * fConst7));
    fConst14 = (1.0f - fConst9);
    fConst15 = (1.0f / fConst4);
    fConst16 = (0.0f - (2.0f * fConst2));
    fConst17 = (1.0f - fConst3);

    clear();
}

void SolinaChorus::AntialiasFilter::clear()
{
    for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
        fRec2[l0] = 0.0f;
    }
    for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
        fRec1[l1] = 0.0f;
    }
    for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
        fRec0[l2] = 0.0f;
    }
}

void SolinaChorus::AntialiasFilter::process(const float *input, float *output, unsigned count)
{
    const float* input0 = input;
    float* output0 = output;
    for (unsigned i = 0; (i < count); i = (i + 1)) {
        fRec2[0] = (float(input0[i]) - (fConst12 * ((fConst13 * fRec2[1]) + (fConst14 * fRec2[2]))));
        fRec1[0] = (0.0f - (fConst12 * (((fConst13 * fRec1[1]) + (fConst14 * fRec1[2])) - (fConst8 * ((fRec2[1] + (0.5f * fRec2[0])) + (0.5f * fRec2[2]))))));
        fRec0[0] = ((fConst11 * ((fRec1[1] + (0.5f * fRec1[0])) + (0.5f * fRec1[2]))) - (fConst15 * ((fConst16 * fRec0[1]) + (fConst17 * fRec0[2]))));
        output0[i] = float((fConst5 * ((fRec0[1] + (0.5f * fRec0[0])) + (0.5f * fRec0[2]))));
        fRec2[2] = fRec2[1];
        fRec2[1] = fRec2[0];
        fRec1[2] = fRec1[1];
        fRec1[1] = fRec1[0];
        fRec0[2] = fRec0[1];
        fRec0[1] = fRec0[0];
    }
}

/**
import("stdfaust.lib");
msp = library("maxmsp.lib");

process = lpf1 : lpf2 : lpf3 with {
        cutoff1 = ba.midikey2hz(122.3);
        cutoff2 = ba.midikey2hz(122.3);
        cutoff3 = ba.midikey2hz(113.5);

        q1 = resonance(0.66);
        q2 = resonance(0.66);
        q3 = resonance(0.54);

        resonance(r) = 1. / (2. - 2. * r);

        lpf1(x) = msp.LPF(x, cutoff1, 0, q1);
        lpf2(x) = msp.LPF(x, cutoff2, 0, q2);
        lpf3(x) = msp.LPF(x, cutoff3, 0, q3);
};
*/
