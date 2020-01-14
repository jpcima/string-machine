CXX ?= g++
CXXFLAGS ?= -O3 -ffast-math -g
LDFLAGS ?=

CXXFLAGS += -std=c++11
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -MD -MP
CXXFLAGS += -Isources
CXXFLAGS += -Ithirdparty/blink

CXXFLAGS += -Istring-machine/dpf/distrho
CXXFLAGS += -Istring-machine/sources -Istring-machine/gen -Istring-machine/plugins/string-machine -Istring-machine/plugins/string-machine/meta

TARGET_MACHINE := $(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(TARGET_MACHINE)))
APP_EXT := .exe
LDFLAGS += -static
endif

SOURCES := \
	sources/main.cpp \
	string-machine/plugins/string-machine/StringMachineShared.cpp \
	string-machine/sources/SolinaChorus.cpp \
	string-machine/sources/SolinaChorusStereo.cpp \
	string-machine/sources/bbd/bbd_line.cpp \
	string-machine/sources/bbd/bbd_filter.cpp \
	string-machine/sources/dsp/Delay3Phase.cpp \
	string-machine/sources/dsp/Delay3PhaseStereo.cpp \
	string-machine/gen/dsp/Delay3PhaseDigital.cpp \
	string-machine/gen/dsp/Delay3PhaseDigitalStereo.cpp \
	string-machine/gen/dsp/LFO3PhaseDual.cpp
OBJS := $(patsubst %.cpp,build/%.o,$(SOURCES))

all: bin/benchmarks$(APP_EXT)

clean:
	rm -rf bin build

bin/benchmarks$(APP_EXT): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: all clean

-include $(OBJS:%.o=%.d)
