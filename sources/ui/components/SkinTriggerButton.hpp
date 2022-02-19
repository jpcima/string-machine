#pragma once
#include "SubWidget.hpp"
#include <functional>
class KnobSkin;

class SkinTriggerButton : public SubWidget {
public:
    SkinTriggerButton(const KnobSkin &skin, Widget *group);

    bool hasInvertedAppearance() const { return fHasInvertedAppearance; }
    void setHasInvertedAppearance(bool inv);

    bool onMouse(const MouseEvent &event) override;
    void onDisplay() override;

    std::function<void()> TriggerCallback;

private:
    bool fValue = false;
    bool fIsPressed = false;
    bool fHasInvertedAppearance = false;
    const KnobSkin &fSkin;
};
