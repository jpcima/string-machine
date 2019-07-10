#include "PlotView.hpp"
#include "Window.hpp"
#include "Cairo.hpp"
#include "ui/Cairo++.h"

PlotView::PlotView(Widget *group)
    : Widget(group)
{
}

void PlotView::invalidateData()
{
    fHasValidData = false;
    repaint();
}

void PlotView::onDisplay()
{
    cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

    unsigned w = getWidth();
    unsigned h = getHeight();

    if ((int)w <= 0 || (int)h <= 0)
        return;

    std::vector<float> &plotData = fPlotData;
    if (plotData.size() != w + 1 || !fHasValidData) {
        plotData.clear();
        plotData.resize(w + 1);
        if (DataCallback)
            DataCallback(plotData.data(), w + 1);
    }

    cairo_save(cr);

    cairo_rectangle(cr, 0, 0, w, h);
    cairo_clip(cr);

    // background
    cairo_set_source_rgba8(cr, fBackgroundColor);
    cairo_paint(cr);

    // pen
    cairo_new_path(cr);
    cairo_move_to(cr, 0.0, (1 - plotData[0]) * h);
    for (unsigned i = 1; i <= w; ++i)
        cairo_line_to(cr, i, (1 - plotData[i]) * h);
    cairo_set_source_rgba8(cr, fPenColor);
    cairo_stroke_preserve(cr);

    // brush
    cairo_line_to(cr, w, h);
    cairo_line_to(cr, 0, h);
    cairo_close_path(cr);
    cairo_set_source_rgba8(cr, fBrushColor);
    cairo_fill(cr);

    // contour
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_set_source_rgba8(cr, {0x2e, 0x34, 0x35, 0xff});
    cairo_stroke(cr);

    cairo_restore(cr);
}
