#include "SkinSlider.hpp"
#include "KnobSkin.hpp"
#include "Cairo.hpp"

///
SkinSlider::SkinSlider(const KnobSkin &skin, Widget *group)
    : SubWidget(group), fSkin(skin)
{
    setSize(skin.getWidth(), skin.getHeight());
}

void SkinSlider::setValue(double value)
{
    value = clampToBounds(value);

    if (fValue == value)
        return;

    fValue = value;
    if (ValueChangedCallback && fValueNotify)
        ValueChangedCallback(value);
    repaint();
}

void SkinSlider::setValueNotified(bool notified)
{
    fValueNotify = notified;
}

void SkinSlider::setValueBounds(double v1, double v2)
{
    fValueBound1 = v1;
    fValueBound2 = v2;
    setValue(fValue);
}

void SkinSlider::setNumSteps(unsigned numSteps)
{
    fNumSteps = numSteps;
}

void SkinSlider::setOrientation(Orientation ori)
{
    if (fOrientation == ori)
        return;

    fOrientation = ori;
    repaint();
}

bool SkinSlider::onMouse(const MouseEvent &event)
{
    DGL::Size<uint> wsize = getSize();
    DGL::Point<int> mpos{(int)event.pos.getX(), (int)event.pos.getY()};

    if (!fIsDragging && event.press && event.button == 1) {
        bool insideX = mpos.getX() >= 0 && (unsigned)mpos.getX() < wsize.getWidth();
        bool insideY = mpos.getY() >= 0 && (unsigned)mpos.getY() < wsize.getHeight();

        if (!insideX || !insideY)
            return false;

        fIsDragging = true;

        double fill = 0;
        if (fOrientation == Horizontal) {
            fill = mpos.getX() / (double)wsize.getWidth();
            setValue(fValueBound1 + fill * (fValueBound2 - fValueBound1));
        }
        else if (fOrientation == Vertical) {
            fill = 1.0 - (mpos.getY() / (double)wsize.getHeight());
            setValue(fValueBound1 + fill * (fValueBound2 - fValueBound1));
        }

        return true;
    }
    else if (fIsDragging && !event.press && event.button == 1) {
        fIsDragging = false;
        return true;
    }

    return false;
}

bool SkinSlider::onMotion(const MotionEvent &event)
{
    DGL::Size<uint> wsize = getSize();
    DGL::Point<int> mpos{(int)event.pos.getX(), (int)event.pos.getY()};

    if (fIsDragging) {
        double fill = 0;
        bool doNotSet = false;
        if (fOrientation == Horizontal)
            fill = mpos.getX() / (double)wsize.getWidth();
        else if (fOrientation == Vertical)
            fill = 1.0 - (mpos.getY() / (double)wsize.getHeight());
        else if (fOrientation == Radial) {
            double dx = mpos.getX() - 0.5 * getWidth();
            double dy = mpos.getY() - 0.5 * getHeight();
            if (dx * dx + dy * dy < 100.0)
                doNotSet = true;
            else {
                double angle = std::atan2(dx, -dy);
                angle = std::max(angle, fAngleMin);
                angle = std::min(angle, fAngleMax);
                fill = (angle - fAngleMin) / (fAngleMax - fAngleMin);
            }
        }
        fill = (fill < 0) ? 0 : fill;
        fill = (fill > 1) ? 1 : fill;
        if (!doNotSet)
            setValue(fValueBound1 + fill * (fValueBound2 - fValueBound1));
        return true;
    }

    return false;
}

bool SkinSlider::onScroll(const ScrollEvent &event)
{
    DGL::Size<uint> wsize = getSize();
    DGL::Point<int> mpos{(int)event.pos.getX(), (int)event.pos.getY()};

    bool inside =
        mpos.getX() >= 0 && mpos.getY() >= 0 &&
        (unsigned)mpos.getX() < wsize.getWidth() && (unsigned)mpos.getY() < wsize.getHeight();

    if (inside) {
        double amount = event.delta.getX() - event.delta.getY();
        if (fOrientation == Vertical)
            amount = -amount;
        setValue(fValue + amount * (fValueBound2 - fValueBound1) / fNumSteps);
        return true;
    }

    return false;
}

void SkinSlider::onDisplay()
{
    const KnobSkin &skin = fSkin;
    cairo_t *cr = static_cast<const CairoGraphicsContext &>(getGraphicsContext()).handle;

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
}

double SkinSlider::clampToBounds(double value)
{
    double vmin = fValueBound1;
    double vmax = fValueBound2;
    if (vmin > vmax)
        std::swap(vmin, vmax);

    value = (value < vmin) ? vmin : value;
    value = (value > vmax) ? vmax : value;
    return value;
}
