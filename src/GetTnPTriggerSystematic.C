#include "canvas_margin.h"
#include "mylib.h"

TGraphAsymmErrors* ValuesToError(TGraphAsymmErrors* a);
void AddSystematic(TGraphAsymmErrors* target, TGraphAsymmErrors* a, TGraphAsymmErrors* b);
void EmptyGraph(TGraphAsymmErrors* a);

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
        TCanvas *c_Data_err = new TCanvas("c_Data_err", "", 800, 800);
        canvas_margin(c_Data_err);

        TCanvas *c_MC = new TCanvas("c_MC", "", 800, 800);
        TPad *c_MC_up = new TPad("c_MC", "", 0, 0.25, 1, 1);
        TPad *c_MC_down = new TPad("c_MC_down", "", 0, 0, 1, 0.25);
        canvas_margin(c_MC, c_MC_up, c_MC_down);
        c_MC_down->SetGridx();
        c_MC_down->SetGridy();
        c_MC_up->Draw();
        c_MC_down->Draw();
        c_MC_up->cd();
        TCanvas *c_MC_err = new TCanvas("c_MC_err", "", 800, 800);
        canvas_margin(c_MC_err);

        TString eff_name = "pt_PLOT_abseta_bin"+TString::Itoa(it_eta,10);

        //==== Save central values for calcualting differences
        TGraphAsymmErrors *gr_Data_Central;
        TGraphAsymmErrors *gr_Data_TotSyst;
        TGraphAsymmErrors *gr_MC_Central;
        TGraphAsymmErrors *gr_MC_TotSyst;

        //==== Legend
        TLegend *lg = new TLegend(0.6, 0.1, 0.93, 0.5);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);

        //==== Loop systematic sources
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
            gr_Data->GetYaxis()->SetRangeUser(0., 1.0);
            gr_Data->GetYaxis()->SetTitle("Efficiency");
          }
          c_Data->cd();
          c_Data_down->cd();
          TGraphAsymmErrors *gr_diff_Data = GraphSubtract( gr_Data, gr_Data_Central, true );
          hist_axis( gr_Data, gr_diff_Data );
          gr_diff_Data->Draw(DrawOption);
          gr_diff_Data->SetLineColor(colors.at(it_syst));
          gr_diff_Data->SetMarkerColor(colors.at(it_syst));
          gr_diff_Data->SetMarkerStyle(21);
          if(it_syst==0){
            gr_diff_Data->GetXaxis()->SetTitle("p_{T} [GeV]");
            gr_diff_Data->GetYaxis()->SetRangeUser(-0.01, 0.01);
            gr_diff_Data->GetYaxis()->SetTitle("Rel. Diff.");
          }
          //==== Error
          //==== If Central, Draw Fit Uncertainty
          if(syst=="Central"){
            c_Data_err->cd();
            TGraphAsymmErrors *gr_error_Data = ValuesToError(gr_Data);
            ScaleGraph(gr_error_Data, 100.);
            gr_error_Data->SetLineColor(kBlack);
            gr_error_Data->SetLineStyle(2);
            gr_error_Data->Draw("al");
            hist_axis(gr_error_Data);
            gr_error_Data->GetXaxis()->SetTitle("p_{T} [GeV]");
            if(trigger=="DoubleIsoMu17Mu8_IsoMu17leg") gr_error_Data->GetXaxis()->SetRangeUser(19., 100.);
            gr_error_Data->GetYaxis()->SetTitle("Rel. Diff.");
            gr_error_Data->GetYaxis()->SetRangeUser(0., 4.);

            gr_Data_TotSyst = (TGraphAsymmErrors*)gr_Data->Clone();
            EmptyGraph(gr_Data_TotSyst);
          }
          //==== If systematic, add up errors
          else{
            AddSystematic(gr_Data_TotSyst, gr_Data, gr_Data_Central);
          }
          
          //==== MC
          c_MC_up->cd();
          gr_MC->Draw(DrawOption);
          if(it_syst==0){
            gr_MC->GetYaxis()->SetRangeUser(0., 1.0);
            gr_MC->GetYaxis()->SetTitle("Efficiency");
          }
          c_MC->cd();
          c_MC_down->cd();
          TGraphAsymmErrors *gr_diff_MC = GraphSubtract( gr_MC, gr_MC_Central, true );
          hist_axis( gr_MC, gr_diff_MC );
          gr_diff_MC->Draw(DrawOption);
          gr_diff_MC->SetLineColor(colors.at(it_syst));
          gr_diff_MC->SetMarkerColor(colors.at(it_syst));
          gr_diff_MC->SetMarkerStyle(21);
          if(it_syst==0){
            gr_diff_MC->GetXaxis()->SetTitle("p_{T} [GeV]");
            gr_diff_MC->GetYaxis()->SetRangeUser(-0.01, 0.01);
            gr_diff_MC->GetYaxis()->SetTitle("Rel. Diff.");
          }
          //==== Error
          //==== If Central, Draw Fit Uncertainty
          if(syst=="Central"){
            c_MC_err->cd();
            TGraphAsymmErrors *gr_error_MC = ValuesToError(gr_MC);
            ScaleGraph(gr_error_MC, 100.);
            gr_error_MC->SetLineColor(kBlack);
            gr_error_MC->SetLineStyle(2);
            gr_error_MC->Draw("al");
            hist_axis(gr_error_MC);
            gr_error_MC->GetXaxis()->SetTitle("p_{T} [GeV]");
            if(trigger=="DoubleIsoMu17Mu8_IsoMu17leg") gr_error_MC->GetXaxis()->SetRangeUser(19., 100.);
            gr_error_MC->GetYaxis()->SetTitle("Rel. Diff.");
            gr_error_MC->GetYaxis()->SetRangeUser(0., 4.);

            gr_MC_TotSyst = (TGraphAsymmErrors*)gr_MC->Clone();
            EmptyGraph(gr_MC_TotSyst);
          }
          //==== If systematic, add up errors
          else{
            AddSystematic(gr_MC_TotSyst, gr_MC, gr_MC_Central);
          }

        } // END Systematic Loop

        //==== Draw

        //==== Data
        c_Data_up->cd();
        gr_Data_Central->Draw("psame");
        lg->Draw();
        c_Data->SaveAs(base_plotpath+DataPeriod+"/"+trigger+"_"+eff_name+"_Data.pdf");
        //==== Error
        c_Data_err->cd();
        ScaleGraph(gr_Data_TotSyst, 100.);
        gr_Data_TotSyst->SetLineColor(kRed);
        gr_Data_TotSyst->SetLineWidth(2);
        gr_Data_TotSyst->Draw("lsame");
        c_Data_err->SaveAs(base_plotpath+DataPeriod+"/"+trigger+"_"+eff_name+"_Data_Diff.pdf");
        c_Data_err->Close();

        c_MC_up->cd();
        gr_MC_Central->Draw("psame");
        lg->Draw();
        c_MC->SaveAs(base_plotpath+DataPeriod+"/"+trigger+"_"+eff_name+"_MC.pdf");
        //==== Error
        c_MC_err->cd();
        ScaleGraph(gr_MC_TotSyst, 100.);
        gr_MC_TotSyst->SetLineColor(kRed);
        gr_MC_TotSyst->SetLineWidth(2);
        gr_MC_TotSyst->Draw("lsame");
        c_MC_err->SaveAs(base_plotpath+DataPeriod+"/"+trigger+"_"+eff_name+"_MC_Diff.pdf");
        c_MC_err->Close();

        c_Data->Close();
        c_MC->Close();

      } // END Eta region Loop

    } // END Trigger Loop


  } // END DataPeriod Loop


}

TGraphAsymmErrors* ValuesToError(TGraphAsymmErrors* a){

  TGraphAsymmErrors *out = (TGraphAsymmErrors*)a->Clone();

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    out->SetPoint(i, x, sqrt((yerr_low*yerr_low+yerr_high*yerr_high)/2.));
    out->SetPointError(i, 0., 0., 0., 0.);

  }

  return out;

}

void AddSystematic(TGraphAsymmErrors* target, TGraphAsymmErrors* a, TGraphAsymmErrors* b){

  //==== a : systematic
  //==== b : central

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double a_x, a_y, a_yerr_low, a_yerr_high, b_x, b_y, b_yerr_low, b_yerr_high;

    a->GetPoint(i, a_x, a_y);
    a_yerr_low  = a->GetErrorYlow(i);
    a_yerr_high = a->GetErrorYhigh(i);
    double a_yerr = sqrt( (a_yerr_low*a_yerr_low+a_yerr_high*a_yerr_high)/2. );

    b->GetPoint(i, b_x, b_y);
    b_yerr_low  = b->GetErrorYlow(i);
    b_yerr_high = b->GetErrorYhigh(i);
    double b_yerr = sqrt( (b_yerr_low*b_yerr_low+b_yerr_high*b_yerr_high)/2. );

    double newerror = sqrt(a_yerr*a_yerr+b_yerr*b_yerr);
    target->SetPoint(i, a_x, newerror/b_y);
    target->SetPointError(i, 0., 0., 0., 0.);
    
  }

}

void EmptyGraph(TGraphAsymmErrors* a){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y;

    a->GetPoint(i, x, y);
    a->SetPoint(i, x, 0.);
    a->SetPointError(i, 0., 0., 0., 0.);

  }  

}


















