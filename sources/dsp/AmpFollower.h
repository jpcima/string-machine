//          Copyright Jean Pierre Cimalando 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <cmath>

struct AmpFollower
{
    double p_ = 0;
    double mem_ = 0;
    void release(double t); // t = fs * release time
    double process(double x);
    void clear();
    double last_output() const;
};

inline void AmpFollower::release(double t)
{
    p_ = std::exp(-1.0 / t);
}

inline double AmpFollower::process(double x)
{
    double y;
    double ax = std::fabs(x);
    double p = p_;
    if (ax > mem_)
        y = ax;
    else
        y = p * mem_ + (1.0 - p) * ax;
    mem_ = y;
    return y;
}

inline void AmpFollower::clear()
{
    mem_ = 0;
}

inline double AmpFollower::last_output() const
{
    return mem_;
}
