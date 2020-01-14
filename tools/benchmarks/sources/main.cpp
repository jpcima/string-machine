#include "SolinaChorus.h"
#include "SolinaChorusStereo.h"
#include "StringSynthDefs.h"
#include "StringMachineShared.hpp"
#include "DenormalDisabler.h"
#include <algorithm>
#include <chrono>
#include <cmath>
namespace chr = std::chrono;

static constexpr double SampleRate = 44100;
using StringSynthDefs::BufferLimit;

template <class F>
double measureElapsed(F &&f)
{
    f(); // dummy run to reduce cache effects
    chr::steady_clock::time_point t1 = chr::steady_clock::now();
    f();
    chr::steady_clock::time_point t2 = chr::steady_clock::now();
    return chr::duration_cast<chr::duration<double>>(t2 - t1).count();
}

template <class Chorus>
void runChorus(Chorus &chorus, double duration);

template <>
void runChorus(SolinaChorus &chorus, double duration)
{
    uint32_t index = 0;
    uint32_t totalFrames = std::ceil(duration * SampleRate);
    const float input[BufferLimit] = {};
    float outputL[BufferLimit];
    float outputR[BufferLimit];
    while (index < totalFrames) {
        uint32_t frames = std::min<uint32_t>(totalFrames - index, BufferLimit);
        float *outputs[] = {outputL, outputR};
        chorus.process(input, outputs, frames);
        index += frames;
    }
}

template <>
void runChorus(SolinaChorusStereo &chorus, double duration)
{
    uint32_t index = 0;
    uint32_t totalFrames = std::ceil(duration * SampleRate);
    const float inputL[BufferLimit] = {};
    const float inputR[BufferLimit] = {};
    float outputL[BufferLimit];
    float outputR[BufferLimit];
    while (index < totalFrames) {
        uint32_t frames = std::min<uint32_t>(totalFrames - index, BufferLimit);
        const float *inputs[] = {inputL, inputR};
        float *outputs[] = {outputL, outputR};
        chorus.process(inputs, outputs, frames);
        index += frames;
    }
}

template <class Chorus>
void setChorusParameter(Chorus &chorus, uint32_t id, float value)
{
    switch (id) {
    case pIdChoEnabled:
        chorus.setEnabled(value > 0.5f);
        break;
    case pIdChoDepth:
        chorus.getLfo().set_globaldepth(value);
        break;
    case pIdChoRate1:
        chorus.getLfo().set_rate1(value);
        break;
    case pIdChoDepth1:
        chorus.getLfo().set_depth1(value);
        break;
    case pIdChoRate2:
        chorus.getLfo().set_rate2(value);
        break;
    case pIdChoDepth2:
        chorus.getLfo().set_depth2(value);
        break;
    case pIdChoModel:
        chorus.setAnalogMode((int)value);
        break;
    }
}

template <class Chorus>
void setChorusDefaults(Chorus &chorus)
{
    for (uint32_t id = 0; id < Parameter_Count; ++id) {
        Parameter param;
        InitParameter(id, param);
        setChorusParameter(chorus, id, param.ranges.def);
    }
}

int main(int argc, char *argv[])
{
    WebCore::DenormalDisabler denormalsDisabled;

    SolinaChorus chorus1;
    SolinaChorusStereo chorus2;

    chorus1.init(SampleRate);
    chorus2.init(SampleRate);

    setChorusDefaults(chorus1);
    setChorusDefaults(chorus2);

    double t1, t2;
    double duration = 60.0;

    t1 = measureElapsed([&chorus1, duration]() { runChorus(chorus1, duration); });
    fprintf(stderr, "Analog Mono: %f\n", t1);
    t2 = measureElapsed([&chorus2, duration]() { runChorus(chorus2, duration); });
    fprintf(stderr, "Analog Stereo: %f\n", t2);
    fprintf(stderr, "Relative %+.2f%%\n", 100.0 * (t2 - t1) / t1);

    setChorusParameter(chorus1, pIdChoModel, 0.0);
    setChorusParameter(chorus2, pIdChoModel, 0.0);

    t1 = measureElapsed([&chorus1, duration]() { runChorus(chorus1, duration); });
    fprintf(stderr, "Digital Mono: %f\n", t1);
    t2 = measureElapsed([&chorus2, duration]() { runChorus(chorus2, duration); });
    fprintf(stderr, "Digital Stereo: %f\n", t2);
    fprintf(stderr, "Relative %+.2f%%\n", 100.0 * (t2 - t1) / t1);

    return 0;
}
