# RooFit hands-on course: one toy, three ways to fit it

A 1-hour guided session built around a single toy experiment shared by all
three parts. Every fit runs on the **same data** (`data.root`), produced by
one weighted MC simulator (`physics.h` + `make_toys.cpp`).

The toy physics:

| component | eta | phi | pt | mass |
|---|---|---|---|---|
| signal (Ns = 2000 at µ = 1) | Gauss(0, 0.5) | 1 + 0.4·cos(2φ) | Γ(k=2, 50 GeV) | **Gauss(125, 2)** |
| background (Nb = 20000) | exp(−θ·\|η\|), θ nuisance | flat | exp(−pt/20) | exp(−m/25) |

The MC is *weighted*: events are drawn once from a fixed proposal
distribution, and the physics parameters µ (signal strength) and θ (background
η slope) enter **only through per-event weights**, so we only need to reweight the sample, never regenerate.
This is very common for realistic anlyses, where nuisance parameters are often treated as MC weight variations (like in this toy example), or per-object scale factors for reconstruction uncertainties, e.g. for electron reconstruction efficiency.
The "real data" are drawn from the "truth"
(µ_true = 1, θ_true = 1.3, mass peak at 125 GeV).

## Setup

```
./run.sh          # everything, or step by step:
root -b -q make_toys.cpp   # simulator NTuples: sim.root, data.root
root -b -q unbinned.cpp    # Part 1: unbinned analytic-shape fit
root -b -q analysis.cpp    # Part 2a: RDF analysis + Vary templates
root -b -q histfactory.cpp # Part 2b: HistFactory fit
root -b -q likelihood.cpp  # Part 3: likelihood anatomy
```

File tour: `physics.h` (the "theory": densities, samplers, weight functions,
all parameters), `make_toys.cpp` (NTuple producer), then one macro per part.

## Part 1: Analytic shapes and unbinned fit

If we *know* the functional forms (signal a Gaussian, background an
exponential) we don't need templates at all. RDataFrame applies the
selection (pt > 20, |η| < 2.2), the surviving masses go into a
`RooDataSet`, and an extended maximum-likelihood fit
`model = nsig·Gauss(m) + nbkg·Exp(m)` measures the yields with the peak
position and background slope floating.

This is implemented in `unbinned.cpp`. Please run that code and answer the following questions:

- Complete the fit macro: the background is still missing in the model. Please add a RooFit pdf that corresponds to the exponential background with the `slope` parameter, and add it as a component for the final RooAddPdf
- Extended ML: the yields *are* fit parameters! The Poisson term for the
  total count is part of the likelihood. Where is the information on nsig
  actually coming from?
- Check the summary printout: nsig = ? vs. the expectation computed from
  `physics.h`. What consistency do you expect?
- The mass resolution (peak width) was fixed "from a resolution study".
  But does it have to be like that? Float it and watch what happens to σ(nsig) and to the
  correlations (`res->correlationMatrix()`). How do you think these resolution nuisance parameters are dealt with in real analyses?

## Part 2: Binned template fit (`make_toys.cpp`, `analysis.cpp`, `histfactory.cpp`)

### The motivating question

> **What if the background had no tractable analytic shape?**
> Detector effects, higher-order QCD, an MC-only truth... You can't write
> b(m; θ) down. But you *can* simulate events and reweight them. That's what
> out toy simulator can already do, so here's what we do: histogram the simulation (templates),
> and build a likelihood over binned Poisson counts. That's HistFactory.

### Intractable shapes: templates with HistFactory

Here is what we do: instead of fitting the `nsig` parameter as before, we'll with the so called "signal strength" parameter µ that is the ratio between `nsig` and the expected number of signal events from the simulator model.

The other parameters like `mean` ,`slope`, or `nbkg` are not needed this time, because the expected shapes are fixed by the simulator. However, the simulator is not perfect: it has tune parameters θ that are now our new nuisance parameters.

`make_toys.cpp` → `analysis.cpp` → `histfactory.cpp`

1. `make_toys.cpp`: the weighted simulator. Trace where µ and θ appear
   (weights only). Check `sum(sig_w)`/`sum(bkg_w)` against expectation and
   discuss what sets their uncertainty.
2. `analysis.cpp`: RDataFrame analysis in |η| — central signal bump vs.
   θ-tilted background slope. **Vary** produces the θ up/down templates on
   top of the nominal histograms in a *single* event loop, from weights
   recomputed on the fly. µ is a pure normalization, so it needs no
   template variation.
3. `histfactory.cpp`: programmatic HistFactory: signal template × NormFactor `mu`
   (POI), background template with a `HistoSys` built from the Vary
   histograms, MC statistical errors activated. Fit; read off
   θ̂ = θ_nom + α_θ·Δθ. Against true 1.3: does it close?

**Exercise**:

- Re-implement the `histfactory.cpp` in "basic" RooFit without HistFactory.
  It's fine if you don't consider the MC stat errors (gamma parmters). Hint: use the [`PiecewiseInterpolation`](https://root.cern/doc/master/classPiecewiseInterpolation.html) class for the template morphing. How close can you get to the same fit result that you get with the HistFactory model?

## Part 3: Understanding the profile likelihood

`likelihood.cpp` (loads `results/meas_combined_meas_model.root`)

Same fit result as Part 2, now dissected. The macro draws, for µ and
α_θ, the ΔNLL *slice* (other parameters frozen) and the ΔNLL *profile*
(others re-minimized at each point), plus the 2D (µ, α_θ) contours:

**Exercises**:

- The contour plot has x and y axis ranges that are too large to be appropriate
  for this plot. Can you improve this using `TAxis::SetRangeUser()`?
