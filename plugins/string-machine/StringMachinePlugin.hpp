#pragma once
#include "StringMachineShared.hpp"
#include "StringSynth.h"
#include "dsp/AmpFollower.h"

class StringMachinePlugin : public Plugin {
public:
    StringMachinePlugin();
    ~StringMachinePlugin();

    const char *getLabel() const override;
    const char *getMaker() const override;
    const char *getLicense() const override;
    const char *getDescription() const override;
    const char *getHomePage() const override;
    uint32_t getVersion() const override;
    int64_t getUniqueId() const override;

    void initParameter(uint32_t index, Parameter &parameter) override;
    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;

    void run(const float **inputs, float **outputs, uint32_t frames,
             const MidiEvent *midiEvents, uint32_t midiEventCount) override;

    //
    float getLastDetuneUpper() const { return fSynth.getLastDetuneUpper(); }
    float getLastDetuneLower() const { return fSynth.getLastDetuneLower(); }

    float getChorusPhase1() const { return fSynth.getChorus().getPhase1(); }
    float getChorusPhase2() const { return fSynth.getChorus().getPhase2(); }

    double getLeftOutputLevel() const { return fOutputLevelFollower[0].last_output(); }
    double getRightOutputLevel() const { return fOutputLevelFollower[1].last_output(); }

private:
    StringSynth fSynth;
    AmpFollower fOutputLevelFollower[2];
};
