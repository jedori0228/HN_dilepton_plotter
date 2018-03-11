#include "RunNtupleForBinnedYieldPlot.C"
#include "canvas_margin.h"

void GetFakeSyst(){

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/FakeSystematic/";

  vector<TString> channels = {
    "DiMuon",
    "DiElectron",
    "EMu",
  };

  vector<TString> WhichRegions = {
    "Preselection_SS",
    "Low_TwoJet_NoFatJet_SS",
    "Low_OneJet_NoFatJet_SS",
    "High_TwoJet_NoFatJet_SS",
    "High_OneFatJet_SS",
  };
  vector<TString> WhichRegionsForLatex = {
    "Preselection",
    "Low-mass SR1",
    "Low-mass SR2",
    "High-mass SR1",
    "High-mass SR2",
  };
  vector<TString> TreeDirNames = {
    "",
    "Skimmed_Low_TwoJet_NoFatjet",
    "Skimmed_Low_OneJet_NoFatjet",
    "Skimmed_High_TwoJet_NoFatjet",
    "Skimmed_High_OneFatJet",
  };

  vector<TString> allbkgs = {
    "fake_Dijet",
  };

  vector< vector<TString> > Muon_FRsystsources = {
    {"Awayjet_20", "Awayjet_30", "Awayjet_60"},
    {"dphi_1p5", "dphi_1", "dphi_3",},
    {"pj_over_pl_1", "pj_over_pl_2"},
  };
  vector< vector<TString> > Electron_FRsystsources = {
    {"Awayjet_20", "Awayjet_30", "Awayjet_60",},
    {"dphi_1p5", "dphi_2", "dphi_3",},
    {"pj_over_pl_0p8", "pj_over_pl_1p2"},
  };

  for(unsigned int it_channel=0; it_channel<channels.size(); it_channel++){

    TString channel = channels.at(it_channel);
    TString PD = "DoubleMuon";
    if(channel.Contains("DiElectron")) PD = "DoubleEG";
    if(channel.Contains("EMu")) PD = "MuonEG";

    TFile *file = new TFile(filepath+"/DiLeptonAnalyzer_SKfake_Dijet_"+PD+"_dilep_cat_v8-0-7.root");

    for(unsigned int it_region=0; it_region<WhichRegions.size(); it_region++){

      TString region = WhichRegions.at(it_region);

      //==== Prompt up/down

      TH1D *hist_central = (TH1D *)file->Get(region+"_FRsyst_Central");
      double y_central = hist_central->GetBinContent(1);
      TH1D *hist_statup = (TH1D *)file->Get(region+"_FRsyst_StatUp");
      double y_statup = hist_statup->GetBinContent(1);
      TH1D *hist_promptup = (TH1D *)file->Get(region+"_FRsyst_PromptUp");
      double y_promptup = hist_promptup->GetBinContent(1);
      TH1D *hist_BJet = (TH1D *)file->Get(region+"_FRsyst_BJet");
      double y_BJet = hist_BJet->GetBinContent(1);

      double syst_statup = fabs(y_statup-y_central)/y_central;
      double syst_promptup = fabs(y_promptup-y_central)/y_central;
      double syst_BJet = fabs(y_BJet-y_central)/y_central;
      cout << WhichRegionsForLatex.at(it_region) << "\t" << y_central << "\t" << syst_statup << "\t" << syst_promptup << "\t" << syst_BJet;

      double syst_promptsyst = syst_statup*syst_statup+syst_promptup*syst_promptup+syst_BJet*syst_BJet;

      //==== Other FR

      if(channel.Contains("DiMuon")){
        for(int i=0; i<Muon_FRsystsources.size(); i++){
          vector<TString> systs = Muon_FRsystsources.at(i);
          double syst_max = -999;
          for(int j=0; j<systs.size(); j++){
            TH1D *hist_this = (TH1D *)file->Get(region+"_FRsyst_Muon_"+systs.at(j));
            double this_yield = hist_this->GetBinContent(1);
            double this_syst = fabs(y_central-this_yield)/this_yield;
            if(this_syst>syst_max) syst_max = this_syst;
          }
          cout << "\t" << syst_max;
          syst_promptsyst += syst_max*syst_max;

          //cout << endl << "DEBUG : " << syst_promptsyst << endl;
        }
        cout << "\t\t\t\t" << sqrt(syst_promptsyst) << endl;
      }
      else if(channel.Contains("DiElectron")){
        cout << "\t\t\t";
        for(int i=0; i<Electron_FRsystsources.size(); i++){
          vector<TString> systs = Electron_FRsystsources.at(i);
          double syst_max = -999;
          for(int j=0; j<systs.size(); j++){
            TH1D *hist_this = (TH1D *)file->Get(region+"_FRsyst_Electron_"+systs.at(j));
            double this_yield = hist_this->GetBinContent(1);
            double this_syst = fabs(y_central-this_yield)/this_yield;
            if(this_syst>syst_max) syst_max = this_syst;
          }
          cout << "\t" << syst_max;
          syst_promptsyst += syst_max*syst_max;
        }
        cout << "\t" << sqrt(syst_promptsyst) << endl;
      }
      else if(channel.Contains("EMu")){
        for(int i=0; i<Muon_FRsystsources.size(); i++){
          vector<TString> systs = Muon_FRsystsources.at(i);
          double syst_max = -999;
          for(int j=0; j<systs.size(); j++){
            TH1D *hist_this = (TH1D *)file->Get(region+"_FRsyst_Muon_"+systs.at(j));
            double this_yield = hist_this->GetBinContent(1);
            double this_syst = fabs(y_central-this_yield)/this_yield;
            if(this_syst>syst_max) syst_max = this_syst;
          }
          cout << "\t" << syst_max;
          syst_promptsyst += syst_max*syst_max;
        }
        for(int i=0; i<Electron_FRsystsources.size(); i++){
          vector<TString> systs = Electron_FRsystsources.at(i);
          double syst_max = -999;
          for(int j=0; j<systs.size(); j++){
            TH1D *hist_this = (TH1D *)file->Get(region+"_FRsyst_Electron_"+systs.at(j));
            double this_yield = hist_this->GetBinContent(1);
            double this_syst = fabs(y_central-this_yield)/this_yield;
            if(this_syst>syst_max) syst_max = this_syst;
          }
          cout << "\t" << syst_max;
          syst_promptsyst += syst_max*syst_max;
        }
        cout << "\t" << sqrt(syst_promptsyst) << endl;
      }
      else{

      }

    }
  }

}

