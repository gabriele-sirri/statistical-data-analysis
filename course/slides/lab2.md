---
marp: true
theme: default
paginate: true
math: katex
header: "Statistical Data Analysis — Lab 2"
style: |
  section { font-size: 26px; }
  section.lead h1 { font-size: 46px; }
  code { font-size: 0.85em; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Lab 2 — Likelihood and fit quality
**Statistical Data Analysis for Nuclear and Subnuclear Physics — Module 3**
G. Sirri · Hands-on sessions, 9:00–13:00

---

# Recap (5 minutes)

Discuss in pairs, then we compare:

1. In the marked Poisson model, which factor is the **rate** and which the **shape**? What is a **channel**, and what is a **component**?
2. Extended fit vs fit with fractions: what information is lost with fractions?
3. A binned likelihood is **not** a $\chi^2$ fit. Why does it matter for low counts?
4. Which two Lab 1 notebooks did you submit? Which cell was the hardest?

---

# Solutions of Lab 1 (15 minutes)

The solutions are in the `solutions` branch: [`solutions/lab1/`](https://github.com/gabriele-sirri/statistical-data-analysis/tree/solutions/solutions/lab1), from today.

- **[A](https://github.com/gabriele-sirri/statistical-data-analysis/blob/solutions/solutions/lab1/ex_A_solution.ipynb)**: the Gaussian fit and the **ranges** of a parameter and of an observable (A1, A3)
- **[B](https://github.com/gabriele-sirri/statistical-data-analysis/blob/solutions/solutions/lab1/ex_B_solution.ipynb)**: the **binned** Breit–Wigner fit and the central limit theorem (B1, B2)
- **[C](https://github.com/gabriele-sirri/statistical-data-analysis/blob/solutions/solutions/lab1/ex_C_solution.ipynb)**: **extended** and **shape-only** fits, and the number of free parameters (C1, C2)

---

# Today's schedule

| Time | |
|---|---|
| 9:00 | Recap and Lab 1 questions |
| 9:20 | Talk A: what happens in `fitTo` |
| 9:40 | Hands-on A: anatomy of a fit |
| 10:25 | **Break (15 min)** |
| 10:40 | Talk B: likelihood intervals, nuisance parameters |
| 11:00 | Hands-on B: the on/off problem |
| 11:45 | **Break (10 min)** |
| 11:55 | Talk C: residuals, pulls and Toy MC |
| 12:10 | Hands-on C: pulls, bias, coverage |
| 12:35 | Open lab: finish a notebook, ask questions |
| 12:55 | Wrap-up |

---

<!-- _class: lead -->
# Talk A
## What happens in `fitTo`

---

# What happens in `fitTo`

`pdf.fitTo(data)` is a convenient wrapper. Under the hood, it does four things:

1. Builds the **negative log-likelihood** $-\ln L(\theta)$ (a function of the parameters)
2. Minimises it with **MIGRAD** (the gradient-descent algorithm of MINUIT).
3. Computes the covariance matrix with **HESSE** (second derivatives).
4. (On request) computes asymmetric errors with **MINOS**.

$$-\ln L(\theta) = -\sum_i \ln f(x_i\,|\,\theta) \;\;[+\,\nu(\theta)\;\text{ if extended}]$$

Today we open the box and call each step ourselves, with `RooMinimizer`.

*More: [why MINUIT, and the risks of another minimiser](./lab2_backup.md)*

---

# MIGRAD, HESSE, MINOS

Three algorithms of **MINUIT**, the minimisation library of ROOT:

| Step | What it does | Output |
|---|---|---|
| **MIGRAD** | follows the gradient to the minimum (variable metric) | best-fit values, **EDM** (Estimated Distance to Minimum).|
| **HESSE** | second derivatives at the minimum: $V = H^{-1}$, $H_{ij}=\partial^2(-\ln L)/\partial\theta_i\partial\theta_j$ | symmetric errors, correlations |
| **MINOS** | scans $-\ln L$ until it rises by 0.5 for each parameter | asymmetric errors |

- HESSE assumes the likelihood is a **parabola** near the minimum
- MINOS makes no such assumption, but costs more fits
- If HESSE and MINOS disagree, the likelihood is not parabolic: **trust MINOS, and say so**

*More: [Hesse and Minos](https://scikit-hep.org/iminuit/notebooks/hesse_and_minos.html)*

---

# Is my fit healthy?

Always check:

| Quantity | Healthy value |
|---|---|
| `status()` | 0 |
| `covQual()` | 3 (full, accurate covariance) |
| EDM (estimated distance to minimum) | tiny |
| parameters at a limit? | none |
| correlation coefficients | no $|\rho|\approx 1$ |

A parameter stuck at its **limit** is a warning, not a result.

---

# When fits go wrong — Debug Flowchart (1/2)

When a fit fails, follow this checklist in order:

1. **Does not converge** (MIGRAD does not find the minimum)
   - Parameter ranges too wide? Initial values too far from the likelihood minimum? 
   - *Fix*: `setRange()` narrower, `setVal()` to reasonable value.

2. **Converges but huge errors or correlation |ρ| ≈ 1**
   - Parameters are degenerate (the fit cannot distinguish them).
   - *Fix*: fix one of the two parameters, or reformulate the model.

---

# When fits go wrong — Debug Flowchart (2/2)

3. **Converges but a parameter is at the limit** (e.g., fraction = 0 or 1)
   - Physical limit is too tight, or the model is wrong.
   - *Fix*: widen the range if it makes sense, or reparametrize (e.g., fit `ln(τ)` instead of `τ`).

4. **Works only on some toys**
   - Low statistics → likelihood is not parabolic.
   - *Fix*: use MINOS, or switch to Neyman intervals (Lab 3).

---   

<!-- _class: lead -->
# Hands-on A
## Anatomy of a fit

---

# Exercise A (≈ 45 min)

Same data and model as Lab 1, Exercise C (LHCb, signal + background).

1. Build the NLL, run **MIGRAD** and **HESSE** by hand with `RooMinimizer`. Read status, EDM, `covQual`
2. Get the **MINOS** errors on `nsig`. Are they symmetric? Same as HESSE?
3. Print the **correlation matrix**. Which pair is most correlated, and why?
4. Plot the NLL scan in `nsig`, the **profile** NLL and the **HESSE parabola** together
5. Draw the 1σ and 2σ **contour** of (`nsig`, `nbkg`)

We write step 1 **together**, live (5 min), then you continue.
Notebook: [`course/lab2/ex_A.ipynb`](../lab2/ex_A.ipynb)

---

### Key Takeaways from Hands-on A

- **`fitTo()` demystified**: It creates an NLL, runs `RooMinimizer(nll).migrad()`, then `.hesse()`.
- **Statefulness**: After a fit, `RooRealVar` objects *automatically update* their central value and error. Just call `var.getVal()` and `var.getError()`.
- **Plotting Components**: `model.plotOn(frame, ROOT.RooFit.Components("bkg_name"), ROOT.RooFit.LineStyle(ROOT.kDashed))`
- **Profiling**: `nll.createProfile(poi)` creates a function that re-minimizes nuisance parameters for each point of the POI.
- **Contours**: `minimizer.contour(var1, var2, 1, 2)` draws $\Delta\text{NLL}$ contours. **Crucial**: Always run `minimizer.hesse()` immediately before `contour()` to ensure a clean, accurate error matrix and avoid stray points.

---

<!-- _class: lead -->
# Talk B
## Likelihood intervals and nuisance parameters

---

# Likelihood-ratio intervals

For **one** parameter $\mu$ (Wilks' theorem, large samples):

$$-2\ln\frac{L(\mu)}{L(\hat\mu)} \;\sim\; \chi^2_1$$

| Confidence level | $\Delta(-\ln L)$ | $-2\Delta\ln L$ |
|---|---|---|
| 68.3 % | 0.5 | 1 |
| 90% | 1.36 | 2.71 |
| 95 % | 1.92 | 3.84 |

The interval is where the NLL curve $ -\ln L $ is below the minimum **+ 0.5**.
It need not be symmetric: this is the **MINOS interval**.

---

# Nuisance parameters

A model has **parameters of interest** $\mu$ and **nuisance parameters** $\theta$ (background rate, resolution, efficiency…).

Two ways to draw the likelihood in $\mu$:

- **Slice**: fix $\theta$ at its best-fit value → too optimistic, ignores uncertainty
- **Profile**: for every $\mu$, re-fit $\theta$ → correct frequentist coverage.

$$\lambda(\mu)=\frac{L\big(\mu,\hat{\hat\theta}(\mu)\big)}{L(\hat\mu,\hat\theta)}, \qquad q(\mu) = -2\ln\lambda(\mu)$$

The profile curve is **wider** than the slice. The gap is the cost of the nuisance parameter.

---

# Signal region / control region (the classic on/off problem)

Counting experiment with an **auxiliary measurement** of the background:

$$L(s,b) = \text{Pois}(n_{\rm on}\,|\,s+b)\;\times\;\text{Pois}(n_{\rm off}\,|\,\tau b)$$

- $n_{\rm on}$: events in the signal region; $n_{\rm off}$: events in the control region
- $\tau$: ratio of control to signal exposure (size of the control region)
- Best fit: $\hat b = n_{\rm off}/\tau$, $\hat s = n_{\rm on}-\hat b$
- The uncertainty on $b$ is **not an input**: it comes from the control region

This is the model behind “background $3.8\pm0.6$”. Constraint terms in Lab 3.

*Note: The same concept extends naturally to shape analyses: control regions become additional channels that constrain nuisance parameters through a simultaneous likelihood fit.*

---

<!-- _class: lead -->
# Hands-on B
## The on/off problem

---

# Exercise B (≈ 45 min)

Counting experiment: $n_{\rm on}=17$, $n_{\rm off}=40$, $\tau=10.53$ (top-quark case).

1. Build the model with two `RooPoisson` and fit: $\hat s$, $\hat b$
2. Compute the 68 % interval on $s$ from the **profile** NLL, and with **MINOS**. Compare
3. Compare with the **slice** at $b=\hat b$
4. Repeat with a poorer control region: $n_{\rm off}=4$, $\tau=1.053$ (same $\hat b$). What changes?

We write the model of step 1 **together**, live (5 min), then you continue.
Notebook: [`course/lab2/ex_B.ipynb`](../lab2/ex_B.ipynb)

---

### Key Takeaways from Hands-on B

- **Profile vs. Slice**: A slice fixes nuisance parameters. A profile (`createProfile`) re-optimizes them.
- **MINOS = Profile Scan**: The `MINOS` algorithm in MINUIT is *exactly* the numerical evaluation of the profile likelihood interval ($\Delta\text{NLL} = 0.5$). They must match.
- **The role of $\tau$**: Propagates the background uncertainty from the control region to the signal region.

---

<!-- _class: lead -->
# Talk C
## Residuals, Pulls and Toy MC

---

# Residuals vs. Pulls: What are we looking at?

- **Residuals**: Evaluated on the **observable** ($x$) for a given **dataset** (real or simulated). 
  - Formula: $(N_{\text{data}} - N_{\text{model}}) / \sigma_{\text{model}}$
  - Purpose: Check the *goodness-of-fit* of the model shape.

- **Pulls**: Evaluated on the **parameters** ($\theta$) of the model. Requires an ensemble of **Toy Monte Carlo** experiments.
  - Formula: $\text{pull} = \frac{\hat{\theta} - \theta_{\text{true}}}{\hat{\sigma}_{\theta}}$
  - Purpose: Check the *statistical properties* of the fitter (bias, error estimation, coverage).

---

# Why toys?

Errors from HESSE or MINOS are **approximations**. A toy study tests them:

1. Generate a dataset with known true parameters
2. Fit it
3. Save the result. Repeat 300–1000 times
   
## What do Pull distributions tell us?
For a healthy, unbiased fit with correctly estimated errors, the pull distribution should be a standard Gaussian $\mathcal{N}(0, 1)$:
1. **Mean $\approx 0$**: No systematic bias in the estimator $\hat{\theta}$.
2. **RMS $\approx 1$**: The fit errors $\hat{\sigma}_{\theta}$ correctly reflect the true statistical fluctuations.
3. **Coverage**: The fraction of toys where the true value falls within the $1\sigma$ interval should be $\approx 68\%$.

---

# What goes wrong at low statistics

- Poisson fluctuations make the likelihood **non-parabolic**
- Parameters hit **boundaries** (e.g. $\nu_s \ge 0$): pulls are no longer Gaussian
- A small bias on the mean is common; a wrong RMS means **wrong errors**

Remedy: report **MINOS or profile intervals**, or run a Neyman construction with toys (Lab 3).

Always check the **fraction of failed fits**: toys that fail to converge are not “missing”, they are data about your model.

---

<!-- _class: lead -->
# Hands-on C
## Pulls, bias, coverage

---

<!-- _class: lead -->
# Hands-on C
## Pulls, bias, coverage (with `RooMCStudy`)

---

# Exercise C (≈ 25 min)

**Model:** LHCb signal + background, extended.

Instead of writing a manual Python loop, we will use the native, highly-optimized C++ class **`RooMCStudy`**, which handles generation, fitting, and pull calculation automatically.

1. Set the true values and initialize `RooMCStudy` **(we will write this part together, live, 5 min)**.
2. Run `generateAndFit()` and use the native `plotPull()` method to visualize the results.
3. Check the statistics: Mean $\approx 0$ (no bias), RMS $\approx 1$ (correct error estimation), Coverage $\approx 68\%$.
4. **Stress test:** Repeat the study with a low signal yield ($\nu_s=5$). 
   - *Question:* What happens to the pull distribution? How many fits fail or hit the physical boundary ($\nu_s \ge 0$)?

Notebook: [`course/lab2/ex_C.ipynb`](../lab2/ex_C.ipynb)

---

### Key Takeaways from Hands-on C

- **`RooMCStudy`**: The native, highly optimized C++ class for Toy Monte Carlo. It handles the generation loop, the fitting, and memory management automatically. *Never write a manual Python loop for toys if you can use this!*
- **`plotPull(var)`**: A built-in method of `RooMCStudy` that generates a beautiful `RooPlot` showing the pull distribution for a specific parameter, complete with a Gaussian fit overlay and mean/sigma statistics.
- **`pullDist(var)` / `fitPar(var)`**: Methods to extract the raw `TH1` histograms of the pulls or the fitted parameter values for further custom analysis.
- **Statefulness in Toys**: When generating toys, `RooMCStudy` uses the *current* values of the `RooRealVar` objects as the "true" values. Always set your parameters to the desired true values before calling `generateAndFit()`.

---

# Open lab (20 min)

Work on the notebook you have not finished, or on the third one if you want to see it before the solutions.

- Every notebook of today is **independent**: pick any
- Ask yourself, for each fit: *what would break it?*
- Run the notebook top to bottom: every check must say `PASS`

Ask for help early. I walk around.

---

# Wrap-up and submission (before Lab 3, in 2 weeks)

**Today you learned**
- what `fitTo` does: NLL, MIGRAD, HESSE, MINOS
- profile vs slice, and why nuisance parameters widen intervals
- toys, pulls, bias and coverage

**By Lab 3**
1. Submit **2 of the 3** notebooks of [`lab2/`](../lab2/) (A, B, C: your choice) on **Virtuale**, every check `PASS`
2. We look at the solutions of all three at the beginning of Lab 3
3. Read Cowan, Cranmer, Gross, Vitells, *Asymptotic formulae for likelihood-based tests of new physics* ([arXiv:1007.1727](https://arxiv.org/abs/1007.1727)), Sections 1–2

**Next time:** constraints and auxiliary measurements, RooStats, correlated systematics (a real problem: OPERA).
