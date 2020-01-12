#include "MidiDefs.h"
#include <cstdio>

const float *MidiPitch = []() -> const float *
{
    static float pitch[128];
    for (unsigned i = 0; i < 128; ++i)
        pitch[i] = 440.0 * std::pow(2.0, (i - 69.0) / 12.0);
    return pitch;
}();

const char **MidiNoteName = []() -> const char **
{
    static const char *names[128];
    constexpr unsigned maxnamelen = 8;
    static char buffer[128 * maxnamelen];
    for (unsigned i = 0; i < 128; ++i) {
        const char *octave[] = {
            "C", "C#", "D", "D#", "E",
            "F", "F#", "G", "G#", "A", "A#", "B",
        };
        char *name = &buffer[i * maxnamelen];
        sprintf(name, "%s%d", octave[i % 12], (int)(i / 12) - 1);
        names[i] = name;
    }
    return names;
}();

static const float *MidiVolume10bit = []() -> const float *
{
    static float volume[1024];
    volume[0] = 0;

    auto calc_volume_14bit = [](unsigned cc14bit) -> double {
        if (cc14bit == 0) return 0.0;
        double x = cc14bit / (double)(127 << 7);
        return std::pow(10.0, 2.0 * std::log10(x)); // from GM recommendation
    };

    double mid_volume = calc_volume_14bit(100u << 7);
    double vol_scale = 1.0 / mid_volume; // compensation to force 0 dB at default
    for (unsigned i = 1; i < 1024; ++i)
        volume[i] = vol_scale * calc_volume_14bit(i << 4);

    return volume;
}();

float MidiGetVolume14bit(unsigned cc14bit)
{
    return MidiVolume10bit[cc14bit >> 4];
}
