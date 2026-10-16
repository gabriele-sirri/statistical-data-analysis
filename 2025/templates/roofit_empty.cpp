
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"

using namespace RooFit;

int roofit_empty()
{
  // Impostazione del modello
  // ---------------------

  // Dichiara le variabili x,media,sigma associando nome, titolo, valore
  // iniziale e intervallo x e' l'osservabile, media e sigma sono parametri

  // Costruisci un modello utilizzando una p.d.f. gaussiana in termini di x,mean
  // and sigma

  // Costruisci la vista (plot frame) per 'x'

  // Visualizza il modello. Cambia un parametro
  // ------------------------------------------

  // Disegna il modello nella vista (i.e. in x)

  // Cambiare il valore del parametro sigma a 3  ( suggerimento: usare il metodo
  // setVal di RooRealVar)

  // Disegna il modello modificato nella stessa vista (i.e. in x)

  // ToyMC: Generare 10000 eventi
  // ----------------------------

  // Genera un dataset (unbinned) di 1000 eventi x secondo il modello

  // Costruisci una seconda vista (plot frame) per 'x'
  // e disegna sia il modello che il dataset nel in questa nuova vista

  // Fittare il modello ai dati
  // --------------------------

  // Fittare modello ai dati

  // Visualizzare (sulla shell) i valori dei parametri media e sigma
  // (ora dovrebbero rappresentare il risultato del fit)

  // Visualizza le due viste su una canvas

  return 0;
}
