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

FILES_SHARED = \
	StringMachineShared.cpp \
	sources/StringOsc.cpp \
	sources/StringSynth.cpp \
	sources/StringFilters.cpp \
	sources/SolinaChorus.cpp \
	sources/dsp/ADSREnvelope.cpp \
	sources/dsp/LFO3PhaseDual.cpp \
	sources/dsp/Delay3Phase.cpp \
	sources/dsp/OnePoleFilter.cpp \
	thirdparty/vco/OscillatorBlepRect.cpp

FILES_DSP = \
	StringMachinePlugin.cpp \
	$(FILES_SHARED)

FILES_UI = \
	StringMachineUI.cpp \
	Artwork.cpp \
	sources/ui/components/KnobSkin.cpp \
	sources/ui/components/SkinSlider.cpp \
	sources/ui/components/SkinToggleButton.cpp \
	sources/ui/components/SkinTriggerButton.cpp \
	sources/ui/components/SkinIndicator.cpp \
	sources/ui/components/PlotView.cpp \
	sources/ui/FontEngine.cpp \
	sources/ui/Fontstash.cpp \
	sources/ui/Cairo++.cpp \
	$(FILES_SHARED)

# --------------------------------------------------------------
# Do some magic

UI_TYPE = cairo
include ../../dpf/Makefile.plugins.mk

BUILD_CXX_FLAGS += \
	-Isources -Ithirdparty/blink -Ithirdparty/vco \
	-Ithirdparty/fontstash -Ithirdparty/stb

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS += lv2
TARGETS += vst

all: $(TARGETS)

#Artwork.cpp Artwork.hpp: $(wildcard artwork/*)
#	../../dpf/utils/res2c.py Artwork artwork

# --------------------------------------------------------------
