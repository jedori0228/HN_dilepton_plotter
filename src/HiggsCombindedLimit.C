#include "canvas_margin.h"

void HiggsCombindedLimit(int i=0){

  bool DrawObserved = true;

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+dataset+"/Limit/";
  TString plotpath = ENV_PLOT_PATH+dataset+"/Limit/";

  TString WhichDirectoryInCutop = "MuMu_Bin1";
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
  
  TLatex latex_CMSPriliminary, latex_Lumi, latex_title;
  latex_CMSPriliminary.SetNDC();
  latex_Lumi.SetNDC();
  latex_title.SetNDC();

  //=== 13 TeV S-only channel

  string elline;
  ifstream in(filepath+"/result.txt");
  int n_central = 26; //FIXME 26
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

    double scale=0.01; //mixing squared is 0.01 now
    if(mass[dummyint]<=60) scale *= 0.01;
    else if(mass[dummyint]<=100) scale *= 0.1;
    else if(mass[dummyint]<=300) scale *= 1.;
    else if(mass[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    //if(mass[dummyint]==70) continue; //FIXME
    //if(mass[dummyint]==90) continue; //FIXME
    //if(mass[dummyint]==80) scale /= 4.45; //FIXME

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

  const int n_SandT = 6;
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

    double scale=0.01; //mixing squared is 0.01 now
    if(mass_SandT[dummyint]<=60) scale *= 0.01;
    else if(mass_SandT[dummyint]<=100) scale *= 0.1;
    else if(mass_SandT[dummyint]<=300) scale *= 1.;
    else if(mass_SandT[dummyint]<=700) scale *= 10.;
    else scale *= 100.;

    //if(mass[dummyint]==80) scale /= 4.45; //FIXME

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

  TGraph *gr_13TeV_obs_SandT = new TGraph(n_SandT,mass_SandT,obs_SandT);
  gr_13TeV_obs_SandT->SetLineWidth(3);
  gr_13TeV_obs_SandT->SetLineColor(kBlack);

  TGraph *gr_13TeV_exp_SandT = new TGraph(n_SandT,mass_SandT,limit_SandT);
  gr_13TeV_exp_SandT->SetLineColor(kBlack);
  gr_13TeV_exp_SandT->SetLineWidth(3);
  gr_13TeV_exp_SandT->SetLineStyle(2);

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
      0.000153022, 0.000158927, 0.000330048, 0.00240212, 0.00732196,
      0.0219599, 0.0109256, 0.00787703, 0.00797621, 0.0113701,
      0.0158563, 0.0417892, 0.08102, 0.139453, 0.237897, 0.722283,
    };
    tempvec_exp_8TeV = {
      0.000117471, 0.000119376, 0.00025116, 0.00185047, 0.00558829,
      0.0164049, 0.00765044, 0.0076666, 0.0100238, 0.0143538,
      0.0202162, 0.0414845, 0.0692952, 0.111788, 0.192697, 0.58519,
    };
  }
  if(channel=="MuMu"){
    tempvec_obs_8TeV = {
      2.09584e-05, 2.58344e-05, 6.25064e-05, 0.000393122, 0.0010261,
      0.00513292, 0.00240843, 0.00182402, 0.00346005, 0.00833979,
      0.0125927, 0.0205839, 0.0403864, 0.0754627, 0.151591, 0.526906, 
    };
    tempvec_exp_8TeV = {
      2.82635E-05, 3.69206E-05, 8.52678E-05, 0.000618594, 0.00148793,
      0.00583953, 0.00257802, 0.00290533, 0.00449771, 0.00722055,
      0.0108741, 0.0194395, 0.0400305, 0.0708397, 0.149737, 0.497138
    };
  }
  if(channel=="MuEl"){
    tempvec_obs_8TeV = {
      6.64339e-05, 7.96033e-05, 0.0001717, 0.00135852, 0.00335107,
      0.00860876, 0.00485913, 0.0048582, 0.00523195, 0.00763538,
      0.00929436, 0.0205983, 0.0367042, 0.0716093, 0.132311, 0.455058, 
    };
    tempvec_exp_8TeV = {
      6.66795e-05, 8.00154e-05, 0.000171178, 0.00135744, 0.00288853,
      0.00703366, 0.0034261, 0.00332376, 0.00448255, 0.00653659,
      0.00795478, 0.0162876, 0.0247572, 0.0466464, 0.0847838, 0.285325,
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

//======================================
  //==== LEP (L3)

  float L3[2][38];
  float DEL[2][39];
  float ATLAS[2][12];
  float CMS[2][8];
 
  L3[0][0]  = 20.75; L3[1][0]  = 1.53e-4;
  L3[0][1]  = 23.75; L3[1][1]  = 1.56e-4;
  L3[0][2]  = 26.37; L3[1][2]  = 1.59e-4;
  L3[0][3]  = 29.30; L3[1][3]  = 1.64e-4;
  L3[0][4]  = 32.54; L3[1][4]  = 1.69e-4;
  L3[0][5]  = 35.61; L3[1][5]  = 1.75e-4;
  L3[0][6]  = 39.55; L3[1][6]  = 1.84e-4;
  L3[0][7]  = 43.61; L3[1][7]  = 1.98e-4;
  L3[0][8]  = 48.45; L3[1][8]  = 2.20e-4;
  L3[0][9]  = 52.23; L3[1][9]  = 2.44e-4;
  L3[0][10] = 55.90; L3[1][10] = 2.76e-4;
  L3[0][11] = 59.82; L3[1][11] = 3.13e-4;
  L3[0][12] = 62.12; L3[1][12] = 3.50e-4;
  L3[0][13] = 64.03; L3[1][13] = 4.02e-4;
  L3[0][14] = 66.49; L3[1][14] = 4.56e-4;
  L3[0][15] = 69.05; L3[1][15] = 5.28e-4;
  L3[0][16] = 71.19; L3[1][16] = 6.49e-4;
  L3[0][17] = 72.28; L3[1][17] = 7.25e-4;
  L3[0][18] = 74.51; L3[1][18] = 8.78e-4;
  L3[0][19] = 76.24; L3[1][19] = 1.06e-3;
  L3[0][20] = 78.02; L3[1][20] = 1.35e-3;
  L3[0][21] = 79.20; L3[1][21] = 1.63e-3;
  L3[0][22] = 80.46; L3[1][22] = 2.03e-3;
  L3[0][23] = 81.71; L3[1][23] = 2.46e-3;
  L3[0][24] = 83.00; L3[1][24] = 3.23e-3;
  L3[0][25] = 84.30; L3[1][25] = 4.18e-3;
  L3[0][26] = 84.98; L3[1][26] = 5.49e-3;
  L3[0][27] = 85.67; L3[1][27] = 6.95e-3;
  L3[0][28] = 86.36; L3[1][28] = 8.80e-3;
  L3[0][29] = 87.40; L3[1][29] = 1.23e-2;
  L3[0][30] = 88.44; L3[1][30] = 1.62e-2;
  L3[0][31] = 89.17; L3[1][31] = 2.28e-2;
  L3[0][32] = 89.90; L3[1][32] = 3.03e-2;
  L3[0][33] = 90.20; L3[1][33] = 3.76e-2;
  L3[0][34] = 90.68; L3[1][34] = 4.75e-2;
  L3[0][35] = 90.72; L3[1][35] = 6.38e-2;
  L3[0][36] = 90.78; L3[1][36] = 8.69e-2;
  L3[0][37] = 90.81; L3[1][37] = 9.93e-2;

  DEL[0][0] = 10.1; DEL[1][0]   = 1.79e-5;
  DEL[0][1] = 11.2; DEL[1][1]   = 1.82e-5;
  DEL[0][2] = 12.7; DEL[1][2]   = 1.85e-5;
  DEL[0][3] = 15.1; DEL[1][3]   = 1.91e-5;
  DEL[0][4] = 17.8; DEL[1][4]   = 2.01e-5;
  DEL[0][5] = 19.8; DEL[1][5]   = 2.08e-5;
  DEL[0][6] = 21.8; DEL[1][6]   = 2.19e-5;
  DEL[0][7] = 23.5; DEL[1][7]   = 2.26e-5;
  DEL[0][8] = 25.5; DEL[1][8]   = 2.30e-5;
  DEL[0][9] = 27.4; DEL[1][9]   = 2.34e-5;
  DEL[0][10] = 29.6; DEL[1][10] = 2.37e-5;
  DEL[0][11] = 33.0; DEL[1][11] = 2.37e-5;
  DEL[0][12] = 36.0; DEL[1][12] = 2.41e-5;
  DEL[0][13] = 40.3; DEL[1][13] = 2.45e-5;
  DEL[0][14] = 44.5; DEL[1][14] = 2.53e-5;
  DEL[0][15] = 47.2; DEL[1][15] = 2.76e-5;
  DEL[0][16] = 50.7; DEL[1][16] = 3.05e-5;
  DEL[0][17] = 53.6; DEL[1][17] = 3.49e-5;
  DEL[0][18] = 56.0; DEL[1][18] = 4.07e-5;
  DEL[0][19] = 57.8; DEL[1][19] = 4.58e-5;
  DEL[0][20] = 59.4; DEL[1][20] = 5.25e-5;
  DEL[0][21] = 61.1; DEL[1][21] = 6.12e-5;
  DEL[0][22] = 62.8; DEL[1][22] = 7.25e-5;
  DEL[0][23] = 64.1; DEL[1][23] = 8.60e-5;
  DEL[0][24] = 65.6; DEL[1][24] = 1.00e-4;
  DEL[0][25] = 66.7; DEL[1][25] = 1.19e-4;
  DEL[0][26] = 67.8; DEL[1][26] = 1.41e-4;
  DEL[0][27] = 69.6; DEL[1][27] = 1.85e-4;
  DEL[0][28] = 70.8; DEL[1][28] = 2.30e-4;
  DEL[0][29] = 72.0; DEL[1][29] = 3.03e-4;
  DEL[0][30] = 73.2; DEL[1][30] = 3.84e-4;
  DEL[0][31] = 74.0; DEL[1][31] = 4.63e-4;
  DEL[0][32] = 75.2; DEL[1][32] = 5.77e-4;
  DEL[0][33] = 76.5; DEL[1][33] = 7.58e-4;
  DEL[0][34] = 76.9; DEL[1][34] = 8.98e-4;
  DEL[0][35] = 77.8; DEL[1][35] = 1.12e-3;
  DEL[0][36] = 78.2; DEL[1][36] = 1.33e-3;
  DEL[0][37] = 79.1; DEL[1][37] = 1.66e-3;
  DEL[0][38] = 79.9; DEL[1][38] = 2.03e-3;
  
  ATLAS[0][0] = 100; ATLAS[1][0]   = 3.5e-3;
  ATLAS[0][1] = 110; ATLAS[1][1]   = 2.8e-3;
  ATLAS[0][2] = 120; ATLAS[1][2]   = 3.0e-3;
  ATLAS[0][3] = 140; ATLAS[1][3]   = 5.1e-3;
  ATLAS[0][4] = 160; ATLAS[1][4]   = 6.9e-3;
  ATLAS[0][5] = 180; ATLAS[1][5]   = 1.0e-2;
  ATLAS[0][6] = 200; ATLAS[1][6]   = 1.7e-2;
  ATLAS[0][7] = 240; ATLAS[1][7]   = 2.6e-2;
  ATLAS[0][8] = 280; ATLAS[1][8]   = 4.2e-2;
  ATLAS[0][9] = 300; ATLAS[1][9]   = 5.1e-2;
  ATLAS[0][10] = 400; ATLAS[1][10]   = 1.7e-1;
  ATLAS[0][11] = 500; ATLAS[1][11] = 4.0e-1;

  TGraph *gr_L3Limit = new TGraph(38, L3[0], L3[1]);
  gr_L3Limit->SetLineWidth(3);
  gr_L3Limit->SetLineStyle(3);
  gr_L3Limit->SetLineColor(kBlue);

  TGraph *gr_DELPHILimit = new TGraph(39, DEL[0], DEL[1]);
  gr_DELPHILimit->SetLineWidth(3);
  gr_DELPHILimit->SetLineStyle(3);
  gr_DELPHILimit->SetLineColor(kRed);

//=======================================

//=======================================

  const int n_mass_trilep = 27;
  double mass_trilep[n_mass_trilep] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10,
    11, 12, 20, 30, 40, 50, 60,
    80,
    100, 130, 150, 200, 400,
    600, 800, 1000, 1200
  };
  vector<double> tmpvec_obs_trilep = {
    0.0163432, 0.00188519, 0.000596955, 0.000282105, 0.000150402,
    0.000104186, 6.77325E-05, 4.99932E-05, 3.53255E-05, 3.13575E-05,
    2.48346E-05, 2.14113E-05, 1.48891E-05, 1.77713E-05, 1.88793E-05, 1.88341E-05, 2.7883E-05,

    0.000333583, //FIXME
    //0.00148444, //scaled FIXME

    0.00452962, 0.0074026, 0.00826272, 0.00848118, 0.0303979,
    0.0835546, 0.2063, 0.440587, 0.846273
  };
  if(channel=="ElEl"){
    tmpvec_obs_trilep = {
      0.0135784, 0.00151879, 0.000447416, 0.000223742, 0.00011303,
      7.23346E-05, 5.10346E-05, 3.77547E-05, 2.72229E-05, 2.33201E-05,
      1.8688E-05, 1.75216E-05, 1.20661E-05, 1.60735E-05, 2.19737E-05, 3.32274E-05, 6.70456E-05,

      0.00076608, //FIXME
      //0.00340906, //scaled FIXME

      0.00662448, 0.010974, 0.014264, 0.0135633, 0.0523753,
      0.167425, 0.428148, 0.949388, 1.83977
    };
  }
  double obs_trilep[n_mass_trilep];
  for(unsigned int i=0; i<tmpvec_obs_trilep.size(); i++) obs_trilep[i] = tmpvec_obs_trilep.at(i);
  TGraph *gr_trilepLimit = new TGraph(n_mass_trilep, mass_trilep, obs_trilep);
  gr_trilepLimit->SetLineWidth(3);
  gr_trilepLimit->SetLineStyle(5);
  gr_trilepLimit->SetLineColor(kRed-5);

//=======================================




  //======================
  //==== S-ch only limit
  //======================

  //=== Legend
  TLegend *lg = new TLegend(0.50, 0.15, 0.90, 0.45);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);

  if(DrawObserved) lg->AddEntry(gr_13TeV_obs,"CL_{s} Observed, s-ch only", "l");
  lg->AddEntry(gr_13TeV_exp,"CL_{s} Expected, s-ch only", "l");
  lg->AddEntry(gr_band_1sigma,"CL_{s} Expected #pm 1 s.d.", "f");
  lg->AddEntry(gr_band_2sigma,"CL_{s} Expected #pm 2 s.d.", "f");
  lg->AddEntry(gr_8TeV_exp, "CMS 8 TeV", "l");
  if(channel!="MuEl"){
    lg->AddEntry(gr_L3Limit, "L3", "l");
    lg->AddEntry(gr_DELPHILimit, "DELPHI", "l");
    lg->AddEntry(gr_trilepLimit, "CMS 13TeV Trilepton", "l");
  }

  TCanvas *c_SOnly = new TCanvas("c_SOnly", "", 800, 800);
  canvas_margin(c_SOnly);
  c_SOnly->cd();
  c_SOnly->Draw();
  c_SOnly->SetLogy();

  TH1D *dummy = new TH1D("hist", "", 10000, 0., 10000.);
  dummy->Draw("hist");
  hist_axis(dummy);
  dummy->GetYaxis()->SetTitleSize(0.06);
  if(channel=="ElEl") dummy->GetYaxis()->SetTitle("#||{V_{eN}}^{2}");
  if(channel=="MuMu") dummy->GetYaxis()->SetTitle("#||{V_{#muN}}^{2}");
  if(channel=="MuEl"){
    dummy->GetYaxis()->SetTitle("#frac{#||{ V_{eN}V_{#muN}^{*}}}{#||{ V_{eN} }^{2} + #||{ V_{#muN} }^{2}}");
    dummy->GetYaxis()->SetTitleOffset(2.1);
    dummy->GetYaxis()->SetTitleSize(0.03);
  }
  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetXaxis()->SetRangeUser(10., 2500);
  dummy->GetYaxis()->SetRangeUser(0.000005, 20.);
  dummy->SetTitle("");
  dummy->Draw("hist");

  gr_band_2sigma->Draw("3same");
  gr_band_1sigma->Draw("3same");
  gr_13TeV_exp->Draw("lsame");
  gr_8TeV_exp->Draw("lsame");
  if(channel!="MuEl"){
    gr_L3Limit->Draw("lsame");
    gr_DELPHILimit->Draw("lsame");
    gr_trilepLimit->Draw("lsame");
  }
  if(DrawObserved) gr_13TeV_obs->Draw("lsame");

  lg->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.20, 0.90, "#font[41]{95% CL upper limit}");

  c_SOnly->SetLogx();
  c_SOnly->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx.pdf");
  c_SOnly->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx.png");

  c_SOnly->Close();

  //======================
  //==== S+T limit
  //======================

  //=== Legend
  TLegend * lg_SandT = new TLegend(0.50, 0.15, 0.90, 0.45);
  lg_SandT->SetBorderSize(0);
  lg_SandT->SetFillStyle(0);

  if(DrawObserved) lg_SandT->AddEntry(gr_13TeV_obs_SandT,"CL_{s} Observed, s- and t-ch", "l");
  lg_SandT->AddEntry(gr_13TeV_exp_SandT,"CL_{s} Expected, s- and t-ch", "l");
  lg_SandT->AddEntry(gr_band_1sigma_SandT,"CL_{s} Expected #pm 1 s.d., s- and t-ch", "f");
  lg_SandT->AddEntry(gr_band_2sigma_SandT,"CL_{s} Expected #pm 2 s.d., s- and t-ch", "f");
  lg_SandT->AddEntry(gr_8TeV_exp, "CMS 8 TeV", "l");
  if(channel!="MuEl"){
    lg_SandT->AddEntry(gr_L3Limit, "L3", "l");
    lg_SandT->AddEntry(gr_DELPHILimit, "DELPHI", "l");
    lg_SandT->AddEntry(gr_trilepLimit, "CMS 13TeV Trilepton", "l");
  }

  TCanvas *c_SandT = new TCanvas("c_SandT", "", 800, 800);
  canvas_margin(c_SandT);
  c_SandT->cd();
  c_SandT->Draw();
  c_SandT->SetLogy();

  dummy->Draw("hist");

  gr_band_2sigma_SandT->Draw("3same");
  gr_band_1sigma_SandT->Draw("3same");
  gr_13TeV_exp_SandT->Draw("lsame");
  gr_8TeV_exp->Draw("lsame");
  if(channel!="MuEl"){
    gr_L3Limit->Draw("lsame");
    gr_DELPHILimit->Draw("lsame");
    gr_trilepLimit->Draw("lsame");
  }
  if(DrawObserved) gr_13TeV_obs_SandT->Draw("lsame");

  lg_SandT->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");
  latex_title.SetTextSize(0.04);
  latex_title.SetLineWidth(2);
  latex_title.DrawLatex(0.20, 0.90, "#font[41]{95% CL upper limit}");

  c_SandT->SetLogx();
  c_SandT->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx_SandT.pdf");
  c_SandT->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_logx_SandT.png");

  c_SandT->Close();


  //==== Ratio 8 TeV vs 13 TeV
  //==== TGraph *gr_13TeV_exp = new TGraph(n_central,mass,limit);
  //==== TGraph *gr_8TeV_exp = new TGraph(nm, mass_8TeV, exp_8TeV);

  vector<double> vec_mass_8and13, vec_limit_8and13ratio;
  for(int i=0; i<n_central; i++){
    for(int j=0; j<nm; j++){
      if(mass[i]==mass_8TeV[j]){
        vec_mass_8and13.push_back(mass[i]);
        vec_limit_8and13ratio.push_back(exp_8TeV[j]/limit[i]);
        cout << i << "\t" << mass[i] << "\t" << exp_8TeV[j] << "\t" << limit[i] << endl;
      }
    }
  }

  vector<double> additional = {350, 400, 500};
  for(int a=0; a<additional.size(); a++){

    for(int i=0; i<n_SandT; i++){

      if(additional.at(a)!=mass_SandT[i]) continue;

      for(int j=0; j<nm; j++){
        if(mass_SandT[i]==mass_8TeV[j]){
          vec_mass_8and13.push_back(mass_SandT[i]);
          vec_limit_8and13ratio.push_back(exp_8TeV[j]/limit_SandT[i]);
          cout << i << "\t" << mass_SandT[i] << "\t" << exp_8TeV[j] << "\t" << limit_SandT[i] << " => " << exp_8TeV[j]/limit_SandT[i] << endl;
        }
      }
    }

  }

  const int n_vec_mass_8and13 = vec_mass_8and13.size();
  double mass_8and13[n_vec_mass_8and13];
  double limit_8and13ratio[n_vec_mass_8and13];
  for(int i=0; i<n_vec_mass_8and13; i++){
    mass_8and13[i] = vec_mass_8and13.at(i);
    limit_8and13ratio[i] = vec_limit_8and13ratio.at(i);
  }

  TGraph *gr_8and13ratio = new TGraph(n_vec_mass_8and13, mass_8and13, limit_8and13ratio);
  TCanvas *c_8and13ratio = new TCanvas("c_8and13ratio", "", 800, 800);
  canvas_margin(c_8and13ratio);
  c_8and13ratio->cd();

  dummy->Draw("hist");
  hist_axis(dummy);
  TString this_channel = "";
  if(channel=="ElEl") this_channel = "|V_{eN}|^{2}";
  if(channel=="MuMu") this_channel = "|V_{#muN}|^{2}";
  if(channel=="MuEl") this_channel = "|V_{eN}V_{#muN}^{*}|/(|V_{eN}|^{2}+|V_{#muN}|^{2})";
  TLatex latexch;
  latexch.SetNDC();
  latexch.SetTextSize(0.03);
  latexch.DrawLatex(0.3, 0.85, "#splitline{Expected 8 TeV / Expected 13 TeV}{in "+this_channel+"}");

  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);
  g1->SetLineStyle(3);
  g1->SetLineWidth(3);
  g1->Draw("lsame");

  double x_2[2], y_2[2];
  x_2[0] = 5000;  y_2[0] = sqrt(35900./19700.);
  x_2[1] = -5000;  y_2[1] = sqrt(35900./19700.);
  TGraph *g2 = new TGraph(2, x_2, y_2);
  g2->SetLineWidth(3);
  g2->Draw("lsame");

  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetXaxis()->SetRangeUser(20., 600);
  dummy->GetYaxis()->SetRangeUser(0., 20.);
  dummy->SetTitle("");
  dummy->GetYaxis()->SetTitle("");
  gr_8and13ratio->SetLineColor(kRed);
  gr_8and13ratio->SetLineWidth(3);
  gr_8and13ratio->Draw("lsame");

  TLegend *lg_8and13ratio = new TLegend(0.25, 0.4, 0.7, 0.6);
  lg_8and13ratio->SetBorderSize(0);
  lg_8and13ratio->SetFillStyle(0);
  lg_8and13ratio->AddEntry(gr_8and13ratio, "Expected Limit Ratio", "l");
  lg_8and13ratio->AddEntry(g2, "y=#sqrt{L_{13TeV}/L_{8TeV}}", "l");
  lg_8and13ratio->AddEntry(g1, "y=1", "l");
  lg_8and13ratio->Draw();

  latex_CMSPriliminary.SetTextSize(0.035);
  latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
  latex_Lumi.SetTextSize(0.035);
  latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

  c_8and13ratio->SetLogx();
  c_8and13ratio->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_ratio.pdf");
  c_8and13ratio->SaveAs(plotpath+"/"+channel+"_13TeV_mixing_ratio.png");
  c_8and13ratio->Close();
  


}
