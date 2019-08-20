/* ------------------------------------------------------------
name: "StringFiltersHighshelf"
Code generated with Faust 2.15.11 (https://faust.grame.fr)
Compilation options: -vec -lv 0 -vs 32 -ftz 0 -mcd 16
------------------------------------------------------------ */

#ifndef  __StringFiltersHighshelfDsp_H__
#define  __StringFiltersHighshelfDsp_H__

#include <cmath>
#include <cstdint>

template <class T> T min(T a, T b) { return (a < b) ? a : b; }
template <class T> T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    void declare(...) {}
};

class UI {
public:
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

class BaseStringFiltersHighshelfDsp {
};

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#define virtual /* do not make methods virtual */

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS StringFiltersHighshelfDsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class StringFiltersHighshelfDsp : public BaseStringFiltersHighshelfDsp {
	
 public:
	
	FAUSTFLOAT fHslider0;
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec0_perm[4];
	
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

	virtual int getNumInputs() {
		return 1;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
	virtual int getOutputRate(int channel) {
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
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (6.28318548f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(3.0f);
		fHslider1 = FAUSTFLOAT(1000.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			fRec0_perm[l0] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual StringFiltersHighshelfDsp* clone() {
		return new StringFiltersHighshelfDsp();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("StringFiltersHighshelf");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Cutoff", &fHslider1, 1000.0f, 10.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Gain", &fHslider0, 3.0f, 1.0f, 10.0f, 0.100000001f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* output0_ptr = outputs[0];
		float fSlow0 = std::pow(10.0f, (0.0250000004f * float(fHslider0)));
		float fSlow1 = (fConst0 * std::max<float>(0.0f, float(fHslider1)));
		float fSlow2 = (1.41421354f * (std::sqrt(fSlow0) * std::sin(fSlow1)));
		float fSlow3 = std::cos(fSlow1);
		float fSlow4 = ((fSlow0 + -1.0f) * fSlow3);
		float fSlow5 = (1.0f / ((fSlow0 + fSlow2) + (1.0f - fSlow4)));
		float fSlow6 = (fSlow0 + (1.0f - (fSlow4 + fSlow2)));
		float fSlow7 = ((fSlow0 + 1.0f) * fSlow3);
		float fSlow8 = (2.0f * (fSlow0 + (-1.0f - fSlow7)));
		float fRec0_tmp[36];
		float* fRec0 = &fRec0_tmp[4];
		float fSlow9 = (fSlow4 + fSlow0);
		float fSlow10 = (((fSlow9 + fSlow2) + 1.0f) * fSlow0);
		float fSlow11 = ((0.0f - (2.0f * fSlow0)) * ((fSlow7 + fSlow0) + -1.0f));
		float fSlow12 = ((fSlow9 + (1.0f - fSlow2)) * fSlow0);
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; (vindex <= (count - 32)); vindex = (vindex + 32)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec0[i] = (float(input0[i]) - (fSlow5 * ((fSlow6 * fRec0[(i - 2)]) + (fSlow8 * fRec0[(i - 1)]))));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec0_perm[j1] = fRec0_tmp[(vsize + j1)];
				
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fSlow5 * (((fSlow10 * fRec0[i]) + (fSlow11 * fRec0[(i - 1)])) + (fSlow12 * fRec0[(i - 2)]))));
				
			}
			
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			int vsize = (count - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec0_tmp[j0] = fRec0_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec0[i] = (float(input0[i]) - (fSlow5 * ((fSlow6 * fRec0[(i - 2)]) + (fSlow8 * fRec0[(i - 1)]))));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec0_perm[j1] = fRec0_tmp[(vsize + j1)];
				
			}
			/* Vectorizable loop 1 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fSlow5 * (((fSlow10 * fRec0[i]) + (fSlow11 * fRec0[(i - 1)])) + (fSlow12 * fRec0[(i - 2)]))));
				
			}
			
		}
		
	}

};

#ifdef FAUST_UIMACROS
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 1
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0
	FAUST_ADDHORIZONTALSLIDER("Cutoff", fHslider1, 1000.0f, 10.0f, 10000.0f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("Gain", fHslider0, 3.0f, 1.0f, 10.0f, 0.10000000000000001f);
#endif
#undef virtual

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif
#ifndef __StringFiltersHighshelfDsp_meta_H__
#define __StringFiltersHighshelfDsp_meta_H__

#include <cstddef>

#ifndef FAUSTMETA
#define FAUSTMETA StringFiltersHighshelfDsp_meta
#endif

#ifdef __GNUC__
#define FMSTATIC __attribute__((unused)) static
#else
#define FMSTATIC static
#endif

namespace StringFiltersHighshelfDsp_meta {
	struct metadata_t { const char *key; const char *value; };
	enum class active_type_t { button, checkbox, vslider, hslider, nentry };
	enum class passive_type_t { vbargraph, hbargraph };
	enum class scale_t { linear, log, exp };

	FMSTATIC constexpr char name[] = u8"StringFiltersHighshelf";
	FMSTATIC constexpr char author[] = u8"";
	FMSTATIC constexpr char copyright[] = u8"";
	FMSTATIC constexpr char license[] = u8"";
	FMSTATIC constexpr char version[] = u8"";
	FMSTATIC constexpr char classname[] = u8"StringFiltersHighshelfDsp";
	FMSTATIC constexpr unsigned inputs = 1;
	FMSTATIC constexpr unsigned outputs = 1;
	FMSTATIC constexpr unsigned actives = 2;
	FMSTATIC constexpr unsigned passives = 0;

	FMSTATIC const metadata_t metadata[] = {{u8"filename", u8"StringFiltersHighshelf"}, {u8"maths.lib/author", u8"GRAME"}, {u8"maths.lib/copyright", u8"GRAME"}, {u8"maths.lib/license", u8"LGPL with exception"}, {u8"maths.lib/name", u8"Faust Math Library"}, {u8"maths.lib/version", u8"2.1"}, {u8"maxmsp.lib/author", u8"GRAME"}, {u8"maxmsp.lib/copyright", u8"GRAME"}, {u8"maxmsp.lib/license", u8"LGPL"}, {u8"maxmsp.lib/name", u8"MaxMSP compatibility Library"}, {u8"maxmsp.lib/version", u8"1.1"}, {u8"name", u8"StringFiltersHighshelf"}};

	FMSTATIC constexpr active_type_t active_type[] = {active_type_t::hslider, active_type_t::hslider};
	FMSTATIC constexpr int active_id[] = {1, 2};
	FMSTATIC const char *const active_label[] = {u8"Cutoff", u8"Gain"};
	FMSTATIC const char *const active_symbol[] = {u8"Cutoff", u8"Gain"};
	FMSTATIC const std::size_t active_offsets[] = {(size_t)&((FAUSTCLASS *)0)->fHslider1, (size_t)&((FAUSTCLASS *)0)->fHslider0};
	FMSTATIC constexpr FAUSTFLOAT active_init[] = {1000, 3};
	FMSTATIC constexpr FAUSTFLOAT active_min[] = {10, 1};
	FMSTATIC constexpr FAUSTFLOAT active_max[] = {10000, 10};
	FMSTATIC constexpr FAUSTFLOAT active_step[] = {1, 0.1};

	FMSTATIC const char *const active_unit[] = {u8"Hz", u8"dB"};
	FMSTATIC constexpr scale_t active_scale[] = {scale_t::linear, scale_t::linear};
	FMSTATIC const char *const active_tooltip[] = {u8"", u8""};

	FMSTATIC const metadata_t active_metadata_0[] = {{u8"unit", u8"Hz"}};
	FMSTATIC const metadata_t active_metadata_1[] = {{u8"unit", u8"dB"}};

	FMSTATIC const metadata_t *const active_metadata[] = {active_metadata_0, active_metadata_1};
	FMSTATIC constexpr std::size_t active_metadata_size[] = {1, 1};

	FMSTATIC inline void active_set(FAUSTCLASS &x, unsigned idx, FAUSTFLOAT v) { *(FAUSTFLOAT *)((char *)&x + active_offsets[idx]) = v; }
	FMSTATIC inline FAUSTFLOAT active_get(const FAUSTCLASS &x, unsigned idx) { return *(const FAUSTFLOAT *)((const char *)&x + active_offsets[idx]); }

	FMSTATIC inline void set_Cutoff(FAUSTCLASS &x, FAUSTFLOAT v) { x.fHslider1 = v; }
	FMSTATIC inline void set_Gain(FAUSTCLASS &x, FAUSTFLOAT v) { x.fHslider0 = v; }
	FMSTATIC inline FAUSTFLOAT get_Cutoff(const FAUSTCLASS &x) { return x.fHslider1; }
	FMSTATIC inline FAUSTFLOAT get_Gain(const FAUSTCLASS &x) { return x.fHslider0; }

	FMSTATIC constexpr passive_type_t passive_type[] = {};
	FMSTATIC constexpr int passive_id[] = {};
	FMSTATIC const char *const passive_label[] = {};
	FMSTATIC const char *const passive_symbol[] = {};
	FMSTATIC const std::size_t passive_offsets[] = {};
	FMSTATIC constexpr FAUSTFLOAT passive_init[] = {};
	FMSTATIC constexpr FAUSTFLOAT passive_min[] = {};
	FMSTATIC constexpr FAUSTFLOAT passive_max[] = {};
	FMSTATIC constexpr FAUSTFLOAT passive_step[] = {};

	FMSTATIC const char *const passive_unit[] = {};
	FMSTATIC constexpr scale_t passive_scale[] = {};
	FMSTATIC const char *const passive_tooltip[] = {};

	FMSTATIC const metadata_t *const passive_metadata[] = {};
	FMSTATIC constexpr std::size_t passive_metadata_size[] = {};

	FMSTATIC inline FAUSTFLOAT passive_get(const FAUSTCLASS &x, unsigned idx) { return *(const FAUSTFLOAT *)((const char *)&x + passive_offsets[idx]); }

}

#undef FMSTATIC
#endif // __StringFiltersHighshelfDsp_meta_H__
#undef FAUSTFLOAT
#undef FAUSTCLASS
#undef FAUSTMETA
