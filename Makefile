#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

ifneq ($(shell test -d dpf && echo 1),1)
$(error DPF is missing, run "git submodule update --init")
endif

include dpf/Makefile.base.mk

PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
LV2DIR ?= $(LIBDIR)/lv2
VSTDIR ?= $(LIBDIR)/vst

all: plugins gen

# --------------------------------------------------------------

PLUGINS := string-machine string-machine-chorus string-machine-chorus-stereo

dgl:
	$(MAKE) -C dpf/dgl ../build/libdgl-cairo.a

plugins: dgl
	$(foreach p,$(PLUGINS),$(MAKE) all -C plugins/$(p);)

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen:
endif

# --------------------------------------------------------------

# macro faustgen: (1)faust args (2)input file (3)output file
define faustgen
	@echo faustgen: $(1) $(2) $(3)
	@install -d $(dir $(3))
	@faust -cn $(notdir $(basename $(3))) -scn Base$(notdir $(basename $(3))) $(1) -a dsp/Architecture.cpp $(2) > $(3)
	@faustmd -cn $(notdir $(basename $(3))) $(patsubst %,-X%,$(1)) $(2) >> $(3)
	@cat dsp/ArchitectureFooter.cpp >> $(3)
endef

dsp:
	$(call faustgen,-vec -uim,dsp/Delay3PhaseDigital.dsp,gen/dsp/Delay3PhaseDigitalDsp.cpp)
	$(call faustgen,-vec -uim,dsp/StringFiltersHighshelf.dsp,gen/dsp/StringFiltersHighshelfDsp.cpp)

# --------------------------------------------------------------

define install-plugin
	install -D -m 755 bin/$(1)-vst$(LIB_EXT) -t $(DESTDIR)$(VSTDIR);
	install -D -m 755 bin/$(1).lv2/*$(LIB_EXT) -t $(DESTDIR)$(LV2DIR)/$(1).lv2;
	install -D -m 644 bin/$(1).lv2/*.ttl -t $(DESTDIR)$(LV2DIR)/$(1).lv2;
endef

install: all
	$(foreach p,$(PLUGINS),$(call install-plugin,$(p)))

define install-user-plugin
	install -D -m 755 bin/$(1)-vst$(LIB_EXT) -t $(HOME)/.vst;
	install -D -m 755 bin/$(1).lv2/*$(LIB_EXT) -t $(HOME)/.lv2/$(1).lv2;
	install -D -m 644 bin/$(1).lv2/*.ttl -t $(HOME)/.lv2/$(1).lv2;
endef

install-user: all
	$(foreach p,$(PLUGINS),$(call install-user-plugin,$(p)))

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(foreach p,$(PLUGINS),$(MAKE) clean -C plugins/$(p);)
	rm -rf bin build

# --------------------------------------------------------------

.PHONY: all dgl plugins gen dsp install install-user clean
