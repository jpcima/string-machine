#pragma once
#include "bbd_filter.h"
#include <algorithm>
#include <memory>
#include <complex>
typedef std::complex<double> cdouble;

class BBD_Line {
public:
    void setup(double fs, unsigned ns, const BBD_Filter_Spec &fsin, const BBD_Filter_Spec &fsout);
    void nstages(unsigned ns);
    void clear();
    void process(unsigned n, const float *input, float *output, const float *clock);

    unsigned nstages() const noexcept { return ns_; }
    const BBD_Filter_Coef &filter_in() const noexcept { return *fin_; }
    const BBD_Filter_Coef &filter_out() const noexcept { return *fout_; }

    static inline double hz_rate_for_delay(double delay_time, unsigned stages)
        { return 2 * stages / delay_time; }
    static inline double delay_for_hz_rate(double rate, unsigned stages)
        { return 2 * stages / rate; }

    static constexpr unsigned supported_nstages_count = 5;
    static constexpr unsigned nstages_min = 512;
    static constexpr unsigned nstages_max = nstages_min << (supported_nstages_count - 1);

private:
    unsigned ns_ = 0; // delay size
    std::unique_ptr<float[]> mem_; // delay memory
    unsigned imem_ = 0; // delay memory index
    double pclk_ = 0; // clock phase
    unsigned ptick_ = 0; // clock tick counter
    double ybbd_old_ = 0;
    const BBD_Filter_Coef *fin_ = nullptr;
    const BBD_Filter_Coef *fout_ = nullptr;
    std::unique_ptr<cdouble[]> Xin_;
    std::unique_ptr<cdouble[]> Xout_;
    std::unique_ptr<cdouble[]> Gin_;
    std::unique_ptr<cdouble[]> Gout_;
};
