# Statistical Data Analysis for Nuclear and Subnuclear Physics - Module 3

This repository contains the materials for **Module 3** of the _Statistical Data Analysis for Nuclear and Subnuclear Physics_ course, part of the Master’s Degree in Physics at the University of Bologna.


### 📁 Repository Structure

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


### 📚 Table of Contents

- [Course Overview](#course-overview)
  * [Key Topics](#key-topics)
  * [Course Structure](#course-structure)
  * [Assessment](#assessment)
- [Prerequisites](#prerequisites)
  * [Recommended Skills](#recommended-skills)
  * [Computer Environment](#computer-environment)
---

<!-- toc -->

### Course Overview

The module focuses on selected statistical analysis cases in High Energy Physics (HEP), using **RooFit** and **RooStats** as the main tools.

#### Key Topics

| Area | Tools / Concepts |
|------|------------------|
| Data Modeling | **RooFit** |
| Statistical Analysis | **RooStats** |
| Multivariate Analysis | **TMVA** |
| Unfolding Techniques | **RooUnfold** |

#### Course Structure

- **4 hands-on lab sessions**
  -   Each session begins with a short lecture (with slides)
  -   Followed by guided exercises or project work
-   **Assignments** must be completed and submitted via **Virtuale** before the exam
- Exercises are perfomed using **PyROOT**  or **C++ code**
> Submission of all assignments is **mandatory** to access the exam

#### Assessment

The final exam includes:
1. Theory questions  
2. One practical exercise  
3. One question based on lab work (e.g., code analysis or commentary)

**Eligibility:** All assignments must be submitted before the exam.---

---
### Prerequisites

#### Recommended Skills
-   **Statistics**: Basic understanding of terminology and methods   
-   **Programming**:
    -   C++ (Modern C++)
    -   Python (for scripting)   
-   **ROOT Framework**: Ability to run C++ macros and manage rootfiles
-   **JUPYTER**: notebooks

#### Computing Environment

**Reference system, as used in the laboratory computers**
The reference environment is **Linux Ubuntu 24.04** running on **Windows Subsystem for Linux (WSL) 2**. The essential software components are **ROOT** and **Jupyter**. The recommended code editor is **Visual Studio Code**.

This is the complete installation guide.  
[WSL Setup Guide with ROOT, Jupyter, and VS Code (Ubuntu 24.04)](./docs/howto/root_on_wsl.md)

**Other options**
- Native Linux / macOS / Windows setups are also suitable—provided the required software tools are properly installed. 


    - **General Setup Guides** from the course _“Programmazione per la Fisica”_ (Bachelor’s Degree in Physics, University of Bologna):  
      - [Windows Subsystem for Linux (WSL)](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/WSLGuide.md) _(in Italian)_  
      - [macOS](https://github.com/Programmazione-per-la-Fisica/howto/blob/main/other-OSes/macOSGuide.md) _(in Italian)_  
      - [ROOT Framework Installation](https://github.com/Programmazione-per-la-Fisica/howto/tree/main/ROOT-installation) _(in English)_

  For Windows
    [ROOT installation](https://www.unibo.it/sitoweb/gabriele.sirri2/contenuti-utili/df5f946d)  
  _(in English, though not fully up to date)_
  
- Cloud-based alternatives :  
  - [ROOT on Colab](./docs/howto/root_on_colab.ipynb)  
  - [ROOT on Binder](./docs/howto/root_on_binder.md) (non-persistent)

---

## Documentation

### ROOT and Related Resources

- **ROOT Reference Guide:**  
  [https://root.cern.ch/doc/master/classes.html](https://root.cern.ch/doc/master/classes.html)

- **RooFit User’s Manual:**  
  [https://root.cern.ch/download/doc/RooFit_Users_Manual_2.91-33.pdf](https://root.cern.ch/download/doc/RooFit_Users_Manual_2.91-33.pdf)

- **RooStats Documentation:**  
  [https://twiki.cern.ch/twiki/bin/view/RooStats/WebHome](https://twiki.cern.ch/twiki/bin/view/RooStats/WebHome)

### Linux Resources

To get familiar with Linux and the command line, refer to this comprehensive tutorial:  
- [Ryan’s Linux Tutorial](https://ryanstutorials.net/linuxtutorial/)

**Recommended chapters:**  
- The Command Line  
- Basic Navigation  
- File Manipulation

---

You can clone the repository using the following `git` command:

```bash
git clone https://github.com/gabriele-sirri/statistical-data-analysis
```
For a brief introduction to Git, refer to this [Git Course](https://github.com/rsreds/git_course) (in Italian).
