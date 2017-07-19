#define DileptonNtuple_cxx
#include "DileptonNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void DileptonNtuple::Loop(){

  Long64_t nentries = fChain->GetEntriesFast();
  //nentries = 1;

  hist_for_error = new TH1D("hist_for_error", "", 1, 0., 1.);
  hist_for_error_up = new TH1D("hist_for_error_up", "", 1, 0., 1.);

  for(Long64_t jentry=0; jentry<nentries;jentry++){
    GetEntry(jentry);

    if(!Pass()) continue;

    unweighted_yield += 1;
    weighted_yield += weight;

    hist_for_error->Fill(0. ,weight);
    hist_for_error_up->Fill(0., weight+weight_err);

  }

}























