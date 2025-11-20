Material available in the [data](../data) folder:
- roofit_empty.cpp an empty macro 
- roofit_empty.ipynb an empty notebook
- B0sInvariantMass.root invariant mass spectrum for a B0s meson (from LHCb)

# [0] WARM UP 

Download and run tutorials rf101, rf201, and rf202
https://root.cern/doc/master/group__tutorial__roofit.html

--
# [1] Hands-on: Basic functionality: fitting, plotting, toy data generation on one-dimensional PDFs. (BASIC)

## Exercise 2021.1 – fit a model to unbinned dataset

Create a Gaussian p.d.f. with mean = 0, and sigma = 1. Visualize the p.d.f. Change the sigma to 3.  Generate an **unbinned** dataset of 10000 events. Make a Fit with Maximum Likelihood. Visualize the results.

*Tips:*
<br>\- You can follow the comments inside the macro **roofit\_empty.cpp** or **roofit_empty.ipynb**
<br>\- *Use information from the slides shown during the lecture or from RooFit Manual at par 2*
<br>\- *Refer to the tutorial rf101\_basics.cxx*

---

## Exercise 2021.2 – fit a model to binned dataset

Create an Exponential p.d.f. to with rate = -1/tau where tau = 4.5  is the mean life. Visualize the p.d.f. . Generate a **binned** dataset of 1000 events **(bin width = 0.5)**.  Make a Fit with Maximum Likelihood. Visualize the results.

_Tips:_
<br>\- You can follow the comments inside the macro **roofit\_empty.cpp** or **roofit_empty.ipynb** 
<br>\- _Define the mean life as a RooRealVar and express the exponential rate using RooFormulaVar_
<br>\- _The binning of the returned RooDataHist is controlled by the default binning associated with the observables generated. To set the number of bins in x to 200, do e.g. x.setBins(200) prior to the call to generateBinned()_


---

## Exercise 12.2 – import a binned dataset, create a model using the factory, fit the model (LHCb)


One of the main objectives of the LHCb experiment is the study of the CP violation through the decay of different particles, like, for example, the b-flavored mesons.

Due to the short half-life, these particles can be observed by reconstructing their decay products and analyzing the so-called “invariant mass spectrum”.

The mass of the mesons is estimated by fitting a Breit-Wigner distribution.

In “B0sInvariantMass.root” an example of invariant mass spectrum for a B0s meson is stored.

Create a macro to open the “B0sInvariantMass.root” and import the corresponding binned dataset. Using RooFit factory and RooWorkspace, create a Breit-Wigner model. Fit the model to the binned dataset. Create a Gaussian function and fit to the data. Finally plot the data, and the BW and Gaussian distribution to the same canvas.

_Tips: 
<br>\- define the RooRealVar out of the factory, 
<br>\- read and import the data from the file and import in the workspace using RooWorkspace::import(…). 
You can see how to import data here:_ [https://root.cern.ch/doc/master/rf102\_\_dataimport_8C.html](https://root.cern.ch/doc/master/rf102__dataimport_8C.html)
<br>\- Compare the fitted value with the particle mass reported in the Particle Data Group. 

---

## Exercise 16.1 - The Central Limit Theorem - Sum of random variables


Using RooFit, define N=5 independent random variables $x_1, x_2, x_3, ...$ 
uniformly distributed between zero and one. Then, define a new variable as the sum of the N random variables $x_{sum} = \sum x_i $

Generate an unbinned dataset of 10000 events of variables $x_1, x_2, x_3, ...$.

You may be interested in the estimation of the expected mean and standard deviation of $x_{sum}$ (the sum of N measurements with a uniform distribution). It’s up to you to calculate it on the paper (it’s not expected you submit the solution).

use the formulas $\sigma = \sqrt{V(x)} = \sqrt{ \overline{x^2} - \overline{x}^2 } $, $\overline{x} = \int x F(x) dx 
$ and $ \overline{x^2} = \int x^2 F(x) dx $
where $F(x)$ 
is the distribution you are averaging over (For this case where $F(x)$

is a uniform distribution in range \[0,1\])

The Central Limit Theorem predicts that the sum of N measurements has a Gaussian distribution in the limit of N→∞ independent of the distribution of each individual measurement.

Then, create a Gaussian p.d.f. for $x_{sum}$ with mean and sigma as calculated before.

Make a Fit with Maximum Likelihood. Visualize the results.

_Tips:_
<br>\- _the product of random variable is distributed according a p.d.f. which is the product of the single p.d.f.s  (use  `RooProdPdf`)_
<br>\- _the variable “sum of random variable” can be defined in RooFit by adding a formula to the generated dataset, as shown in this example for 2 variables:_
``` cpp
// Construct formula to calculate the sum events
RooFormulaVar fsum{"fsum", "var1+var2 ", RooArgList{var1, var2} ;
// Add column with variable xsum to previously generated dataset
auto xsum = static_cast<RooRealVar\*>(data->addColumn(fsum));
```
\- _define a Gaussian model for xsum (sum of variables). With this respect, xsum behaves exactly as any other `RooRealVar`, even defined using  `RooFormulaVar`._
<br>\- _Range and binning are property of a `RooRealVar`. Given that xsum is defined using a `RooFormulaVar` and not with the `RooRealVar` class constructor, you have to explicitly specify a range and a binning to obtain a frame from `xsum`_
``` cpp
auto plot = xsum->frame(Bins(40), Title("Sum of Random variables"), Range(0., 6.));
```
<br>\- _Don’t’ forget to adjust the range..._

---

