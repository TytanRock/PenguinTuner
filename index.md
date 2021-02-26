---
title: Penguin Tuner
permalink: /
description: Overview of Penguin Tuner
---

# What is this?

This is Penguin Tuner, a cross-platform GTK+ application that provides much the same functionality as CTRE's Phoenix Tuner.

You'll find that the layout is very similar to Phoenix Tuner, this is intentional so that users who are familiar with Phoenix Tuner can use Penguin Tuner with little re-learning.

You'll also find that this application isn't as fully fleshed-out as Phoenix Tuner, this is because **Penguin Tuner is a personal project of mine**, I work on it only in my free time.
Because of this, Penguin Tuner is **not** supported by CTRE, and is not an official CTRE product. 
If you run into issues using Penguin Tuner, go to this project's [Issues Page](https://github.com/TytanRock/PenguinTuner/issues) and file an issue or [Start a discussion](https://github.com/TytanRock/PenguinTuner/discussions).

# Pictures

Of course, pictures are worth thousands of words, so here's some pictures of Penguin Tuner.

These pictures were taken on a Raspberry Pi 3B+ using Raspberry Pi OS, so the layout will be the same, but the theme may change depending on your OS.

Keep in mind that updating pictures is time-consuming, so these may be slightly out-of-date.
If you want these up-to-date, file an issue or create a Pull Request with updated images!

<img src="/images/RobotController.png" alt="Robot Controller Image">

<img src="/images/CanDevices.png" alt="CAN Devices Image">

<img src="/images/SelfTest.png" alt="Self Test Image">


# Who am I?

I'm Cory Ness, an intern at CTRE and the maintainer of Penguin Tuner.

While this makes it great for me to work on Penguin Tuner, it also means I'm sensitive to CTRE's IP and licensing concerns.

Therefore, only part of this application is open-sourced, the GUI/frontend.

The backend of Penguin Tuner, Penguin Backend, is close-sourced and provided as a shared-object that Penguin Tuner links against. 

This allows me to open-source some of Penguin Tuner while maintaining my obligations to CTRE, and realistically I see most users wanting the source for customization purposes anyway.

You can find more info about me at [my website](https://tytan.rocks).

