#pragma once
#include <cstdint>

struct ColorRGBA8 {
    uint8_t r, g, b, a;
};

inline bool operator==(ColorRGBA8 a, ColorRGBA8 b) noexcept
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

inline bool operator!=(ColorRGBA8 a, ColorRGBA8 b) noexcept
{
    return !operator==(a, b);
}
