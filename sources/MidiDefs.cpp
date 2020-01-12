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
