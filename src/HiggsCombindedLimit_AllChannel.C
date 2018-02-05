#include "canvas_margin.h"
#include "HiggsCombindedLimit.C"

void HiggsCombindedLimit_AllChannel(){

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limit/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/AllChannel/";

  //TString filepath = ENV_FILE_PATH+dataset+"/Limit/FullCLs/";
  //TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/FullCLs/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  
  TLatex latex_CMSPriliminary, latex_Lumi, latex_title;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_title.SetNDC();

  TGraph *gr_MuMu = HiggsCombindedLimit(3);
  TGraph *gr_ElEl = HiggsCombindedLimit(6);
  TGraph *gr_MuEl = HiggsCombindedLimit(9);

  gr_MuMu->SetLineColor(kCyan);
  gr_ElEl->SetLineColor(kRed);
  gr_MuEl->SetLineColor(kBlue);

  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetYaxis()->SetTitleOffset(0.6);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetTitle("Mixing");
  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetXaxis()->SetTitleSize(0.05);
  dummy->GetXaxis()->SetRangeUser(10., 2500);
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");
  dummy->Draw("hist");

  //======================
  //==== S+T limit
  //======================

  //=== Legend
  TLegend * lg_SandT = new TLegend(0.60, 0.20, 0.92, 0.55);
  lg_SandT->SetBorderSize(0);
  lg_SandT->SetFillStyle(0);

  lg_SandT->AddEntry(gr_MuMu, "Observed #||{V_{#muN}}^{2}", "l");
  lg_SandT->AddEntry(gr_ElEl, "Observed #||{V_{eN}}^{2}", "l");
  lg_SandT->AddEntry(gr_MuEl, "Observed #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");

  TCanvas *c_SandT = new TCanvas("c_SandT", "", 1200, 800);
  canvas_margin(c_SandT);
  c_SandT->SetTopMargin( 0.05 );
  c_SandT->SetBottomMargin( 0.13 );
  c_SandT->SetRightMargin( 0.05 );
  c_SandT->SetLeftMargin( 0.10 );
  c_SandT->cd();
  c_SandT->Draw();
  c_SandT->SetLogy();

  dummy->GetXaxis()->SetRangeUser(10., 2500);
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->Draw("hist");

  gr_MuMu->Draw("lsame");
  gr_ElEl->Draw("lsame");
  gr_MuEl->Draw("lsame");

  lg_SandT->Draw();

  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.77, 0.96, "35.9 fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.05);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.15, 0.85, "#font[41]{95% CL upper limit}");
  latex_title.DrawLatex(0.15, 0.90, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");

  c_SandT->SetLogx();
  c_SandT->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_SandT.pdf");
  c_SandT->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_SandT.png");

/*
  //==== HighMass
  dummy->GetXaxis()->SetRangeUser(90,2500);
  dummy->GetYaxis()->SetRangeUser(1E-4,20);
  c_SandT->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx_SandT_HighMass.pdf");
  c_SandT->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx_SandT_HighMass.png");
*/

  c_SandT->Close();


}
