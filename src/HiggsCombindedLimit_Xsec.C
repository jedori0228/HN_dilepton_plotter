#include "canvas_margin.h"

double GetXsec(int mass);
double GetXsecST(int mass);

void HiggsCombindedLimit_Xsec(int i=0){

  bool DrawObserved = true;

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limit/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/";

  TString WhichDirectoryInCutop = "MuEl_Combined";
  if(i==1) WhichDirectoryInCutop = "MuMu_Bin1";
  if(i==2) WhichDirectoryInCutop = "MuMu_Bin2";
  if(i==3) WhichDirectoryInCutop = "MuMu_Combined";
  if(i==4) WhichDirectoryInCutop = "ElEl_Bin1";
  if(i==5) WhichDirectoryInCutop = "ElEl_Bin2";
  if(i==6) WhichDirectoryInCutop = "ElEl_Combined";
  if(i==7) WhichDirectoryInCutop = "MuEl_Bin1";
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

  //=== 13 TeV S+T channel

  string elline;
  ifstream in(filepath+"/result.txt");
  const int n_central = 19;
  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];

  vector<int> MassInTchSample = {300, 600, 800, 1000, 1200, 1500};

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

    double scale=1.; //mixing squared is 0.01 now
    if(mass[dummyint]<=60) scale *= 0.01;
    else if(mass[dummyint]<=100) scale *= 0.1;
    else if(mass[dummyint]<=300) scale *= 1.;
    else if(mass[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    double this_xsec = GetXsec(mass[dummyint]);

    if(mass[dummyint] >= MassInTchSample.at(0)){
      this_xsec += GetXsecST(mass[dummyint])/2.; // SS Only
    }

    scale *= this_xsec;

    //if(channel=="MuEl") scale *= 0.5;

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

  TGraph *gr_13TeV_obs = new TGraph(n_central,mass,obs);
  gr_13TeV_obs->SetLineWidth(3);
  gr_13TeV_obs->SetLineColor(kBlack);

  TGraph *gr_13TeV_exp = new TGraph(n_central,mass,limit);
  gr_13TeV_exp->SetLineWidth(3);
  gr_13TeV_exp->SetLineStyle(2);
  gr_13TeV_exp->SetFillColor(kWhite);

  TGraphAsymmErrors *gr_band_1sigma = new TGraphAsymmErrors(n_central, mass, limit, 0, 0, onesig_left, onesig_right);
  gr_band_1sigma->SetFillColor(kGreen);
  gr_band_1sigma->SetLineColor(kGreen);
  gr_band_1sigma->SetMarkerColor(kGreen);

  TGraphAsymmErrors *gr_band_2sigma = new TGraphAsymmErrors(n_central, mass, limit, 0, 0, twosig_left, twosig_right);
  gr_band_2sigma->SetFillColor(kYellow);
  gr_band_2sigma->SetLineColor(kYellow);
  gr_band_2sigma->SetMarkerColor(kYellow);


  //==== 13 TeV S channel only

  string elline_SOnly;
  ifstream in_SOnly(filepath+"/result_SOnly.txt");

  const int n_SOnly = 13;
  double mass_SOnly[n_SOnly], obs_SOnly[n_SOnly], limit_SOnly[n_SOnly], onesig_left_SOnly[n_SOnly], onesig_right_SOnly[n_SOnly], twosig_left_SOnly[n_SOnly], twosig_right_SOnly[n_SOnly];
  dummyint=0;

  while(getline(in_SOnly,elline_SOnly)){
    std::istringstream is( elline_SOnly );

    is >> mass_SOnly[dummyint];
    is >> obs_SOnly[dummyint];
    is >> limit_SOnly[dummyint];
    is >> onesig_left_SOnly[dummyint];
    is >> onesig_right_SOnly[dummyint];
    is >> twosig_left_SOnly[dummyint];
    is >> twosig_right_SOnly[dummyint];

    double scale=1.; //mixing squared is 0.01 now
    if(mass_SOnly[dummyint]<=60) scale *= 0.01;
    else if(mass_SOnly[dummyint]<=100) scale *= 0.1;
    else if(mass_SOnly[dummyint]<=300) scale *= 1.;
    else if(mass_SOnly[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    double this_xsec = GetXsec(mass_SOnly[dummyint]);
    cout << mass_SOnly[dummyint] << "\t" << this_xsec << endl;
    scale *= this_xsec;

    obs_SOnly[dummyint] *= scale;
    limit_SOnly[dummyint] *= scale;
    onesig_left_SOnly[dummyint] *= scale;
    onesig_right_SOnly[dummyint] *= scale;
    twosig_left_SOnly[dummyint] *= scale;
    twosig_right_SOnly[dummyint] *= scale;

    onesig_left_SOnly[dummyint] = limit_SOnly[dummyint]-onesig_left_SOnly[dummyint];
    onesig_right_SOnly[dummyint] = onesig_right_SOnly[dummyint] - limit_SOnly[dummyint];
    twosig_left_SOnly[dummyint] = limit_SOnly[dummyint]-twosig_left_SOnly[dummyint];
    twosig_right_SOnly[dummyint] = twosig_right_SOnly[dummyint] - limit_SOnly[dummyint];

    dummyint++;
  }

  TGraph *gr_13TeV_obs_SOnly = new TGraph(n_SOnly,mass_SOnly,obs_SOnly);
  gr_13TeV_obs_SOnly->SetLineWidth(3);
  gr_13TeV_obs_SOnly->SetLineColor(kBlack);

  TGraph *gr_13TeV_exp_SOnly = new TGraph(n_SOnly,mass_SOnly,limit_SOnly);
  gr_13TeV_exp_SOnly->SetLineWidth(3);
  gr_13TeV_exp_SOnly->SetLineStyle(1);
  gr_13TeV_exp_SOnly->SetLineColor(kBlue);





  TLegend *lg = new TLegend(0.50, 0.55, 0.90, 0.90);
  TLegend *lg_log = new TLegend(0.20, 0.55, 0.60, 0.90);

  if(DrawObserved) lg->AddEntry(gr_13TeV_obs,"CL_{s} Observed", "l");
  lg->AddEntry(gr_13TeV_exp_SOnly, "CL_{s} Expected, s-ch only", "l");
  lg->AddEntry(gr_13TeV_exp,"CL_{s} Expected", "l");
  lg->AddEntry(gr_band_1sigma,"CL_{s} Expected #pm 1 s.d.", "f");
  lg->AddEntry(gr_band_2sigma,"CL_{s} Expected #pm 2 s.d.", "f");

  if(DrawObserved) lg_log->AddEntry(gr_13TeV_obs,"CL_{s} Observed", "l");
  lg_log->AddEntry(gr_13TeV_exp_SOnly, "CL_{s} Expected, s-ch only", "l");
  lg_log->AddEntry(gr_13TeV_exp,"CL_{s} Expected", "l");
  lg_log->AddEntry(gr_band_1sigma,"CL_{s} Expected #pm 1 s.d.", "f");
  lg_log->AddEntry(gr_band_2sigma,"CL_{s} Expected #pm 2 s.d.", "f");

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
      0.238636, 0.171337, 0.204524, 0.525581, 0.142802,
      0.15618, 0.0365141, 0.0110612, 0.00617064, 0.004475,
      0.00355606, 0.00283105, 0.00215555, 0.00175336, 0.00163501, 0.00168907,
    };
  }
  if(channel=="MuMu"){
    MixingValues8TeV = {
      //==== MuMu
      0.0574156, 0.0529912, 0.0694351, 0.175697, 0.0380223,
      0.0555941, 0.0123044, 0.00419174, 0.00276877, 0.00225111,
      0.00191277, 0.00132662, 0.00124522, 0.0011111, 0.0012705, 0.00143492,
    };
  }
  if(channel=="MuEl"){
    MixingValues8TeV = {
      //==== MuEl
      0.270911, 0.229688, 0.278787, 0.771095, 0.147626,
      0.133925, 0.0327043, 0.00959089, 0.00551888, 0.00407575,
      0.00279852, 0.00222304, 0.00154023, 0.00146327, 0.00143876, 0.0016471,
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

  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  if(channel=="ElEl") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrowe^{#pm}N#rightarrowe^{#pm}e^{#pm}q#bar{q}] (pb)");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrow#mu^{#pm}N#rightarrow#mu^{#pm}#mu^{#pm}q#bar{q}] (pb)");
  if(channel=="MuEl") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrowe^{#pm}#mu^{#pm}N#rightarrowe^{#pm}#mu^{#pm}q#bar{q}] (pb)");
  dummy->GetXaxis()->SetTitle("m(N) (GeV)");
  dummy->GetXaxis()->SetRangeUser(10., 2000);
  dummy->GetYaxis()->SetTitleSize(0.06); 
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");

  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");
  gr_13TeV_exp->Draw("lsame");
  gr_8TeV_exp->Draw("lsame");
  if(DrawObserved) gr_13TeV_obs->Draw("lsame");
  gr_13TeV_exp_SOnly->Draw("lsame");

  lg->AddEntry(gr_8TeV_exp, "CMS 8 TeV Expected", "l");
  lg->SetX2NDC(0.90);
  lg->SetY2NDC(0.67);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  lg->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

  c_out->SaveAs(plotpath+"/"+channel+"_13TeV_xsec.pdf");
  c_out->SaveAs(plotpath+"/"+channel+"_13TeV_xsec.png");
  c_out->Close();

  //==== logX
  TCanvas *c_out_logx = new TCanvas("c_out_logx", "", 800, 800);
  canvas_margin(c_out_logx);
  c_out_logx->cd();
  c_out_logx->Draw();
  c_out_logx->SetLogy();
  //c_out_logx->SetGridx();
  //c_out_logx->SetGridy();

  dummy->Draw("hist");
  hist_axis(dummy);
  if(channel=="ElEl") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrowe^{#pm}N#rightarrowe^{#pm}e^{#pm}q#bar{q}] (pb)");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrow#mu^{#pm}N#rightarrow#mu^{#pm}#mu^{#pm}q#bar{q}] (pb)");
  if(channel=="MuEl") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrowe^{#pm}#mu^{#pm}N#rightarrowe^{#pm}#mu^{#pm}q#bar{q}] (pb)");
  dummy->GetXaxis()->SetTitle("m(N) (GeV)");
  dummy->GetXaxis()->SetRangeUser(10., 2500);
  dummy->GetYaxis()->SetTitleSize(0.06);
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");

  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");
  gr_13TeV_exp->Draw("lsame");
  gr_8TeV_exp->Draw("lsame");
  gr_13TeV_exp_SOnly->Draw("lsame");
  if(DrawObserved) gr_13TeV_obs->Draw("lsame");

  lg_log->AddEntry(gr_8TeV_exp, "CMS 8 TeV Expected", "l");
  lg_log->SetX2NDC(0.90);
  lg_log->SetY2NDC(0.67);
  lg_log->SetBorderSize(0);
  lg_log->SetFillStyle(0);
  //lg_log->Draw();
  lg->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

  c_out_logx->SetLogx();
  c_out_logx->SaveAs(plotpath+"/"+channel+"_13TeV_xsec_logx.pdf");
  c_out_logx->SaveAs(plotpath+"/"+channel+"_13TeV_xsec_logx.png");

  c_out_logx->Close();






}

double GetXsec(int mass){

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
    return 0.4525;
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
  return -999;
}

double GetXsecST(int mass){

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

  cout << "[GetXsecST] Mass Wrong : " << mass << endl;
  return -999;
}













