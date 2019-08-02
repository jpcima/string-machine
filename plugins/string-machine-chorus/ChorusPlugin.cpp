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
    const SolinaChorus &chorus = fChorus[0];

    switch (index) {
    case pIdChoEnabled:
        return chorus.getEnabled();
    case pIdChoDepth:
        return chorus.getLfo().getDepth();
    case pIdChoRate1:
        return chorus.getLfo().getRate1();
    case pIdChoDepth1:
        return chorus.getLfo().getDepth1();
    case pIdChoRate2:
        return chorus.getLfo().getRate2();
    case pIdChoDepth2:
        return chorus.getLfo().getDepth2();
    case pIdChoModel:
        return chorus.getAnalogMode();

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
    case pIdChoEnabled:
        for (SolinaChorus &chorus : fChorus)
            chorus.setEnabled(value > 0.5f);
        break;
    case pIdChoDepth:
        for (SolinaChorus &chorus : fChorus)
            chorus.getLfo().setDepth(value);
        break;
    case pIdChoRate1:
        for (SolinaChorus &chorus : fChorus)
            chorus.getLfo().setRate1(value);
        break;
    case pIdChoDepth1:
        for (SolinaChorus &chorus : fChorus)
            chorus.getLfo().setDepth1(value);
        break;
    case pIdChoRate2:
        for (SolinaChorus &chorus : fChorus)
            chorus.getLfo().setRate2(value);
        break;
    case pIdChoDepth2:
        for (SolinaChorus &chorus : fChorus)
            chorus.getLfo().setDepth2(value);
        break;
    case pIdChoModel:
        for (SolinaChorus &chorus : fChorus)
            chorus.setAnalogMode((int)value);
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

    for (SolinaChorus &chorus : fChorus)
        chorus.init(sampleRate);
}

void ChorusPlugin::deactivate()
{
}

void ChorusPlugin::run(const float **inputs, float **outputs, uint32_t totalFrames)
{
    WebCore::DenormalDisabler denormalsDisabled;

    constexpr unsigned bufferLimit = StringSynthDefs::BufferLimit;

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

        if (DISTRHO_PLUGIN_NUM_INPUTS == 1) {
            const float *input = inputs[0];
            for (uint32_t i = 0; i < frames; ++i)
                mixL[i] = dryGain * input[frameIndex + i];
            memcpy(mixR, mixL, frames * sizeof(float));
        }
        else if (DISTRHO_PLUGIN_NUM_INPUTS == 2) {
            const float *inputL = inputs[0];
            const float *inputR = inputs[1];
            for (uint32_t i = 0; i < frames; ++i) {
                mixL[i] = dryGain * inputL[frameIndex + i];
                mixR[i] = dryGain * inputR[frameIndex + i];
            }
        }

        for (unsigned channel = 0; channel < DISTRHO_PLUGIN_NUM_INPUTS; ++channel) {
            float tempL[bufferLimit];
            float tempR[bufferLimit];
            float tempDiscard[bufferLimit];

            float *outputsTemp[3] = { tempL, tempR, tempDiscard };
            fChorus[channel].process(inputs[channel] + frameIndex, outputsTemp, frames);

            for (uint32_t i = 0; i < frames; ++i) {
                mixL[i] += wetGain * tempL[i];
                mixR[i] += wetGain * tempR[i];
            }
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
