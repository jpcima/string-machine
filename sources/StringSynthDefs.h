#pragma once

namespace StringSynthDefs {
    enum { BufferLimit = 64 };
    enum { PolyphonyLimit = 32 };
};

// 1 to enable panning in the chorus, increase CPU usage requirement
#ifndef STRING_SYNTH_USE_STEREO
#   define STRING_SYNTH_USE_STEREO 1
#endif
