#include "OnePoleFilter.h"

std::complex<double> OnePoleLPF::getResponse(double frequency) const
{
    double p = fPole;
    std::complex<double> z = std::polar(1.0, 2.0 * M_PI * frequency * fSampleTime);
    std::complex<double> z1 = 1.0 / z;
    std::complex<double> h = (1.0 - p) / (1.0 - p * z1);
    return h;
}

std::complex<double> OnePoleHPF::getResponse(double frequency) const
{
    double p = fPole;
    std::complex<double> z = std::polar(1.0, 2.0 * M_PI * frequency * fSampleTime);
    std::complex<double> z1 = 1.0 / z;
    std::complex<double> h = ((0.5 * (1.0 + p)) - (0.5 * (1.0 + p)) * z1) / (1.0 - p * z1);
    return h;
}
