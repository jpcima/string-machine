#pragma once
#include "Widget.hpp"
#include <functional>
class KnobSkin;

class SkinSlider : public Widget {
public:
    SkinSlider(const KnobSkin &skin, Widget *group);

    enum Orientation {
        Horizontal,
        Vertical,
        Radial,
    };

    double value() const noexcept { return fValue; }
    void setValue(double value);

    bool valueNotified() const { return fValueNotify; }
    void setValueNotified(bool notified);

    void setValueBounds(double v1, double v2);
    void setNumSteps(unsigned numSteps);
    void setOrientation(Orientation ori);

    bool onMouse(const MouseEvent &event) override;
    bool onMotion(const MotionEvent &event) override;
    bool onScroll(const ScrollEvent &event) override;
    void onDisplay() override;

    std::function<void(double)> ValueChangedCallback;

private:
    double clampToBounds(double value);

private:
    double fValue = 0;
    double fValueBound1 = 0, fValueBound2 = 1;
    unsigned fNumSteps = 100;
    Orientation fOrientation = Horizontal;
    double fAngleMin = -2.3561945;
    double fAngleMax = +2.3561945;
    bool fValueNotify = true;
    bool fIsDragging = false;
    const KnobSkin &fSkin;
};
