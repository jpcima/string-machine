#pragma once
#include <cstdint>

class ADSREnvelope {
public:
    struct Settings {
        float attack;
        float decay;
        float sustain;
        float release;
    };

    void init(const Settings *settings, double sampleRate);

    void clear();
    void process(float *output, uint32_t sampleCount);

    void trigger() { fTrigger = 1; }
    void release() { fTrigger = 0; }
    bool isTriggered() const { return fTrigger != 0; }

    float getCurrentLevel() const { return fCurrentLevel; }

    enum ADSRState {
        IDLE,
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE
    };

private:
    const ADSREnvelope::Settings *fSettings;
    int fSamplingFreq;
    float fConst1;
    int fTrigger;
    float fCurrentLevel;
    int iRec1[2];
    float fRec0[2];
};
