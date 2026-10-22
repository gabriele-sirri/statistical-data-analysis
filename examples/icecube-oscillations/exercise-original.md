# IceCube oscillations (2019/2021) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2019) Exercise 2019.minuit.ex1 - IceCube Oscillations: 3 years muon neutrino disappearance data
(2021) Exercise 2021.minuit - IceCube Oscillations: 3 years muon neutrino disappearance data

Inspired by https://icecube.wisc.edu/science/data/nu_osc

https://arxiv.org/pdf/1410.7227.pdf

In the 1990s, Super-K and MACRO’s measurements of atmospheric neutrinos led to the acceptance of the mass-induced oscillation model.

As of today, the three mixing angles, the solar mass splitting and the absolute value of the atmospheric mass splitting that control the oscillation phenomenon have been measured. The existence of CP-violation and the ordering of the masses remain open issues.

Here’s a measurement of neutrino oscillations via atmospheric muon neutrino disappearance with three years of data of the completed IceCube neutrino detector in Antartica released in 2015.

DeepCore, a region of denser instrumentation, enables the detection and reconstruction of atmospheric muon neutrinos between 10 GeV and 100 GeV, where a strong disappearance signal is expected. The detector volume surrounding DeepCore is used as a veto region to suppress the atmospheric muon background. Neutrino events are selected where the detected Cherenkov photons of the secondary particles minimally scatter, and the neutrino energy and arrival direction (or zenith angle)are reconstructed. Both variables are used to obtain the neutrino oscillation parameters from the data. The results are compatible and comparable in precision to those of dedicated oscillation experiments.

You can view the paper here: arXiv:1410.7227

In the simplest scenario, with only two neutrino flavors, the survival probability is given by:

[Eq. 1]

Where the  (km) is the distance traveled by the neutrino,  (GeV) is the neutrino energy,  (eV²) is the neutrino mass splitting and  is the neutrino mixing.

Atmospheric neutrinos are produced in the upper atmosphere. The arrival direction (or zenith angle) is a direct measurement of the flight length L. 
For vertical downward neutrinos: cos(zenith) = 1 and  km , 
For horizontal neutrinos : cos(zenith) = 0 and  km , 
For vertical upward neutrinos: cos(zenith) = -1 and  km ,

Description of the data set

Data are stored as binned dataset in icucube.dat file. Each row provides the counts of neutrino events for a range of arrival direction (cos(zenith)) and neutrino energy (log10(E/GeV)) with the following format:

min(cos(zenith))	max(cos(zenith))	min(log10(E/GeV))	max(log10(E/GeV))	Counts

PART 1 : DATA AND MODEL

Define your observable, which is the reconstructed neutrino energy and the arrival direction. The data set is binned, so find the proper ranges and binnings !!

Load the binned dataset with events observed by ICECUBE

Hint: create one RooDataHist for the two observables  RooArgList{ cos_z, log_e}
         open the file, 
         loop on the raw, evaluate the bin center for each observables,
        set each observable to the bin center value
        fill the RooDataHist with the RooDataHist::set method using the Count as weight,
Hint2: the following example is limited to the case of one-dimensional RooDataHist

RooDataHist data{"data", "data", x};

ifstream file("enubet_histo.dat");

double bin_center, bin_content;

while (!file.eof()) {

file >> bin_center >> bin_content;

x.setVal(bin_center);

data.set(x, bin_content);

}

Then, build a model to describe such spectrum using the following instructions:

We assume here the neutrino energy and the arrival direction distribution for non-oscillated neutrinos are flat. We neglect also any background component. 
As a consequence, the shape of the distribution of neutrino energy and arrival direction for oscillated neutrinos is just the survival probability shown in [Eq. 1].

The oscillation probability depends on mixing , mass splitting , neutrino energy (observable) and distance

Create the variables mixing (i.e.  as a variable) and dm2 (i.e. ).

You can find the current global fit on Particle Data Group pubblications

Mixing ranges from 0.00001 (avoid border) to 1

Dm2 ranges from 0.00001 to 0.03 eV

Use RooFormulaVar to define the distance L from the cos(zenith); 
for the sake of simplicity,  define L as  “100-13000 * cos(zenith)”

Use RooFormulaVar to define the energy E from the log(E/GeV);

Create the p.d.f of neutrino energy and arrival direction of oscillated neutrino by implementing the [Eq. 1] in a RooGenericPdf
     Hint: example: RooGenericPdf model{"model", "model", "1+2+@0*@1", 
                                        RooArgSet(x, y) };

Don’t care about normalization. RooFit will adjust it for you.

Now you can fit the model to the data.

PART 2: PLOT DATA

Divide the a TCanvas according to the number of bins of the energy dataset.

For each bin, define a range for the energy ( example: log_e.setRange("erange1", 0.80, 0.92); ). Then, take a one-dimensional frame (a RooPlot) for the arrival direction cos_z and plot data and model, constraining the range.

(willing students may plot the data, set the mixing parameter to 0, plot the model before fitting, then superimpose the model after fitting)

Hint:example    	y.setRange(“sig”, -1,1);
				auto fx = x.frame();
				data->plotOn(fx, CutRange(“sig”));
				model.plotOn(fx, ProjectionRange(“sig”));

Hint: https://root-forum.cern.ch/t/roofit-a-easy-way-to-save-the-initial-values-and-set-them/6364
Save the canvas as data.png.

PART 3:

You shall minimize the likelihood explicity by hand using a RooMinuit object  (look to the slides pag 54)

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

Zoom the plot axes. Save the plot as contour.png

(submit source code, data.png, contour.png and a text file with the fit results obtained in [A], [B], [C], and [D])
