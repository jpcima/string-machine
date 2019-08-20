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

NAME = string-machine-chorus-stereo

# --------------------------------------------------------------
# Files to build

FILES_SHARED = \
	StereoChorusShared.cpp \
	sources/SolinaChorus.cpp \
	sources/bbd/bbd_line.cpp \
	sources/bbd/bbd_filter.cpp \
	sources/dsp/LFO3PhaseDual.cpp \
	sources/dsp/Delay3Phase.cpp

FILES_DSP = \
	StereoChorusPlugin.cpp \
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
