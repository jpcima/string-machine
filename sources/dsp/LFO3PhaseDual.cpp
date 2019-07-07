#include "LFO3PhaseDual.h"
#include <array>
#include <cmath>
#include <cstring>
#include <cassert>

template <unsigned N> std::array<float, N> createLfoSine();
static std::array<float, 128> LfoSine = createLfoSine<128>();

void LFO3PhaseDual::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;

    fDepth = 0.0;

    for (unsigned r = 0; r < 2; ++r) {
        RowLFOs &row = fRowsLFO[r];
        row.rate = 0.0;
        row.depth = 0.0;

        for (unsigned l = 0; l < 3; ++l)
            row.lfos[l].phase = row.lfos[l].phase0 = l / 3.0f;
    }

    for (unsigned l = 0; l < 3; ++l) {
        SmoothFilter &flt = fSmoothOutput[l];
        flt.init(sampleRate);
        flt.setTime(1e-3);
    }
}

void LFO3PhaseDual::process(float *outputs[3], unsigned count)
{
    float sampleTime = fSampleTime;
    float globalDepth = fDepth;
    RowLFOs *rows = fRowsLFO;

    float phaseIncr[2][3];
    for (unsigned r = 0; r < 2; ++r) {
        for (unsigned l = 0; l < 3; ++l)
            phaseIncr[r][l] = rows[r].rate * sampleTime;
    }

    for (unsigned l = 0; l < 3; ++l)
        memset(outputs[l], 0, count * sizeof(float));

    for (unsigned i = 0; i < count; ++i) {
        for (unsigned r = 0; r < 2; ++r) {
            RowLFOs &row = rows[r];
            float rowDepth = globalDepth * row.depth;

            for (unsigned l = 0; l < 3; ++l)
                outputs[l][i] += rowDepth * getLfoSine(row.lfos[l].phase);

            row.lfos[0].phase += phaseIncr[r][0];
            if (row.lfos[0].phase >= 1.0f) {
                row.lfos[0].phase = wrapPhase(row.lfos[0].phase);
                for (unsigned l = 1; l < 3; ++l)
                    row.lfos[l].phase = row.lfos[l].phase0 + row.lfos[0].phase;
            }

            for (unsigned l = 1; l < 3; ++l)
                row.lfos[l].phase = wrapPhase(row.lfos[l].phase + phaseIncr[r][l]);
        }
    }

    for (unsigned l = 0; l < 3; ++l) {
        float *output = outputs[l];
        SmoothFilter &flt = fSmoothOutput[l];
        for (unsigned i = 0; i < count; ++i)
            output[i] = flt.process(output[i]);
    }
}

float LFO3PhaseDual::getLfoSine(float phase)
{
    constexpr unsigned n = LfoSine.size();
    float i = phase * n;
    unsigned i1 = (unsigned)i % n;
    unsigned i2 = (i1 + 1) % n;
    float m = i - i1;
    return (1 - m) * LfoSine[i1] + m * LfoSine[i2];
}

float LFO3PhaseDual::wrapPhase(float phase)
{
    return phase - (int)phase;
}

template <unsigned N> std::array<float, N> createLfoSine()
{
    std::array<float, N> s;
    for (unsigned i = 0; i < N; ++i)
        s[i] = std::sin(2.0 * M_PI * i / N);
    return s;
}
