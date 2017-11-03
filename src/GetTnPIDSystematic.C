#include "canvas_margin.h"
#include "mylib.h"

TGraphAsymmErrors* ValuesToError(TGraphAsymmErrors* a, bool rel);
void AddSystematicToError(TGraphAsymmErrors *prev, TGraphAsymmErrors *newerror);
void AddSystematicToCentralValue(TH2D *central, TH2D *a);
void EmptyGraph(TGraphAsymmErrors* a);
void EmptyHistError(TH2D *a);
void PickLargestError(TGraphAsymmErrors *central, TGraphAsymmErrors *previous, TGraphAsymmErrors *now);
void PickLargestError(TH2D *central, TH2D *previous, TH2D *now);

void GetTnPIDSystematic(){

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  double YErrorMax = 20;

  //==== Central in the first element
  vector< vector<TString> > vsysts  = { {"Central"}, {"NMassBins30", "NMassBins50"}, {"MassRange_60_130", "MassRange_70_120"}, {"SignalShapeCB"}, {"TagPt20IsoInf", "TagPt30Iso0p08"}, {"ProbeMult99"} };
  vector< vector<Color_t> > vcolors = { {kBlack},    {kRed,          kOrange      }, {kYellow,            kGreen,           }, {kBlue,         }, {kViolet,         kGray           }, {kCyan        } };

  //vector< vector<TString> > vsysts  = { {"Central"}, {"NMassBins30", "NMassBins50"} };
  //vector< vector<Color_t> > vcolors = { {kBlack},    {kRed,          kOrange      } };

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = ENV_PLOT_PATH+"/TnP_Results/IDSF/";
  TString base_plotpath = ENV_PLOT_PATH+"/TnP_Results/IDSF/";

  vector<TString> DataPeriods = {"BCDEF", "GH"};
  vector<double> abseta = {0., 0.9, 1.2, 2.1, 2.4};
  vector<TString> fitftns = {"vpvPlusExpo", "vpvPlusExpoPassFail", "voigtPlusExpo", "voigtPlusExpoPassFail", "vpvPlusCheb_3rd", "vpvPlusCheb_4th"};

  for(unsigned int it_DataPeriod=0; it_DataPeriod<DataPeriods.size(); it_DataPeriod++){

    TString DataPeriod = DataPeriods.at(it_DataPeriod);

    //==== output rootfile
    TFile *output = new TFile(base_plotpath+DataPeriod+"/MuonIDEfficiency_HNDILEP_Run"+DataPeriod+".root", "RECREATE");

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

      TGraphAsymmErrors *gr_error_Data;
      TGraphAsymmErrors *gr_error_MC;

      //==== Legend
      TLegend *lg = new TLegend(0.6, 0.1, 0.93, 0.5);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);

      //==== Loop over systematic sources
      for(unsigned int it_vsyst=0; it_vsyst<vsysts.size(); it_vsyst++){

        vector<TString> systs = vsysts.at(it_vsyst);
        vector<Color_t> colors = vcolors.at(it_vsyst);

        TGraphAsymmErrors *gr_Data_ThisSourceLargest = NULL;
        TGraphAsymmErrors *gr_MC_ThisSourceLargest = NULL;

        //==== Loop working points
        for(unsigned int it_syst=0; it_syst<systs.size(); it_syst++){

          TString syst = systs.at(it_syst);
          TString filepath = base_filepath+DataPeriod+"/"+syst+"/";

          vector<double> pt = {10, 20, 25, 30, 40, 50, 60, 120};

          TFile *file = new TFile(filepath+"MuonIDEfficiency_HNDILEP_Run"+DataPeriod+".root");

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
          if(it_vsyst==0&&it_syst==0) DrawOption = "ap";

          //===========
          //==== Data
          //===========

          c_Data_up->cd();
          gr_Data->Draw(DrawOption);
          if(it_vsyst==0&&it_syst==0){
            gr_Data->GetYaxis()->SetRangeUser(0., 1.0);
            gr_Data->GetYaxis()->SetTitle("Efficiency");
          }
          c_Data->cd();
          c_Data_down->cd();
          //==== gr_diff_Data : Relative Difference
          TGraphAsymmErrors *gr_diff_Data = GraphSubtract( gr_Data, gr_Data_Central, true );
          ScaleGraph(gr_diff_Data, 100.);
          hist_axis( gr_Data, gr_diff_Data );
          gr_diff_Data->Draw(DrawOption);
          gr_diff_Data->SetLineColor(colors.at(it_syst));
          gr_diff_Data->SetMarkerColor(colors.at(it_syst));
          gr_diff_Data->SetMarkerStyle(21);
          if(it_vsyst==0&&it_syst==0){
            gr_diff_Data->GetXaxis()->SetTitle("p_{T} [GeV]");
            gr_diff_Data->GetYaxis()->SetRangeUser(-YErrorMax, YErrorMax);
            gr_diff_Data->GetYaxis()->SetTitle("Rel. Diff. [%]");
          }
          //==== Error
          //==== If Central, Draw Fit Uncertainty
          if(syst=="Central"){
            c_Data_err->cd();
            //==== now graph value is rel error
            gr_error_Data = ValuesToError(gr_Data, true);
            ScaleGraph(gr_error_Data, 100.);
            gr_error_Data->SetLineColor(kBlue);
            gr_error_Data->SetMarkerColor(kBlue);
            gr_error_Data->SetLineWidth(2);
            gr_error_Data->Draw("ap");
            hist_axis(gr_error_Data);
            gr_error_Data->GetXaxis()->SetTitle("p_{T} [GeV]");
            gr_error_Data->GetYaxis()->SetTitle("Rel. Diff. [%]");
            gr_error_Data->GetYaxis()->SetRangeUser(0., YErrorMax);

            gr_Data_TotSyst = (TGraphAsymmErrors*)gr_Data->Clone();
            EmptyGraph(gr_Data_TotSyst);
          }
          //==== If systematic, add up errors
          else{
            if(!gr_Data_ThisSourceLargest){
              gr_Data_ThisSourceLargest = (TGraphAsymmErrors*)gr_Data_Central->Clone();
              EmptyGraph(gr_Data_ThisSourceLargest);
            }
            PickLargestError(gr_Data_Central, gr_Data_ThisSourceLargest, gr_Data);
          }

          //======================================
          //==== MC (Exactly same thing as Data)
          //======================================

          c_MC_up->cd();
          gr_MC->Draw(DrawOption);
          if(it_vsyst==0&&it_syst==0){
            gr_MC->GetYaxis()->SetRangeUser(0., 1.0);
            gr_MC->GetYaxis()->SetTitle("Efficiency");
          }
          c_MC->cd();
          c_MC_down->cd();
          //==== gr_diff_MC : Relative Difference
          TGraphAsymmErrors *gr_diff_MC = GraphSubtract( gr_MC, gr_MC_Central, true );
          ScaleGraph(gr_diff_MC, 100.);
          hist_axis( gr_MC, gr_diff_MC );
          gr_diff_MC->Draw(DrawOption);
          gr_diff_MC->SetLineColor(colors.at(it_syst));
          gr_diff_MC->SetMarkerColor(colors.at(it_syst));
          gr_diff_MC->SetMarkerStyle(21);
          if(it_vsyst==0&&it_syst==0){
            gr_diff_MC->GetXaxis()->SetTitle("p_{T} [GeV]");
            gr_diff_MC->GetYaxis()->SetRangeUser(-YErrorMax, YErrorMax);
            gr_diff_MC->GetYaxis()->SetTitle("Rel. Diff. [%]");
          }
          //==== Error
          //==== If Central, Draw Fit Uncertainty
          if(syst=="Central"){
            c_MC_err->cd();
            //==== now graph value is rel error
            gr_error_MC = ValuesToError(gr_MC, true);
            ScaleGraph(gr_error_MC, 100.);
            gr_error_MC->SetLineColor(kBlue);
            gr_error_MC->SetMarkerColor(kBlue);
            gr_error_MC->SetLineWidth(2);
            gr_error_MC->Draw("ap");
            hist_axis(gr_error_MC);
            gr_error_MC->GetXaxis()->SetTitle("p_{T} [GeV]");
            gr_error_MC->GetYaxis()->SetTitle("Rel. Diff. [%]");
            gr_error_MC->GetYaxis()->SetRangeUser(0., YErrorMax);

            gr_MC_TotSyst = (TGraphAsymmErrors*)gr_MC->Clone();
            EmptyGraph(gr_MC_TotSyst);
          }
          //==== If systematic, add up errors
          else{
            if(!gr_MC_ThisSourceLargest){
              gr_MC_ThisSourceLargest = (TGraphAsymmErrors*)gr_MC_Central->Clone();
              EmptyGraph(gr_MC_ThisSourceLargest);
            }
            PickLargestError(gr_MC_Central, gr_MC_ThisSourceLargest, gr_MC);
          }



        } // END Working point

        if(gr_Data_ThisSourceLargest && gr_MC_ThisSourceLargest){
          AddSystematicToError(gr_Data_TotSyst, gr_Data_ThisSourceLargest);
          AddSystematicToError(gr_MC_TotSyst, gr_MC_ThisSourceLargest);
        }

      } // END Systematic Loop

      //==== Draw

      //==== Data
      c_Data_up->cd();
      gr_Data_Central->Draw("psame");
      lg->Draw();
      c_Data->SaveAs(base_plotpath+DataPeriod+"/"+eff_name+"_Data.pdf");
      //==== Error
      c_Data_err->cd();
      ScaleGraph(gr_Data_TotSyst, 100.);
      gr_Data_TotSyst->SetLineColor(kRed);
      gr_Data_TotSyst->SetMarkerColor(kRed);
      gr_Data_TotSyst->SetLineWidth(2);
      gr_Data_TotSyst->Draw("psame");
      gr_error_Data->GetYaxis()->SetRangeUser(0., YErrorMax);
      //==== Sum
      TGraphAsymmErrors *gr_Data_AllError = (TGraphAsymmErrors *)gr_error_Data->Clone();
      for(int aaa=0; aaa<gr_Data_AllError->GetN(); aaa++){

        double x_fit, y_fit;
        double x_syst, y_syst;

        gr_Data_AllError->GetPoint(aaa, x_fit, y_fit);
        gr_Data_TotSyst->GetPoint(aaa, x_syst, y_syst);

        double err = sqrt(y_fit*y_fit+y_syst*y_syst);

        gr_Data_AllError->SetPoint(aaa, x_fit, err);
      }
      gr_Data_AllError->SetLineColor(kBlack);
      gr_Data_AllError->SetMarkerColor(kBlack);
      gr_Data_AllError->SetLineWidth(2);
      gr_Data_AllError->Draw("psame");

      TLegend *lg_error = new TLegend(0.6, 0.7, 0.93, 0.9);
      lg_error->SetFillStyle(0);
      lg_error->SetBorderSize(0);
      lg_error->AddEntry(gr_Data_AllError, "Total Uncert.", "lp");
      lg_error->AddEntry(gr_Data_TotSyst, "Syst. Uncert.", "lp");
      lg_error->AddEntry(gr_error_Data, "Fit Uncert.", "lp");
      lg_error->Draw();

      c_Data_err->SaveAs(base_plotpath+DataPeriod+"/"+eff_name+"_Data_Diff.pdf");
      c_Data_err->Close();

      c_MC_up->cd();
      gr_MC_Central->Draw("psame");
      lg->Draw();
      c_MC->SaveAs(base_plotpath+DataPeriod+"/"+eff_name+"_MC.pdf");
      //==== Error
      c_MC_err->cd();
      ScaleGraph(gr_MC_TotSyst, 100.);
      gr_MC_TotSyst->SetLineColor(kRed);
      gr_MC_TotSyst->SetMarkerColor(kRed);
      gr_MC_TotSyst->SetLineWidth(2);
      gr_MC_TotSyst->Draw("psame");
      gr_error_MC->GetYaxis()->SetRangeUser(0., YErrorMax);
      //==== Sum
      TGraphAsymmErrors *gr_MC_AllError = (TGraphAsymmErrors *)gr_error_MC->Clone();
      for(int aaa=0; aaa<gr_MC_AllError->GetN(); aaa++){

        double x_fit, y_fit;
        double x_syst, y_syst;

        gr_MC_AllError->GetPoint(aaa, x_fit, y_fit);
        gr_MC_TotSyst->GetPoint(aaa, x_syst, y_syst);

        double err = sqrt(y_fit*y_fit+y_syst*y_syst);

        gr_MC_AllError->SetPoint(aaa, x_fit, err);
      }
      gr_MC_AllError->SetLineColor(kBlack);
      gr_MC_AllError->SetMarkerColor(kBlack);
      gr_MC_AllError->SetLineWidth(2);
      gr_MC_AllError->Draw("psame");
      lg_error->Draw();
      c_MC_err->SaveAs(base_plotpath+DataPeriod+"/"+eff_name+"_MC_Diff.pdf");
      c_MC_err->Close();

      c_Data->Close();
      c_MC->Close();

    } // END Eta region Loop

    //======================
    //==== Get 2D directly
    //======================

    TH2D *hist_2D_Data_Central = NULL;
    TH2D *hist_2D_MC_Central = NULL;
    TH2D *hist_2D_SF_Central = NULL;

    for(unsigned int it_vsyst=0; it_vsyst<vsysts.size(); it_vsyst++){

      vector<TString> systs = vsysts.at(it_vsyst);
      vector<Color_t> colors = vcolors.at(it_vsyst);

      TH2D *hist_2D_Data_Largest = NULL;
      TH2D *hist_2D_MC_Largest = NULL;

      //==== Loop systematic sources
      for(unsigned int it_syst=0; it_syst<systs.size(); it_syst++){

        TString syst = systs.at(it_syst);
        TString filepath = base_filepath+DataPeriod+"/"+syst+"/";

        TFile *file = new TFile(filepath+"MuonIDEfficiency_HNDILEP_Run"+DataPeriod+".root");

        TH2D *hist_2D_Data = (TH2D *)file->Get("IDEff_HNDilepton_"+DataPeriod+"_Data");
        TH2D *hist_2D_MC = (TH2D *)file->Get("IDEff_HNDilepton_"+DataPeriod+"_MC");
        if(syst=="Central"){
          hist_2D_Data_Central = (TH2D *)hist_2D_Data->Clone();
          hist_2D_MC_Central = (TH2D *)hist_2D_MC->Clone();

          hist_2D_Data_Largest = (TH2D *)hist_2D_Data_Central->Clone();
          EmptyHistError(hist_2D_Data_Largest);
          hist_2D_MC_Largest = (TH2D *)hist_2D_MC_Central->Clone();
          EmptyHistError(hist_2D_MC_Largest);
        }
        else{
          if(!hist_2D_Data_Largest || !hist_2D_MC_Largest){
            hist_2D_Data_Largest = (TH2D *)hist_2D_Data_Central->Clone();
            EmptyHistError(hist_2D_Data_Largest);
            hist_2D_MC_Largest = (TH2D *)hist_2D_MC_Central->Clone();
            EmptyHistError(hist_2D_MC_Largest);
          }

          PickLargestError(hist_2D_Data_Central, hist_2D_Data_Largest, hist_2D_Data);
          PickLargestError(hist_2D_MC_Central, hist_2D_MC_Largest, hist_2D_MC);
        }

      } // END working point

      AddSystematicToCentralValue(hist_2D_Data_Central, hist_2D_Data_Largest);
      AddSystematicToCentralValue(hist_2D_MC_Central, hist_2D_MC_Largest);

    } // END Syst loop

    hist_2D_SF_Central = (TH2D *)hist_2D_Data_Central->Clone();
    hist_2D_SF_Central->Divide(hist_2D_MC_Central);
    hist_2D_SF_Central->SetName("abseta_pt_PLOT");

    output->cd();
    hist_2D_Data_Central->Write();
    hist_2D_MC_Central->Write();
    hist_2D_SF_Central->Write();
    output->Close();
      


  } // END DataPeriod Loop


}

TGraphAsymmErrors* ValuesToError(TGraphAsymmErrors* a, bool rel){

  TGraphAsymmErrors *out = (TGraphAsymmErrors*)a->Clone();

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, xerr_low, xerr_high, yerr_low, yerr_high;

    a->GetPoint(i, x, y);
    xerr_low  = a->GetErrorXlow(i);
    xerr_high = a->GetErrorXhigh(i);
    yerr_low  = a->GetErrorYlow(i);
    yerr_high = a->GetErrorYhigh(i);

    double newval = sqrt((yerr_low*yerr_low+yerr_high*yerr_high)/2.);
    if(rel) newval = newval/y;

    out->SetPoint(i, x, newval);
    out->SetPointError(i, xerr_low, xerr_high, 0., 0.);

  }

  return out;

}

void AddSystematicToError(TGraphAsymmErrors *prev, TGraphAsymmErrors *newerror){

  //==== a : Total Syst
  //==== b : New Syst

  int NX = prev->GetN();

  for(int i=0; i<NX; i++){
    double x_prev, y_prev;
    prev->GetPoint(i, x_prev, y_prev);
    double x_new, y_new;
    newerror->GetPoint(i, x_new, y_new);

    double y_added = sqrt(y_prev*y_prev+y_new*y_new);
    prev->SetPoint(i, x_prev, y_added);

  }

}

void AddSystematicToCentralValue(TH2D *central, TH2D *a){

  for(int i=1; i<=central->GetXaxis()->GetNbins(); i++){

    for(int j=1; j<=central->GetYaxis()->GetNbins(); j++){

      double value_central = central->GetBinContent(i,j);
      double err_original = central->GetBinError(i,j);

      double this_syst = a->GetBinError(i,j);

      double new_err = sqrt(err_original*err_original+this_syst*this_syst);
      central->SetBinError(i,j, new_err);
    }

  }

}

void EmptyGraph(TGraphAsymmErrors* a){

  int NX = a->GetN();

  for(int i=0; i<NX; i++){

    double x, y, xerr_low, xerr_high;

    a->GetPoint(i, x, y);
    xerr_low  = a->GetErrorXlow(i);
    xerr_high = a->GetErrorXhigh(i);
    a->SetPoint(i, x, 0.);
    a->SetPointError(i, xerr_low, xerr_high, 0., 0.);

  }  

}

void PickLargestError(TGraphAsymmErrors *central, TGraphAsymmErrors *previous, TGraphAsymmErrors *now){

  //==== Central : Eff
  //==== Previous : Error
  //==== now : Eff

  int NX = central->GetN();

  for(int i=0; i<NX; i++){

    double x_central, y_central;
    double x_prev, y_prev;
    double x_now, y_now;

    central->GetPoint(i, x_central, y_central);
    previous->GetPoint(i, x_prev, y_prev);
    now->GetPoint(i, x_now, y_now);

    double this_y = max( y_prev, fabs(y_now-y_central)/y_central );

    previous->SetPoint(i, x_prev, this_y);

  }

}

void PickLargestError(TH2D *central, TH2D *previous, TH2D *now){

  //==== Central : Eff
  //==== Previous : Error
  //==== now : Eff

  for(int ix=1; ix<=central->GetXaxis()->GetNbins(); ix++){
    for(int iy=1; iy<=central->GetYaxis()->GetNbins(); iy++){

      double y_central = central->GetBinContent(ix, iy);
      double y_now = now->GetBinContent(ix, iy);

      double yerr_now = fabs(y_central-y_now);
      double yerr_previous = previous->GetBinError(ix, iy);

      double newerr = max(yerr_now, yerr_previous);

      previous->SetBinError(ix, iy, newerr);


    }
  }

}

void EmptyHistError(TH2D *a){
  for(int ix=1; ix<=a->GetXaxis()->GetNbins(); ix++){
    for(int iy=1; iy<=a->GetYaxis()->GetNbins(); iy++){
      a->SetBinError(ix, iy, 0);
    }
  }
}












