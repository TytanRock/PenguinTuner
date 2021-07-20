---
title: Installation
permalink: /installation
description: How to install Penguin Tuner
---

# What can run this

Penguin Tuner will eventually be cross-platform, which means it doesn't matter what operating system you're using, you can use this.

Currently, though, it only supports Linux and Mac.
Windows will come eventually, though it will probably be some time before I get to it.
If you have a need for Windows, shoot an issue and I'll raise its priority.

# How to Install

Installing Penguin Tuner is super easy and simple, you have various options depending on the operating system you use.

## Linux (Debian) - Add my GPG key to your apt sources

You can add my GPG key to your apt sources list, which means Penguin Tuner is apt install'ed just like any other package.

This is done by performing the following commands in the terminal:
``` bash
curl -s --compressed "https://penguintuner.tytan.rocks/KEY.gpg" | sudo apt-key add -
sudo curl -s --compressed -o /etc/apt/sources.list.d/penguintuner.list "https://penguintuner.tytan.rocks/penguintuner.list"
sudo apt update
sudo apt install penguintuner
```

Whenever a new Penguin Tuner release occurs, you can update by doing the following:
``` bash
sudo apt update
sudo apt install penguintuner
```

## Linux (Debian) - Download the package from Github Releases

I also publish the packages on [Github Releases](https://github.com/TytanRock/PenguinTuner/releases), you can navigate to the most up-to-date version and download it.

Once it's downloaded, you can install it just like any other apt package:
``` bash
sudo apt install ./penguintuner_<version>_<arch>.deb
```

## Mac/Linux Homebrew installation

I also provide a homebrew tap to install penguintuner through the homebrew package manager. This is very easy to setup and install once you have homebrew. If you don't have homebrew, go to the [Homebrew Home Page](https://brew.sh/) which has instructions on installing brew.

Once brew is installed, then you can add my tap and install penguintuner.
My tap is public at [TytanRock/homebrew-penguintuner](https://github.com/TytanRock/homebrew-penguintuner) if you want to look through it.
The exact commands you need to execute are the following:
``` bash
brew tap tytanrock/penguintuner
brew install penguintuner
```

And you have Penguin Tuner.

