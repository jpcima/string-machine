#pragma once
#include "ui/FontEngine.h"
#include "ui/Color.h"
#include "ui/Geometry.h"
#include "SubWidget.hpp"
#include <string>
#include <functional>
class KnobSkin;
class FontEngine;

class SkinIndicator : public SubWidget {
public:
    SkinIndicator(const KnobSkin &skin, FontEngine &fe, Widget *group);

    enum Orientation {
        Horizontal,
        Vertical,
    };

    double value() const noexcept { return fValue; }
    void setValue(double value);

    bool valueNotified() const { return fValueNotify; }
    void setValueNotified(bool notified);

    void setValueBounds(double v1, double v2);
    void setNumSteps(unsigned numSteps);

    //
    const std::string &text() const { return fText; }
    void setText(std::string text);

    const Font &textFont() const { return fTextFont; }
    void setTextFont(const Font &font);

    int textAlign() const { return fTextAlign; }
    void setTextAlign(int align) { fTextAlign = align; }

    PointF textOffset() const { return fTextOffset; }
    void setTextOffset(PointF off) { fTextOffset = off; }

    //
    void onDisplay() override;

    std::function<void(double)> ValueChangedCallback;

private:
    double clampToBounds(double value);

private:
    double fValue = 0;
    double fValueBound1 = 0, fValueBound2 = 1;
    bool fValueNotify = true;
    const KnobSkin &fSkin;

    FontEngine &fFontEngine;
    std::string fText;
    Font fTextFont;
    ColorRGBA8 fTextColor;
    int fTextAlign = 0;
    PointF fTextOffset;
};
