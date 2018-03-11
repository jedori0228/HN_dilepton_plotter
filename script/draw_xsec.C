#include "canvas_margin.h"

void draw_xsec(){

  TString dataset = getenv("CATANVERSION");
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString plotpath = ENV_PLOT_PATH+"/"+dataset;

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
  const int n_8TeV = 22;
  for(int i=0; i<n_8TeV; i++) xsec_dimu_8TeV[i] = 1.34 * xsec_dimu_8TeV[i];
  
  for(int i=0; i<n_8TeV;i++) cout << mass_dimu_8TeV[i] << "\t" << xsec_dimu_8TeV[i] << endl;
  
  double mass_dimu_13TeV_NLO[] = {
15, 20, 30, 40, 50, 60, 65, 70, 75, 80, 85, 90, 95, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000
  };
  double xsec_dimu_13TeV_NLO[] = {
4362.0, 4172.5, 3651.5, 2926.5, 2067.0, 1163.5, 747.5, 391.7, 143.15,
40.12, // error
22.65, 15.4, 10.9, 7.75, 2.445, 1.1, 0.34, 0.143, 0.0715, 0.02365, 0.00985, 0.00472, 0.00247, 0.001385, 0.00081, 0.000496, 0.000312, 0.0002015, 0.000133, 8.9e-05, 6.05e-05, 2.9e-05, 1.025e-05
  };
  const int n_13TeV = 33;

  double mass_dimu_13TeV_NLO_tch[] = {
100, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000
  };
  double xsec_dimu_13TeV_NLO_tch[] = {
0.04825, 0.02455, 0.0164, 0.00915, 0.0058, 0.003905, 0.00275, 0.00199, 0.00147, 0.00111, 0.000845, 0.00065, 0.00051, 0.000397, 0.0003135, 0.00025, 0.0001605, 8.45e-05
  };
  const int n_13TeV_tch = 18;

  TGraph *gr_dimu_8TeV = new TGraph(n_8TeV, mass_dimu_8TeV, xsec_dimu_8TeV);
  TGraph *gr_dimu_13TeV_NLO = new TGraph(n_13TeV, mass_dimu_13TeV_NLO, xsec_dimu_13TeV_NLO);
  TGraph *gr_dimu_13TeV_NLO_tch = new TGraph(n_13TeV_tch, mass_dimu_13TeV_NLO_tch, xsec_dimu_13TeV_NLO_tch);

  gr_dimu_8TeV->SetLineColor(kBlack);
  gr_dimu_13TeV_NLO->SetLineColor(kRed);
  gr_dimu_13TeV_NLO_tch->SetLineColor(kBlue);

  gr_dimu_8TeV->SetMarkerColor(kBlack);
  gr_dimu_13TeV_NLO->SetMarkerColor(kRed);
  gr_dimu_13TeV_NLO_tch->SetMarkerColor(kBlue);

  gr_dimu_8TeV->SetLineWidth(3);
  gr_dimu_13TeV_NLO->SetLineWidth(3);
  gr_dimu_13TeV_NLO_tch->SetLineWidth(3);

  gr_dimu_8TeV->SetMarkerStyle(20);
  gr_dimu_13TeV_NLO->SetMarkerStyle(20);
  gr_dimu_13TeV_NLO_tch->SetMarkerStyle(20);

  TLegend *lg = new TLegend(0.2, 0.2, 0.80, 0.4);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  lg->AddEntry(gr_dimu_13TeV_NLO, "SS #mu#mu + jj (s-ch), aMC@NLO (13 TeV)", "lp");
  lg->AddEntry(gr_dimu_13TeV_NLO_tch, "SS #mu#mu + jjj (t-ch), aMC@NLO (13 TeV)", "lp");
  lg->AddEntry(gr_dimu_8TeV, "SS #mu#mu + jj (s-ch), ALPGEN (8 TeV)", "lp");
  
  TH1D *hist_dummy = new TH1D("hist_dummy", "", 4000, 1., 4001);
  
  TCanvas *c1 = new TCanvas("c1", "", 800, 800);
  canvas_margin(c1);
  c1->cd();

  hist_dummy->Draw("hist");
  hist_axis(hist_dummy);
  hist_dummy->SetTitle("");
  hist_dummy->GetYaxis()->SetTitle("#sigma (pb)");
  hist_dummy->GetXaxis()->SetTitle("m(N) (GeV)");
  
  c1->SetLogy();
  hist_dummy->GetYaxis()->SetRangeUser(0.000001, 10000);
  hist_dummy->GetXaxis()->SetRangeUser(10., 2100.);
  c1->SetLogx();
  
  gr_dimu_8TeV->Draw("plsame");
  gr_dimu_13TeV_NLO->Draw("plsame");
  gr_dimu_13TeV_NLO_tch->Draw("plsame");
  lg->Draw();

  TLatex latex_mixing;
  latex_mixing.SetNDC();
  latex_mixing.SetTextSize(0.05);
  latex_mixing.DrawLatex(0.65, 0.8, "#splitline{|V_{#muN}|^{2} = 1.0}{|V_{eN}|^{2} = 0}");

  c1->SaveAs(plotpath+"/13_8_xsec.pdf");

/*
  //==== ratio

  cout << "==================================" << endl;
  cout << "==== (13TeV dimu)/(8TeV dimu) ====" << endl;
  cout << "==================================" << endl;
  
  double mass_ratio[] = {
40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700
  };
  const int n_ratio = 16;

  double xsec_ratio_13TeV_8TeV[n_ratio];
  for(unsigned int i=0;i<n_ratio;i++){
    double this_13TeV = 0.;
    for(unsigned int j=0;j<n_13TeV;j++){
      if(mass_dimu_13TeV_NLO[j] == mass_ratio[i]){
        this_13TeV = xsec_dimu_13TeV_NLO[j];
        break;
      }
    }
    double this_8TeV = 0.;
    for(unsigned int j=0;j<n_8TeV;j++){
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
  */

}
