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

NAME = string-machine-chorus

# --------------------------------------------------------------
# Files to build

FILES_SHARED = \
	ChorusShared.cpp \
	sources/SolinaChorus.cpp \
	sources/bbd/bbd_line.cpp \
	sources/bbd/bbd_filter.cpp \
	sources/dsp/Delay3Phase.cpp \
	gen/dsp/Delay3PhaseDigital.cpp \
	gen/dsp/LFO3PhaseDual.cpp

FILES_DSP = \
	ChorusPlugin.cpp \
	$(FILES_SHARED)

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

BUILD_CXX_FLAGS += \
	-Isources -Igen -Imeta -Ithirdparty/blink

# --------------------------------------------------------------
# Enable all possible plugin types

TARGETS += lv2_dsp
TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
