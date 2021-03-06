#!/bin/sh

# If we're not root, prompt for root to install everything
[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

apt-get update
apt-get install -y libcurl4-openssl-dev libgtk-3-dev libssh-dev build-essential meson ninja-build

