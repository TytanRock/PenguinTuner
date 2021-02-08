#!/bin/sh

meson setup --cross-file armhf.ini obj-x86_64-linux-gnu
cd obj-x86_64-linux-gnu
meson configure -Dhost_arch=armhf
meson compile

