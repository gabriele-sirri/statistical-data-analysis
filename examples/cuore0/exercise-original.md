# CUORE-0 composite extended model (2020) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2020) Exercise 2020.composite.extended.cuore0

Inspired by Figure 10 of: “Analysis Techniques for the Evaluation of the Neutrinoless Double-β Decay Lifetime in 130Te with CUORE-0”  arXiv:1601.01334v3 [nucl-ex] 27 Apr 2016;
https://arxiv.org/abs/1601.01334

CUORE is a cryogenic experiment at Laboratori Nazionali del Gran Sasso to search for the neutrinoless double-β decay (0νββ decay) of Te-130 using a segmented array TeO2 bolometric detectors operated at extremely low temperatures. CUORE-0 was a prototype operated from 2013 to 2015.

The CUORE-0 physics spectrum spanned over a very large range of reconstructed energy. The Region of Interest (ROI) for the 0νββ decay analysis was defined as the range 2470–2570 keV; this region contained 233 events.

The ROI contains:

a flat background;

the hypothetical signal of 0νββ decay at 2527 keV;

a peak from the single-crystal coincidence of the two γ-rays from Co-60 decay which lies 21 keV below the signal

Using RooFit, define an extended composite model for the spectrum:

model(x) = n_sig*sig(x) + n_co60 *co60(x) +n_bkg*bkg(x)

where x is the reconstructed energy.

The signal peak is a Gaussian distribution with a constant mean fixed at the expected peak value and a sigma floating in the range 0.0001 - 60 keV. The same applies to the Co-60 peak.

Download   cuore0.dat 		unbinned dataset

Load the unbinned dataset with 233 eventi from the file cuore0.dat

Tip: RooDataSet data = *RooDataSet::read("cuore0.dat", x, "D");

Fit the model to the data using a maximum likelihood fit. Plot data and model. Superimpose each single component with different color

Tip: use the named functions RooFit::Components(…) and RooFit::LineColor(…).

evaluate the number of background (signal) events in the signal range

To follow the instructions given below here you shall import data and model in workspace w; check the content of the workspace with w.Print() before continue.

Working with RooWorkspace is not mandatory, you can apply the native RooFit classes if you want.

1. use of sub-ranges

- define a ‘signal range’ in observable x:

w.var("x")->setRange("sigrange",2498,2514) ;

- Create an integral object that represents the fraction of background events in the signal range

w.factory("int::f_bkg_sigRange(bkg,x|sigrange,x)") ;

the first x indicates which observable to integrate over and in which range, the second x indicates which observables to normalize over. 
(Without a range specification this would result in 1 by construction)

- Retrieve the value of the fraction by calling

w.function("f_bkg_sigRange")->getVal() ;

- Now construct a formula named Nbkg_sigRange that expresses the number of background events in the signal range: use product operator

w.factory("prod:: n_bkg_SigRange(n_bkg,f_bkg_sigRange)")

- Evaluate the n_bkg_SigRange function in the workspace to count the number of signal events in the range [2498,2514]

2. Linear error propagation

Now we calculate the error on n_bkg_SigRange. To that end we first need to save a RooFitResult object from the fitTo() operation:

Save the RooFitResult* pointer returned by fitTo() in an object named fr, and add a Save() argument to fitTo() to instruct to make sure an fit resulted will be returned.

Calculate the error on the number of background events by calling
w.function(“n_bkg_SigRange”)->getPropagatedError(*fr) ;

3. Repeat step 1 and 2 to evaluate the number of signal in the signal range n_sig_sigRange and its error

Make histogram of residual and pull distributions

Have a look to https://root.cern.ch/doc/master/rf109__chi2residpull_8C.html

Note: methods residHist(…) and pull(..) by default  compute the residuals (pulls) of the latest-plotted histogram with respect to the latest-plotted curve.

-> Construct a histogram with the residuals of the data w.r.t. the curve

-> Construct a histogram with the pulls of the data w.r.t the curve

-> Create a new frame to draw the residual distribution and add the distribution to the frame

-> Create a new frame to draw the pull distribution and add the distribution to the frame

Additional task…

Visualize the correlation matrix

Look at the correlation matrix of the fit.

To make a visual presentation of the correlation matrix, save the RooFitResult object returned by fitTo(..) (don’t forget to add RooFit::Save() as argument of fitTo(..)) 

Then, add the following code:

TCanvas c;
gStyle->SetPalette(1) ;
fit_results->correlationHist()->Draw(“colz”) ;

Discussion (it may not apply to this problem): 
What are the largest correlations?

If correlations are very strong (>>0.9) the model may become unstable and it may be worthwhile to fix one of the parameters in the fit.

This works best if the correlation is between two nuisance parameters (i.e. non-physics parameters)

If a correlation is between a parameter of interest (= physics) and a nuisance parameter (=others) fixing a nuisance parameter will strongly underestimate the uncertainty on physics parameter and you’ll need another strategy to control the error on the nuisance parameter.
