#!/bin/bash

# ---------------------------------------------------------------------------------------------------------------------
# stop on error

set -e

# ---------------------------------------------------------------------------------------------------------------------
# print shell commands

set -x

# ---------------------------------------------------------------------------------------------------------------------
# set variables

test ! -z "$_MINGW"
test ! -z "$_HOST"

# ---------------------------------------------------------------------------------------------------------------------
# setup

export AR="$_HOST"-ar
export RANLIB="$_HOST"-ranlib
export CC="$_HOST"-gcc
export CXX="$_HOST"-g++
export STRIP="$_HOST"-strip
export WINDRES="$_HOST"-windres
export PKG_CONFIG="$_HOST"-pkg-config

export PKG_CONFIG="$PKG_CONFIG --static"

export PATH=/opt/"$_MINGW"/"$_HOST"/bin:/opt/"$_MINGW"/bin:"$PATH"

export CFLAGS="-I/opt/$_MINGW/include"
export CXXFLAGS="-I/opt/$_MINGW/include"
export LDFLAGS="-L/opt/$_MINGW/lib"

# ---------------------------------------------------------------------------------------------------------------------
# prepare

# invoke the Windows ttl generator using wine
sed -i 's/"$GEN"/wine "$GEN"/g' dpf/utils/generate-ttl.sh

# ---------------------------------------------------------------------------------------------------------------------
# build the plugin

# TODO setup cairo UI build...
CROSS_COMPILING=true WINDOWS=true make $MAKE_ARGS
