// analysis.cpp : RDataFrame analysis over the toy NTuples.
//
//  * Event transformations: |eta| folding, azimuth folded into [0, pi), then
//    a signal-enriching selection: pt > 20 GeV and |eta| < 2.2.
//  * Analysis observable: std::abs(eta) = |eta| in 8 bins of [0, 2.2]. The
//  signal is a
//    central bump; the background falls as exp(-theta * std::abs(eta)), so the
//    bin-to- bin shape of the background measures theta.
//  * One event loop computes the nominal histograms AND the up/down weight
//    variation of the background nuisance parameter via RDF's Vary:
//      bkg_w -> theta   up/down  ("bkg_shape:theta_up", "bkg_shape:theta_down")
//    The varied weights are recomputed from the event kinematics alone — the
//    same reweighting the simulator itself uses. The signal strength mu is a
//    pure normalization parameter and needs no template variation.
//
//  Output: hists.root with h_sig, h_bkg, h_bkg_theta_up/down, h_data.

#include <cmath>
#include <iostream>

#include "ROOT/RDFHelpers.hxx" // Experimental::VariationsFor
#include "ROOT/RDataFrame.hxx"
#include "TFile.h"

#include "physics.h"

void analysis() {
  // --- MC loop: nominal + varied histograms in a single pass -------------
  ROOT::RDataFrame sim("sim", "sim.root");

  auto mc =
      sim
          // |eta| is the natural variable for this eta-symmetric
          // problem; folding doubles the per-bin stats
          .Define("aeta", [](double eta) { return std::fabs(eta); }, {"eta"})
          .Define("phi_fold",
                  [](double phi) { return phi < 0. ? phi + toy::kPi : phi; },
                  {"phi"})
          .Filter([](double pt) { return pt > 20.; }, {"pt"}, "pt > 20 GeV")
          .Filter([](double eta) { return std::abs(eta) < 2.2; }, {"eta"},
                  "|eta| < 2.2")
          // up/down variation of the theta physics weight, computed
          // from kinematics only (theta acts on weights, nothing
          // else — re-running the sim is never needed)
          .Vary(
              "bkg_w",
              [](double eta, double phi, double pt, double mass) {
                return ROOT::RVec<double>{
                    toy::bkg_weight(eta, phi, pt, mass,
                                    toy::kThetaNom + toy::kThetaDelta),
                    toy::bkg_weight(eta, phi, pt, mass,
                                    toy::kThetaNom - toy::kThetaDelta)};
              },
              {"eta", "phi", "pt", "mass"}, {"theta_up", "theta_down"},
              "bkg_shape");

  constexpr int kNBins = 8;
  auto hSig = mc.Histo1D(
      ROOT::RDF::TH1DModel{"h_sig", ";|#eta|;events", kNBins, 0., 2.2}, "aeta",
      "sig_w");
  auto hBkg = mc.Histo1D(
      ROOT::RDF::TH1DModel{"h_bkg", ";|#eta|;events", kNBins, 0., 2.2}, "aeta",
      "bkg_w");

  auto vBkg = ROOT::RDF::Experimental::VariationsFor(hBkg);

  // --- data loop: same selections, unweighted -----------------------------
  ROOT::RDataFrame dat("data", "data.root");
  auto hData =
      dat.Define("aeta", [](double eta) { return std::fabs(eta); }, {"eta"})
          .Filter([](double pt) { return pt > 20.; }, {"pt"}, "pt > 20 GeV")
          .Filter([](double aeta) { return aeta < 2.2; }, {"aeta"},
                  "|eta| < 2.2")
          .Histo1D(
              ROOT::RDF::TH1DModel{"h_data", ";|#eta|;events", kNBins, 0., 2.2},
              "aeta");

  // --- persist ------------------------------------------------------------
  TFile out("hists.root", "RECREATE");
  hSig->Write("h_sig");
  vBkg["nominal"].Write("h_bkg");
  vBkg["bkg_shape:theta_up"].Write("h_bkg_theta_up");
  vBkg["bkg_shape:theta_down"].Write("h_bkg_theta_down");
  hData->Write("h_data");

  std::cout << "\nhists.root written. Yields after selection:\n"
            << "  signal       : " << hSig->Integral() << "\n"
            << "  background   : " << vBkg["nominal"].Integral() << "\n"
            << "  bkg theta_up : " << vBkg["bkg_shape:theta_up"].Integral()
            << "\n"
            << "  bkg theta_dn : " << vBkg["bkg_shape:theta_down"].Integral()
            << "\n"
            << "  data         : " << hData->Integral() << "\n";

  std::cout << "\nCut flow (MC, unweighted event counts):\n";
  mc.Report()->Print();
}

int main() {
  analysis();
  return 0;
}
