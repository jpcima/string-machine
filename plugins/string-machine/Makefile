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
	sources/SolinaChorusStereo.cpp \
	sources/MidiDefs.cpp \
	sources/bbd/bbd_line.cpp \
	sources/bbd/bbd_filter.cpp \
	sources/dsp/AHDSREnvelope.cpp \
	sources/dsp/Delay3Phase.cpp \
	sources/dsp/Delay3PhaseStereo.cpp \
	sources/dsp/OnePoleFilter.cpp \
	gen/dsp/Delay3PhaseDigital.cpp \
	gen/dsp/Delay3PhaseDigitalStereo.cpp \
	gen/dsp/LFO3PhaseDual.cpp \
	gen/dsp/StringFiltersHighshelf.cpp \
	gen/dsp/NoiseLFO.cpp \
	gen/dsp/PwmOscillator.cpp \
	gen/dsp/AsymWaveshaper.cpp \
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
	-Isources -Igen -Imeta -Ithirdparty/blink -Ithirdparty/vco \
	-Ithirdparty/fontstash -Ithirdparty/stb -Ithirdparty/pl_list

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS += lv2_sep
TARGETS += vst

all: $(TARGETS)

RES2C := ../../dpf/utils/res2c.py
artwork:
	$(RES2C) Artwork artwork
.PHONY: artwork

layouts: StringMachineUILayouts.Main.inc
.PHONY: layouts

LAYOUT_TOOL := ../../tools/layout-tool/bin/layout-tool$(APP_EXT)
$(LAYOUT_TOOL):
	$(MAKE) -C ../../tools/layout-tool

StringMachineUILayouts.%.inc: layouts/%.fl $(LAYOUT_TOOL)
	$(LAYOUT_TOOL) $< > $@

# --------------------------------------------------------------
