---
marp: true
theme: default
paginate: true
math: katex
header: "Statistical Data Analysis — Lab 2 (backup slides)"
style: |
  section { font-size: 24px; }
  section.lead h1 { font-size: 46px; }
  code { font-size: 0.85em; }
  table { font-size: 0.8em; }
---

<!-- _class: lead -->
<!-- _paginate: false -->
# Lab 2 — Backup slides
## Not shown in class: for questions and for reference

---

# Backup: why MINUIT?

- **MINUIT** is a minimisation library written at CERN: F. James and M. Roos, *Comput. Phys. Commun.* 10 (1975) 343. **Minuit2** is the C++ version, included in ROOT
- It does more than finding a minimum:
  - **MIGRAD**: a variable-metric minimiser, with a stopping criterion (the EDM)
  - **HESSE**: the covariance matrix from the second derivatives
  - **MINOS**: asymmetric errors from the likelihood scan
  - parameter **limits**, and an error definition for likelihood fits ($-\ln L$ rises by 0.5)
- It is the standard of particle physics: **RooFit**, `iminuit` (the Python wrapper) and the fits of the experiments use the same algorithms, so results are **comparable and reproducible**

---

# Backup: the risks of using another minimiser

Alternatives exist: `scipy.optimize` (BFGS, L-BFGS-B, Nelder–Mead), fits with automatic differentiation (JAX, zfit), and `iminuit`, which **is** MINUIT from Python.

Risks of a generic minimiser:

- **Errors**: finding the minimum is not enough. You need a reliable **covariance matrix** and the **right error definition** (0.5 for $-\ln L$, 1 for $\chi^2$). The inverse Hessian of a quasi-Newton method is an approximation and can be wrong
- **No MINOS**: no asymmetric errors, so no check of the parabolic assumption
- **Convergence**: different stopping criteria. "Converged" may not mean "at the minimum": check the EDM
- **Limits**: parameters at a boundary are treated differently, and the errors there are not reliable
- **Comparison**: harder to compare with published results

And MINUIT is **not magic**: it can stop in a local minimum or at a limit. Always read the **status**, the **EDM** and `covQual`.
