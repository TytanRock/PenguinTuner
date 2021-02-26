---
title: Installation
permalink: /installation
description: How to install Penguin Tuner
---

# What can run this

Penguin Tuner will eventually be cross-platform, which means it doesn't matter what operating system you're using, you can use this.

Currently, though, it only supports Linux.
MacOS is next on my list, and finally Windows, though it will probably be some time before I get to it.
If you have a need for MacOS or Windows, shoot an issue and I'll raise its priority.

Regarding Linux...

I am not familiar with the intricacies of various Linux distros, so I may use some terms wrong. Please correct me in an issue tracker if I misrepresent or misunderstand something.

I developed and tested Penguin Tuner primarily on **Debian**-based linux distros, namely on Ubuntu, Debian, Kali, and Raspberry Pi OS.

I also developed Penguin Tuner with Cross-Compilation support, so I support **amd64**, **armel**, **armhf**, and **arm64** architectures.

This means if you're using a Debian-based distro on one of those architectures (desktop, raspberry pi, or jetson for instance), you will have no problem running Penguin Tuner.

I don't know what this means for arch linux or other distros. It may work, it might not.

# How to install

Installing Penguin Tuner in a debian-based system is super easy and simple. You have two options

## Add my GPG key to your apt sources

You can add my GPG key to your apt sources list, which means Penguin Tuner is apt install'ed just like any other package.

This is done by performing the following commands in the terminal:
```
curl -s --compressed "https://penguintuner.tytan.rocks/KEY.gpg" | sudo apt-key add -
sudo curl -s --compressed -o /etc/apt/sources.list.d/penguintuner.list "https://penguintuner.tytan.rocks/penguintuner.list"
sudo apt update
sudo apt install penguintuner
```

Whenever a new Penguin Tuner release occurs, you can update by doing the following:
```
sudo apt update
sudo apt install penguintuner
```

## Download the package from Github Releases

I also publish the packages on [Github Releases](https://github.com/TytanRock/PenguinTuner/releases), you can navigate to the most up-to-date version and download it.

Once it's downloaded, you can install it just like any other apt package:
```
sudo apt install ./penguintuner_<version>_<arch>.deb
```

And you have Penguin Tuner.
