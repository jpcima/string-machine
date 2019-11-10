#!/bin/bash

# ---------------------------------------------------------------------------------------------------------------------
# stop on error

set -e

# ---------------------------------------------------------------------------------------------------------------------
# print shell commands

set -x

# ---------------------------------------------------------------------------------------------------------------------
# setup

export PKG_CONFIG="pkg-config --static"
export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig"

export PATH=/usr/local/bin:"$PATH"

export CFLAGS="-I/usr/local/include"
export CXXFLAGS="-I/usr/local/include"
export LDFLAGS="-L/usr/local/lib"

# ---------------------------------------------------------------------------------------------------------------------
# build the plugin

# TODO setup cairo UI build...
MACOS=true make $MAKE_ARGS
