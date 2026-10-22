# CMS Higgs discovery 2012 (2020) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2020) Exercise 2020.3.2 (CMS- Higgs Discovery 2012) 
composite model; working with likelihoods, RooStats

Inspired by Figure 4 “Distribution of the four-lepton invariant mass” of: “Observation of a new boson at a mass of 125 GeV with the CMS experiment at the LHC”  arXiv:1207.7235v2 [hep-ex] 28 Jan 2013
https://arxiv.org/abs/1207.7235 , https://inspirehep.net/literature/1124338

Root files have been processed from the Higgs analysis example on the CMS 2011-2012 Open Data . 
Data source was https://github.com/cms-opendata-analyses/HiggsExample20112012.

In 2012, the Compact Muon Solenoid (CMS) experiment at the LHC presented results from searches for the standard model Higgs boson in proton-proton collisions at sqrt(s) = 7 and 8 TeV. The search is performed in five decay modes: gamma gamma, ZZ, WW, tau tau, and b b-bar. An excess of events is observed above the expected background at a mass near 125 GeV, signalling the production of a new particle compatible with standard model Higgs boson.

PART ONE – COMPOSITE MODEL

This exercise aims to reproduce the Figure 4 representing the  H → ZZ → 4 leptons decay mode

Define the four lepton invariant mass distribution as an observable. Take the range, binning and units from the final plot-

Download:

_cms_higgs_data.txt	real data

_cms_higgs_TTbarto4l.txt	top contribution (scaled to the MC generator cross section).

_cms_higgs_DYto4l.txt	Drell Yan (Z/*) contribution (scaled to the Z peak)

_cms_higgs_ZZto4l.txt	ZZ contribution 
(scaled to describe the data in the independent mass range 180-600 GeV

_cms_higgs_HZZto4l.txt	Higgs to ZZ to 4 leptons contribution

All files contain binned data. The file format is [BIN-CENTER]  [BIN WEIGHT].

The first (last) record is an underflow (overflow) bin and is outside the observable range. They should not be include.

Background histograms are already scaled to the final distribution.

Now, we want to build a composite model using the histograms stored in the file.

The final model is expected to looks like:

model(x) = f_s * sign(x) + (1 – f_s) * bkg(x)

where

f_s the fraction of signal

sign (x) the H → ZZ → 4 leptons distribution

bkg(x) the sum of background components to 4leptons from

The background is a sum of 3 components ttbar, DY and ZZ, and their distribution are stored in files.

Read all the binned dataset and fill a RooDataHist for each file:

Example code:

RooDataHist data{"data", "data", x};

ifstream file("filename.txt");

double val, weight;

while (!file.eof()) {

file >> val >> weight;

x.setVal(val);

…			data.set(x weight);  // (*)

}

Then, create a P.D.F. for each background component:

Hint: have a look to RooHistPdf in https://root.cern/doc/master/rf706__histpdf_8C_source.html

Build a composite model for the background only, such as

bkg(x) = f_ttbar * ttbar(x) + f_drly * drly(x) + (1- f_ttbar.- f_drly) * zz(x)

We want the fractions of the 3 background components to be fixed relative to one another.
Given that the input histograms are already scaled from the input files, f_ttbar and f_drly shall be set proportional to the relative weight of their RooDataHist integrals over the observable range.

Hint: use the method sum(kTRUE) of RooDataHist to get the integral over the observable range.

As approximation set a signal pdf using a Guassian distribution.

Let only the mean (mass of Higgs) be a floating parameter and fix the width to 3 GeV. 

Fit the model to the data. Only f_s and the mass of the Higgs are floating parameters.
Save the fit results to an object RooFitResults.

Plot the data and the fitted model.
Plot also the signal component in red and the total bkg component in black.

Write the best fit parameters on the plot too. (hint: paramOn(…) method of RooAbsPdf).

PART TWO: use a RooStats ProfileLikelihoodCalculator for a confidence interval.

Compute the 95% confidence interval for Higgs mass

The calculator considers systematics by eliminating nuisance parameters with the profile likelihood. This is equivalent to the method of MINOS (algorithm of MINUIT!).

Specify components of model for statistical tools

// Hint: create a model for statistical tools (ModelConfig), 
          a model config must be defined inside a RooWorkspace

RooWorkspace w;

RooStats::ModelConfig mc("model_config", &w);

Set the model, the observable, the Higgs mass as Parameter of Interest and f_s as nuisance parameter.

Compute the 95% confidence interval for Higgs mass with a Profile Likelihood Calculator.

Plot the interval.

Hint: use the ProfileLikelihood Calculator as shown in the slides…

PART THREE: use a RooStats ProfileLikelihoodCalculator for a Hypothesis test 
Compute the p-value and its corresponding significance for Higgs discovery

The variable fraction of signal (f_s) is somehow the signal strength in this composite model.

To establish a discovery one tries to reject the background only hypothesis corresponding to f_s = 0.

Change the model config and set f_s as Parameter of Interest and the Higgs mass as nuisance parameter.

Hint: use the ProfileLikelihood Calculator as shown in the slides…

The null hypothesis (i.e. the signal peak is a statistical fluctuation of the flat background) 
corresponds to f_s = 0, i.e. a null value for the parameter of interest.

Compute Significance and P-VALUE.

(submit source code, plots, and results as text file )

Exercise 3.2 -  composite model; profile likelihood

Repeat the last part of Exercise 3.1 running MINOS using “mixing” as parameter of interest instead of “dm2”.

(submit a text file with the snapshot of fit result)

Exercise 3.3 -  equivalence of profile likelihood and MINOS

Use some graphical tool (powerpoint, gimp, paint, root, …. ) to verify that the 68% confidence interval obtained by  intersecando la profile likelihood al valore 0.5 corresponds to the error estimated evaluated by MINOS by taking the edges of the contour plot at sigma = 1.
[see slide 88]

(Allegate l’immagine)

TMVA

Riferimenti:

- TMVA web site: http://tmva.sourceforge.net

- TMVA manual: TMVA - Toolkit for Multivariate Data Analysis , arXiv:physics/0703039v5 [physics.data-an]

- TMVA workshop ( http://indico.cern.ch/conferenceDisplay.py?confId=112879 )

In particolare “My tips and tricks” http://indico.cern.ch/contributionDisplay.py?contribId=5&confId=112879

- http://www.unibo.it/docenti/gabriele.sirri2  --> Contenuti utili   --> Analisi stat... Calendario e Materiale

La versione TMVA inclusa in ROOT contiene un set di utili macro :
- ROOT 5 : nella cartella $ROOTSYS/tmva/test/ 
- ROOT 6 : nella cartella $ROOTSYS/tutorials/tmva/

Per ogni esercizio, dovete creare un cartella di lavoro separata. 
Potete eseguire le macro direttamente dalla cartella di lavoro, da riga di comando in questo modo:

- ROOT 5 
root –l $ROOTSYS/tmva/test/TMVAClassification.C\(\"LD,MLP,BDT\"\)
root –l $ROOTSYS/tmva/test/TMVAGui.C

- ROOT 6 
root –l $ROOTSYS/tutorials/tmva/TMVAClassification.C\(\"LD,MLP,BDT\"\)
root –l TMVA::TMVAGui()

Quando è richiesto di modificare qualcosa (per esempio  TMVAClassification.C ), copiate la macro nella cartella di lavoro e lavorate sulla copia. Si raccomanda di non modificare le macro presenti in $ROOTSYS/tmva/test/ o $ROOTSYS/tutorials/tmva/ .

Nota: in Windows la sintassi è TMVAClassification.C\(\"LD,MLP,BDT\"\) , senza ‘\’ prima delle parentesi.

Scaricate “Tutorial 4 TMVA (files per iniziare)” da AMS Campus

Trovate il link in http://www.unibo.it/docenti/gabriele.sirri2

--> Contenuti utili  --> Analisi statistica dei dati ... Calendario e Materiale

In “Tutorial 4 TMVA (files per iniziare)” trovate:

- exercise70/ tmva_class_example.root	un root file necessario per l’esercizio tmva_ex70.C

- exercise71/ *.*	una serie di file necessario per l’esercizio tmva_ex71.C

Esercizio 70 – TMVAGui

Create una cartella di lavoro “tmva_ex70”

Copiate tmva_class_example.root nella cartella di lavoro (lo trovate anche in  http://root.cern.ch/files/tmva_class_example.root )

Eseguite la macro TMVAClassification.C . Eseguite il traning dei classificatory LD, MLP, BDT sul campione di dati di test. Non è richiesto di modificare la macro, solo di eseguirla:

root[] .x $ROOTSYS/tmva/test/TMVAClassification.C("LD,MLP,BDT")

Nel frattempo…    aprite TMVAClassification.C e localizzate nel codice dove sono definite:

i) le variabili di input per il training; 
ii) le variabili spettatori; 
iii) il tree del segnale e del background; 
iv) il peso del segnale e del background; 
v) i tagli di selezione del segnale e del background; 
vi) il numero di eventi di training e di testing; 
vii) la scelta dei metodi multivariate da applicare; 
viii) le chiamate di avvio del training, del test e dei paragoni fra I vara metodi.

Per usare il set di macro di TMVA (e vedere l’output del training e del test), eseguite:

root[] .x $ROOTSYS/tmva/test/TMVAGui.C     // se root v5
root[]  TMVA::TMVAGui()                    // se root v6

(Allegare i .png dei plot che ritenete più significativi)

(SKIP THE FOLLOWING)

Eseguite l’applivazione reader usando il seguente commando:
       root -l TMVAClassificationApplication.C\(\"LD,BDT\"\)

DOCUMENTATION:  slides shown during the lecture, then:

- TMVA web site: http://tmva.sourceforge.net

- TMVA manual: TMVA - Toolkit for Multivariate Data Analysis , arXiv:physics/0703039v5 [physics.data-an]

- TMVA workshop http://indico.cern.ch/contributionDisplay.py?contribId=5&confId=112879 (“My tips and tricks”)

Download

mva_generate_data.cpp 	generates data according to a 3-dimensional distribution for two different hypotheses (signal and background) and stores the result in a root file (as two TTree objects).

mva_plot_data.cpp 	fill and display some correlation plots of the variables

In the following exercises “XX” e “YYY” are referred to your matriculation numer, according to this formula: MATRICULATION NUMBER = YYY?XX .
