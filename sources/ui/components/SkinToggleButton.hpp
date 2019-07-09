#pragma once
#include "Widget.hpp"
#include <functional>
class KnobSkin;

class SkinToggleButton : public Widget {
public:
    SkinToggleButton(const KnobSkin &skin, Widget *group);

    bool value() const noexcept { return fValue; }
    void setValue(bool value);

    bool valueNotified() const { return fValueNotify; }
    void setValueNotified(bool notified);

    bool hasInvertedAppearance() const { return fHasInvertedAppearance; }
    void setHasInvertedAppearance(bool inv);

    bool onMouse(const MouseEvent &event) override;
    void onDisplay() override;

    std::function<void(bool)> ValueChangedCallback;

private:
    bool fValue = false;
    bool fIsPressed = false;
    bool fHasInvertedAppearance = false;
    bool fValueNotify = true;
    const KnobSkin &fSkin;
};
