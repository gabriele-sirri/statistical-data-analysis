// physics.h — the "theory" behind the toy experiment.
//
// Weighted-events simulator: events are always drawn from one fixed proposal
// distribution d(x) in the phase space x = (eta, phi, pt, mass). The physics
// parameters — the signal strength mu and the background-shape nuisance
// parameter theta — enter ONLY through per-event weights:
//
//   w(x; mu, theta) = [ mu * Ns * s(x)  +  Nb * b(x; theta) ] / (Nsim * d(x))
//
// where s, b are normalized signal/background densities, Ns/Nb the expected
// yields at (mu=1, theta=theta_nom), and Nsim the number of proposal events.
// The total simulated sample is one TTree; the two physics components are
// carried as separate weight columns (sig_w, bkg_w), which is exactly the
// information a HistFactory model needs (one sample per component).
//
// Phase-space picture, designed so that eta/phi selections are interesting:
//   signal:     eta ~ Gauss(0, 0.5)  (central bump)
//               phi ~ 1 + 0.4 cos(2 phi)   (gentle azimuthal modulation)
//               pt  ~ Gamma(k=2, scale=50) (hard spectrum, mode at 50 GeV)
//   background: eta ~ exp(-theta * |eta|)  (theta tilts the eta slope — this
//                                          is what the fit must measure)
//               phi flat, pt ~ exp(-pt/20) (soft spectrum)

#pragma once

#include <cmath>
#include <string>

#include "TRandom.h"

namespace toy {

constexpr double kPi = 3.14159265358979323846;

// Phase-space boundaries
constexpr double kEtaMax = 2.5;
constexpr double kPtMax = 200.0;

// Expected yields before selection cuts
constexpr double kNSig = 2000.;  // at mu = 1
constexpr double kNBkg = 20000.; // at nominal theta

// Monte Carlo sample size (number of proposal events = TTree entries).
// 400k keeps the MC error on sum(sig_w) per component below ~2%.
constexpr double kNSim = 400000.;

// Parameter of interest: signal strength mu
constexpr double kMuNom = 1.0;
// (mu is a pure normalization: it needs no up/down template variation.)

// Nuisance parameter: background eta slope theta
constexpr double kThetaNom = 1.0;   // value assumed in the MC sample
constexpr double kThetaDelta = 0.4; // 1-sigma up/down variation size
constexpr double kThetaTrue = 1.3;  // value nature picked for the "real data"

// Mass dimension (used by the unbinned-fit part of the course): a Gaussian
// signal peak on an exponential continuum. The mass shapes are analytic and
// tractable — deliberately, so that the unbinned fit has a "known model",
// while the eta shape (parameterized by theta) is treated as intractable and
// saved for the template-based HistFactory part.
constexpr double kMassMin = 110.;
constexpr double kMassMax = 140.;
constexpr double kMass0 = 125.;    // signal peak position
constexpr double kMassSigma = 2.;  // signal peak width
constexpr double kMassSlope = 25.; // background exponential slope

// ---------------------------------------------------------------------------
// Normalized probability densities
// ---------------------------------------------------------------------------

// pt densities are normalized over [0, kPtMax] so that sig_pdf/bkg_pdf are
// exactly normalized on the phase space the proposal covers.
inline double sig_pt_norm() {
  const double x = kPtMax / 50.;
  return 1. - std::exp(-x) * (1. + x); // Gamma(k=2, 50) CDF at kPtMax
}

inline double bkg_pt_norm() {
  return 1. - std::exp(-kPtMax / 20.); // exp(20) CDF at kPtMax
}

// mass densities, normalized over [kMassMin, kMassMax] (same reason as pt)
inline double sig_mass_norm() {
  const double s = std::sqrt(2.) * kMassSigma;
  return 0.5 * (std::erf((kMassMax - kMass0) / s) -
                std::erf((kMassMin - kMass0) / s));
}

inline double bkg_mass_norm() {
  return kMassSlope *
         (std::exp(-kMassMin / kMassSlope) - std::exp(-kMassMax / kMassSlope));
}

inline double sig_pdf(double eta, double phi, double pt, double mass) {
  const double g =
      std::exp(-0.5 * eta * eta / 0.25) / (0.5 * std::sqrt(2. * kPi));
  const double phimod = (1. + 0.4 * std::cos(2. * phi)) / (2. * kPi);
  const double p = (pt / (50. * 50.)) * std::exp(-pt / 50.) / sig_pt_norm();
  const double dm = mass - kMass0;
  const double m = std::exp(-0.5 * dm * dm / (kMassSigma * kMassSigma)) /
                   (kMassSigma * std::sqrt(2. * kPi) * sig_mass_norm());
  return g * phimod * p * m;
}

inline double bkg_pdf(double eta, double phi, double pt, double mass,
                      double theta) {
  const double zeta =
      2. * (1. - std::exp(-theta * kEtaMax)) / theta; // eta normalization
  const double e = std::exp(-theta * std::fabs(eta)) / zeta;
  const double p = std::exp(-pt / 20.) / (20. * bkg_pt_norm());
  const double m = std::exp(-mass / kMassSlope) / bkg_mass_norm();
  return e * (1. / (2. * kPi)) * p * m;
}

inline double proposal_pdf(double eta, double phi, double pt, double mass) {
  const double ptZ =
      25. * (1. - std::exp(-kPtMax / 25.)); // truncated exponential
  return (1. / (2. * kEtaMax)) * (1. / (2. * kPi)) *
         (1. / (kMassMax - kMassMin)) * std::exp(-pt / 25.) / ptZ;
}

// ---------------------------------------------------------------------------
// Event weights: the ONLY place where mu and theta act on the simulation
// ---------------------------------------------------------------------------

inline double sig_weight(double eta, double phi, double pt, double mass,
                         double mu) {
  return mu * kNSig * sig_pdf(eta, phi, pt, mass) /
         (kNSim * proposal_pdf(eta, phi, pt, mass));
}

inline double bkg_weight(double eta, double phi, double pt, double mass,
                         double theta) {
  return kNBkg * bkg_pdf(eta, phi, pt, mass, theta) /
         (kNSim * proposal_pdf(eta, phi, pt, mass));
}

// ---------------------------------------------------------------------------
// Samplers
// ---------------------------------------------------------------------------

inline void sample_proposal(TRandom &rng, double &eta, double &phi, double &pt,
                            double &mass) {
  eta = rng.Uniform(-kEtaMax, kEtaMax);
  phi = rng.Uniform(-kPi, kPi);
  pt = -25. * std::log(1. - rng.Uniform() * (1. - std::exp(-kPtMax / 25.)));
  mass = rng.Uniform(kMassMin, kMassMax);
}

inline void sample_signal(TRandom &rng, double &eta, double &phi, double &pt,
                          double &mass) {
  do {
    eta = rng.Gaus(0., 0.5);
  } while (std::fabs(eta) >= kEtaMax);
  // hit-and-miss for 1 + 0.4 cos(2 phi)
  double u;
  do {
    phi = rng.Uniform(-kPi, kPi);
    u = rng.Uniform(0., 1.4);
  } while (u > 1. + 0.4 * std::cos(2. * phi));
  // Gamma(k=2, scale=50), truncated at kPtMax (to match sig_pdf)
  do {
    pt = -50. * std::log(rng.Uniform() * rng.Uniform());
  } while (pt > kPtMax);
  // Gaussian mass peak, truncated to [kMassMin, kMassMax]
  do {
    mass = rng.Gaus(kMass0, kMassSigma);
  } while (mass < kMassMin || mass > kMassMax);
}

inline void sample_background(TRandom &rng, double theta, double &eta,
                              double &phi, double &pt, double &mass) {
  const double aeta =
      -std::log(1. - rng.Uniform() * (1. - std::exp(-theta * kEtaMax))) / theta;
  eta = (rng.Uniform() < 0.5) ? aeta : -aeta;
  phi = rng.Uniform(-kPi, kPi);
  pt = -20. *
       std::log(1. - rng.Uniform() * bkg_pt_norm()); // truncated at kPtMax
  // exponential mass, truncated to [kMassMin, kMassMax]
  const double emin = std::exp(-kMassMin / kMassSlope),
               emax = std::exp(-kMassMax / kMassSlope);
  mass = -kMassSlope * std::log(emin - rng.Uniform() * (emin - emax));
}

} // namespace toy
