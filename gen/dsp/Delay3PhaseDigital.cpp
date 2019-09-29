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

#include "Delay3PhaseDigital.hpp"
#include <cmath>

class Delay3PhaseDigital::BasicDsp {
public:
    virtual ~BasicDsp() {}
};

//------------------------------------------------------------------------------
// Begin the Faust code section

namespace {

template <class T> inline T min(T a, T b) { return (a < b) ? a : b; }
template <class T> inline T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    // dummy
    void declare(...) {}
};

class UI {
public:
    // dummy
    void openHorizontalBox(...) {}
    void openVerticalBox(...) {}
    void closeBox(...) {}
    void declare(...) {}
    void addButton(...) {}
    void addCheckButton(...) {}
    void addVerticalSlider(...) {}
    void addHorizontalSlider(...) {}
    void addVerticalBargraph(...) {}
};

typedef Delay3PhaseDigital::BasicDsp dsp;

} // namespace

#define FAUSTPP_VIRTUAL // do not declare any methods virtual
#define FAUSTPP_PRIVATE public // do not hide any members
#define FAUSTPP_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTPP_BEGIN_NAMESPACE namespace {
#define FAUSTPP_END_NAMESPACE }

#if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifndef FAUSTPP_PRIVATE
#   define FAUSTPP_PRIVATE private
#endif
#ifndef FAUSTPP_PROTECTED
#   define FAUSTPP_PROTECTED protected
#endif
#ifndef FAUSTPP_VIRTUAL
#   define FAUSTPP_VIRTUAL virtual
#endif

#ifndef FAUSTPP_BEGIN_NAMESPACE
#   define FAUSTPP_BEGIN_NAMESPACE
#endif
#ifndef FAUSTPP_END_NAMESPACE
#   define FAUSTPP_END_NAMESPACE
#endif

FAUSTPP_BEGIN_NAMESPACE

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

FAUSTPP_END_NAMESPACE
#include <algorithm>
#include <cmath>
#include <math.h>
FAUSTPP_BEGIN_NAMESPACE


#ifndef FAUSTCLASS 
#define FAUSTCLASS Delay3PhaseDigitalDsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Delay3PhaseDigitalDsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec2[3];
	float fRec1[3];
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec0[3];
	int IOTA;
	float fVec0[16384];
	int iConst18;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("filename", "Delay3PhaseDigital");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("maxmsp.lib/author", "GRAME");
		m->declare("maxmsp.lib/copyright", "GRAME");
		m->declare("maxmsp.lib/license", "LGPL");
		m->declare("maxmsp.lib/name", "MaxMSP compatibility Library");
		m->declare("maxmsp.lib/version", "1.1");
		m->declare("name", "Delay3PhaseDigital");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 4;
		
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 3;
		
	}
	FAUSTPP_VIRTUAL int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	FAUSTPP_VIRTUAL int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (36137.0f / fConst0);
		fConst2 = std::cos(fConst1);
		fConst3 = (0.460000008f * std::sin(fConst1));
		fConst4 = (fConst3 + 1.0f);
		fConst5 = ((1.0f - fConst2) / fConst4);
		fConst6 = (60076.8906f / fConst0);
		fConst7 = std::cos(fConst6);
		fConst8 = (1.0f - fConst7);
		fConst9 = (0.340000004f * std::sin(fConst6));
		fConst10 = (fConst9 + 1.0f);
		fConst11 = (fConst8 / fConst10);
		fConst12 = (1.0f / fConst10);
		fConst13 = (0.0f - (2.0f * fConst7));
		fConst14 = (1.0f - fConst9);
		fConst15 = (1.0f / fConst4);
		fConst16 = (0.0f - (2.0f * fConst2));
		fConst17 = (1.0f - fConst3);
		iConst18 = int(std::ceil((0.0500000007f * fConst0)));
		
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
			
		}
		IOTA = 0;
		for (int l3 = 0; (l3 < 16384); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
			
		}
		
	}
	
	FAUSTPP_VIRTUAL void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	FAUSTPP_VIRTUAL void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTPP_VIRTUAL Delay3PhaseDigitalDsp* clone() {
		return new Delay3PhaseDigitalDsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Delay3PhaseDigital");
		ui_interface->closeBox();
		
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec2[0] = (float(input0[i]) - (fConst12 * ((fConst13 * fRec2[1]) + (fConst14 * fRec2[2]))));
			fRec1[0] = (0.0f - (fConst12 * (((fConst13 * fRec1[1]) + (fConst14 * fRec1[2])) - (fConst8 * ((fRec2[1] + (0.5f * fRec2[0])) + (0.5f * fRec2[2]))))));
			fRec0[0] = ((fConst11 * ((fRec1[1] + (0.5f * fRec1[0])) + (0.5f * fRec1[2]))) - (fConst15 * ((fConst16 * fRec0[1]) + (fConst17 * fRec0[2]))));
			float fTemp0 = ((fRec0[1] + (0.5f * fRec0[0])) + (0.5f * fRec0[2]));
			fVec0[(IOTA & 16383)] = fTemp0;
			float fTemp1 = (fConst0 * ((0.00100000005f * float(input1[i])) + 0.00499999989f));
			float fTemp2 = (fTemp1 + 4.99999987e-06f);
			int iTemp3 = int(fTemp2);
			float fTemp4 = std::floor(fTemp2);
			float fTemp5 = ((fVec0[((IOTA - std::min<int>(iConst18, std::max<int>(0, iTemp3))) & 16383)] * (0.0f - (fTemp1 + (-1.0f - fTemp4)))) + ((fTemp1 - fTemp4) * fVec0[((IOTA - std::min<int>(iConst18, std::max<int>(0, (iTemp3 + 1)))) & 16383)]));
			float fTemp6 = (fConst0 * ((0.00100000005f * float(input2[i])) + 0.00499999989f));
			float fTemp7 = (fTemp6 + 4.99999987e-06f);
			int iTemp8 = int(fTemp7);
			float fTemp9 = std::floor(fTemp7);
			float fTemp10 = ((fVec0[((IOTA - std::min<int>(iConst18, std::max<int>(0, iTemp8))) & 16383)] * (0.0f - (fTemp6 + (-1.0f - fTemp9)))) + ((fTemp6 - fTemp9) * fVec0[((IOTA - std::min<int>(iConst18, std::max<int>(0, (iTemp8 + 1)))) & 16383)]));
			float fTemp11 = (fTemp5 + fTemp10);
			float fTemp12 = (fConst0 * ((0.00100000005f * float(input3[i])) + 0.00499999989f));
			float fTemp13 = (fTemp12 + 4.99999987e-06f);
			int iTemp14 = int(fTemp13);
			float fTemp15 = std::floor(fTemp13);
			float fTemp16 = ((fVec0[((IOTA - std::min<int>(iConst18, std::max<int>(0, iTemp14))) & 16383)] * (0.0f - (fTemp12 + (-1.0f - fTemp15)))) + ((fTemp12 - fTemp15) * fVec0[((IOTA - std::min<int>(iConst18, std::max<int>(0, (iTemp14 + 1)))) & 16383)]));
			output0[i] = FAUSTFLOAT((fConst5 * (fTemp11 - fTemp16)));
			output1[i] = FAUSTFLOAT((0.0f - (fConst5 * (fTemp16 - (fTemp5 - fTemp10)))));
			output2[i] = FAUSTFLOAT((fConst5 * (fTemp11 + fTemp16)));
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			IOTA = (IOTA + 1);
			
		}
		
	}

};
FAUSTPP_END_NAMESPACE


#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif


//------------------------------------------------------------------------------
// End the Faust code section

Delay3PhaseDigital::Delay3PhaseDigital()
    : fDsp(new Delay3PhaseDigitalDsp)
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    dsp.instanceResetUserInterface();
}

Delay3PhaseDigital::~Delay3PhaseDigital()
{
}

void Delay3PhaseDigital::init(float sample_rate)
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    dsp.instanceClear();
}

void Delay3PhaseDigital::clear() noexcept
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    dsp.instanceClear();
}

void Delay3PhaseDigital::process(
    const float *in0,const float *in1,const float *in2,const float *in3,
    float *out0,float *out1,float *out2,
    unsigned count) noexcept
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),const_cast<float *>(in1),const_cast<float *>(in2),const_cast<float *>(in3),
    };
    float *outputs[] = {
        out0,out1,out2,
    };
    dsp.compute(count, inputs, outputs);
}

const char *Delay3PhaseDigital::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
}

const char *Delay3PhaseDigital::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
}

const char *Delay3PhaseDigital::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
}

const char *Delay3PhaseDigital::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
}

const Delay3PhaseDigital::ParameterRange *Delay3PhaseDigital::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return 0;
    }
}

bool Delay3PhaseDigital::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool Delay3PhaseDigital::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool Delay3PhaseDigital::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool Delay3PhaseDigital::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

float Delay3PhaseDigital::get_parameter(unsigned index) const noexcept
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    switch (index) {
    
    default:
        (void)dsp;
        return 0;
    }
}

void Delay3PhaseDigital::set_parameter(unsigned index, float value) noexcept
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    switch (index) {
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}



float Delay3PhaseDigital::get_passive(unsigned index) const noexcept
{
    Delay3PhaseDigitalDsp &dsp = static_cast<Delay3PhaseDigitalDsp &>(*fDsp);
    switch (index) {
    
    default:
        (void)dsp;
        return 0;
    }
}


