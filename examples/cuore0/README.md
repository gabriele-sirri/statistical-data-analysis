# CUORE-0: neutrinoless double-beta decay

**Field:** nuclear physics · **Used in:** extra case for self-study

**Question.** Is there a peak at the $^{130}$Te $Q$-value (2527.5 keV)? If not, what upper limit on the signal can you set?

**Source.** Simplified problem modelled on the first phase of the CUORE experiment.

**Real measurement.** CUORE Collaboration, “Search for Neutrinoless Double-Beta Decay of ¹³⁰Te with CUORE-0”, Phys. Rev. Lett. 115 (2015) 102502: [arXiv:1504.02454](https://arxiv.org/abs/1504.02454), [doi:10.1103/PhysRevLett.115.102502](https://doi.org/10.1103/PhysRevLett.115.102502).

| File | Content |
|---|---|
| `data/cuore0.dat` | 233 reconstructed energies in keV (2471–2569) |
| `data/cuore0.root` | the same data in ROOT format |

## Suggested path (self-study)

- **After Lab 2:** background (flat or exponential) + the known $^{60}$Co sum peak (about 2506 keV); baseline extended fit; HESSE vs MINOS.
- **After Lab 3:** add the possible peak at 2527.5 keV; one systematic (energy scale, resolution or efficiency) as a nuisance parameter; profile interval or upper limit (see `course/optional/upper_limit_cls.ipynb`).
- **After Lab 4:** binned version (HistFactory).
- *Caveat to watch:* very few events, Gaussian approximations of the intervals fail.

The original exercise text is `exercise-original.md` (draft extraction). Solutions: see the `solutions` branch, if published.
