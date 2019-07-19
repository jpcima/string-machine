#include "StringMachinePlugin.hpp"
#include "StringMachinePresets.hpp"
#include "StringSynthDefs.h"
#include "DenormalDisabler.h"

StringMachinePlugin::StringMachinePlugin()
    : Plugin(Parameter_Count, NumPrograms, State_Count)
{
    for (unsigned p = 0; p < Parameter_Count; ++p) {
        Parameter param;
        InitParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

StringMachinePlugin::~StringMachinePlugin()
{
}

const char *StringMachinePlugin::getLabel() const
{
    return DISTRHO_PLUGIN_LABEL;
}

const char *StringMachinePlugin::getMaker() const
{
    return DISTRHO_PLUGIN_MAKER;
}

const char *StringMachinePlugin::getLicense() const
{
    return DISTRHO_PLUGIN_LICENSE;
}

const char *StringMachinePlugin::getDescription() const
{
    return DISTRHO_PLUGIN_DESCRIPTION;
}

const char *StringMachinePlugin::getHomePage() const
{
    return DISTRHO_PLUGIN_HOMEPAGE;
}

uint32_t StringMachinePlugin::getVersion() const
{
    return d_version(DISTRHO_PLUGIN_VERSION);
}

int64_t StringMachinePlugin::getUniqueId() const
{
    return d_cconst(DISTRHO_PLUGIN_UNIQUE_ID);
}

void StringMachinePlugin::initParameter(uint32_t index, Parameter &parameter)
{
    InitParameter(index, parameter);
}

float StringMachinePlugin::getParameterValue(uint32_t index) const
{
    const StringSynth &synth = fSynth;

    switch (index) {
    case pIdOscDetune:
        return synth.getDetune();
    case pIdOscHpCutoffUpper:
        return synth.getOscSettings().highpassUpperCutoff;
    case pIdOscHpCutoffLower:
        return synth.getOscSettings().highpassLowerCutoff;

    case pIdFltLpCutoffUpper:
        return synth.getFltSettings().lowpassUpperCutoff;
    case pIdFltHpCutoffUpper:
        return synth.getFltSettings().highpassUpperCutoff;
    case pIdFltLpCutoffLower:
        return synth.getFltSettings().lowpassLowerCutoff;
    case pIdFltHpCutoffLower:
        return synth.getFltSettings().highpassLowerCutoff;
    case pIdFltHsCutoffEq:
        return synth.getFltSettings().highshelfEqCutoff;
    case pIdFltHsBoostEq:
        return synth.getFltSettings().highshelfEqBoost;

    case pIdMixGainUpper:
        return synth.getMixGainUpper();
    case pIdMixGainLower:
        return synth.getMixGainLower();

    case pIdEnvAttack:
        return synth.getEnvSettings().attack;
    case pIdEnvDecay:
        return synth.getEnvSettings().decay;
    case pIdEnvSustain:
        return synth.getEnvSettings().sustain;
    case pIdEnvRelease:
        return synth.getEnvSettings().release;

    case pIdChoEnabled:
        return synth.getChorus().getEnabled();
    case pIdChoDepth:
        return synth.getChorus().getLfo().getDepth();
    case pIdChoRate1:
        return synth.getChorus().getLfo().getRate1();
    case pIdChoDepth1:
        return synth.getChorus().getLfo().getDepth1();
    case pIdChoRate2:
        return synth.getChorus().getLfo().getRate2();
    case pIdChoDepth2:
        return synth.getChorus().getLfo().getDepth2();

    case pIdMasterGain:
        return synth.getMasterGain();

    default:
        DISTRHO_SAFE_ASSERT(false);
        return 0.0;
    }
}

void StringMachinePlugin::setParameterValue(uint32_t index, float value)
{
    StringSynth &synth = fSynth;

    switch (index) {
    case pIdOscDetune:
        synth.setDetune(value);
        break;
    case pIdOscHpCutoffUpper:
        synth.getOscSettings().highpassUpperCutoff = value;
        break;
    case pIdOscHpCutoffLower:
        synth.getOscSettings().highpassLowerCutoff = value;
        break;

    case pIdFltLpCutoffUpper:
        synth.getFltSettings().lowpassUpperCutoff = value;
        break;
    case pIdFltHpCutoffUpper:
        synth.getFltSettings().highpassUpperCutoff = value;
        break;
    case pIdFltLpCutoffLower:
        synth.getFltSettings().lowpassLowerCutoff = value;
        break;
    case pIdFltHpCutoffLower:
        synth.getFltSettings().highpassLowerCutoff = value;
        break;
    case pIdFltHsCutoffEq:
        synth.getFltSettings().highshelfEqCutoff = value;
        break;
    case pIdFltHsBoostEq:
        synth.getFltSettings().highshelfEqBoost = value;
        break;

    case pIdMixGainUpper:
        synth.setMixGainUpper(value);
        break;
    case pIdMixGainLower:
        synth.setMixGainLower(value);
        break;

    case pIdEnvAttack:
        synth.getEnvSettings().attack = value;
        break;
    case pIdEnvDecay:
        synth.getEnvSettings().decay = value;
        break;
    case pIdEnvSustain:
        synth.getEnvSettings().sustain = value;
        break;
    case pIdEnvRelease:
        synth.getEnvSettings().release = value;
        break;

    case pIdChoEnabled:
        synth.getChorus().setEnabled(value > 0.5f);
        break;
    case pIdChoDepth:
        synth.getChorus().getLfo().setDepth(value);
        break;
    case pIdChoRate1:
        synth.getChorus().getLfo().setRate1(value);
        break;
    case pIdChoDepth1:
        synth.getChorus().getLfo().setDepth1(value);
        break;
    case pIdChoRate2:
        synth.getChorus().getLfo().setRate2(value);
        break;
    case pIdChoDepth2:
        synth.getChorus().getLfo().setDepth2(value);
        break;

    case pIdMasterGain:
        synth.setMasterGain(value);
        break;

    default:
        DISTRHO_SAFE_ASSERT(false);
        break;
    }
}

void StringMachinePlugin::initProgramName(uint32_t index, String &programName)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < NumPrograms, );

    programName = "Program " + String(index + 1);
}

void StringMachinePlugin::loadProgram(uint32_t index)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < NumPrograms, );

    for (unsigned p = 0; p < Parameter_Count; ++p)
        setParameterValue(p, Programs[index][p]);
}

void StringMachinePlugin::activate()
{
    double sampleRate = getSampleRate();

    fSynth.init(sampleRate);

    for (unsigned c = 0; c < 2; ++c)
        fOutputLevelFollower[c].release(0.5 * sampleRate);
}

void StringMachinePlugin::deactivate()
{
}

void StringMachinePlugin::run(const float **, float **outputs, uint32_t totalFrames,
                              const MidiEvent *midiEvents, uint32_t midiEventCount)
{
    WebCore::DenormalDisabler denormalsDisabled;

    StringSynth &synth = fSynth;
    constexpr unsigned bufferLimit = StringSynthDefs::BufferLimit;

    float *outL = outputs[0];
    float *outR = outputs[1];

    uint32_t frameIndex = 0;
    const MidiEvent *midiCurrent = midiEvents;

    while (totalFrames - frameIndex > 0) {
        uint32_t frames = totalFrames - frameIndex;
        frames = (frames < bufferLimit) ? frames : bufferLimit;

        while (midiCurrent != midiEvents + midiEventCount && (midiCurrent->frame < frameIndex + frames || frameIndex + frames == totalFrames)) {
            if (midiCurrent->size <= 3)
                synth.handleMessage(midiCurrent->data);
            ++midiCurrent;
        }

        float *outputsAtIndex[2] = { outL + frameIndex, outR + frameIndex };
        synth.generate(outputsAtIndex, frames);

        frameIndex += frames;
    }

    for (unsigned c = 0; c < 2; ++c) {
        AmpFollower &follower = fOutputLevelFollower[c];
        const float *output = outputs[c];
        for (uint32_t i = 0; i < totalFrames; ++i)
            follower.process(output[i]);
    }
}

///
namespace DISTRHO {

Plugin *createPlugin()
{
    return new StringMachinePlugin;
}

} // namespace DISTRHO
