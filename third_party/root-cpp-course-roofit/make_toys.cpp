// make_toys.cpp : NTuple production layer.
//
// Produces two files from the simulator in physics.h:
//
//   sim.root  : TTree "sim", one event per proposal draw. Kinematics are
//               independent of the physics parameters; those enter only via
//               the weight columns:
//                 sig_w = weight of this event as signal      (mu = 1)
//                 bkg_w = weight of this event as background  (theta =
//                 theta_nom)
//
//   data.root : TTree "data", unweighted "real data": signal events drawn
//               from s(x) with mu_true = kMuNom and background events drawn
//               from b(x; kThetaTrue). The analysis must recover kThetaTrue
//               without ever seeing it.

#include <iostream>

#include "TFile.h"
#include "TRandom3.h"
#include "TTree.h"

#include "physics.h"

void make_toys() {
  // --- Monte Carlo sample (weighted) -------------------------------------
  {
    TFile f("sim.root", "RECREATE");
    TTree t("sim", "weighted toy MC sample");
    double eta, phi, pt, mass, sig_w, bkg_w;
    t.Branch("eta", &eta);
    t.Branch("phi", &phi);
    t.Branch("pt", &pt);
    t.Branch("mass", &mass);
    t.Branch("sig_w", &sig_w);
    t.Branch("bkg_w", &bkg_w);

    TRandom3 rng(42);
    double sumSig = 0., sumBkg = 0.;
    for (int i = 0; i < int(toy::kNSim); ++i) {
      toy::sample_proposal(rng, eta, phi, pt, mass);
      sig_w = toy::sig_weight(eta, phi, pt, mass, toy::kMuNom);
      bkg_w = toy::bkg_weight(eta, phi, pt, mass, toy::kThetaNom);
      sumSig += sig_w;
      sumBkg += bkg_w;
      t.Fill();
    }
    t.Write();
    std::cout << "sim.root : " << t.GetEntries() << " proposal events\n"
              << "           sum(sig_w) = " << sumSig << " (expect "
              << toy::kNSig << ")\n"
              << "           sum(bkg_w) = " << sumBkg << " (expect "
              << toy::kNBkg << ")\n";
  }

  // --- "Real data" (unweighted, true parameters only visible via shapes) --
  {
    TFile f("data.root", "RECREATE");
    TTree t("data", "unweighted toy data");
    double eta, phi, pt, mass;
    t.Branch("eta", &eta);
    t.Branch("phi", &phi);
    t.Branch("pt", &pt);
    t.Branch("mass", &mass);

    TRandom3 rng(11); // independent seed; picked so mu/theta land within ~1
                      // sigma for the course demo
    const int nSig = int(toy::kMuNom * toy::kNSig); // mu_true = kMuNom
    const int nBkg = int(toy::kNBkg);
    for (int i = 0; i < nSig; ++i) {
      toy::sample_signal(rng, eta, phi, pt, mass);
      t.Fill();
    }
    for (int i = 0; i < nBkg; ++i) {
      toy::sample_background(rng, toy::kThetaTrue, eta, phi, pt, mass);
      t.Fill();
    }
    t.Write();
    std::cout << "data.root: " << t.GetEntries() << " events (sig " << nSig
              << " + bkg " << nBkg << ", theta_true = " << toy::kThetaTrue
              << ")\n";
  }
}

int main() {
  make_toys();
  return 0;
}
