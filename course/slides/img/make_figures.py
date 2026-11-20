"""Figures of the slides, drawn with ROOT and RooFit (RooPlot). Run from this folder:  python make_figures.py
The slides only use the names of the PNG files."""
import ROOT
from ROOT import RooFit as RF
ROOT.gROOT.SetBatch(True); ROOT.gErrorIgnoreLevel = ROOT.kWarning
ROOT.RooMsgService.instance().getStream(0).minLevel = RF.WARNING
ROOT.RooMsgService.instance().setGlobalKillBelow(RF.WARNING)

st = ROOT.gStyle
st.SetOptStat(0); st.SetOptTitle(1); st.SetTitleBorderSize(0); st.SetTitleFillColor(0); st.SetTitleFontSize(0.05)
st.SetPadLeftMargin(0.15); st.SetPadBottomMargin(0.15); st.SetPadTopMargin(0.10); st.SetPadRightMargin(0.05)
for ax in "xyz":
    st.SetLabelSize(0.045, ax); st.SetTitleSize(0.055, ax); st.SetLabelFont(42, ax); st.SetTitleFont(42, ax)
st.SetTitleOffset(1.1, "x"); st.SetTitleOffset(1.2, "y")
BLUE, ORANGE = ROOT.kAzure + 1, ROOT.kOrange + 7
DATA = "../../../examples/lhcb-b0-ppbar/data/rarest_b0_decay.dat"

# ---------- the model of Lab 1 (Exercise C) and of Lab 2 (Exercise C)
m     = ROOT.RooRealVar("m", "m [MeV]", 5080, 5540)
mean  = ROOT.RooRealVar("mean", "mean", 5288, 5200, 5350)
sigma = ROOT.RooRealVar("sigma", "sigma", 14.8, 5, 50)
slope = ROOT.RooRealVar("slope", "slope", -0.002, -0.02, 0)
sig   = ROOT.RooGaussian("sig", "sig", m, mean, sigma)
bkg   = ROOT.RooExponential("bkg", "bkg", m, slope)
nsig  = ROOT.RooRealVar("nsig", "#nu_{s}", 33, 0, 400)
nbkg  = ROOT.RooRealVar("nbkg", "#nu_{b}", 133, 0, 600)
model = ROOT.RooAddPdf("model", "sig+bkg", ROOT.RooArgList(sig, bkg), ROOT.RooArgList(nsig, nbkg))

# ---------- Figure 1: likelihood interval, the HESSE parabola against the profile (real data)
data = ROOT.RooDataSet("data", "data", ROOT.RooArgSet(m))
for line in open(DATA):
    v = float(line.split()[0])
    if 5080 < v < 5540:
        m.setVal(v); data.add(ROOT.RooArgSet(m))
model.fitTo(data, Extended=True, PrintLevel=-1, Hesse=True)
best, err = nsig.getVal(), nsig.getError()
nll = model.createNLL(data, RF.Extended(True))
prof = nll.createProfile(ROOT.RooArgSet(nsig))
model.fitTo(data, Extended=True, PrintLevel=-1, Minos=ROOT.RooArgSet(nsig))
lo, hi = nsig.getErrorLo(), nsig.getErrorHi()
nsig.setVal(best)

c1 = ROOT.TCanvas("c1", "likelihood", 900, 600)
frame = nsig.frame(RF.Range(max(0.5, best - 3.2*err), best + 3.2*err), RF.Title(";signal yield #nu_{s};-ln L - (-ln L)_{min}"))
prof.plotOn(frame, RF.ShiftToZero(), RF.LineColor(BLUE), RF.LineWidth(4), RF.Name("profile"))
parab = ROOT.RooFormulaVar("parab", "0.5*pow((@0-%f)/%f,2)" % (best, err), ROOT.RooArgList(nsig))
parab.plotOn(frame, RF.LineColor(ORANGE), RF.LineStyle(ROOT.kDashed), RF.LineWidth(4), RF.Name("parabola"))
frame.SetMinimum(-0.25); frame.SetMaximum(3.2); frame.Draw()
x1, x2 = frame.GetXaxis().GetXmin(), frame.GetXaxis().GetXmax()
half = ROOT.TLine(x1, 0.5, x2, 0.5); half.SetLineColor(ROOT.kGray + 1); half.Draw()
t_half = ROOT.TLatex(x2 - 0.02*(x2 - x1), 0.58, "#Delta(-ln L) = 0.5"); t_half.SetTextAlign(31); t_half.SetTextSize(0.04); t_half.SetTextColor(ROOT.kGray + 2); t_half.Draw()
b_minos = ROOT.TLine(best + lo, 0.20, best + hi, 0.20); b_minos.SetLineColor(BLUE); b_minos.SetLineWidth(9); b_minos.Draw()
b_hesse = ROOT.TLine(best - err, 0.0, best + err, 0.0); b_hesse.SetLineColor(ORANGE); b_hesse.SetLineWidth(9); b_hesse.Draw()
l_minos = ROOT.TLatex(best + hi + 0.025*(x2 - x1), 0.20, "MINOS: %.1f / +%.1f" % (lo, hi)); l_minos.SetTextSize(0.042); l_minos.SetTextColor(BLUE); l_minos.SetTextAlign(12); l_minos.Draw()
l_hesse = ROOT.TLatex(best + err + 0.025*(x2 - x1), -0.02, "HESSE: #pm%.1f" % err); l_hesse.SetTextSize(0.042); l_hesse.SetTextColor(ORANGE); l_hesse.SetTextAlign(12); l_hesse.Draw()
leg = ROOT.TLegend(0.40, 0.70, 0.93, 0.87); leg.SetBorderSize(0); leg.SetFillStyle(0); leg.SetTextSize(0.042)
leg.AddEntry(frame.findObject("profile"), "profile of -ln L (the real likelihood)", "L")
leg.AddEntry(frame.findObject("parabola"), "parabola: what HESSE assumes", "L"); leg.Draw()
c1.SaveAs("likelihood_interval.png")
print("figure 1: nsig = %.1f  HESSE +-%.1f  MINOS %.1f / +%.1f" % (best, err, lo, hi))

# ---------- Figure 2: how a pull distribution looks (schematic): histograms and curves of ROOT
rnd = ROOT.TRandom3(3)
panels = [("healthy", 0.0, 1.0), ("mean #neq 0: bias", 0.6, 1.0),
          ("RMS > 1: underestimated", 0.0, 1.6), ("RMS < 1: overestimated", 0.0, 0.6)]
st.SetTitleFontSize(0.075)
c2 = ROOT.TCanvas("c2", "pulls", 1600, 440); c2.Divide(4, 1)
keep = []
for k, (title, mu, rms) in enumerate(panels, 1):
    c2.cd(k); ROOT.gPad.SetLeftMargin(0.08); ROOT.gPad.SetBottomMargin(0.17); ROOT.gPad.SetTopMargin(0.16)
    h = ROOT.TH1F("hp%d" % k, title + ";pull;", 40, -4, 4)
    for _ in range(6000): h.Fill(rnd.Gaus(mu, rms))
    h.SetFillColor(ROOT.kAzure - 9); h.SetLineColor(BLUE); h.SetMaximum(1.25*max(h.GetMaximum(), 6000*0.2/2.5066))
    h.GetYaxis().SetLabelSize(0); h.GetYaxis().SetTickLength(0); h.GetXaxis().SetTitleSize(0.07); h.GetXaxis().SetLabelSize(0.06)
    h.GetXaxis().SetTitleOffset(1.0); h.SetTitleSize(0.07)
    h.Draw("hist")
    g = ROOT.TF1("g%d" % k, "[0]*exp(-0.5*x*x)", -4, 4); g.SetParameter(0, 6000*0.2/2.5066)
    g.SetLineColor(ROOT.kBlack); g.SetLineStyle(2); g.SetLineWidth(2); g.Draw("same")
    z = ROOT.TLine(0, 0, 0, h.GetMaximum()); z.SetLineColor(ROOT.kGray + 1); z.Draw()
    keep += [h, g, z]
c2.SaveAs("pull_diagnosis.png"); st.SetTitleFontSize(0.05)

# ---------- Figure 3: the pulls of Exercise C, real toys with RooMCStudy and plotPull
TRUTH = {mean: 5288, sigma: 14.8, slope: -0.002, nbkg: 133}
def study(ns, seed, n=1000):
    ROOT.RooRandom.randomGenerator().SetSeed(seed)
    for v, t in TRUTH.items(): v.setVal(t)
    nsig.setVal(ns)
    mcs = ROOT.RooMCStudy(model, ROOT.RooArgSet(m), RF.Silence(), RF.Extended(True))
    mcs.generateAndFit(n)
    return mcs
c3 = ROOT.TCanvas("c3", "pulls of Exercise C", 1500, 560); c3.Divide(2, 1)
mc = []
for k, ns in enumerate((33, 5), 1):
    c3.cd(k); ROOT.gPad.SetTopMargin(0.12)
    mcs = study(ns, 123); mc.append(mcs)
    fr = mcs.plotPull(nsig, RF.FitGauss(True), RF.Bins(40), RF.FrameRange(-4, 4))
    fr.SetTitle("#nu_{s} = %d: pulls of 1000 toys" % ns); fr.GetXaxis().SetTitle("pull of #nu_{s}")
    fr.SetMaximum(1.45*fr.GetMaximum())      # room for the box of the Gaussian fit
    fr.Draw()
c3.SaveAs("pull_33_vs_5.png")

# ---------- Figure 4 (Lab 3): Poisson likelihood against its Gaussian approximation
c4 = ROOT.TCanvas("c4", "Poisson or Gauss", 1400, 520); c4.Divide(2, 1)
fs = []
for k, n in enumerate((5, 40), 1):
    c4.cd(k); ROOT.gPad.SetLeftMargin(0.13)
    xmin, xmax = (-3.0, 14.0) if n == 5 else (0.5, 90.0)
    fp = ROOT.TF1("fp%d" % k, "exp([0]*log(x) - x - ([0]*log([0]) - [0]))", 0.05, xmax); fp.SetParameter(0, n)
    fg = ROOT.TF1("fg%d" % k, "exp(-pow([0]-x,2)/(2*[0]))", xmin, xmax); fg.SetParameter(0, n)
    fg.SetTitle("n_{off} = %d;b;likelihood (peak = 1)" % n); fg.SetLineColor(ORANGE); fg.SetLineStyle(2); fg.SetLineWidth(4)
    fp.SetLineColor(BLUE); fp.SetLineWidth(4)
    fg.SetMinimum(0); fg.SetMaximum(1.15); fg.Draw(); fp.Draw("same")
    if k == 1:
        lg = ROOT.TLegend(0.50, 0.70, 0.93, 0.86); lg.SetBorderSize(0); lg.SetFillStyle(0); lg.SetTextSize(0.05)
        lg.AddEntry(fp, "Poisson (exact)", "L"); lg.AddEntry(fg, "Gaussian constraint", "L"); lg.Draw(); fs.append(lg)
    fs += [fp, fg]
c4.SaveAs("poisson_vs_gauss.png")
print("figures done")
