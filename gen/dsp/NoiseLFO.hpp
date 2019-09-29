//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: NoiseLFO.dsp
// Name: NoiseLFO
// Author: 
// Copyright: 
// License: 
// Version: 
//------------------------------------------------------------------------------

#pragma once
#ifndef NoiseLFO_Faust_pp_Gen_HPP_
#define NoiseLFO_Faust_pp_Gen_HPP_

#include <memory>

class NoiseLFO {
public:
    NoiseLFO();
    ~NoiseLFO();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        
        float *out0,
        unsigned count) noexcept;

    enum { NumInputs = 0 };
    enum { NumOutputs = 1 };
    enum { NumParameters = 1 };
    enum { NumPassives = 0 };

    enum Parameter {
        p_frequency,
        
        
    };

    struct ParameterRange {
        float init;
        float min;
        float max;
    };

    static const char *parameter_label(unsigned index) noexcept;
    static const char *parameter_short_label(unsigned index) noexcept;
    static const char *parameter_symbol(unsigned index) noexcept;
    static const char *parameter_unit(unsigned index) noexcept;
    static const ParameterRange *parameter_range(unsigned index) noexcept;
    static bool parameter_is_trigger(unsigned index) noexcept;
    static bool parameter_is_boolean(unsigned index) noexcept;
    static bool parameter_is_integer(unsigned index) noexcept;
    static bool parameter_is_logarithmic(unsigned index) noexcept;

    float get_parameter(unsigned index) const noexcept;
    void set_parameter(unsigned index, float value) noexcept;

    
    float get_frequency() const noexcept;
    void set_frequency(float value) noexcept;
    

    float get_passive(unsigned index) const noexcept;

    

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;
};

#endif // NoiseLFO_Faust_pp_Gen_HPP_
