#include "bbd_line.h"
#include <algorithm>
#include <cassert>

static constexpr unsigned interp_size = 128;

template <unsigned Channels>
void BBD_Line<Channels>::setup(double fs, unsigned ns, const BBD_Filter_Spec &fsin, const BBD_Filter_Spec &fsout)
{
    mem_.reserve(8192 * Channels);

    const BBD_Filter_Coef &fin = BBD::compute_filter_cached(fs, interp_size, fsin);
    const BBD_Filter_Coef &fout = BBD::compute_filter_cached(fs, interp_size, fsout);
    fin_ = &fin;
    fout_ = &fout;

    assert(fin.M <= Mmax);
    assert(fout.M <= Mmax);

    set_delay_size(ns);
    clear();
}

template <unsigned Channels>
void BBD_Line<Channels>::set_delay_size(unsigned ns)
{
    mem_.clear();
    mem_.resize(ns * Channels);
    imem_ = 0;
    ns_ = ns;
}

template <unsigned Channels>
void BBD_Line<Channels>::clear()
{
    std::fill(mem_.begin(), mem_.end(), 0);
    imem_ = 0;
    pclk_ = 0;
    ptick_ = 0;
    ybbd1_.fill(0);
    for (unsigned c = 0; c < Channels; ++c) {
        Xin_[c].fill(0);
        Xout1_[c].fill(0);
    }
}

template <unsigned Channels>
void BBD_Line<Channels>::process(unsigned n, const float *const inputs[Channels], float *const outputs[Channels], const float *clock)
{
    unsigned ns = ns_;
    float *mem = mem_.data();
    unsigned imem = imem_;
    double pclk = pclk_;
    unsigned ptick = ptick_;
    std::array<double, Channels> ybbd1 = ybbd1_;

    const BBD_Filter_Coef &fin = *fin_;
    const BBD_Filter_Coef &fout = *fout_;
    unsigned Min = fin.M;
    unsigned Mout = fout.M;
    const cdouble *const Pin = fin.P.get();
    const cdouble *const Pout = fout.P.get();

    for (unsigned i = 0; i < n; ++i) {
        std::array<cdouble, Mmax> Xout_[Channels] = {};

        double fclk = clock[i];
        if (fclk > 0) {
            double pclk_old = pclk;
            pclk += fclk;

            unsigned tick_count = (unsigned)pclk;
            pclk -= tick_count;

            for (unsigned tick = 0; tick < tick_count; ++tick) {
                double d = (1 - pclk_old + tick) * (1 / fclk);
                d -= (unsigned)d;

                if ((ptick & 1) == 0) {
                    cdouble Gin[Mmax];
                    fin.interpolate_G(d, Gin);

                    for (unsigned c = 0; c < Channels; ++c) {
                        const std::array<cdouble, Mmax> &Xin = Xin_[c];
                        cdouble s = 0;
                        for (unsigned m = 0; m < Min; ++m)
                            s += Gin[m] * Xin[m];
                        mem[imem * Channels + c] = s.real();
                    }

                    imem = ((imem + 1) < ns) ? (imem + 1) : 0;
                }
                else {
                    cdouble Gout[Mmax];
                    fout.interpolate_G(d, Gout);

                    for (unsigned c = 0; c < Channels; ++c) {
                        std::array<cdouble, Mmax> &Xout = Xout_[c];
                        double ybbd = mem[imem * Channels + c];
                        double delta = ybbd - ybbd1[c];
                        ybbd1[c] = ybbd;
                        for (unsigned m = 0; m < Mout; ++m)
                            Xout[m] += Gout[m] * delta;
                    }
                }

                ++ptick;
            }
        }

        for (unsigned c = 0; c < Channels; ++c) {
            const float *input = inputs[c];
            float *output = outputs[c];

            std::array<cdouble, Mmax> &Xin = Xin_[c];
            std::array<cdouble, Mmax> &Xout1 = Xout1_[c];
            const std::array<cdouble, Mmax> &Xout = Xout_[c];

            for (unsigned m = 0; m < Min; ++m)
                Xin[m] = Pin[m] * Xin[m] + cdouble(input[i]);

            cdouble y = fout.H * ybbd1[c];
            for (unsigned m = 0; m < Mout; ++m) {
                cdouble xout = Pout[m] * Xout1[m] + Xout[m];
                Xout1[m] = xout;
                y += xout;
            }

            output[i] = y.real();
        }
    }

    imem_ = imem;
    pclk_ = pclk;
    ptick_ = ptick;
    ybbd1_ = ybbd1;
}

template <unsigned Channels>
void BBD_Line<Channels>::process(unsigned n, float *const inouts[Channels], const float *clock)
{
    process(n, inouts, inouts, clock);
}

template class BBD_Line<1>;
template class BBD_Line<2>;
