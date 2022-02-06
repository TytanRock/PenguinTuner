#!/bin/sh

case "$(uname -s)" in
    Darwin*)
        brew update
        brew install pkgconfig cmake python3 curl libssh gtk+4
        pip3 install meson ninja
        ;;
    Linux*)
        # If we're not root, prompt for root to install everything
        [ "$(whoami)" != "root" ] && exec sudo -- "$0" "$@"
        apt-get update
        apt-get install -y libcurl4-openssl-dev libgtk-4-dev libssh-dev build-essential meson ninja-build
        ;;
    *)
        echo "Unknown Architecture, cannot configure"
esac
