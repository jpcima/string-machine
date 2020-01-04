
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: AsymWaveshaper.dsp
// Name: AsymWaveshaper
// Author: 
// Copyright: 
// License: 
// Version: 
//------------------------------------------------------------------------------







#include "AsymWaveshaper.hpp"



#include <utility>
#include <cmath>

class AsymWaveshaper::BasicDsp {
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

typedef AsymWaveshaper::BasicDsp dsp;

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

static float AsymWaveshaperDsp_faustpower3_f(float value) {
	return ((value * value) * value);
}
static float AsymWaveshaperDsp_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS AsymWaveshaperDsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class AsymWaveshaperDsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fVec0[2];
	float fConst2;
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "AsymWaveshaper.dsp");
		m->declare("filters.lib/dcblockerat:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblockerat:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblockerat:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "AsymWaveshaper");
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
		fConst0 = (109.955742f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
		fConst1 = (1.0f / (fConst0 + 1.0f));
		fConst2 = (1.0f - fConst0);
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
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
	
	FAUSTPP_VIRTUAL AsymWaveshaperDsp* clone() {
		return new AsymWaveshaperDsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("AsymWaveshaper");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "symbol", "amount");
		ui_interface->addHorizontalSlider("Clipping amount", &fHslider0, 1.0f, 0.100000001f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = AsymWaveshaperDsp_faustpower3_f(float(fHslider0));
		float fSlow1 = ((0.0f - std::sqrt(fSlow0)) / fSlow0);
		float fSlow2 = (0.333333343f * fSlow0);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float(input0[i]) + -0.666666687f);
			float fTemp1 = std::max<float>(fTemp0, fSlow1);
			float fTemp2 = (((fTemp0 > 0.0f) ? fTemp0 : (fTemp1 * (1.0f - (fSlow2 * AsymWaveshaperDsp_faustpower2_f(fTemp1))))) + 0.666666687f);
			fVec0[0] = fTemp2;
			fRec0[0] = (fConst1 * ((fTemp2 - fVec0[1]) + (fConst2 * fRec0[1])));
			output0[i] = FAUSTFLOAT(fRec0[0]);
			fVec0[1] = fVec0[0];
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




AsymWaveshaper::AsymWaveshaper()
{

    AsymWaveshaperDsp *dsp = new AsymWaveshaperDsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();

}

AsymWaveshaper::~AsymWaveshaper()
{
}

void AsymWaveshaper::init(float sample_rate)
{

    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();

}

void AsymWaveshaper::clear() noexcept
{

    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
    dsp.instanceClear();

}

void AsymWaveshaper::process(
    const float *in0,
    float *out0,
    unsigned count) noexcept
{

    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),
    };
    float *outputs[] = {
        out0,
    };
    dsp.compute(count, inputs, outputs);

}

const char *AsymWaveshaper::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Clipping amount";
    
    default:
        return 0;
    }
}

const char *AsymWaveshaper::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "";
    
    default:
        return 0;
    }
}

const char *AsymWaveshaper::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "amount";
    
    default:
        return 0;
    }
}

const char *AsymWaveshaper::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "";
    
    default:
        return 0;
    }
}

const AsymWaveshaper::ParameterRange *AsymWaveshaper::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 1, 0.1, 1 };
        return &range;
    }
    
    default:
        return 0;
    }
}

bool AsymWaveshaper::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool AsymWaveshaper::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool AsymWaveshaper::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool AsymWaveshaper::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

float AsymWaveshaper::get_parameter(unsigned index) const noexcept
{
    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider0;
    
    default:
        (void)dsp;
        return 0;
    }
}

void AsymWaveshaper::set_parameter(unsigned index, float value) noexcept
{
    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
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


float AsymWaveshaper::get_amount() const noexcept
{
    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
    return dsp.fHslider0;
}


void AsymWaveshaper::set_amount(float value) noexcept
{
    AsymWaveshaperDsp &dsp = static_cast<AsymWaveshaperDsp &>(*fDsp);
    dsp.fHslider0 = value;
}




