 #include "RooRealVar.h"
 #include "RooDataSet.h"
 #include "RooGaussian.h"
 #include "TCanvas.h"
 #include "RooPlot.h"
 #include "TAxis.h"
 using namespace RooFit;
  
 void roofit_empty_en()
 {
    // S e t u p   m o d e l
    // ---------------------
  
    // Declare variables x,mean,sigma with associated name, title, initial value and allowed range
    
    // Build gaussian pdf in terms of x,mean and sigma
    
    // Construct plot frame in 'x'
    
    // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
    // ---------------------------------------------------------------------------
  
    // Plot gauss in frame (i.e. in x)
    
    // Change the value of sigma to 3 
    
    // Plot gauss in frame (i.e. in x) and draw frame on canvas
    
    // G e n e r a t e   e v e n t s
    // -----------------------------
  
    // Generate a dataset of 1000 events in x from gauss
    
    // Make a second plot frame in x and draw both the
    // data and the pdf in the frame

  
    // F i t   m o d e l   t o   d a t a
    // -----------------------------
  
    // Fit pdf to data
    
    // Print values of mean and sigma (that now reflect fitted values and errors)
    
    // Draw all frames on a canvas
    
 }
 