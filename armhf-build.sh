#!/bin/sh

rm -rf build
meson setup --cross-file armhf.ini build
cd build
ninja

