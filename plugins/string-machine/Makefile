#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------

# Disable stripping by default
SKIP_STRIPPING ?= true

# --------------------------------------------------------------
# Project name, used for binaries

NAME = string-machine

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	StringMachinePlugin.cpp \
	StringMachineShared.cpp \
	sources/StringOsc.cpp \
	sources/StringSynth.cpp \
	sources/StringFilters.cpp \
	sources/SolinaChorus.cpp \
	sources/dsp/ADSREnvelope.cpp \
	sources/dsp/OscillatorBlepRect.cpp \
	sources/dsp/LFO3PhaseDual.cpp \
	sources/dsp/Delay3Phase.cpp

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

BUILD_CXX_FLAGS += -Isources -Ithirdparty/blink

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS += lv2_dsp
TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
