#pragma once
#include <complex>
#include <cmath>

class OnePoleLPF {
public:
    void init(double sampleRate);
    void setCutoff(double frequency);
    double process(double input);
    std::complex<double> getResponse(double frequency) const;
    void clear();

private:
    double fPole = 0;
    double fDelayOutput = 0;
    double fSampleTime = 0;
};

inline void OnePoleLPF::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;
}

inline void OnePoleLPF::setCutoff(double frequency)
{
    fPole = std::exp(-2.0 * M_PI * frequency * fSampleTime);
}

inline double OnePoleLPF::process(double input)
{
    double p = fPole;
    double output = input * (1 - p) + fDelayOutput * p;
    fDelayOutput = output;
    return output;
}

inline void OnePoleLPF::clear()
{
    fDelayOutput = 0.0;
}

///
class OnePoleHPF {
public:
    void init(double sampleRate);
    void setCutoff(double frequency);
    double process(double input);
    std::complex<double> getResponse(double frequency) const;
    void clear();

private:
    double fPole = 0;
    double fDelayInput = 0;
    double fDelayOutput = 0;
    double fSampleTime = 0;
};

inline void OnePoleHPF::init(double sampleRate)
{
    fSampleTime = 1.0 / sampleRate;
}

inline void OnePoleHPF::setCutoff(double frequency)
{
    fPole = std::exp(-2.0 * M_PI * frequency * fSampleTime);
}

inline double OnePoleHPF::process(double input)
{
    double p = fPole;
    double output = input * (0.5 * (1 + p)) + fDelayInput * - (0.5 * (1 + p)) + fDelayOutput * p;
    fDelayInput = input;
    fDelayOutput = output;
    return output;
}

inline void OnePoleHPF::clear()
{
    fDelayInput = 0.0;
    fDelayOutput = 0.0;
}
