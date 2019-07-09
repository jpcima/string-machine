#include "FontEngine.h"
#include <stdexcept>

FontEngine::FontEngine()
    : FontEngine(512, 512)
{
}

FontEngine::FontEngine(unsigned width, unsigned height)
{
    FONSparams params = {};
    params.width = width;
    params.height = height;
    params.flags = FONS_ZERO_TOPLEFT;
    params.userPtr = this;
    params.renderCreate = &renderCreate;
    params.renderResize = &renderResize;
    params.renderUpdate = &renderUpdate;
    params.renderDraw = &renderDraw;
    params.renderDelete = &renderDelete;

    FONScontext *ctx = fonsCreateInternal(&params);
    if (!ctx)
        throw std::runtime_error("cannot create font stash");
    fContext.reset(ctx);
}

FontEngine::~FontEngine()
{
}

bool FontEngine::addFont(const char *name, const uint8_t *data, unsigned size)
{
    FONScontext *ctx = fContext.get();
    return fonsAddFontMem(ctx, name, (uint8_t *)data, size, false) != FONS_INVALID;
}

void FontEngine::draw(cairo_t *cr, const char *text, const Font &font, double x, double y)
{
    FONScontext *ctx = fContext.get();

    const char *name = font.name.empty() ? "default" : font.name.c_str();
    int id = fonsGetFontByName(ctx, name);

    if (id == FONS_INVALID)
        return;

    fonsSetFont(ctx, id);
    fonsSetSize(ctx, font.size);
    fonsSetColor(ctx, font.color.r | (font.color.g << 8) | (font.color.b << 16) | (font.color.a << 24));
    fonsSetSpacing(ctx, font.spacing);
    fonsSetBlur(ctx, font.blur);

    fDrawingContext = cr;
    fonsDrawText(ctx, x, y, text, nullptr);
    fDrawingContext = nullptr;
}

void FontEngine::drawInBox(cairo_t *cr, const char *text, const Font &font, const Rect &box, int align)
{
    return drawInBox(cr, text, font, box.to<double>(), align);
}

void FontEngine::drawInBox(cairo_t *cr, const char *text, const Font &font, const RectF &box, int align)
{
    FONScontext *ctx = fContext.get();

    const char *name = font.name.empty() ? "default" : font.name.c_str();
    int id = fonsGetFontByName(ctx, name);

    if (id == FONS_INVALID)
        return;

    fonsSetFont(ctx, id);
    fonsSetSize(ctx, font.size);
    fonsSetColor(ctx, font.color.r | (font.color.g << 8) | (font.color.b << 16) | (font.color.a << 24));
    fonsSetSpacing(ctx, font.spacing);
    fonsSetBlur(ctx, font.blur);

    double x = box.x;
    double y = box.y;
    double w = box.w;
    double h = box.h;

    int fonsalign;

    switch (align & (AlignLeft|AlignRight)) {
    default:
        fonsalign = FONS_ALIGN_CENTER;
        x += 0.5 * w;
        break;
    case AlignLeft:
        fonsalign = (align & AlignInside) ? FONS_ALIGN_LEFT : FONS_ALIGN_RIGHT;
        break;
    case AlignRight:
        fonsalign = (align & AlignInside) ? FONS_ALIGN_RIGHT : FONS_ALIGN_LEFT;
        x += w;
        break;
    }

    switch (align & (AlignTop|AlignBottom)) {
    default:
        fonsalign |= FONS_ALIGN_MIDDLE;
        y += 0.5 * h;
        break;
    case AlignTop:
        fonsalign |= (align & AlignInside) ? FONS_ALIGN_TOP : FONS_ALIGN_BOTTOM;
        break;
    case AlignBottom:
        fonsalign |= (align & AlignInside) ? FONS_ALIGN_BOTTOM : FONS_ALIGN_TOP;
        y += h;
        break;
    }

    fonsSetAlign(ctx, fonsalign);
    draw(cr, text, font, x, y);
    fonsSetAlign(ctx, 0);
}

int FontEngine::renderCreate(void *uptr, int width, int height)
{
    FontEngine *self = (FontEngine *)uptr;
    cairo_surface_t *atlas = cairo_image_surface_create(CAIRO_FORMAT_A8, width, height);
    if (!atlas)
        throw std::runtime_error("cannot create cairo surface");
    self->fAtlas.reset(atlas);
    return true;
}

int FontEngine::renderResize(void *uptr, int width, int height)
{
    return renderCreate(uptr, width, height);
}

void FontEngine::renderUpdate(void *uptr, int *rect, const unsigned char *data)
{
    FontEngine *self = (FontEngine *)uptr;
    FONScontext *ctx = self->fContext.get();

    unsigned rx = rect[0];
    unsigned ry = rect[1];
    unsigned rw = rect[2] - rx;
    unsigned rh = rect[3] - ry;

    cairo_surface_t *atlas = self->fAtlas.get();

    unsigned tw = cairo_image_surface_get_width(atlas);
    unsigned th = cairo_image_surface_get_height(atlas);

    if (rx + rw > tw)
        rw = tw - rx;
    if (ry + rh > th)
        rh = th - ry;

    cairo_surface_flush(atlas);
    uint8_t *pixels = cairo_image_surface_get_data(atlas);
    unsigned stride = cairo_image_surface_get_stride(atlas);

    unsigned aw = 0;
    unsigned ah = 0;
    fonsGetAtlasSize(ctx, (int *)&aw, (int *)&ah);

    for (unsigned y = ry; y < ry + rh; ++y) {
        for (unsigned x = rx; x < rx + rw; ++x)
            pixels[x + y * stride] = data[x + y * aw];
    }

    cairo_surface_mark_dirty(atlas);
}

void FontEngine::renderDraw(void *uptr, const FONSquad *quads, const unsigned int *colors, int nquads)
{
    FontEngine *self = (FontEngine *)uptr;
    FONScontext *ctx = self->fContext.get();
    cairo_surface_t *atlas = self->fAtlas.get();
    cairo_t *cr = self->fDrawingContext;

    unsigned aw = 0;
    unsigned ah = 0;
    fonsGetAtlasSize(ctx, (int *)&aw, (int *)&ah);

    cairo_save(cr);

    for (unsigned i = 0; i < (unsigned)nquads; ++i) {
        RectF dst{
            quads[i].x0,
            quads[i].y0,
            quads[i].x1 - quads[i].x0,
            quads[i].y1 - quads[i].y0
        };

        RectF src{
            aw * quads[i].s0,
            ah * quads[i].t0,
            aw * (quads[i].s1 - quads[i].s0),
            ah * (quads[i].t1 - quads[i].t0)
        };

        ColorRGBA8 color = {
            (uint8_t)((colors[i] >>  0) & 0xff),
            (uint8_t)((colors[i] >>  8) & 0xff),
            (uint8_t)((colors[i] >> 16) & 0xff),
            (uint8_t)((colors[i] >> 24) & 0xff),
        };

        ///
        cairo_matrix_t mat;
        cairo_get_matrix(cr, &mat);

        cairo_translate(cr, dst.x, dst.y);
        cairo_scale(cr, dst.w / src.w, dst.h / src.h);

        cairo_rectangle(cr, 0, 0, src.w, src.h);
        cairo_reset_clip(cr);
        cairo_clip_preserve(cr);

        cairo_set_source_rgba8(cr, color);
        cairo_mask_surface(cr, atlas, -src.x, -src.y);
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
        cairo_stroke(cr);

        cairo_set_matrix(cr, &mat);
    }

    cairo_restore(cr);
}

void FontEngine::renderDelete(void *uptr)
{
    (void)uptr;
}
