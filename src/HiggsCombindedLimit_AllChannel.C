#include "canvas_margin.h"
#include "HiggsCombindedLimit.C"

double GetXsecSch(int mass);
double GetXsecTch(int mass);

void HiggsCombindedLimit_AllChannel(int WhichSR=1, int ObsOrExp=0){

  //int WhichSR = 0;  // 1 : SR1, 2 : SR2, 3 : Combined
  //int ObsOrExp = -1; // 0 : Obs, 1 : Exp

  TString string_WhichSR = "";
  if(WhichSR==1) string_WhichSR = "SR1";
  else if(WhichSR==2) string_WhichSR = "SR2";
  else if(WhichSR==3) string_WhichSR = "Combined";

  TString string_ObsOrExp = "";
  if(ObsOrExp==0) string_ObsOrExp = "Obs";
  else if(ObsOrExp==1) string_ObsOrExp = "Exp";

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limit/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/AllChannel/"+string_ObsOrExp+"/"+string_WhichSR+"/";

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

  TGraph *gr_MuMu = HiggsCombindedLimit(0+WhichSR,"",0+ObsOrExp,true);
  TGraph *gr_ElEl = HiggsCombindedLimit(3+WhichSR,"",0+ObsOrExp,true);
  TGraph *gr_MuEl = HiggsCombindedLimit(6+WhichSR,"",0+ObsOrExp,true);
  TGraph *gr_MuMu_SOnly = HiggsCombindedLimit(0+WhichSR,"",4+ObsOrExp,true);
  TGraph *gr_ElEl_SOnly = HiggsCombindedLimit(3+WhichSR,"",4+ObsOrExp,true);
  TGraph *gr_MuEl_SOnly = HiggsCombindedLimit(6+WhichSR,"",4+ObsOrExp,true);

  gr_ElEl->SetLineColor(kRed);
  gr_MuEl->SetLineColor(kBlue);

  gr_MuMu_SOnly->SetLineColor(kCyan);
  gr_ElEl_SOnly->SetLineColor(kRed);
  gr_MuEl_SOnly->SetLineColor(kBlue);
  gr_MuMu_SOnly->SetLineStyle(3);
  gr_ElEl_SOnly->SetLineStyle(3);
  gr_MuEl_SOnly->SetLineStyle(3);


  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetYaxis()->SetTitleOffset(0.6);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetTitle("Mixing");
  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetXaxis()->SetTitleSize(0.05);
  dummy->GetXaxis()->SetRangeUser(20., 2000);
  dummy->GetYaxis()->SetRangeUser(0.000005, 1.);
  dummy->SetTitle("");
  dummy->Draw("hist");

  //======================
  //==== S+T limit
  //======================

  TCanvas *c_SandT = new TCanvas("c_SandT", "", 1200, 800);
  canvas_margin(c_SandT);
  c_SandT->SetTopMargin( 0.05 );
  c_SandT->SetBottomMargin( 0.13 );
  c_SandT->SetRightMargin( 0.05 );
  c_SandT->SetLeftMargin( 0.10 );
  c_SandT->cd();
  c_SandT->Draw();
  c_SandT->SetLogy();

  dummy->GetXaxis()->SetRangeUser(20., 2000);
  dummy->GetYaxis()->SetRangeUser(0.000005, 1.);
  dummy->Draw("hist");

  //=== Legend
  TLegend * lg_SandT = new TLegend(0.60, 0.20, 0.92, 0.55);
  lg_SandT->SetBorderSize(0);
  lg_SandT->SetFillStyle(0);

  if(ObsOrExp==0){
    lg_SandT->AddEntry(gr_MuMu, "Observed #||{V_{#muN}}^{2}", "l");
    lg_SandT->AddEntry(gr_ElEl, "Observed #||{V_{eN}}^{2}", "l");
    lg_SandT->AddEntry(gr_MuEl, "Observed #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");
  }
  else{
    lg_SandT->AddEntry(gr_MuMu, "Expected #||{V_{#muN}}^{2}", "l");
    lg_SandT->AddEntry(gr_ElEl, "Expected #||{V_{eN}}^{2}", "l");
    lg_SandT->AddEntry(gr_MuEl, "Expected #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");
  }

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

  gr_MuMu_SOnly->Draw("lsame");
  gr_ElEl_SOnly->Draw("lsame");
  gr_MuEl_SOnly->Draw("lsame");

  c_SandT->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx.pdf");
  c_SandT->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx.png");

  c_SandT->Close();


  //==== Ratio of S vs S+T

  TCanvas *c_ratio = new TCanvas("c_ratio", "", 600, 600);
  c_ratio->cd();
  canvas_margin(c_ratio);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetXaxis()->SetRangeUser(200, 1500);
  dummy->GetYaxis()->SetRangeUser(0., 6);
  dummy->GetYaxis()->SetTitle("Sensitivity Ratio");

  vector<double> vec_mass_ratio_MuMu, vec_ratio_MuMu;
  vector<double> vec_XsecRatio;
  int NX_MuMu_SOnly = gr_MuMu_SOnly->GetN();
  int NX_MuMu = gr_MuMu->GetN();
  for(int i=0; i<NX_MuMu_SOnly; i++){
    double x_SOnly, y_SOnly;
    gr_MuMu_SOnly->GetPoint(i, x_SOnly, y_SOnly);

    for(int j=0; j<NX_MuMu; j++){
      double x_SandT, y_SandT;
      gr_MuMu->GetPoint(j, x_SandT, y_SandT);

      if(x_SandT==x_SOnly){
        cout << x_SandT << "\t" << y_SandT << "\t" << y_SOnly << endl;
        vec_mass_ratio_MuMu.push_back(x_SandT);
        vec_ratio_MuMu.push_back(y_SOnly/y_SandT);

        if(x_SandT>=100){
          double xsec_s = GetXsecSch(int(x_SandT));
          double xsec_t = GetXsecTch(int(x_SandT))/2.;
          vec_XsecRatio.push_back( (xsec_s+xsec_t)/(xsec_s) );
        }
        else{
          vec_XsecRatio.push_back( 1. );
        }
      }

    }
  }
  const int n_ratio_MuMu = vec_mass_ratio_MuMu.size();
  double mass_ratio_MuMu[n_ratio_MuMu], ratio_MuMu[n_ratio_MuMu];
  double XsecRatio[n_ratio_MuMu];
  for(int i=0; i<n_ratio_MuMu; i++){
    mass_ratio_MuMu[i] = vec_mass_ratio_MuMu.at(i);
    ratio_MuMu[i] = vec_ratio_MuMu.at(i);
    XsecRatio[i] = vec_XsecRatio.at(i);
  }
  TGraph *gr_ratio_MuMu = new TGraph(n_ratio_MuMu, mass_ratio_MuMu, ratio_MuMu);
  TGraph *gr_ratio_xsec = new TGraph(n_ratio_MuMu, mass_ratio_MuMu, XsecRatio);

  vector<double> vec_mass_ratio_ElEl, vec_ratio_ElEl;
  int NX_ElEl_SOnly = gr_ElEl_SOnly->GetN();
  int NX_ElEl = gr_ElEl->GetN();
  for(int i=0; i<NX_ElEl_SOnly; i++){
    double x_SOnly, y_SOnly;
    gr_ElEl_SOnly->GetPoint(i, x_SOnly, y_SOnly);

    for(int j=0; j<NX_ElEl; j++){
      double x_SandT, y_SandT;
      gr_ElEl->GetPoint(j, x_SandT, y_SandT);

      if(x_SandT==x_SOnly){
        cout << x_SandT << "\t" << y_SandT << "\t" << y_SOnly << endl;
        vec_mass_ratio_ElEl.push_back(x_SandT);
        vec_ratio_ElEl.push_back(y_SOnly/y_SandT);

      }

    }
  }
  const int n_ratio_ElEl = vec_mass_ratio_ElEl.size();
  double mass_ratio_ElEl[n_ratio_ElEl], ratio_ElEl[n_ratio_ElEl];
  for(int i=0; i<n_ratio_ElEl; i++){
    mass_ratio_ElEl[i] = vec_mass_ratio_ElEl.at(i);
    ratio_ElEl[i] = vec_ratio_ElEl.at(i);
  }
  TGraph *gr_ratio_ElEl = new TGraph(n_ratio_ElEl, mass_ratio_ElEl, ratio_ElEl);
  vector<double> vec_mass_ratio_MuEl, vec_ratio_MuEl;
  int NX_MuEl_SOnly = gr_MuEl_SOnly->GetN();
  int NX_MuEl = gr_MuEl->GetN();
  for(int i=0; i<NX_MuEl_SOnly; i++){
    double x_SOnly, y_SOnly;
    gr_MuEl_SOnly->GetPoint(i, x_SOnly, y_SOnly);

    for(int j=0; j<NX_MuEl; j++){
      double x_SandT, y_SandT;
      gr_MuEl->GetPoint(j, x_SandT, y_SandT);

      if(x_SandT==x_SOnly){
        cout << x_SandT << "\t" << y_SandT << "\t" << y_SOnly << endl;
        vec_mass_ratio_MuEl.push_back(x_SandT);
        vec_ratio_MuEl.push_back(y_SOnly/y_SandT);

      }

    }
  }
  const int n_ratio_MuEl = vec_mass_ratio_MuEl.size();
  double mass_ratio_MuEl[n_ratio_MuEl], ratio_MuEl[n_ratio_MuEl];
  for(int i=0; i<n_ratio_MuEl; i++){
    mass_ratio_MuEl[i] = vec_mass_ratio_MuEl.at(i);
    ratio_MuEl[i] = vec_ratio_MuEl.at(i);
  }
  TGraph *gr_ratio_MuEl = new TGraph(n_ratio_MuEl, mass_ratio_MuEl, ratio_MuEl);

  gr_ratio_MuMu->SetLineColor(kCyan);
  gr_ratio_ElEl->SetLineColor(kRed);
  gr_ratio_MuEl->SetLineColor(kBlue);

  gr_ratio_MuMu->SetLineWidth(3);
  gr_ratio_ElEl->SetLineWidth(3);
  gr_ratio_MuEl->SetLineWidth(3);

  gr_ratio_MuMu->Draw("lsame");
  gr_ratio_ElEl->Draw("lsame");
  gr_ratio_MuEl->Draw("lsame");

  TLegend * lg_ratio = new TLegend(0.20, 0.55, 0.60, 0.85);
  lg_ratio->SetBorderSize(0);
  lg_ratio->SetFillStyle(0);

  if(ObsOrExp==0){
    lg_ratio->AddEntry(gr_ratio_MuMu, "Observed #||{V_{#muN}}^{2}", "l");
    lg_ratio->AddEntry(gr_ratio_ElEl, "Observed #||{V_{eN}}^{2}", "l");
    lg_ratio->AddEntry(gr_ratio_MuEl, "Observed #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");
  }
  else{
    lg_ratio->AddEntry(gr_ratio_MuMu, "Expected #||{V_{#muN}}^{2}", "l");
    lg_ratio->AddEntry(gr_ratio_ElEl, "Expected #||{V_{eN}}^{2}", "l");
    lg_ratio->AddEntry(gr_ratio_MuEl, "Expected #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");
  }

  lg_ratio->Draw();

  c_ratio->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_ratio.pdf");
  c_ratio->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_ratio.png");

  gr_ratio_xsec->SetLineColor(kViolet);
  gr_ratio_xsec->Draw("lsame");
  c_ratio->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_ratio_withXsecRatio.pdf");
  c_ratio->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_ratio_withXsecRatio.png");

  c_ratio->Close();

  //==== Ratio of SR1 vs SR1+SR2
  TGraph *gr_MuMu_SR1 = HiggsCombindedLimit(1,"",ObsOrExp,true);
  TGraph *gr_ElEl_SR1 = HiggsCombindedLimit(4,"",ObsOrExp,true);
  TGraph *gr_MuEl_SR1 = HiggsCombindedLimit(7,"",ObsOrExp,true);
  TGraph *gr_MuMu_Combined = HiggsCombindedLimit(3,"",ObsOrExp,true);
  TGraph *gr_ElEl_Combined = HiggsCombindedLimit(6,"",ObsOrExp,true);
  TGraph *gr_MuEl_Combined = HiggsCombindedLimit(9,"",ObsOrExp,true);

  vector<double> vec_mass_ratio_MuMu_SRs, vec_ratio_MuMu_SRs;
  int NX_MuMu_SR1 = gr_MuMu_SR1->GetN();
  int NX_MuMu_Combined = gr_MuMu_Combined->GetN();
  cout << "[HiggsCombindedLimit_AllChannel] vec_mass_ratio_MuMu_SRs" << endl;
  for(int i=0; i<NX_MuMu_SR1; i++){
    double x_SR1, y_SR1;
    gr_MuMu_SR1->GetPoint(i, x_SR1, y_SR1);

    for(int j=0; j<NX_MuMu_Combined; j++){
      double x_Combined, y_Combined;
      gr_MuMu_Combined->GetPoint(j, x_Combined, y_Combined);

      if(x_Combined==x_SR1 && x_Combined!=500 && x_Combined!=600){ //FIXME
        cout << x_Combined << "\t" << y_Combined << "\t" << y_SR1 << endl;
        vec_mass_ratio_MuMu_SRs.push_back(x_Combined);
        vec_ratio_MuMu_SRs.push_back(y_SR1/y_Combined);

      }

    }
  }
  const int n_ratio_MuMu_SRs = vec_mass_ratio_MuMu_SRs.size();
  double mass_ratio_MuMu_SRs[n_ratio_MuMu_SRs], ratio_MuMu_SRs[n_ratio_MuMu_SRs];
  for(int i=0; i<n_ratio_MuMu_SRs; i++){
    mass_ratio_MuMu_SRs[i] = vec_mass_ratio_MuMu_SRs.at(i);
    ratio_MuMu_SRs[i] = vec_ratio_MuMu_SRs.at(i);
  }
  TGraph *gr_ratio_MuMu_SRs = new TGraph(n_ratio_MuMu_SRs, mass_ratio_MuMu_SRs, ratio_MuMu_SRs);

  vector<double> vec_mass_ratio_ElEl_SRs, vec_ratio_ElEl_SRs;
  int NX_ElEl_SR1 = gr_ElEl_SR1->GetN();
  int NX_ElEl_Combined = gr_ElEl_Combined->GetN();
  cout << "[HiggsCombindedLimit_AllChannel] vec_mass_ratio_ElEl_SRs" << endl;
  for(int i=0; i<NX_ElEl_SR1; i++){
    double x_SR1, y_SR1;
    gr_ElEl_SR1->GetPoint(i, x_SR1, y_SR1);

    for(int j=0; j<NX_ElEl_Combined; j++){
      double x_Combined, y_Combined;
      gr_ElEl_Combined->GetPoint(j, x_Combined, y_Combined);

      //if(x_Combined==x_SR1){
      if(x_Combined==x_SR1 && x_Combined!=500 && x_Combined!=600){ //FIXME
        cout << x_Combined << "\t" << y_Combined << "\t" << y_SR1 << endl;
        vec_mass_ratio_ElEl_SRs.push_back(x_Combined);
        vec_ratio_ElEl_SRs.push_back(y_SR1/y_Combined);

      }

    }
  }
  const int n_ratio_ElEl_SRs = vec_mass_ratio_ElEl_SRs.size();
  double mass_ratio_ElEl_SRs[n_ratio_ElEl_SRs], ratio_ElEl_SRs[n_ratio_ElEl_SRs];
  for(int i=0; i<n_ratio_ElEl_SRs; i++){
    mass_ratio_ElEl_SRs[i] = vec_mass_ratio_ElEl_SRs.at(i);
    ratio_ElEl_SRs[i] = vec_ratio_ElEl_SRs.at(i);
  }
  TGraph *gr_ratio_ElEl_SRs = new TGraph(n_ratio_ElEl_SRs, mass_ratio_ElEl_SRs, ratio_ElEl_SRs);

  vector<double> vec_mass_ratio_MuEl_SRs, vec_ratio_MuEl_SRs;
  int NX_MuEl_SR1 = gr_MuEl_SR1->GetN();
  int NX_MuEl_Combined = gr_MuEl_Combined->GetN();
  cout << "[HiggsCombindedLimit_AllChannel] vec_mass_ratio_MuEl_SRs" << endl;
  for(int i=0; i<NX_MuEl_SR1; i++){
    double x_SR1, y_SR1;
    gr_MuEl_SR1->GetPoint(i, x_SR1, y_SR1);

    for(int j=0; j<NX_MuEl_Combined; j++){
      double x_Combined, y_Combined;
      gr_MuEl_Combined->GetPoint(j, x_Combined, y_Combined);

      //if(x_Combined==x_SR1){
      if(x_Combined==x_SR1 && x_Combined!=500 && x_Combined!=600){ //FIXME
        cout << x_Combined << "\t" << y_Combined << "\t" << y_SR1 << endl;
        vec_mass_ratio_MuEl_SRs.push_back(x_Combined);
        vec_ratio_MuEl_SRs.push_back(y_SR1/y_Combined);

      }

    }
  }
  const int n_ratio_MuEl_SRs = vec_mass_ratio_MuEl_SRs.size();
  double mass_ratio_MuEl_SRs[n_ratio_MuEl_SRs], ratio_MuEl_SRs[n_ratio_MuEl_SRs];
  for(int i=0; i<n_ratio_MuEl_SRs; i++){
    mass_ratio_MuEl_SRs[i] = vec_mass_ratio_MuEl_SRs.at(i);
    ratio_MuEl_SRs[i] = vec_ratio_MuEl_SRs.at(i);
  }
  TGraph *gr_ratio_MuEl_SRs = new TGraph(n_ratio_MuEl_SRs, mass_ratio_MuEl_SRs, ratio_MuEl_SRs);

  TCanvas *c_ratio_SRs = new TCanvas("c_ratio_SRs", "", 600, 600);
  c_ratio_SRs->cd();
  c_ratio_SRs->SetLogx();
  canvas_margin(c_ratio_SRs);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetXaxis()->SetRangeUser(20, 1500);
  dummy->GetYaxis()->SetRangeUser(0., 30);
  dummy->GetYaxis()->SetTitle("Sensitivity Ratio");

  gr_ratio_MuMu_SRs->SetLineColor(kCyan);
  gr_ratio_ElEl_SRs->SetLineColor(kRed);
  gr_ratio_MuEl_SRs->SetLineColor(kBlue);

  gr_ratio_MuMu_SRs->SetLineWidth(3);
  gr_ratio_ElEl_SRs->SetLineWidth(3);
  gr_ratio_MuEl_SRs->SetLineWidth(3);

  gr_ratio_MuMu_SRs->Draw("lsame");
  gr_ratio_ElEl_SRs->Draw("lsame");
  gr_ratio_MuEl_SRs->Draw("lsame");

  TLegend * lg_ratio_SRs = new TLegend(0.20, 0.50, 0.52, 0.85);
  lg_ratio_SRs->SetBorderSize(0);
  lg_ratio_SRs->SetFillStyle(0);

  if(ObsOrExp==0){
    lg_ratio_SRs->AddEntry(gr_ratio_MuMu_SRs, "Observed #||{V_{#muN}}^{2}", "l");
    lg_ratio_SRs->AddEntry(gr_ratio_ElEl_SRs, "Observed #||{V_{eN}}^{2}", "l");
    lg_ratio_SRs->AddEntry(gr_ratio_MuEl_SRs, "Observed #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");
  }
  else{
    lg_ratio_SRs->AddEntry(gr_ratio_MuMu_SRs, "Expected #||{V_{#muN}}^{2}", "l");
    lg_ratio_SRs->AddEntry(gr_ratio_ElEl_SRs, "Expected #||{V_{eN}}^{2}", "l");
    lg_ratio_SRs->AddEntry(gr_ratio_MuEl_SRs, "Expected #frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}", "l");
  }

  lg_ratio_SRs->Draw();

  c_ratio_SRs->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_ratio_SRs.pdf");
  c_ratio_SRs->SaveAs(plotpath+"/AllChannel_13TeV_mixing_logx_ratio_SRs.png");

  c_ratio_SRs->Close();

}

double GetXsecSch(int mass){

  if(mass==15) return 43.62;
  if(mass==20) return 41.725;
  if(mass==30) return 36.515;
  if(mass==40) return 29.265;
  if(mass==50) return 20.67;
  if(mass==60) return 11.635;
  if(mass==65) return 7.475;
  if(mass==70) return 3.917;
  if(mass==75) return 1.4315;
  if(mass==80){
    return 0.401242;
/*
    Wrong = 2.01340
    Correct = 0.4525
    correction = Correct/Wrong;
    return 8.29E-01*correction;
*/
  }
  if(mass==85) return 2.26E-01;
  if(mass==90) return 1.54E-01;
  if(mass==95) return 1.09E-01;
  if(mass==100) return 7.77E-02;
  if(mass==125) return 2.45E-02;
  if(mass==150) return 1.10E-02;
  if(mass==200) return 3.40E-03;
  if(mass==250) return 1.43E-03;
  if(mass==300) return 7.13E-04;
  if(mass==400) return 2.37E-04;
  if(mass==500) return 9.86E-05;
  if(mass==600) return 4.72E-05;
  if(mass==700) return 2.47E-05;
  if(mass==800) return 1.38E-05;
  if(mass==900) return 8.11E-06;
  if(mass==1000) return 4.96E-06;
  if(mass==1100) return 3.12E-06;
  if(mass==1200) return 2.02E-06;
  if(mass==1300) return 1.33E-06;
  if(mass==1400) return 8.91E-07;
  if(mass==1500) return 6.05E-07;
  if(mass==1700) return 2.90E-07;
  if(mass==2000) return 1.02E-07;

  cout << "[GetXsec] Mass Wrong : " << mass << endl;
  return 0.;
}

double GetXsecTch(int mass){

  if(mass==100) return 9.65E-04;
  if(mass==150) return 4.91E-04;
  if(mass==200) return 3.28E-04;
  if(mass==300) return 1.83E-04;
  if(mass==400) return 1.16E-04;
  if(mass==500) return 7.81E-05;
  if(mass==600) return 5.50E-05;
  if(mass==700) return 3.98E-05;
  if(mass==800) return 2.94E-05;
  if(mass==900) return 2.22E-05;
  if(mass==1000) return 1.69E-05;
  if(mass==1100) return 1.30E-05;
  if(mass==1200) return 1.02E-05;
  if(mass==1300) return 7.94E-06;
  if(mass==1400) return 6.27E-06;
  if(mass==1500) return 5.00E-06;
  if(mass==1700) return 3.21E-06;
  if(mass==2000) return 1.69E-06;

  cout << "[GetXsecTch] Mass Wrong : " << mass << endl;
  return 0.;
}

























