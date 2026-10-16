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

# Recap (10 minutes)

Discuss in pairs, then we compare:

1. In the marked Poisson model, which factor is the **rate** and which the **shape**?
2. Extended fit vs fit with fractions: what information is lost with fractions?
3. A binned likelihood is **not** a $\chi^2$ fit. Why does it matter for low counts?
4. Which team and which case did you choose for the project?

---

# Today's schedule

| Time | |
|---|---|
| 9:00 | Recap and project check |
| 9:10 | Talk A: what happens in `fitTo` |
| 9:30 | Hands-on A: anatomy of a fit |
| 10:15 | **Break (15 min)** |
| 10:30 | Talk B: likelihood intervals, nuisance parameters |
| 10:50 | Hands-on B: the on/off problem |
| 11:35 | **Break (10 min)** |
| 11:45 | Talk C: validate with toys |
| 12:00 | Hands-on C: pulls, bias, coverage |
| 12:25 | Project: baseline fit |
| 12:55 | Wrap-up |

---

<!-- _class: lead -->
# Talk A
## What happens in `fitTo`

---

# From pdf to number

`pdf.fitTo(data)` does four things:

1. Builds the **negative log-likelihood** $-\ln L(\theta)$ (a function of the parameters)
2. Minimises it with **MINUIT**: `MIGRAD`
3. Computes the covariance matrix: `HESSE`
4. (On request) computes asymmetric errors: `MINOS`

$$-\ln L(\theta) = -\sum_i \ln f(x_i\,|\,\theta) \;\;[+\,\nu(\theta)\;\text{ if extended}]$$

Today we open the box and call each step ourselves, with `RooMinimizer`.

---

# MIGRAD, HESSE, MINOS

| Step | What it does | Output |
|---|---|---|
| **MIGRAD** | follows the gradient to the minimum (variable metric) | best-fit values, **EDM** |
| **HESSE** | second derivatives at the minimum: $V = H^{-1}$, $H_{ij}=\partial^2(-\ln L)/\partial\theta_i\partial\theta_j$ | symmetric errors, correlations |
| **MINOS** | scans $-\ln L$ until it rises by 0.5 for each parameter | asymmetric errors |

- HESSE assumes the likelihood is a **parabola** near the minimum
- MINOS makes no such assumption, but costs more fits
- If HESSE and MINOS disagree, the likelihood is not parabolic: **trust MINOS, and say so**

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

# When fits go wrong

| Symptom | Likely cause | Remedy |
|---|---|---|
| does not converge | bad start values, ranges too wide | start near the data, bound the ranges |
| huge errors, $|\rho|\to 1$ | two parameters do the same job | fix one, or reparametrise |
| parameter at limit | model or range wrong | check model, widen range if physical |
| fit works on some toys only | low statistics | toy study (Talk C) |

Reparametrising example: fit $\ln\tau$ instead of $\tau$, or use fractions between 0 and 1.

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

Notebook: `lab2/ex_A.ipynb`

---

<!-- _class: lead -->
# Talk B
## Likelihood intervals and nuisance parameters

---

# Likelihood-ratio intervals

For one parameter $\mu$ (Wilks' theorem, large samples):

$$-2\ln\frac{L(\mu)}{L(\hat\mu)} \;\sim\; \chi^2_1$$

| Confidence level | $\Delta(-\ln L)$ | $-2\Delta\ln L$ |
|---|---|---|
| 68.3 % | 0.5 | 1 |
| 95 % | 1.92 | 3.84 |

The interval is where the NLL curve is below the minimum **+ 0.5**.
It need not be symmetric: this is the MINOS interval.

---

# Nuisance parameters

A model has **parameters of interest** $\mu$ and **nuisance parameters** $\theta$ (background rate, resolution, efficiency…).

Two ways to draw the likelihood in $\mu$:

- **Slice**: fix $\theta$ at its best-fit value → too optimistic, ignores what we do not know
- **Profile**: for every $\mu$, re-fit $\theta$

$$\lambda(\mu)=\frac{L\big(\mu,\hat{\hat\theta}(\mu)\big)}{L(\hat\mu,\hat\theta)}, \qquad q(\mu) = -2\ln\lambda(\mu)$$

The profile curve is **wider** than the slice. The gap is the cost of the nuisance parameter.

---

# The on/off problem

Counting experiment with an **auxiliary measurement** of the background:

$$L(s,b) = \text{Pois}(n_{\rm on}\,|\,s+b)\;\times\;\text{Pois}(n_{\rm off}\,|\,\tau b)$$

- $n_{\rm on}$: events in the signal region; $n_{\rm off}$: events in the control region
- $\tau$: ratio of control to signal exposure (size of the control region)
- Best fit: $\hat b = n_{\rm off}/\tau$, $\hat s = n_{\rm on}-\hat b$
- The uncertainty on $b$ is **not an input**: it comes from the control region

This is the model behind “background $3.8\pm0.6$”. Constraint terms in Lab 3.

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

Notebook: `lab2/ex_B.ipynb`

---

<!-- _class: lead -->
# Talk C
## Validate with toys

---

# Why toys?

Errors from HESSE or MINOS are **approximations**. A toy study tests them:

1. Generate a dataset with known true parameters
2. Fit it
3. Save the result. Repeat 300–1000 times

**Pull** of a parameter:

$$\text{pull} = \frac{\hat\theta-\theta_{\rm true}}{\hat\sigma_\theta}$$

Healthy fit: pull **mean ≈ 0** (no bias), **RMS ≈ 1** (errors have the right size), and ≈ 68 % of toys inside $|{\rm pull}|<1$ (**coverage**).

---

# What goes wrong at low statistics

- Poisson fluctuations make the likelihood **non-parabolic**
- Parameters hit **boundaries** (e.g. $N_s \ge 0$): pulls are no longer Gaussian
- A small bias on the mean is common; a wrong RMS means **wrong errors**

Remedy: report **MINOS or profile intervals**, or run a Neyman construction with toys (Lab 3).

Always check the **fraction of failed fits**: toys that fail to converge are not “missing”, they are data about your model.

---

<!-- _class: lead -->
# Hands-on C
## Pulls, bias, coverage

---

# Exercise C (≈ 25 min)

Model: LHCb signal + background, extended.

1. Write the toy loop: **generate → fit → pull**, for $N_s=33$
2. Fill a histogram of the pulls. Mean, RMS, coverage
3. Repeat with $N_s=5$. What happens to the pulls? How many fits fail or sit at the boundary?

Notebook: `lab2/ex_C.ipynb`

---

# Project: baseline fit (30 min)

By the end of today, every team has:

- the data of its case **read in** (RDataFrame or numpy → RooFit)
- a first **model** and a first **fit**
- the **HESSE vs MINOS** errors on the main parameter
- a note in the notebook: *what would break this fit?*

Ask for help early. Use the break to ask.

---

# Wrap-up and homework (before Lab 3, in 2 weeks)

**Today you learned**
- what `fitTo` does: NLL, MIGRAD, HESSE, MINOS
- profile vs slice, and why nuisance parameters widen intervals
- toys, pulls, bias and coverage

**By Lab 3**
1. Finish the exercises (solutions after the deadline)
2. Project: add **one systematic** as a nuisance parameter
3. Read Cowan, Cranmer, Gross, Vitells, *Asymptotic formulae for likelihood-based tests of new physics* (arXiv:1007.1727), Sections 1–2

**Next time:** selection with TMVA, optimal cut, significance, RooStats.
