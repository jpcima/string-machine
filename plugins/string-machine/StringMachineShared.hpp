#pragma once
#include "DistrhoPlugin.hpp"
#include <cstdint>

void InitParameter(uint32_t index, Parameter &parameter);

enum {
    pIdDetune,

    pIdOscHpCutoffUpper,
    pIdOscHpCutoffLower,

    pIdFltLpCutoffUpper,
    pIdFltHpCutoffUpper,
    pIdFltLpCutoffLower,
    pIdFltHpCutoffLower,
    pIdFltHsCutoffEq,
    pIdFltHsBoostEq,

    pIdMixGainUpper,
    pIdMixGainLower,

    pIdEnvAttack,
    pIdEnvDecay,
    pIdEnvSustain,
    pIdEnvRelease,

    pIdChoEnabled,
    pIdChoDepth,
    pIdChoRate1,
    pIdChoDepth1,
    pIdChoRate2,
    pIdChoDepth2,

    pIdMasterGain,

    ///
    Parameter_Count
};

enum {
    ///
    State_Count,
};
