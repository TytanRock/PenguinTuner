#!/bin/sh

# If we're not root, prompt for root to install everything
[ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"

case "$(uname -s)" in
    Darwin*)
        brew update
        brew install pkgconfig cmake python3 curl libssh gtk+3
        pip3 install meson ninja
        ;;
    Linux*)
        apt-get update
        apt-get install -y libcurl4-openssl-dev libgtk-3-dev libssh-dev build-essential meson ninja-build
        ;;
    *)
        echo "Unknown Architecture, cannot configure"
esac
