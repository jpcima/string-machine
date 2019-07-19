#pragma once

class TriangleLFO {
public:
    void init(double sampleRate);

    void setFrequency(float frequency);
    float process();

private:
    float fPhase = 0;
    float fPhaseIncrement = 0;
    float fSampleTime = 0;
};

inline void TriangleLFO::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;
    fPhaseIncrement = 0;
    fPhase = 0;
}

inline void TriangleLFO::setFrequency(float frequency)
{
    fPhaseIncrement = frequency * fSampleTime;
}

inline float TriangleLFO::process()
{
    float phase = fPhase;
    float ramp = 2.0f * phase;
    float output = (phase < 0.5f) ? ramp : (2.0f - ramp);
    phase += fPhaseIncrement;
    phase -= (int)phase;
    fPhase = phase;
    return output;
}
