#include "canvas_margin.h"
#include "mylib.h"

void CompareWG(){

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/Regions/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/CompareWG/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TFile *file_SS = new TFile(filepath+"/DiLeptonAnalyzer_SKWGtoLNuG_dilep_cat_"+catversion+".root");
  TFile *file_All = new TFile(filepath+"/DiLeptonAnalyzer_SKWGtoLNuG_weighted_dilep_cat_"+catversion+".root");

  vector<TString> regions = {
    "Preselection_SS",
  };
  vector<TString> regionsForLatex = {
    "Preselection",
  };

  vector<TString> channels = {
    "DiMuon", "DiElectron", "EMu",
  };

  vector<TString> vars = {
    "MET2overST", "PFMET", 
    "m_ll",
    "leadingLepton_Pt", "leadingLepton_Eta",
    "secondLepton_Pt", "secondLepton_Eta",
    "Njets",
  };
  vector<TString> xtitles = {
    "#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)", "#slash{E}_{T}^{miss} (GeV)",
    "m(ll) (GeV)",
    "Leading Lepton p_{T} (GeV)", "Leading Lepton #eta",
    "Subleading Lepton p_{T} (GeV)", "Subleading Lepton #eta",
    "# of jets",
  };

  vector<int> rebins = {
    2, 5,
    5,
    10, 5,
    10, 5,
    1,
  };
  vector<int> xmins = {
    0, 0,
    0,
    0, -3,
    0, -3,
    0,
  };
  vector<int> xmaxs = {
    40, 80,
    100,
    150, 3,
    150, 3,
    5,
  };

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    for(unsigned int j=0; j<regions.size(); j++){

      TString region = regions.at(j);

      TString dirname = channel+"_"+region;

      TDirectory *dir_SS = (TDirectory *)file_SS->Get(dirname);
      TDirectory *dir_All = (TDirectory *)file_All->Get(dirname);

      for(unsigned int k=0; k<vars.size(); k++){

        TString var = vars.at(k);

        TH1D *hist_SS = (TH1D *)dir_SS->Get(var+"_"+channel+"_"+region);
        TH1D *hist_All = (TH1D *)dir_All->Get(var+"_"+channel+"_"+region);

        hist_SS->Rebin(rebins.at(k));
        hist_All->Rebin(rebins.at(k));

        TCanvas *c1 = new TCanvas("c1", "", 600, 600);
        canvas_margin(c1);
        c1->cd();

/*
        hist_SS->SetLineColor(kRed);
        hist_SS->SetLineWidth(3);
        hist_All->SetMarkerColor(kBlack);
        hist_All->SetLineColor(kBlack);
        hist_All->SetMarkerStyle(3);
*/

        hist_All->SetFillColor(kOrange);
        hist_All->SetLineColor(kOrange);
        hist_SS->SetMarkerColor(kBlack);
        hist_SS->SetLineColor(kBlack);
        hist_SS->SetMarkerStyle(20);
        hist_SS->SetMarkerSize(1.6);

        hist_All->Draw("hist");
        hist_axis(hist_All);
        double y_max = max(GetMaximum(hist_All), GetMaximum(hist_SS));
        hist_All->GetXaxis()->SetRangeUser(xmins.at(k), xmaxs.at(k));
        hist_All->GetYaxis()->SetRangeUser(0, 1.2*y_max);
        hist_All->GetYaxis()->SetTitle("Events");
        hist_All->GetXaxis()->SetTitle(xtitles.at(k));

        hist_SS->Draw("pe1same");

        TH1D *hist_All_err = (TH1D *)hist_All->Clone();
        hist_All_err->SetMarkerColorAlpha(kAzure-9, 0);
        hist_All_err->SetFillStyle(3013);
        hist_All_err->SetFillColor(kBlack);
        hist_All_err->SetLineColor(0);
        hist_All_err->Draw("sameE2");


        //==== Legend

        TLegend *lg = new TLegend(0.5, 0.75, 0.93, 0.9);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);
        lg->AddEntry(hist_SS, "SS Only", "pe");
        lg->AddEntry(hist_All, "Reweighted OS+SS", "f");
        lg->Draw();

        //==== latex

        TLatex latex_CMSPriliminary, latex_Lumi;
        latex_CMSPriliminary.SetNDC();
        latex_Lumi.SetNDC();
        latex_CMSPriliminary.SetTextSize(0.035);
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
        latex_Lumi.SetTextSize(0.035);
        latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

        TString str_channel = "#mu#mu";
        if(channel=="DiElectron") str_channel = "ee";
        if(channel=="EMu") str_channel = "e#mu";

        str_channel = "#splitline{"+str_channel+"}{"+regionsForLatex.at(j)+"}";
        TLatex channelname;
        channelname.SetNDC();
        channelname.SetTextSize(0.037);
        channelname.DrawLatex(0.2, 0.88, str_channel);

        TLatex WGName;
        WGName.SetNDC();
        WGName.SetTextSize(0.04);
        WGName.DrawLatex(0.65, 0.5, "W#gamma Reweighting");

        TString this_plotpath = plotpath+"/"+channel+"/"+region;
        gSystem->mkdir(this_plotpath, kTRUE);
        c1->SaveAs(this_plotpath+"/"+var+".pdf");
        c1->Close();


      }

    }

  }


}
