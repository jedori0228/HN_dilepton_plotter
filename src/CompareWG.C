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
    "MET2overST",
    "m_ll",
    "leadingLepton_Pt", "leadingLepton_Eta",
    "secondLepton_Pt", "secondLepton_Eta",
  };
  vector<TString> xtitles = {
    "#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)",
    "m(ll) (GeV)",
    "Leading Lepton p_{T} (GeV)", "Leading Lepton #eta",
    "Subleading Lepton p_{T} (GeV)", "Subleading Lepton #eta",
  };

  vector<int> rebins = {
    2,
    5,
    10, 5,
    10, 5,
  };
  vector<int> xmins = {
    0,
    0,
    0, -3,
    0, -3,
  };
  vector<int> xmaxs = {
    40,
    100,
    150, 3,
    150, 3,
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

        hist_SS->SetLineColor(kRed);
        hist_SS->SetLineWidth(3);
        hist_All->SetMarkerColor(kBlack);
        hist_All->SetLineColor(kBlack);
        hist_All->SetMarkerStyle(3);

        hist_SS->Draw("histe1");
        hist_axis(hist_SS);
        double y_max = max(GetMaximum(hist_SS), GetMaximum(hist_All));
        hist_SS->GetXaxis()->SetRangeUser(xmins.at(k), xmaxs.at(k));
        hist_SS->GetYaxis()->SetRangeUser(0, 1.2*y_max);
        hist_SS->GetYaxis()->SetTitle("Events");
        hist_SS->GetXaxis()->SetTitle(xtitles.at(k));

        hist_All->Draw("psame");

        //==== Legend

        TLegend *lg = new TLegend(0.5, 0.75, 0.93, 0.9);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);
        lg->AddEntry(hist_SS, "SS Only", "l");
        lg->AddEntry(hist_All, "Reweighted OS+SS", "p");
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

        TString this_plotpath = plotpath+"/"+channel+"/"+region;
        gSystem->mkdir(this_plotpath, kTRUE);
        c1->SaveAs(this_plotpath+"/"+var+".pdf");
        c1->Close();


      }

    }

  }


}
