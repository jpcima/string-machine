#include "ChorusPlugin.hpp"
#include "StringSynthDefs.h"
#include "DenormalDisabler.h"
#include <cstring>

enum { NumPrograms = 0 }; // no programs

ChorusPlugin::ChorusPlugin()
    : Plugin(Parameter_Count, NumPrograms, State_Count)
{
    for (unsigned p = 0; p < Parameter_Count; ++p) {
        Parameter param;
        InitParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

ChorusPlugin::~ChorusPlugin()
{
}

const char *ChorusPlugin::getLabel() const
{
    return DISTRHO_PLUGIN_LABEL;
}

const char *ChorusPlugin::getMaker() const
{
    return DISTRHO_PLUGIN_MAKER;
}

const char *ChorusPlugin::getLicense() const
{
    return DISTRHO_PLUGIN_LICENSE;
}

const char *ChorusPlugin::getDescription() const
{
    return DISTRHO_PLUGIN_DESCRIPTION;
}

const char *ChorusPlugin::getHomePage() const
{
    return DISTRHO_PLUGIN_HOMEPAGE;
}

uint32_t ChorusPlugin::getVersion() const
{
    return d_version(DISTRHO_PLUGIN_VERSION);
}

int64_t ChorusPlugin::getUniqueId() const
{
    return d_cconst(DISTRHO_PLUGIN_UNIQUE_ID);
}

void ChorusPlugin::initParameter(uint32_t index, Parameter &parameter)
{
    InitParameter(index, parameter);
}

float ChorusPlugin::getParameterValue(uint32_t index) const
{
    switch (index) {
    case pIdBypass:
        return fBypass;

    case pIdChoDepth:
        return fChorus.getLfo().get_globaldepth();
    case pIdChoRate1:
        return fChorus.getLfo().get_rate1();
    case pIdChoDepth1:
        return fChorus.getLfo().get_depth1();
    case pIdChoRate2:
        return fChorus.getLfo().get_rate2();
    case pIdChoDepth2:
        return fChorus.getLfo().get_depth2();
    case pIdChoModel:
        return fChorus.getAnalogMode();

    case pIdWetGain:
        return fWetGain;
    case pIdDryGain:
        return fDryGain;

    default:
        DISTRHO_SAFE_ASSERT(false);
        return 0.0;
    }
}

void ChorusPlugin::setParameterValue(uint32_t index, float value)
{
    switch (index) {
    case pIdBypass:
        fBypass = value > 0.5f;
        break;

    case pIdChoDepth:
        fChorus.getLfo().set_globaldepth(value);
        break;
    case pIdChoRate1:
        fChorus.getLfo().set_rate1(value);
        break;
    case pIdChoDepth1:
        fChorus.getLfo().set_depth1(value);
        break;
    case pIdChoRate2:
        fChorus.getLfo().set_rate2(value);
        break;
    case pIdChoDepth2:
        fChorus.getLfo().set_depth2(value);
        break;
    case pIdChoModel:
        fChorus.setAnalogMode((int)value);
        break;

    case pIdWetGain:
        fWetGain = value;
        break;
    case pIdDryGain:
        fDryGain = value;
        break;

    default:
        DISTRHO_SAFE_ASSERT(false);
        break;
    }
}

void ChorusPlugin::activate()
{
    double sampleRate = getSampleRate();

    fChorus.init(sampleRate);
    fChorus.setEnabled(true);

    fWasBypassed = false;
}

void ChorusPlugin::deactivate()
{
}

void ChorusPlugin::run(const float **inputs, float **outputs, uint32_t totalFrames)
{
    bool bypass = fBypass;
    bool wasBypassed = fWasBypassed;
    fWasBypassed = bypass;

    if (bypass) {
        auto checked_memcpy = [](void *dst, const void *src, size_t count)
                                  { if (dst != src) memcpy(dst, src, count); };
#if DISTRHO_PLUGIN_NUM_INPUTS == 1
        checked_memcpy(outputs[0], inputs[0], totalFrames * sizeof(float));
        checked_memcpy(outputs[1], inputs[0], totalFrames * sizeof(float));
#elif DISTRHO_PLUGIN_NUM_INPUTS == 2
        checked_memcpy(outputs[0], inputs[0], totalFrames * sizeof(float));
        checked_memcpy(outputs[1], inputs[1], totalFrames * sizeof(float));
#endif
        return;
    }

    if (wasBypassed)
        fChorus.clear();

    WebCore::DenormalDisabler denormalsDisabled;

    constexpr unsigned bufferLimit = StringSynthDefs::BufferLimit;

#if DISTRHO_PLUGIN_NUM_INPUTS == 1
    const float *in = inputs[0];
#elif DISTRHO_PLUGIN_NUM_INPUTS == 2
    const float *inL = inputs[0];
    const float *inR = inputs[1];
#endif

    float *outL = outputs[0];
    float *outR = outputs[1];

    float wetGain = std::pow(10.0f, 0.05f * fWetGain);
    float dryGain = std::pow(10.0f, 0.05f * fDryGain);

    uint32_t frameIndex = 0;

    while (totalFrames - frameIndex > 0) {
        uint32_t frames = totalFrames - frameIndex;
        frames = (frames < bufferLimit) ? frames : bufferLimit;

        float mixL[bufferLimit];
        float mixR[bufferLimit];

#if DISTRHO_PLUGIN_NUM_INPUTS == 1
        for (uint32_t i = 0; i < frames; ++i)
            mixL[i] = dryGain * in[frameIndex + i];
        memcpy(mixR, mixL, frames * sizeof(float));
#elif DISTRHO_PLUGIN_NUM_INPUTS == 2
        for (uint32_t i = 0; i < frames; ++i) {
            mixL[i] = dryGain * inL[frameIndex + i];
            mixR[i] = dryGain * inR[frameIndex + i];
        }
#endif

        float tempL[bufferLimit];
        float tempR[bufferLimit];
        float *outputsTemp[2] = { tempL, tempR };
#if DISTRHO_PLUGIN_NUM_INPUTS == 1
        fChorus.process(in + frameIndex, outputsTemp, frames);
#elif DISTRHO_PLUGIN_NUM_INPUTS == 2
        const float *inputsTemp[2] = { inL + frameIndex, inR + frameIndex };
        fChorus.process(inputsTemp, outputsTemp, frames);
#endif

        for (uint32_t i = 0; i < frames; ++i) {
            mixL[i] += wetGain * tempL[i];
            mixR[i] += wetGain * tempR[i];
        }

        memcpy(outL + frameIndex, mixL, frames * sizeof(float));
        memcpy(outR + frameIndex, mixR, frames * sizeof(float));

        frameIndex += frames;
    }
}

///
namespace DISTRHO {

Plugin *createPlugin()
{
    return new ChorusPlugin;
}

} // namespace DISTRHO
