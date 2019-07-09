#include "SkinToggleButton.hpp"
#include "KnobSkin.hpp"
#include "Window.hpp"
#include "Cairo.hpp"

SkinToggleButton::SkinToggleButton(const KnobSkin &skin, Widget *group)
    : Widget(group), fSkin(skin)
{
    setSize(skin.getWidth(), skin.getHeight());
}

void SkinToggleButton::setValue(bool value)
{
    if (fValue == value)
        return;

    fValue = value;
    if (ValueChangedCallback && fValueNotify)
        ValueChangedCallback(value);
    repaint();
}

void SkinToggleButton::setValueNotified(bool notified)
{
    fValueNotify = notified;
}

void SkinToggleButton::setHasInvertedAppearance(bool inv)
{
    if (fHasInvertedAppearance == inv)
        return;

    fHasInvertedAppearance = inv;
    repaint();
}

bool SkinToggleButton::onMouse(const MouseEvent &event)
{
    DGL::Size<uint> wsize = getSize();
    DGL::Point<int> mpos = event.pos;

    bool inside = mpos.getX() >= 0 && mpos.getY() >= 0 &&
        (unsigned)mpos.getX() < wsize.getWidth() && (unsigned)mpos.getY() < wsize.getHeight();

    if (event.press && event.button == 1 && inside) {
        fIsPressed = true;
        repaint();
        return true;
    }
    else if (!event.press && event.button == 1) {
        if (fIsPressed) {
            fIsPressed = false;
            if (inside)
                setValue(!fValue);
            repaint();
        }
    }

    return false;
}

void SkinToggleButton::onDisplay()
{
    const KnobSkin &skin = fSkin;
    cairo_t *cr = getParentWindow().getGraphicsContext().cairo;

    int w = getWidth();
    int h = getHeight();

    bool checked = fValue ^ fIsPressed;
    if (fHasInvertedAppearance)
        checked = !checked;

    cairo_surface_t *image = skin.getImageForRatio(checked ? 1.0 : 0.0);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_fill(cr);
}
