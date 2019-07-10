#pragma once
#include "ui/Geometry.h"

#if !defined(DECL_IGNORABLE)
#if defined(__GNUC__)
#define DECL_IGNORABLE __attribute__((unused))
#else
#define DECL_IGNORABLE
#endif
#endif

struct Label {
    const char *text;
    int align;
    Rect bounds;
};

namespace MainLayout {
    // Positioning generated from Fluid UI "resources/ui/layout.fl".
    DECL_IGNORABLE static Rect window_TopLevel = {741, 151, 935, 245};
    DECL_IGNORABLE static Rect group_StringOsc = {5, 30, 185, 170};
    DECL_IGNORABLE static Rect subgroup_AutoDetune = {10, 50, 85, 145};
    DECL_IGNORABLE static Rect knob_OscDetune = {50, 145, 30, 30};
    DECL_IGNORABLE static Rect val_OscDetune = {45, 178, 40, 12};
    DECL_IGNORABLE static Rect val_OscDetune1 = {35, 83, 40, 12};
    DECL_IGNORABLE static Rect val_OscDetune2 = {35, 103, 40, 12};
    DECL_IGNORABLE static Rect subgroup_StringOsc = {105, 50, 80, 145};
    DECL_IGNORABLE static Rect knob_OscHpCutoffUpper = {130, 80, 30, 30};
    DECL_IGNORABLE static Rect knob_OscHpCutoffLower = {130, 145, 30, 30};
    DECL_IGNORABLE static Rect val_OscHpCutoffUpper = {125, 113, 40, 12};
    DECL_IGNORABLE static Rect val_OscHpCutoffLower = {125, 178, 40, 12};
    DECL_IGNORABLE static Rect group_StringFilters = {190, 40, 210, 155};
    DECL_IGNORABLE static Rect knob_FltLpCutoffUpper = {205, 75, 30, 30};
    DECL_IGNORABLE static Rect val_FltLpCutoffUpper = {200, 108, 40, 12};
    DECL_IGNORABLE static Rect knob_FltLpCutoffLower = {205, 140, 30, 30};
    DECL_IGNORABLE static Rect val_FltLpCutoffLower = {200, 173, 40, 12};
    DECL_IGNORABLE static Rect knob_FltHpCutoffUpper = {255, 75, 30, 30};
    DECL_IGNORABLE static Rect val_FltHpCutoffUpper = {250, 108, 40, 12};
    DECL_IGNORABLE static Rect knob_FltHpCutoffLower = {255, 140, 30, 30};
    DECL_IGNORABLE static Rect val_FltHpCutoffLower = {250, 173, 40, 12};
    DECL_IGNORABLE static Rect knob_FltHsCutoffEq = {355, 75, 30, 30};
    DECL_IGNORABLE static Rect val_FltHsCutoffEq = {350, 108, 40, 12};
    DECL_IGNORABLE static Rect knob_FltHsBoostEq = {355, 140, 30, 30};
    DECL_IGNORABLE static Rect val_FltHsBoostEq = {350, 173, 40, 12};
    DECL_IGNORABLE static Rect group_Mixer = {400, 40, 60, 155};
    DECL_IGNORABLE static Rect knob_MixGainUpper = {415, 75, 30, 30};
    DECL_IGNORABLE static Rect val_MixGainUpper = {410, 108, 40, 12};
    DECL_IGNORABLE static Rect knob_MixGainLower = {415, 140, 30, 30};
    DECL_IGNORABLE static Rect val_MixGainLower = {410, 173, 40, 12};
    DECL_IGNORABLE static Rect group_SolinaChorus = {460, 10, 165, 230};
    DECL_IGNORABLE static Rect knob_ChoDepth1 = {565, 80, 30, 30};
    DECL_IGNORABLE static Rect knob_ChoDepth2 = {565, 145, 30, 30};
    DECL_IGNORABLE static Rect val_ChoDepth1 = {560, 113, 40, 12};
    DECL_IGNORABLE static Rect val_ChoDepth2 = {560, 178, 40, 12};
    DECL_IGNORABLE static Rect knob_ChoRate1 = {490, 80, 30, 30};
    DECL_IGNORABLE static Rect knob_ChoRate2 = {490, 145, 30, 30};
    DECL_IGNORABLE static Rect val_ChoRate1 = {485, 113, 40, 12};
    DECL_IGNORABLE static Rect val_ChoRate2 = {485, 178, 40, 12};
    DECL_IGNORABLE static Rect slider_ChoDepth = {510, 200, 100, 25};
    DECL_IGNORABLE static Rect led_Lfo1 = {537, 90, 9, 9};
    DECL_IGNORABLE static Rect led_Lfo2 = {537, 155, 9, 9};
    DECL_IGNORABLE static Rect btn_ChoEnabled = {480, 40, 35, 15};
    DECL_IGNORABLE static Rect group_Level = {625, 30, 175, 90};
    DECL_IGNORABLE static Rect knob_MasterGain = {640, 65, 30, 30};
    DECL_IGNORABLE static Rect val_MasterGain = {635, 98, 40, 12};
    DECL_IGNORABLE static Rect vu_LeftVolume = {700, 67, 95, 11};
    DECL_IGNORABLE static Rect vu_RightVolume = {700, 82, 95, 11};
    DECL_IGNORABLE static Rect group_Envelope = {625, 130, 305, 85};
    DECL_IGNORABLE static Rect knob_EnvAttack = {640, 160, 30, 30};
    DECL_IGNORABLE static Rect val_EnvAttack = {635, 193, 40, 12};
    DECL_IGNORABLE static Rect knob_EnvDecay = {685, 160, 30, 30};
    DECL_IGNORABLE static Rect val_EnvDecay = {680, 193, 40, 12};
    DECL_IGNORABLE static Rect knob_EnvSustain = {730, 160, 30, 30};
    DECL_IGNORABLE static Rect val_EnvSustain = {725, 193, 40, 12};
    DECL_IGNORABLE static Rect knob_EnvRelease = {775, 160, 30, 30};
    DECL_IGNORABLE static Rect val_EnvRelease = {770, 193, 40, 12};
    DECL_IGNORABLE static Rect plot_Env = {815, 155, 105, 45};
    DECL_IGNORABLE static Label group_StringOsc_label = {"String Osc", 17, {5, 30, 185, 170}};
    DECL_IGNORABLE static Label subgroup_AutoDetune_label = {"Auto Detune", 17, {10, 50, 85, 145}};
    DECL_IGNORABLE static Label knob_OscDetune_label = {"Detune", 1, {50, 145, 30, 30}};
    DECL_IGNORABLE static Label val_OscDetune1_label = {"4'", 4, {35, 83, 40, 12}};
    DECL_IGNORABLE static Label val_OscDetune2_label = {"8'", 4, {35, 103, 40, 12}};
    DECL_IGNORABLE static Label subgroup_StringOsc_label = {"Shape", 17, {105, 50, 80, 145}};
    DECL_IGNORABLE static Label knob_OscHpCutoffUpper_label = {"HP cutoff 4'", 1, {130, 80, 30, 30}};
    DECL_IGNORABLE static Label knob_OscHpCutoffLower_label = {"HP cutoff 8'", 1, {130, 145, 30, 30}};
    DECL_IGNORABLE static Label group_StringFilters_label = {"String Filters", 17, {190, 40, 210, 155}};
    DECL_IGNORABLE static Label knob_FltLpCutoffUpper_label = {"4' LP", 1, {205, 75, 30, 30}};
    DECL_IGNORABLE static Label knob_FltLpCutoffLower_label = {"8' LP", 1, {205, 140, 30, 30}};
    DECL_IGNORABLE static Label knob_FltHpCutoffUpper_label = {"4' HP", 1, {255, 75, 30, 30}};
    DECL_IGNORABLE static Label knob_FltHpCutoffLower_label = {"8' HP", 1, {255, 140, 30, 30}};
    DECL_IGNORABLE static Label knob_FltHsCutoffEq_label = {"4' EQ", 1, {355, 75, 30, 30}};
    DECL_IGNORABLE static Label knob_FltHsBoostEq_label = {"4' Boost", 1, {355, 140, 30, 30}};
    DECL_IGNORABLE static Label group_Mixer_label = {"Mixer", 17, {400, 40, 60, 155}};
    DECL_IGNORABLE static Label knob_MixGainUpper_label = {"Vol 4'", 1, {415, 75, 30, 30}};
    DECL_IGNORABLE static Label knob_MixGainLower_label = {"Vol 8'", 1, {415, 140, 30, 30}};
    DECL_IGNORABLE static Label group_SolinaChorus_label = {"Solina Chorus", 17, {460, 10, 165, 230}};
    DECL_IGNORABLE static Label knob_ChoDepth1_label = {"Depth 1", 1, {565, 80, 30, 30}};
    DECL_IGNORABLE static Label knob_ChoDepth2_label = {"Depth 2", 1, {565, 145, 30, 30}};
    DECL_IGNORABLE static Label knob_ChoRate1_label = {"Rate 1", 1, {490, 80, 30, 30}};
    DECL_IGNORABLE static Label knob_ChoRate2_label = {"Rate 2", 1, {490, 145, 30, 30}};
    DECL_IGNORABLE static Label slider_ChoDepth_label = {"Depth", 4, {510, 200, 100, 25}};
    DECL_IGNORABLE static Label led_Lfo1_label = {"LFO 1", 1, {537, 90, 9, 9}};
    DECL_IGNORABLE static Label led_Lfo2_label = {"LFO 2", 1, {537, 155, 9, 9}};
    DECL_IGNORABLE static Label btn_ChoEnabled_label = {"On/Off", 1, {480, 40, 35, 15}};
    DECL_IGNORABLE static Label group_Level_label = {"Level", 17, {625, 30, 175, 90}};
    DECL_IGNORABLE static Label knob_MasterGain_label = {"Output", 1, {640, 65, 30, 30}};
    DECL_IGNORABLE static Label vu_LeftVolume_label = {"L", 4, {700, 67, 95, 11}};
    DECL_IGNORABLE static Label vu_RightVolume_label = {"R", 4, {700, 82, 95, 11}};
    DECL_IGNORABLE static Label group_Envelope_label = {"ADSR Envelope", 17, {625, 130, 305, 85}};
    DECL_IGNORABLE static Label knob_EnvAttack_label = {"A", 1, {640, 160, 30, 30}};
    DECL_IGNORABLE static Label knob_EnvDecay_label = {"D", 1, {685, 160, 30, 30}};
    DECL_IGNORABLE static Label knob_EnvSustain_label = {"S", 1, {730, 160, 30, 30}};
    DECL_IGNORABLE static Label knob_EnvRelease_label = {"R", 1, {775, 160, 30, 30}};
    DECL_IGNORABLE static Label plot_Env_label = {"ADSR - Env", 1, {815, 155, 105, 45}};
};
