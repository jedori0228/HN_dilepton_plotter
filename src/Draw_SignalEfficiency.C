#include "canvas_margin.h"

void Draw_SignalEfficiency(){

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Regions/Signal/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalEfficiency/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<int> masses = {40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
  const int n_mass = masses.size();
  TString NMCfilepath = WORKING_DIR+"/data/SignalN_MC.txt";

  vector<TString> channels = {"MuMu", "ElEl", "MuEl"};
  TString region = "Preselection";

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    cout << "["<<channel<<"]" << endl;

    double x[n_mass], y_ak4[n_mass], y_SS[n_mass], y[n_mass];

    for(unsigned int j=0; j<masses.size(); j++){

      x[j] = masses.at(j);

      TString mass = TString::Itoa(masses.at(j),10);

      string elline;
      ifstream in(NMCfilepath);
      int N_MC = -999;
      while(getline(in,elline)){
        std::istringstream is( elline );
        TString samplename;
        is >> samplename;
        is >> N_MC;
        if(samplename=="HN"+channel+"_"+mass){
          break;
        }
      }

      TString filename = "DiLeptonAnalyzer_SKHN"+channel+"_"+mass+"_cat_v8-0-7.root";
      TFile *file = new TFile(base_filepath+filename);

      TString PDName = "";
      if(channel=="MuMu") PDName = "DiMuon";
      if(channel=="ElEl") PDName = "DiElectron";
      if(channel=="MuEl") PDName = "EMu";

      TString histname_ak4 = PDName+"_"+"LegacyTwoJets"+"_SS/Nevents_"+PDName+"_"+"LegacyTwoJets"+"_SS";
      TString histname = PDName+"_"+region+"_SS/Nevents_"+PDName+"_"+region+"_SS";

      TH1D *hist_ak4 = (TH1D *)file->Get(histname_ak4);
      TH1D *hist = (TH1D *)file->Get(histname);
      TH1D *hist_SS = (TH1D *)file->Get(PDName+"_SS/Nevents_"+PDName+"_SS");


      double eff_ak4 = hist_ak4->GetEntries()/N_MC;
      double eff = hist->GetEntries()/N_MC;
      double eff_SS = hist_SS->GetEntries()/N_MC;

/*
      double eff_ak4 = hist_ak4->GetBinContent(1)/N_MC;
      double eff = hist->GetBinContent(1)/N_MC;
      double eff_SS = hist_SS->GetBinContent(1)/N_MC;
*/
      y_ak4[j] = eff_ak4;
      y[j] = eff;
      y_SS[j] = eff_SS;

      cout << mass << "\t" << hist_SS->GetEntries() << "\t" << N_MC << "\t" << y_SS[j] << endl;

    }

    TCanvas *c1 = new TCanvas("c1", "", 600, 600);
    canvas_margin(c1);
    c1->Draw();
    c1->cd();

    TH1D *hist_empty = new TH1D("hist_empty", "", 3000, 1., 3001.);
    hist_axis(hist_empty);
    hist_empty->SetName("DUMMY_FOR_AXIS");
    hist_empty->GetYaxis()->SetTitle("Efficiency");
    hist_empty->SetLineWidth(0);
    hist_empty->SetLineColor(0);
    hist_empty->SetMarkerSize(0);
    hist_empty->SetMarkerColor(0);
    hist_empty->GetYaxis()->SetRangeUser(0., 1.0);
    hist_empty->GetXaxis()->SetRangeUser(20, 3000);
    hist_empty->Draw("histsame");
    hist_empty->GetXaxis()->SetTitle("m_{N} (GeV)");
    c1->SetLogx();

    TGraph *gr_ak4 = new TGraph(n_mass, x, y_ak4);
    TGraph *gr = new TGraph(n_mass, x, y);
    TGraph *gr_SS = new TGraph(n_mass, x, y_SS);

    gr_ak4->SetLineColor(kBlue);
    gr_ak4->SetLineWidth(3);
    gr->SetLineColor(kRed);
    gr->SetLineWidth(3);
    gr_SS->SetLineColor(kBlack);
    gr_SS->SetLineWidth(3);

    TLegend *lg = new TLegend(0.2, 0.65, 0.9, 0.95);
    lg->SetBorderSize(0);
    lg->SetFillStyle(0);

    TString str_SS = "";
    if(channel == "MuMu") str_SS = "SS(#mu#mu)";
    if(channel == "ElEl") str_SS = "SS(ee)";
    if(channel == "MuEl") str_SS = "SS(e#mu)";

    lg->AddEntry(gr_SS, str_SS, "l");
    lg->AddEntry(gr, str_SS+"+(DiJet or Onejet or FatJet)", "l");
    lg->AddEntry(gr_ak4, str_SS+"+(Dijet)", "l");
    lg->Draw();

    gr_SS->Draw("lsame");
    gr_ak4->Draw("lsame");
    gr->Draw("lsame");

    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();
    latex_CMSPriliminary.SetTextSize(0.035);
    latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");


    c1->SaveAs(base_plotpath+channel+".pdf");
    c1->SaveAs(base_plotpath+channel+".png");
    c1->Close();


  }

}
