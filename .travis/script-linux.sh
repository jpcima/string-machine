#!/bin/bash

# ---------------------------------------------------------------------------------------------------------------------
# stop on error

set -e

# ---------------------------------------------------------------------------------------------------------------------
# print shell commands

set -x

# ---------------------------------------------------------------------------------------------------------------------
# set variables

test ! -z "$_BITS"

# ---------------------------------------------------------------------------------------------------------------------
# setup

export PKG_CONFIG="pkg-config"

case "$_BITS" in
    32)
        export PKG_CONFIG_LIBDIR="/usr/lib/i386-linux-gnu/pkgconfig:/usr/lib/pkgconfig:/usr/share/pkgconfig"
        ;;
    64)
        export PKG_CONFIG_LIBDIR="/usr/lib/x86_64-linux-gnu/pkgconfig:/usr/lib/pkgconfig:/usr/share/pkgconfig"
        ;;
esac

export CFLAGS="-m$_BITS"
export CXXFLAGS="-m$_BITS"
export LDFLAGS="-m$_BITS"

# ---------------------------------------------------------------------------------------------------------------------
# build the plugin

LINUX=true make $MAKE_ARGS
