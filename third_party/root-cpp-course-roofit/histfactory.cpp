// histfactory.cpp : programmatic HistFactory model + fit.
//
// Model:
//   channel "channel", 8 bins in |eta|
//     sample "signal"     (h_sig)       scaled by POI "mu" (NormFactor)
//     sample "background" (h_bkg)       with HistoSys "theta" built from the
//                                       RDF varied histograms
//                                       h_bkg_theta_down / h_bkg_theta_up
//   both samples carry their MC statistical uncertainty (ActivateStatError)
//
// HistFactory names the HistoSys nuisance parameter "alpha_theta": a unit
// Gaussian-constrained interpolation parameter, so that
//     theta = kThetaNom + alpha_theta * kThetaDelta
// with kThetaNom = 1.0, kThetaDelta = 0.4. Data were generated with
// kThetaTrue = 1.3, i.e. alpha_true = +0.75. The fit should land near that.
//
// Note on the MC stat errors: ROOT's StatErrorConfig defaults to a
// RelErrorThreshold of 0.05, below which gamma_stat parameters are FROZEN.
// This toy's MC stat errors are O(1%), so without the explicit
// SetRelErrorThreshold(0) below, ActivateStatError() would have no effect on
// the fit (all gamma_stat frozen at 1, visible as "falls below threshold of
// 0.05" warnings at model build time).
//
// Diagnostics (the usual fit-quality plots):
//   histfactory_prefit.pdf   data vs model at the prefit parameter values
//                            (mu=1, alpha_theta=0, gamma_stat=1). Grey 1-sigma
//                            band = prefit uncertainty: the constraint widths
//                            (alpha: 1, gamma_stat: relative MC stat error),
//                            propagated linearly. mu is unconstrained prefit
//                            and does not contribute to the prefit band.
//   histfactory_postfit.pdf  same at the postfit point; band = full postfit
//                            covariance matrix propagated linearly (nuisances
//                            constrained by data => band shrinks).
//   both canvases show stacked signal/background, Poisson data error bars,
//   and a bottom residual panel: (data - model)/sqrt(data).
//   histfactory_pulls.pdf    combine-style nuisance-parameter pulls:
//                            (theta_hat - theta_0)/sigma_0 with the postfit
//                            error in units of the prefit sigma_0. The POI mu
//                            is shown at the top as (mu_hat - 1)/sigma_hat.

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "RooAbsData.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooArgList.h"
#include "RooFitResult.h"
#include "RooMsgService.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooStats/HistFactory/MakeModelAndMeasurementsFast.h"
#include "RooStats/HistFactory/Measurement.h"
#include "TAxis.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMatrixDSym.h"
#include "TPad.h"
#include "TStyle.h"
#include "TSystem.h"

#include "physics.h"

namespace {

// ---------------------------------------------------------------------------
// Model evaluation, bin by bin
// ---------------------------------------------------------------------------

// Content of bin i of the HistFactory channel model at the CURRENT parameter
// values. channel_model (RooRealSumPdf) evaluates to a bin density; multiply
// by the bin width to get counts.
std::vector<double> modelBins(RooAbsReal &channelModel, RooRealVar &x) {
  const RooAbsBinning &binning = x.getBinning();
  std::vector<double> out(binning.numBins());
  for (int i = 0; i < binning.numBins(); ++i) {
    x.setVal(binning.binCenter(i));
    out[i] = channelModel.getVal() * binning.binWidth(i);
  }
  return out;
}

// Observed counts per bin from the (binned) data set.
std::vector<double> dataBins(RooAbsData &data) {
  std::vector<double> out(data.numEntries());
  for (int i = 0; i < data.numEntries(); ++i) {
    data.get(i);
    out[i] = data.weight();
  }
  return out;
}

// ---------------------------------------------------------------------------
// Uncertainty bands by linear (finite-difference) propagation
// ---------------------------------------------------------------------------

using ModelEvaluator = std::vector<double> (*)();

// Band from INDEPENDENT prefit constraints: for each parameter with a stored
// prefit error sigma0, shift by +/- sigma0 and add the half-difference in
// quadrature. Unconstrained parameters (mu prefit) contribute nothing.
std::vector<double> prefitBand(RooAbsReal &channelModel, RooRealVar &x,
                               const std::vector<RooRealVar *> &pars) {
  const auto base = modelBins(channelModel, x);
  std::vector<double> var(base.size(), 0.);
  for (auto *p : pars) {
    const double sigma0 = p->getError();
    if (sigma0 <= 0.)
      continue;
    const double v0 = p->getVal();
    p->setVal(v0 + sigma0);
    const auto up = modelBins(channelModel, x);
    p->setVal(v0 - sigma0);
    const auto dn = modelBins(channelModel, x);
    p->setVal(v0);
    for (std::size_t i = 0; i < var.size(); ++i) {
      const double d = 0.5 * (up[i] - dn[i]);
      var[i] += d * d;
    }
  }
  for (double &v : var)
    v = std::sqrt(v);
  return var;
}

// Band from the full postfit covariance: var_i = g_i^T C g_i with numeric
// gradients g over the floating parameters of the fit result.
std::vector<double> postfitBand(RooAbsReal &channelModel, RooRealVar &x,
                                const RooFitResult &res, RooWorkspace &w) {
  const auto base = modelBins(channelModel, x);
  const TMatrixDSym cov = res.covarianceMatrix();
  const RooArgList &fp = res.floatParsFinal();
  const int nPar = fp.getSize();

  std::vector<std::vector<double>> grad(nPar, std::vector<double>(base.size()));
  for (int p = 0; p < nPar; ++p) {
    auto *v = w.var(fp[p].GetName());
    if (!v)
      continue;
    const double sigma = v->getError();
    const double h = std::max(1e-4, 1e-2 * sigma); // small symmetric step
    const double v0 = v->getVal();
    v->setVal(v0 + h);
    const auto up = modelBins(channelModel, x);
    v->setVal(v0 - h);
    const auto dn = modelBins(channelModel, x);
    v->setVal(v0);
    for (std::size_t i = 0; i < base.size(); ++i)
      grad[p][i] = (up[i] - dn[i]) / (2. * h);
  }

  std::vector<double> out(base.size(), 0.);
  for (std::size_t i = 0; i < base.size(); ++i) {
    double var = 0.;
    for (int p = 0; p < nPar; ++p)
      for (int q = 0; q < nPar; ++q)
        var += grad[p][i] * cov[p][q] * grad[q][i];
    out[i] = std::sqrt(std::max(var, 0.));
  }
  return out;
}

// ---------------------------------------------------------------------------
// Drawing helpers
// ---------------------------------------------------------------------------

std::unique_ptr<TH1D> makeHist(const char *name, const char *title,
                               const RooAbsBinning &binning,
                               const std::vector<double> &content) {
  const int nb = binning.numBins();
  auto h = std::make_unique<TH1D>(name, title, nb, binning.lowBound(),
                                  binning.highBound());
  for (int i = 0; i < nb; ++i)
    h->SetBinContent(i + 1, content[i]);
  return h;
}

// Data vs model canvas: stacked signal/background steps, grey uncertainty
// band around the total, Poisson data points, residual panel underneath.
void makeFitCanvas(RooRealVar &x, const std::vector<double> &data,
                   const std::vector<double> &total,
                   const std::vector<double> &background,
                   const std::vector<double> &band, const char *title,
                   const char *bandLabel, const std::string &annotate,
                   const char *outFile) {
  const RooAbsBinning &binning = x.getBinning();
  const int nb = binning.numBins();

  auto hData = makeHist("hDataPlot", title, binning, data);
  hData->SetBinErrorOption(TH1::kPoisson); // asymmetric Poisson error bars
  hData->SetMarkerStyle(20); // HEP style: black dot + thick black error bar
  hData->SetMarkerSize(1.0);
  hData->SetMarkerColor(kBlack);
  hData->SetLineColor(kBlack);
  hData->SetLineWidth(2);
  auto hBkg = makeHist("hBkgPlot", "", binning, background);
  hBkg->SetFillColor(kAzure - 4);
  hBkg->SetLineColor(kAzure - 4);
  std::vector<double> signal(nb);
  for (int i = 0; i < nb; ++i)
    signal[i] = total[i] - background[i];
  auto hSig = makeHist("hSigPlot", "", binning, signal);
  hSig->SetFillColor(kOrange - 3);
  hSig->SetLineColor(kOrange - 3);
  auto hTot = makeHist("hTotPlot", "", binning, total);
  hTot->SetLineColor(kAzure + 2);
  hTot->SetLineWidth(2);

  auto gBand = std::make_unique<TGraphAsymmErrors>(nb);
  for (int i = 0; i < nb; ++i) {
    gBand->SetPoint(i, binning.binCenter(i), total[i]);
    gBand->SetPointError(i, 0.5 * binning.binWidth(i),
                         0.5 * binning.binWidth(i), band[i], band[i]);
  }
  gBand->SetFillColor(kGray);
  gBand->SetLineColor(kGray);

  double ymax = 0.;
  for (int i = 0; i < nb; ++i)
    ymax = std::max(
        ymax, std::max(total[i] + band[i], data[i] + std::sqrt(data[i])));

  // bottom panel: per-bin residuals (data - model)/sigma_data with the data
  // uncertainty bars (+-1 in these units by construction), plus the model
  // band expressed in sigma_data units around zero
  auto hPull = makeHist("hPull", "", binning, std::vector<double>(nb, 0.));
  auto gPullBand = std::make_unique<TGraphAsymmErrors>(nb);
  double maxPull = 3.4;
  for (int i = 0; i < nb; ++i) {
    if (data[i] <= 0.)
      continue;
    const double sd = std::sqrt(data[i]);
    const double pull = (data[i] - total[i]) / sd;
    hPull->SetBinContent(i + 1, pull);
    hPull->SetBinError(i + 1, 1.); // bin sigma in pull units
    gPullBand->SetPoint(i, binning.binCenter(i), 0.);
    gPullBand->SetPointError(i, 0.5 * binning.binWidth(i),
                             0.5 * binning.binWidth(i), band[i] / sd,
                             band[i] / sd);
    maxPull = std::max(maxPull,
                       1.15 * std::max(std::abs(pull), band[i] / sd));
  }
  hPull->SetMarkerStyle(20); // same HEP look as the data in the top panel
  hPull->SetMarkerSize(0.9);
  hPull->SetMarkerColor(kBlack);
  hPull->SetLineColor(kBlack);
  hPull->SetLineWidth(2);
  gPullBand->SetFillColor(kGray);

  TCanvas c("cFit", title, 800, 800);
  auto *pTop = new TPad("pTop", "", 0., 0.30, 1., 1.);
  pTop->SetBottomMargin(0.025);
  pTop->Draw();
  auto *pBot = new TPad("pBot", "", 0., 0., 1., 0.30);
  pBot->SetTopMargin(0.04);
  pBot->SetBottomMargin(0.34);
  pBot->Draw();

  pTop->cd();
  hTot->SetTitle(title);
  hTot->GetXaxis()->SetLabelSize(0); // |eta| labels only on the bottom pad
  hTot->GetYaxis()->SetTitle("Events");
  hTot->GetYaxis()->SetTitleOffset(1.1);
  hTot->SetMaximum(1.35 * ymax);
  hTot->SetMinimum(0.);
  hTot->Draw("hist");
  // stack look: the cumulative (bkg+sig) orange area first, then the azure
  // background area on top covering [0, bkg] and leaving signal [bkg, total]
  auto hStack = std::make_unique<TH1D>(*hBkg);
  hStack->Add(hSig.get());
  hStack->SetFillColor(kOrange - 3);
  hStack->Draw("hist same");
  hBkg->Draw("hist same");
  gBand->Draw("2 same");
  hData->Draw("E0 same");

  auto leg = std::make_unique<TLegend>(0.46, annotate.empty() ? 0.60 : 0.54,
                                       0.86, 0.88);
  leg->SetBorderSize(0);
  if (!annotate.empty()) {
    leg->SetHeader(annotate.c_str(), "C"); // fit result on top of the legend
    leg->SetTextAlign(12);
  }
  leg->AddEntry(hData.get(), "Data", "PE");
  leg->AddEntry(hStack.get(), "Signal (#mu #times s)", "F");
  leg->AddEntry(hBkg.get(), "Background", "F");
  leg->AddEntry(gBand.get(), bandLabel, "F");
  leg->Draw();

  pBot->cd();
  hPull->GetYaxis()->SetTitle("Residual");
  hPull->GetYaxis()->CenterTitle();
  hPull->GetYaxis()->SetRangeUser(-maxPull, maxPull);
  hPull->GetYaxis()->SetNdivisions(305);
  hPull->GetXaxis()->SetTitle(x.GetTitle());
  for (TAxis *ax : {hPull->GetXaxis(), hPull->GetYaxis()}) {
    ax->SetLabelSize(0.10);
    ax->SetTitleSize(0.12);
  }
  hPull->GetYaxis()->SetTitleOffset(0.45);
  hPull->GetYaxis()->SetLabelSize(0.09);
  hPull->GetXaxis()->SetTitleOffset(1.0);
  hPull->Draw("PE"); // markers with the +-1 data-uncertainty bars
  gPullBand->Draw("2 same");
  auto *zero = new TLine(binning.lowBound(), 0., binning.highBound(), 0.);
  zero->SetLineColor(kGray + 2);
  zero->Draw();
  for (double y : {-1., 1.}) {
    auto *gi = new TLine(binning.lowBound(), y, binning.highBound(), y);
    gi->SetLineColor(kGray + 1);
    gi->SetLineStyle(kDashed);
    gi->Draw();
  }
  hPull->Draw("PE same");

  c.SaveAs(outFile);
}

// ---------------------------------------------------------------------------
// Combine-style nuisance-parameter pulls
// ---------------------------------------------------------------------------

// Pretty axis label for a fit-parameter name in the pulls plot.
std::string prettyParam(const std::string &n) {
  if (n == "mu")
    return "#mu  (POI, ref 1.0, units of #sigma_{#mu})";
  if (n == "alpha_theta")
    return "#alpha_{#theta}";
  const std::string prefix = "gamma_stat_channel_bin_";
  if (n.rfind(prefix, 0) == 0)
    return "#gamma_{MC, " + n.substr(prefix.size()) + "}";
  return n;
}

// Pivots for the row ordering: POI first, then shape nuisance, then gammas.
int pullRank(const std::string &n) {
  if (n == "mu")
    return 0;
  if (n == "alpha_theta")
    return 1;
  return 2;
}

// Prefit reference of one parameter, snapshotted BEFORE the fit (the live
// workspace variables have moved to the postfit point by plotting time).
struct PullRef {
  std::string name;
  double v0 = 0.;    // prefit value
  double sigma0 = 0; // prefit constraint width; <= 0: unconstrained (POI)
};

// For each floating parameter p:
//   x position  = (p_hat - p_0) / sigma_0    ("pull")
//   x error bar = sigma_hat / sigma_0        (postfit error in prefit units)
// p_0/sigma_0 come from `prefitRef`; mu (no prefit constraint) uses
// p_0 = mu_nominal and sigma_0 = sigma_hat, i.e. compatibility with mu=1.
void makePullsCanvas(const RooFitResult &post,
                     const std::vector<PullRef> &prefitRef,
                     const char *outFile) {
  struct Pull {
    std::string name;
    double pull;
    double err;
  };
  std::vector<Pull> pulls;
  for (const auto &ref : prefitRef) {
    auto *fitPar = static_cast<RooRealVar *>(
        post.floatParsFinal().find(ref.name.c_str()));
    if (!fitPar)
      continue; // frozen in the fit, no pull available
    double sigmaRef = ref.sigma0;
    double refVal = ref.v0;
    if (sigmaRef <= 0.) { // unconstrained (the POI): use its own fit error
      refVal = toy::kMuNom;
      sigmaRef = fitPar->getError();
    }
    pulls.push_back({ref.name, (fitPar->getVal() - refVal) / sigmaRef,
                     fitPar->getError() / sigmaRef});
  }
  std::stable_sort(pulls.begin(), pulls.end(),
                   [](const Pull &a, const Pull &b) {
                     const int ra = pullRank(a.name), rb = pullRank(b.name);
                     return ra != rb ? ra < rb : a.name < b.name;
                   });
  if (pulls.empty())
    return;

  const int n = static_cast<int>(pulls.size());
  double xmax = 3.2;
  for (const auto &p : pulls)
    xmax = std::max(xmax, std::abs(p.pull) + p.err + 0.6);

  TCanvas c("cPulls", "nuisance-parameter pulls", 800, 140 + 42 * n);
  c.SetLeftMargin(0.26);
  c.SetRightMargin(0.03);

  TH2F axes("axes", "", 10, -xmax, xmax, n, 0.5, n + 0.5);
  axes.SetStats(0);
  axes.GetXaxis()->SetTitle("(#theta - #theta_{0}) / #sigma_{0}");
  axes.GetXaxis()->SetTitleOffset(1.1);
  axes.GetXaxis()->SetTitleSize(0.045);
  for (int i = 0; i < n; ++i) // top row = first entry
    axes.GetYaxis()->SetBinLabel(n - i, prettyParam(pulls[i].name).c_str());
  axes.Draw();

  // grey |pull| < 1 reference band; the pad owns all primitives below
  auto *band1 = new TBox(-1., 0.5, 1., n + 0.5);
  band1->SetFillColor(kGray);
  band1->Draw();

  auto *g = new TGraphErrors(n);
  for (int i = 0; i < n; ++i) {
    g->SetPoint(i, pulls[i].pull, n - i);
    g->SetPointError(i, pulls[i].err, 0.);
  }
  g->SetMarkerStyle(21);
  g->SetMarkerSize(1.1);
  g->SetLineWidth(2);
  g->Draw("PE");

  auto *zero = new TLine(0., 0.5, 0., n + 0.5);
  zero->SetLineColor(kGray + 2);
  zero->SetLineStyle(kDashed);
  zero->Draw();

  c.SaveAs(outFile);

  std::cout << "  pulls ((postfit-prefit)/sigma_prefit):\n";
  for (const auto &p : pulls)
    std::cout << "    " << p.name << " : " << p.pull << " +/- " << p.err
              << "\n";
}

} // namespace

void histfactory() {
  gSystem->mkdir("results", /*recursive=*/true);
  gStyle->SetOptStat(0);

  RooStats::HistFactory::Measurement meas("meas", "rdf_histfactory_toy");
  meas.SetOutputFilePrefix("results/meas");
  meas.SetPOI("mu");
  meas.SetLumi(1.0);
  meas.SetLumiRelErr(0.01);
  meas.AddConstantParam("Lumi"); // no luminosity uncertainty in this toy

  RooStats::HistFactory::Channel chan("channel");
  chan.SetData("h_data", "hists.root");
  // ROOT's default RelErrorThreshold = 0.05 would freeze all gamma_stat bins
  // of this toy (MC stat errors are O(1%)): keep them floating.
  chan.GetStatErrorConfig().SetRelErrorThreshold(0.0);

  RooStats::HistFactory::Sample sig("signal", "h_sig", "hists.root");
  sig.SetNormalizeByTheory(false);
  sig.AddNormFactor("mu", 1.0, 0.0, 5.0); // POI: multiplies the signal template
  sig.ActivateStatError();

  RooStats::HistFactory::Sample bkg("background", "h_bkg", "hists.root");
  bkg.SetNormalizeByTheory(false);
  bkg.AddHistoSys("theta", "h_bkg_theta_down", "hists.root", "",
                  "h_bkg_theta_up", "hists.root", "");
  bkg.ActivateStatError();

  chan.AddSample(sig);
  chan.AddSample(bkg);
  meas.AddChannel(chan);
  meas.CollectHistograms();

  auto wsPtr = RooStats::HistFactory::MakeModelAndMeasurementFast(meas);
  RooWorkspace &w = *wsPtr;

  auto *pdf = w.pdf("simPdf");
  auto *data = w.data("obsData");
  auto *channelModel = w.pdf("channel_model"); // bin-density of the model
  auto *mu = w.var("mu");
  auto *alpha = w.var("alpha_theta");
  auto *x = w.var("obs_x_channel");
  if (!pdf || !data || !channelModel || !mu || !alpha || !x) {
    std::cerr << "workspace is missing pdf/data/parameter, dumping it:\n";
    w.Print();
    return;
  }

  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);

  // --- prefit state --------------------------------------------------------
  // All floating parameters at their starting values (mu=1, alpha=0,
  // gamma=1). Record the prefit reference (value, sigma) from the workspace:
  // HistFactory sets initial errors equal to the constraint widths
  // (alpha_theta: 1, gamma_stat: relative MC stat error; mu: none).
  alpha->setVal(0.);
  std::vector<RooRealVar *> bandPars;
  std::vector<PullRef> prefitRef;
  for (RooAbsArg *abs : w.allVars()) {
    auto *v = dynamic_cast<RooRealVar *>(abs);
    if (!v || v->isConstant())
      continue;
    if (v == x)
      continue;
    bandPars.push_back(v);
    prefitRef.push_back({v->GetName(), v->getVal(), v->getError()});
  }

  // --- prefit plot -----------------------------------------------------------
  makeFitCanvas(*x, dataBins(*data), modelBins(*channelModel, *x),
                [&] { // background-only bins: mu -> 0, restore afterwards
                  const double mu0 = mu->getVal();
                  mu->setVal(0.);
                  auto b = modelBins(*channelModel, *x);
                  mu->setVal(mu0);
                  return b;
                }(),
                prefitBand(*channelModel, *x, bandPars),
                "Pre-fit: data vs model",
                "pre-fit unc. (1#sigma)", "", "histfactory_prefit.pdf");

  // --- fit to data -----------------------------------------------------------
  // alpha_theta starts at its nominal value 0 (set above, nothing moved it).
  std::cout << "\n===== model built, fitting =====\n";
  std::unique_ptr<RooFitResult> res(pdf->fitTo(*data, RooFit::Save(),
                                               RooFit::PrintLevel(-1),
                                               RooFit::PrintEvalErrors(-1)));
  RooMsgService::instance().setGlobalKillBelow(RooFit::DEBUG);

  const double thetaHat = toy::kThetaNom + alpha->getVal() * toy::kThetaDelta;
  const double thetaErr = alpha->getError() * toy::kThetaDelta;

  res->Print("v");
  std::cout << "\n===== fit summary =====\n"
            << "  mu          = " << mu->getVal() << " +/- " << mu->getError()
            << "   (true: " << toy::kMuNom << ")\n"
            << "  alpha_theta = " << alpha->getVal() << " +/- "
            << alpha->getError() << "\n  ==> theta   = " << thetaHat << " +/- "
            << thetaErr
            << "   (true value used for the data: " << toy::kThetaTrue << ")\n";

  // --- postfit plot ----------------------------------------------------------
  char annotate[256];
  snprintf(annotate, sizeof(annotate),
           "#mu = %.2f #pm %.2f,   #theta = %.2f #pm %.2f", mu->getVal(),
           mu->getError(), thetaHat, thetaErr);
  makeFitCanvas(*x, dataBins(*data), modelBins(*channelModel, *x),
                [&] {
                  const double mu0 = mu->getVal();
                  mu->setVal(0.);
                  auto b = modelBins(*channelModel, *x);
                  mu->setVal(mu0);
                  return b;
                }(),
                postfitBand(*channelModel, *x, *res, w),
                "Post-fit: data vs model", "post-fit unc. (1#sigma)",
                annotate, "histfactory_postfit.pdf");

  // --- pulls plot --------------------------------------------------------------
  makePullsCanvas(*res, prefitRef, "histfactory_pulls.pdf");

  std::cout << "\nwrote histfactory_prefit.pdf, histfactory_postfit.pdf, "
               "histfactory_pulls.pdf\n";
}

int main() {
  histfactory();
  return 0;
}
