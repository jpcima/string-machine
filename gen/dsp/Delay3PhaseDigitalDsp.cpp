/* ------------------------------------------------------------
name: "Delay3PhaseDigital"
Code generated with Faust 2.15.11 (https://faust.grame.fr)
Compilation options: -vec -lv 0 -vs 32 -ftz 0 -mcd 16
------------------------------------------------------------ */

#ifndef  __Delay3PhaseDigitalDsp_H__
#define  __Delay3PhaseDigitalDsp_H__

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

class BaseDelay3PhaseDigitalDsp {
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
#define FAUSTCLASS Delay3PhaseDigitalDsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Delay3PhaseDigitalDsp : public BaseDelay3PhaseDigitalDsp {
	
 public:
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fRec2_perm[4];
	float fConst8;
	float fRec1_perm[4];
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec0_perm[4];
	float fConst17;
	float fYec0[16384];
	int fYec0_idx;
	int fYec0_idx_save;
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

	virtual int getNumInputs() {
		return 4;
		
	}
	virtual int getNumOutputs() {
		return 3;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			case 1: {
				rate = 0;
				break;
			}
			case 2: {
				rate = 0;
				break;
			}
			case 3: {
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
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (60076.8906f / fConst0);
		fConst2 = (0.340000004f * std::sin(fConst1));
		fConst3 = (fConst2 + 1.0f);
		fConst4 = (1.0f / fConst3);
		fConst5 = std::cos(fConst1);
		fConst6 = (0.0f - (2.0f * fConst5));
		fConst7 = (1.0f - fConst2);
		fConst8 = (1.0f - fConst5);
		fConst9 = (fConst8 / fConst3);
		fConst10 = (36137.0f / fConst0);
		fConst11 = (0.460000008f * std::sin(fConst10));
		fConst12 = (fConst11 + 1.0f);
		fConst13 = (1.0f / fConst12);
		fConst14 = std::cos(fConst10);
		fConst15 = (0.0f - (2.0f * fConst14));
		fConst16 = (1.0f - fConst11);
		fConst17 = ((1.0f - fConst14) / fConst12);
		iConst18 = int(std::ceil((0.0500000007f * fConst0)));
		
	}
	
	virtual void instanceResetUserInterface() {
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 4); l0 = (l0 + 1)) {
			fRec2_perm[l0] = 0.0f;
			
		}
		for (int l1 = 0; (l1 < 4); l1 = (l1 + 1)) {
			fRec1_perm[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 4); l2 = (l2 + 1)) {
			fRec0_perm[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 16384); l3 = (l3 + 1)) {
			fYec0[l3] = 0.0f;
			
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		
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
	
	virtual Delay3PhaseDigitalDsp* clone() {
		return new Delay3PhaseDigitalDsp();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Delay3PhaseDigital");
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* input2_ptr = inputs[2];
		FAUSTFLOAT* input3_ptr = inputs[3];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		FAUSTFLOAT* output2_ptr = outputs[2];
		float fRec2_tmp[36];
		float* fRec2 = &fRec2_tmp[4];
		float fRec1_tmp[36];
		float* fRec1 = &fRec1_tmp[4];
		float fRec0_tmp[36];
		float* fRec0 = &fRec0_tmp[4];
		float fZec0[32];
		float fZec1[32];
		int iZec2[32];
		float fZec3[32];
		float fZec4[32];
		float fZec5[32];
		float fZec6[32];
		int iZec7[32];
		float fZec8[32];
		float fZec9[32];
		float fZec10[32];
		float fZec11[32];
		float fZec12[32];
		int iZec13[32];
		float fZec14[32];
		float fZec15[32];
		int vindex = 0;
		/* Main loop */
		for (vindex = 0; (vindex <= (count - 32)); vindex = (vindex + 32)) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			int vsize = 32;
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec2_tmp[j0] = fRec2_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec2[i] = (float(input0[i]) - (fConst4 * ((fConst6 * fRec2[(i - 1)]) + (fConst7 * fRec2[(i - 2)]))));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec2_perm[j1] = fRec2_tmp[(vsize + j1)];
				
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec1[i] = (0.0f - (fConst4 * (((fConst6 * fRec1[(i - 1)]) + (fConst7 * fRec1[(i - 2)])) - (fConst8 * ((fRec2[(i - 1)] + (0.5f * fRec2[i])) + (0.5f * fRec2[(i - 2)]))))));
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec1_perm[j3] = fRec1_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = (fConst0 * ((0.00100000005f * float(input1[i])) + 0.00499999989f));
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = (fConst0 * ((0.00100000005f * float(input2[i])) + 0.00499999989f));
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec0_tmp[j4] = fRec0_perm[j4];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec0[i] = ((fConst9 * ((fRec1[(i - 1)] + (0.5f * fRec1[i])) + (0.5f * fRec1[(i - 2)]))) - (fConst13 * ((fConst15 * fRec0[(i - 1)]) + (fConst16 * fRec0[(i - 2)]))));
				
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec0_perm[j5] = fRec0_tmp[(vsize + j5)];
				
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec1[i] = (fZec0[i] + 4.99999987e-06f);
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = (fZec5[i] + 4.99999987e-06f);
				
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec11[i] = (fConst0 * ((0.00100000005f * float(input3[i])) + 0.00499999989f));
				
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 16383);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fYec0[((i + fYec0_idx) & 16383)] = ((fRec0[(i - 1)] + (0.5f * fRec0[i])) + (0.5f * fRec0[(i - 2)]));
				
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec2[i] = int(fZec1[i]);
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec3[i] = std::floor(fZec1[i]);
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec7[i] = int(fZec6[i]);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = std::floor(fZec6[i]);
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec12[i] = (fZec11[i] + 4.99999987e-06f);
				
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec4[i] = ((fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, iZec2[i]))) & 16383)] * (0.0f - (fZec0[i] + (-1.0f - fZec3[i])))) + ((fZec0[i] - fZec3[i]) * fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, (iZec2[i] + 1)))) & 16383)]));
				
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = ((fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, iZec7[i]))) & 16383)] * (0.0f - (fZec5[i] + (-1.0f - fZec8[i])))) + ((fZec5[i] - fZec8[i]) * fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, (iZec7[i] + 1)))) & 16383)]));
				
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec13[i] = int(fZec12[i]);
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = std::floor(fZec12[i]);
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (fZec4[i] + fZec9[i]);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = ((fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, iZec13[i]))) & 16383)] * (0.0f - (fZec11[i] + (-1.0f - fZec14[i])))) + ((fZec11[i] - fZec14[i]) * fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, (iZec13[i] + 1)))) & 16383)]));
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fConst17 * (fZec10[i] - fZec15[i])));
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT((0.0f - (fConst17 * (fZec15[i] - (fZec4[i] - fZec9[i])))));
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output2[i] = FAUSTFLOAT((fConst17 * (fZec10[i] + fZec15[i])));
				
			}
			
		}
		/* Remaining frames */
		if (vindex < count) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* input2 = &input2_ptr[vindex];
			FAUSTFLOAT* input3 = &input3_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			FAUSTFLOAT* output2 = &output2_ptr[vindex];
			int vsize = (count - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			for (int j0 = 0; (j0 < 4); j0 = (j0 + 1)) {
				fRec2_tmp[j0] = fRec2_perm[j0];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec2[i] = (float(input0[i]) - (fConst4 * ((fConst6 * fRec2[(i - 1)]) + (fConst7 * fRec2[(i - 2)]))));
				
			}
			/* Post code */
			for (int j1 = 0; (j1 < 4); j1 = (j1 + 1)) {
				fRec2_perm[j1] = fRec2_tmp[(vsize + j1)];
				
			}
			/* Recursive loop 1 */
			/* Pre code */
			for (int j2 = 0; (j2 < 4); j2 = (j2 + 1)) {
				fRec1_tmp[j2] = fRec1_perm[j2];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec1[i] = (0.0f - (fConst4 * (((fConst6 * fRec1[(i - 1)]) + (fConst7 * fRec1[(i - 2)])) - (fConst8 * ((fRec2[(i - 1)] + (0.5f * fRec2[i])) + (0.5f * fRec2[(i - 2)]))))));
				
			}
			/* Post code */
			for (int j3 = 0; (j3 < 4); j3 = (j3 + 1)) {
				fRec1_perm[j3] = fRec1_tmp[(vsize + j3)];
				
			}
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec0[i] = (fConst0 * ((0.00100000005f * float(input1[i])) + 0.00499999989f));
				
			}
			/* Vectorizable loop 3 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec5[i] = (fConst0 * ((0.00100000005f * float(input2[i])) + 0.00499999989f));
				
			}
			/* Recursive loop 4 */
			/* Pre code */
			for (int j4 = 0; (j4 < 4); j4 = (j4 + 1)) {
				fRec0_tmp[j4] = fRec0_perm[j4];
				
			}
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fRec0[i] = ((fConst9 * ((fRec1[(i - 1)] + (0.5f * fRec1[i])) + (0.5f * fRec1[(i - 2)]))) - (fConst13 * ((fConst15 * fRec0[(i - 1)]) + (fConst16 * fRec0[(i - 2)]))));
				
			}
			/* Post code */
			for (int j5 = 0; (j5 < 4); j5 = (j5 + 1)) {
				fRec0_perm[j5] = fRec0_tmp[(vsize + j5)];
				
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec1[i] = (fZec0[i] + 4.99999987e-06f);
				
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec6[i] = (fZec5[i] + 4.99999987e-06f);
				
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec11[i] = (fConst0 * ((0.00100000005f * float(input3[i])) + 0.00499999989f));
				
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			fYec0_idx = ((fYec0_idx + fYec0_idx_save) & 16383);
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fYec0[((i + fYec0_idx) & 16383)] = ((fRec0[(i - 1)] + (0.5f * fRec0[i])) + (0.5f * fRec0[(i - 2)]));
				
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec2[i] = int(fZec1[i]);
				
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec3[i] = std::floor(fZec1[i]);
				
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec7[i] = int(fZec6[i]);
				
			}
			/* Vectorizable loop 12 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec8[i] = std::floor(fZec6[i]);
				
			}
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec12[i] = (fZec11[i] + 4.99999987e-06f);
				
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec4[i] = ((fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, iZec2[i]))) & 16383)] * (0.0f - (fZec0[i] + (-1.0f - fZec3[i])))) + ((fZec0[i] - fZec3[i]) * fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, (iZec2[i] + 1)))) & 16383)]));
				
			}
			/* Vectorizable loop 15 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec9[i] = ((fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, iZec7[i]))) & 16383)] * (0.0f - (fZec5[i] + (-1.0f - fZec8[i])))) + ((fZec5[i] - fZec8[i]) * fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, (iZec7[i] + 1)))) & 16383)]));
				
			}
			/* Vectorizable loop 16 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				iZec13[i] = int(fZec12[i]);
				
			}
			/* Vectorizable loop 17 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec14[i] = std::floor(fZec12[i]);
				
			}
			/* Vectorizable loop 18 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec10[i] = (fZec4[i] + fZec9[i]);
				
			}
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				fZec15[i] = ((fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, iZec13[i]))) & 16383)] * (0.0f - (fZec11[i] + (-1.0f - fZec14[i])))) + ((fZec11[i] - fZec14[i]) * fYec0[(((i + fYec0_idx) - std::min<int>(iConst18, std::max<int>(0, (iZec13[i] + 1)))) & 16383)]));
				
			}
			/* Vectorizable loop 20 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output0[i] = FAUSTFLOAT((fConst17 * (fZec10[i] - fZec15[i])));
				
			}
			/* Vectorizable loop 21 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output1[i] = FAUSTFLOAT((0.0f - (fConst17 * (fZec15[i] - (fZec4[i] - fZec9[i])))));
				
			}
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; (i < vsize); i = (i + 1)) {
				output2[i] = FAUSTFLOAT((fConst17 * (fZec10[i] + fZec15[i])));
				
			}
			
		}
		
	}

};

#ifdef FAUST_UIMACROS
	#define FAUST_INPUTS 4
	#define FAUST_OUTPUTS 3
	#define FAUST_ACTIVES 0
	#define FAUST_PASSIVES 0
#endif
#undef virtual

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif
#ifndef __Delay3PhaseDigitalDsp_meta_H__
#define __Delay3PhaseDigitalDsp_meta_H__

#include <cstddef>

#ifndef FAUSTMETA
#define FAUSTMETA Delay3PhaseDigitalDsp_meta
#endif

#ifdef __GNUC__
#define FMSTATIC __attribute__((unused)) static
#else
#define FMSTATIC static
#endif

namespace Delay3PhaseDigitalDsp_meta {
	struct metadata_t { const char *key; const char *value; };
	enum class active_type_t { button, checkbox, vslider, hslider, nentry };
	enum class passive_type_t { vbargraph, hbargraph };
	enum class scale_t { linear, log, exp };

	FMSTATIC constexpr char name[] = u8"Delay3PhaseDigital";
	FMSTATIC constexpr char author[] = u8"";
	FMSTATIC constexpr char copyright[] = u8"";
	FMSTATIC constexpr char license[] = u8"";
	FMSTATIC constexpr char version[] = u8"";
	FMSTATIC constexpr char classname[] = u8"Delay3PhaseDigitalDsp";
	FMSTATIC constexpr unsigned inputs = 4;
	FMSTATIC constexpr unsigned outputs = 3;
	FMSTATIC constexpr unsigned actives = 0;
	FMSTATIC constexpr unsigned passives = 0;

	FMSTATIC const metadata_t metadata[] = {{u8"basics.lib/name", u8"Faust Basic Element Library"}, {u8"basics.lib/version", u8"0.0"}, {u8"delays.lib/name", u8"Faust Delay Library"}, {u8"delays.lib/version", u8"0.1"}, {u8"filename", u8"Delay3PhaseDigital"}, {u8"maths.lib/author", u8"GRAME"}, {u8"maths.lib/copyright", u8"GRAME"}, {u8"maths.lib/license", u8"LGPL with exception"}, {u8"maths.lib/name", u8"Faust Math Library"}, {u8"maths.lib/version", u8"2.1"}, {u8"maxmsp.lib/author", u8"GRAME"}, {u8"maxmsp.lib/copyright", u8"GRAME"}, {u8"maxmsp.lib/license", u8"LGPL"}, {u8"maxmsp.lib/name", u8"MaxMSP compatibility Library"}, {u8"maxmsp.lib/version", u8"1.1"}, {u8"name", u8"Delay3PhaseDigital"}};

	FMSTATIC constexpr active_type_t active_type[] = {};
	FMSTATIC constexpr int active_id[] = {};
	FMSTATIC const char *const active_label[] = {};
	FMSTATIC const char *const active_symbol[] = {};
	FMSTATIC const std::size_t active_offsets[] = {};
	FMSTATIC constexpr FAUSTFLOAT active_init[] = {};
	FMSTATIC constexpr FAUSTFLOAT active_min[] = {};
	FMSTATIC constexpr FAUSTFLOAT active_max[] = {};
	FMSTATIC constexpr FAUSTFLOAT active_step[] = {};

	FMSTATIC const char *const active_unit[] = {};
	FMSTATIC constexpr scale_t active_scale[] = {};
	FMSTATIC const char *const active_tooltip[] = {};

	FMSTATIC const metadata_t *const active_metadata[] = {};
	FMSTATIC constexpr std::size_t active_metadata_size[] = {};

	FMSTATIC inline void active_set(FAUSTCLASS &x, unsigned idx, FAUSTFLOAT v) { *(FAUSTFLOAT *)((char *)&x + active_offsets[idx]) = v; }
	FMSTATIC inline FAUSTFLOAT active_get(const FAUSTCLASS &x, unsigned idx) { return *(const FAUSTFLOAT *)((const char *)&x + active_offsets[idx]); }


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
#endif // __Delay3PhaseDigitalDsp_meta_H__
#undef FAUSTFLOAT
#undef FAUSTCLASS
#undef FAUSTMETA
