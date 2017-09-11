#include "canvas_margin.h"
#include "mylib.h"

void Draw_FakeSampleDistribution(){

  vector<TString> Leptons = {"Muon_v7_SIP3p5"};

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/FakeRateRootfiles_Norm/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/FakeSampleDistribution/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<TString> samples = {
    "DY", "WJets", "top", "VV", "VGamma",
  };
  vector<TString> alias = {
    "DY", "W + Jets", "top", "VV", "V#gamma",
  };
  vector<Color_t> colors = {
    kYellow, kGreen, kRed, kOrange, kSpring-7,
  };

  vector<TString> vars_tmp = {
    "pt_cone" ,"MT", "PFMET"
  };
  vector<int> rebins_tmp = {
    10, 10, 10
  };
  if(vars_tmp.size()!=rebins_tmp.size()){
    cout << "vars_tmp.size()!=rebins_tmp.size()" << endl;
    return;
  }

  vector<TString> vars;
  vector<int> rebins;
  for(unsigned int i=0; i<vars_tmp.size(); i++){
    vars.push_back(vars_tmp.at(i)+"_F0");
    vars.push_back(vars_tmp.at(i)+"_F");
    rebins.push_back(rebins_tmp.at(i));
    rebins.push_back(rebins_tmp.at(i));
  }

  //==== y=1 line
  double x_1[2], y_1[2];
  x_1[0] = 1000;  y_1[0] = 1;
  x_1[1] = -1000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);

  for(unsigned int i=0; i<Leptons.size(); i++){

    TString Lepton = Leptons.at(i);

    gSystem->mkdir(plotpath+Lepton, kTRUE);

    TString Lep = "El";
    if(Lepton.Contains("Muon")) Lep = "Mu";

    TString PD = "DoubleEG";
    if(Lepton.Contains("Muon")) PD = "DoubleMuon";

    TString lepflavour = "Electron";
    if(Lepton.Contains("Muon")) lepflavour = "Muon";

    TString data_filename = "FRCalculator_"+Lep+"_dxysig_DILEP_data_"+PD+"_cat_v8-0-7.root";
    TFile *file_data = new TFile(filepath+Lepton+"/"+data_filename);

    for(unsigned int k=0; k<vars.size(); k++){

      TString var = vars.at(k);
      TString histname = "Single"+lepflavour+"Trigger_Dijet_Awayjet_40_"+var;

      TH1D *hist_data = (TH1D *)file_data->Get(histname);
      hist_data->Rebin(rebins.at(k));
      hist_data->SetMarkerStyle(20);
      hist_data->SetMarkerSize(1.6);

      THStack *mc_stack = new THStack("mc_stack", "");
      TH1D* MC_stacked_allerr = NULL;
      for(unsigned int l=0; l<samples.size(); l++){
        TString sample = samples.at(l);
        TFile *file_tmp = new TFile(filepath+Lepton+"/FRCalculator_"+Lep+"_dxysig_DILEP_SK"+sample+"_cat_v8-0-7.root");
        TH1D *hist_tmp = (TH1D *)file_tmp->Get(histname);
        if(!hist_tmp) continue;

        hist_tmp->Rebin(rebins.at(k));
        hist_tmp->SetFillColor(colors.at(l));
        mc_stack->Add(hist_tmp);

        int n_bins = hist_tmp->GetXaxis()->GetNbins();
        if(!MC_stacked_allerr){
          MC_stacked_allerr = new TH1D("MC_stacked_allerr", "",
                                    n_bins,
                                    hist_tmp->GetXaxis()->GetBinLowEdge(1),
                                    hist_tmp->GetXaxis()->GetBinUpEdge(n_bins));
        }
        MC_stacked_allerr->Add(hist_tmp);

      }

      //==== Draw

      TCanvas *c1 = new TCanvas("c1", "", 800, 800);
      TPad *c1_up;
      TPad *c1_down;
      c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
      c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

      canvas_margin(c1, c1_up, c1_down);

      c1_up->Draw();
      c1_down->Draw();
      c1_up->cd();

      TH1D *hist_empty = (TH1D*)mc_stack->GetHists()->At(0)->Clone();
      hist_empty->SetName("DUMMY_FOR_AXIS");
      hist_empty->SetLineWidth(0);
      hist_empty->SetLineColor(0);
      hist_empty->SetMarkerSize(0);
      hist_empty->SetMarkerColor(0);
      hist_empty->Draw("histsame");

      double x_min = hist_empty->GetXaxis()->GetXmin();
      double x_max = hist_empty->GetXaxis()->GetXmax();
      if(var.Contains("MT")){
        x_min = 0.;
        x_max = 200.;
      }
      if(var.Contains("PFMET")){
        x_min = 0.;
        x_max = 200.;
      }
      hist_empty->GetXaxis()->SetRangeUser(x_min, x_max);

      double ymax = max( GetMaximum(hist_data), GetMaximum(MC_stacked_allerr) );
      hist_empty->GetYaxis()->SetRangeUser(0.,1.2*ymax);

      mc_stack->Draw("histsame");
      hist_data->Draw("psame");

      c1_down->cd();
      TH1D* ratio_point = (TH1D*)hist_data->Clone();
      TH1D* ratio_allerr = (TH1D*)hist_data->Clone();
      for(int i=1; i<=ratio_point->GetXaxis()->GetNbins(); i++){
        //==== FIXME for zero? how?
        if(MC_stacked_allerr->GetBinContent(i)!=0){
        //==== ratio point
        ratio_point->SetBinContent( i, ratio_point->GetBinContent(i) / MC_stacked_allerr->GetBinContent(i) );
        ratio_point->SetBinError  ( i, ratio_point->GetBinError(i)   / MC_stacked_allerr->GetBinContent(i) );
        //==== ratio allerr
        ratio_allerr->SetBinContent( i, 1. );
        ratio_allerr->SetBinError( i, MC_stacked_allerr->GetBinError(i)/ MC_stacked_allerr->GetBinContent(i) );
        }
      }
      ratio_allerr->SetMaximum(2.0);
      ratio_allerr->SetMinimum(0.0);
      //ratio_allerr->GetXaxis()->SetTitle(x_title[i_var]);
      ratio_allerr->SetYTitle("#frac{Obs.}{Pred.}");
      ratio_allerr->SetFillColor(kOrange);
      ratio_allerr->SetMarkerSize(0);
      ratio_allerr->SetMarkerStyle(0);
      ratio_allerr->SetLineColor(kWhite);
      ratio_allerr->GetXaxis()->SetRangeUser(x_min, x_max);
      ratio_allerr->Draw("E2same");
      hist_axis(hist_empty, ratio_allerr);

      ratio_point->Draw("PE1same");

      //==== y=1 line
      g1->Draw("same");

      //==== write lumi on the top
      c1->cd();
      TLatex latex_CMSPriliminary, latex_Lumi;
      latex_CMSPriliminary.SetNDC();
      latex_Lumi.SetNDC();
      latex_CMSPriliminary.SetTextSize(0.035);
      latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
      latex_Lumi.SetTextSize(0.035);
      latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

      c1->SaveAs(plotpath+Lepton+"/"+histname+".pdf");
      c1->Close();

    } // Variables



  } // Lepton loop
  

}
