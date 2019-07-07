#pragma once
#include <cmath>

class SmoothFilter {
public:
    void init(double sampleRate);
    void setTime(double t);
    float process(float input);

private:
    float fSampleTime;
    float fPole;
    float fMemory;
};

inline void SmoothFilter::init(double sampleRate)
{
    fSampleTime = 1.0f / sampleRate;
    fPole = 0.0f;
    fMemory = 0.0f;
}

inline void SmoothFilter::setTime(double t)
{
    fPole = std::exp(- fSampleTime / t);
}

inline float SmoothFilter::process(float input)
{
    float pole = fPole;
    return (fMemory = pole * fMemory + (1.0f - pole) * input);
}
