#!/bin/sh

meson setup --cross-file armhf.ini build
cd build
meson compile

