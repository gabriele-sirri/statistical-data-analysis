# LHCb B0 → p p̄ (2021) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2021) Exercise 2021.composite.LHCb  First observation of the rare purely baryonic decay

Inspired by Figure 1 of: “First observation of the rare purely baryonic decay ”  arXiv:1709.01156v2 [hep-ex] 6 Dec 2017; https://arxiv.org/abs/1709.01156

See also https://cerncourier.com/a/the-rarest-b0-decay-ever-observed/

In 2017 the LHCb collaboration has observed the rare baryonic decay . The branching fraction was measured at the level of about 1.3 per 100 million decays, which makes this decay mode the rarest decay of a B0 meson ever observed. It is also the rarest observed hadronic decay of all beauty mesons.

The search for the rare decays  and  had previously been performed by LHCb with the full 3  data sample collected during the first run of the LHC. An excess of  candidates with respect to the background-only hypothesis is observed with a statistical significance of 5.3 standard deviations. The hint of a  signal reported in 2013 is, however, not confirmed, and an upper limit for the corresponding branching fraction was set. The measured  and  branching fractions are compatible with the latest theoretical calculations.

The exercise aims to reproduce the Invariant Mass Distribution of Figure 1

Download   rarest_b0_decay.dat 		dataset collected by a B-meson experiment

Load the unbinned dataset from the file rarest_b0_decay.dat

Tip: RooDataSet data = *RooDataSet::read("rarest_b0_decay.dat", x, "v");

Using RooFit, define an (non-extended) composite model for invariant mass.

The model components are:

a background (you’re free to choose the model: 
flat, polynomial, chebysev polynomial, exponential, …);

a guassian peak around the  mass

a guassian peak around the  mass

Fit the model to the data using a maximum likelihood fit. Plot data and model.

Superimpose each single component with different color

Tip: use the named functions RooFit::Components(…) and RooFit::LineColor(…).

Comment: you probably don’t see the plot as you expected… set reasonable ranges of signal peaks and assume that  and  have the same widths to make the model easier.

PART 2:

evaluate the number of background (signal) events in the signal range

To follow the instructions given below here you shall import data and model in workspace w; check the content of the workspace with w.Print() before continue.

Working with RooWorkspace is not mandatory, you can apply the native RooFit classes if you want.

1. use of sub-ranges

- define a ‘signal range’ in observable x:

w.var("x")->setRange("sigrange",5320,5400) ;

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

RooFit: working with likelihoods

DOCUMENTAZIONE:  Utilizzate le informazioni dalle slide mostrate a lezione e anche da:

- Manuale di RooFit:  https://root.cern.ch/download/doc/RooFit_Users_Manual_2.91-33.pdf

- Sito web di RooFit:  https://root.cern.ch/roofit-20-minutes
- Tutorials di RooFit:  https://root.cern.ch/root/htmldoc/tutorials/roofit/index.html
- Slide su RooFit:     http://hadron.physics.fsu.edu/~skpark/document/ROOT/roofit-intro-roostats-v12a.pdf

Nota: le pagine indicate nei suggerimenti si riferiscono a:  http://hadron.physics.fsu.edu/~skpark/document/ROOT/roofit-intro-roostats-v12a.pdf

Esercizio 11 -  composite model; working with likelihoods

Utilizzando la factory di RooFit come è stato fatto per l’esercizio 9, creare un modello che abbia i seguenti ingredient:

l’osservabile è una variabile “x” definita tra -20 e 20

il modello è composto dalla somma di due gaussiane:     f*gaus1(..)+(1-f)*gaus2(..)
La media di entrambe le gaussiane è “mean” e vale 0 (costante). La sigma della prima gaussiana è “s1” e vale 3.k (costante) dove k è l’ultima cifra del vostro numero di matricola. La sigma della seconda gaussiana è “s2” ed è definita sull’intervallo [3,6] con valore iniziale 4. Il coefficiente “f” ha valore iniziale 0.5 e non è costante.

Nota: questo modello contiene forti correlazioni.

Generare un dataset con 1000 eventi.

SALVARE IL WORKSPACE (MODELLO + DATI) SU FILE .

Minimizzare la likelihood passandola “a mano” direttamente a un oggetto RooMinuit. 
[vedere pag. 48]

costruire una unbinned (negative log) likelihood del modello rispetto ai dati generati, utilizzando il metodo RooAbsPdf::createNLL(RooAbsData&) ; l’oggetto restituito dalla funzione è di tipo RooAbsReal*

costruire un interfaccia MINUIT alla funzione likelihood

attivare la modalità verbosa per visualizzare gli step di MINUIT 
(usare RooMinut::setVerbose(kTRUE) )

chiamare MIGRAD per minimizzare la likelihood

visualizzare (con RooRealVar::Print() ) il valore dei parametri  f,mean,s1,s2 . 
Notare che valori (e errori) ora riflettono il risultato di MIGRAD. [A]

disattivare la modalità verbosa

chiamare HESSE per calcolare gli errori con d^2 L/dp^2

visualizzare (con RooRealVar::Print() ) il valore dei parametri  f,mean,s1,s2 .
Notare che gli errori ora riflettono il risultato di HESSE. [B]

chiamare MINOS per il parametro “s2”

visualizzare (con RooRealVar::Print() ) il valore dei parametri  f,mean,s1,s2 .
Notare che gli errori di “s2” ora sono asimmetrici.  [C]

Salvare i risultati.

Salvare uno snapshot del risultato del fit. Questo oggetto contiene i valori iniziali e finali del parametric, la matrice di correlazione, il valore di EDM, il valore di FCN, l’ultimo status code di MINUIT  e il numero di volte in cui MINUIT ha trovato problem di computazione (es. probabilità nulla durante la valutazione della likelihood).
Utilizzare il metodo RooMinuit::save() ; l’oggetto restituito dalla funzione è di tipo RooFitResult*. Fate il Print(“v”) . [D]

Contour plot.

Creare un contour plot di “f” vs “s2” at 1,2,3 sigma, utilizzando il metodo RooMinuit::contour(var1, var2, n1, n2, n3 ); l’oggetto restituito dalla funzione è un plot frame (il solito oggetto di tipo RooPlot* )

Disegnate il plot frame (solito metodo Draw() ) e salvare su file.

(Allegate il file esercizio11.cxx, l’immagine della canvas in formato .png  e un file testo contenente i risultati indicati da [A], [B], [C], [D])

Esercizio 12 -  composite model; profile likelihood

Caricate il workspace salvato dall’esercizio precedente. [ Attenzione: non eseguite da capo l’esercizio 11. I dati devono essere gli stessi ]
Allo stesso modo dell’esercizio precedente: create un oggetto neg log likelihood (NLL) e minimizzatelo chiamando migrad().

Partendo dalla NLL, costruire una profile likelihood per il parametro “s2”, utilizzando il metodo RooAbsReal * RooAbsReal::createProfile( const RooArgSet & paramsOfInterest); l’oggetto restituito è di tipo RooAbsReal* ed è la profile likelihood. [vedere pag. 52]

Questo metodo elimina tutti i parameteri (di nuisance) dalla funzione eccetto quello dichiarato in paramsOfInterest (il parametro di interesse).

Create un plot frame (oggetto di tipo RooPlot) per il parametro “s2” 
Plottate sul frame la NLL, utilizzando il metodo plotOn() come al solito 
Aggiungete l’argomento ShiftToZero() a plotOn() verificate cosa succede al plot della NLL.

Plottate sul frame la Profile Likelihood in rosso , utilizzando il metodo plotOn() come al solito a aggiungendo l’argomento LineColor(kRed) .

Aggiustate il range del plot frame in modo che i punti dove la profile likelihood assume il valore 0.5 siano facilmente individuabili; utilizzando RooPlot::setMinimum(…) e RooPlot::SetMaximum().

Disegnate il plot frame su una canvas e salvate su file.

(Allegate il file esercizio12.cxx, l’immagine della canvas in formato .png  )

Esercizio 13 -  composite model; profile likelihood

Ripetere l’esercizio 12 utilizzando “f” come parametro di interesse anziche’ “s2”

(Allegate il file esercizio13.cxx, l’immagine della canvas in formato .png  )

Esercizio 14 -  equivalenza MINOS – profile likelihood

Utilizzare un qualche tool grafico (powerpoint, gimp, paint, root, …. ) per verificare che l’intervallo al 68% individuato intersecando la profile likelihood al valore 0.5 corrisponde all’errore computato da MINOS prendendo gli estremi del contour plot per sigma = 1.
[vedere pag. 53]

(Allegate l’immagine)
