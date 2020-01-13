#include "SolinaChorus.h"
#include "StringSynthDefs.h"
#include <cmath>
#include <cstring>

using StringSynthDefs::BufferLimit;

void SolinaChorus::init(double sampleRate)
{
    fLfo.init(sampleRate);
    fDelay.init(sampleRate);
}

void SolinaChorus::process(const float *input, float *const outputs[3], unsigned count)
{
    float lfoOut0[BufferLimit];
    float lfoOut120[BufferLimit];
    float lfoOut240[BufferLimit];
    float *lfoOuts[] = {lfoOut0, lfoOut120, lfoOut240};

    fLfo.process(lfoOut0, lfoOut120, lfoOut240, count);

    if (fEnabled)
        fDelay.process(input, lfoOuts, outputs, count);
    else {
        float discardBuffer[3][BufferLimit];
        float *discardOutputs[] = {discardBuffer[0], discardBuffer[1], discardBuffer[2]};
        fDelay.process(input, lfoOuts, discardOutputs, count);

        float *outputL = outputs[0];
        float *outputR = outputs[1];

        if (outputL != input)
            memcpy(outputL, input, count * sizeof(float));
        if (outputR != outputL)
            memcpy(outputR, outputL, count * sizeof(float));
    }
}
