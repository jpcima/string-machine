#include "SolinaChorus.h"
#include "StringSynthDefs.h"
#include <cmath>
#include <cstring>

using StringSynthDefs::BufferLimit;

void SolinaChorus::init(double sampleRate)
{
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

    if (fEnabled)
        fDelay.process(input, lfoOuts, outputs, count);
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
