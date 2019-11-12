
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: PwmOscillator.dsp
// Name: PwmOscillator
// Author: 
// Copyright: 
// License: 
// Version: 
//------------------------------------------------------------------------------






#pragma once
#ifndef PwmOscillator_Faust_pp_Gen_HPP_
#define PwmOscillator_Faust_pp_Gen_HPP_

#include <memory>

class PwmOscillator {
public:
    PwmOscillator();
    ~PwmOscillator();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        const float *in0,
        float *out0,
        unsigned count) noexcept;

    enum { NumInputs = 1 };
    enum { NumOutputs = 1 };
    enum { NumActives = 2 };
    enum { NumPassives = 0 };
    enum { NumParameters = 2 };

    enum Parameter {
        p_mod_depth,
        p_mod_frequency,
        
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

    
    float get_mod_depth() const noexcept;
    
    float get_mod_frequency() const noexcept;
    
    
    void set_mod_depth(float value) noexcept;
    
    void set_mod_frequency(float value) noexcept;
    

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;



};




#endif // PwmOscillator_Faust_pp_Gen_HPP_
