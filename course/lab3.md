---
marp: true
theme: default
paginate: true
math: katex
header: "Statistical Data Analysis — Lab 3"
style: |
  section { font-size: 26px; }
  section.lead h1 { font-size: 46px; }
  code { font-size: 0.85em; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Lab 3 — Systematics and inference
**Statistical Data Analysis for Nuclear and Subnuclear Physics — Module 3**
G. Sirri · Hands-on sessions, 9:00–13:00

---

# Recap (10 minutes)

Discuss in pairs, then we compare:

1. Slice vs profile likelihood: which is wider, and why?
2. In the on/off problem, where does the uncertainty on the background come from?
3. What does a pull RMS of 1.3 tell you?
4. Does your project fit converge? Which parameter is hardest to fit?

---

# Today's schedule

| Time | |
|---|---|
| 9:00 | Recap and project check |
| 9:10 | Talk A: constraints vs auxiliary measurements |
| 9:30 | Hands-on A: on/off with a Gaussian constraint |
| 10:10 | **Break (15 min)** |
| 10:25 | Talk B: RooStats, significance, intervals |
| 10:45 | Hands-on B: ModelConfig and hypothesis test |
| 11:25 | **Break (10 min)** |
| 11:35 | Talk C: correlated systematics |
| 11:50 | Hands-on C: a real problem, OPERA |
| 12:30 | Project: add a systematic |
| 12:55 | Wrap-up |

---

<!-- _class: lead -->
# Talk A
## Constraints vs auxiliary measurements

---

# Two ways to model a systematic

A nuisance parameter $\theta$ is known only up to an uncertainty. Where does that knowledge come from?

| | Auxiliary measurement | Constraint term |
|---|---|---|
| What you write | the likelihood of the control data | a pdf for the *result* of that measurement |
| Example | $\text{Pois}(n_{\rm off}\,|\,\tau b)$ | $\text{Gauss}(b_0\,|\,b,\sigma_b)$ |
| You need | the control data | only the summary $b_0\pm\sigma_b$ |
| Typical use | a sideband, a control region you fit | “background $3.8\pm0.6$” from a publication or a separate group |

Both enter the likelihood **as a factor**. The second is an approximation of the first.

---

# From on/off to a Gaussian constraint

The control measurement gives $\hat b_0=n_{\rm off}/\tau$ with $\sigma_b=\sqrt{n_{\rm off}}/\tau$.

For large $n_{\rm off}$:

$$\text{Pois}(n_{\rm off}\,|\,\tau b)\;\approx\;\text{Gauss}(b_0\,|\,b,\sigma_b)$$

- Good for $n_{\rm off}\gtrsim 30$–$50$. Bad for few counts: the Gaussian is symmetric, allows $b<0$, and **overstates significance**
- Positive, multiplicative uncertainty (efficiency, luminosity)? use a **log-normal**
- Counts with a known $\tau$? the exact companion of the Poisson is a **Gamma**

Rule: **use the measurement when you have it; use a constraint when you only have its result.**

---

# The full model, and global observables

$$L(\mu,\vec\theta)=\underbrace{\text{Pois}\big(n\,|\,\nu(\mu,\vec\theta)\big)\prod_{i=1}^{n} f(x_i\,|\,\mu,\vec\theta)}_{\text{extended marked Poisson}}\;\times\;\underbrace{\prod_j c_j(a_j\,|\,\theta_j)}_{\text{constraints}}$$

- $a_j$ = result of the auxiliary measurement: a **global observable**
- In the **fit**: $a_j$ are constants. In **toys**: $a_j$ are re-thrown with the data (frequentist)
- RooFit: `createNLL(data, GlobalObservables(...))`; RooStats: `ModelConfig.SetGlobalObservables`

---

<!-- _class: lead -->
# Hands-on A
## On/off with a Gaussian constraint

---

# Exercise A (≈ 40 min)

Top-quark case: $n_{\rm on}=17$, $n_{\rm off}=40$, $\tau=10.53$, i.e. “background $3.8\pm0.6$”.

1. Build the model with a **Gaussian constraint** on $b$ (global observable $b_0=3.80$, $\sigma_b=0.60$)
2. Compute the **significance** $Z_0$ for both models (auxiliary Poisson, Gaussian): they should agree
3. Repeat with a poor control region ($n_{\rm off}=4$, $\tau=1.053$): which model is **too optimistic**?
4. When is it fine to use a constraint?

Notebook: `lab3/ex_A.ipynb`

---

<!-- _class: lead -->
# Talk B
## RooStats: significance and intervals

---

# Roles in RooStats

RooStats needs every element of the model to have a **role**:

| Element | In `ModelConfig` |
|---|---|
| the model | `SetPdf` |
| parameters of interest | `SetParametersOfInterest` |
| nuisance parameters | `SetNuisanceParameters` |
| observables | `SetObservables` |
| global observables | `SetGlobalObservables` |

Then **calculators** work on `(data, ModelConfig)`: `ProfileLikelihoodCalculator`, `AsymptoticCalculator`, `FrequentistCalculator`, `HypoTestInverter`…

---

# Hypothesis test and significance

Null hypothesis: no signal ($\mu=0$). Test statistic:

$$q_0=-2\ln\frac{L(0,\hat{\hat\theta})}{L(\hat\mu,\hat\theta)}\quad(\hat\mu\ge 0),\qquad Z=\sqrt{q_0},\qquad p=1-\Phi(Z)$$

| Claim | $Z$ | $p$ (one-sided) |
|---|---|---|
| evidence | 3 | $1.3\times10^{-3}$ |
| discovery | 5 | $2.9\times10^{-7}$ |

**Counting estimate, background known:** (Cowan, Cranmer, Gross, Vitells 2011)

$$Z_A=\sqrt{2\Big[(s+b)\ln\Big(1+\frac{s}{b}\Big)-s\Big]}\;\xrightarrow{s\ll b}\;\frac{s}{\sqrt b}$$

$s/\sqrt b$ **overstates** the significance when $s\gtrsim b$.

---

# Intervals and limits

- **Profile-likelihood interval** (what we used in Lab 2): the $\mu$ where $q(\mu)\le 1$
- **Upper limit** when the signal is not seen: $\text{CL}_s$ method, via `HypoTestInverter`
- Asymptotic formulae are fast and good for large samples; **toys** are needed when counts are small

Choose the calculator from the **question**:

| Question | Tool |
|---|---|
| how significant is the excess? | hypothesis test ($q_0$) |
| what is $\mu$ and its uncertainty? | profile-likelihood interval |
| nothing seen, how big can $\mu$ be? | $\text{CL}_s$ upper limit |

---

<!-- _class: lead -->
# Hands-on B
## ModelConfig and hypothesis test

---

# Exercise B (≈ 40 min)

Same top-quark model, now in a **workspace** with a `ModelConfig`.

1. Import the model, define POI, nuisance, observables and global observables
2. 68 % and 95 % **interval** on $s$ with `ProfileLikelihoodCalculator`
3. **Significance** and p-value of the background-only hypothesis
4. Compare with $Z_A$ (background known) and with $s/\sqrt b$. Which is closest to the RooStats result, and why?

Notebook: `lab3/ex_B.ipynb`

---

<!-- _class: lead -->
# Talk C
## Correlated systematics

---

# Systematics are correlated

A systematic rarely affects one number. A **source** (charm cross section, tagging efficiency, luminosity) moves several yields at once.

For $N$ channels, with a source $k$ moving channel $i$ by $v_{ik}$:

$$\Sigma_{ij}=\sum_k v_{ik}\,v_{jk}\qquad\text{(sources independent, each fully correlated across channels)}$$

- Independent errors per channel: $\Sigma$ **diagonal**
- A common source: off-diagonal terms. Ignoring them changes the **size** of the uncertainty on $\mu$

Question: **how much does it change the result?** Only a calculation tells.

---

# Diagonalise: independent nuisance parameters

Real symmetric $\Sigma=U\Lambda U^T$ ($\Lambda$ diagonal, eigenvalues $\lambda_k\ge 0$).

$$\vec\beta=\vec\beta_0+U\sqrt{\Lambda}\,\vec z,\qquad z_k\sim\mathcal N(0,1)\;\;\text{independent}$$

- One standard-normal nuisance parameter $z_k$ per **non-zero eigenvalue**
- **Rank** of $\Sigma$ = number of independent sources: 4 channels with 3 sources → 3 nuisance parameters, not 4
- Fully correlated errors in $N$ channels: **one** nuisance parameter

This is exactly what HistFactory, `pyhf` and CMS/ATLAS combinations do under the hood.

---

# A real problem: OPERA $\nu_\tau$ appearance

Final OPERA analysis (arXiv:1804.04912, Table III): 4 channels, 10 candidates.

| Channel | Bkg: charm | had. re-int. | large-$\mu$ scat. | Signal $\mu=1$ | Observed |
|---|---|---|---|---|---|
| $\tau\to1h$ | $0.15\pm0.03$ | $1.28\pm0.38$ | – | $2.96\pm0.59$ | 6 |
| $\tau\to3h$ | $0.44\pm0.09$ | $0.09\pm0.03$ | – | $1.83\pm0.37$ | 3 |
| $\tau\to\mu$ | $0.008\pm0.002$ | – | $0.016\pm0.008$ | $1.15\pm0.23$ | 1 |
| $\tau\to e$ | $0.035\pm0.007$ | – | – | $0.84\pm0.17$ | 0 |

- Every signal error is **≈ 20 %**. The 2015 paper lists the sources: model (10 %), $\theta_{23},\Delta m^2_{23}$ (10 %), tagging efficiency (15 %). They are common to all channels
- Background sources are shared across channels (charm in all four)

**Assumption in this exercise:** each source is fully correlated across the channels it touches. It is our modelling choice, not the collaboration's published treatment.

---

<!-- _class: lead -->
# Hands-on C
## OPERA with a covariance matrix

---

# Exercise C (≈ 40 min)

1. Build $\Sigma_b$ from the three background sources. **Diagonalise** it with `numpy`. Rank? Eigenvalues?
2. Build the RooFit model: 4 Poisson terms, $\beta_i=\beta_{0i}+\sum_k A_{ik}z_k$ with $A=U\sqrt\Lambda$, constraints $\text{Gauss}(0|z_k,1)$
3. Fit, compute the **significance** $Z_0$ and the 68 % interval on $\mu$
4. Add a **signal uncertainty** of 20 % per channel with correlation $\rho$ between channels. Scan $\rho=0,\,0.5,\,1$
5. How much does the interval on $\mu$ change? Does $Z_0$ change? Why?

Notebook: `lab3/ex_C.ipynb`

---

# Project: add a systematic (25 min)

Choose **one** systematic in your case and write it as a **nuisance parameter**:

- an auxiliary measurement, or a constraint term
- named, with a **source** and a size you can justify
- the effect on your main result: **with and without** it

Then decide: does it change your conclusion? That sentence goes into your showcase as the **caveat**.

---

# Wrap-up and homework (before Lab 4, in 2 weeks)

**Today you learned**
- constraint term vs auxiliary measurement, global observables
- RooStats: `ModelConfig`, hypothesis test, profile interval, $Z_A$
- correlated systematics: covariance, diagonalisation, rank

**By Lab 4**
1. Finish the exercises (solutions after the deadline)
2. Project: model with your systematic, result **with and without** it
3. Read the HistFactory section of the ROOT manual (`root.cern/manual/roofit/`) and look at `third_party/root-cpp-course-roofit/README.md`

**Next time:** HistFactory, the anatomy of a binned likelihood, and your showcase.
