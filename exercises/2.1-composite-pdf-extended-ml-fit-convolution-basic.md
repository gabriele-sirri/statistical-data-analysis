Templates available in the [templates](../templates) folder:
- `roofit_empty.cpp` - an empty macro 
- `roofit_empty.ipynb` - an empty notebook

  
# [0] WARM UP

Download and run tutorials rf502, rf503 (RooWorkspace), rf511
(factory) and rf601 (Minuit)
https://root.cern/doc/master/group__tutorial__roofit.html

--

# [1] Hands-on: RooWorkspace, Factory, Composite Model

## Exercise 13.1 - Composite Model: Signal + Background (Non-extended)

Edit the `roofit_empty` macro and, following the outline:
-  build a Gaussian PDF with  `mean` = 0 and `sigma` = 3.  
Call this Gaussian PDF **`sig`**.

- Add an exponential background component **`bkg`**, defined as  $\exp(-x/\tau)$ with an initial value of **$\tau = 10$**.

- Define a parameter **`fsig`** representing the signal fraction $f_{sig}$.  
- Construct the composite model:
  <br>$  \mathrm{model}(x)=f_{sig}\cdot \mathrm{sig}(x)+(1−f_{sig})\mathrm{bkg}(x)
  $

Then, 
- Visualize the PDF.  
- Generate a **binned dataset** of **1000 events** (bin width = 0.5).  
- Perform a **Maximum Likelihood fit** and visualize the results.
<br>

> Hints:
> - Use `RooFormulaVar` to express `-1./tau`.  
> - Use `RooAddPdf` for the composite model.  
> - Use `generateBinned(...)` to generate the binned dataset.  

## Exercise 13.2 - Extended ML Fit

- Rewrite Exercise 13.1 so that the model is suitable for **extended ML fitting**.

- Multiply:
  - the signal PDF by **Nsig = 200** (range: 0-10000)  
  - the background PDF by **Nbkg = 800** (range: 0-10000)
