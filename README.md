# 87944 - Statistical Data Analysis for Nuclear and Subnuclear Physics (Module 3) 2023/2024 
# 96082 - Computer Science for High Energy Physics (Module 3) 2023/2024

This repository contains material supporting the courses given at ALMA MATER STUDIORUM - Università di Bologna, Academic Year 2023/2024
- "87944 - Statistical Data Analysis for Nuclear and Subnuclear Physics", 
Second cycle degree/2-year master in PHYSICS;
- "96082 - Computer Science for High Energy Physics", Second cycle degree/2-year master in ADVANCED METHODS IN PARTICLE PHYSICS.

The `code` folder contains source code shown during the classes.

The content of this repository can be downloaded by `git` command:

```shell
git clone https://github.com/gabriele-sirri/sda2023
```
or directly as `zip` file.

An introduction to Git can be found [here](https://github.com/rsreds/git_course).

## Computing Environment

The computing environment for data analysis requires:

* [ROOT](https://root.cern/) with RooStats and TMVA features enables.
* editor/IDE: _Visual Studio Code_ (suggested), or others as `nano`, `vi`, `emacs`, _Eclipse_, ...

ROOT comes with a *C++* interpreter and integrates smoothly with *Python*. It works on Linux, macOS, or Windows. 

### Reference platform 

The reference platform is a Linux Ubuntu 22.04. Other recent Linux distributions (Ubuntu or other) can be fine, as well as other operating systems, such as Windows and MacOS.

For *Windows* users, the installation of Linux Ubuntu environment exploiting the Windows Subsystem for Linux (WSL) is *strongly recommended* without the need for a separate virtual machine or dual booting.

For setting up the platform, as well as for using other operating systems, such as Windows and MacOS, follow:

* the instructions written [here](https://www.unibo.it/sitoweb/gabriele.sirri2/contenuti-utili/df5f946d) (in English but not completely up to date)

* the [guides](https://github.com/Programmazione-per-la-Fisica/howto) developed for the course "Programmazione per la Fisica"(first cycle degree in Fisica, Università di Bologna) are a good reference
  - [Windows Subsystem for Linux](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/WSLGuide.md) in Italian
  - [MacOS](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/macOSGuide.md) in Italian
  
  - [ROOT framework installation](https://github.com/Programmazione-per-la-Fisica/howto/tree/main/ROOT-installation) (in English)

To familiarize yourself with Linux, the following guide is suggested:
* [Linux tutorial](https://ryanstutorials.net/linuxtutorial/) is a comprehensive guide to Linux and Bash written by Ryan Chadwick. Chapters "The Command Line", "Basic Navigation", "File Manipulation" contain critical information.

#### Alternative environment: Jupyter Notebook on cloud (without persistance!)
This "Jupyter notebook" allows you to easily interact with ROOT using your browser. 

WARNING: this configuration comes without any persistance and your files will be lost when you close the browser.
It's up to you to save a copy of your file locally on your computer.

Run the environment on mybinder: [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/gabriele-sirri/root-binder/HEAD)  
https://mybinder.org/v2/gh/gabriele-sirri/root-binder/HEAD
