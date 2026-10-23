---
marp: true
theme: default
paginate: true
math: katex
header: "Statistical Data Analysis — Lab 1 (backup slides)"
style: |
  section { font-size: 24px; }
  section.lead h1 { font-size: 46px; }
  code { font-size: 0.85em; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Lab 1 — Backup slides
## Not shown in class: for questions and for reference

---

# Backup: binned likelihood and $\chi^2$

A histogram has expected $\nu_j(\theta)$ and observed $n_j$ in bin $j$. Three ways to fit it:

| Name | Function to minimise |
|---|---|
| Pearson $\chi^2$ | $\sum_j (n_j-\nu_j)^2/\nu_j$ |
| Neyman $\chi^2$ | $\sum_j (n_j-\nu_j)^2/n_j$ |
| **Poisson likelihood** | $-2\ln\lambda = 2\sum_j\big[\nu_j - n_j + n_j\ln(n_j/\nu_j)\big]$ |

- **Large numbers** (central limit theorem): for large $\nu_j$ a Poisson becomes a Gaussian with mean and variance $\nu_j$, and the three agree (rule of thumb: $\nu_j \gtrsim 10$ in every bin)
- **Low counts**: Neyman is undefined for empty bins. Both $\chi^2$ are **biased**. The Poisson likelihood is exact
- **Invariance**: the ML estimate does not change if you reparametrise $\theta \to g(\theta)$
- **Wilks**: $-2\ln\lambda$ is asymptotically $\chi^2$-distributed, so the Poisson likelihood also gives a goodness of fit

---

# Backup: binned likelihood and $\chi^2$, where to read more

- S. Baker and R. D. Cousins, *Clarification of the use of chi-square and likelihood functions in fits to histograms*, Nucl. Instrum. Methods 221 (1984) 437
- G. Cowan, K. Cranmer, E. Gross, O. Vitells, *Asymptotic formulae for likelihood-based tests of new physics*, [arXiv:1007.1727](https://arxiv.org/abs/1007.1727) (Wilks' theorem and the Asimov dataset)
- ROOT tutorials: [`rf602_chi2fit`](https://root.cern/doc/master/rf602__chi2fit_8py.html), [`rf614_binned_fit_problems`](https://root.cern/doc/master/rf614__binned__fit__problems_8py.html)
