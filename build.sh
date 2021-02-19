#!/bin/sh

rm -rf build
meson setup build
cd build
ninja
