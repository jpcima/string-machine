#pragma once
#include "ChorusShared.hpp"
#include "SolinaChorus.h"

class ChorusPlugin : public Plugin {
public:
    ChorusPlugin();
    ~ChorusPlugin();

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

    void activate() override;
    void deactivate() override;

    void run(const float **inputs, float **outputs, uint32_t frames) override;

private:
    float fWetGain = 0.0;
    float fDryGain = 0.0;

    SolinaChorus fChorus[DISTRHO_PLUGIN_NUM_INPUTS];
};
