#include "ADSREnvelope.h"
#include <cmath>

void ADSREnvelope::init(const Settings *settings, double sampleRate)
{
    fSettings = settings;
    fTrigger = 0;

    fConst0 = float(sampleRate);
    fConst1 = (6.90999985f / fConst0);

    clear();
}

void ADSREnvelope::clear()
{
    fCurrentLevel = 0.0f;

    for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
        iRec1[l0] = 0;
    }
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
        fRec0[l1] = 0.0f;
    }
}

void ADSREnvelope::process(float *output, uint32_t count)
{
    const Settings settings = *fSettings;
    float currentLevel = fCurrentLevel;

    float* output0 = output;
    int iSlow0 = fTrigger;
    float fSlow1 = float(settings.release);
    float fSlow2 = float(settings.attack);
    int iSlow3 = int((fConst0 * fSlow2));
    float fSlow4 = float(settings.decay);
    float fSlow5 = float(iSlow0);
    float fSlow6 = (fSlow5 * std::pow(10.0f, (0.0500000007f * float(settings.sustain))));
    for (int i = 0; (i < count); i = (i + 1)) {
        iRec1[0] = (iSlow0 * (iRec1[1] + 1));
        int iTemp0 = (iRec1[0] < iSlow3);
        float fTemp1 = std::exp((0.0f - (fConst1 / (iSlow0?(iTemp0?fSlow2:fSlow4):fSlow1))));
        fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow0?(iTemp0?fSlow5:fSlow6):0.0f) * (1.0f - fTemp1)));
        output0[i] = currentLevel = float(fRec0[0]);
        iRec1[1] = iRec1[0];
        fRec0[1] = fRec0[0];
    }

    fCurrentLevel = currentLevel;
}

/**
import("stdfaust.lib");

process = en.adsre(attack, decay, sustain, release, trigger) with {
  attack = hslider("[1] Attack [unit:s]", 0., 0., 10.0, 0.01);
  decay = hslider("[2] Decay [unit:s]", 0., 0., 10.0, 0.01);
  sustain = hslider("[3] Sustain [unit:dB]", 0, -40.0, 0.0, 1.0) : ba.db2linear;
  release = hslider("[4] Release [unit:s]", 0., 0., 10.0, 0.01);
  trigger = checkbox("[5] Trigger");
};
 */
