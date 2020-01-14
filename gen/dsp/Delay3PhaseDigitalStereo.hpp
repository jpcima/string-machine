
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: Delay3PhaseDigital.dsp
// Name: Delay3PhaseDigital
// Author: 
// Copyright: 
// License: 
// Version: 
//------------------------------------------------------------------------------






#pragma once
#ifndef Delay3PhaseDigitalStereo_Faust_pp_Gen_HPP_
#define Delay3PhaseDigitalStereo_Faust_pp_Gen_HPP_

#include <memory>

class Delay3PhaseDigitalStereo {
public:
    Delay3PhaseDigitalStereo();
    ~Delay3PhaseDigitalStereo();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        const float *in0,const float *in1,const float *in2,const float *in3,const float *in4,
        float *out0,float *out1,float *out2,float *out3,float *out4,float *out5,
        unsigned count) noexcept;

    enum { NumInputs = 5 };
    enum { NumOutputs = 6 };
    enum { NumActives = 0 };
    enum { NumPassives = 0 };
    enum { NumParameters = 0 };

    enum Parameter {
        
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

    
    

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;



};




#endif // Delay3PhaseDigitalStereo_Faust_pp_Gen_HPP_
