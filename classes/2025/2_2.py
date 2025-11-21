import ROOT

# define observable
x = ROOT.RooRealVar('x', 'observable', -20, 20)   # range -20,20 

#define constants
m = ROOT.RooRealVar('m', 'mean', 0) # mean fixed to 0 and shared by both Gaussians
s1 = ROOT.RooRealVar('s1', 's1', 3.123) # constant

# parameters
s2 = ROOT.RooRealVar('s2', 's2', 4, 3, 6) # parameter
f = ROOT.RooRealVar('f', 'f', 0.5, 0, 1)

# model
gaus1 = ROOT.RooGaussian('g1', 'g1', x, m, s1)
gaus2 = ROOT.RooGaussian('g2', 'g2', x, m, s2)

model = ROOT.RooAddPdf('model', 'my model', 
                       ROOT.RooArgList(gaus1, gaus2),
                       ROOT.RooArgList(f))

# Generate an unbinned dataset data of 1000 events from the model
data = model.generate(x, 1000)
# save a workspace
w = ROOT.RooWorkspace('w')
w.Import(model)
w.Import(data)

w.writeToFile('test.root')

w.Print()
# minimize the Negative Log-Likelihood

# create a NLL function
nll = model.createNLL(data)

# create an MINUIT instance
minuit = ROOT.RooMinimizer(nll)
f.Print()
s2.Print()
minuit.setVerbose(True)

# run migrad
minuit.migrad()
f.Print()
s2.Print()
minuit.setVerbose(False)

# run HESSE Error Calculation
minuit.hesse()
f.Print()
s2.Print()
# run minos
minuit.minos(s2)
f.Print()
s2.Print()
fit_results = minuit.save()

fit_results.Print('v')
#  Visualize the correlation matrix 
 
c = ROOT.TCanvas()

fit_results.correlationMatrix().Draw('colZ')

c.Draw()
# Contour Plot

frame = minuit.contour(f, s2, 1, 2, 3)

c2 = ROOT.TCanvas()
frame.Draw()
c2.Draw()

