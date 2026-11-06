# RooFit: Python and C++ side by side

The notebooks of the course are in Python (PyROOT). If you prefer **C++**, you can do the same exercises in a macro: the RooFit objects are the same, only the syntax changes.

*This table has not been compiled against every ROOT version: if a line does not work, check the [RooFit tutorials](https://root.cern/doc/master/group__tutorial__roofit__main.html), which show every example in both languages.*

## How to run

| | Python | C++ |
|---|---|---|
| Where | a cell of a Jupyter notebook, or `python3 script.py` | a macro `macro.C`: `root -l -q macro.C` |
| Header | `import ROOT` | `#include "RooRealVar.h"`, `#include "RooGaussian.h"`, ... and `using namespace RooFit;` |
| Entry point | top-level code | `void macro() { ... }` |
| Options of a function | keyword arguments: `Save=True`, `PrintLevel=-1`, `Range="fit"` | `RooFit` helpers: `Save()`, `PrintLevel(-1)`, `Range("fit")` |
| Objects | normal objects | create objects on the stack (`RooRealVar x(...)`), and use `->` for pointers |

## The same program

| Task | Python | C++ |
|---|---|---|
| Observable | `x = ROOT.RooRealVar("x", "x", -10, 10)` | `RooRealVar x("x", "x", -10, 10);` |
| Parameter (start, min, max) | `mean = ROOT.RooRealVar("mean", "mean", 0, -10, 10)` | `RooRealVar mean("mean", "mean", 0, -10, 10);` |
| Constant | `tau.setConstant(True)` | `tau.setConstant(true);` |
| Pdf | `gauss = ROOT.RooGaussian("gauss", "gauss", x, mean, sigma)` | `RooGaussian gauss("gauss", "gauss", x, mean, sigma);` |
| Generate | `data = gauss.generate(ROOT.RooArgSet(x), 10000)` | `std::unique_ptr<RooDataSet> data{gauss.generate(RooArgSet(x), 10000)};` |
| Fit | `res = gauss.fitTo(data, Save=True, PrintLevel=-1)` | `auto res = gauss.fitTo(*data, Save(), PrintLevel(-1));` |
| Fit in a sub-range | `x.setRange("fit", -5, 5)`, then `fitTo(data, Range="fit")` | `x.setRange("fit", -5, 5);`, then `fitTo(*data, Range("fit"))` |
| Plot | `frame = x.frame()`, `data.plotOn(frame)`, `gauss.plotOn(frame)`, `frame.Draw()` | `RooPlot* frame = x.frame(); data->plotOn(frame); gauss.plotOn(frame); frame->Draw();` |
| One component | `model.plotOn(frame, Components="bkg")` | `model.plotOn(frame, Components("bkg"));` |
| Sum of pdfs (extended) | `ROOT.RooAddPdf("model", "model", ROOT.RooArgList(sig, bkg), ROOT.RooArgList(nsig, nbkg))` | `RooAddPdf model("model", "model", RooArgList(sig, bkg), RooArgList(nsig, nbkg));` |
| Sum of pdfs (fraction) | `ROOT.RooAddPdf("model", "model", ROOT.RooArgList(sig, bkg), ROOT.RooArgList(fsig))` | `RooAddPdf model("model", "model", RooArgList(sig, bkg), RooArgList(fsig));` |
| NLL | `nll = model.createNLL(data, ROOT.RooFit.Extended(True))` | `std::unique_ptr<RooAbsReal> nll{model.createNLL(*data, Extended(true))};` |
| Minimiser | `minim = ROOT.RooMinimizer(nll)`, `minim.minimize("Minuit2", "Migrad")`, `minim.hesse()` | `RooMinimizer minim(*nll); minim.minimize("Minuit2", "Migrad"); minim.hesse();` |
| Result | `res = minim.save()`, `res.status()` | `auto res = minim.save(); res->status();` |

## Two habits that save time

- In C++ `generate` returns a pointer: use `*data` when a function wants an object, and `data->` to call a method.
- The notebooks print `PASS` or `FAIL` with a `check(...)` function. In a macro, print the same numbers with `std::cout` and compare them to the values written in the notebook.
