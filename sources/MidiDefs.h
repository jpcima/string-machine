#pragma once
#include <cmath>

extern const float *MidiPitch/*[128]*/;
extern const char **MidiNoteName/*[128]*/;

enum {
    kStatusNoteOn = 0x90,
    kStatusNoteOff = 0x80,
    kStatusControllerChange = 0xb0,
    kStatusPitchBend = 0xe0,
};

enum {
    kCcDataMsb = 6,
    kCcDataLsb = 38,
    kCcNrpnLsb = 98,
    kCcNrpnMsb = 99,
    kCcRpnLsb = 100,
    kCcRpnMsb = 101,
    kCcSoundOff = 120,
    kCcResetControllers = 121,
    kCcNotesOff = 123,
    kCcOmniOff = 124,
    kCcOmniOn = 125,
    kCcMonoOn = 126,
    kCcPolyOn = 127,
};
