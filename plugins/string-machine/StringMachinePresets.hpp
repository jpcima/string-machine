#pragma once
#include "DistrhoPluginInfo.h"

struct Preset {
    const char *name;
    struct Group { const char *name; };
    struct Parameter { int id; float value; };
    const Group *group;
    const Parameter *parameters;
};

extern const Preset Presets[];
extern const unsigned NumPresets;
