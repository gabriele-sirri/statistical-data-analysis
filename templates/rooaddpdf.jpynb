import ROOT

# Declare observable x
x = ROOT.RooRealVar("x", "x", 0, 10)

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
