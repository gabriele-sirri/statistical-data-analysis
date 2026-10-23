# Statistical Data Analysis for Nuclear and Subnuclear Physics

[![Github Codespace](https://img.shields.io/badge/open-GH_Codespaces-blue?logo=github)](https://codespaces.new/gabriele-sirri/statistical-data-analysis?quickstart=1)
[![SWAN](https://swan.docs.cern.ch/images/logos/open_in_swan.svg)](https://cern.ch/swanserver/cgi-bin/go?projurl=https://github.com/gabriele-sirri/statistical-data-analysis.git)
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/gabriele-sirri/statistical-data-analysis/main)

Hands-on lab module on ROOT, RooFit, RooStats and HistFactory, for experimental particle and astroparticle physics.

## Layout

```
.devcontainer/  environment.yml    the environment (Codespaces / conda)
course/                            slides, notebooks for the current edition
docs/                              installation guides and documentation
examples/                          self-contained physics-inspired exercises and datasets
third_party/                       material of the ROOT Project course (LGPL)
```

The `third_party/root-cpp-course-roofit` files are copied from
[`root-project/root-cpp-course`](https://github.com/root-project/root-cpp-course) (LGPL 2.1, see `ORIGIN.md`).


## Getting started

- Start here: [`course/README.md`](course/README.md)
- Use-cases: [`examples/README.md`](examples/README.md)
- Previous edition (2025): [`sda2025/`](https://github.com/gabriele-sirri/sda2025)


## Course structure

 - Lab 1 - Roofit basics and likelihood fits

 - Lab 2 - Fit diagnostics, MINUIT and validation

 - Lab 3 - Systematics, covariance matrices and RooStats

 - Lab 4 - HistFactory statistical models, RDataFrame `Vary`, and a TMVA demo

Submit 2 of 3 notebooks in each of Labs 1–3, both notebooks of Lab 4 (see [`course/README.md`](course/README.md)).


## Before the course: set up ROOT

Students are encouraged to **bring a laptop with a working ROOT environment, preferably iwth Python and Jupyter support** (Windows, Linux or macOS).

 If this is not possible, or if you cannot run ROOT, you can use  **GitHub Codespaces in a browser on the lab computers** (a free GitHub account is required: create it before the first lab).

1. Install ROOT with the guides in [`docs/`](docs/):
   [Windows](docs/root_on_windows.md) · [Windows with WSL](docs/root_on_wsl.md) · [Ubuntu](docs/root_on_ubuntu.md) · [Binder](docs/root_on_binder.md) · [Google Colab](docs/root_on_colab.ipynb).
   For a local installation use the course environment: `conda env create -f environment.yml`.
2. Check it: `python course/tools/check_setup.py`. Every line must say **PASS**. Do it **before Lab 1** and send the output to the instructor if something says FAIL.
3. No working ROOT? Open the repository in Codespaces: the badge above, or *Code → Codespaces → Create codespace*.

**Codespaces quota:** the free plan gives 120 core-hours per month, i.e. **60 hours on a 2-core codespace** (and 15 GB of storage). A codespace keeps running after you close the browser until its idle timeout (30 minutes by default): **stop it from the Codespaces page when you finish**. Unused codespaces are deleted after 30 days. Students can get more free hours with the GitHub Student Developer Pack.

Binder and Colab are fallback options: sessions are temporary, so download your notebooks before closing.


## License

Code, notebooks, slides and exercise texts: licensed under the EUPL-1.2 (European Union Public Licence, see [`LICENSE`](LICENSE)).

Material in `third_party/`: LGPL 2.1, see the license in that folder.

Data: each dataset keeps the license and terms of its original source, listed in [`DATA.md`](DATA.md).
Datasets digitised by hand from published figures or simulated for teaching are approximate, and not official data releases.
