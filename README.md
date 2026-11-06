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

Students are encouraged to **bring a laptop with a working ROOT environment, preferably with Python and Jupyter support** (Windows, Linux or macOS).

 If this is not possible, or if you cannot run ROOT, you can use  **GitHub Codespaces in a browser on the lab computers** (a free GitHub account is required: create it before the first lab).

1. Install ROOT with the guides in [`docs/`](docs/):
   [Windows](docs/root_on_windows.md) · [Windows with WSL](docs/root_on_wsl.md) · [Ubuntu](docs/root_on_ubuntu.md) · [Binder](docs/root_on_binder.md) · [Google Colab](docs/root_on_colab.ipynb).
   Prefer C++ to Python? [RooFit in Python and C++, side by side](docs/python_cpp_roofit.md).
   For a local installation use the course environment: `conda env create -f environment.yml`.
2. Check it: `python course/tools/check_setup.py`. Every line must say **PASS**. Do it **before Lab 1** and send the output to the instructor if something says FAIL.
3. No working ROOT? Open the repository in Codespaces: the badge above, or *Code → Codespaces → Create codespace*.

**Codespaces quota:** the free plan gives 120 core-hours per month, i.e. **60 hours on a 2-core codespace** (and 15 GB of storage). A codespace keeps running after you close the browser until its idle timeout (30 minutes by default): **stop it from the Codespaces page when you finish**. Unused codespaces are deleted after 30 days. Students can get more free hours with the GitHub Student Developer Pack.

Binder and Colab are fallback options: sessions are temporary, so download your notebooks before closing.


## References

Start here: the chapters on **Probability** and **Statistics** of the [Review of Particle Physics](https://pdg.lbl.gov/) of the PDG (Reviews, Tables and Plots → Mathematical Tools). Short, standard, and updated every year.

- G. Cowan, *Statistical Data Analysis*, Oxford University Press (1998)
- K. Cranmer, *Practical Statistics for the LHC*, [arXiv:1503.07622](https://arxiv.org/abs/1503.07622)
- G. Cowan, K. Cranmer, E. Gross, O. Vitells, *Asymptotic formulae for likelihood-based tests of new physics*, Eur. Phys. J. C 71 (2011) 1554, [arXiv:1007.1727](https://arxiv.org/abs/1007.1727)
- F. James and M. Roos, *MINUIT*, Comput. Phys. Commun. 10 (1975) 343
- S. Baker and R. D. Cousins, *Clarification of the use of chi-square and likelihood functions in fits to histograms*, Nucl. Instrum. Methods 221 (1984) 437
- ROOT: [RooFit](https://root.cern/manual/roofit/), [RooStats](https://root.cern/doc/master/group__Roostats.html), [HistFactory](https://root.cern/doc/master/group__HistFactory.html), [RooFit tutorials](https://root.cern/doc/master/group__tutorial__roofit__main.html)

## License

Code, notebooks, slides and exercise texts: licensed under the EUPL-1.2 (European Union Public Licence, see [`LICENSE`](LICENSE)).

Material in `third_party/`: LGPL 2.1, see the license in that folder.

Data: each dataset keeps the license and terms of its original source, listed in [`DATA.md`](DATA.md).
Datasets digitised by hand from published figures or simulated for teaching are approximate, and not official data releases.
