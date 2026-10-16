---
marp: true
theme: default
paginate: true
math: katex
header: "Statistical Data Analysis — Lab 4"
style: |
  section { font-size: 26px; }
  section.lead h1 { font-size: 46px; }
  code { font-size: 0.85em; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Lab 4 — HistFactory and your analysis
**Statistical Data Analysis for Nuclear and Subnuclear Physics — Module 3**
G. Sirri · Hands-on sessions, 9:00–13:00

---

# Recap (5 minutes)

1. Constraint term or auxiliary measurement: which one do you use, and when?
2. A source of systematic uncertainty moves three channels. How many nuisance parameters do you need?
3. Which tool for a discovery, which for an upper limit?

Today ends with **your showcase**.

---

# Today's schedule

| Time | |
|---|---|
| 9:00 | Recap |
| 9:05 | Talk A: from histograms to a likelihood (HistFactory) |
| 9:25 | Hands-on A: one toy, three ways (ROOT Team course) |
| 10:05 | **Break (10 min)** |
| 10:15 | Talk B: RDataFrame `Vary` and modern C++ |
| 10:30 | Hands-on B: HistFactory on CMS $H\to4\ell$ |
| 11:05 | **Break (10 min)** |
| 11:15 | Project: last 20 minutes |
| 11:35 | **Showcases** (3–5 min per team) |
| 12:50 | Wrap-up and feedback |

---

<!-- _class: lead -->
# Talk A
## From histograms to a likelihood

---

# The binned model

Bins $b$, expected counts $\nu_b(\vec\phi,\vec\alpha)$, observed $n_b$:

$$L(\vec\phi,\vec\alpha)=\prod_{b\in\text{bins}}\text{Pois}\big(n_b\,|\,\nu_b(\vec\phi,\vec\alpha)\big)\;\times\;\prod_j c_j(a_j\,|\,\alpha_j)$$

$$\nu_b=\sum_{\text{samples}}\;\underbrace{\nu^{0}_{sb}}_{\text{template}}\;\times\;\underbrace{\prod_\kappa \kappa_{sb}(\vec\phi,\vec\alpha)}_{\text{modifiers}}$$

It is the **extended marked Poisson model** of Lab 1, with a histogram as the shape and modifiers as nuisance parameters. **HistFactory** is the recipe that builds this likelihood from histograms.

---

# HistFactory building blocks

| Level | Meaning | In the ROOT API |
|---|---|---|
| **Measurement** | the whole analysis, POI, luminosity | `Measurement` |
| **Channel** | a region with its own data (signal region, control region) | `Channel` |
| **Sample** | one process: a template histogram | `Sample` |
| **Modifier** | how a parameter changes a sample | see next slide |

Output: a **workspace** with a `ModelConfig`: the same objects you used in Lab 3.

---

# Modifiers

| Modifier | Effect | Constraint | Typical use |
|---|---|---|---|
| `NormFactor` | free scale factor | none | signal strength $\mu$; **a background normalised by a control region** |
| `OverallSys` | scale by $1\pm\epsilon$ | Gaussian | luminosity, cross section |
| `HistoSys` | morph the shape (up/down templates) | Gaussian | energy scale, tune parameter |
| `StatError` | per-bin MC statistics | Poisson / Gaussian | finite simulation |

A **shared** `NormFactor` between two channels is a **control-region measurement**: the same idea as the on/off problem, with histograms.

---

# Same likelihood, different file format

- ROOT: `hist2workspace` or the C++/Python API → RooFit workspace
- `pyhf`: the same model in JSON, pure Python
- Both implement the same likelihood, cross-checked by the LHC experiments

What you learn today is what ATLAS and CMS use to publish their statistical models.

---

<!-- _class: lead -->
# Hands-on A
## One toy, three ways

---

# Exercise A (≈ 40 min)

ROOT Team course `02-roofit`, in `third_party/root-cpp-course-roofit/`:

1. Run the pipeline (`make_toys`, `unbinned`, `analysis`, `histfactory`, `likelihood`)
2. **Where do $\mu$ and $\theta$ act in the simulation?** (look at `physics.h`)
3. Compare the three fits of the same data: yields, $\hat\mu$, uncertainties
4. Read $\hat\theta=\theta_{\rm nom}+\hat\alpha\,\Delta\theta$ and compare with $\theta_{\rm true}=1.3$
5. Compare the slice and the profile of $\mu$ with Lab 2

Notebook: `lab4/ex_A.ipynb` (guide, C++ macros run from Python)

---

<!-- _class: lead -->
# Talk B
## RDataFrame `Vary` and modern C++

---

# Systematic variations in one event loop

```python
ROOT.gInterpreter.Declare("double w_theta(double eta, double theta) {...}")   # weight as a function of theta

df = df.Vary("bkg_w", "ROOT::RVec<double>{w_theta(eta, 1.4), w_theta(eta, 0.6)}",
             ["theta_up", "theta_down"], "bkg_shape")
h_nom = df.Histo1D(("h", ";|#eta|;events", 8, 0, 2.2), "aeta", "bkg_w")
variations = ROOT.RDF.Experimental.VariationsFor(h_nom)
h_up, h_down = variations["bkg_shape:theta_up"], variations["bkg_shape:theta_down"]
```

- **One event loop**: nominal and varied histograms together
- The varied histograms are exactly the `HistoSys` inputs
- Cost: close to a single loop, not $1+2N$ loops

Code from the ROOT Team course: `analysis.cpp`.

---

# Why modern C++ in analysis

```python
ROOT.gInterpreter.Declare("""
double mass_scale(double m, double k) { return m * (1 + k); }
""")
df = df.Define("m_up", "mass_scale(m, 0.005)")
```

- The expression is **compiled just in time**: C++ speed from Python
- Lambdas, `auto`, `RVec`: concise, vectorised code
- A Python loop over events does **not** scale; RDataFrame does
- Production code (experiment frameworks) is C++: you can read and write both

See the optional notebook `optional/rdf_cpp_speed.ipynb`.

---

<!-- _class: lead -->
# Hands-on B
## HistFactory on CMS $H\to4\ell$

---

# The case

CMS Open Data, $H\to ZZ^*\to4\ell$ (arXiv:1207.7235). Real data and simulated templates.

| | Signal region | Control region |
|---|---|---|
| range | $70$–$181$ GeV, 37 bins | $m_{4\ell}>181$ GeV, **1 bin** |
| data | 102 events | 176 events |
| samples | $H\to4\ell$, $ZZ$, DY, $t\bar t$ | the same |

- Signal: $\mu$ (`NormFactor`)
- $ZZ$: `kZZ` (`NormFactor`) **shared** by both channels: the control region measures it
- Other backgrounds: from simulation (Lab 3: they could be constrained)

---

# Exercise B (≈ 35 min)

1. Build the `Measurement`: two channels, four samples, shared `kZZ`
2. Fit: $\hat\mu$, $\hat k_{ZZ}$. Compare with the fit **without** control region ($k_{ZZ}=1$)
3. 68 % interval on $\mu$, significance of $\mu=0$ (RooStats, as in Lab 3)
4. Add a 5 % luminosity uncertainty (`OverallSys`; **illustrative size**). What changes?
5. Slice vs profile of $\mu$: how correlated are $\mu$ and $k_{ZZ}$?

Notebook: `lab4/ex_B.ipynb`

---

# Showcase: one figure, one number, one caveat (3–5 min)

- **One figure** from your notebook, readable from the back of the room
- **One number**: your main result with its uncertainty, and its meaning
- **One caveat**: the most important limitation, usually your systematic
- Say **who did what**. Every team member speaks

Order: by lottery. Questions: one per team, from another team.

---

# Wrap-up and feedback

**You can now**
- write the full model: marked Poisson, nuisance parameters, constraints, control regions
- fit it, validate it with toys, and make statements with RooStats
- read a HistFactory workspace and a published statistical model

**Before you leave**
- Final notebook + one-page report on the course portal
- Solutions of all labs are in `solutions/` after the deadline
- Optional material: `optional/`
- Short anonymous feedback form (5 questions)

Thank you!
