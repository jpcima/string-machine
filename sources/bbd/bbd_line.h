#pragma once
#include "bbd_filter.h"
#include <algorithm>
#include <vector>
#include <array>
#include <complex>
typedef std::complex<double> cdouble;

template <unsigned Channels = 1>
class BBD_Line {
public:
    void setup(double fs, unsigned ns, const BBD_Filter_Spec &fsin, const BBD_Filter_Spec &fsout);
    void set_delay_size(unsigned ns);
    void clear();
    void process(unsigned n, const float *const inputs[Channels], float *const outputs[Channels], const float *clock);
    void process(unsigned n, float *const inouts[Channels], const float *clock);

    const BBD_Filter_Coef &filter_in() const noexcept { return *fin_; }
    const BBD_Filter_Coef &filter_out() const noexcept { return *fout_; }

    static inline double hz_rate_for_delay(double delay_time, unsigned stages)
        { return 2 * stages / delay_time; }
    static inline double delay_for_hz_rate(double rate, unsigned stages)
        { return 2 * stages / rate; }

private:
    unsigned ns_; // delay size
    std::vector<float> mem_; // delay memory
    unsigned imem_; // delay memory index
    double pclk_; // clock phase
    unsigned ptick_; // clock tick counter
    const BBD_Filter_Coef *fin_;
    const BBD_Filter_Coef *fout_;
    std::array<double, Channels> ybbd1_;

    enum { Mmax = 8 }; // the maximum filter order
    std::array<cdouble, Mmax> Xin_[Channels];
    std::array<cdouble, Mmax> Xout1_[Channels]; // sample memory of output filter
};
