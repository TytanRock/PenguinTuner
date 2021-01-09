#!/bin/sh

mkdir build/$TARGET_ARCHITECTURE -p
cd build/$TARGET_ARCHITECTURE

if ($ON_DOCKER == 'true') then
	cmake ../.. -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE
else
	export TARGET_ARCHITECTURE=linux-x64
	cmake ..
fi
make

