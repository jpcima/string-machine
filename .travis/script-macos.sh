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
export PKG_CONFIG_PATH="/opt/local/lib/pkgconfig"

export PATH=/opt/local/bin:"$PATH"

export CFLAGS="-I/opt/local/include"
export CXXFLAGS="-I/opt/local/include"
export LDFLAGS="-L/opt/local/lib"

# ---------------------------------------------------------------------------------------------------------------------
# build the plugin

# TODO setup cairo UI build...
MACOS=true make $MAKE_ARGS
