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

    cairo_new_path(cr);
    cairo_arc(cr, x + w - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc(cr, x + w - radius, y + h - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc(cr, x + radius, y + h - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(cr);
}

enum RectangleCorner {
    RectangleNE = 1 << 0,
    RectangleSE = 1 << 1,
    RectangleSW = 1 << 2,
    RectangleNW = 1 << 3,
    RectangleAllCorners = RectangleNE|RectangleSE|RectangleSW|RectangleNW,
};

template <class T>
void cairo_rounded_rectangle_with_corners(cairo_t *cr, const RectT<T> &r, double radius, int corners)
{
    double degrees = M_PI / 180.0;

    double x = r.x;
    double y = r.y;
    double w = r.w;
    double h = r.h;

    cairo_new_path(cr);
    if (corners & RectangleNE)
        cairo_arc(cr, x + w - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    else
        cairo_move_to(cr, x + w, y);
    if (corners & RectangleSE)
        cairo_arc(cr, x + w - radius, y + h - radius, radius, 0 * degrees, 90 * degrees);
    else
        cairo_line_to(cr, x + w, y + h);
    if (corners & RectangleSW)
        cairo_arc(cr, x + radius, y + h - radius, radius, 90 * degrees, 180 * degrees);
    else
        cairo_line_to(cr, x, y + h);
    if (corners & RectangleNW)
        cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    else
        cairo_line_to(cr, x, y);
    cairo_close_path(cr);
}
