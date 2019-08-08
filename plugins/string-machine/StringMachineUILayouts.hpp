#pragma once
#include "ui/Geometry.h"

#if !defined(DECL_IGNORABLE)
#if defined(__GNUC__)
#define DECL_IGNORABLE __attribute__((unused))
#else
#define DECL_IGNORABLE
#endif
#endif

struct Label {
    const char *text;
    int align;
    Rect bounds;
};

namespace MainLayout {
    #include "StringMachineUILayouts.Main.inc"
};
