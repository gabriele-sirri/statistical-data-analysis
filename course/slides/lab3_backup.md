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

# Constraint terms: how to model "$b_0\pm\sigma_b$"

**Given** an estimate $b_0\pm\sigma_b$ for the true unknown parameter $\beta$ (e.g. $3.8\pm0.6$), which constraint $c(b_0\,|\,\beta)$ do we put in the likelihood?

| | Constraint | Use when |
|---|---|---|
| **Poisson** | $\text{Pois}(n_{\rm off}\,\|\,\tau\beta)$ | this is exact, auxiliary measurements in control regions (not a proxy) |
| **Gamma** | $\propto\beta^{k-1}e^{-\tau\beta}$ | $\beta>0$, from counts: $k=n_{\rm off}+1$ |
| **Gaussian** | $\text{Gauss}(b_0\,\|\,\beta,\sigma_b)$ | large counts, $\sigma_b/b_0\lesssim0.2$ |
| **Log-normal** | $\text{LN}(b_0\,\|\,\beta,\kappa)$, $\ln\kappa\simeq\sigma_b/b_0$ | $\beta>0$, multiplicative (efficiency, lumi) |

- **Poisson = Gamma** in $\beta$ (exact): same shape, different normalisation
- **Poisson → Gaussian** for $n_{\rm off}\gtrsim30$: $b_0=n_{\rm off}/\tau$, $\sigma_b=\sqrt{n_{\rm off}}/\tau$
- **Log-normal → Gaussian** for $\sigma_b/b_0\to0$
- Only $b_0\pm\sigma_b$ known? Match moments: Gamma $k=(b_0/\sigma_b)^2$, rate $=b_0/\sigma_b^2$

*Poisson is a pmf in $n$; the others are compared as functions of $\beta$.*

---

![bg right:48% fit](img/constraints_comparison.png)

# Backup: the shapes for $\hat b=3.8$

Left: $n_{\rm off}=40$ ($\sigma_b=0.6$): all agree.  
Right: $n_{\rm off}=4$ ($\sigma_b=1.9$): Gaussian is  symmetric and leaks to $\beta<0$; Gamma and log-normal are skewed.

