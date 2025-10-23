# Statistical Data Analysis for Nuclear and Subnuclear Physics  
**Master’s Degree in Physics – University of Bologna**  
**Academic Year 2025/2026**

**Module 3**

Gabriele Sirri, INFN Bologna

---
This repository contains the materials for **Module 3** of the _Statistical Data Analysis for Nuclear and Subnuclear Physics_ course, part of the Master’s Degree in Physics at the University of Bologna.

Cover some cases for statistical analysis in HEP using RooFit and RooStats as main tools

## Computing Environment

The reference environment is **Linux Ubuntu 24.04** on **Windows Subsystem for Linux (WSL) 2**, as used in the lab computers.

The minimum required software tools are **ROOT** and **Jupyter**.
The recommended editor is **Visual Studio Code**.  

link:  "WSL Setup Guide with ROOT, Jupyter, and VS Code (Ubuntu 24.04)"

Other Linux distributions, as well as Windows or macOS, are also acceptable provided you installed the software tools. 

link: "Alternative environment: Jupyter Notebook on cloud (without persistance!)"

---

You can download the repository using the following `git` command:

```bash
git clone https://github.com/gabriele-sirri/statistical-data-analysis
```
For a brief introduction to Git, please refer to this [Git Course](https://github.com/rsreds/git_course) (italian).

## Documentation

### ROOT reference guide:

https://root.cern.ch/doc/master/classes.html

RooFit manual 
https://root.cern.ch/download/doc/RooFit_Users_Manual_2.91-33.pdf

RooStats documentation
https://twiki.cern.ch/twiki/bin/view/RooStats/WebHome

### For setting up the platform, as well as for using other operating systems:

*[ROOT installation](https://www.unibo.it/sitoweb/gabriele.sirri2/contenuti-utili/df5f946d) (in English but not completely up to date)

* [guides](https://github.com/Programmazione-per-la-Fisica/howto) developed for the course "Programmazione per la Fisica"(first cycle degree in Fisica, Università di Bologna) are a good reference
  - [Windows Subsystem for Linux](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/WSLGuide.md) in Italian
  - [MacOS](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/macOSGuide.md) in Italian
  
  - [ROOT framework installation](https://github.com/Programmazione-per-la-Fisica/howto/tree/main/ROOT-installation) (in English)

To familiarize yourself with Linux

* [Linux tutorial](https://ryanstutorials.net/linuxtutorial/) is a comprehensive guide to Linux and Bash written by Ryan Chadwick. Chapters "The Command Line", "Basic Navigation", "File Manipulation" contain critical information.



#### Alternative environment: Jupyter Notebook on cloud (without persistance!)
This "Jupyter notebook" allows you to easily interact with ROOT using your browser. 

WARNING: this configuration comes without any persistance and your files will be lost when you close the browser.
It's up to you to save a copy of your file locally on your computer.

Run the environment on mybinder: [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/gabriele-sirri/root-binder/HEAD)  
https://mybinder.org/v2/gh/gabriele-sirri/root-binder/HEAD
