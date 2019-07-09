#include "KnobSkin.hpp"
#include <cassert>

KnobSkin::KnobSkin(const char *pngData, unsigned pngSize, unsigned imageCount)
    : fSurface(cairo_image_surface_create_from_png_data(pngData, pngSize)),
      fImageCount(imageCount),
      fSubSurface(new cairo_surface_u[imageCount])
{
    assert(imageCount > 0);

    cairo_surface_t *surface = fSurface.get();
    if (!surface)
        throw std::runtime_error("cannot load skin image");

    cairo_format_t fmt = cairo_image_surface_get_format(surface);
    unsigned char *d = cairo_image_surface_get_data(surface);
    unsigned w = cairo_image_surface_get_width(surface);
    unsigned hf = cairo_image_surface_get_height(surface);
    unsigned h = hf / imageCount;
    unsigned s = cairo_image_surface_get_stride(surface);

    for (unsigned i = 0; i < imageCount; ++i) {
        cairo_surface_t *sub = cairo_image_surface_create_for_data(d + i * (h * s), fmt, w, h, s);
        if (!surface)
            throw std::runtime_error("cannot extract skin image region");
        fSubSurface[i].reset(sub);
    }
}

cairo_surface_t *KnobSkin::getImageForRatio(double ratio) const
{
    unsigned imageCount = fImageCount;
    int index = (int)(0.5 + ratio * imageCount);
    index = (index < 0) ? 0 : index;
    index = ((unsigned)index < imageCount) ? index : (imageCount - 1);
    return fSubSurface[index].get();
}

unsigned KnobSkin::getWidth() const
{
    return cairo_image_surface_get_width(fSubSurface[0].get());
}

unsigned KnobSkin::getHeight() const
{
    return cairo_image_surface_get_height(fSubSurface[0].get());
}
