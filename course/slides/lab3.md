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

# Recap (5 minutes)

Discuss in pairs, then we compare:

1. Slice vs profile likelihood: which is wider, and why?
2. In the on/off problem, where does the uncertainty on the background come from?
3. What does a pull RMS of 1.3 tell you?
4. Which two Lab 2 notebooks did you submit? Did the toy study run for you?

---

# Recap: answers

1. A **slice** keeps the nuisance parameters fixed. A **profile** re-fits them at every point, so their uncertainty adds: **the profile is wider**
2. From the **control region**: $\sigma_b=\sqrt{n_{\rm off}}/\tau$, the Poisson uncertainty of the control count
3. RMS $>1$: **the uncertainty is underestimated** (1.3 means about 30 % too small)
4. The hardest cells: we open them now

---

# Solutions of Lab 2 (15 minutes)

The solutions are in the `solutions` branch: [`solutions/lab2/`](../../solutions/lab2), from today.

- **[A](../../solutions/lab2/ex_A_solution.ipynb)**: `HESSE`, `MINOS` and the contour (A1, A2, A5)
- **[B](../../solutions/lab2/ex_B_solution.ipynb)**: the on/off model, and the profile interval versus `MINOS` (B1, B2)
- **[C](../../solutions/lab2/ex_C_solution.ipynb)**: the toy study, the pulls and the failed fits (C1, C2)

---

# Today's schedule

| Time | |
|---|---|
| 9:00 | Recap and Lab 2 questions |
| 9:20 | Talk A: constraints vs auxiliary measurements |
| 9:40 | Hands-on A: on/off with a Gaussian constraint |
| 10:20 | **Break (15 min)** |
| 10:35 | Talk B: RooStats, significance, intervals |
| 10:55 | Hands-on B: ModelConfig and hypothesis test |
| 11:35 | **Break (10 min)** |
| 11:45 | Talk C: correlated systematics |
| 12:00 | Hands-on C: a real problem, OPERA |
| 12:40 | Open lab: finish a notebook, ask questions |
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

![w:640](img/poisson_vs_gauss.png)

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

Notebook: [`course/lab3/ex_A.ipynb`](../lab3/ex_A.ipynb)


---

### Key Takeaways from Hands-on A

**Statistics**
- A **constraint** is the pdf of an **auxiliary measurement**: a Gaussian of $b_0$ around $b$. The measurement $b_0$ is a number, not a data event
- A **poor control region** means a **large** uncertainty on $b$, and a **lower** significance

**RooFit**
- `RooGaussian(b0, b, sigma_b)` is the constraint, multiplied by the model with `RooProdPdf`
- `createNLL(data, GlobalObservables(b0))` tells the fit that $b_0$ is a **global observable**, not a free variable
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

Null hypothesis: no signal ($\mu=0$). Test statistic ($\hat{\hat\theta}$: the nuisance parameters re-fitted with $\mu=0$ fixed, the *profile* of Lab 2):

$$q_0=-2\ln\frac{L(0,\hat{\hat\theta})}{L(\hat\mu,\hat\theta)}\quad(\hat\mu\ge 0),\qquad Z=\sqrt{q_0},\qquad p=1-\Phi(Z)$$

| Claim | $Z$ | $p$ (one-sided) |
|---|---|---|
| evidence | 3 | $1.3\times10^{-3}$ |
| discovery | 5 | $2.9\times10^{-7}$ |

**Counting estimate, background known:** ([Cowan, Cranmer, Gross, Vitells 2011](https://arxiv.org/abs/1007.1727))

$$Z_A=\sqrt{2\Big[(s+b)\ln\Big(1+\frac{s}{b}\Big)-s\Big]}\;\xrightarrow{s\ll b}\;\frac{s}{\sqrt b}$$

$s/\sqrt b$ **overstates** the significance when $s\gtrsim b$.

---

# Intervals and limits

- **Profile-likelihood interval** (what we used in Lab 2): the $\mu$ where $q(\mu)\le 1$, with $q(\mu)=-2\ln\lambda(\mu)$: the same ratio as $q_0$, with $\mu$ fixed at the tested value
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

Notebook: [`course/lab3/ex_B.ipynb`](../lab3/ex_B.ipynb)


---

### Key Takeaways from Hands-on B

**Statistics**
- A **discovery** is a test of the background-only hypothesis: a **p-value**, expressed in sigma. An **upper limit** is a different question (CL$_s$: see the optional notebook)
- $s/\sqrt b$ is a rough guide. $Z_A$ ignores the uncertainty on $b$

**RooFit and RooStats**
- `RooWorkspace` holds the model and the data. `ModelConfig` gives the **roles**: pdf, parameter of interest, nuisance parameters, observables, global observables
- A **calculator** takes a `ModelConfig`: `ProfileLikelihoodCalculator` gives the **intervals** (B2) and the **p-value** of the background-only hypothesis (B3)
---

<!-- _class: lead -->
# Talk C
## Correlated systematics

---

# Systematics are correlated

A systematic rarely affects one number. A **source** (charm cross section, tagging efficiency, luminosity) moves several expected numbers of events (yields) at once.

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

Final OPERA analysis ([arXiv:1804.04912](https://arxiv.org/abs/1804.04912), Table III): 4 channels, 10 candidates.

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

Notebook: [`course/lab3/ex_C.ipynb`](../lab3/ex_C.ipynb)


---

### Key Takeaways from Hands-on C

**Statistics**
- Correlated uncertainties: the **covariance matrix** $\Sigma$. We write $\Sigma = A A^T$ and give **one nuisance parameter per independent source**
- The **number of nuisance parameters** is the **rank** of $\Sigma$

**RooFit**
- `numpy.linalg.eigh` gives the eigenvalues and eigenvectors: keep the non-zero ones, $A=U\sqrt{w}$
- Each channel gets a `RooFormulaVar` with the nuisance parameters $\theta_k$ and a `RooGaussian` constraint for each
---

# Open lab (15 min)

Finish a notebook, or start the one you have not done. The three of today are independent.

For every systematic you write, ask three questions:

- is it an **auxiliary measurement** or a **constraint term**?
- what is its **source**, and what size can you justify?
- how much does the result change **with and without** it?

If the answer to the last one is "almost nothing", say it in your notebook: that is a result.

---

# Wrap-up and submission (before Lab 4, in 2 weeks)

**Today you learned**
- constraint term vs auxiliary measurement, global observables
- RooStats: `ModelConfig`, hypothesis test, profile interval, $Z_A$
- correlated systematics: covariance, diagonalisation, rank

**By Lab 4**
1. Submit **2 of the 3** notebooks of [`lab3/`](../lab3/) (A, B, C: your choice) on **Virtuale**, every check `PASS`
2. We look at the solutions of all three at the beginning of Lab 4
3. Read the HistFactory section of the ROOT manual ([`root.cern/manual/roofit/`](https://root.cern/manual/roofit/)) and look at [`third_party/root-cpp-course-roofit/README.md`](../../third_party/root-cpp-course-roofit/README.md)

**Next time:** HistFactory, the anatomy of a binned likelihood, RDataFrame `Vary`, and a TMVA demo.
