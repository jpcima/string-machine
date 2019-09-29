//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: StringFiltersHighshelf.dsp
// Name: StringFiltersHighshelf
// Author: 
// Copyright: 
// License: 
// Version: 
//------------------------------------------------------------------------------

#include "StringFiltersHighshelf.hpp"
#include <cmath>

class StringFiltersHighshelf::BasicDsp {
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

typedef StringFiltersHighshelf::BasicDsp dsp;

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
#define FAUSTCLASS StringFiltersHighshelfDsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class StringFiltersHighshelfDsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("filename", "StringFiltersHighshelf");
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
		m->declare("name", "StringFiltersHighshelf");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 1;
		
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 1;
		
	}
	FAUSTPP_VIRTUAL int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
		switch (channel) {
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
	
	static void classInit(int samplingFreq) {
		
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (6.28318548f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq))));
		
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(3.0f);
		fHslider1 = FAUSTFLOAT(1000.0f);
		
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
			
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
	
	FAUSTPP_VIRTUAL StringFiltersHighshelfDsp* clone() {
		return new StringFiltersHighshelfDsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("StringFiltersHighshelf");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "symbol", "cutoff");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Cutoff", &fHslider1, 1000.0f, 10.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "symbol", "gain");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Gain", &fHslider0, 3.0f, 1.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::pow(10.0f, (0.0250000004f * float(fHslider0)));
		float fSlow1 = (fConst0 * std::max<float>(0.0f, float(fHslider1)));
		float fSlow2 = (1.41421354f * (std::sqrt(fSlow0) * std::sin(fSlow1)));
		float fSlow3 = std::cos(fSlow1);
		float fSlow4 = ((fSlow0 + -1.0f) * fSlow3);
		float fSlow5 = (1.0f / ((fSlow0 + fSlow2) + (1.0f - fSlow4)));
		float fSlow6 = (fSlow4 + fSlow0);
		float fSlow7 = (((fSlow6 + fSlow2) + 1.0f) * fSlow0);
		float fSlow8 = (fSlow0 + (1.0f - (fSlow4 + fSlow2)));
		float fSlow9 = ((fSlow0 + 1.0f) * fSlow3);
		float fSlow10 = (2.0f * (fSlow0 + (-1.0f - fSlow9)));
		float fSlow11 = ((0.0f - (2.0f * fSlow0)) * ((fSlow9 + fSlow0) + -1.0f));
		float fSlow12 = ((fSlow6 + (1.0f - fSlow2)) * fSlow0);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = (float(input0[i]) - (fSlow5 * ((fSlow8 * fRec0[2]) + (fSlow10 * fRec0[1]))));
			output0[i] = FAUSTFLOAT((fSlow5 * (((fSlow7 * fRec0[0]) + (fSlow11 * fRec0[1])) + (fSlow12 * fRec0[2]))));
			fRec0[2] = fRec0[1];
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

StringFiltersHighshelf::StringFiltersHighshelf()
    : fDsp(new StringFiltersHighshelfDsp)
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    dsp.instanceResetUserInterface();
}

StringFiltersHighshelf::~StringFiltersHighshelf()
{
}

void StringFiltersHighshelf::init(float sample_rate)
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    dsp.instanceClear();
}

void StringFiltersHighshelf::clear() noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    dsp.instanceClear();
}

void StringFiltersHighshelf::process(
    const float *in0,
    float *out0,
    unsigned count) noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),
    };
    float *outputs[] = {
        out0,
    };
    dsp.compute(count, inputs, outputs);
}

const char *StringFiltersHighshelf::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Cutoff";
    
    case 1:
        return "Gain";
    
    default:
        return 0;
    }
}

const char *StringFiltersHighshelf::parameter_short_label(unsigned index) noexcept
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

const char *StringFiltersHighshelf::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "cutoff";
    
    case 1:
        return "gain";
    
    default:
        return 0;
    }
}

const char *StringFiltersHighshelf::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Hz";
    
    case 1:
        return "dB";
    
    default:
        return 0;
    }
}

const StringFiltersHighshelf::ParameterRange *StringFiltersHighshelf::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 1000.0, 10.0, 10000.0 };
        return &range;
    }
    
    case 1: {
        static const ParameterRange range = { 3.0, 1.0, 10.0 };
        return &range;
    }
    
    default:
        return 0;
    }
}

bool StringFiltersHighshelf::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool StringFiltersHighshelf::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool StringFiltersHighshelf::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool StringFiltersHighshelf::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return true;
    
    default:
        return false;
    }
}

float StringFiltersHighshelf::get_parameter(unsigned index) const noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider1;
    
    case 1:
        return dsp.fHslider0;
    
    default:
        (void)dsp;
        return 0;
    }
}

void StringFiltersHighshelf::set_parameter(unsigned index, float value) noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fHslider1 = value;
        break;
    
    case 1:
        dsp.fHslider0 = value;
        break;
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float StringFiltersHighshelf::get_cutoff() const noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    return dsp.fHslider1;
}

void StringFiltersHighshelf::set_cutoff(float value) noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    dsp.fHslider1 = value;
}

float StringFiltersHighshelf::get_gain() const noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    return dsp.fHslider0;
}

void StringFiltersHighshelf::set_gain(float value) noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    dsp.fHslider0 = value;
}


float StringFiltersHighshelf::get_passive(unsigned index) const noexcept
{
    StringFiltersHighshelfDsp &dsp = static_cast<StringFiltersHighshelfDsp &>(*fDsp);
    switch (index) {
    
    default:
        (void)dsp;
        return 0;
    }
}


