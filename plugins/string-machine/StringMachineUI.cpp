#include "StringMachineUI.hpp"
#include "StringMachineUILayouts.hpp"
#include "StringMachinePresets.hpp"
#include "Artwork.hpp"
#include "Window.hpp"
#include "ui/components/SkinSlider.hpp"
#include "ui/components/SkinToggleButton.hpp"
#include "ui/components/SkinTriggerButton.hpp"
#include "ui/components/SkinIndicator.hpp"
#include "ui/components/PlotView.hpp"
#include "ui/FontEngine.h"
#include "ui/Cairo++.h"
#include <array>
#include <cstdio>

static constexpr ColorRGBA8 bgColor{0xbd, 0xbc, 0xb5, 0xff};

///
StringMachineUI::StringMachineUI()
    : UI(MainLayout::window_TopLevel.w, MainLayout::window_TopLevel.h),
      fSkinKnob(Artwork::knobData, Artwork::knobDataSize, 31),
      fSkinSlider(Artwork::sliderData, Artwork::sliderDataSize, 31),
      fSkinToggleButton(Artwork::toggle_buttonData, Artwork::toggle_buttonDataSize, 2),
      fSkinTriggerButton(Artwork::trigger_buttonData, Artwork::trigger_buttonDataSize, 2),
      fSkinLed(Artwork::ledData, Artwork::ledDataSize, 2),
      fSkinVu(Artwork::vuData, Artwork::vuDataSize, 31),
      fSkinValueDisplay(Artwork::value_displayData, Artwork::value_displayDataSize, 1),
      fRandomGenerator(std::random_device{}())
{
    for (unsigned p = 0; p < Parameter_Count; ++p)
        InitParameter(p, fParameters[p]);

    fEnvSettings.attack = 0.0;
    fEnvSettings.hold = 0.0;
    fEnvSettings.decay = 0.0;
    fEnvSettings.sustain = 0.0;
    fEnvSettings.release = 0.0;

    FontEngine *fe = fFontEngine.get();
    if (!fe) {
        fe = new FontEngine;
        fFontEngine.reset(fe);
        fe->addFont("default", (const uint8_t *)Artwork::ProggyTinyData, Artwork::ProggyTinyDataSize);
        fe->addFont("title", (const uint8_t *)Artwork::ProggySquareData, Artwork::ProggySquareDataSize);
    }

    #define KNOB(x) { SkinSlider *s = createKnobForParameter(pId##x, MainLayout::knob_##x, fSkinKnob); \
                      s->setOrientation(SkinSlider::Radial); }
    #define HSLIDER(x) { SkinSlider *s = createKnobForParameter(pId##x, MainLayout::slider_##x, fSkinSlider); \
                         s->setOrientation(SkinSlider::Horizontal); }
    #define TOGGLE_BUTTON(x) createToggleButtonForParameter(pId##x, MainLayout::btn_##x, fSkinToggleButton)
    #define VALUE_DISPLAY(x) createValueDisplayForParameter(pId##x, MainLayout::val_##x, fSkinValueDisplay)
    KNOB(OscDetune);
    KNOB(OscHpCutoffUpper);
    KNOB(OscHpCutoffLower);
    KNOB(FltLpCutoffUpper);
    KNOB(FltHpCutoffUpper);
    KNOB(FltLpCutoffLower);
    KNOB(FltHpCutoffLower);
    KNOB(FltHsCutoffEq);
    KNOB(FltHsBoostEq);
    KNOB(MixGainUpper);
    KNOB(MixGainLower);
    KNOB(EnvAttack);
    KNOB(EnvHold);
    KNOB(EnvDecay);
    KNOB(EnvSustain);
    KNOB(EnvRelease);
    TOGGLE_BUTTON(ChoEnabled);
    HSLIDER(ChoDepth);
    KNOB(ChoRate1);
    KNOB(ChoDepth1);
    KNOB(ChoRate2);
    KNOB(ChoDepth2);
    TOGGLE_BUTTON(ChoModel);
    KNOB(MasterGain);
    VALUE_DISPLAY(OscDetune);
    VALUE_DISPLAY(OscHpCutoffUpper);
    VALUE_DISPLAY(OscHpCutoffLower);
    VALUE_DISPLAY(FltLpCutoffUpper);
    VALUE_DISPLAY(FltLpCutoffLower);
    VALUE_DISPLAY(FltHpCutoffUpper);
    VALUE_DISPLAY(FltHpCutoffLower);
    VALUE_DISPLAY(FltHsCutoffEq);
    VALUE_DISPLAY(FltHsBoostEq);
    VALUE_DISPLAY(MixGainUpper);
    VALUE_DISPLAY(MixGainLower);
    VALUE_DISPLAY(ChoDepth1);
    VALUE_DISPLAY(ChoDepth2);
    VALUE_DISPLAY(ChoRate1);
    VALUE_DISPLAY(ChoRate2);
    VALUE_DISPLAY(MasterGain);
    VALUE_DISPLAY(EnvAttack);
    VALUE_DISPLAY(EnvHold);
    VALUE_DISPLAY(EnvDecay);
    VALUE_DISPLAY(EnvSustain);
    VALUE_DISPLAY(EnvRelease);
    #undef KNOB
    #undef HSLIDER
    #undef TOGGLE_BUTTON
    #undef VALUE_DISPLAY

    for (unsigned i = 0; i < 2; ++i) {
        SkinIndicator *led = new SkinIndicator(fSkinLed, *fe, this);
        fLfoIndicator[i].reset(led);
        switch (i) {
        case 0: led->setAbsolutePos(MainLayout::led_Lfo1.x, MainLayout::led_Lfo1.y); break;
        case 1: led->setAbsolutePos(MainLayout::led_Lfo2.x, MainLayout::led_Lfo2.y); break;
        }
    }

    for (unsigned i = 0; i < 2; ++i) {
        SkinIndicator *vd = new SkinIndicator(fSkinValueDisplay, *fe, this);
        fOscDetuneDisplay[i].reset(vd);
        switch (i) {
        case 0: vd->setAbsolutePos(MainLayout::val_OscDetune1.x, MainLayout::val_OscDetune1.y); break;
        case 1: vd->setAbsolutePos(MainLayout::val_OscDetune2.x, MainLayout::val_OscDetune2.y); break;
        }

        Font font;
        font.size = 10.0;
        font.color = ColorRGBA8{0xff, 0xff, 0xff, 0xff};
        vd->setTextFont(font);

        vd->setTextOffset({0.0, 1.0});

        vd->setText(formatDisplayValue(0.0));
    }

    for (unsigned i = 0; i < 2; ++i) {
        SkinIndicator *vd = new SkinIndicator(fSkinVu, *fe, this);
        fVuDisplay[i].reset(vd);
        switch (i) {
        case 0: vd->setAbsolutePos(MainLayout::vu_LeftVolume.x, MainLayout::vu_LeftVolume.y); break;
        case 1: vd->setAbsolutePos(MainLayout::vu_RightVolume.x, MainLayout::vu_RightVolume.y); break;
        }
    }

    PlotView *pv = new PlotView(this);
    fAdsrView.reset(pv);
    pv->setAbsolutePos(MainLayout::plot_Env.x, MainLayout::plot_Env.y);
    pv->setSize(MainLayout::plot_Env.w, MainLayout::plot_Env.h);
    pv->DataCallback = [this](float *d, unsigned n) { computeAdsrPlot(d, n); };
}

StringMachineUI::~StringMachineUI()
{
}

void StringMachineUI::onDisplay()
{
    FontEngine &fe = *fFontEngine;

    cairo_t *cr = getParentWindow().getGraphicsContext().cairo;
    cairo_set_source_rgba8(cr, bgColor);
    cairo_paint(cr);

    cairo_set_line_width(cr, 1.0);

    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);

    const Label *group_labels[] = {
        &MainLayout::group_StringOsc_label,
        &MainLayout::group_StringFilters_label,
        &MainLayout::group_Mixer_label,
        &MainLayout::group_SolinaChorus_label,
        &MainLayout::group_Level_label,
        &MainLayout::group_Envelope_label,
    };

    const Label *subgroup_labels[] = {
        &MainLayout::subgroup_AutoDetune_label,
        &MainLayout::subgroup_StringOsc_label,
    };

    const Label *control_labels[] = {
        &MainLayout::knob_OscDetune_label,
        &MainLayout::knob_OscHpCutoffUpper_label,
        &MainLayout::knob_OscHpCutoffLower_label,
        &MainLayout::knob_FltLpCutoffUpper_label,
        &MainLayout::knob_FltLpCutoffLower_label,
        &MainLayout::knob_FltHpCutoffUpper_label,
        &MainLayout::knob_FltHpCutoffLower_label,
        &MainLayout::knob_FltHsCutoffEq_label,
        &MainLayout::knob_FltHsBoostEq_label,
        &MainLayout::knob_MixGainUpper_label,
        &MainLayout::knob_MixGainLower_label,
        &MainLayout::knob_ChoDepth1_label,
        &MainLayout::knob_ChoDepth2_label,
        &MainLayout::knob_ChoRate1_label,
        &MainLayout::knob_ChoRate2_label,
        &MainLayout::btn_ChoModel_label,
        &MainLayout::slider_ChoDepth_label,
        &MainLayout::led_Lfo1_label,
        &MainLayout::led_Lfo2_label,
        &MainLayout::btn_ChoEnabled_label,
        &MainLayout::knob_MasterGain_label,
        &MainLayout::vu_LeftVolume_label,
        &MainLayout::vu_RightVolume_label,
        &MainLayout::knob_EnvAttack_label,
        &MainLayout::knob_EnvHold_label,
        &MainLayout::knob_EnvDecay_label,
        &MainLayout::knob_EnvSustain_label,
        &MainLayout::knob_EnvRelease_label,
        &MainLayout::val_OscDetune1_label,
        &MainLayout::val_OscDetune2_label,
    };

    for (const Label *label : group_labels) {
        Font font;
        font.name = "title";
        font.size = 11.0;
        font.color = ColorRGBA8{0xff, 0xff, 0xff, 0xff};

        RectF frame = label->bounds.to<double>().off_by({0.5, 0.5}).reduced({1, 0});
        RectF titleFrame = RectF(frame).take_from_top(14);

        cairo_rounded_rectangle_with_corners(cr, titleFrame, 5.0, RectangleNW|RectangleNE);
        cairo_set_source_rgba8(cr, ColorRGBA8{0x58, 0x58, 0x56, 0xff});
        cairo_fill(cr);
        cairo_move_to(cr, titleFrame.x, titleFrame.y + titleFrame.h);
        cairo_line_to(cr, titleFrame.x + titleFrame.w, titleFrame.y + titleFrame.h);
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_stroke(cr);

        Rect textBounds = label->bounds.off_by({0, 3});
        fe.drawInBox(cr, label->text, font, textBounds, label->align);

        cairo_rounded_rectangle(cr, frame, 5.0);
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_stroke(cr);
    }

    for (const Label *label : subgroup_labels) {
        Font font;
        font.name = "title";
        font.size = 11.0;

        Rect textBounds = label->bounds.off_by({0, 3});
        fe.drawInBox(cr, label->text, font, textBounds, label->align);

        RectF frame = label->bounds.to<double>().off_by({0.5, 0.5}).reduced({1, 0});
        cairo_rounded_rectangle(cr, frame, 5.0);
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
        cairo_stroke(cr);
    }

    for (const Label *label : control_labels) {
        Font font;
        font.size = 10.0;

        Rect bounds = label->bounds;

        if (label == &MainLayout::slider_ChoDepth_label) {
            bounds.x -= 4;
            bounds.y += 1;
        }
        else if (label == &MainLayout::vu_LeftVolume_label || label == &MainLayout::vu_RightVolume_label) {
            bounds.y += 2;
        }
        else if (label == &MainLayout::val_OscDetune1_label || label == &MainLayout::val_OscDetune2_label) {
            bounds.x -= 2;
        }

        fe.drawInBox(cr, label->text, font, bounds, label->align);
    }

    if (fDeveloperMode) {
        RectF rect(5.5, 7.5, 100.0, 15.0);

        cairo_rounded_rectangle(cr, rect, 5.0);
        cairo_set_source_rgba8(cr, ColorRGBA8{0xff, 0x7e, 0x00, 0xff});
        cairo_fill_preserve(cr);
        cairo_set_source_rgba8(cr, ColorRGBA8{0x00, 0x00, 0x00, 0xff});
        cairo_stroke(cr);

        Font font;
        font.size = 10.0;
        font.color = ColorRGBA8{0xff, 0xff, 0xff, 0xff};
        fe.drawInBox(cr, "Developer mode", font, rect.off_by({0, 1}), FontEngine::AlignCenter);

        SkinTriggerButton &randButton = *fRandomizeButton;
        font.size = 10.0;
        font.color = ColorRGBA8{0x00, 0x00, 0x00, 0xff};
        fe.drawInBox(cr, "Random", font, Rect(randButton.getAbsoluteX(), randButton.getAbsoluteY(), randButton.getWidth(), randButton.getHeight()).off_by({-8, 2}), FontEngine::AlignLeft);
    }
}

void StringMachineUI::parameterChanged(uint32_t index, float value)
{
    SkinSlider *sl = fSliderForParameter[index].get();
    if (sl) {
        sl->setValueNotified(false);
        sl->setValue(convertNormalizedFromParameter(index, value));
        sl->setValueNotified(true);
    }

    SkinToggleButton *cb = fToggleButtonForParameter[index].get();
    if (cb) {
        cb->setValueNotified(false);
        cb->setValue(value);
        cb->setValueNotified(true);
    }

    updateParameterValue(index, value);
}

void StringMachineUI::programLoaded(uint32_t index)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < NumPrograms, );

    for (unsigned p = 0; p < Parameter_Count; ++p)
        parameterChanged(p, Programs[index][p]);
}

void StringMachineUI::uiIdle()
{
}

bool StringMachineUI::onKeyboard(const KeyboardEvent &event)
{
    if (event.press && event.mod == 0) {
        fKeyHistory[fKeyHistoryIndex++] = KeyPress{event.key, false};
        fKeyHistoryIndex %= KeyHistorySize;
        checkForDeveloperCode();
    }

    return UI::onKeyboard(event);
}

bool StringMachineUI::onSpecial(const SpecialEvent &event)
{
    if (event.press && event.mod == 0) {
        fKeyHistory[fKeyHistoryIndex++] = KeyPress{event.key, true};
        fKeyHistoryIndex %= KeyHistorySize;
        checkForDeveloperCode();
    }

    return UI::onSpecial(event);
}

void StringMachineUI::updateParameterValue(uint32_t index, float value)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < Parameter_Count,);

    SkinIndicator *vd = fValueDisplayForParameter[index].get();
    if (vd)
        vd->setText(formatDisplayValue(value));

    switch (index) {
    case pIdEnvAttack:
        fEnvSettings.attack = value;
        fAdsrView->invalidateData();
        break;
    case pIdEnvHold:
        fEnvSettings.hold = value;
        fAdsrView->invalidateData();
        break;
    case pIdEnvDecay:
        fEnvSettings.decay = value;
        fAdsrView->invalidateData();
        break;
    case pIdEnvSustain:
        fEnvSettings.sustain = value;
        fAdsrView->invalidateData();
        break;
    case pIdEnvRelease:
        fEnvSettings.release = value;
        fAdsrView->invalidateData();
        break;

    case pIdWatchDetuneUpper:
        fOscDetuneDisplay[0]->setText(formatDisplayValue(value));
        break;
    case pIdWatchDetuneLower:
        fOscDetuneDisplay[1]->setText(formatDisplayValue(value));
        break;
    case pIdWatchChorusPhase1:
    case pIdWatchChorusPhase2:
    {
        SkinIndicator &x = *fLfoIndicator[index - pIdWatchChorusPhase1];
        x.setValue(value > M_PI);
        break;
    }
    case pIdWatchMasterLevel1:
    case pIdWatchMasterLevel2:
    {
        SkinIndicator &x = *fVuDisplay[index - pIdWatchMasterLevel1];
        constexpr double levelMin = -20.0, levelMax = 0.0;
        x.setValue((value - levelMin) * (1.0 / (levelMax - levelMin)));
        break;
    }
    }
}

SkinSlider *StringMachineUI::createKnobForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < Parameter_Count, nullptr);

    SkinSlider *sl = new SkinSlider(skin, this);
    fSliderForParameter[index].reset(sl);
    sl->setAbsolutePos(bounds.x, bounds.y);
    sl->setOrientation(SkinSlider::Vertical);

    const Parameter &param = fParameters[index];
    sl->setValueBounds(0.0, 1.0);
    sl->setValue(convertNormalizedFromParameter(index, param.ranges.def));

    sl->ValueChangedCallback =
        [this, index](double value) {
            value = convertNormalizedToParameter(index, value);
            updateParameterValue(index, value);
            setParameterValue(index, value);
        };

    return sl;
}

SkinToggleButton *StringMachineUI::createToggleButtonForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < Parameter_Count, nullptr);

    SkinToggleButton *cb = new SkinToggleButton(skin, this);
    fToggleButtonForParameter[index].reset(cb);
    cb->setAbsolutePos(bounds.x, bounds.y);

    const Parameter &param = fParameters[index];
    cb->setValue(param.ranges.def > 0.5f);

    cb->ValueChangedCallback =
        [this, index](bool value) {
            updateParameterValue(index, value);
            setParameterValue(index, value);
        };

    return cb;
}

SkinIndicator *StringMachineUI::createValueDisplayForParameter(unsigned index, const Rect &bounds, const KnobSkin &skin)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < Parameter_Count, nullptr);

    SkinIndicator *vd = new SkinIndicator(skin, *fFontEngine, this);
    fValueDisplayForParameter[index].reset(vd);
    vd->setAbsolutePos(bounds.x, bounds.y);

    Font font;
    font.size = 10.0;
    font.color = ColorRGBA8{0xff, 0xff, 0xff, 0xff};
    vd->setTextFont(font);

    vd->setTextOffset({0.0, 1.0});

    const Parameter &param = fParameters[index];
    vd->setText(formatDisplayValue(param.ranges.def));

    return vd;
}

void StringMachineUI::computeAdsrPlot(float *data, unsigned size)
{
    AHDSREnvelope env;
    AHDSREnvelope::Settings settings = fEnvSettings;

    double keyOnTime = settings.attack + settings.hold + settings.decay;
    double nonSustainTime = keyOnTime + std::min<double>(settings.release, 1.0);
    double sustainTime = nonSustainTime * (1.0 / 4.0);
    double totalRunTime = nonSustainTime + sustainTime;

    // double totalRunTime = 6.0;
    // double keyOnTime = 0.5 * totalRunTime;

    double sampleRate = size / totalRunTime;
    unsigned keyOnSamples = (unsigned)(0.5 + keyOnTime * sampleRate);

    //
    env.init(&settings, sampleRate);
    env.trigger();
    env.process(data, keyOnSamples);
    env.release();
    env.process(data + keyOnSamples, size - keyOnSamples);

#if 0
    // to decibel
    for (unsigned i = 0; i < size; ++i) {
        constexpr double dbMin = -40.0;
        constexpr double dbMax = +0.0;
        double sample = data[i];
        if (sample <= 0.0)
            sample = dbMin;
        else
            sample = 20.0 * std::log10(sample);
        data[i] = (sample - dbMin) * (1.0 / (dbMax - dbMin));
    }
#endif

    for (unsigned i = 0; i < size; ++i)
        data[i] *= 0.9f;
}

bool StringMachineUI::checkForKeySequence(const KeyPress *sequence, unsigned sequenceSize)
{
    if (KeyHistorySize < sequenceSize)
        return false;

    bool sequencesEqual = true;
    unsigned historyIndex = (fKeyHistoryIndex + KeyHistorySize - sequenceSize) % KeyHistorySize;
    for (unsigned i = 0; i < sequenceSize && sequencesEqual; ++i) {
        sequencesEqual = sequence[i] == fKeyHistory[historyIndex];
        historyIndex = (historyIndex + 1) % KeyHistorySize;
    }

    return sequencesEqual;
}

void StringMachineUI::checkForDeveloperCode()
{
    const std::array<KeyPress, 9> sequence1{{
        {kKeyUp, true}, {kKeyUp, true},
        {kKeyDown, true}, {kKeyDown, true},
        {kKeyLeft, true}, {kKeyRight, true},
        {kKeyLeft, true}, {kKeyRight, true},
        {'\r', false},
    }};

    const std::array<KeyPress, 10> sequence2{{
        {kKeyUp, true}, {kKeyUp, true},
        {kKeyDown, true}, {kKeyDown, true},
        {kKeyLeft, true}, {kKeyRight, true},
        {kKeyLeft, true}, {kKeyRight, true},
        {'b', false}, {'a', false},
    }};

    bool entered = checkForKeySequence(sequence1.data(), sequence1.size()) ||
        checkForKeySequence(sequence2.data(), sequence2.size());

    if (entered)
        enableDeveloperMode();
}

void StringMachineUI::enableDeveloperMode()
{
    if (fDeveloperMode)
        return;

    fDeveloperMode = true;

    SkinTriggerButton *randButton = new SkinTriggerButton(fSkinTriggerButton, this);
    fRandomizeButton.reset(randButton);
    randButton->setAbsolutePos(165, 6);
    randButton->TriggerCallback = [this]() { randomizeParameters(); };

    repaint();
}

double StringMachineUI::convertNormalizedToParameter(unsigned index, double value)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < Parameter_Count, 0.0)

    const Parameter &param = fParameters[index];
    double min = param.ranges.min;
    double max = param.ranges.max;

    if (param.hints & kParameterIsLogarithmic)
        value = min * std::pow(max / min, value);
    else
        value = min + value * (max - min);

    if (param.hints & kParameterIsInteger)
        value = std::lround(value);

    return value;
}

double StringMachineUI::convertNormalizedFromParameter(unsigned index, double value)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < Parameter_Count, 0.0)

    const Parameter &param = fParameters[index];
    double min = param.ranges.min;
    double max = param.ranges.max;

    if (param.hints & kParameterIsLogarithmic)
        value = std::log(value / min) / std::log(max / min);
    else
        value = (value - min) / (max - min);

    return value;
}

void StringMachineUI::randomizeParameters()
{
    std::minstd_rand &rand = fRandomGenerator;

    for (unsigned p = 0; p < Parameter_Count; ++p) {
        if (!isRandomizableParameter(p))
            continue;

        double value = std::uniform_real_distribution<double>{0.0, 1.0}(rand);
        value = convertNormalizedToParameter(p, value);
        setParameterValue(p, value);
        parameterChanged(p, value);
    }
}

bool StringMachineUI::isRandomizableParameter(unsigned index)
{
    switch (index) {
    case pIdMasterGain:
        return false;
    default:
        return true;
    }
}

std::string StringMachineUI::formatDisplayValue(double value)
{
    char buf[64];
    sprintf(buf, "%.2f", value);
    return buf;
}

std::unique_ptr<FontEngine> StringMachineUI::fFontEngine;

///
namespace DISTRHO {

UI *createUI()
{
    return new StringMachineUI;
}

} // namespace DISTRHO
