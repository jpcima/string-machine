#pragma once
#include "StringMachineShared.hpp"
#include "DistrhoUI.hpp"
#include "ui/components/KnobSkin.hpp"
#include "ui/Geometry.h"
#include "dsp/ADSREnvelope.h"
#include <random>
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
    bool onSpecial(const SpecialEvent &event) override;

private:
    void updateParameterValue(uint32_t index, float value);

    SkinSlider *createKnobForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);
    SkinToggleButton *createToggleButtonForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);
    SkinIndicator *createValueDisplayForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);

    void computeAdsrPlot(float *data, unsigned size);

    void checkForDeveloperCode();
    void enableDeveloperMode();

    double convertNormalizedToParameter(unsigned index, double value);
    double convertNormalizedFromParameter(unsigned index, double value);

    void randomizeParameters();
    static bool isRandomizableParameter(unsigned index);

    static std::string formatDisplayValue(double value);

private:
    static std::unique_ptr<FontEngine> fFontEngine;

    ADSREnvelope::Settings fEnvSettings;

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

    struct KeyPress {
        uint32_t key;
        bool special;

        bool operator==(const KeyPress &other) const
            { return key == other.key && special == other.special; }
        bool operator!=(const KeyPress &other) const
            { return !operator==(other); }
    };

    enum { KeyHistorySize = 16 };
    KeyPress fKeyHistory[KeyHistorySize] = {};
    unsigned fKeyHistoryIndex = 0;

    bool fDeveloperMode = false;
    std::unique_ptr<SkinTriggerButton> fRandomizeButton;
    std::minstd_rand fRandomGenerator;
};
