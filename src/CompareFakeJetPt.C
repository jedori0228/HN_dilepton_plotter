#include "canvas_margin.h"

void CompareFakeJetPt(){

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/NonPromptSyst_AwayJet/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/NonPromptSyst_AwayJet/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<TString> samples = {"QCD", "DYJets", "TTLL_powheg"};
  vector<Color_t> colors = {870, kYellow-3, kRed};
  vector<TString> alias = {"QCD", "DY", "t#bar{t}"};

  TString histname = "DiElectron_LooseSample_LeptonClosestJet_Pt";

  TCanvas *c1 = new TCanvas("c1", "", 800, 800);
  canvas_margin(c1);
  c1->cd();

  TLegend *lg = new TLegend(0.7, 0.7, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0); 

  for(unsigned int i=0; i<samples.size(); i++){

    TString sample = samples.at(i);

    TFile *file = new TFile(filepath+"/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_"+catversion+".root");
    TH1D *hist = (TH1D*)file->Get(histname);
    hist->SetMarkerStyle(21);
    hist->SetMarkerSize(1);
    hist->SetMarkerColor(colors.at(i));
    hist->SetLineColor(colors.at(i));
    hist->Rebin(10);

    double maxval = hist->GetMaximum();
    hist->Scale(1./maxval);

    lg->AddEntry(hist, alias.at(i), "p");

    if(i==0){
      hist->Draw("psame");
      hist_axis(hist);
      hist->GetXaxis()->SetRangeUser(0., 200.);
      hist->GetXaxis()->SetTitle("LeptonCloseJet p_{T} [GeV]");
      hist->GetYaxis()->SetTitle("A.U.");
    }
    else{
      hist->Draw("psame");
    }

  }

  lg->Draw();
  c1->SaveAs(plotpath+"/pts.pdf");


}
