#pragma once
#include "StringMachineShared.hpp"
#include "DistrhoUI.hpp"
#include "ui/components/KnobSkin.hpp"
#include "ui/Geometry.h"
#include "dsp/AHDSREnvelope.h"
#include <random>
#include <array>
#include <string>
#include <memory>

class SkinSlider;
class SkinToggleButton;
class SkinTriggerButton;
class SkinIndicator;
class PlotView;
class FontEngine;

///
class StringMachineUI : public UI {
public:
    StringMachineUI();
    ~StringMachineUI();

protected:
    void onDisplay() override;
    void parameterChanged(uint32_t index, float value) override;
    void programLoaded(uint32_t index) override;
    void uiIdle() override;

    bool onKeyboard(const KeyboardEvent &event) override;

private:
    void updateParameterValue(uint32_t index, float value);
    std::array<float, Parameter_Count> getParameterDefaults() const;

    SkinSlider *createKnobForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);
    SkinToggleButton *createToggleButtonForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);
    SkinIndicator *createValueDisplayForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);

    void computeAdsrPlot(float *data, unsigned size);

    struct KeyPress;
    bool checkForKeySequence(const uint32_t *sequence, unsigned sequenceSize);

    void checkForDeveloperCode();
    void enableDeveloperMode();

    double convertNormalizedToParameter(unsigned index, double value);
    double convertNormalizedFromParameter(unsigned index, double value);

    void randomizeParameters();
    bool isRandomizableParameter(unsigned index) const;

    static std::string formatDisplayValue(double value);

private:
    static std::unique_ptr<FontEngine> fFontEngine;

    AHDSREnvelope::Settings fEnvSettings;

    KnobSkin fSkinKnob;
    KnobSkin fSkinSlider;
    KnobSkin fSkinToggleButton;
    KnobSkin fSkinTriggerButton;
    KnobSkin fSkinLed;
    KnobSkin fSkinVu;
    KnobSkin fSkinValueDisplay;

    std::unique_ptr<SkinSlider> fSliderForParameter[Parameter_Count];
    std::unique_ptr<SkinToggleButton> fToggleButtonForParameter[Parameter_Count];
    std::unique_ptr<SkinIndicator> fValueDisplayForParameter[Parameter_Count];
    std::unique_ptr<SkinIndicator> fLfoIndicator[2];
    std::unique_ptr<SkinIndicator> fOscDetuneDisplay[2];
    std::unique_ptr<SkinIndicator> fVuDisplay[2];
    std::unique_ptr<PlotView> fAdsrView;

    Parameter fParameters[Parameter_Count];

    enum { KeyHistorySize = 16 };
    uint32_t fKeyHistory[KeyHistorySize] = {};
    unsigned fKeyHistoryIndex = 0;

    bool fDeveloperMode = false;
    std::unique_ptr<SkinTriggerButton> fRandomizeButton;
    std::minstd_rand fRandomGenerator;
};
