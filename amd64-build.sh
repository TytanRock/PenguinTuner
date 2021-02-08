#!/bin/sh

meson setup obj-x86_64-linux-gnu
cd obj-x86_64-linux-gnu
meson compile

