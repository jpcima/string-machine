CXX ?= g++
CXXFLAGS ?= -O2 -g
LDFLAGS ?=

CXXFLAGS += -std=c++11
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -MD -MP
CXXFLAGS += -Isources

TARGET_MACHINE := $(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(TARGET_MACHINE)))
APP_EXT := .exe
LDFLAGS += -static
endif

SOURCES := \
	sources/main.cpp \
	sources/string-machine/sources/StringOsc.cpp \
	sources/string-machine/gen/dsp/AsymWaveshaper.cpp \
	sources/string-machine/gen/dsp/PwmOscillator.cpp
OBJS := $(patsubst sources/%.cpp,build/%.o,$(SOURCES))

CXXFLAGS += -Isources/string-machine/sources -Isources/string-machine/gen

all: bin/test-string-osc$(APP_EXT)

clean:
	rm -rf bin build

bin/test-string-osc$(APP_EXT): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.o: sources/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: all clean

-include $(OBJS:%.o=%.d)
