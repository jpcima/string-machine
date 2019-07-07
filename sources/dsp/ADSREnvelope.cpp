#include "ADSREnvelope.h"
#include <cmath>

void ADSREnvelope::init(const Settings *settings, double samplingFreq)
{
    fSamplingFreq = samplingFreq;
    fConst1 = (6.90999985f / samplingFreq);

    fTrigger = 0;
    fSettings = settings;

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

void ADSREnvelope::process(float *output0, uint32_t count)
{
    Settings settings = *fSettings;
    float currentLevel = fCurrentLevel;
    int iSlow0 = fTrigger;
    float fSlow1 = float(settings.release);
    float fSlow2 = float(settings.attack);
    int iSlow3 = int((fSamplingFreq * fSlow2));
    float fSlow4 = float(settings.decay);
    float fSlow5 = float(iSlow0);
    float fSlow6 = (fSlow5 * float(settings.sustain));
    for (int i = 0; (i < (int)count); i = (i + 1)) {
        iRec1[0] = (iSlow0 * (iRec1[1] + 1));
        int iTemp0 = (iRec1[0] < iSlow3);
        float fTemp1 = std::exp((0.0f - (fConst1 / (iSlow0?(iTemp0?fSlow2:fSlow4):fSlow1))));
        fRec0[0] = ((fRec0[1] * fTemp1) + ((iSlow0?(iTemp0?fSlow5:fSlow6):0.0f) * (1.0f - fTemp1)));
        currentLevel = float(fRec0[0]);
        output0[i] = currentLevel;
        iRec1[1] = iRec1[0];
        fRec0[1] = fRec0[0];
    }
    fCurrentLevel = currentLevel;
}
