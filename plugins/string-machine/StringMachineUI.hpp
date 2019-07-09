#pragma once
#include "StringMachineShared.hpp"
#include "DistrhoUI.hpp"
#include "ui/components/KnobSkin.hpp"
#include "ui/Geometry.h"
#include "dsp/ADSREnvelope.h"
#include <string>
#include <memory>

class SkinSlider;
class SkinToggleButton;
class SkinIndicator;
class PlotView;
class FontEngine;

///
class StringMachineUI : public UI {
public:
    StringMachineUI();
    ~StringMachineUI();

    void onDisplay() override;
    void parameterChanged(uint32_t index, float value) override;
    void uiIdle() override;

private:
    void updateParameterValue(uint32_t index, float value);

    SkinSlider *createKnobForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);
    SkinToggleButton *createToggleButtonForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);
    SkinIndicator *createValueDisplayForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin);

    void computeAdsrPlot(float *data, unsigned size);

    double convertNormalizedToParameter(unsigned index, double value);
    double convertNormalizedFromParameter(unsigned index, double value);

    static std::string formatDisplayValue(double value);

private:
    static std::unique_ptr<FontEngine> fFontEngine;

    ADSREnvelope::Settings fEnvSettings;

    KnobSkin fSkinKnob;
    KnobSkin fSkinSlider;
    KnobSkin fSkinToggleButton;
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
};
