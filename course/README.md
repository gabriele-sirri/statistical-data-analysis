# Team project

One analysis, built across the four labs, in teams of **2–3**.
Pick a case below by **Lab 2**, register in [`teams.md`](teams.md), and present in **Lab 4**.

## The cases

| # | Case | Field | Core question | Data (in `data/`) |
|---|---|---|---|---|
| 1 | LHCb $B^0 \to p\bar p$ | flavour | Is there a signal over the background? How many events? | `rarest_b0_decay.dat` |
| 2 | CMS $H \to 4\ell$ | collider | What is the signal strength and its significance? | `higgs_4l.dat`, `cms_m4l/` |
| 3 | CUORE-0 | nuclear | Is there a peak at the $^{130}$Te $Q$-value? If not, what limit? | `cuore0.dat` |
| 4 | Neutrino oscillations (IceCube *or* MINOS) | neutrino | What are the oscillation parameters and their intervals? | `icecube.dat` / `minos_2013_*.dat` |
| 5 | MAGIC gamma telescope | astroparticle | How well can we separate $\gamma$ from hadrons, and what significance follows? | `magic/magic04.data` |
| 6 | Top quark, on/off | collider | 17 events observed, a control region measures the background: what do we conclude? | numbers only (see below) |

Case 5 leans on TMVA (Lab 3). Case 6 needs no data file and is the lightest on I/O.

### Case cards

**1. LHCb $B^0 \to p\bar p$.** Invariant mass of 166 candidates (MeV). Peaks for $B^0$ and $B^0_s$ over a combinatorial exponential background.
*Watch out:* a peak that looks clear by eye can have a modest significance.
*Inspired by:* LHCb, “First observation of the rare purely baryonic decay $B^0 \to p\bar p$”.

**2. CMS $H \to 4\ell$.** Four-lepton mass, 70–181 GeV, with ZZ, Drell–Yan and $t\bar t$ contributions.
*Watch out:* background normalisations come from control ranges: they are nuisance parameters.

**3. CUORE-0.** Energy spectrum, 2470–2570 keV: a known $^{60}$Co sum peak (about 2507 keV) and a flat background. Search for a possible peak near 2527 keV and, if absent, an upper limit.
*Watch out:* with very few events, Gaussian approximations of the intervals fail.

**4. Neutrino oscillations.** Binned counts in zenith and energy (IceCube), or an energy spectrum with a simulation (MINOS). Fit the oscillation parameters.
*Watch out:* MINOS intervals and profile-likelihood intervals are equivalent only if the likelihood is regular. Check it.

**5. MAGIC.** 19 020 simulated events, ten image parameters, class $g$ (gamma) or $h$ (hadron).
*Watch out:* signal efficiency, background rejection and purity are three different things, and the class mix is not the real one.

**6. Top quark, on/off.** Counting experiment: `nobs = 17` in the signal region, `noff = 40` in a control region, with ratio of exposures `tau = 10.53`. The task: model, significance, interval.
*Watch out:* “background $3.8 \pm 0.6$” is itself a measurement. Model it as one.

> Your own case? Welcome, if you have data and a clear question. Talk to the instructor first.

## Milestones

| By | Everyone has |
|---|---|
| **Lab 2** | team registered, case chosen, data read, a first fit (or a first counting model) |
| **Lab 3** | errors studied (HESSE vs MINOS, profile likelihood), one systematic included, an interval or a p-value |
| **Lab 4** | HistFactory or workspace version of the model, final result, **3–5 minute showcase** |

Each lab leaves 40 minutes for the project. Use the weeks between labs.

## The showcase: one figure, one number, one caveat

- **One figure:** the plot that carries your result, readable from the back of the room.
- **One number:** your main result with its uncertainty or interval, and what it means.
- **One caveat:** the most important limitation. What does your result *not* tell us?

No slides are needed. Show the figure from your notebook.

## What to hand in

- Your notebook or macro, runnable top to bottom.
- A **one-page report**: question, model, result, caveat, and a section *“Who did what”*.
- Commits from every team member in the team repository (or your own fork).

The project is part of your work in the course and will be used for the lab question at the exam.
Each member should be able to explain any part of the analysis.

## Tools

RooFit and RooStats as in the labs; RDataFrame for reading and selecting data;
HistFactory in Lab 4. Python is the default; C++ is welcome.
