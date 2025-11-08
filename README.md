# Statistical Data Analysis for Nuclear and Subnuclear Physics <br> Module 3

This repository contains the materials for **Module 3** of the _Statistical Data Analysis for Nuclear and Subnuclear Physics_ course, part of the Master’s Degree in Physics at the University of Bologna.


### Repository Structure

```bash
statistical-data-analysis/
│
├── data/                 → Real or toy datasets 
│
├── docs/                 → Documentation and reference material
│ ├── howto/              → Practical guides (ROOT installation)
│ ├── teaching_material/  → Slides
│ └── references.md
│
├── templates/            → Analysis templates or notebook skeletons
│
├── exercises/            → Exercises organized by lesson or topic
│
└── README.md
```


### Table of Contents

- [Course Overview](#course-overview)
  * [Key Topics](#key-topics)
  * [Course Structure](#course-structure)
  * [Assessment](#assessment)
- [Prerequisites](#prerequisites)
  * [Recommended Skills](#recommended-skills)
  * [Preparation Before Laboratory Sessions](#preparation-before-laboratory-sessions)
- [Computing Environment](#computing-environment)
  * [Testing Your Installation](#testing-your-installation)
- [Documentation](#documentation)
  * [ROOT and Related Resources](#root-and-related-resources)
  * [Linux Resources](#linux-resources)
  * [Further Reading on C++](#further-reading-on-c)
   
---

<!-- toc -->

### Course Overview

The module focuses on selected statistical analysis cases in High Energy Physics (HEP), using **RooFit** and **RooStats** as the main tools.

#### <ins>Key Topics</ins>

| Area | Tools / Concepts |
|------|------------------|
| Data Modeling | **RooFit** |
| Statistical Analysis | **RooStats** |
| Multivariate Analysis | **TMVA** |
| Unfolding Techniques | **RooUnfold** |

#### <ins>Course Structure</ins>

- **4 hands-on lab sessions**
  -   Each session begins with a short lecture (with slides)
  -   Followed by guided exercises or project work
-   **Assignments** must be completed and submitted via **Virtuale** before the exam
- Exercises are perfomed using **PyROOT**  or **C++ code**
> Submission of all assignments is **mandatory** to access the exam

- **Computer Lab Setup** 
  <br> You can choose between two options:
  1.  **Personal Laptop** (with ROOT installed and RooFit/RooStats/TMVA)
  2.  **Lab workstations** (Windows machines accessible via UNIBO credentials)

#### <ins>Assessment</ins>

The final exam is joint between Modules 1, 2, and 3 and includes:
1. Theory questions  
2. One practical exercise  
3. One question based on lab work (e.g., code analysis or commentary)

**Eligibility:** All assignments must be submitted before the exam.

#### <ins>Teaching Materials</ins>

Available on:
- **Virtuale (UNIBO)**: slides, assignments
- **GitHub**: installation guides, examples, templates

---

### Prerequisites

Students enrolling in this course are expected to have familiarity with basic concepts in **statistics** and **programming**, as well as with the **[ROOT Framework](https://root.cern)** for data analysis and visualization.

#### <ins>Recommended Skills</ins>

Both **C++** and **Python** users are welcome in this course. All students should be comfortable using **ROOT** to load and execute macros or run jupyter notebooks. 

**For C++ Users**
- Familiarity with **C++** syntax and concepts. **You will not be required to compile code**
- Ability to run C++ macros within the **ROOT** environment and manage ROOT files.

**For Python Users**
- Familiarity with **Python** and **Jupyter Notebooks**.  
- Ability to use **ROOT** via **PyROOT**.

#### <ins>Preparation Before Laboratory Sessions</ins>

Before attending the lab sessions, students are expected to:
1. Review the **ROOT Primer**.  
2. Read the following sections from *Practical Statistics for the LHC*:  
   - *Introduction*  
   - *Conceptual Blocks for Modeling*  
3. Refresh their programming fundamentals:
   - **C++ Users:** namespaces, classes, inheritance, pointers vs. references.  
   - **Python Users:** Python syntax, Jupyter workflows, and ROOT integration.

---

### Computing Environment

- **Required software**: ROOT, Jupyter, Visual Studio Code (recommended)

- **Reference system:**
  <br>**Linux Ubuntu 24.04 (Windows Subsystem for Linux WSL 2 on Windows)**
  <br>same setup as the university lab machines.
  <br>
  <br>📄 Installation guide:<br>
  [WSL Setup Guide with ROOT, Jupyter, and VS Code (Ubuntu 24.04)](docs/howto/ROOT_installation.md)
  <br>
  
- **Other options**
  <br> Native Linux / macOS / Windows setups are also suitable
  <br> provided the required software tools are properly installed. 
  * **General Setup Guides** from the course 
      _“Programmazione per la Fisica”_ 
     (Bachelor’s Degree in Physics, University of Bologna):  
     + [Windows Subsystem for Linux (WSL)](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/WSLGuide.md) _(in Italian)_  
     + [macOS](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/macOSGuide.md) _(in Italian)_  
     + [ROOT Framework Installation](https://github.com/Programmazione-per-la-Fisica/howto/tree/main/ROOT-installation)  
  * for Windows 7, 8, 10 (up to build 10511)
     + [ROOT installation](https://www.unibo.it/sitoweb/gabriele.sirri2/contenuti-utili/df5f946d)  
  
- **Cloud-based alternatives**
  <br> If you can't install ROOT locally, you can use one of the following cloud-based environments to run ROOT and notebooks directly in your browser.
  * **ROOT on Colab**
    <br>Run ROOT interactively on **Google Colab**, 
    with optional persistent storage through your Google Drive or github. 
    Sessions are **time-limited** (typically up to 12 hours) and may disconnect after periods of inactivity.
    + [ROOT on Colab](./docs/howto/root_on_colab.ipynb)
  * **ROOT on Binder**
    <br>Launch ROOT notebooks in a **temporary Binder environment** without any local setup.  
    No account or installation is required, but all work is **non-persistent** 
    (data is lost after the session ends unless you **manually download or export your notebooks**).   
    + [ROOT on Binder](./docs/howto/root_on_binder.md)

#### <ins>Testing Your Installation</ins>

To check that ROOT and its extensions are correctly installed:

```python 
import ROOT
w = ROOT.RooWorkspace()       # Expected output: RooFit v3.xx ...
t = ROOT.TMVA.TMVAGui()       # Expected error: file TMVA.root does not exist
```

---

### Documentation

#### <ins>ROOT and Related Resources</ins>

#### ROOT
-   [Main Docs](https://root.cern/doc/master/)    
-   [Class Reference](https://root.cern/doc/master/classes.html)

#### RooFit
-   [Manual](https://root.cern/manual/roofit/) 
-   [Quick Start Guide](https://ph-root-2.cern.ch/d/roofit-20-minutes.html)    
-   [User Manual PDF](https://root.cern.ch/download/doc/RooFit_Users_Manual_2.91-33.pdf)    
-   [Tutorials](https://root.cern/doc/master/group__tutorial__roofit.html)
    
#### RooStats
-   [Documentation](https://twiki.cern.ch/twiki/bin/view/RooStats/WebHome)    
-   [Examples](https://github.com/pellicci/UserCode/tree/master/RooFitStat_class)
    
#### <ins>Linux Resources</ins>

To get familiar with Linux and the command line, refer to this comprehensive tutorial:  
- [Ryan’s Linux Tutorial](https://ryanstutorials.net/linuxtutorial/)
<br>**Recommended chapters:**  
  * The Command Line  
  * Basic Navigation  
  * File Manipulation

#### <ins>Further Reading on C++</ins>

-   [ISO C++](http://www.isocpp.org)    
-   [C++ Standards Committee](http://www.open-std.org/jtc1/sc22/wg21/)    
-   [C++ Now](http://cppnow.org/)    
-   [CppCon](http://cppcon.org/)    
-   [Boost Libraries](http://www.boost.org/)    

💡 Learn and apply **Modern C++** (C++11 / C++14 / C++17 / C++20)

---
