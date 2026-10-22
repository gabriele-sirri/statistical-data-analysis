# MAGIC gamma telescope (2020) — original exercise text (draft extraction)

> Plain-text extraction from the 2018–2021 tutorial collection. **Equations, figures and tables are missing.** Use the original document for the full statement.

(2020) Exercise 2020.tmva - MAGIC Gamma Telescope Data Set

Inspired by “Neural networks for gamma-hadron separation in MAGIC”  arXiv:astro-ph/0503539 24 Mar 2005 https://arxiv.org/abs/astro-ph/0503539

Go to https://archive.ics.uci.edu/ml/datasets/MAGIC+Gamma+Telescope

read Data Set Information, the Attributes Information and download the MAGIC Gamma Telescope Data Set.

Data are MC generated to simulate registration of high energy gamma particles in an atmospheric Cherenkov telescope: it is composed by 12332 gamma (signal) events and 6688 hadron events (background).

--

For this exercise you shall perform a simple multivariate analysis using TMVA and other ROOT routines.

Reference

- https://nbviewer.jupyter.org/url/root.cern/doc/master/notebooks/classification.C.nbconvert.ipynb

- TMVA basic manual: https://root.cern/manual/tmva/

- TMVA user manual: https://root.cern/download/doc/tmva/TMVAUsersGuide.pdf

TMVA is expected to create lots of auxiliary files, so it’s strongly suggested to create a new working folder in order to have a clean place where to perform the analysis.

The most straightforward way to get started with TMVA is to simply run an example macro: 		$ROOTSYS/tutorials/tmva/TMVAClassification.C. 
(Hint: again, don’t get your ROOT installation dirty: copy the macro or in your working folder)

Change the file TMVAClassification.C (or write your own tmva_training.cpp macro following the example code shown during the lecture) in such a way that a data loader is created to perform the following actions:

define the input variables that shall be used for the mva training;

read in the “signal” and the ”background” data sets;

Hint: The data loader is flexible, input data can be Rootfiles as well as Text files. See TMVA Users Guide and pay attention that in the guide AddBackgroundTree(..), AddSignalTree(..), SetInputTrees(..) are methods of the factory while in the recent ROOT implementation thery are methods of the dataloader.

Code example 6, for signal and background stored as different TTrees from TFile sources (root files);

Code example 7, for signal and background stored in the same TTree form a TFile source;

Code example 9, for signal and background stored as different TEXT files.

In case of text file, you can process the input file at your convenience before reading data.

Book a list of classifiers: Cuts, Fisher, MLPBNN, and BDT. The first is an automatic rectangular cut optimization, the second one is the Fisher discriminant, the third one is a neural network, and the last one is a standard boosted decision tree.

Now run training and testing.

TMVA automatically splits the data internally into a training set and a test set.

Hint: see the slides of the course. When you prepare the training and test tree consider the following options to split the sample in order to use half of the events for training, half for testing
NTrain_Signal=0:NTrain_Background=0:NTest_Signal=0:NTest_Background=0

Hint: to book the multilayer perceptron you need a line of the form:
factory->BookMethod(TMVA::Types::kMLP, "MLP", "H:!V:HiddenLayers=N+5");
See the TMVA manual for more details. 
.

Hint: to book a BDT with 200 boosting iterations you need a line of the form:
factory->BookMethod(TMVA::Types::kBDT, "BDT", 
                    "NTrees = 200:BoostType = AdaBoost");
See the TMVA manual for more details.

FISHER:

determine the coefficients of a Fisher discriminant. 
When you run the program, the coefficients of the discriminating functions are written into a subdirectory weights as text files. Take a look at these files and identify the relevant coefficients.

MLP & BDT

Coefficients of the multilayer perceptron and BDT are stored in a file in the weights subdirectory.

Open the TMVAGUI:

Have a look at the input variable distributions.

Look how different the signal and the background are distributed.

Assume that the expected number of respectively signal and background events are 10 and 100.

At which values would you cut to separate the signal from the background?

submit the source code, relevant plots (not more than 5), a text file with your answer

For willing students:
the macro called by the “(5a) Classifier Cut Efficiencies” button of TMVAGUI compute a significance using an approximated formula Z = sqrt(S /(S+B ))  (S – number of signal, B – number of background).

create a new macro my_mvaeff.cpp based on $ROOTSYS/include/tmva/mvaeff.h (or mvaeff.C in ROOT 5) to estimate the expected discovery significance with the following formula:

G. Cowan et al., “Asymptotic formulae for likelihood-based tests of new physics”, ., Eur. Phys. J. C71, 1554 (2011)

Submit the plot created by the modified macro

Exercise 2021.tmva - ATLAS full-detector simulation, with "Higgs to tautau" events

Inspired by arXiv:1501.04943v3 [hep-ex] 27 Apr 2015  
https://arxiv.org/abs/1501.04943


Please go to “Dataset from the ATLAS Higgs Boson Machine Learning Challenge 2014” http://opendata.cern.ch/record/328, read the data set information, the attributes information (a.k.a. dataset semantics) and download the Data Set.

Dataset is built from official ATLAS full-detector simulation, with "Higgs to tautau" events mixed with different backgrounds. It is composed by 818238 events (279560 signal and 539768 background).

Dataset is saved as CSV file.

Hint: you may use the macro prepare_dataset.cpp  to  read the CSV and create a TTree. The macro exploits ROOT::RDataFrame, a high level interface for analyses of data stored in TTree, CSV's and other data formats.

Note:
Don’t use the following variable as INPUT VARIABLE for the MVA analysis.
- “EventId”, “KaggleSet”, “KaggleWeight” 
- “Weight” because is a weight and must be properly set as the individual event weight (!)
- “Label” because is the flag to disentangle the signal sample from the background sample. It originates from the monte-carlo truth and is a basic information for the training (but it is not an input variable of course…)

--

For this exercise you shall perform a simple multivariate analysis using TMVA and other ROOT routines.

Reference

- https://nbviewer.jupyter.org/url/root.cern/doc/master/notebooks/classification.C.nbconvert.ipynb

- TMVA basic manual: https://root.cern/manual/tmva/

- TMVA user manual: https://root.cern/download/doc/tmva/TMVAUsersGuide.pdf

--

TMVA is expected to create lots of auxiliary files, so it’s strongly suggested to create a new working folder in order to have a clean place where to perform the analysis.

The most straightforward way to get started with TMVA is to simply run an example macro: 		$ROOTSYS/tutorials/tmva/TMVAClassification.C. 
(Hint: again, don’t get your ROOT installation dirty: copy the macro or in your working folder)

Change the file TMVAClassification.C (or write your own tmva_training.cpp macro following the example code shown during the lecture) in such a way that a data loader is created to perform the following actions:

define the input variables that shall be used for the mva training;

read in the “signal” and the “background” data sets;

Hint: The data loader is flexible, input data can be Rootfiles as well as Text files. See TMVA Users Guide and pay attention that in the guide AddBackgroundTree(..), AddSignalTree(..), SetInputTrees(..) are methods of the factory while in the recent ROOT implementation thery are methods of the dataloader.

Code example 6, for signal and background stored as different TTrees from TFile sources (root files);

Code example 7, for signal and background stored in the same TTree form a TFile source;

Code example 9, for signal and background stored as different TEXT files.

In case of text file, you can process the input file at your convenience before reading data.

Set the individual event weight for signal and background

Book a list of classifiers: Cuts, Fisher, MLPBNN, and BDT. The first is an automatic rectangular cut optimization, the second one is the Fisher discriminant, the third one is a neural network, and the last one is a standard boosted decision tree.

Now run training and testing.

TMVA automatically splits the data internally into a training set and a test set.

Hint: see the slides of the course. When you prepare the training and test tree consider the following options to split the sample in order to use half of the events for training, half for testing
NTrain_Signal=0:NTrain_Background=0:NTest_Signal=0:NTest_Background=0

Hint: see the slides of the course. When you prepare the training and test tree consider the following options to split the sample in order to use 10k (20k) of the signal (background) events for training, the rest  for testing
NTrain_Signal=10000:NTrain_Background=20000:NTest_Signal=0:NTest_Background=0

Hint: to book the multilayer perceptron you need a line of the form:
factory->BookMethod(TMVA::Types::kMLP, "MLP", "H:!V:HiddenLayers=N+5");
See the TMVA manual for more details. 
.

Hint: to book a BDT with 200 boosting iterations you need a line of the form:
factory->BookMethod(TMVA::Types::kBDT, "BDT", 
                    "NTrees=200:BoostType=AdaBoost");
See the TMVA manual for more details.

FISHER:

determine the coefficients of a Fisher discriminant. 
When you run the program, the coefficients of the discriminating functions are written into a subdirectory weights as text files. Take a look at these files and identify the relevant coefficients.

MLP & BDT

Coefficients of the multilayer perceptron and BDT are stored in a file in the weights subdirectory.

Open the TMVAGUI:

Have a look at the input variable distributions.

Look how different the signal and the background are distributed.

Assume that the expected number of respectively signal and background events are 2000 and 6000.

At which values would you cut to separate the signal from the background?

submit the source code, relevant plots (not more than 5), a text file with your answer

For willing students:
the macro called by the “(5a) Classifier Cut Efficiencies” button of TMVAGUI compute a significance using an approximated formula Z = sqrt(S /(S+B ))  (S – number of signal, B – number of background).

create a new macro my_mvaeff.cpp based on $ROOTSYS/include/tmva/mvaeff.h (or mvaeff.C in ROOT 5) to estimate the expected discovery significance with the following formula:

G. Cowan et al., “Asymptotic formulae for likelihood-based tests of new physics”, ., Eur. Phys. J. C71, 1554 (2011)

Submit the plot created by the modified macro

TUTORIAL 5 : Introduzione a RooStats

Riprendiamo l’esercizio della precedente lezione su RooFit 
(gaussian signal + exponential background, extended p.d.f.) .

Scaricate “Tutorial 5 (files per iniziare)” da AMS Campus

Trovate il link in http://www.unibo.it/docenti/gabriele.sirri2

--> Contenuti utili  --> Analisi statistica dei dati ... Calendario e Materiale

In “Tutorial 5 (files per iniziare)” trovate:

- makemodel :	c’è la costruzione del modello , la generazione di un set di  1000 dati simulato. Il workspace è salvato in «model.root».
Alcune modifiche rispetto alla lezione precedente :
Range e Valori iniziali dei parametri sono stati modificati.
«mean» e «sigma» sono fissati come costanti.
I dati sono importati nel workspace e salvati su file.

- usemodel : 	legge il modello dal file, esegue il fit del modello 
e disegna dati e risultato del fit in un plot.

Riferimenti:

- http://www.unibo.it/docenti/gabriele.sirri2  --> Contenuti utili   --> Analisi stat... Calendario e Materiale

- ROOSTATS    : https://twiki.cern.ch/twiki/bin/view/RooStats
- short tutorial : https://twiki.cern.ch/twiki/bin/view/RooStats/RooStatsTutorialsAugust2012

- RooStatsTutorial_120323.pdf https://indico.desy.de/getFile.py/access?contribId=15&resId=3&materialId=slides&confId=5065

Esercizio 30 -  Confidence Interval con  ProfileLikelihoodCalculator

Si modifichi il modello:

Specificare i componenti del modello per i tool statistici di RooStats:  
pdf, osservabile e parametro di interesse.

Utilizzare il numero di eventi di segnale come unico parametro di interesse.

Fissare costanti tutti gli altri parametri del modello.

Importare la configurazione nel workspace e salvare su file.

NOTA: 	Attenzione alla generazione : la generazione è fatta secondo il rapporto dei valori impostati di Ns e Nb . Se si genera con  ->generate(*x,N) allora avremo N*Nb/(Nb+Ns) eventi di background e N*Ns/(Nb+Ns) eventi di segnale.
In questo caso è facile introdurre dei problemi: ad esempio,  supponiamo Nb=1000 costante e Ns variabile con valore iniziale Ns =100, se scelgo “male” N (esempio N =1000), roofit produrra’ un campione di dati simulati con 909 eventi di background e 91 di segnale; successivamente cercherei erroneamente di fittare Ns a questi dati avendo però nel modello Nb=1000 costante, con la risultante sottostima di Ns.
La soluzione è usare RooRealVar::setVal(…) per definire i valori di Ns che e Nb prima di simulare i dati e successivamente  generare(*x) senza indicare “N” ; in questo caso il numero di dati simulati sarà Ns+Nb .

Si modifichi l’uso del modello:

leggere il modelConfig dal workspace 
esempio: ModelConfig* mc = (ModelConfig*) w.obj("ModelConfig");

calcolare un Confidence Interval al 90% utilizzando il ProfileLikelihoodCalculator
Suggerimento: usare  ProfileLikelihoodCalculator plc(*data,*mc) dove mc è il ModelConfig anziché   ProfileLikelihoodCalculator plc(*data, *pdf, *poi_var) come indicato in alcune slide

Disegnare il profilo della likelihood e sovrapporre l’intervallo

calcolare la discovery significance utilizzando il profilelikelihoodcalculator
come test di ipotesi

scrivere sulla console i limiti dell’intervallo e la significatività

(Allegate il file .cxx e il .png )

Esercizio 31 -  Confidence Interval con  Feldman-Cousin

Aggiungere l’intervallo calcolato con Feldman-Cousin

suggerimenti : modificare solo usemodel()

guardare il codice in :  $ROOTSYS/tuturials/roostats/IntervalExamples.C

Esercizio 32 -  Confidence Interval con  Feldman-Cousin

Definire tau e Nb come nuisance parameters  ;  ripetere i test dell’ex. 30 e confrontarli .

suggerimento modificare makemodel()  (vedere il tutorial) 
(Allegate il file .cxx e il .png )

Esercizio 40 – Counting Model con termini di constraint

Esercizio 50 – Counting Model con termini di constraint

Run $ROOTSYS/tutorials/roostats/StandardHypoTestDemo.C  for hypothesis test (for computing the discovery significance) using all RooStats hypothesis tests calculators and test statistics.

Run this macro on the Gaus+Exp Model

Run this macro on the Poisson Counting Model 
(in this case set useNC = true , “NC” = “Number Counting” )

Provate a utilizzare diversi test calculators e test statistici. 
Se il metodo è Bayesiano ricordate che dovete mettete delle prior .

(Allegare il file .cxx dei modelli, file txt con i risultati del calcolo di significance e i png dei plot ottenuti)
