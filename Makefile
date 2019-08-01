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

install: all
	install -D -m 755 bin/string-machine-vst$(LIB_EXT) -t $(DESTDIR)$(VSTDIR)
	install -D -m 755 bin/string-machine.lv2/*$(LIB_EXT) -t $(DESTDIR)$(LV2DIR)/string-machine.lv2
	install -D -m 644 bin/string-machine.lv2/*.ttl -t $(DESTDIR)$(LV2DIR)/string-machine.lv2

install-user: all
	install -D -m 755 bin/string-machine-vst$(LIB_EXT) -t $(HOME)/.vst
	install -D -m 755 bin/string-machine.lv2/*$(LIB_EXT) -t $(HOME)/.lv2/string-machine.lv2
	install -D -m 644 bin/string-machine.lv2/*.ttl -t $(HOME)/.lv2/string-machine.lv2

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(foreach p,$(PLUGINS),$(MAKE) clean -C plugins/$(p);)
	rm -rf bin build

# --------------------------------------------------------------

.PHONY: plugins clean install install-user
