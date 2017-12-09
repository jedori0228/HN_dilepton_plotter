#include "canvas_margin.h"
#include "mylib.h"

void Draw_SignalDistribution(){

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Regions/Signal/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalDistribution/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<int> masses = {40, 50, 60, 70, 80};
  vector<Color_t> colors = {kRed, kOrange, kGreen, kBlue, kViolet};
  vector<TString> channels = {"MuMu", "ElEl", "MuEl"};


  vector<TString> regions = {"Low_TwoJet_NoFatJet"};
  vector<TString> vars = {"m_Leadljj_lljjWclosest", "m_SubLeadljj_lljjWclosest", "m_lljj_lljjWclosest", "leadingLepton_Pt", "PFMET", "m_ll", "secondLepton_Pt"};

/*
  vector<TString> regions = {"Low_OneJet_NoFatJet"};
  vector<TString> vars = {"m_Leadlj", "m_SubLeadlj", "m_llj", "leadingLepton_Pt", "PFMET", "m_ll", "secondLepton_Pt"};
*/
  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    for(unsigned int k=0; k<regions.size(); k++){
      TString region = regions.at(k);

      for(unsigned int l=0; l<vars.size(); l++){

        TCanvas *c1 = new TCanvas("c1", "", 600, 600);
        canvas_margin(c1);
        c1->Draw();
        c1->cd();

        TH1D *hist_dummy = new TH1D("hist_dummy", "", 250, 0., 250.);
        hist_dummy->Rebin(5);
        hist_dummy->Draw("hist");
        hist_axis(hist_dummy);
        hist_dummy->GetYaxis()->SetRangeUser(0., 1.1);

        for(unsigned j=0; j<masses.size(); j++){

          TString mass = TString::Itoa(masses.at(j),10);

          TString filename = "DiLeptonAnalyzer_SKHN"+channel+"_"+mass+"_cat_v8-0-7.root";
          TFile *file = new TFile(base_filepath+filename);

          TString PDName = "";
          if(channel=="MuMu") PDName = "DiMuon";
          if(channel=="ElEl") PDName = "DiElectron";
          if(channel=="MuEl") PDName = "EMu";

          TString histname = PDName+"_"+region+"_SS/"+vars.at(l)+"_"+PDName+"_"+region+"_SS";
          TH1D *hist = (TH1D *)file->Get(histname);
          if(!hist) continue;

          hist->Rebin(5);
          hist->SetLineColor(colors.at(j));
          double y_max = GetMaximum(hist);
          hist->Scale(1./y_max);
          
          hist->Draw("histsame");

        }

        c1->SaveAs(base_plotpath+"/HN"+channel+"_"+region+"_"+vars.at(l)+".pdf");
        c1->Close();

      }


    }


  }

}
