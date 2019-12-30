#include "StringMachinePlugin.hpp"
#include "StringMachinePresets.hpp"
#include "StringSynthDefs.h"
#include "DenormalDisabler.h"

StringMachinePlugin::StringMachinePlugin()
    : Plugin(Parameter_Count, NumPrograms, State_Count)
{
    double sampleRate = getSampleRate();
    fSynth.init(sampleRate);

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
    case pIdOscPwmDepth:
        return synth.getOscSettings().pwmDepth;
    case pIdOscPwmFrequency:
        return synth.getOscSettings().pwmFrequency;

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
    case pIdEnvHold:
        return synth.getEnvSettings().hold;
    case pIdEnvDecay:
        return synth.getEnvSettings().decay;
    case pIdEnvSustain:
        return synth.getEnvSettings().sustain;
    case pIdEnvRelease:
        return synth.getEnvSettings().release;

    case pIdChoEnabled:
        return synth.getChorus().getEnabled();
    case pIdChoDepth:
        return synth.getChorus().getLfo().get_globaldepth();
    case pIdChoRate1:
        return synth.getChorus().getLfo().get_rate1();
    case pIdChoDepth1:
        return synth.getChorus().getLfo().get_depth1();
    case pIdChoRate2:
        return synth.getChorus().getLfo().get_rate2();
    case pIdChoDepth2:
        return synth.getChorus().getLfo().get_depth2();
    case pIdChoModel:
        return synth.getChorus().getAnalogMode();

    case pIdMasterGain:
        return synth.getMasterGain();

    case pIdOutDetuneUpper:
        return fSynth.getLastDetuneUpper();
    case pIdOutDetuneLower:
        return fSynth.getLastDetuneLower();
    case pIdOutChorusPhase1:
        return (2 * M_PI) * fSynth.getChorus().getPhase1();
    case pIdOutChorusPhase2:
        return (2 * M_PI) * fSynth.getChorus().getPhase2();
    case pIdOutMasterLevel1:
    case pIdOutMasterLevel2:
    {
        double level = fOutputLevelFollower[index - pIdOutMasterLevel1].last_output();
        return 20 * std::log10(std::max(level, 1e-5));
    }

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
    case pIdOscPwmDepth:
        synth.getOscSettings().pwmDepth = value;
        break;
    case pIdOscPwmFrequency:
        synth.getOscSettings().pwmFrequency = value;
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
    case pIdEnvHold:
        synth.getEnvSettings().hold = value;
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
        synth.getChorus().getLfo().set_globaldepth(value);
        break;
    case pIdChoRate1:
        synth.getChorus().getLfo().set_rate1(value);
        break;
    case pIdChoDepth1:
        synth.getChorus().getLfo().set_depth1(value);
        break;
    case pIdChoRate2:
        synth.getChorus().getLfo().set_rate2(value);
        break;
    case pIdChoDepth2:
        synth.getChorus().getLfo().set_depth2(value);
        break;
    case pIdChoModel:
        synth.getChorus().setAnalogMode((int)value);
        break;

    case pIdMasterGain:
        synth.setMasterGain(value);
        break;

    case pIdOutDetuneUpper:
    case pIdOutDetuneLower:
    case pIdOutChorusPhase1:
    case pIdOutChorusPhase2:
    case pIdOutMasterLevel1:
    case pIdOutMasterLevel2:
        break;

    default:
        DISTRHO_SAFE_ASSERT(false);
        break;
    }
}

void StringMachinePlugin::initProgramName(uint32_t index, String &programName)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < NumPrograms, );

    programName = Programs[index].name;
}

void StringMachinePlugin::loadProgram(uint32_t index)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < NumPrograms, );

    for (unsigned p = 0; p < Parameter_Count; ++p)
        setParameterValue(p, Programs[index].values[p]);
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
