#pragma once
#include "ui/Cairo++.h"

class KnobSkin {
public:
    KnobSkin(const char *pngData, unsigned pngSize, unsigned imageCount);
    cairo_surface_t *getImageForRatio(double ratio) const;

    unsigned getWidth() const;
    unsigned getHeight() const;

private:
    cairo_surface_u fSurface;
    unsigned fImageCount = 0;
    std::unique_ptr<cairo_surface_u[]> fSubSurface;
};
