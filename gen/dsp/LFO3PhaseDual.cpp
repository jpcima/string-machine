
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







#include "LFO3PhaseDual.hpp"



#include <utility>
#include <cmath>

class LFO3PhaseDual::BasicDsp {
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

typedef LFO3PhaseDual::BasicDsp dsp;

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

class LFO3PhaseDualDspSIG0 {
	
  FAUSTPP_PRIVATE:
	
	int iRec3[2];
	
  public:
	
	int getNumInputsLFO3PhaseDualDspSIG0() {
		return 0;
	}
	int getNumOutputsLFO3PhaseDualDspSIG0() {
		return 1;
	}
	int getInputRateLFO3PhaseDualDspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRateLFO3PhaseDualDspSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitLFO3PhaseDualDspSIG0(int sample_rate) {
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			iRec3[l3] = 0;
		}
	}
	
	void fillLFO3PhaseDualDspSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec3[0] = (iRec3[1] + 1);
			table[i] = std::sin((0.0490873866f * float((iRec3[0] + -1))));
			iRec3[1] = iRec3[0];
		}
	}

};

static LFO3PhaseDualDspSIG0* newLFO3PhaseDualDspSIG0() { return (LFO3PhaseDualDspSIG0*)new LFO3PhaseDualDspSIG0(); }
static void deleteLFO3PhaseDualDspSIG0(LFO3PhaseDualDspSIG0* dsp) { delete dsp; }

static float ftbl0LFO3PhaseDualDspSIG0[128];

#ifndef FAUSTCLASS 
#define FAUSTCLASS LFO3PhaseDualDsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class LFO3PhaseDualDsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fVbargraph0;
	float fConst4;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fRec4[2];
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fHslider4;
	float fRec6[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "LFO3PhaseDual.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "LFO3PhaseDual");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 0;
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 3;
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
	
	static void classInit(int sample_rate) {
		LFO3PhaseDualDspSIG0* sig0 = newLFO3PhaseDualDspSIG0();
		sig0->instanceInitLFO3PhaseDualDspSIG0(sample_rate);
		sig0->fillLFO3PhaseDualDspSIG0(128, ftbl0LFO3PhaseDualDspSIG0);
		deleteLFO3PhaseDualDspSIG0(sig0);
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / fConst0);
		fConst2 = std::exp((0.0f - (10.0f / fConst0)));
		fConst3 = (1.0f - fConst2);
		fConst4 = (9.99999975e-05f * fConst3);
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(6.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fHslider2 = FAUSTFLOAT(50.0f);
		fHslider3 = FAUSTFLOAT(0.59999999999999998f);
		fHslider4 = FAUSTFLOAT(50.0f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec2[l2] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec6[l6] = 0.0f;
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
	
	FAUSTPP_VIRTUAL LFO3PhaseDualDsp* clone() {
		return new LFO3PhaseDualDsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("LFO3PhaseDual");
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "symbol", "rate1");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Rate 1", &fHslider0, 6.0f, 3.0f, 9.0f, 0.00999999978f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "symbol", "depth1");
		ui_interface->declare(&fHslider2, "unit", "%");
		ui_interface->addHorizontalSlider("Depth 1", &fHslider2, 50.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "symbol", "rate2");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Rate 2", &fHslider3, 0.600000024f, 0.300000012f, 0.899999976f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "4", "");
		ui_interface->declare(&fHslider4, "symbol", "depth2");
		ui_interface->declare(&fHslider4, "unit", "%");
		ui_interface->addHorizontalSlider("Depth 2", &fHslider4, 50.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->declare(&fHslider1, "5", "");
		ui_interface->declare(&fHslider1, "symbol", "globaldepth");
		ui_interface->declare(&fHslider1, "unit", "%");
		ui_interface->addHorizontalSlider("Global Depth", &fHslider1, 100.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->declare(&fVbargraph0, "6", "");
		ui_interface->declare(&fVbargraph0, "symbol", "phase1");
		ui_interface->addVerticalBargraph("Phase 1", &fVbargraph0, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph1, "7", "");
		ui_interface->declare(&fVbargraph1, "symbol", "phase2");
		ui_interface->addVerticalBargraph("Phase 2", &fVbargraph1, 0.0f, 1.0f);
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		float fSlow0 = (fConst3 * float(fHslider0));
		float fSlow1 = float(fHslider1);
		float fSlow2 = (fConst4 * (fSlow1 * float(fHslider2)));
		float fSlow3 = (fConst3 * float(fHslider3));
		float fSlow4 = (fConst4 * (fSlow1 * float(fHslider4)));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (fConst2 * fRec1[1]));
			float fTemp0 = (fRec0[1] + (fConst1 * fRec1[0]));
			fRec0[0] = (fTemp0 - float(int(fTemp0)));
			float fTemp1 = (fRec0[0] - float(int(fRec0[0])));
			fVbargraph0 = FAUSTFLOAT(fTemp1);
			fRec2[0] = (fSlow2 + (fConst2 * fRec2[1]));
			float fTemp2 = (128.0f * fTemp1);
			int iTemp3 = int(fTemp2);
			float fTemp4 = float(iTemp3);
			fRec5[0] = (fSlow3 + (fConst2 * fRec5[1]));
			float fTemp5 = (fRec4[1] + (fConst1 * fRec5[0]));
			fRec4[0] = (fTemp5 - float(int(fTemp5)));
			float fTemp6 = (fRec4[0] - float(int(fRec4[0])));
			fVbargraph1 = FAUSTFLOAT(fTemp6);
			fRec6[0] = (fSlow4 + (fConst2 * fRec6[1]));
			float fTemp7 = (128.0f * fTemp6);
			int iTemp8 = int(fTemp7);
			float fTemp9 = float(iTemp8);
			output0[i] = FAUSTFLOAT(((fRec2[0] * ((ftbl0LFO3PhaseDualDspSIG0[iTemp3] * (fTemp4 + (1.0f - fTemp2))) + ((fTemp2 - fTemp4) * ftbl0LFO3PhaseDualDspSIG0[((iTemp3 + 1) % 128)]))) + (fRec6[0] * ((ftbl0LFO3PhaseDualDspSIG0[iTemp8] * (fTemp9 + (1.0f - fTemp7))) + ((fTemp7 - fTemp9) * ftbl0LFO3PhaseDualDspSIG0[((iTemp8 + 1) % 128)])))));
			float fTemp10 = (128.0f * (fRec0[0] + (0.333333343f - float(int((fRec0[0] + 0.333333343f))))));
			int iTemp11 = int(fTemp10);
			float fTemp12 = float(iTemp11);
			float fTemp13 = (128.0f * (fRec4[0] + (0.333333343f - float(int((fRec4[0] + 0.333333343f))))));
			int iTemp14 = int(fTemp13);
			float fTemp15 = float(iTemp14);
			output1[i] = FAUSTFLOAT(((fRec2[0] * ((ftbl0LFO3PhaseDualDspSIG0[iTemp11] * (fTemp12 + (1.0f - fTemp10))) + ((fTemp10 - fTemp12) * ftbl0LFO3PhaseDualDspSIG0[((iTemp11 + 1) % 128)]))) + (fRec6[0] * ((ftbl0LFO3PhaseDualDspSIG0[iTemp14] * (fTemp15 + (1.0f - fTemp13))) + ((fTemp13 - fTemp15) * ftbl0LFO3PhaseDualDspSIG0[((iTemp14 + 1) % 128)])))));
			float fTemp16 = (128.0f * (fRec0[0] + (0.666666687f - float(int((fRec0[0] + 0.666666687f))))));
			int iTemp17 = int(fTemp16);
			float fTemp18 = float(iTemp17);
			float fTemp19 = (128.0f * (fRec4[0] + (0.666666687f - float(int((fRec4[0] + 0.666666687f))))));
			int iTemp20 = int(fTemp19);
			float fTemp21 = float(iTemp20);
			output2[i] = FAUSTFLOAT(((fRec2[0] * ((ftbl0LFO3PhaseDualDspSIG0[iTemp17] * (fTemp18 + (1.0f - fTemp16))) + ((fTemp16 - fTemp18) * ftbl0LFO3PhaseDualDspSIG0[((iTemp17 + 1) % 128)]))) + (fRec6[0] * ((ftbl0LFO3PhaseDualDspSIG0[iTemp20] * (fTemp21 + (1.0f - fTemp19))) + ((fTemp19 - fTemp21) * ftbl0LFO3PhaseDualDspSIG0[((iTemp20 + 1) % 128)])))));
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec6[1] = fRec6[0];
		}
	}

};
FAUSTPP_END_NAMESPACE


#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif



//------------------------------------------------------------------------------
// End the Faust code section




LFO3PhaseDual::LFO3PhaseDual()
{

    LFO3PhaseDualDsp *dsp = new LFO3PhaseDualDsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();

}

LFO3PhaseDual::~LFO3PhaseDual()
{
}

void LFO3PhaseDual::init(float sample_rate)
{

    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();

}

void LFO3PhaseDual::clear() noexcept
{

    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.instanceClear();

}

void LFO3PhaseDual::process(
    
    float *out0,float *out1,float *out2,
    unsigned count) noexcept
{

    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    float *inputs[] = {
        0
    };
    float *outputs[] = {
        out0,out1,out2,
    };
    dsp.compute(count, inputs, outputs);

}

const char *LFO3PhaseDual::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Rate 1";
    
    case 1:
        return "Depth 1";
    
    case 2:
        return "Rate 2";
    
    case 3:
        return "Depth 2";
    
    case 4:
        return "Global Depth";
    
    case 5:
        return "Phase 1";
    
    case 6:
        return "Phase 2";
    
    default:
        return 0;
    }
}

const char *LFO3PhaseDual::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "";
    
    case 1:
        return "";
    
    case 2:
        return "";
    
    case 3:
        return "";
    
    case 4:
        return "";
    
    case 5:
        return "";
    
    case 6:
        return "";
    
    default:
        return 0;
    }
}

const char *LFO3PhaseDual::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "rate1";
    
    case 1:
        return "depth1";
    
    case 2:
        return "rate2";
    
    case 3:
        return "depth2";
    
    case 4:
        return "globaldepth";
    
    case 5:
        return "phase1";
    
    case 6:
        return "phase2";
    
    default:
        return 0;
    }
}

const char *LFO3PhaseDual::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Hz";
    
    case 1:
        return "%";
    
    case 2:
        return "Hz";
    
    case 3:
        return "%";
    
    case 4:
        return "%";
    
    case 5:
        return "";
    
    case 6:
        return "";
    
    default:
        return 0;
    }
}

const LFO3PhaseDual::ParameterRange *LFO3PhaseDual::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 6, 3, 9 };
        return &range;
    }
    
    case 1: {
        static const ParameterRange range = { 50, 0, 100 };
        return &range;
    }
    
    case 2: {
        static const ParameterRange range = { 0.60000002, 0.30000001, 0.89999998 };
        return &range;
    }
    
    case 3: {
        static const ParameterRange range = { 50, 0, 100 };
        return &range;
    }
    
    case 4: {
        static const ParameterRange range = { 100, 0, 100 };
        return &range;
    }
    
    case 5: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
    }
    
    case 6: {
        static const ParameterRange range = { 0, 0, 1 };
        return &range;
    }
    
    default:
        return 0;
    }
}

bool LFO3PhaseDual::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool LFO3PhaseDual::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool LFO3PhaseDual::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool LFO3PhaseDual::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

float LFO3PhaseDual::get_parameter(unsigned index) const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider0;
    
    case 1:
        return dsp.fHslider2;
    
    case 2:
        return dsp.fHslider3;
    
    case 3:
        return dsp.fHslider4;
    
    case 4:
        return dsp.fHslider1;
    
    case 5:
        return dsp.fVbargraph0;
    
    case 6:
        return dsp.fVbargraph1;
    
    default:
        (void)dsp;
        return 0;
    }
}

void LFO3PhaseDual::set_parameter(unsigned index, float value) noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fHslider0 = value;
        break;
    
    case 1:
        dsp.fHslider2 = value;
        break;
    
    case 2:
        dsp.fHslider3 = value;
        break;
    
    case 3:
        dsp.fHslider4 = value;
        break;
    
    case 4:
        dsp.fHslider1 = value;
        break;
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float LFO3PhaseDual::get_rate1() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fHslider0;
}

float LFO3PhaseDual::get_depth1() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fHslider2;
}

float LFO3PhaseDual::get_rate2() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fHslider3;
}

float LFO3PhaseDual::get_depth2() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fHslider4;
}

float LFO3PhaseDual::get_globaldepth() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fHslider1;
}

float LFO3PhaseDual::get_phase1() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fVbargraph0;
}

float LFO3PhaseDual::get_phase2() const noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    return dsp.fVbargraph1;
}


void LFO3PhaseDual::set_rate1(float value) noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.fHslider0 = value;
}

void LFO3PhaseDual::set_depth1(float value) noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.fHslider2 = value;
}

void LFO3PhaseDual::set_rate2(float value) noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.fHslider3 = value;
}

void LFO3PhaseDual::set_depth2(float value) noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.fHslider4 = value;
}

void LFO3PhaseDual::set_globaldepth(float value) noexcept
{
    LFO3PhaseDualDsp &dsp = static_cast<LFO3PhaseDualDsp &>(*fDsp);
    dsp.fHslider1 = value;
}




