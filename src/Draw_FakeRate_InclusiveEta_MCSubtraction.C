#include "canvas_margin.h"
#include "mylib.h"

TString DoubleToString(double a);

void Draw_FakeRate_InclusiveEta_MCSubtraction(){

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_PLOT_PATH+"/"+dataset+"/FakeRateRootfiles/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/FakeRateRootfiles/MCSubtractionCompare/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<TString> IDs = {
    "Muon_Data_v7_SIP3", "Electron_Data_v7_5",
  };

  for(unsigned int i=0; i<IDs.size(); i++){

    TString ID_after = IDs.at(i);
    TString ID_before = ID_after+"_WITHOUTMCSUBT";

    TFile *file_after = new TFile(filepath+"/"+ID_after+"/"+ID_after+"_FR.root");
    TFile *file_before = new TFile(filepath+"/"+ID_before+"/"+ID_before+"_FR.root");

    TH1D *fr_after = (TH1D *)file_after->Get(ID_after+"_FR_Awayjet40_InclusiveEta");
    TH1D *fr_before = (TH1D *)file_before->Get(ID_before+"_FR_Awayjet40_InclusiveEta");

    TGraphAsymmErrors *gr_after = hist_to_graph(fr_after);
    TGraphAsymmErrors *gr_before = hist_to_graph(fr_before);

    TCanvas *c1 = new TCanvas("c1", "", 600, 600);
    canvas_margin(c1);
    c1->cd();

    TH1D *dummy = new TH1D("dummy", "", 100, 0., 100.);
    hist_axis(dummy);
    dummy->Draw("hist");
    dummy->GetXaxis()->SetRangeUser(10., 60.);
    dummy->GetYaxis()->SetRangeUser(0., 0.4);
    dummy->GetXaxis()->SetTitle("p_{T}^{cone} (GeV)");

    if(ID_after.Contains("Muon")) dummy->GetYaxis()->SetTitle("Muon Fake Rate");
    else dummy->GetYaxis()->SetTitle("Electron Fake Rate");

    gr_after->SetLineWidth(3);
    gr_before->SetLineWidth(3);

    gr_after->SetLineColor(kBlack);
    gr_before->SetLineColor(kRed);

    TLegend *lg = new TLegend(0.4, 0.7, 0.8, 0.93);
    lg->SetBorderSize(0);
    lg->SetFillStyle(0);
    lg->AddEntry(gr_before, "Before Prompt Subtraction", "lp");
    lg->AddEntry(gr_after, "After Prompt Subtraction", "lp");
   
    gr_after->Draw("psame");
    gr_before->Draw("psame");

    lg->Draw();

    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

    c1->SaveAs(plotpath+"/"+ID_after+".pdf");
    c1->SaveAs(plotpath+"/"+ID_after+".png");

    c1->Close();

  }


}
