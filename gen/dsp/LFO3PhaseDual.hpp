//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: LFO3PhaseDual.dsp
// Name: LFO3PhaseDual
// Author: 
// Copyright: 
// License: 
// Version: 
//------------------------------------------------------------------------------

#pragma once
#ifndef LFO3PhaseDual_Faust_pp_Gen_HPP_
#define LFO3PhaseDual_Faust_pp_Gen_HPP_

#include <memory>

class LFO3PhaseDual {
public:
    LFO3PhaseDual();
    ~LFO3PhaseDual();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        
        float *out0,float *out1,float *out2,
        unsigned count) noexcept;

    enum { NumInputs = 0 };
    enum { NumOutputs = 3 };
    enum { NumParameters = 5 };
    enum { NumPassives = 2 };

    enum Parameter {
        p_rate1,
        p_depth1,
        p_rate2,
        p_depth2,
        p_globaldepth,
        
        p_phase1,
        p_phase2,
        
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

    
    float get_rate1() const noexcept;
    void set_rate1(float value) noexcept;
    
    float get_depth1() const noexcept;
    void set_depth1(float value) noexcept;
    
    float get_rate2() const noexcept;
    void set_rate2(float value) noexcept;
    
    float get_depth2() const noexcept;
    void set_depth2(float value) noexcept;
    
    float get_globaldepth() const noexcept;
    void set_globaldepth(float value) noexcept;
    

    float get_passive(unsigned index) const noexcept;

    
    float get_phase1() const noexcept;
    void set_phase1(float value) noexcept;
    
    float get_phase2() const noexcept;
    void set_phase2(float value) noexcept;
    

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;
};

#endif // LFO3PhaseDual_Faust_pp_Gen_HPP_
