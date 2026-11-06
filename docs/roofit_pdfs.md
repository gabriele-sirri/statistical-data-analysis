# RooFit pdfs: a quick list

All the pdfs of RooFit derive from the abstract class [`RooAbsPdf`](https://root.cern/doc/master/classRooAbsPdf.html). This is why they all behave in the same way: you can `fitTo` them, `generate` from them, and `plotOn` a frame. A pdf is **always normalised over the observable**, for any values of the parameters.

Each class name links to the reference page of ROOT, which also shows the formula. The arguments are given in the usual order: first the observable, then the parameters.

## Standard shapes

| Shape | Class | Arguments | Typical use |
|---|---|---|---|
| Gaussian | [`RooGaussian`](https://root.cern/doc/master/classRooGaussian.html) | `x, mean, sigma` | resolution, a narrow peak |
| Exponential | [`RooExponential`](https://root.cern/doc/master/classRooExponential.html) | `x, c` | falling background (`c < 0`), lifetimes |
| Polynomial | [`RooPolynomial`](https://root.cern/doc/master/classRooPolynomial.html) | `x, {a0, a1, ...}` | smooth background |
| Chebychev | [`RooChebychev`](https://root.cern/doc/master/classRooChebychev.html) | `x, {t0, t1, ...}` | smooth background, more stable than a polynomial |
| Bernstein | [`RooBernstein`](https://root.cern/doc/master/classRooBernstein.html) | `x, {c0, c1, ...}` | smooth background, positive by construction |
| Breit–Wigner | [`RooBreitWigner`](https://root.cern/doc/master/classRooBreitWigner.html) | `x, mean, width` | the natural line shape of a resonance |
| Voigtian (Breit–Wigner ⊗ Gaussian) | [`RooVoigtian`](https://root.cern/doc/master/classRooVoigtian.html) | `x, mean, width, sigma` | a resonance with detector resolution |
| Crystal Ball | [`RooCBShape`](https://root.cern/doc/master/classRooCBShape.html) | `x, mean, sigma, alpha, n` | a peak with a radiative tail |
| Landau | [`RooLandau`](https://root.cern/doc/master/classRooLandau.html) | `x, mean, sigma` | energy loss in thin layers |
| Argus | [`RooArgusBG`](https://root.cern/doc/master/classRooArgusBG.html) | `m, m0, c` | combinatorial background near a kinematic end-point |
| Log-normal | [`RooLognormal`](https://root.cern/doc/master/classRooLognormal.html) | `x, m0, k` | positive quantities, multiplicative uncertainties |
| Poisson | [`RooPoisson`](https://root.cern/doc/master/classRooPoisson.html) | `x, mean` | a number of events: counting experiments |
| Uniform | [`RooUniform`](https://root.cern/doc/master/classRooUniform.html) | `x` | a flat distribution |

## Pdfs from data or from a formula

| Class | Arguments | Use |
|---|---|---|
| [`RooHistPdf`](https://root.cern/doc/master/classRooHistPdf.html) | `x, dataHist` | a template from a histogram (simulation) |
| [`RooKeysPdf`](https://root.cern/doc/master/classRooKeysPdf.html) | `x, dataSet` | a smooth shape from a sample, by kernel estimation |
| [`RooGenericPdf`](https://root.cern/doc/master/classRooGenericPdf.html) | `formula, {variables}` | any formula: it is normalised for you |

## Building a pdf from other pdfs

| Class | What it does | Seen in |
|---|---|---|
| [`RooAddPdf`](https://root.cern/doc/master/classRooAddPdf.html) | sum of components: N coefficients for N pdfs (numbers of events, extended), or N−1 (fractions, shape only) | Lab 1 |
| [`RooProdPdf`](https://root.cern/doc/master/classRooProdPdf.html) | product of pdfs: independent observables, or a model times its constraints | Labs 2 and 3 |
| [`RooSimultaneous`](https://root.cern/doc/master/classRooSimultaneous.html) | one pdf per channel, fitted together | Lab 3 |
| [`RooExtendPdf`](https://root.cern/doc/master/classRooExtendPdf.html) | gives a number of events to a pdf: it becomes extended | |
| [`RooFFTConvPdf`](https://root.cern/doc/master/classRooFFTConvPdf.html) | convolution of two pdfs (for example a Landau and a Gaussian) | optional notebook |
| [`RooNumConvPdf`](https://root.cern/doc/master/classRooNumConvPdf.html) | the same, by brute-force numerical integration | |

## How to create one

In Python:

```python
x     = ROOT.RooRealVar("x", "x", 0, 10)
mean  = ROOT.RooRealVar("mean", "mean", 5, 0, 10)
sigma = ROOT.RooRealVar("sigma", "sigma", 0.5, 0.1, 2)
gauss = ROOT.RooGaussian("gauss", "gauss", x, mean, sigma)
```

With the **factory** syntax (a string, the leading `Roo` is dropped), in a `RooWorkspace`:

```python
w = ROOT.RooWorkspace("w")
w.factory("x[0, 10]")
w.factory("Gaussian::gauss(x, mean[5, 0, 10], sigma[0.5, 0.1, 2])")
```

## Where to look for more

The [reference page of `RooAbsPdf`](https://root.cern/doc/master/classRooAbsPdf.html) shows the inheritance diagram, with all the classes derived from it, and the [RooFit tutorials](https://root.cern/doc/master/group__tutorial__roofit__main.html) show most of them in C++ and in Python.
