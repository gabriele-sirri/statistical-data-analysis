import ROOT

# Declare observable x
x = ROOT.RooRealVar("x", "x", 0, 10, "GeV")

# Create one Gaussian PDFs g1(x,mean1,sigma) and its parameters
mean = ROOT.RooRealVar("mean", "mean of gaussians", 5)
sigma = ROOT.RooRealVar("sigm", "width of gaussians", 0.5)

sig = ROOT.RooGaussian("sig", "Signal component", x, mean, sigma)

# Build Chebychev polynomial p.d.f.
a0 = ROOT.RooRealVar("a0", "a0", 0.5, 0., 1.)
a1 = ROOT.RooRealVar("a1", "a1", 0.2, 0., 1.)

bkg = ROOT.RooChebychev("bkg", "Background", x, ROOT.RooArgSet(a0, a1))

# Sum the composite signal and background
#
# case 1: shape-ONLY model
#         𝑚(𝑥)= Prod( 𝑓 𝑠(𝑥)+(1−𝑓)𝑏(𝑥) )
#
# case 2: Extended LikeliHood Formalism, Rate * Shape
#         𝑚(𝑥)= Pois (n_obs | n_s+n_b ) 
#              * Prod( n_s* 𝑠(𝑥)+ n_b* 𝑏(𝑥) ) / (n_s + n_b) 
#       
#         define nbkg (nsig) as expected number of events of the bkg (sig) component
#         exploit the properties of RooAddPdf for adding Pois
#         and - as usual in RooFit - forget about the normalization 
#
# case 3: use the signal strength mu as paramter of interest
#         𝑚(𝑥)= Pois (n_obs | mu * n_s + n_b ) 
#              * Prod( mu * n_s* 𝑠(𝑥)+ n_b* 𝑏(𝑥) ) / ( mu * n_s + n_b) 
#


# Create a second gaussian pdf

m2 = ROOT.RooRealVar('m2', 'm2', 3, 0, 5) # mean 
s2 = ROOT.RooRealVar('s2', 's2', 0.3, 0.00001, 1) # sigma

gaus2 = ROOT.RooGaussian('g2', 'g2', x, m2, s2)    # second gaus
# case 1: shape-ONLY model
#         𝑚(𝑥)= Prod( 𝑓1 * 𝑠1(𝑥)+ f2 * s2(x) + (1−𝑓1-f2) * 𝑏(𝑥) )

f1 = ROOT.RooRealVar('f1', 'fraction of first signal component', 0.2, 0, 1)  
f2 = ROOT.RooRealVar('f2', 'fraction of second signal component', 0.3, 0, 1)

model = ROOT.RooAddPdf('model', 'composite model', 
                       ROOT.RooArgList(sig, gaus2, bkg),
                       ROOT.RooArgList(f1,f2))


# visualization

frame = x.frame()

model.plotOn(frame)
model.plotOn(frame, 
             ROOT.RooFit.Components('bkg'),
             ROOT.RooFit.LineColor(ROOT.kRed),
             ROOT.RooFit.LineStyle(ROOT.kDashed))
c = ROOT.TCanvas()
frame.Draw()
c.Draw()
# case 2: Extended LikeliHood Formalism, Rate * Shape
#         𝑚(𝑥)= Pois (n_obs | n_s+n_b ) 
#              * Prod( n_s* 𝑠(𝑥)+ n_b* 𝑏(𝑥) ) / (n_s + n_b) 
#       
#         define nbkg (nsig) as expected number of events of the bkg (sig) component
#         exploit the properties of RooAddPdf for adding Pois
#         and - as usual in RooFit - forget about the normalization 

n1 = ROOT.RooRealVar('n1','n. of expected events for sig', 10, 0, 100)
n2 = ROOT.RooRealVar('n2','n. of expected events for gaus2', 20, 0, 100)
nbkg = ROOT.RooRealVar('nbkg', 'n. of expected bkg events', 100, 0, 300)

# create the final model

model2 = ROOT.RooAddPdf('model2', 'rate*shape model', 
                        ROOT.RooArgList(sig, gaus2, bkg),
                        ROOT.RooArgList(n1, n2, nbkg))
# generate a toy MC for model2

data = model2.generate(x) # generate an unbinned dataset of events

data.Print()
# case 3: use the signal strength mu as parameter of interest
#         𝑚(𝑥)= Pois (n_obs | mu * n_s + n_b ) 
#              * Prod( mu * n_s* 𝑠(𝑥)+ n_b* 𝑏(𝑥) ) / ( mu * n_s + n_b)

# replace "n_s" with "mu * n_s" <-- n. of expected events for sig
#
# mu is the new parameter which modelize the excess of sig 
#     mu = 0 the model reduces to the banckground-only
#     mu = 1 the signal yield is the nominal one (e.g the one predicted ny the theory)
#     when mu is not compatible to 0 we have an excess of signal
#
# n_s becomes a constant <-- nominal n. of expected events for sig. 

n_s = ROOT.RooRealVar('n_s', 'nominal n. of expected events for sig', 11)

mu = ROOT.RooRealVar('mu', 'signal strength', 1, 0, 3)

# n_sig = mu * n_s n. of expected events for sig ???
n_sig = ROOT.RooFormulaVar('n_sig', '@0 * @1', ROOT.RooArgList(mu, n_s))

# create the final model

model3 = ROOT.RooAddPdf('model3', 'rate*shape model with mu', 
                        ROOT.RooArgList(sig, gaus2, bkg),
                        ROOT.RooArgList(n_sig, n2, nbkg))
#                                         ^
#                                       n_sig

p = x.frame()

data.plotOn(p)

c = ROOT.TCanvas()
p.Draw()
c.Draw()
