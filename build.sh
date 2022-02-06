#!/bin/sh

case "$(uname -s)" in
    Darwin*)
        mkdir -p build
        cd build
        cmake ..
        make
        ;;
    Linux*)
        mkdir -p build
        cd build
        cmake ..
        make
        ;;
    MINGW*)
        echo "I haven't figured out how to build on Windows with only CLI yet."
        ;;
esac
