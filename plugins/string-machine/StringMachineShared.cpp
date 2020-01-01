#include "StringMachineShared.hpp"
#include "StringSynthDefs.h"
#include <cmath>

void InitParameter(uint32_t index, Parameter &parameter)
{
    ParameterEnumerationValue *pev;

    switch (index) {
    case pIdOscDetune:
        parameter.symbol = "osc_detune";
        parameter.name = "Oscillator detune";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(0.0016, 0.0, 1.0);
        break;
    case pIdOscHpCutoffUpper:
        parameter.symbol = "osc_hp_cutoff_upper";
        parameter.name = "Oscillator HP Cutoff 4'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(8.0, -20.0, 60.0);
        break;
    case pIdOscHpCutoffLower:
        parameter.symbol = "osc_hp_cutoff_lower";
        parameter.name = "Oscillator HP Cutoff 8'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(8.0, -20.0, 60.0);
        break;
    case pIdOscPwmDepth:
        parameter.symbol = "osc_pwm_depth";
        parameter.name = "Oscillator PWM Depth";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "%";
        parameter.ranges = ParameterRanges(0.0, 0.0, 100.0);
        break;
    case pIdOscPwmFrequency:
        parameter.symbol = "osc_pwm_frequency";
        parameter.name = "Oscillator PWM Frequency";
        parameter.hints = kParameterIsAutomable|kParameterIsLogarithmic;
        parameter.unit = "Hz";
        parameter.ranges = ParameterRanges(0.25, 0.1, 5.0);
        break;

    case pIdFltLpCutoffUpper:
        parameter.symbol = "flt_lp_cutoff_upper";
        parameter.name = "Filters LP Cutoff 4'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(5.2, -20.0, 120.0);
        break;
    case pIdFltHpCutoffUpper:
        parameter.symbol = "flt_hp_cutoff_upper";
        parameter.name = "Filters HP Cutoff 4'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(12.2, -20.0, 120.0);
        break;
    case pIdFltLpCutoffLower:
        parameter.symbol = "flt_lp_cutoff_lower";
        parameter.name = "Filters LP Cutoff 8'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(16.4, -20.0, 120.0);
        break;
    case pIdFltHpCutoffLower:
        parameter.symbol = "flt_hp_cutoff_lower";
        parameter.name = "Filters HP Cutoff 8'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(-0.4, -20.0, 120.0);
        break;
    case pIdFltHsCutoffEq:
        parameter.symbol = "flt_hs_cutoff_eq";
        parameter.name = "Filters HS Cutoff 4'";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(24.8, -20.0, 120.0);
        break;
    case pIdFltHsBoostEq:
        parameter.symbol = "flt_hs_boost_eq";
        parameter.name = "Filters HS Boost 4'";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(6.0, -20.0, 20.0);
        break;

    case pIdMixGainUpper:
        parameter.symbol = "mix_gain_upper";
        parameter.name = "Mix Gain 4'";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0.0, -20.0, 0.0);
        break;
    case pIdMixGainLower:
        parameter.symbol = "mix_gain_lower";
        parameter.name = "Mix Gain 8'";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0.0, -20.0, 0.0);
        break;

    case pIdEnvAttack:
        parameter.symbol = "env_attack";
        parameter.name = "Envelope attack";
        parameter.hints = kParameterIsAutomable|kParameterIsLogarithmic;
        parameter.unit = "s";
        parameter.ranges = ParameterRanges(0.1939, 0.01, 10.0);
        break;
    case pIdEnvHold:
        parameter.symbol = "env_hold";
        parameter.name = "Envelope hold";
        parameter.hints = kParameterIsAutomable|kParameterIsLogarithmic;
        parameter.unit = "s";
        parameter.ranges = ParameterRanges(0.01, 0.01, 10.0);
        break;
    case pIdEnvDecay:
        parameter.symbol = "env_decay";
        parameter.name = "Envelope decay";
        parameter.hints = kParameterIsAutomable|kParameterIsLogarithmic;
        parameter.unit = "s";
        parameter.ranges = ParameterRanges(10.0, 0.01, 10.0);
        break;
    case pIdEnvSustain:
        parameter.symbol = "env_sustain";
        parameter.name = "Envelope sustain";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0.0, -60.0, 0.0);
        break;
    case pIdEnvRelease:
        parameter.symbol = "env_release";
        parameter.name = "Envelope release";
        parameter.hints = kParameterIsAutomable|kParameterIsLogarithmic;
        parameter.unit = "s";
        parameter.ranges = ParameterRanges(3.0, 0.01, 10.0);
        break;

    case pIdChoEnabled:
        parameter.symbol = "cho_enabled";
        parameter.name = "Chorus enabled";
        parameter.hints = kParameterIsInteger|kParameterIsBoolean;
        parameter.ranges = ParameterRanges(1.0, 0.0, 1.0);
        break;
    case pIdChoDepth:
        parameter.symbol = "cho_depth";
        parameter.name = "Chorus global depth";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "%";
        parameter.ranges = ParameterRanges(100.0, 0.0, 100.0);
        break;
    case pIdChoRate1:
        parameter.symbol = "cho_rate1";
        parameter.name = "Chorus rate 1";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(5.8346, 1.0, 9.0);
        break;
    case pIdChoDepth1:
        parameter.symbol = "cho_depth1";
        parameter.name = "Chorus depth 1";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "%";
        parameter.ranges = ParameterRanges(30.71, 0.0, 100.0);
        break;
    case pIdChoRate2:
        parameter.symbol = "cho_rate2";
        parameter.name = "Chorus rate 2";
        parameter.hints = kParameterIsAutomable;
        parameter.ranges = ParameterRanges(0.5835, 0.1, 0.9);
        break;
    case pIdChoDepth2:
        parameter.symbol = "cho_depth2";
        parameter.name = "Chorus depth 2";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "%";
        parameter.ranges = ParameterRanges(90.55, 0.0, 100.0);
        break;
    case pIdChoModel:
        parameter.symbol = "cho_model";
        parameter.name = "Chorus model";
        parameter.hints = kParameterIsInteger;
        parameter.ranges = ParameterRanges(1.0, 0.0, 1.0);
        parameter.enumValues.values = pev = new ParameterEnumerationValue[(parameter.enumValues.count = 2)];
        parameter.enumValues.restrictedMode = true;
        pev[0] = {0.0, "Digital delay"};
        pev[1] = {1.0, "Analog bucket-brigade delay"};
        break;

    case pIdMasterGain:
        parameter.symbol = "master_gain";
        parameter.name = "Master Gain";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(3.0, -60.0, +20.0);
        break;

    case pIdPolyphony:
        parameter.symbol = "polyphony";
        parameter.name = "Polyphony";
        parameter.hints = kParameterIsAutomable|kParameterIsInteger;
        parameter.ranges = ParameterRanges(16.0, 1.0, StringSynthDefs::PolyphonyLimit);
        break;

    case pIdOutDetuneUpper:
        parameter.symbol = "osc_current_detune_upper";
        parameter.name = "Oscillator detune 4'";
        parameter.hints = kParameterIsAutomable|kParameterIsOutput;
        parameter.ranges = ParameterRanges(0.0, -1.0, +1.0);
        break;
    case pIdOutDetuneLower:
        parameter.symbol = "osc_current_detune_lower";
        parameter.name = "Oscillator detune 8'";
        parameter.hints = kParameterIsAutomable|kParameterIsOutput;
        parameter.ranges = ParameterRanges(0.0, -1.0, +1.0);
        break;
    case pIdOutChorusPhase1:
        parameter.symbol = "cho_current_phase1";
        parameter.name = "Chorus phase 1";
        parameter.hints = kParameterIsAutomable|kParameterIsOutput;
        parameter.unit = "rad";
        parameter.ranges = ParameterRanges(0.0, 0.0, 2 * M_PI);
        break;
    case pIdOutChorusPhase2:
        parameter.symbol = "cho_current_phase2";
        parameter.name = "Chorus phase 2";
        parameter.hints = kParameterIsAutomable|kParameterIsOutput;
        parameter.unit = "rad";
        parameter.ranges = ParameterRanges(0.0, 0.0, 2 * M_PI);
        break;
    case pIdOutMasterLevel1:
        parameter.symbol = "master_current_level1";
        parameter.name = "Master level 1";
        parameter.hints = kParameterIsAutomable|kParameterIsOutput;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0.0, -100.0, +100.0);
        break;
    case pIdOutMasterLevel2:
        parameter.symbol = "master_current_level2";
        parameter.name = "Master level 2";
        parameter.hints = kParameterIsAutomable|kParameterIsOutput;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0.0, -100.0, +100.0);
        break;

    default:
        DISTRHO_SAFE_ASSERT(false);
        break;
    }
}
