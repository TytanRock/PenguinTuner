#!/bin/sh

case "$(uname -s)" in
    Darwin*) arch=macos;;
    Linux*)  arch="$(dpkg --print-architecture)"
esac

rm -rf build
meson setup -Darchitecture=${arch} build
cd build
ninja $1
