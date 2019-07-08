#include "Delay3Phase.h"
#include "bbd/bbd_filter.h"
#include "../StringSynthDefs.h"
#include <algorithm>
#include <cmath>

using StringSynthDefs::BufferLimit;

static constexpr unsigned NumStages = 512;

void Delay3Phase::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;

    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].setup(sampleRate, NumStages, bbd_fin_j60, bbd_fout_j60);

    clear();
}

void Delay3Phase::clear()
{
    for (unsigned l = 0; l < 3; ++l)
        fDelayLine[l].clear();
}

void Delay3Phase::process(const float *input, const float *const mods[3], float *const outputs[3], unsigned count)
{
    float sampleTime = fSampleTime;

    float lineOutputs[3][BufferLimit];

    for (unsigned l = 0; l < 3; ++l) {
        BBD_Line &line = fDelayLine[l];
        float *lineOutput = lineOutputs[l];
        const float *mod = mods[l];

        float clock[BufferLimit];
        for (unsigned i = 0; i < count; ++i)
            clock[i] = BBD_Line::hz_rate_for_delay(5e-3f + (1e-3f * mod[i]), NumStages) * sampleTime;

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

/**
import("stdfaust.lib");

process(x, mod1, mod2, mod3) =
  L, R, Mono
with {
  line(x, mod) = de.fdelayltv(1, delaybufsize, delay, x) with {
    delaybufsize = int(ceil(50e-3 * ma.SR));
    delay = (5e-3 + (1e-3 * mod)) * ma.SR;
  };

  line1 = line(x, mod1);
  line2 = line(x, mod2);
  line3 = line(x, mod3);

  L = line1 + line2 - line3;
  R = line1 - line2 - line3;
  Mono = line1 + line2 + line3;
};
*/
