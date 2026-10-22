---
marp: true
theme: default
paginate: true
math: katex
header: "Statistical Data Analysis — Lab 1"
style: |
  section { font-size: 26px; }
  section.lead h1 { font-size: 46px; }
  code { font-size: 0.85em; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Lab 1 — Data modelling and RooFit basics
**Statistical Data Analysis for Nuclear and Subnuclear Physics — Module 3**
G. Sirri · Hands-on sessions, 9:00–13:00

---

# Roadmap: 4 labs, one analysis chain

| Lab | Topic | What to submit |
|---|---|---|
| **1** | Data model, RooFit, fits | **2 of 3** notebooks (A, B, C) |
| **2** | Likelihood, MINUIT, toys, nuisance parameters | **2 of 3** notebooks |
| **3** | Systematics, RooStats, correlated uncertainties | **2 of 3** notebooks |
| **4** | HistFactory, RDataFrame `Vary`, TMVA | **both** notebooks (A, B) |

- Labs are **two weeks apart**: finish your notebooks between labs
- You choose which 2 of the 3 to submit. We work on **all** of them in class, and solutions are published for all
- Each lab: 3 × (short talk → hands-on), 2 breaks
- Tools: **ROOT / RooFit / RooStats**, Python first, modern C++ when it matters

---

# Today's schedule

| Time | |
|---|---|
| 9:00 | Setup check (5 min) + talk A: data modelling |
| 9:25 | Hands-on A: Gaussian, toys, fits |
| 10:20 | **Break (15 min)** |
| 10:35 | Talk B: RooFit building blocks, binned vs unbinned |
| 10:55 | Hands-on B: lifetime + LHCb $B^0$ mass |
| 11:50 | **Break (10 min)** |
| 12:00 | Talk C: composite models, extended fits |
| 12:15 | Hands-on C: signal + background |
| 12:50 | Wrap-up and submission rules |

---

# Setup check (5 minutes)

Use **your laptop with ROOT**. If it does not work, open the repo in **GitHub Codespaces** (in the browser, free GitHub account). Then run:

```python
import ROOT
print(ROOT.__version__)
w = ROOT.RooWorkspace("w")          # RooFit banner expected
ROOT.gInterpreter.ProcessLine('std::cout << "C++ OK" << std::endl;')
```

- No ROOT banner or import error → ask now, not at 12:00
- Laptop: Windows (WSL), Linux or macOS. Fallback: Codespaces on the lab computers. **Same notebooks everywhere**
- Codespaces: **stop it when you finish**. Free quota: 60 h/month on 2 cores. After you close the browser it keeps running for about 30 minutes

---

<!-- _class: lead -->
# Talk A
## From data to a model

---

# The inference chain

$$\text{data} \;\longrightarrow\; \text{model} \;\longrightarrow\; \text{likelihood} \;\longrightarrow\; \text{inference}$$

- **Model**: probability of the data given parameters, $P(\text{data}\,|\,\theta)$
- **Likelihood**: the same function, read as a function of $\theta$ with data fixed
- **Inference**: estimates, intervals, tests, limits

This course builds one block per lab. Today: **the model**.

---

# The marked Poisson model

An experiment records $n$ events, each with measured features $\vec{x}_i$ (the "marks"):

$$P(n,\{\vec{x}_i\}\,|\,\theta) \;=\; \text{Pois}(n\,|\,\nu(\theta)) \;\prod_{i=1}^{n} f(\vec{x}_i\,|\,\theta)$$

- $\nu(\theta)$: expected number of events → **rate**
- $f(\vec{x}\,|\,\theta)$: normalised pdf of the marks → **shape**
- Rate-only = counting experiment. Shape-only = $\nu$ is not interesting (fix or ignore)

Reference: Cranmer, *Practical Statistics for the LHC*, arXiv:1503.07622

---

# Notation: observables and parameters

| | Letters | Examples | What it is |
|---|---|---|---|
| **Observable** (data) | Roman | $x$, $m$, $E$, $n$ | measured, event by event |
| **Parameter** | Greek | $\mu$, $\sigma$, $\tau$, $\nu$, $\theta$ | unknown constant of the model |

- $n$ = events **observed**, $\nu$ = events **expected**
- A hat is an **estimate** from the data: $\hat\theta$ is the best-fit value
- A subscript 0 is a fixed reference value: $\theta_0$ (true or hypothesised)
- From Lab 2: $\mu$ = **parameter of interest**, $\theta$ = **nuisance parameters**
- Careful: one letter can have two meanings ($\mu$ = mean of a Gaussian, or signal strength). **Always say what each symbol is.**

---

# A range for every variable, but not the same range

| | Observable $x$ | Parameter $\theta$ |
|---|---|---|
| In RooFit | `RooRealVar("x","x", xmin, xmax)` | `RooRealVar("mean","mean", start, lo, hi)` |
| You must give | the **range** | a **starting value** and an **allowed interval** (or fix it) |
| What the range is | the domain where the pdf is **normalised**: $\int f\,dx = 1$ | a **bound for the minimiser**: it cannot leave it |
| Events outside | **not in the fit** | not applicable |
| The fit depends on it | **yes**: shape, normalisation, and (extended fit) the yields $N_s$, $N_b$ | **yes**: if the minimum is near a limit, or the interval is badly chosen |

The range of an observable **defines the model**. The range of a parameter **steers the search**.

---

# Parameter limits: what can go wrong

- **Too narrow**: the best fit sits on the boundary. The printout shows it, and the errors (HESSE, MINOS) are **not reliable** there
- **Too wide**: slow or failed convergence, and unphysical regions ($\sigma \le 0$, negative yields)
- **Start near the expected value**: the starting value is not the range
- **Physical or numerical?** A limit like $\mu \ge 0$ is physics and can change the inference (Lab 3). A loose limit to help MIGRAD is numerics. **Say which one it is**
- To keep a parameter out of the fit: `par.setConstant(True)`

Try on the minimal program:

```python
sigma.setRange(0.1, 2)        # the true value, 3, is now outside: look at sigma and its error
x.setRange("fit", -5, 5)      # a sub-range of the observable
gauss.fitTo(data, Range="fit")  # what changes, and why?
```

---

# Channels and processes

Several **processes** (signal, backgrounds) contribute to one **channel**:

$$\nu = \sum_p \nu_p, \qquad f(x) = \sum_p \frac{\nu_p}{\nu}\, f_p(x)$$

| Example | Observable $x$ | Signal | Background |
|---|---|---|---|
| LHCb | $m(p\bar p)$ | $B^0$ peak | combinatorial |
| CUORE-0 | energy | peak | flat/exponential |
| IceCube | zenith / energy | oscillation | atmospheric |
| MAGIC | image parameter | $\gamma$ | hadrons |

Different fields, **same structure**.

---

# Why RooFit?

RooFit = a toolkit to **build, combine, fit and share** probability models.

- Models are **objects**: compose them, don't rewrite the likelihood
- Normalisation, toys, plots, composite and simultaneous fits come for free
- The model lives in a **workspace**: it goes straight into RooStats and HistFactory

Honest comparison (we use RooFit because it is what experiments use):

| Tool | Strength |
|---|---|
| `scipy` / `iminuit` | simple fits, pure Python |
| `zfit`, `pyhf` | modern Python alternatives (pyhf = HistFactory in Python) |
| **RooFit** | full chain model → workspace → RooStats, used in collaborations |

---

<!-- _class: lead -->
# Hands-on A
## Gaussian: model, toys, fit

---

# The minimal RooFit program

```python
import ROOT

x     = ROOT.RooRealVar("x", "x", -10, 10)
mean  = ROOT.RooRealVar("mean", "mean", 0, -10, 10)
sigma = ROOT.RooRealVar("sigma", "sigma", 3, 0.1, 10)
gauss = ROOT.RooGaussian("gauss", "gauss", x, mean, sigma)

data   = gauss.generate(x, 10000)                 # toy MC
result = gauss.fitTo(data, Save=True, PrintLevel=-1)   # ML fit

frame = x.frame(Title="Gaussian")
data.plotOn(frame)
gauss.plotOn(frame)
frame.Draw()
```

- Variables are shared objects: the pdf *knows* `mean` and `sigma`
- Pythonic keyword arguments (`Save=True`) replace `RooFit.Save()`

---

# Exercise A (≈ 50 min)

**A1.** Gaussian, mean = 0, $\sigma$ = 1. Plot the pdf. Change $\sigma$ to 3.
Generate 10 000 **unbinned** events, fit with ML, plot the result.

**A2.** Exponential pdf with $\tau$ = 4.5. Generate **binned** data
(1000 events, bin width 0.5) with `generateBinned`. Fit and plot.

**Questions to answer in your notebook**
1. Fitted values and errors vs the true ones: are they compatible?
2. Repeat A1 with 100 events instead of 10 000. What changes?
3. Why is the error on $\sigma$ different from the error on the mean?

Notebook: `course/lab1/ex_A.ipynb`  ·  Reference: tutorials `rf101`, `rf201`, `rf202`

---

<!-- _class: lead -->
# Talk B
## RooFit building blocks

---

# Four objects to know

| Object | Role | Example |
|---|---|---|
| `RooRealVar` | variable / parameter, with range | `x`, `mean` |
| `RooAbsPdf` | normalised density | `RooGaussian`, `RooExponential` |
| `RooDataSet` / `RooDataHist` | unbinned / binned data | `generate`, `generateBinned` |
| `RooPlot` | frame to overlay data, pdf, pulls | `x.frame()` |

Rules of thumb
- Observables have a **range**; parameters have a **range and a start value**
- A pdf is **normalised over the observable** automatically
- `fitTo` minimises $-\ln L$ with MINUIT (more in Lab 2)

---

# Unbinned vs binned likelihood

**Unbinned**: uses every event

$$-\ln L = -\sum_i \ln f(x_i\,|\,\theta)$$

**Binned**: Poisson in each bin, expected $\nu_j(\theta)$, observed $n_j$

$$-\ln L = \sum_j \big[\nu_j(\theta) - n_j \ln \nu_j(\theta)\big]$$

- Binned is **not** a $\chi^2$ fit: it is exact for low counts, empty bins included
- Binned loses information if bins are wide; unbinned is slower with many events
- Same pdf, same code: only the dataset type changes

---

# Exercise B (≈ 55 min)

**B1. LHCb $B^0_s$ mass** — file `examples/lhcb-b0-ppbar/data/b0_invariant_mass.root`.
Import the histogram as a `RooDataHist`. Fit a Breit–Wigner. Add a Gaussian
resolution and compare the result with the PDG mass.

**B2. Central limit theorem with RooFit**
Generate the sum of $N$ uniform variables, fit a Gaussian, check the **tails**
for $N$ = 2, 5, 10, 20. Where does the Gaussian stop being a good model?

*Inspired by LHCb, “First observation of the rare purely baryonic decay $B^0 \to p\bar p$”.*

Notebook: `course/lab1/ex_B.ipynb`

---

<!-- _class: lead -->
# Talk C
## Composite models and extended fits

---

# Adding pdfs: shape-only vs extended

**Shape-only** (fractions): total yield $N$ is fixed by the data

$$f(x) = f_s\, f_{\rm sig}(x) + (1-f_s)\, f_{\rm bkg}(x)$$

**Extended** (yields): the marked Poisson model of Talk A

$$\mathcal{L} = \text{Pois}(n\,|\,N_s+N_b)\prod_i \frac{N_s f_{\rm sig}(x_i)+N_b f_{\rm bkg}(x_i)}{N_s+N_b}$$

```python
model = ROOT.RooAddPdf("model", "sig+bkg",
                       ROOT.RooArgList(sig, bkg),
                       ROOT.RooArgList(nsig, nbkg))
model.fitTo(data, Extended=True)
model.plotOn(frame, Components="bkg", LineStyle="--")
```

- Extended fit → the **yield is a parameter** (this is the rate/shape split in code)

---

# Getting data in: RDataFrame in one slide

Select and define with RDataFrame, then give the result to RooFit.

```python
ROOT.gInterpreter.Declare("""
double mass(double pt1, double pt2, double deta, double dphi)
{ return std::sqrt(2*pt1*pt2*(std::cosh(deta) - std::cos(dphi))); }
""")                                   # C++, compiled just in time
df = ROOT.RDataFrame("tree", "file.root")
df = df.Filter("pt > 20").Define("m", "mass(pt1, pt2, deta, dphi)")
h  = df.Histo1D(("h", ";m;events", 100, 100, 150), "m")
```

- Lazy: nothing runs until you ask for a result; **one event loop** for all results
- The expression is **C++ compiled just in time**: Python convenience, C++ speed (try it in exercise C4)
- Multi-threading with `ROOT.EnableImplicitMT()`
- Full RDataFrame treatment: Lab 4 (systematic variations with `Vary`)
- Fill a `RooDataSet` from RDataFrame: see `unbinned.cpp` in the ROOT Team course

---

<!-- _class: lead -->
# Hands-on C
## Signal + background

---

# Exercise C (≈ 35 min)

**C1. Extended fit, signal + background** — `examples/lhcb-b0-ppbar/data/rarest_b0_decay.dat`
Gaussian signal + exponential background, extended ML.
Report $N_s$, $N_b$ with errors. Plot with the components and the pulls.

**C2. Same exercise, shape-only (fractions)**
What happened to the information on the total yield?

**Questions C.** Which error is larger, and why? When would you *need* the rate? Is the signal significant? (Compare $N_s$ with its error: no p-value yet, we do it in Lab 3.)

**C4. (optional, 10 min)** Count the events in a mass window with `RDataFrame` and a **C++ function** (JIT).

---

# Wrap-up and submission (before Lab 2, in 2 weeks)

**Today you learned**
- the marked Poisson model: rate × shape
- RooFit objects: variable, pdf, dataset, frame
- unbinned vs binned likelihood, extended fits

**By Lab 2**
1. Submit **2 of the 3** notebooks of `lab1/` (A, B, C: your choice), run top to bottom with every check `PASS`
2. Upload them on **Virtuale**
3. Read *Practical Statistics for the LHC*, sections on likelihood and nuisance parameters
4. Open your Codespace once, to confirm it still works

Solutions of all three notebooks appear after the deadline.

**Next time:** MINUIT, $-\ln L$ scans, profile likelihood, nuisance parameters.
