#include "ChorusShared.hpp"

void InitParameter(uint32_t index, Parameter &parameter)
{
    ParameterEnumerationValue *pev;

    switch (index) {
    case pIdBypass:
        parameter.designation = kParameterDesignationBypass;
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
        parameter.ranges = ParameterRanges(5.8346, 3.0, 9.0);
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
        parameter.ranges = ParameterRanges(0.5835, 0.3, 0.9);
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

    case pIdWetGain:
        parameter.symbol = "wet_gain";
        parameter.name = "Wet gain";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(0.0, -60.0, +20.0);
        break;
    case pIdDryGain:
        parameter.symbol = "dry_gain";
        parameter.name = "Dry gain";
        parameter.hints = kParameterIsAutomable;
        parameter.unit = "dB";
        parameter.ranges = ParameterRanges(-60.0, -60.0, +20.0);
        break;

    default:
        DISTRHO_SAFE_ASSERT(false);
        break;
    }
}

