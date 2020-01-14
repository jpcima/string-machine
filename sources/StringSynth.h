#pragma once
#include "StringOsc.h"
#include "StringFilters.h"
#include "SolinaChorus.h"
#include "SolinaChorusStereo.h"
#include "StringSynthDefs.h"
#include "dsp/AHDSREnvelope.h"
#include "dsp/NoiseLFO.hpp"
#include <pl_list.hpp>
#include <memory>
#include <cstdint>

class StringSynth {
public:
    StringSynth();
    ~StringSynth();

    void init(double sampleRate);

    void handleMessage(const uint8_t *msg);
    void resetAllControllers(unsigned channel);
    void generate(float *outputs[2], unsigned count);

    float getDetune() const { return fDetuneAmount; }
    void setDetune(float amount) { fDetuneAmount = amount; }

    const StringOsc::Settings &getOscSettings() const { return fOscSettings; }
    StringOsc::Settings &getOscSettings() { return fOscSettings; }

    const AHDSREnvelope::Settings &getEnvSettings() const { return fEnvSettings; }
    AHDSREnvelope::Settings &getEnvSettings() { return fEnvSettings; }

    const StringFilters::Settings &getFltSettings() const { return fFltSettings; }
    StringFilters::Settings &getFltSettings() { return fFltSettings; }

    float getMixGainUpper() const { return fMixGainUpper; }
    void setMixGainUpper(float value) { fMixGainUpper = value; }
    float getMixGainLower() const { return fMixGainLower; }
    void setMixGainLower(float value) { fMixGainLower = value; }

#if STRING_SYNTH_USE_STEREO
    typedef SolinaChorusStereo Chorus;
#else
    typedef SolinaChorus Chorus;
#endif

    const Chorus &getChorus() const { return fChorus; }
    Chorus &getChorus() { return fChorus; }

    float getMasterGain() const { return fMasterGain; }
    void setMasterGain(float value) { fMasterGain = value; }

    unsigned getPolyphony() const { return fPolyphony; }
    void setPolyphony(int value);

    float getLastDetuneUpper() const { return fLastDetuneUpper; }
    float getLastDetuneLower() const { return fLastDetuneLower; }

private:
    struct Voice {
        unsigned channel;
        unsigned note;
        float bend;
        unsigned release; // accumulated time in release phase, the greater the
                          // more electible as a voice allocation target
        AHDSREnvelope env;
        StringOsc osc;
        StringFilters flt;

        unsigned id; // only to debug voice allocs
    };

private:
    std::unique_ptr<Voice[]> fVoicesReserved;

    pl_list<Voice *> fVoicesUsed;
    pl_list<Voice *> fVoicesFree;

    float fDetuneAmount = 0;
    NoiseLFO fDetuneLFO[2];

    float fLastDetuneUpper = 0;
    float fLastDetuneLower = 0;

    float fMixGainUpper = 0;
    float fMixGainLower = 0;

    StringOsc::Settings fOscSettings;
    AHDSREnvelope::Settings fEnvSettings;
    StringFilters::Settings fFltSettings;

    Chorus fChorus;

    float fMasterGain = 0;

    unsigned fPolyphony = 16;

    struct RpnIdentifier {
        unsigned registered : 1;
        unsigned msb : 7;
        unsigned lsb : 7;
    };

    struct Controllers {
        RpnIdentifier rpnIdentifier = {};
        float pitchBend = 0;
        float pitchBendSensitivity = 0;
        unsigned volume14bit = 0;
        unsigned expression14bit = 0;
        unsigned pan14bit = 0;
        float calcBendRatio() const;
    };
    Controllers fControllers[16];

private:
    void noteOn(unsigned channel, unsigned note, unsigned vel);
    void noteOff(unsigned channel, unsigned note, unsigned vel);
    void allNotesOff(unsigned channel);
    void allSoundOff(unsigned channel);
    void allSoundOffAllChannels();
    Voice &allocNewVoice();
    Voice *findVoiceKeyedOn(unsigned channel, unsigned note);
#if STRING_SYNTH_USE_STEREO
    bool generateVoiceAdding(Voice &voice, float *outputL, float *outputR, const float *const detune[2], float bend, float addGainL, float addGainR, unsigned count);
#else
    bool generateVoiceAdding(Voice &voice, float *output, const float *const detune[2], float bend, float addGain, unsigned count);
#endif
    static void clearFinishedVoice(Voice &voice);
    static bool voiceHasReleased(const Voice &voice);
    static bool voiceHasFinished(const Voice &voice);
};
