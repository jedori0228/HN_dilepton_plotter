#include "canvas_margin.h"
#include "mylib.h"

void GetTnPTriggerSystematic(){

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  vector<TString> systs = {"Central", "NMassBins30", "NMassBins50", "MassRange_60_130", "MassRange_70_120", "SignalShapeSingleV", "TagPt30Iso0p08", "TagPt30Iso0p08", "ProbeMult99"};
  vector<Color_t> colors = {kBlack,     kRed,           kOrange,          kYellow,        kGreen,           kBlue,                kViolet,            kGray,          kCyan};

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = ENV_PLOT_PATH+"/TnP_Results/TriggerSF/";
  TString base_plotpath = ENV_PLOT_PATH+"/TnP_Results/TriggerSF/";

  vector<TString> DataPeriods = {"BCDEF", "GH"};
  vector<double> abseta = {0., 0.9, 1.2, 2.1, 2.4};
  vector<TString> fitftns = {"vpvPlusExpo", "vpvPlusExpoPassFail", "voigtPlusExpo", "voigtPlusExpoPassFail", "vpvPlusCheb_3rd", "vpvPlusCheb_4th"};
  vector<TString> triggers = {"DoubleIsoMu17Mu8_IsoMu17leg", "Mu8_OR_TkMu8"};


  for(unsigned int it_DataPeriod=0; it_DataPeriod<DataPeriods.size(); it_DataPeriod++){

    TString DataPeriod = DataPeriods.at(it_DataPeriod);

    for(unsigned int it_trigger=0; it_trigger<triggers.size(); it_trigger++){

      TString trigger = triggers.at(it_trigger);

      //==== Let's loop Eta Region, and get Eff vs pT
      //==== pt_PLOT_abseta_bin0_Data
      //==== pt_PLOT_abseta_bin0_MC

      for(int it_eta=0; it_eta<=3; it_eta++){

        TCanvas *c_Data = new TCanvas("c_Data", "", 800, 800);
        TPad *c_Data_up = new TPad("c_Data", "", 0, 0.25, 1, 1);
        TPad *c_Data_down = new TPad("c_Data_down", "", 0, 0, 1, 0.25);
        canvas_margin(c_Data, c_Data_up, c_Data_down);
        c_Data_down->SetGridx();
        c_Data_down->SetGridy();
        c_Data_up->Draw();
        c_Data_down->Draw();
        c_Data_up->cd();

        TCanvas *c_MC = new TCanvas("c_MC", "", 800, 800);
        TPad *c_MC_up = new TPad("c_MC", "", 0, 0.25, 1, 1);
        TPad *c_MC_down = new TPad("c_MC_down", "", 0, 0, 1, 0.25);
        canvas_margin(c_MC, c_MC_up, c_MC_down);
        c_MC_down->SetGridx();
        c_MC_down->SetGridy();
        c_MC_up->Draw();
        c_MC_down->Draw();
        c_MC_up->cd();

        TString eff_name = "pt_PLOT_abseta_bin"+TString::Itoa(it_eta,10);

        TGraphAsymmErrors *gr_Data_Central;
        TGraphAsymmErrors *gr_MC_Central;

        TLegend *lg = new TLegend(0.6, 0.1, 0.93, 0.5);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);
        for(unsigned int it_syst=0; it_syst<systs.size(); it_syst++){

          TString syst = systs.at(it_syst);
          TString filepath = base_filepath+DataPeriod+"/"+syst+"/"+trigger+"/";

          vector<double> pt = {10, 20, 25, 30, 40, 50, 60, 120};
          if(trigger=="DoubleIsoMu17Mu8_IsoMu17leg") pt = {10, 15, 16, 17, 18, 19, 20, 25, 30, 40, 50, 60, 120};

          TFile *file = new TFile(filepath+"MuonTriggerEfficiency_HNDILEP_"+trigger+"_Run"+DataPeriod+".root");

          TGraphAsymmErrors *gr_Data = (TGraphAsymmErrors*)file->Get(eff_name+"_Data");
          TGraphAsymmErrors *gr_MC = (TGraphAsymmErrors*)file->Get(eff_name+"_MC");

          if(syst=="Central"){
            gr_Data_Central = (TGraphAsymmErrors*)gr_Data->Clone();
            gr_MC_Central = (TGraphAsymmErrors*)gr_MC->Clone();
          }
          else{
            RemoveLargeError(gr_Data);
            RemoveLargeError(gr_MC);
          }

          gr_Data->SetLineColor(colors.at(it_syst));
          gr_Data->SetMarkerColor(colors.at(it_syst));
          gr_MC->SetMarkerColor(colors.at(it_syst));
          gr_MC->SetLineColor(colors.at(it_syst));

          lg->AddEntry(gr_Data, syst, "p");

          TString DrawOption = "psame";
          if(it_syst==0) DrawOption = "ap";

          //==== Data
          c_Data_up->cd();
          gr_Data->Draw(DrawOption);
          if(it_syst==0){
            gr_Data->GetYaxis()->SetRangeUser(0., 1.1);
          }
          c_Data->cd();
          c_Data_down->cd();
          TGraphAsymmErrors *gr_diff_Data = GraphSubtract( gr_Data, gr_Data_Central );
          hist_axis( gr_Data, gr_diff_Data );
          gr_diff_Data->Draw(DrawOption);
          gr_diff_Data->SetLineColor(colors.at(it_syst));
          gr_diff_Data->SetMarkerColor(colors.at(it_syst));
          gr_diff_Data->SetMarkerStyle(21);
          if(it_syst==0){
            gr_diff_Data->GetYaxis()->SetRangeUser(-0.01, 0.01);
          }

          //==== MC
          c_MC_up->cd();
          gr_MC->Draw(DrawOption);
          if(it_syst==0){
            gr_MC->GetYaxis()->SetRangeUser(0., 1.1);
          }
          c_MC->cd();
          c_MC_down->cd();
          TGraphAsymmErrors *gr_diff_MC = GraphSubtract( gr_MC, gr_MC_Central );
          hist_axis( gr_MC, gr_diff_MC );
          gr_diff_MC->Draw(DrawOption);
          gr_diff_MC->SetLineColor(colors.at(it_syst));
          gr_diff_MC->SetMarkerColor(colors.at(it_syst));
          gr_diff_MC->SetMarkerStyle(21);
          if(it_syst==0){
            gr_diff_MC->GetYaxis()->SetRangeUser(-0.01, 0.01);
          }

        } // END Systematic Loop

        c_Data_up->cd();
        lg->Draw();
        c_Data->SaveAs(base_plotpath+DataPeriod+"/"+trigger+"_"+eff_name+"_Data.pdf");

        c_MC_up->cd();
        lg->Draw();
        c_MC->SaveAs(base_plotpath+DataPeriod+"/"+trigger+"_"+eff_name+"_MC.pdf");

        c_Data->Close();
        c_MC->Close();

      } // END Eta region Loop

    } // END Trigger Loop


  } // END DataPeriod Loop


}
