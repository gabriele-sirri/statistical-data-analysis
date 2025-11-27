/*
## Exercise 2021.1 – fit a model to unbinned dataset

Create a Gaussian p.d.f. with mean = 0, and sigma = 1. 
Visualize the p.d.f. Change the sigma to 3.  
Generate an **unbinned** dataset of 10000 events.
Make a Fit with Maximum Likelihood. Visualize the results.

*Tips:*
 - You can follow the comments inside the macro **roofit\_empty.cpp**
   or **roofit_empty.ipynb**
 - *Use information from the slides shown during the lecture or from
    RooFit Manual at par 2*
 - *Refer to the tutorial rf101\_basics.cxx*
*/

// run this example from the command line
// $ root -l live_coding_session1.cpp

void live_coding_session1()
{
  // S e t u p   m o d e l
  // ---------------------

  // Declare variables x,mean,sigma with associated name, title, initial value
  // and allowed range
  RooRealVar x("x", "x", -10, 10);
  RooRealVar mean("mean", "mean of gaussian", 0, -10, 10);
  RooRealVar sigma("sigma", "width of gaussian", 1, 0.00001, 10); // WARNING: don't set the lower limit of sigma exactly equal to 0
  
  // Build gaussian p.d.f in terms of x,mean and sigma
  RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma); 
  //NOTE: no need a third parameter for the height. RooFit automatically takes care about normalization.

  // Construct plot frame in 'x'
  auto xframe = x.frame();   // return a RooPlot* (pointer)

  // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
  // ---------------------------------------------------------------------------

  // Plot gauss in frame (i.e. in x)
  gauss.plotOn(xframe);  // Note: the model is normalized to 1

  // Change the value of sigma to 3
  sigma.setVal(3);

  // Plot gauss in frame (i.e. in x) and draw frame on canvas
  gauss.plotOn(xframe, RooFit::LineColor(kRed)); 

  new TCanvas;
  xframe->Draw();

  // G e n e r a t e   e v e n t s
  // -----------------------------

  // Generate a dataset of 1000 events in x from gauss
  RooDataSet* data = gauss.generate(x, 1000);

  // Make a second plot frame in x and draw both the
  // data and the p.d.f in the frame
  auto xframe2 = x.frame();  // return a RooPlot* (pointer)
  data->plotOn(xframe2);     // Warning: plot the the data before the model!  
  gauss.plotOn(xframe2);     // Note: the model is normalized to the n. of events of the dataset

  // F i t   m o d e l   t o   d a t a
  // -----------------------------

  // Fit pdf to data
  gauss.fitTo(*data);

  // Print values of mean and sigma (that now reflect fitted values and errors)
  mean.Print();
  sigma.Print();

  // Draw all frames on a canvas
  new TCanvas;
  xframe2->Draw();
}
