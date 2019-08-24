//-----------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: StringFiltersHighshelf.dsp
// Name: StringFiltersHighshelf
// Author: 
// Copyright: 
// License: 
// Version: 
//-----------------------------------------------------------------------------

#pragma once
#ifndef StringFiltersHighshelf_Faust_pp_Gen_HPP_
#define StringFiltersHighshelf_Faust_pp_Gen_HPP_

#if __cplusplus < 201103L
#   define noexcept
#endif

class StringFiltersHighshelfDsp;

class StringFiltersHighshelf {
public:
    StringFiltersHighshelf();
    ~StringFiltersHighshelf();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        const float *in0,
        float *out0,
        unsigned count) noexcept;

    enum { inputs = 1 };
    enum { outputs = 1 };
    enum { parameters = 2 };

    enum Parameter {
        p_cutoff,
        p_gain,
        
    };


    struct ParameterRange {
        float init;
        float min;
        float max;
    };

    static const char *parameter_label(unsigned index) noexcept;
    static const char *parameter_symbol(unsigned index) noexcept;
    static const char *parameter_unit(unsigned index) noexcept;
    static const ParameterRange *parameter_range(unsigned index) noexcept;
    static bool parameter_is_trigger(unsigned index) noexcept;
    static bool parameter_is_boolean(unsigned index) noexcept;
    static bool parameter_is_integer(unsigned index) noexcept;
    static bool parameter_is_logarithmic(unsigned index) noexcept;

    float get_parameter(unsigned index) const noexcept;
    void set_parameter(unsigned index, float value) noexcept;

    
    float get_cutoff() const noexcept;
    void set_cutoff(float value) noexcept;
    
    float get_gain() const noexcept;
    void set_gain(float value) noexcept;
    

private:
    StringFiltersHighshelfDsp *fDsp;

private:
    StringFiltersHighshelf(const StringFiltersHighshelf &other);
    StringFiltersHighshelf &operator=(const StringFiltersHighshelf &other);

#if __cplusplus >= 201103L
public:
    StringFiltersHighshelf(StringFiltersHighshelf &&other) noexcept;
    StringFiltersHighshelf &operator=(StringFiltersHighshelf &&other) noexcept;
#endif
};

#endif // StringFiltersHighshelf_Faust_pp_Gen_HPP_
