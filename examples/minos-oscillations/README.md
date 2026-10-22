# MINOS: $\nu_\mu$ disappearance in the Far Detector

**Field:** neutrino physics · **Used in:** extra case for self-study

**Question.** What are $\Delta m^2$ and $\sin^2 2\theta$ from the observed energy spectrum, compared with the unoscillated simulation?

**Source.** Inspired by Figures 1–2 of MINOS, “Measurement of Neutrino and Antineutrino Oscillations Using Beam and Atmospheric Data in MINOS”, arXiv:1304.6335.

**Real measurement.** MINOS Collaboration, “Measurement of Neutrino and Antineutrino Oscillations Using Beam and Atmospheric Data in MINOS”: [arXiv:1304.6335](https://arxiv.org/abs/1304.6335).

| File | Content |
|---|---|
| `data/minos_2013_data.dat` | 3470 neutrino energies in GeV (0.54–13.99) |
| `data/minos_2013_mc.dat` | 48 295 simulated unoscillated events (0.50–14.00 GeV) |

## Suggested path (self-study)

- **After Lab 2:** two-flavour survival probability, template from the simulation, baseline fit; HESSE vs MINOS; the NLL contour in ($\Delta m^2$, $\sin^2 2\theta$).
- **After Lab 3:** a normalisation uncertainty on the flux, as a constraint term; its effect on the contour.
- **After Lab 4:** binned model with HistFactory.
- *Caveat to watch:* the fit can have two minima in $\Delta m^2$; scan before trusting MIGRAD.

The original exercise text is `exercise-original.md` (draft extraction). Solutions: see the `solutions` branch, if published.
