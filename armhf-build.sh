#!/bin/sh

meson setup --cross-file armhf.ini --cross-file cross.ini build
cd build
meson configure -Dhost_arch=armhf
meson compile

