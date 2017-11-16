#include "canvas_margin.h"

void HiggsCombindedLimit(int i=0){

  bool DrawObserved = false;

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limit/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/";

  TString WhichDirectoryInCutop = "MuEl_Combined";
  if(i==1) WhichDirectoryInCutop = "MuMu";
  if(i==2) WhichDirectoryInCutop = "MuMu_Bin2";
  if(i==3) WhichDirectoryInCutop = "MuMu_Combined";
  if(i==4) WhichDirectoryInCutop = "ElEl";
  if(i==5) WhichDirectoryInCutop = "ElEl_Bin2";
  if(i==6) WhichDirectoryInCutop = "ElEl_Combined";
  if(i==7) WhichDirectoryInCutop = "MuEl";
  if(i==8) WhichDirectoryInCutop = "MuEl_Bin2";
  if(i==9) WhichDirectoryInCutop = "MuEl_Combined";

  TString channel = "MuMu";
  if(WhichDirectoryInCutop.Contains("ElEl")) channel = "ElEl";
  if(WhichDirectoryInCutop.Contains("MuEl")) channel = "MuEl";

  filepath = filepath+WhichDirectoryInCutop+"/";
  plotpath = plotpath+WhichDirectoryInCutop+"/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  
  TLatex latex_CMSPriliminary, latex_Lumi;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();

  //=== 13 TeV S channel

  string elline;
  ifstream in(filepath+"/result_"+channel+".txt");
  double mass[24], obs[24], limit[24], onesig_left[24], onesig_right[24], twosig_left[24], twosig_right[24];

  int dummyint=0;
  while(getline(in,elline)){
    std::istringstream is( elline );

    is >> mass[dummyint];
    is >> obs[dummyint];
    is >> limit[dummyint];
    is >> onesig_left[dummyint];
    is >> onesig_right[dummyint];
    is >> twosig_left[dummyint];
    is >> twosig_right[dummyint];

    double scale=0.01; //mixing squared is 0.01 now
    if(mass[dummyint]<=60) scale *= 0.01;
    else if(mass[dummyint]<=100) scale *= 0.1;
    else if(mass[dummyint]<=300) scale *= 1.;
    else if(mass[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    if(channel=="MuEl") scale *= 0.5;

    obs[dummyint] *= scale;
    limit[dummyint] *= scale;
    onesig_left[dummyint] *= scale;
    onesig_right[dummyint] *= scale;
    twosig_left[dummyint] *= scale;
    twosig_right[dummyint] *= scale;

    onesig_left[dummyint] = limit[dummyint]-onesig_left[dummyint];
    onesig_right[dummyint] = onesig_right[dummyint] - limit[dummyint];
    twosig_left[dummyint] = limit[dummyint]-twosig_left[dummyint];
    twosig_right[dummyint] = twosig_right[dummyint] - limit[dummyint];

    dummyint++;
  }

  TGraph *gr_13TeV_obs = new TGraph(24,mass,obs);
  gr_13TeV_obs->SetLineWidth(3);
  gr_13TeV_obs->SetLineColor(kBlack);

  TGraph *gr_13TeV_exp = new TGraph(24,mass,limit);
  gr_13TeV_exp->SetLineWidth(3);
  gr_13TeV_exp->SetLineStyle(2);
  gr_13TeV_exp->SetFillColor(kWhite);

  TGraphAsymmErrors *gr_band_1sigma = new TGraphAsymmErrors(24, mass, limit, 0, 0, onesig_left, onesig_right);
  gr_band_1sigma->SetFillColor(kGreen);
  gr_band_1sigma->SetLineColor(kGreen);
  gr_band_1sigma->SetMarkerColor(kGreen);

  TGraphAsymmErrors *gr_band_2sigma = new TGraphAsymmErrors(24, mass, limit, 0, 0, twosig_left, twosig_right);
  gr_band_2sigma->SetFillColor(kYellow);
  gr_band_2sigma->SetLineColor(kYellow);
  gr_band_2sigma->SetMarkerColor(kYellow);


  //==== 13 TeV S+T channel

  string elline_SandT;
  ifstream in_SandT(filepath+"/result_"+channel+"_VBF.txt");

  double mass_SandT[5], obs_SandT[5], limit_SandT[5], onesig_left_SandT[5], onesig_right_SandT[5], twosig_left_SandT[5], twosig_right_SandT[5];
  dummyint=0;

  while(getline(in_SandT,elline_SandT)){
    std::istringstream is( elline_SandT );

    is >> mass_SandT[dummyint];
    is >> obs_SandT[dummyint];
    is >> limit_SandT[dummyint];
    is >> onesig_left_SandT[dummyint];
    is >> onesig_right_SandT[dummyint];
    is >> twosig_left_SandT[dummyint];
    is >> twosig_right_SandT[dummyint];

    double scale=0.01; //mixing squared is 0.01 now
    if(mass_SandT[dummyint]<=60) scale *= 0.01;
    else if(mass_SandT[dummyint]<=100) scale *= 0.1;
    else if(mass_SandT[dummyint]<=300) scale *= 1.;
    else if(mass_SandT[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    if(channel=="MuEl") scale *= 0.5;

    obs_SandT[dummyint] *= scale;
    limit_SandT[dummyint] *= scale;
    onesig_left_SandT[dummyint] *= scale;
    onesig_right_SandT[dummyint] *= scale;
    twosig_left_SandT[dummyint] *= scale;
    twosig_right_SandT[dummyint] *= scale;

    onesig_left_SandT[dummyint] = limit_SandT[dummyint]-onesig_left_SandT[dummyint];
    onesig_right_SandT[dummyint] = onesig_right_SandT[dummyint] - limit_SandT[dummyint];
    twosig_left_SandT[dummyint] = limit_SandT[dummyint]-twosig_left_SandT[dummyint];
    twosig_right_SandT[dummyint] = twosig_right_SandT[dummyint] - limit_SandT[dummyint];

    dummyint++;
  }

  TGraph *gr_13TeV_obs_SandT = new TGraph(5,mass_SandT,obs_SandT);
  gr_13TeV_obs_SandT->SetLineWidth(3);
  gr_13TeV_obs_SandT->SetLineColor(kBlack);

  TGraph *gr_13TeV_exp_SandT = new TGraph(5,mass_SandT,limit_SandT);
  gr_13TeV_exp_SandT->SetLineWidth(5);
  gr_13TeV_exp_SandT->SetLineStyle(1);
  gr_13TeV_exp_SandT->SetLineColor(kViolet);





  TLegend *lg = new TLegend(0.50, 0.15, 0.90, 0.50);
  TLegend *lg_log = new TLegend(0.20, 0.55, 0.60, 0.90);

  if(DrawObserved) lg->AddEntry(gr_13TeV_obs,"CL_{s} Observed", "l");
  lg->AddEntry(gr_13TeV_exp,"CL_{s} Expected", "l");
  lg->AddEntry(gr_band_1sigma,"CL_{s} Expected #pm 1 #sigma", "f");
  lg->AddEntry(gr_band_2sigma,"CL_{s} Expected #pm 2 #sigma", "f");

  if(DrawObserved) lg_log->AddEntry(gr_13TeV_obs,"CL_{s} Observed", "l");
  lg_log->AddEntry(gr_13TeV_exp,"CL_{s} Expected", "l");
  lg_log->AddEntry(gr_band_1sigma,"CL_{s} Expected #pm 1 #sigma", "f");
  lg_log->AddEntry(gr_band_2sigma,"CL_{s} Expected #pm 2 #sigma", "f");

  //==== 8 TeV overlay

  const int nm = 16;
  double mass_8TeV[nm] = {
    40, 50, 60, 70, 80,
    90, 100, 125, 150, 175,
    200, 250, 300, 350, 400, 500
  };
  double exp[nm];

  vector<double> MixingValues8TeV;
  if(channel=="ElEl"){
    MixingValues8TeV = {
      //==== ElEl
      0.000117471, 0.000119376, 0.00025116, 0.00185047, 0.00558829,
      0.0164049, 0.00765044, 0.0076666, 0.0100238, 0.0143538,
      0.0202162, 0.0414845, 0.0692952, 0.111788, 0.192697, 0.58519,
    };
  }
  if(channel=="MuMu"){
    MixingValues8TeV = {
      //==== MuMu
      2.82635E-05, 3.69206E-05, 8.52678E-05, 0.000618594, 0.00148793,
      0.00583953, 0.00257802, 0.00290533, 0.00449771, 0.00722055,
      0.0108741, 0.0194395, 0.0400305, 0.0708397, 0.149737, 0.497138
    };
  }
  if(channel=="MuEl"){
    MixingValues8TeV = {
      //==== MuEl
      6.66795e-05, 8.00154e-05, 0.000171178, 0.00135744, 0.00288853,
      0.00703366, 0.0034261, 0.00332376, 0.00448255, 0.00653659,
      0.00795478, 0.0162876, 0.0247572, 0.0466464, 0.0847838, 0.285325,
    };
  }

  for(unsigned int j=0; j<MixingValues8TeV.size(); j++) exp[j] = MixingValues8TeV.at(j);

  TGraph *gr_8TeV_exp = new TGraph(nm, mass_8TeV, exp);
  gr_8TeV_exp->SetLineColor(kRed);
  gr_8TeV_exp->SetLineWidth(3);

  TCanvas *c_out = new TCanvas("c_out", "", 800, 800);
  canvas_margin(c_out);
  c_out->cd();
  c_out->Draw();
  c_out->SetLogy();
  c_out->SetGridx();
  c_out->SetGridy();

  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  if(channel=="ElEl") dummy->GetYaxis()->SetTitle("|V_{eN}|^{2}");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("|V_{#muN}|^{2}");
  if(channel=="MuEl") dummy->GetYaxis()->SetTitle("|V_{eN}V_{#muN}^{*}|/(|V_{eN}|^{2}+|V_{#muN}|^{2})");
  dummy->GetXaxis()->SetTitle("m(HN) [GeV]");
  dummy->GetXaxis()->SetRangeUser(10., 2000);
  dummy->GetYaxis()->SetTitleSize(0.06); 
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");

  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");
  gr_13TeV_exp->Draw("lsame");
  gr_8TeV_exp->Draw("lsame");
  if(DrawObserved) gr_13TeV_obs->Draw("lsame");
  gr_13TeV_exp_SandT->Draw("lsame");

  lg->AddEntry(gr_8TeV_exp, "CMS 8 TeV Expected", "l");
  lg->SetX2NDC(0.90);
  lg->SetY2NDC(0.67);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  lg->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} Simulation");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

  c_out->SaveAs(plotpath+"/"+channel+"_13TeV_mixing.pdf");
  c_out->SaveAs(plotpath+"/"+channel+"_13TeV_mixing.png");
  c_out->Close();

  //==== logX
  TCanvas *c_out_logx = new TCanvas("c_out_logx", "", 800, 800);
  canvas_margin(c_out_logx);
  c_out_logx->cd();
  c_out_logx->Draw();
  c_out_logx->SetLogy();
  c_out_logx->SetGridx();
  c_out_logx->SetGridy();

  dummy->Draw("hist");
  hist_axis(dummy);
  if(channel=="ElEl") dummy->GetYaxis()->SetTitle("|V_{eN}|^{2}");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("|V_{#muN}|^{2}");
  if(channel=="MuEl") dummy->GetYaxis()->SetTitle("|V_{eN}V_{#muN}^{*}|/(|V_{eN}|^{2}+|V_{#muN}|^{2})");
  dummy->GetXaxis()->SetTitle("m(HN) [GeV]");
  dummy->GetXaxis()->SetRangeUser(20., 2500);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");

  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");
  gr_13TeV_exp->Draw("lsame");
  gr_8TeV_exp->Draw("lsame");
  gr_13TeV_exp_SandT->Draw("lsame");
  if(DrawObserved) gr_13TeV_obs->Draw("lsame");

  lg_log->AddEntry(gr_8TeV_exp, "CMS 8 TeV Expected", "l");
  lg_log->SetX2NDC(0.90);
  lg_log->SetY2NDC(0.67);
  lg_log->SetBorderSize(0);
  lg_log->SetFillStyle(0);
  //lg_log->Draw();
  lg->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} Simulation");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

  c_out_logx->SetLogx();
  c_out_logx->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx.pdf");
  c_out_logx->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx.png");

  c_out_logx->Close();






}
