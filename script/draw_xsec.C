#include "canvas_margin.h"

void draw_xsec(){

  TString dataset = getenv("CATANVERSION");
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");

  gStyle->SetOptStat(0);
  
  double mass_dimu_8TeV[] = {
    40, 50, 60, 70,
    80, 90, 100, 125,
    150, 175, 200, 225,
    250, 275, 300, 325,
    350, 375, 400, 500,
    600, 700
  };
  double xsec_dimu_8TeV[] = {
    1515., 1071., 607.7, 212.0,
    19.06, 7.105, 3.562, 1.0767,
    0.4594, 0.23266, 0.13127, 0.07966,
    0.05093, 0.03386, 0.023214, 0.016317,
    0.011705, 0.008545, 0.006332, 0.002154,
    0.0008545, 0.0003831
  };
  
  for(int i=0; i<22;i++) cout << mass_dimu_8TeV[i] << "\t" << xsec_dimu_8TeV[i] << endl;
  
  double mass_dimu_13TeV_NLO[] = {
    40, 50, 60, 70, 80,
    90, 100, 125, 150, 200,
    250, 300, 400, 500, 600,
    700, 800, 900, 1000, 1100,
    1200, 1300, 1400, 1500
  };
  double xsec_dimu_13TeV_NLO[] = {
    2898, 2042.6, 1147.8, 387.98, 201.34,
    15.434, 7.76, 2.444, 1.1012, 0.3397,
    1.43E-01, 7.122E-02, 2.360E-02, 9.844E-03, 4.700E-03,
    2.467E-03, 1.379E-03, 8.112E-04, 4.955E-04, 3.117E-04,
    2.012E-04, 1.325E-04, 8.892E-05, 6.052E-05
  };
  
  for(int i=0; i<24;i++) cout << mass_dimu_13TeV_NLO[i] << "\t" << xsec_dimu_13TeV_NLO[i]/200. << endl;
  
  TGraph *gr_dimu_8TeV = new TGraph(22, mass_dimu_8TeV, xsec_dimu_8TeV);
  TGraph *gr_dimu_13TeV_NLO = new TGraph(24, mass_dimu_13TeV_NLO, xsec_dimu_13TeV_NLO);

  gr_dimu_8TeV->SetLineColor(kBlue);
  gr_dimu_13TeV_NLO->SetLineColor(kRed);

  gr_dimu_8TeV->SetLineWidth(3);
  gr_dimu_13TeV_NLO->SetLineWidth(3);

  TLegend *lg = new TLegend(0.5, 0.5, 0.95, 0.9);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  lg->AddEntry(gr_dimu_13TeV_NLO, "SS #mu#mu + jj, aMC@NLO (13 TeV)", "l");
  lg->AddEntry(gr_dimu_8TeV, "SS #mu#mu + jj, ALPGEN (8 TeV)", "l");
  
  TH1D *hist_dummy = new TH1D("hist_dummy", "", 2000, 1., 2001);
  
  TCanvas *c1 = new TCanvas("c1", "", 800, 800);
  TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
  canvas_margin(c1, c1_up, c1_down);
  
  c1_down->SetGridx();
  c1_down->SetGridy();
  
  c1_up->Draw();
  c1_down->Draw();

  c1_up->cd();

  hist_dummy->Draw("hist");
  hist_dummy->SetTitle("");
  hist_dummy->GetYaxis()->SetTitle("xsec [pb]");
  
  c1_up->SetLogy();
  hist_dummy->GetYaxis()->SetRangeUser(0.0001, 10000);
  hist_dummy->GetXaxis()->SetRangeUser(1., 1600.);
  //c1_up->SetLogx();
  
  gr_dimu_8TeV->Draw("plsame");
  gr_dimu_13TeV_NLO->Draw("plsame");
  lg->Draw();
  
  c1_down->cd();
  TH1D *hist_dummy_down = (TH1D*)hist_dummy->Clone();
  hist_dummy_down->Draw("hist");
  hist_dummy_down->GetXaxis()->SetTitle("m(N) [GeV]");
  hist_dummy_down->GetYaxis()->SetTitle("#splitline{13TeV/8TeV}{SS DiMu Ch.}");
  hist_dummy_down->GetYaxis()->SetRangeUser(0., 10.0);
  hist_dummy_down->GetXaxis()->SetRangeUser(1., 1600.);
  //c1_down->SetLogx();
  
  cout << "==================================" << endl;
  cout << "==== (13TeV dimu)/(8TeV dimu) ====" << endl;
  cout << "==================================" << endl;
  
  double mass_ratio[] = {
    40, 50, 60, 70,
    90, 100, 150, 200,
    300, 400, 500, 700
  };
  double xsec_ratio_13TeV_8TeV[12];
  for(unsigned int i=0;i<12;i++){
    double this_13TeV = 0.;
    for(unsigned int j=0;j<17;j++){
      if(mass_dimu_13TeV_NLO[j] == mass_ratio[i]){
        this_13TeV = xsec_dimu_13TeV_NLO[j];
        break;
      }
    }
    double this_8TeV = 0.;
    for(unsigned int j=0;j<22;j++){
      if(mass_dimu_8TeV[j] == mass_ratio[i]){
        this_8TeV = xsec_dimu_8TeV[j];
        break;
      }
    }
    //cout << "mass = " << mass_ratio[i] << endl;
    //cout << "  13 TeV = " << this_13TeV << endl;
    //cout << "  8 TeV = " << this_8TeV << endl;
    xsec_ratio_13TeV_8TeV[i] = this_13TeV/this_8TeV;
    cout << mass_ratio[i] << "\t" << xsec_ratio_13TeV_8TeV[i] << endl;
  }
  
  TGraph *ratio_8TeV_13TeV_dimu = new TGraph(12, mass_ratio, xsec_ratio_13TeV_8TeV);
  ratio_8TeV_13TeV_dimu->SetMarkerStyle(31);
  ratio_8TeV_13TeV_dimu->SetMarkerSize(3);
  ratio_8TeV_13TeV_dimu->SetMarkerColor(kBlue);
  ratio_8TeV_13TeV_dimu->SetLineColor(kBlue);
  ratio_8TeV_13TeV_dimu->SetLineWidth(2);
  ratio_8TeV_13TeV_dimu->Draw("lsame");
  hist_axis(hist_dummy, hist_dummy_down);
  
  c1_up->cd();
  TLatex latex_mixing;
  latex_mixing.SetNDC();
  latex_mixing.SetTextSize(0.05);
  latex_mixing.DrawLatex(0.65, 0.3, "#splitline{|V_{#muN}|^{2} = 1.0}{|V_{eN}|^{2} = 0}");

  c1->SaveAs(WORKING_DIR+"/13_8_xsec.pdf");
  
  
}
