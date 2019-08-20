#include <cmath>
#include <cstdint>

template <class T> T min(T a, T b) { return (a < b) ? a : b; }
template <class T> T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    void declare(...) {}
};

class UI {
public:
    void openHorizontalBox(...) {}
    void openVerticalBox(...) {}
    void closeBox(...) {}
    void declare(...) {}
    void addButton(...) {}
    void addCheckButton(...) {}
    void addVerticalSlider(...) {}
    void addHorizontalSlider(...) {}
    void addVerticalBargraph(...) {}
};

class dsp {
};

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#define virtual /* do not make methods virtual */

<<includeIntrinsic>>
<<includeclass>>

#undef virtual

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
