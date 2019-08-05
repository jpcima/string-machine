#pragma once

#define DISTRHO_PLUGIN_BRAND           "Jean Pierre Cimalando"
#define DISTRHO_PLUGIN_NAME            "String machine stereo chorus"
#define DISTRHO_PLUGIN_URI             "http://jpcima.sdf1.org/lv2/string-machine-chorus-stereo"
#define DISTRHO_PLUGIN_HOMEPAGE        "https://github.com/jpcima/string-machine"
#define DISTRHO_PLUGIN_UNIQUE_ID       'S','t','r','C'
#define DISTRHO_PLUGIN_VERSION         0,0,0
#define DISTRHO_PLUGIN_LABEL           "String machine stereo chorus"
#define DISTRHO_PLUGIN_LICENSE         "http://spdx.org/licenses/GPL-2.0-or-later"
#define DISTRHO_PLUGIN_MAKER           "Jean Pierre Cimalando"
#define DISTRHO_PLUGIN_DESCRIPTION     "Emulation of an electronic string ensemble chorus"
#define DISTRHO_PLUGIN_NUM_INPUTS      2
#define DISTRHO_PLUGIN_NUM_OUTPUTS     2
#define DISTRHO_PLUGIN_IS_SYNTH        0
#define DISTRHO_PLUGIN_HAS_UI          0
#define DISTRHO_PLUGIN_HAS_EMBED_UI    0
#define DISTRHO_PLUGIN_HAS_EXTERNAL_UI 0
#define DISTRHO_PLUGIN_IS_RT_SAFE      1
#define DISTRHO_PLUGIN_WANT_PROGRAMS   0
#define DISTRHO_PLUGIN_WANT_STATE      0
#define DISTRHO_PLUGIN_WANT_FULL_STATE 0

#define DISTRHO_PLUGIN_WANT_DIRECT_ACCESS 1

enum {
    pIdBypass,

    pIdChoDepth,
    pIdChoRate1,
    pIdChoDepth1,
    pIdChoRate2,
    pIdChoDepth2,
    pIdChoModel,

    pIdWetGain,
    pIdDryGain,

    ///
    Parameter_Count
};

enum {
    ///
    State_Count,
};
