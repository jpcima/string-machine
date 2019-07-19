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

    void trigger() { fTrigger = 1; }
    void release() { fTrigger = 0; }
    bool isTriggered() const { return fTrigger != 0; }

    float getCurrentLevel() const { return fCurrentLevel; }

private:
    const ADSREnvelope::Settings *fSettings = nullptr;
    float fCurrentLevel = 0;
    int fTrigger = 0;

    float fConst0 = 0;
    float fConst1 = 0;
    float fRec0[2] = {};
    int iRec1[2] = {};
};
