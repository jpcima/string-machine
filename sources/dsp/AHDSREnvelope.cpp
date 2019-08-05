#include "AHDSREnvelope.h"
#include <cmath>

void AHDSREnvelope::init(const Settings *settings, double sampleRate)
{
    fSampleRate = sampleRate;
    fSettings = settings;
    fTrigger = 0;

    updateRates();
    clear();
}

void AHDSREnvelope::clear()
{
    fCurrentStage = Release;
    fCurrentLevel = 0.0f;
    fTrigger = 0;
}

void AHDSREnvelope::trigger()
{
    fCurrentStage = Attack;
    fTrigger = 1;
}

void AHDSREnvelope::release()
{
    fCurrentStage = Release;
    fTrigger = 0;
}

void AHDSREnvelope::process(float *output, uint32_t count)
{
    updateRates();

    float ar = fAttackRate;
    unsigned hf = fHoldFrames;
    float dr = fDecayRate;
    float sl = std::pow(10.0f, 0.05f * fSettings->sustain);
    float rr = fReleaseRate;

    int stage = fCurrentStage;
    float level = fCurrentLevel;
    unsigned counter = fCurrentFrames;

    for (uint32_t i = 0; i < count; ++i) {
        switch (stage) {
        case Attack:
            if (level < 1) {
                const float target = 1.1; // set higher so 1 is reached in reasonable time
                level = ar * level + (1 - ar) * target;
                break;
            }
            stage = Hold;
            counter = 0;
            // fall through
        case Hold:
            if (counter++ < hf)
                break;
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
    fCurrentFrames = counter;
}

void AHDSREnvelope::updateRates()
{
    const Settings settings = *fSettings;
    float sampleRate = fSampleRate;
    float sampleTime = 1 / sampleRate;

    const float kt = 1.0 / 2.2; // ~ 90% time constant

    if (fAttack != settings.attack) {
        fAttack = settings.attack;
        fAttackRate = 0.0;
        if (settings.attack > 0)
            fAttackRate = std::exp(-sampleTime / (kt * settings.attack));
    }
    if (fHold != settings.hold) {
        fHold = settings.hold;
        fHoldFrames = 0;
        if (settings.hold > 0)
            fHoldFrames = (unsigned)(0.5 + sampleRate * settings.hold);
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
