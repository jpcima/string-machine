
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







#include "PwmOscillator.hpp"



#include <utility>
#include <cmath>

class PwmOscillator::BasicDsp {
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

typedef PwmOscillator::BasicDsp dsp;

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

static float PwmOscillatorDsp_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS PwmOscillatorDsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class PwmOscillatorDsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	int iVec0[2];
	float fConst2;
	float fVec1[2];
	float fRec0[2];
	float fVec2[2];
	int IOTA;
	float fVec3[4096];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fVec4[2];
	float fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("filename", "PwmOscillator.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "PwmOscillator");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 1;
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 1;
	}
	FAUSTPP_VIRTUAL int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
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
		switch ((channel)) {
			case 0: {
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
	
	static void classInit(int sample_rate) {
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (0.25f * fConst0);
		fConst2 = (1.0f / fConst0);
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(75.0f);
		fHslider1 = FAUSTFLOAT(0.25f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec1[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec0[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec2[l3] = 0.0f;
		}
		IOTA = 0;
		for (int l4 = 0; (l4 < 4096); l4 = (l4 + 1)) {
			fVec3[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec4[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
		}
	}
	
	FAUSTPP_VIRTUAL void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	FAUSTPP_VIRTUAL void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTPP_VIRTUAL PwmOscillatorDsp* clone() {
		return new PwmOscillatorDsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("PwmOscillator");
		ui_interface->declare(&fHslider0, "symbol", "mod_depth");
		ui_interface->declare(&fHslider0, "unit", "%");
		ui_interface->addHorizontalSlider("Mod depth", &fHslider0, 75.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "symbol", "mod_frequency");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Mod frequency", &fHslider1, 0.25f, 0.100000001f, 5.0f, 0.00999999978f);
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (0.00400000019f * float(fHslider0));
		float fSlow1 = float(fHslider1);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			float fTemp0 = std::max<float>(float(input0[i]), 23.4489498f);
			float fTemp1 = std::max<float>(20.0f, std::fabs(fTemp0));
			fVec1[0] = fTemp1;
			float fTemp2 = (fRec0[1] + (fConst2 * fVec1[1]));
			fRec0[0] = (fTemp2 - std::floor(fTemp2));
			float fTemp3 = PwmOscillatorDsp_faustpower2_f(((2.0f * fRec0[0]) + -1.0f));
			fVec2[0] = fTemp3;
			float fTemp4 = ((float(iVec0[1]) * (fTemp3 - fVec2[1])) / fTemp1);
			fVec3[(IOTA & 4095)] = fTemp4;
			fVec4[0] = fSlow1;
			float fTemp5 = ((fConst2 * fVec4[1]) + fRec1[1]);
			fRec1[0] = (fTemp5 - std::floor(fTemp5));
			float fTemp6 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst0 * ((0.5f - (fSlow0 * (1.0f - std::fabs(((2.0f * fRec1[0]) + -1.0f))))) / fTemp0))));
			int iTemp7 = int(fTemp6);
			float fTemp8 = std::floor(fTemp6);
			output0[i] = FAUSTFLOAT((fConst1 * ((fTemp4 - (fVec3[((IOTA - iTemp7) & 4095)] * (fTemp8 + (1.0f - fTemp6)))) - ((fTemp6 - fTemp8) * fVec3[((IOTA - (iTemp7 + 1)) & 4095)]))));
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			fVec2[1] = fVec2[0];
			IOTA = (IOTA + 1);
			fVec4[1] = fVec4[0];
			fRec1[1] = fRec1[0];
		}
	}

};
FAUSTPP_END_NAMESPACE


#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif



//------------------------------------------------------------------------------
// End the Faust code section




PwmOscillator::PwmOscillator()
{

    PwmOscillatorDsp *dsp = new PwmOscillatorDsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();

}

PwmOscillator::~PwmOscillator()
{
}

void PwmOscillator::init(float sample_rate)
{

    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();

}

void PwmOscillator::clear() noexcept
{

    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    dsp.instanceClear();

}

void PwmOscillator::process(
    const float *in0,
    float *out0,
    unsigned count) noexcept
{

    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),
    };
    float *outputs[] = {
        out0,
    };
    dsp.compute(count, inputs, outputs);

}

const char *PwmOscillator::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Mod depth";
    
    case 1:
        return "Mod frequency";
    
    default:
        return 0;
    }
}

const char *PwmOscillator::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "";
    
    case 1:
        return "";
    
    default:
        return 0;
    }
}

const char *PwmOscillator::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "mod_depth";
    
    case 1:
        return "mod_frequency";
    
    default:
        return 0;
    }
}

const char *PwmOscillator::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "%";
    
    case 1:
        return "Hz";
    
    default:
        return 0;
    }
}

const PwmOscillator::ParameterRange *PwmOscillator::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 75, 0, 100 };
        return &range;
    }
    
    case 1: {
        static const ParameterRange range = { 0.25, 0.1, 5 };
        return &range;
    }
    
    default:
        return 0;
    }
}

bool PwmOscillator::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool PwmOscillator::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool PwmOscillator::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool PwmOscillator::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    case 1:
        return true;
    
    default:
        return false;
    }
}

float PwmOscillator::get_parameter(unsigned index) const noexcept
{
    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider0;
    
    case 1:
        return dsp.fHslider1;
    
    default:
        (void)dsp;
        return 0;
    }
}

void PwmOscillator::set_parameter(unsigned index, float value) noexcept
{
    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fHslider0 = value;
        break;
    
    case 1:
        dsp.fHslider1 = value;
        break;
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float PwmOscillator::get_mod_depth() const noexcept
{
    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    return dsp.fHslider0;
}

float PwmOscillator::get_mod_frequency() const noexcept
{
    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    return dsp.fHslider1;
}


void PwmOscillator::set_mod_depth(float value) noexcept
{
    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    dsp.fHslider0 = value;
}

void PwmOscillator::set_mod_frequency(float value) noexcept
{
    PwmOscillatorDsp &dsp = static_cast<PwmOscillatorDsp &>(*fDsp);
    dsp.fHslider1 = value;
}




