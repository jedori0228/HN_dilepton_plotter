#include "canvas_margin.h"
#include "mylib.h"

void Draw_SignalDistribution(){

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Regions/Signal/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalDistribution/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //===============
  //==== Low Mass
  //===============


  vector<int> masses = {40, 50, 60, 70, 80};
  vector<Color_t> colors = {kRed, kOrange, kGreen, kBlue, kViolet};
  vector<TString> channels = {"MuMu", "ElEl", "MuEl"};
  vector<TString> channelsForLatex = {"#mu#mu", "ee", "#mue"};

  vector<TString> regions = {"Preselection"};
  vector<TString> vars = {
    "m_jj_lljjWclosest", "m_lljj_lljjWclosest", "m_Leadljj_lljjWclosest", "m_SubLeadljj_lljjWclosest",
    "m_Leadlj", "m_SubLeadlj", "m_llj",
    "leadingLepton_Pt", "secondLepton_Pt",
    "PFMET", "m_ll", "DeltaRl1l2"
  };
  vector<TString> xtitles = {
    "m(jj_{W}) (GeV)",  "m(lljj_{W}) (GeV)", "m(Leading Lepton+jj_{W}) (GeV)", "m(Subleading Lepton+jj_{W}) (GeV)",
    "m(Leading Lepton+j) (GeV)", "m(Subleading Lepton+j) (GeV)", "m(llj) (GeV)",
    "Leading Lepton p_{T} (GeV)", "Subleading Lepton p_{T} (GeV)",
    "#slash{E}_{T}^{miss} (GeV)", "m(ll) (GeV)", "#DeltaR(l_{1},l_{2})",
  };


/*
  //================
  //==== High Mass
  //================


  vector<int> masses = {300, 600, 800, 1000, 1500};
  vector<Color_t> colors = {kRed, kOrange, kGreen, kBlue, kViolet};

  int n_masses_s = masses.size();
  for(int i=0; i<n_masses_s; i++){
    //masses.push_back( -masses.at(i) );
    //colors.push_back( colors.at(i) );
  }

  vector<TString> channels = {"MuMu", "ElEl", "MuEl"};
  vector<TString> channelsForLatex = {"#mu#mu", "ee", "#mue"};

  vector<TString> regions = {"Preselection"};
  vector<TString> vars = {
    "leadingLepton_Pt", "secondLepton_Pt",
    "m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest",
    "leadingLepton_Eta", "secondLepton_Eta",
    "m_jj_jjWclosest", "m_lljj_jjWclosest", "m_Leadljj_jjWclosest", "m_SubLeadljj_jjWclosest",
  };
  vector<TString> xtitles = {
    "Leading Lepton p_{T} (GeV)", "Subleading Lepton p_{T} (GeV)",
    "m(Leading Lepton+Fatjet) (GeV)", "Subleading Lepton+Fatjet (GeV)", "m(ll+Fatjet) (GeV)",
    "Leading Lepton #eta", "Subleading Lepton #eta",
    "m(jj_{W}) (GeV)",  "m(lljj_{W}) (GeV)", "m(Leading Lepton+jj_{W}) (GeV)", "m(Subleading Lepton+jj_{W}) (GeV)",
  };
*/

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    for(unsigned int k=0; k<regions.size(); k++){
      TString region = regions.at(k);

      for(unsigned int l=0; l<vars.size(); l++){

        TCanvas *c1 = new TCanvas("c1", "", 600, 600);
        canvas_margin(c1);
        c1->Draw();
        c1->cd();

        int n_rebin = 50;
        double x_max = 1000.;
        double x_min = 0.;
        if(vars.at(l).Contains("leadingLepton_Pt")) x_max = 2000.;
        if(vars.at(l).Contains("m_")){
          x_max = 2000.;
          n_rebin = 50;
        }
        if(vars.at(l).Contains("Eta")){
          x_max = 3.;
          n_rebin = 3;
        }
        if(vars.at(l)=="m_jj_jjWclosest"){
          x_max = 150.;
        }
        if(vars.at(l).Contains("lljjWclosest")){
          x_max = 500.;
        }
        if(vars.at(l)=="m_Leadlj" || vars.at(l)=="m_SubLeadlj" || vars.at(l)=="m_llj" ){
          x_max = 300.;
        }
        if(vars.at(l) == "m_ll"){
          x_max = 100.;
          n_rebin = 5.;
        }

        if(vars.at(l).Contains("Eta")){
          x_min = -3.;
        }

        TH1D *hist_dummy = new TH1D("hist_dummy", "", int(x_max), x_min, x_max);
        hist_dummy->Draw("hist");
        hist_axis(hist_dummy);
        hist_dummy->GetYaxis()->SetRangeUser(0., 1.1);

        if(vars.at(l).Contains("DeltaR")){
          hist_dummy->GetXaxis()->SetRangeUser(0., 5.0);
          n_rebin = 1;
        }

        hist_dummy->Rebin(n_rebin);
        hist_dummy->GetYaxis()->SetTitle("Events");
        hist_dummy->GetXaxis()->SetTitle(xtitles.at(l));

        TLegend *lg = new TLegend(0.6, 0.5, 0.9, 0.9);
        lg->SetBorderSize(0);
        lg->SetFillStyle(0);

        TLegend *lg2 = new TLegend(0.4, 0.2, 0.7, 0.6);
        lg2->SetBorderSize(0);
        lg2->SetFillStyle(0);

        for(unsigned j=0; j<masses.size(); j++){

          TString mass = TString::Itoa(abs(masses.at(j)),10);

          TString filename = "DiLeptonAnalyzer_SKHN"+channel+"_"+mass+"_cat_v8-0-7.root";
          if(masses.at(j)<0) filename = "DiLeptonAnalyzer_SKHNDilepton_"+channel+"_Tchannel_M"+mass+"_cat_v8-0-7.root";
          TFile *file = new TFile(base_filepath+filename);

          TString PDName = "";
          if(channel=="MuMu") PDName = "DiMuon";
          if(channel=="ElEl") PDName = "DiElectron";
          if(channel=="MuEl") PDName = "EMu";

          TString histname = PDName+"_"+region+"_SS/"+vars.at(l)+"_"+PDName+"_"+region+"_SS";
          TH1D *hist = (TH1D *)file->Get(histname);
          if(!hist) continue;

          hist->Rebin(n_rebin);
          hist->SetLineColor(colors.at(j));
          hist->SetLineWidth(3);
          if(masses.at(j)<0) hist->SetLineStyle(3);
          double y_max = GetMaximum(hist);
          hist->Scale(1./y_max);
          
          hist->Draw("histsame");

          TString alias = "Sch";
          if(masses.at(j)<0) alias = "Tch";
          alias = alias+" HN"+mass;
          lg->AddEntry(hist, alias, "l");
          lg2->AddEntry(hist, alias, "l");

        }

        TLatex latex_CMSPriliminary, latex_Lumi;
        latex_CMSPriliminary.SetNDC();
        latex_Lumi.SetNDC();
        latex_CMSPriliminary.SetTextSize(0.035);
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
        latex_Lumi.SetTextSize(0.035);
        latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

        TString str_channel = channelsForLatex.at(i);
        TLatex channelname;
        channelname.SetNDC();
        channelname.SetTextSize(0.037);
        channelname.DrawLatex(0.2, 0.88, str_channel);


        if(vars.at(l).Contains("secondLepton_Eta")) lg2->Draw();
        else lg->Draw();

        c1->SaveAs(base_plotpath+"/HN"+channel+"_"+region+"_"+vars.at(l)+".pdf");
        c1->Close();

      }


    }


  }

}
