# Poisson counting with uncertain background, on/off, hypothesis test (2018–2020) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2018) Exercise 40  Poisson Counting Model with uncertain background

(2019) Exercise 40  Poisson Counting Model with uncertain background

This exercise is just intended to let you practice with ModelConfig and several RooStats calculators.You are not requested to submit anything.

(2020) Exercise 40  Poisson Counting Model with uncertain background
credits: Exercise 4: Create a Poisson Counting Model 
https://twiki.cern.ch/twiki/bin/view/RooStats/RooStatsTutorialsJune2013

Let's suppose we observe nobs events when we expect nexp, where nexp = s+b (s is the number of signal events and b is the number of background events. The expected distribution for nexp is a Poisson Poisson( nobs | s+b). s is the parameter we want to estimate or set a limit (the parameter of interest), while b is the nuisance parameter.  b is not known exactly, but has uncertainty sigmab. The nominal value of b is  “b0”. To express this uncertainty we add in the model a Gaussian constraint. We can interpret this term as having an additional measurement b0 with an uncertainty sigmab: i.e. we have a likelihood for that measurement Gaussian( b0 | b, sigma). In case of Bayesian statistics we can interpret the constraint as a prior knowledge on the parameter b.

Make first the RooFit workspace using its factory syntax. Let's assume nobs=3, b0=1, sigmab=0.2.

Create the ModelConfig object and import in the workspace. We need to add in the ModelConfig also b0 as a “global observable”. The reason is that b0 needs to be treated as an auxiliary observable in case of frequentist statistics and varied when tossing pseudo-experiments.

The following Hints are based on the RooFit factory, but you’re not obliged to use the factory.

Hint:  We make first the RooFit workspace using its factory syntax. We have nobs=3, b0=1, sigmab=0.2.

int nobs = 3;   // number of observed events

double b0 = 1; // number of background events

double sigmab = 0.2;   // relative uncertainty in b

RooWorkspace w("w");

// make Poisson model * Gaussian constraint

w.factory("sum:nexp(s[3,0,15],b[1,0,10])");

// Poisson of (n | s+b)

w.factory("Poisson:pdf(nobs[0,50],nexp)");

// Gaussian constraint to express uncertainty in b

w.factory("Gaussian:constraint(b0[1,0,10],b,sigmab[0.2])");

// the total model p.d.f will be the product of the two

w.factory("PROD:model(pdf,constraint)");

We need also to define b0, the global observable, as a constant variable (being an observable in the frequentist approach cannot change when we fit the model. However, b0 needs to have a range for the normalization of the Gaussian).

w.var("b0")->setConstant(true);

After creating the model p.d.f, create the ModelConfig object and we set b0 as a global observable

ModelConfig mc("ModelConfig",&w);

mc.SetPdf(*w.pdf("model"));

mc.SetParametersOfInterest(*w.var("s"));

mc.SetObservables(*w.var("nobs"));

mc.SetNuisanceParameters(*w.var("b"));

// need now to set the global observable

mc.SetGlobalObservables(*w.var("b0"));

// this is needed for the hypothesis tests

mc.SetSnapshot(*w.var("s"));

// import model in the workspace

w.import(mc);

We generate a hypothetical observed data set. Since we have a counting model, the data set will contain only one event and the observable nobs will have our desired value (i.e. 3). Remember to import the data set in the workspace and then save the workspace in a ROOT file.

// make data set with the namber of observed events

RooDataSet data("data","", *w.var("nobs"));

w.var("nobs")->setVal(nobs);

data.add(*w.var("nobs") );

// import data set in workspace and save it in a file

w.import(data);

w.writeToFile("CountingModel.root", true);

Compute a 95% upper limit on the signal parameter s, using RooStats Profile Likelihood Calculator
Hint: use the ProfileLikelihood Calculator as shown in the slides…
The null hypothesis (i.e. the signal peak is a statistical fluctuation of the flat background) corresponds to s=0, i.e. a null value for the parameter of interest.

As an alternative, you can exploit this macro without writing any line of source code:
$ROOTSYS/tutorials/roostats/StandardProfileLikelihoodDemo.C

(optional) Compute a 95% upper limit on the signal parameter s, using RooStats Feldman-Cousins Calculator.
Hint:  you can exploit $ROOTSYS/tutorials/roostats/StandardFeldmanCousinsDemo.C

This exercise is meant as preparatory for the next one, don’t submit code.

next is on_off - Observation of the Top Quark

see Exercise 40  Poisson Counting Model with uncertain background as preparatory exercise

(2020) Exercise 2020.on_off - Observation of the Top Quark

Inspired by Table 1 of “Evaluation of three methods for calculating statistical significance when incorporating a systematic uncertainty into a test of the background-only hypothesis for a Poisson process”  arXiv:physics/0702156v4 [physics.data-an] 20 Nov 2008 https://arxiv.org/abs/physics/0702156

The test case implemented here is referred to data published in “Observation of the Top Quark” Phys.Rev.Lett.74:2632-2637,1995, https://arxiv.org/abs/hep-ex/9503003

PART I

Change the values of exercise 40 according to the D0 collaboration results as described in the abstract (i.e. set the number of observed events, the number of expected background events and it’s sigma).

Compute p-value and significance and verify it is compatible with the published one.

Hint: use the ProfileLikelihood Calculator as described in the slides.

(submit the source code, report the resulting significance and p-value in the source code as a comment)

PART II

Create a counting model based on Poisson Statistics as in Exercise 40 but suppose the total number of observed events is nobs = 17 and the background b is estimated from a sideband region where the signal is not expected. This auxiliary measurement of background consists of the observation of noff = 40 events while tau*b  are expected. The parameter tau denotes the ratio of the expected means of noff and nobs. 
Suppose it is known exactly or with negligible uncertainty and is tau=10.53.

Hint: you can define the expected number of events in the sideband region using the expression: 	w.factory("prod:tau_b(tau[10.53],b)");

Compute p-value and significance and verify it is compatible with the published one.

Hint: use the ProfileLikelihood Calculator as described in the slides.

(submit the source code, report the resulting significance and p-value in the source code as a comment)

(2018) Exercise 41 On/Off problem

(2019) Exercise 41 On/Off problem

Inspired by “Evaluation of three methods for calculating statistical significance when incorporating a systematic uncertainty into a test of the background-only hypothesis for a Poisson process”  arXiv:physics/0702156v4 [physics.data-an] 20 Nov 2008 
https://arxiv.org/abs/physics/0702156

Create a counting model based on Poisson Statistics as in Exercise 40 but suppose the background b is estimated from another counting experiment carried out in a sideband region where the signal is not expected. This auxiliary measurement of background consists of the observation of noff = 90 events while tau*b  are expected. The parameter tau denotes the ratio of the expected means of noff and nobs. Suppose it is known exactly or with negligible uncertainty and is tau=100.

Hints: you can define the expected number of events in the sideband region using the expression: 	w.factory("prod:tb(t[100],b)");

Compute a 95% upper limit on the signal parameter s, using RooStats Profile Likelihood Calculator

Compute a 95% upper limit on the signal parameter s, using RooStats Feldman-Cousins Calculator.

(submit the source code, the plot of the profile likelihood interval and  text file with the resulting intervals)

(2018) Exercise 42  Hypothesis test

Compute the significance of observing the Co-60 signal of the extended combined model described in the Exercise 16 of Tutorial 2 (Cuore-0 experiment).

Hint: set reasonable ranges for all parameters 
	- n. of flat background events: [0,400]
	- n. of signal and of Co-60 events: [0,100]
	- width of signal and Co-60 sources: [1,7] keV.

Hint: create the Model Config using the number of Co-60 events as parameter of interest, the remaining floating parameters are nuisance

  // define set of nuisance parameters

w->defineSet("nuisance_params", "n_sgn,n_bkg,co_width,sgn_width");

mc.SetNuisanceParameters(*w->set("nuisance_params"));

Hint: in order to evaluate the significance use the ProfileLikelihood Calculator as described in the slides. The null hypothesis (i.e. the Co-60 peak is a statistical fluctuation of the flat background) corresponds to n. of Co60 events = 0, i.e. a null value for the parameter of interest.

(submit the source code, the plot of the profile likelihood interval at 90% and a text file with the resulting significance)
