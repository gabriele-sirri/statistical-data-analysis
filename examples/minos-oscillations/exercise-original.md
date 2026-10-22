# MINOS composite model, working with likelihoods (2020) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2020) Exercise 2020.3.1  (MINOS)  composite model; working with likelihoods

Inspired by Figure 1 and Figure 2 of: “Measurement of Neutrino and Antineutrino Oscillations Using Beam and Atmospheric Data in MINOS”  arXiv:1304.6335v3 [hep-ex] 10 Jul 2013 
https://arxiv.org/abs/1304.6335

Neutrino oscillation provides direct evidence that neutrinos have non-zero mass and represents the only phenomenon observed to date with an origin beyond the Standard Model of particle interactions.

The MINOS Experiment was a long-baseline neutrino experiment designed to observe the phenomena of neutrino oscillations, an effect which is related to neutrino mass. The observed energy distributions of muon neutrino charged-current interactions in the MINOS Far Detector depends on the resulting neutrino oscillation probability, i.e. on mixing angles and on the differences between the squared neutrino masses.

The MINOS experiment performed precision measurements of oscillations via  disappearance. These oscillations are well described by an effective two-flavor model with flavor and mass eigenstates related by a single mixing angle

In this approximation, the  survival probability is given by

[Eq. 1]

where  (km) is the distance traveled by the neutrino,  (GeV) is its energy, and  (eV²) is the mass splitting.

PART 1 : DATA AND MODEL

Download:

minos_2013_data.dat 	unbinned dataset of a neutrino oscillation experiment

minos_2013_mc.dat		unbinned dataset of simulated neutrino oscillation experiment

Define your observable, which is the reconstructed neutrino energy. This variable ranges from 0.5 to 14 GeV

Load the unbinned dataset with events observed by the MINOS experiments

Hint: RooDataSet data = *RooDataSet::read("minos_2013_data.dat", energy, "v");

Then, build a model to describe such spectrum using the following instructions:

The energy distribution for non-oscillated neutrinos is simulated by a Monte Carlo. The resulting unbinned dataset is stored in the file minos_2013_mc.dat. Load this file into a RooDataSet object.

Then, use this Monte Carlo dataset to create an histogram-based function which represents the shape of the energy distribution for non-oscillated neutrinos
         Hint: an histogram-based function. is represented in RooFit by the RooHistFunc class. 
         Use the method binnedClone() to create a RooDataHist from the RooDataSet;
         then create a RooHistFunc object from the RooDataHist. 
    RooHistFunc func_noosc { "func_mc_noosc", "No oscillation", e, *dh_mc_noosc, 2 };

The shape of the energy distribution for oscillated neutrinos is obtained by multiplying this function by the oscillation probability shown in [Eq. 1]. The oscillation probability depends on mixing , mass splitting , neutrino energy (observable) and distance  km (constant).

Create the  variables mixing (i.e.  as a whole) and dm2 (i.e. ).

Create a RooFormulaVar to evaluate the oscillation probability expressed by the [Eq. 1]

Create the final p.d.f of the energy distribution of oscillated neutrino using a RooGenericPdf
     Hint: model = RooGenericPdf{ "model", "model", "@0*@1", 
                                        RooArgSet(prob_osc, func_noosc) };

Don’t care about normalization. RooFit will adjust it for you.

Now you can fit the model to the data. Plot data and model. Save the plot as minos_data.png.

PART 2:

You shall minimize the likelihood explicity by hand using a RooMinuit object 
(look to the slides pag 54)

Construct a function object representing the negative log likelihood of the model with respect to the data.
     Hint: use RooAbsPdf::createNLL(RooAbsData&), the returned object is a RooAbsReal*

Create a MINUIT interface object (RooMinuit)

Activate verbose logging of MINUIT parameter space stepping
     Hint: RooMinut::setVerbose(kTRUE)

Call MIGRAD to minimize the likelihood

Print values (use: RooRealVar::Print() ) of all parameters (dm2, mixing), that reflect values (and error estimates) that are back propagated from MINUIT as evaluated by MIGRAD [A]

Disable verbose logging

Run HESSE to calculate errors from the second derivative at maximum

Print values of all parameters (dm2, mixing), that reflect values (and error estimates) that are back propagated from MINUIT as evaluated by HESSE [B]

Run MINOS on dm2 parameter only

Print value of dm2 parameter, that reflect value (and error estimates) that are back propagated from MINUIT as evaluated by MINOS [C].
Please note that the error estimates is not symmetric.

Saving results.

Save a snapshot of the fit result. This object contains the initial fit parameters, the final fit parameters, the complete correlation  matrix, the EDM, the minimized FCN , the last MINUIT status code and  the number of times the RooFit function object has indicated evaluation problems (e.g. zero probabilities during likelihood evaluation).
      Hint: use RooMinuit::save() ; the returned value is a RooFitResult* type. Then, call Print(“v”) . [D]

Contour plot.

Make contour plot of dm2 vs mixing  at 1,2,3 sigma
      Hint: use RooMinuit::contour(var1, var2, n1, n2, n3 ); the returned value is a RooPlot* frame;
       plot the frame using the method Draw(..) as usual

Zoom (by hand) the plot axes to better visualize the countour. 
Save the plot as minos_likelihood.png

(submit source code, minos_data.png, minos_likelihood.png and a text file with the fit results obtained in [A], [B], [C], and [D])
