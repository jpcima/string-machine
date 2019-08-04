#include "ADSREnvelope.h"
#include <cmath>

void ADSREnvelope::init(const Settings *settings, double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;
    fSettings = settings;
    fTrigger = 0;

    updateRates();
    clear();
}

void ADSREnvelope::clear()
{
    fCurrentStage = Release;
    fCurrentLevel = 0.0f;
    fTrigger = 0;
}

void ADSREnvelope::trigger()
{
    fCurrentStage = Attack;
    fTrigger = 1;
}

void ADSREnvelope::release()
{
    fCurrentStage = Release;
    fTrigger = 0;
}

void ADSREnvelope::process(float *output, uint32_t count)
{
    updateRates();

    float ar = fAttackRate;
    float dr = fDecayRate;
    float sl = std::pow(10.0f, 0.05f * fSettings->sustain);
    float rr = fReleaseRate;

    int stage = fCurrentStage;
    float level = fCurrentLevel;

    for (uint32_t i = 0; i < count; ++i) {
        switch (stage) {
        case Attack:
            if (level < 1) {
                const float target = 1.1; // set higher so 1 is reached in reasonable time
                level = ar * level + (1 - ar) * target;
                break;
            }
            stage = Decay;
            // fall through
        case Decay:
            if (level > sl) {
                level = dr * level + (1 - dr) * sl;
                break;
            }
            stage = Sustain;
            // fall through
        case Sustain:
            level = dr * level + (1 - dr) * sl;
            break;
        case Release:
            level = rr * level;
            break;
        }

        output[i] = level;
    }

    fCurrentStage = stage;
    fCurrentLevel = level;
}

void ADSREnvelope::updateRates()
{
    const Settings settings = *fSettings;
    float sampleTime = fSampleTime;

    const float kt = 1.0 / 2.2; // ~ 90% time constant

    if (fAttack != settings.attack) {
        fAttack = settings.attack;
        fAttackRate = 0.0;
        if (settings.attack > 0)
            fAttackRate = std::exp(-sampleTime / (kt * settings.attack));
    }
    if (fDecay != settings.decay) {
        fDecay = settings.decay;
        fDecayRate = 0.0;
        if (settings.decay > 0)
            fDecayRate = std::exp(-sampleTime / (kt * settings.decay));
    }
    if (fRelease != settings.release) {
        fRelease = settings.release;
        fReleaseRate = 0.0;
        if (settings.release > 0)
            fReleaseRate = std::exp(-sampleTime / (kt * settings.release));
    }
}
