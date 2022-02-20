
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







#include "NoiseLFO.hpp"



#include <utility>
#include <cmath>

class NoiseLFO::BasicDsp {
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

typedef NoiseLFO::BasicDsp dsp;

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
#define FAUSTCLASS NoiseLFODsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class NoiseLFODsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fConst2;
	float fRec6[2];
	float fRec7[2];
	int iRec8[2];
	float fRec5[2];
	float fRec4[2];
	float fRec3[2];
	float fRec2[2];
	float fRec1[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "NoiseLFO.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/nlf2:author", "Julius O. Smith III");
		m->declare("filters.lib/nlf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/nlf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "NoiseLFO");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 0;
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 1;
	}
	FAUSTPP_VIRTUAL int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
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
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (6.28318548f / fConst0);
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec6[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec7[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec8[l3] = 0;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec3[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec2[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec1[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec0[l9] = 0.0f;
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
	
	FAUSTPP_VIRTUAL NoiseLFODsp* clone() {
		return new NoiseLFODsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("NoiseLFO");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "symbol", "frequency");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Frequency", &fHslider0, 1.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = (1.0f / std::tan((fConst1 * fSlow0)));
		float fSlow2 = (1.0f / (fSlow1 + 1.0f));
		float fSlow3 = (1.0f - fSlow1);
		float fSlow4 = (fConst2 * fSlow0);
		float fSlow5 = std::sin(fSlow4);
		float fSlow6 = std::cos(fSlow4);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec6[0] = ((fSlow5 * fRec7[1]) + (fSlow6 * fRec6[1]));
			fRec7[0] = ((float((1 - iVec0[1])) + (fSlow6 * fRec7[1])) - (fSlow5 * fRec6[1]));
			int iTemp0 = ((fRec6[1] <= 0.0f) & (fRec6[0] > 0.0f));
			iRec8[0] = ((1103515245 * iRec8[1]) + 12345);
			fRec5[0] = ((fRec5[1] * float((1 - iTemp0))) + (4.65661287e-10f * (float(iRec8[0]) * float(iTemp0))));
			fRec4[0] = (0.0f - (fSlow2 * ((fSlow3 * fRec4[1]) - (fRec5[0] + fRec5[1]))));
			fRec3[0] = (0.0f - (fSlow2 * ((fSlow3 * fRec3[1]) - (fRec4[0] + fRec4[1]))));
			fRec2[0] = (0.0f - (fSlow2 * ((fSlow3 * fRec2[1]) - (fRec3[0] + fRec3[1]))));
			fRec1[0] = (0.0f - (fSlow2 * ((fSlow3 * fRec1[1]) - (fRec2[0] + fRec2[1]))));
			fRec0[0] = (0.0f - (fSlow2 * ((fSlow3 * fRec0[1]) - (fRec1[0] + fRec1[1]))));
			output0[i] = FAUSTFLOAT(fRec0[0]);
			iVec0[1] = iVec0[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			iRec8[1] = iRec8[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};
FAUSTPP_END_NAMESPACE


#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif



//------------------------------------------------------------------------------
// End the Faust code section




NoiseLFO::NoiseLFO()
{

    NoiseLFODsp *dsp = new NoiseLFODsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();

}

NoiseLFO::~NoiseLFO()
{
}

void NoiseLFO::init(float sample_rate)
{

    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();

}

void NoiseLFO::clear() noexcept
{

    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    dsp.instanceClear();

}

void NoiseLFO::process(
    
    float *out0,
    unsigned count) noexcept
{

    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    float *inputs[] = {
        0
    };
    float *outputs[] = {
        out0,
    };
    dsp.compute(count, inputs, outputs);

}

const char *NoiseLFO::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Frequency";
    
    default:
        return 0;
    }
}

const char *NoiseLFO::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "";
    
    default:
        return 0;
    }
}

const char *NoiseLFO::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "frequency";
    
    default:
        return 0;
    }
}

const char *NoiseLFO::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Hz";
    
    default:
        return 0;
    }
}

const NoiseLFO::ParameterRange *NoiseLFO::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 1, 0, 100 };
        return &range;
    }
    
    default:
        return 0;
    }
}

bool NoiseLFO::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool NoiseLFO::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool NoiseLFO::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool NoiseLFO::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

float NoiseLFO::get_parameter(unsigned index) const noexcept
{
    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider0;
    
    default:
        (void)dsp;
        return 0;
    }
}

void NoiseLFO::set_parameter(unsigned index, float value) noexcept
{
    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fHslider0 = value;
        break;
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float NoiseLFO::get_frequency() const noexcept
{
    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    return dsp.fHslider0;
}


void NoiseLFO::set_frequency(float value) noexcept
{
    NoiseLFODsp &dsp = static_cast<NoiseLFODsp &>(*fDsp);
    dsp.fHslider0 = value;
}




