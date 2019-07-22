#pragma once
#include "bbd_filter.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <complex>
typedef std::complex<double> cdouble;

class BBD_Line {
public:
    void setup(double fs, unsigned ns, const BBD_Filter_Spec &fsin, const BBD_Filter_Spec &fsout);
    void set_delay_size(unsigned ns);
    void clear();
    void process(unsigned n, const float *input, float *output, const float *clock);
    void process(unsigned n, float *inout, const float *clock);

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
    double ybbd_old_;
    const BBD_Filter_Coef *fin_;
    const BBD_Filter_Coef *fout_;
    std::unique_ptr<cdouble[]> Xin_;
    std::unique_ptr<cdouble[]> Xout_;
    std::unique_ptr<cdouble[]> Xout_mem_; // sample memory of output filter
    std::unique_ptr<cdouble[]> Gin_;
    std::unique_ptr<cdouble[]> Gout_;
};
