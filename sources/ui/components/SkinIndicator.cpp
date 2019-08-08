#include "SkinIndicator.hpp"
#include "KnobSkin.hpp"
#include "Window.hpp"
#include "Cairo.hpp"

SkinIndicator::SkinIndicator(const KnobSkin &skin, FontEngine &fe, Widget *group)
    : Widget(group), fSkin(skin), fFontEngine(fe)
{
    setSize(skin.getWidth(), skin.getHeight());
}

void SkinIndicator::setValue(double value)
{
    value = clampToBounds(value);

    if (fValue == value)
        return;

    fValue = value;
    if (ValueChangedCallback && fValueNotify)
        ValueChangedCallback(value);
    repaint();
}

void SkinIndicator::setValueNotified(bool notified)
{
    fValueNotify = notified;
}

void SkinIndicator::setValueBounds(double v1, double v2)
{
    fValueBound1 = v1;
    fValueBound2 = v2;
    setValue(fValue);
}

void SkinIndicator::setText(std::string text)
{
    if (fText == text)
        return;

    fText = text;
    repaint();
}

void SkinIndicator::setTextFont(const Font &font)
{
    if (fTextFont == font)
        return;

    fTextFont = font;
    repaint();
}

void SkinIndicator::onDisplay()
{
    const KnobSkin &skin = fSkin;
    cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

    int w = getWidth();
    int h = getHeight();

    //
    double v1 = fValueBound1;
    double v2 = fValueBound2;

    //
    double value = fValue;
    double fill = 0;
    if (v1 != v2)
        fill = (value - v1) / (v2 - v1);

    //
    cairo_surface_t *image = skin.getImageForRatio(fill);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_fill(cr);

    //
    const std::string &text = fText;
    if (!text.empty())
        fFontEngine.drawInBox(cr, text.c_str(), fTextFont, RectF(fTextOffset.x, fTextOffset.y, w, h), fTextAlign);
}

double SkinIndicator::clampToBounds(double value)
{
    double vmin = fValueBound1;
    double vmax = fValueBound2;
    if (vmin > vmax)
        std::swap(vmin, vmax);

    value = (value < vmin) ? vmin : value;
    value = (value > vmax) ? vmax : value;
    return value;
}
