#include "StringOsc.h"
#include "StringSynthDefs.h"
#include <getopt.h>
#include <cmath>

int main(int argc, char *argv[])
{
    double sampleRate = 44100.0;
    double frequency = 440.0;
    double duration = 1.0;
    StringOsc::Settings settings;

    for (int c; (c = getopt(argc, argv, "")) != -1;) {
        switch (c) {
        default:
            return 1;
        }
    }

    StringOsc osc;
    osc.init(&settings, sampleRate);

    osc.setFrequency(frequency);

    unsigned numFrames = std::ceil(duration * sampleRate);

    float bufferLeft[StringSynthDefs::BufferLimit];
    float bufferRight[StringSynthDefs::BufferLimit];
    //float bufferZeros[StringSynthDefs::BufferLimit];
    float bufferOnes[StringSynthDefs::BufferLimit];

    for (unsigned i = 0; i < StringSynthDefs::BufferLimit; ++i) {
        //bufferZeros[i] = 0.0;
        bufferOnes[i] = 1.0;
    }

    for (unsigned index = 0, count; index < numFrames; index += count) {
        count = numFrames - index;
        if (count > StringSynthDefs::BufferLimit)
            count = StringSynthDefs::BufferLimit;

        float *outputs[2] = {bufferLeft, bufferRight};

        const float *detuneFactor[2] = {bufferOnes, bufferOnes};
        double bendFactor = 1.0;

        osc.process(outputs, detuneFactor, bendFactor, count);

        for (unsigned i = 0; i < count; ++i) {
            printf(
                "%f %f %f\n",
                (index + i) * (1.0 / sampleRate),
                bufferLeft[i], bufferRight[i]);
        }
    }

    return 0;
}
