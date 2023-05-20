# SADX - Gnorc Cove

A level port of Gnorc Cove from Spyro 1.

## Overview:

This repository only hosts the code I used for this mod. If you are looking for the latest playable release, you can download it from [GameBanana - Gnorc Cove](https://gamebanana.com/mods/433998).

The purpose of this repository is to backup my code on the cloud and to serve as public resource for other modders, I think some of this code might serve as helpful examples for other people working on level mods.

## Repository Notes:

Cloning this repository should result in a buildable .dll project of this mod without any additional tweaks needed, though there's a few things worth noting:

* Make sure that you are compiling in **x86 mode**.
* The project settings already have setup the necessary additional include directories in **Project > Properties > C/C++ > General > Additional Include Directories** for both **Release - x86** and **Debug - x86**. These are the include directories:

  * `$(ProjectDir)`
  * `$(ProjectDir)objects`
  * `$(ProjectDir)programming`

* The files in the `programming` folder are the same ones encountered in the `programming` folder that is shipped with the SADX Mod Loader. I copy these files manually at the time of creating my project, so remember that you might need to replace them with "fresh" ones from the latest Mod Loader release.

  * Adding to this: `AnimationFile.cpp`, `LandTableInfo.cpp` and `ModelInfo.cpp` have been edited (changed `#include "stdafx.h"` for `#include "pch.h"`) since I needed to add them to the **Source Files** of this project for some specific functions I used (**Source Files > Right Click > Add Existing Item**).

If you are starting out, it's recommendable making your own project from scratch and use these functions and annotations as a guide / example to learn what they do instead of cloning the repository (since a lot of things are tailored in particular for my mod, so they might not apply on a general way).

It's also recommended to check out the [X-Hax Discord](https://discord.gg/gqJCF47) if you are looking for further help and troubleshooting.
