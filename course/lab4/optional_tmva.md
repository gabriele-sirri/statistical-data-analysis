---
marp: true
theme: default
paginate: true
math: katex
header: "Optional — TMVA demo"
style: |
  section { font-size: 26px; }
  section.lead h1 { font-size: 46px; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Selecting events: the physicist's way
**Optional demo (30–45 min)** · TMVA, MAGIC data, Asimov significance

---

# The problem

Separate **signal** (gammas) from **background** (hadrons) with ten image parameters.
A cut on one variable is not enough: combine them.

- **Rectangular cuts**: simple, transparent
- **Fisher**: a linear combination
- **BDT**: boosted decision trees, the workhorse of HEP

TMVA trains, tests and compares them, and plots the result automatically.

---

# Vocabulary: machine learning vs physics

| Machine learning | Physics |
|---|---|
| recall, true-positive rate | **signal efficiency** $\varepsilon_s$ |
| false-positive rate | **background efficiency** $\varepsilon_b$ |
| 1 − false-positive rate | **background rejection** |
| precision | **purity** $s/(s+b)$ |
| accuracy | not used |

**Efficiencies do not depend on the S/B ratio. Purity does.** That is why we quote $(\varepsilon_s,\varepsilon_b)$ and the expected yields separately.

---

# The ROC curve and the working point

- ROC: background rejection vs signal efficiency, one point per **cut** on the response
- Different cuts are different **working points** of the same classifier
- Which point is “best”? **It depends on what you want to measure**

Choose the cut by optimising the **final significance**, not the accuracy.

---

# The naive figure of merit

$$Z_{\rm naive}=\frac{s}{\sqrt{b}}$$

- Valid for $s\ll b$ and large $b$
- Rewards tight cuts as $\varepsilon_b\to0$: **pathological** at low background
- Always overestimates the true significance

Example: $s=3$, $b=0.1$ gives $s/\sqrt b\approx 9.5$ from three events.

---

# The Asimov significance

From the profile-likelihood ratio, with $b$ known (Cowan, Cranmer, Gross, Vitells 2011):

$$Z_A=\sqrt{2\Big[(s+b)\ln\Big(1+\frac{s}{b}\Big)-s\Big]}\;\le\;\frac{s}{\sqrt b}$$

- Behaves for small $b$: the optimal cut stays sensible
- Reduces to $s/\sqrt b$ for $s\ll b$
- Ignores the uncertainty on $b$ (Lab 3: include it as a nuisance parameter)

---

# What the notebook does

1. Convert the MAGIC CSV to ROOT trees (RDataFrame `FromNumpy`, `Snapshot`)
2. Train BDT and Fisher with TMVA (`Factory`, `DataLoader`)
3. Read the test tree: classifier response for signal and background
4. Scan the cut: $\varepsilon_s$, $\varepsilon_b$, purity, $s/\sqrt b$, $Z_A$
5. Find the optimal cut for two sets of expected yields: **it moves**

Notebook: `optional/tmva_magic_demo.ipynb`

---

# Take-home messages

- Translate: recall → signal efficiency, precision → purity
- Optimise the **physics figure of merit**, with expected yields, not the ML score
- Optimising on the test sample and measuring on the same sample is a bias: use independent samples
- The efficiency is a **systematic**: model it as a nuisance parameter (Lab 3)

**Reference:** arXiv:1007.1727
