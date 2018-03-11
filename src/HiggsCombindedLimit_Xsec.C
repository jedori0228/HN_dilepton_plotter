#include "canvas_margin.h"

double GetXsec(int mass);
double GetXsecTch(int mass);

void HiggsCombindedLimit_Xsec(int i=0){

  bool DrawObserved = true;

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  //TString filepath = ENV_FILE_PATH+dataset+"/Limit/";
  //TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/";

  TString filepath = ENV_FILE_PATH+dataset+"/Limit/FullCLs/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/FullCLs/";

  TString WhichDirectoryInCutop = "MuMu_Combined";
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
  
  TLatex latex_CMSPriliminary, latex_Lumi, latex_title, latex_processname;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_title.SetNDC();
  latex_processname.SetNDC();

  //=== 13 TeV S-only channel

  string elline;
  ifstream in(filepath+"/result.txt");
  int n_central = 27;  //28, but now removing 80 GeV
  double mass[n_central], obs[n_central], limit[n_central], onesig_left[n_central], onesig_right[n_central], twosig_left[n_central], twosig_right[n_central];

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

    if(obs[dummyint]<=0 || limit[dummyint]<=0 || onesig_left[dummyint]<=0 || onesig_right[dummyint]<=0 || twosig_left[dummyint]<=0 || twosig_right[dummyint]<=0){
      n_central--;
      continue;
    }
    if(mass[dummyint]>=1700){
      n_central--;
      continue;
    }

    double scale=1.; //mixing squared is 0.01 now
    if(mass[dummyint]<=60) scale *= 0.01;
    else if(mass[dummyint]<=100) scale *= 0.1;
    else if(mass[dummyint]<=300) scale *= 1.;
    else if(mass[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    scale *= 0.01;

    double this_xsec = GetXsec(mass[dummyint]);

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


  //==== 13 TeV T added

  string elline_SandT;
  ifstream in_SandT(filepath+"/result_VBF.txt");

  int n_SandT = 29; //30, but now removing 80 GeV
  double mass_SandT[n_SandT], obs_SandT[n_SandT], limit_SandT[n_SandT], onesig_left_SandT[n_SandT], onesig_right_SandT[n_SandT], twosig_left_SandT[n_SandT], twosig_right_SandT[n_SandT];
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

    if(obs_SandT[dummyint]<=0 || limit_SandT[dummyint]<=0 || onesig_left_SandT[dummyint]<=0 || onesig_right_SandT[dummyint]<=0 || twosig_left_SandT[dummyint]<=0 || twosig_right_SandT[dummyint]<=0){
      n_SandT--;
      continue;
    }
    if(mass_SandT[dummyint]>=1700){
      n_SandT--;
      continue;
    }

    double scale=1.; //mixing squared is 0.01 now
    if(mass_SandT[dummyint]<=60) scale *= 0.01;
    else if(mass_SandT[dummyint]<=100) scale *= 0.1;
    else if(mass_SandT[dummyint]<=300) scale *= 1.;
    else if(mass_SandT[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    scale *= 0.01;

    double this_xsec = GetXsec(mass_SandT[dummyint]);
    this_xsec += GetXsecTch(mass[dummyint])/2.; // SS-only

    scale *= this_xsec;

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

  TGraph *gr_13TeV_obs_SandT = new TGraph(n_SandT,mass_SandT,obs_SandT);
  gr_13TeV_obs_SandT->SetLineWidth(3);
  gr_13TeV_obs_SandT->SetLineColor(kBlack);

  TGraph *gr_13TeV_exp_SandT = new TGraph(n_SandT,mass_SandT,limit_SandT);
  gr_13TeV_exp_SandT->SetLineWidth(3);
  gr_13TeV_exp_SandT->SetLineStyle(2);
  gr_13TeV_exp_SandT->SetFillColor(kWhite);

  TGraphAsymmErrors *gr_band_1sigma_SandT = new TGraphAsymmErrors(n_SandT, mass_SandT, limit_SandT, 0, 0, onesig_left_SandT, onesig_right_SandT);
  gr_band_1sigma_SandT->SetFillColor(kGreen);
  gr_band_1sigma_SandT->SetLineColor(kGreen);
  gr_band_1sigma_SandT->SetMarkerColor(kGreen);

  TGraphAsymmErrors *gr_band_2sigma_SandT = new TGraphAsymmErrors(n_SandT, mass_SandT, limit_SandT, 0, 0, twosig_left_SandT, twosig_right_SandT);
  gr_band_2sigma_SandT->SetFillColor(kYellow);
  gr_band_2sigma_SandT->SetLineColor(kYellow);
  gr_band_2sigma_SandT->SetMarkerColor(kYellow);

  //==== 8 TeV overlay

  const int nm = 16;
  double mass_8TeV[nm] = {
    40, 50, 60, 70, 80,
    90, 100, 125, 150, 175,
    200, 250, 300, 350, 400, 500
  };
  double obs_8TeV[nm], exp_8TeV[nm];

  vector<double> tempvec_obs_8TeV, tempvec_exp_8TeV;
  if(channel=="ElEl"){
    tempvec_obs_8TeV = {
0.310856, 0.228104, 0.268764, 0.682266, 0.187104, 0.209065, 0.0521459, 0.0113648, 0.00491012, 0.00354478, 0.00278916, 0.00285184, 0.00252027, 0.00218728, 0.00201853, 0.00208477,
    };
    tempvec_exp_8TeV = {
0.238636, 0.171337, 0.204524, 0.525581, 0.142802, 0.15618, 0.0365141, 0.0110612, 0.00617064, 0.004475, 0.00355606, 0.00283105, 0.00215555, 0.00175336, 0.00163501, 0.00168907,
    };
  }
  if(channel=="MuMu"){
    tempvec_obs_8TeV = {
0.0425758, 0.0370795, 0.0509001, 0.111657, 0.0262207, 0.0488669, 0.011495, 0.00263166, 0.00212999, 0.00260005, 0.00221507, 0.00140472, 0.00125629, 0.00118361, 0.00128623, 0.00152084,
    };
    tempvec_exp_8TeV = {
0.0574156, 0.0529912, 0.0694351, 0.175697, 0.0380223, 0.0555941, 0.0123044, 0.00419174, 0.00276877, 0.00225111, 0.00191277, 0.00132662, 0.00124522, 0.0011111, 0.0012705, 0.00143492,
    };
  }
  if(channel=="MuEl"){
    tempvec_obs_8TeV = {
0.269913, 0.228505, 0.279637, 0.771711, 0.171265, 0.163916, 0.0463834, 0.0140186, 0.00644153, 0.00476088, 0.00326979, 0.0028114, 0.0022835, 0.00224634, 0.00224528, 0.00262692,
    };
    tempvec_exp_8TeV = {
0.270911, 0.229688, 0.278787, 0.771095, 0.147626, 0.133925, 0.0327043, 0.00959089, 0.00551888, 0.00407575, 0.00279852, 0.00222304, 0.00154023, 0.00146327, 0.00143876, 0.0016471,
    };
  }

  for(unsigned int j=0; j<tempvec_obs_8TeV.size(); j++){
    obs_8TeV[j] = tempvec_obs_8TeV.at(j);
    exp_8TeV[j] = tempvec_exp_8TeV.at(j);
  }

  TGraph *gr_8TeV_exp = new TGraph(nm, mass_8TeV, obs_8TeV);
  gr_8TeV_exp->SetLineColor(kViolet);
  gr_8TeV_exp->SetLineStyle(10);
  gr_8TeV_exp->SetLineWidth(3);

  //======================
  //==== S-ch only limit
  //======================

  //=== Legend
  TLegend *lg = new TLegend(0.20, 0.15, 0.55, 0.40);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);

  if(DrawObserved) lg->AddEntry(gr_13TeV_obs,"CL_{s} Observed, s-ch only", "l");
  lg->AddEntry(gr_13TeV_exp,"CL_{s} Expected, s-ch only", "l");
  lg->AddEntry(gr_band_1sigma,"CL_{s} Expected #pm 1 s.d.", "f");
  lg->AddEntry(gr_band_2sigma,"CL_{s} Expected #pm 2 s.d.", "f");
  //lg->AddEntry(gr_8TeV_exp, "CMS 8 TeV", "l");

  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 800, 800);
  canvas_margin(c_SOnly);
  c_SOnly->cd();
  c_SOnly->Draw();
  c_SOnly->SetLogy();

  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetYaxis()->SetTitleSize(0.06);
/*
  if(channel=="ElEl") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrowe^{#pm}N#rightarrowe^{#pm}e^{#pm}q#bar{q}] (pb)");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrow#mu^{#pm}N#rightarrow#mu^{#pm}#mu^{#pm}q#bar{q}] (pb)");
  if(channel=="MuEl") dummy->GetYaxis()->SetTitle("#sigma#timesBR[pp#rightarrowe^{#pm}#mu^{#pm}N#rightarrowe^{#pm}#mu^{#pm}q#bar{q}] (pb)");
*/
  dummy->GetYaxis()->SetTitle("#sigma #times  #bf{#it{#Beta}} (pb)");
  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetXaxis()->SetRangeUser(10., 2500);
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");
  dummy->Draw("hist");

  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");
  gr_13TeV_exp->Draw("lsame");
  //gr_8TeV_exp->Draw("lsame");
  if(DrawObserved) gr_13TeV_obs->Draw("lsame");

  lg->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.20, 0.90, "#font[41]{95% CL upper limit}");

  TString processname = "";
  if(channel=="MuMu") processname = "pp#rightarrow#mu^{#pm}N#rightarrow#mu^{#pm}#mu^{#pm}q#bar{q'}";
  if(channel=="ElEl") processname = "pp#rightarrowe^{#pm}N#rightarrowe^{#pm}e^{#pm}q#bar{q'}";
  if(channel=="MuEl") processname = "pp#rightarrowl^{#pm}N#rightarrowl^{#pm}l^{#pm}q#bar{q'}";
  processname = "#font[41]{"+processname+"}";
  latex_processname.SetTextSize(0.04);
  latex_processname.SetLineWidth(2);
  latex_processname.DrawLatex(0.20, 0.85, processname);

  c_SOnly->SetLogx();
  c_SOnly->SaveAs(plotpath+"/"+channel+"_13TeV_xsec_logx.pdf");
  c_SOnly->SaveAs(plotpath+"/"+channel+"_13TeV_xsec_logx.png");

  c_SOnly->Close();

  //======================
  //==== S+T limit
  //======================

  //=== Legend
  TLegend * lg_SandT = new TLegend(0.20, 0.15, 0.55, 0.40);
  lg_SandT->SetBorderSize(0);
  lg_SandT->SetFillStyle(0);

  if(DrawObserved) lg_SandT->AddEntry(gr_13TeV_obs_SandT,"CL_{s} Observed, s- and t-ch", "l");
  lg_SandT->AddEntry(gr_13TeV_exp_SandT,"CL_{s} Expected, s- and t-ch", "l");
  lg_SandT->AddEntry(gr_band_1sigma_SandT,"CL_{s} Expected #pm 1 s.d., s- and t-ch", "f");
  lg_SandT->AddEntry(gr_band_2sigma_SandT,"CL_{s} Expected #pm 2 s.d., s- and t-ch", "f");
  //lg_SandT->AddEntry(gr_8TeV_exp, "CMS 8 TeV", "l");

  TCanvas *c_SandT = new TCanvas("c_SandT", "", 800, 800);
  canvas_margin(c_SandT);
  c_SandT->cd();
  c_SandT->Draw();
  c_SandT->SetLogy();

  dummy->Draw("hist");

  gr_band_2sigma_SandT->Draw("3same");
  gr_band_1sigma_SandT->Draw("3same");
  gr_13TeV_exp_SandT->Draw("lsame");
  //gr_8TeV_exp->Draw("lsame");
  if(DrawObserved) gr_13TeV_obs_SandT->Draw("lsame");

  lg_SandT->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.20, 0.90, "#font[41]{95% CL upper limit}");

  processname = "#font[41]{"+processname+"}";
  latex_processname.SetTextSize(0.04);
  latex_processname.SetLineWidth(2);
  latex_processname.DrawLatex(0.20, 0.85, processname);

  c_SandT->SetLogx();
  c_SandT->SaveAs(plotpath+"/"+channel+"_13TeV_xsec_logx_SandT.pdf");
  c_SandT->SaveAs(plotpath+"/"+channel+"_13TeV_xsec_logx_SandT.png");

  c_SandT->Close();

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













