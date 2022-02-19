#pragma once
#include "SubWidget.hpp"
#include "ui/Color.h"
#include <functional>
#include <vector>

class PlotView : public SubWidget {
public:
    explicit PlotView(Widget *group);

    void invalidateData();

    std::function<void(float *, unsigned)> DataCallback;

protected:
    void onDisplay() override;

private:
    std::vector<float> fPlotData;
    bool fHasValidData = false;
    ColorRGBA8 fPenColor {0xfc, 0xe9, 0x4f, 0xff};
    ColorRGBA8 fBrushColor {0xc1, 0x7d, 0x11, 0xff};
    ColorRGBA8 fBackgroundColor {0, 0, 0, 0xff};
};
