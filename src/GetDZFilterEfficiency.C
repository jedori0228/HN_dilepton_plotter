#include "canvas_margin.h"

void GetDZFilterEfficiency(){

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/DZFilter/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/DZFilter/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<TString> channels = {
    "DiMuon",
    "DiElectron",
    "Mu8Ele23_EMu",
    //"Mu23Ele8_EMu",
  };
  vector<TString> latexs = {
    "#splitline{OS dimuon, |m(OS)-m(Z)| < 15 GeV}{Data : periodH}",
    "#splitline{OS dielectron, |m(OS)-m(Z)| < 15 GeV}{Data : Whole period}",
    "#splitline{OS emu}{Data : periodG}",
  };

  const int n_rebin = 5;
  double bins[n_rebin+1] = {0, 0.01, 0.02, 0.03, 0.04, 0.08};

/*
  const int n_rebin = 1;
  double bins[n_rebin+1] = {0, 0.08};
*/

  for(unsigned int it_ch=0; it_ch<channels.size(); it_ch++){

    TString Channel = channels.at(it_ch);

    TString filename_MC = "DiLeptonAnalyzer_SKDYJets_dilep_cat_v8-0-7.root";

    TString filename_data = "DoubleMuon.root";
    //filename_data = "DiLeptonAnalyzer_periodG_SKDoubleMuon_dilep_cat_v8-0-7.root";

    if(Channel=="DiElectron"){
      filename_data = "DoubleEG.root";
    }
    if(Channel.Contains("EMu")){
      filename_data = "DiLeptonAnalyzer_periodG_SKMuonEG_dilep_cat_v8-0-7.root";
      filename_MC = "DiLeptonAnalyzer_SKTT_powheg_dilep_cat_v8-0-7.root";
    }

    TFile *file_DY = new TFile(filepath+filename_MC);
    TFile *file_doublemuon = new TFile(filepath+filename_data);

  /*
    TH2D *DZ_DY = (TH2D *)file_DY->Get(Channel+"DZFired_eta1_vs_eta2");
    TH2D *NonDZ_DY = (TH2D *)file_DY->Get(Channel+"NonDZFired_eta1_vs_eta2");
    DZ_DY->Divide(NonDZ_DY);

    TH2D *DZ_doublemuon = (TH2D *)file_doublemuon->Get(Channel+"DZFired_eta1_vs_eta2");
    TH2D *NonDZ_doublemuon = (TH2D *)file_doublemuon->Get(Channel+"NonDZFired_eta1_vs_eta2");
    DZ_doublemuon->Divide(NonDZ_doublemuon);
  */

    TCanvas* c1 = new TCanvas("c1", "", 800, 800);
    c1->Draw();
    TPad *c1_up;
    TPad *c1_down;
    c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
    c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

    canvas_margin(c1, c1_up, c1_down);

    c1_up->Draw();
    c1_down->Draw();

    c1_up->cd();

    TH1D *hist_dummy_top = new TH1D("hist_dummy_top", "", 100, 0., 0.1);
    hist_dummy_top = (TH1D *)hist_dummy_top->Rebin(n_rebin,"hnew1", bins);
    hist_dummy_top->GetYaxis()->SetRangeUser(0.8, 1.2);
    hist_dummy_top->GetXaxis()->SetRangeUser(0., 0.08);
    hist_dummy_top->Draw("hist");
    hist_dummy_top->GetYaxis()->SetTitle("DZ Filter Efficiency");

    TH1D *DZ_DY = (TH1D *)file_DY->Get(Channel+"DZFired_dZ");
    TH1D *NonDZ_DY = (TH1D *)file_DY->Get(Channel+"NonDZFired_dZ");
    DZ_DY = (TH1D *)DZ_DY->Rebin(n_rebin,"hnew1", bins);
    NonDZ_DY = (TH1D *)NonDZ_DY->Rebin(n_rebin,"hnew1", bins);
    DZ_DY->Divide(NonDZ_DY);
    DZ_DY->SetLineColor(kBlue);
    DZ_DY->SetLineWidth(2);
    DZ_DY->Draw("same");

    TH1D *DZ_doublemuon = (TH1D *)file_doublemuon->Get(Channel+"DZFired_dZ");
    TH1D *NonDZ_doublemuon = (TH1D *)file_doublemuon->Get(Channel+"NonDZFired_dZ");
    DZ_doublemuon = (TH1D *)DZ_doublemuon->Rebin(n_rebin,"hnew1", bins);
    NonDZ_doublemuon = (TH1D *)NonDZ_doublemuon->Rebin(n_rebin,"hnew1", bins);
    DZ_doublemuon->Divide(NonDZ_doublemuon);
    DZ_doublemuon->SetLineColor(kBlack);
    DZ_doublemuon->SetLineWidth(2);
    DZ_doublemuon->Draw("same");

    TLegend *lg = new TLegend(0.17, 0.65, 0.5, 0.85);
    lg->SetBorderSize(0);
    lg->SetFillStyle(0);
    lg->AddEntry(DZ_doublemuon, "Data", "lpe");
    lg->AddEntry(DZ_DY, "MC", "lpe");
    lg->Draw();

    cout << Channel << endl;
    cout << "MC : " << DZ_DY->GetBinContent(1) << " +- " << DZ_DY->GetBinError(1) << endl;
    cout << "Data : " << DZ_doublemuon->GetBinContent(1) << " +- " << DZ_doublemuon->GetBinError(1) << endl;
    cout << "=> SF = " << DZ_doublemuon->GetBinContent(1)/DZ_DY->GetBinContent(1) << endl;

    c1_down->cd();
    TH1D *ratio = (TH1D *)DZ_doublemuon->Clone();
    ratio->Divide(DZ_DY);
    ratio->Draw();
    hist_axis(hist_dummy_top,ratio);
    ratio->GetYaxis()->SetTitle("Data Eff./MC Eff.");
    ratio->GetXaxis()->SetTitle("#Delta(dZ) (cm)");
    ratio->GetYaxis()->SetRangeUser(0.92, 1.05);
    ratio->GetXaxis()->SetRangeUser(0., 0.08);

    c1->cd();
    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");
    
    TLatex tag;
    tag.SetNDC();
    tag.SetTextSize(0.035);
    tag.DrawLatex(0.4, 0.8, latexs.at(it_ch));

    c1->SaveAs(plotpath+Channel+".pdf");
    c1->Close();

  }

}
