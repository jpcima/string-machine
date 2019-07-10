#pragma once
#include "Geometry.h"
#include "Color.h"
#include <cairo/cairo.h>
#include <type_traits>
#include <memory>
#include <cmath>

cairo_surface_t *cairo_image_surface_create_from_png_data(const char *data, unsigned length);
void cairo_set_source_rgba8(cairo_t *cr, ColorRGBA8 c);

struct cairo_surface_deleter;
typedef std::unique_ptr<std::remove_pointer<cairo_surface_t>::type, cairo_surface_deleter> cairo_surface_u;

///
struct cairo_surface_deleter {
    void operator()(cairo_surface_t *x) const noexcept { cairo_surface_destroy(x); }
};

template <class T>
inline void cairo_rectangle(cairo_t *cr, const RectT<T> &r)
{
    cairo_rectangle(cr, r.x, r.y, r.w, r.h);
}

template <class T>
void cairo_rounded_rectangle(cairo_t *cr, const RectT<T> &r, double radius)
{
    double degrees = M_PI / 180.0;

    double x = r.x;
    double y = r.y;
    double w = r.w;
    double h = r.h;

    cairo_new_sub_path(cr);
    cairo_arc(cr, x + w - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc(cr, x + w - radius, y + h - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc(cr, x + radius, y + h - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(cr);
}
