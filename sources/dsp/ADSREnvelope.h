#pragma once
#include <cstdint>

class ADSREnvelope {
public:
    struct Settings {
        float attack = 0;
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
        Decay = 1,
        Sustain = 2,
        Release = 3,
    };

private:
    float fSampleTime = 0;

    //
    const ADSREnvelope::Settings *fSettings = nullptr;
    int fCurrentStage = 0;
    float fCurrentLevel = 0;
    int fTrigger = 0;

    //
    float fAttack = 0;
    float fDecay = 0;
    float fRelease = 0;

    float fAttackRate = 0;
    float fDecayRate = 0;
    float fReleaseRate = 0;
};
