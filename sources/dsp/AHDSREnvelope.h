#pragma once
#include <cstdint>

class AHDSREnvelope {
public:
    struct Settings {
        float attack = 0;
        float hold = 0;
        float decay = 0;
        float sustain = 0;
        float release = 0;
    };

    void init(const Settings *settings, double sampleRate);

    void clear();
    void process(float *output, uint32_t sampleCount);

    void trigger();
    void release();
    bool isTriggered() const { return fTrigger != 0; }

    float getCurrentLevel() const { return fCurrentLevel; }

private:
    void updateRates();

private:
    enum {
        Attack = 0,
        Hold = 1,
        Decay = 2,
        Sustain = 3,
        Release = 4,
    };

private:
    float fSampleRate = 0;

    //
    const AHDSREnvelope::Settings *fSettings = nullptr;
    int fCurrentStage = 0;
    float fCurrentLevel = 0;
    unsigned fCurrentFrames = 0;
    int fTrigger = 0;

    //
    float fAttack = 0;
    float fHold = 0;
    float fDecay = 0;
    float fRelease = 0;

    float fAttackRate = 0;
    unsigned fHoldFrames = 0;
    float fDecayRate = 0;
    float fReleaseRate = 0;
};
