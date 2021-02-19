#!/bin/sh

rm -rf build
meson setup -Darchitecture=$(dpkg --print-architecture) build
cd build
ninja
