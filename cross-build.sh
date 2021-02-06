#!/bin/bash

rm -rf arm
meson setup --cross-file armhf.ini --cross-file cross.ini arm

