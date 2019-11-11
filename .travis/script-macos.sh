#!/bin/bash

# ---------------------------------------------------------------------------------------------------------------------
# stop on error

set -e

# ---------------------------------------------------------------------------------------------------------------------
# print shell commands

set -x

# ---------------------------------------------------------------------------------------------------------------------
# download sources in the cache directory

install -d download

LIBPNG_VERSION=1.6.37
PIXMAN_VERSION=0.38.4
CAIRO_VERSION=1.16.0

download_file() {
    test -f "$1" || wget -q -O "$1" "$2"
}

download_file {download/,https://download.sourceforge.net/libpng/}libpng-"$LIBPNG_VERSION".tar.xz
download_file {download/,https://www.cairographics.org/releases/}pixman-"$PIXMAN_VERSION".tar.gz
download_file {download/,https://www.cairographics.org/releases/}cairo-"$CAIRO_VERSION".tar.xz

# ---------------------------------------------------------------------------------------------------------------------
# setup

export PKG_CONFIG="pkg-config --static"
export PKG_CONFIG_PATH="/opt/local/lib/pkgconfig"

export PATH=/opt/local/bin:"$PATH"

export CFLAGS="-I/opt/local/include -arch i386 -arch x86_64"
export CXXFLAGS="-I/opt/local/include -arch i386 -arch x86_64"
export LDFLAGS="-L/opt/local/lib -arch i386 -arch x86_64"

# ---------------------------------------------------------------------------------------------------------------------
# dependencies

build_auto_dep() {
    cd "$1"
    shift
    ./configure --enable-silent-rules --enable-static --disable-shared --prefix=/opt/local "$@"
    make $MAKE_ARGS
    sudo make install
    cd ..
}

# extract
tar xJf download/libpng-"$LIBPNG_VERSION".tar.xz
tar xzf download/pixman-"$PIXMAN_VERSION".tar.gz
tar xJf download/cairo-"$CAIRO_VERSION".tar.xz

# patch
patch -d pixman-"$PIXMAN_VERSION" -p1 -i "`pwd`"/.travis/pixman-0.38.4-subdirs.patch
patch -d cairo-"$CAIRO_VERSION" -p1 -i "`pwd`"/.travis/cairo-1.16.0-subdirs.patch

# build
build_auto_dep libpng-"$LIBPNG_VERSION"
build_auto_dep pixman-"$PIXMAN_VERSION"
build_auto_dep cairo-"$CAIRO_VERSION" --enable-xlib=no --enable-xlib-xrender=no --enable-xcb=no --enable-ft=no --enable-fc=no --enable-gobject=no

# ---------------------------------------------------------------------------------------------------------------------
# build the plugin

MACOS=true make $MAKE_ARGS
