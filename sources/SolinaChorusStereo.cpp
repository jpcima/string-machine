#include "SolinaChorusStereo.h"
#include "StringSynthDefs.h"
#include <cmath>
#include <cstring>

using StringSynthDefs::BufferLimit;

void SolinaChorusStereo::init(double sampleRate)
{
    fLfo.init(sampleRate);
    fDelay.init(sampleRate);
}

void SolinaChorusStereo::process(const float *inputs[2], float *const outputs[2], unsigned count)
{
    float lfoOut0[BufferLimit];
    float lfoOut120[BufferLimit];
    float lfoOut240[BufferLimit];
    float *lfoOuts[] = {lfoOut0, lfoOut120, lfoOut240};

    fLfo.process(lfoOut0, lfoOut120, lfoOut240, count);

    if (fEnabled)
        fDelay.process(inputs, lfoOuts, outputs, count);
    else {
        float discardBuffer[2][BufferLimit];
        float *discardOutputs[] = {discardBuffer[0], discardBuffer[1]};
        fDelay.process(inputs, lfoOuts, discardOutputs, count);

        const float *inputL = inputs[0];
        const float *inputR = inputs[1];
        float *outputL = outputs[0];
        float *outputR = outputs[1];

        if (outputL != inputL)
            memcpy(outputL, inputL, count * sizeof(float));
        if (outputR != inputR)
            memcpy(outputL, inputR, count * sizeof(float));
    }
}
