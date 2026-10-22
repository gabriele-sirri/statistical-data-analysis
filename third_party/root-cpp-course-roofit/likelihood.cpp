// likelihood.cpp : Part 3 of the course: likelihood anatomy.
//
// Reuses the HistFactory workspace produced by histfactory.cpp
// (results/meas_combined_meas_model.root) and dissects the likelihood that
// the fit actually minimized:
//
//   1. one-dimensional scans in mu and alpha_theta, twice per parameter:
//      - "slice":  NLL with all other parameters FROZEN at their best fit
//      - profile:  NLL re-minimized over all other parameters at each point
//      The distance between the two curves *is* the effect of correlations.
//      The Delta NLL = 0.5 intersections reproduce the HESSE one-sigma
//      errors (Wilks) — the scan makes visible what HESSE approximates.
//
//   2. a 2D likelihood contour in (mu, alpha_theta) at 1 and 2 sigma, to be
//      compared with the HESSE covariance ellipse: identical only if the NLL
//      is exactly parabolic.

#include <iostream>

#include "RooAbsData.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooFitResult.h"
#include "RooMinimizer.h"
#include "RooMsgService.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLine.h"

namespace {

// Draw a 1D Delta-NLL scan of nll in var: frozen other parameters (black)
// vs. profiled (red), with the Delta NLL = 0.5 (1 sigma) line.
void scan1D(RooAbsReal &nll, RooRealVar &var, double lo, double hi,
            const char *xTitle, TCanvas &c, int pad) {
  c.cd(pad);
  RooPlot *frame = var.frame(RooFit::Range(lo, hi), RooFit::Title(xTitle));
  nll.plotOn(frame, RooFit::ShiftToZero(), RooFit::LineColor(kBlack));
  RooAbsReal *pll = nll.createProfile(var);
  pll->plotOn(frame, RooFit::ShiftToZero(), RooFit::LineColor(kRed));
  frame->SetMinimum(0.);
  frame->SetMaximum(3.);
  frame->GetYaxis()->SetTitle("- #Delta ln L");
  frame->Draw();
  TLine line;
  line.SetLineStyle(kDashed);
  line.DrawLine(lo, 0.5, hi, 0.5);
  line.DrawLine(lo, 2.0, hi, 2.0);
}

} // namespace

void likelihood() {

  RooRealVar::enableSilentClipping();

  // --- load the workspace written by histfactory.cpp ---------------------------------
  TFile f("results/meas_combined_meas_model.root");
  auto *w = f.Get<RooWorkspace>("combined");
  if (!w) {
    std::cerr
        << "run histfactory.cpp first (results/meas_combined_meas_model.root missing)\n";
    return;
  }
  auto *pdf = (RooAbsPdf *)w->pdf("simPdf");
  auto *data = w->data("obsData");
  auto *mu = w->var("mu");
  auto *alpha = w->var("alpha_theta");

  // Quell RooFit chatter below WARNING for the rest of the macro:
  // RooMinimizer emits an INFO note ("no discrete parameters ...") on every
  // minimize() call, i.e. once per point of each profile scan below.
  // PrintLevel only controls Minuit's own output, hence the stream-level mute.
  const auto savedKillBelow = RooMsgService::instance().globalKillBelow();
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);

  // re-fit quietly so all floating parameters sit at the minimum
  std::unique_ptr<RooFitResult> res(pdf->fitTo(*data, RooFit::Save(),
                                               RooFit::PrintLevel(-1),
                                               RooFit::PrintEvalErrors(-1)));

  std::unique_ptr<RooAbsReal> nll(pdf->createNLL(*data));

  std::cout << "\n===== likelihood anatomy =====\n"
            << "  best fit:  mu = " << mu->getVal() << " +/- " << mu->getError()
            << "   alpha_theta = " << alpha->getVal() << " +/- "
            << alpha->getError() << "\n"
            << "  corr(mu, alpha_theta) = "
            << res->correlation("mu", "alpha_theta") << "\n";

  // --- 1D scans: slice (frozen others) vs. profile --------------------------
  TCanvas c1("c1", "1D likelihood scans", 1200, 500);
  c1.Divide(2, 1);
  scan1D(*nll, *mu, mu->getVal() - 4 * mu->getError(),
         mu->getVal() + 4 * mu->getError(),
         "slice (black) vs profile (red): mu", c1, 1);
  scan1D(*nll, *alpha, alpha->getVal() - 4 * alpha->getError(),
         alpha->getVal() + 4 * alpha->getError(),
         "slice (black) vs profile (red): alpha_theta", c1, 2);
  c1.SaveAs("likelihood_scan.pdf");

  // --- 2D contour vs HESSE ellipse ------------------------------------------
  RooMinimizer rm(*nll);
  rm.setPrintLevel(-1);
  rm.minimize("Minuit2", "Migrad");
  TCanvas c2("c2", "2D likelihood contour", 700, 600);
  RooPlot *cnt = rm.contour(*mu, *alpha, 1., 2.);
  cnt->SetTitle("#DeltaNLL contours (1#sigma, 2#sigma): mu vs alpha_theta");
  cnt->Draw();
  c2.SaveAs("likelihood_contour.pdf");

  RooMsgService::instance().setGlobalKillBelow(savedKillBelow);

  std::cout << "wrote likelihood_scan.pdf and likelihood_contour.pdf\n"
            << "check: the red profile curves cross DeltaNLL=0.5 at ~ +/- the "
               "HESSE errors above\n";
}

int main() {
  likelihood();
  return 0;
}
