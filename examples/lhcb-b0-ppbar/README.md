# LHCb: $B^0 \to p\bar p$, the rarest $B^0$ decay ever observed

**Field:** flavour physics · **Used in:** Lab 1 (Exercises B and C), Lab 2 (Exercises A and C)

> In 2017 the LHCb experiment at CERN saw, for the first time, a $B^0$ meson decay into just a proton and an antiproton. The branching fraction is about $1.25\times10^{-8}$: **roughly one $B^0$ in eighty million** decays this way, which makes it the rarest $B^0$ decay observed to date. The signal is a small peak in the $p\bar p$ invariant mass, on top of a smooth background of random $p\bar p$ pairs. The same analysis also searched for the $B^0_s\to p\bar p$ decay: no signal was seen, and an upper limit of $1.5\times10^{-8}$ (90% CL) was set. How do you decide that a handful of events above a background is a discovery, and how many signal events are there?

**Reference figure.** Figure 1 of the paper: the $p\bar p$ invariant mass of the selected candidates, with the fit and its components (a peak at the $B^0$ mass, a peak at the $B^0_s$ mass, a combinatorial background). The exercise reproduces it. More on the result: [CERN Courier, “The rarest B⁰ decay ever observed”](https://cerncourier.com/a/the-rarest-b0-decay-ever-observed/).

**Real measurement.** LHCb Collaboration, “First observation of the rare purely baryonic decay B⁰→p p̄”, Phys. Rev. Lett. 119 (2017) 232001: [arXiv:1709.01156](https://arxiv.org/abs/1709.01156), [doi:10.1103/PhysRevLett.119.232001](https://doi.org/10.1103/PhysRevLett.119.232001). The data of this folder are a simplified version built for teaching.

**The statistical task.** A signal over a combinatorial background in one observable, the mass: fit a model with a peak and a background, count the signal events, estimate their uncertainty, and ask whether the peak is significant.

| File | Content |
|---|---|
| `data/rarest_b0_decay.dat` | 166 candidate masses $m(p\bar p)$ in MeV (5084–5541), one per line. Peaks near the $B^0$ mass (5280 MeV) and, weaker, the $B^0_s$ mass (5367 MeV) |
| `data/b0_invariant_mass.root` | TH1F `massaB0`: a simplified, broad B-meson mass peak centred near 5.37 GeV (the $B^0_s$ mass), 100 bins in 5–6 GeV, 760 entries. The names of the file and of the histogram are historical |

**What the course does.** Lab 1: Breit–Wigner and resolution on the mass peak (Exercise B), extended fit signal + background on the rare decay (Exercise C). Lab 2: errors, profile likelihood, toys and pulls.
