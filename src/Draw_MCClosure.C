#include "canvas_margin.h"

void Draw_MCClosure(){

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString channel = "DiMuon";

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/MCClosure/"+channel+"/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/MCClosure/"+channel+"/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<TString> regions = {
    "Preselection_SS",
    "Preselection_AllCharge",
    "0nlbjets_SS",
  };
  TString region = "Preselection_SS";

  vector<TString> samples = {
    "TT_powheg", "WJets", "DYJets", "WJets_MG", "DYtoEE", "DYJets_MG",
  };

  vector<TString> vars = {
    "leadingLepton_Pt", "secondLepton_Pt", "Nevents", "Nbjets_nolepveto", "PFMET", "Njets", "secondJet_Pt",
  };
  vector<TString> xtitle = {
    "Leading Lepton p_{T} [GeV]", "Sub-Leading Lepton p_{T} [GeV]", "onebin", "# of b-jets", "E_{T}^{miss} [GeV]", "# of jets", "Leading Jet p_{T} [GeV]", 
  };
  vector<double> ymaxs = {
    50, 100, 400, 100, 50, 50, 50,
  };
  vector<int> rebins = {
    5, 5, 1, 1, 10, 1, 10
  };

  for(unsigned int i=0; i<samples.size(); i++){

    TString sample = samples.at(i);
    //cout << sample << endl;

    TFile *file_Measured = new TFile(filepath+"Measured/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_v8-0-7.root");
    TFile *file_Predicted = new TFile(filepath+"Predicted/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_v8-0-7.root");

    for(unsigned int k=0; k<regions.size(); k++){

      TString region = regions.at(k);

      for(unsigned int j=0; j<vars.size(); j++){

        TString var = vars.at(j);
        TString histname = var+"_"+channel+"_"+region;

        //cout << histname << endl;
        TH1D *hist_Measured = (TH1D*)file_Measured->Get(histname);
        TH1D *hist_Predicted = (TH1D*)file_Predicted->Get(histname);
        TH1D *hist_Predicted_up = (TH1D*)file_Predicted->Get(histname+"_up");

        if(!hist_Measured || !hist_Predicted) continue;

        for(int a=1; a<=hist_Predicted->GetXaxis()->GetNbins(); a++){
          double err_sumw2 = hist_Predicted->GetBinError(a);
          double err_propagated = hist_Predicted_up->GetBinContent(a)-hist_Predicted->GetBinContent(a);
          double newerr = sqrt(err_sumw2*err_sumw2+err_propagated*err_propagated);
          hist_Predicted->SetBinError(a, newerr);
        }

        if(var=="Nevents"){
          cout << "["<<sample<<"]" << endl;
          cout << "Region : " << region << endl;
          cout << "Measured = " << hist_Measured->GetBinContent(1) << " +- " << hist_Measured->GetBinError(1) << " ("<<hist_Measured->GetEntries() << ")" << endl;
          cout << "Predicted = " << hist_Predicted->GetBinContent(1) << " +- " << hist_Predicted->GetBinError(1) << " ("<<hist_Predicted->GetEntries() << ")" << endl;
          cout << "=> (Measured-Predicted)/Predicted = " << (hist_Measured->GetBinContent(1)-hist_Predicted->GetBinContent(1))/hist_Predicted->GetBinContent(1) << endl;
        }

        hist_Measured->Rebin(rebins.at(j));
        hist_Predicted->Rebin(rebins.at(j));

        TCanvas *c1 = new TCanvas("c1", "", 800, 800);
        canvas_margin(c1);
        c1->Draw();

        hist_Measured->SetLineColor(kBlack);
        hist_Measured->SetMarkerColor(kBlack);
        hist_Measured->SetMarkerStyle(2);
        hist_Measured->SetMarkerSize(2);

        hist_Predicted->SetLineColor(kRed);
        hist_Predicted->SetLineWidth(3);

        hist_Predicted->Draw("histsamee1");
        hist_Measured->Draw("psamee1");

        hist_axis(hist_Predicted);
        if(var.Contains("Pt")) hist_Predicted->GetXaxis()->SetRangeUser(0, 200);
        if(var.Contains("PFMET")) hist_Predicted->GetXaxis()->SetRangeUser(0, 200);

        double hist_ymax = max( hist_Measured->GetMaximum(), hist_Predicted->GetMaximum() );
        hist_Predicted->GetYaxis()->SetRangeUser(0., hist_ymax*1.5);

        TLegend *lg = new TLegend(0.7, 0.7, 0.93, 0.93);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);

        lg->AddEntry(hist_Predicted, "Predicted", "l");
        lg->AddEntry(hist_Measured, "Measured", "p");
        lg->Draw();

        hist_Predicted->GetXaxis()->SetTitle(xtitle.at(j));
        hist_Predicted->GetYaxis()->SetTitle("Events");

        c1->SaveAs(plotpath+"/"+channel+"_"+region+"_"+sample+"_"+var+".pdf");
        c1->Close();

      }


    }
  }






}
