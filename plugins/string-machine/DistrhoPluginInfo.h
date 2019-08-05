#pragma once

#define DISTRHO_PLUGIN_BRAND           "Jean Pierre Cimalando"
#define DISTRHO_PLUGIN_NAME            "String machine"
#define DISTRHO_PLUGIN_URI             "http://jpcima.sdf1.org/lv2/string-machine"
#define DISTRHO_PLUGIN_HOMEPAGE        "https://github.com/jpcima/string-machine"
#define DISTRHO_PLUGIN_UNIQUE_ID       'S','t','r','M'
#define DISTRHO_PLUGIN_VERSION         0,0,0
#define DISTRHO_PLUGIN_LABEL           "String machine"
#define DISTRHO_PLUGIN_LICENSE         "http://spdx.org/licenses/GPL-2.0-or-later"
#define DISTRHO_PLUGIN_MAKER           "Jean Pierre Cimalando"
#define DISTRHO_PLUGIN_DESCRIPTION     "Emulation of an electronic string ensemble synthesizer"
#define DISTRHO_PLUGIN_NUM_INPUTS      0
#define DISTRHO_PLUGIN_NUM_OUTPUTS     2
#define DISTRHO_PLUGIN_IS_SYNTH        1
#define DISTRHO_PLUGIN_HAS_UI          1
#define DISTRHO_PLUGIN_HAS_EMBED_UI    1
#define DISTRHO_PLUGIN_HAS_EXTERNAL_UI 0
#define DISTRHO_PLUGIN_IS_RT_SAFE      1
#define DISTRHO_PLUGIN_WANT_PROGRAMS   1
#define DISTRHO_PLUGIN_WANT_STATE      0
#define DISTRHO_PLUGIN_WANT_FULL_STATE 0

#define DISTRHO_PLUGIN_WANT_DIRECT_ACCESS 1

enum {
    pIdOscDetune,
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
    pIdEnvHold,
    pIdEnvDecay,
    pIdEnvSustain,
    pIdEnvRelease,

    pIdChoEnabled,
    pIdChoDepth,
    pIdChoRate1,
    pIdChoDepth1,
    pIdChoRate2,
    pIdChoDepth2,
    pIdChoModel,

    pIdMasterGain,

    ///
    Parameter_Count
};

enum {
    ///
    State_Count,
};
