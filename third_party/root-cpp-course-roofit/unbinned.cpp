// unbinned.cpp : Part 1 of the course: the *analytic-shape* fit.
//
// The same data.root NTuple that Part 2 (histfactory.cpp) analyses with templates is
// here fitted unbinned in the mass dimension. This works because we assume
// the shapes to be analytically tractable: a Gaussian signal peak at 125 GeV
// on an exponential continuum. (Part 2 is the answer to: "and if they
// aren't?")
//
// Pipeline:
//   1. RDataFrame applies the same event selection as the binned analysis
//      (pt > 20 GeV, |eta| < 2.2) and hands the surviving mass values to
//      RooFit as an unbinned RooDataSet.
//   2. Extended maximum-likelihood fit: model = Ns*sig + Nb*bkg with the
//      yields as fit parameters, peak position and background slope floating.
//   3. Closure: fitted signal yield vs. the expectation from physics.h.

#include <cmath>
#include <iostream>

#include "ROOT/RDataFrame.hxx"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TCanvas.h"

#include "physics.h"

void unbinned() {
  // --- 1. selected masses out of RDataFrame -------------------------------
  ROOT::RDataFrame dat("data", "data.root");
  auto masses =
      dat.Filter([](double pt) { return pt > 20.; }, {"pt"})
          .Filter([](double eta) { return std::abs(eta) < 2.2; }, {"eta"})
          .Take<double>("mass");

  RooRealVar m("mass", "m", toy::kMassMin, toy::kMassMax, "GeV");
  RooDataSet ds("ds", "selected data", {m});
  for (double v : *masses) {
    m.setVal(v);
    ds.add({m});
  }
  std::cout << "selected " << ds.numEntries() << " events\n";

  // --- 2. analytic model: Gaussian peak + exponential continuum ------------
  // The signal position floats (a classic), the width is assumed known from
  // resolution studies.
  RooRealVar mean("mean", "peak position", toy::kMass0 - 0.5, 120., 130.);
  RooRealVar width("width", "peak width", toy::kMassSigma, 0.01 * toy::kMassSigma, 100 * toy::kMassSigma);
  width.setConstant(true);
  RooGaussian sig("sig", "signal", m, mean, width);

  // RooExponential parametrizes pdf(m) ~ exp(slope*m), so slope = -1/25 GeV^-1
  RooRealVar slope("slope", "background slope", -1. / toy::kMassSlope, -0.08,
                   0.);
  // TODO: define bkg function here (exponential):

  // Extended model: the yields themselves are fit parameters. Poisson
  // fluctuations of the total event count are then part of the likelihood.
  RooRealVar nsig("nsig", "signal yield", 0.8 * ds.numEntries(), 0.,
                  2. * ds.numEntries());
  RooRealVar nbkg("nbkg", "background yield", 0.8 * ds.numEntries(), 0.,
                  2. * ds.numEntries());

  // TODO: once the background component is defined, enable it in the RooAddPdf
  RooAddPdf model("model", "sig+bkg",
          {sig /*, bkg*/},
          {nsig /*, nbkg*/}
          );

  std::unique_ptr<RooFitResult> res(model.fitTo(
      ds, RooFit::Save(), RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1)));

  // --- 3. closure: what did we inject? -------------------------------------
  // Expected signal yield after selection, straight from physics.h:
  const double sigPtSf =
      (std::exp(-0.4) * 1.4 - std::exp(-4.) * 5.) / toy::sig_pt_norm();
  const double sigEtaSf = std::erf(2.2 / (0.5 * std::sqrt(2.)));
  const double expectSig = toy::kNSig * sigPtSf * sigEtaSf;
  // truth slope in RooExponential convention
  const double slopeTrue = -1. / toy::kMassSlope;

  std::cout << "\n===== unbinned fit summary =====\n"
            << "  nsig  = " << nsig.getVal() << " +/- " << nsig.getError()
            << "   (expect ~" << expectSig << ")\n"
            << "  nbkg  = " << nbkg.getVal() << " +/- " << nbkg.getError()
            << "\n"
            << "  mean  = " << mean.getVal() << " +/- " << mean.getError()
            << "   (true: " << toy::kMass0 << ")\n"
            << "  slope = " << slope.getVal() << " +/- " << slope.getError()
            << "   (true: " << slopeTrue << ")\n";

  // --- plot ----------------------------------------------------------------
  TCanvas c;
  RooPlot *frame =
      m.frame(RooFit::Title("unbinned mass fit"), RooFit::Bins(30));
  ds.plotOn(frame);
  model.plotOn(frame);
  model.plotOn(frame, RooFit::Components("bkg"), RooFit::LineStyle(kDashed),
               RooFit::LineColor(kRed));
  frame->Draw();
  c.SaveAs("unbinned_fit.pdf");
  std::cout << "wrote unbinned_fit.pdf\n";
}

int main() {
  unbinned();
  return 0;
}
