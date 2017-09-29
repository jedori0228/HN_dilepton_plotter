#include "canvas_margin.h"
#include "mylib.h"

void Draw_MCClosure(){

  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = kError;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/MCClosure/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/MCClosure/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<TString> channels = {
    "DiElectron", "DiMuon", "EMu",
  };

  vector<TString> regions = {
    "Preselection",
    "alljets",
    "0jets",
    "1jets",
  };
  TString region = "Preselection_SS";

  vector<TString> samples = {
    "TT_powheg", "DYJets", "DYJets_positive", "WJets", "WJets_positive",
    //"TT_powheg", "DYJets_positive", "WJets_positive",
    //"DYJets", "DYJets_positive",
    //"WJets", "WJets_positive",
    //"TT_powheg",
    //"DYJets_MG", "DYJets", "DYJets_positive",
    //"WJets_MG", "WJets", "WJets_positive",
  };

  vector<TString> vars = {
    "leadingLepton_Pt", "secondLepton_Pt", "Nevents", "Nbjets_nolepveto", "PFMET", "Njets", "secondJet_Pt", "leadingLepton_Type", "secondLepton_Type", "secondLepton_Eta", "leadingLepton_Eta", "secondLepton_mva", "secondLepton_RelIso", "weight_fr", "NLooseNotTight_weight1", "secondLepton_Pt_cone",
  };
  vector<TString> xtitle = {
    "Leading Lepton p_{T} [GeV]", "Sub-Leading Lepton p_{T} [GeV]", "onebin", "# of b-jets", "E_{T}^{miss} [GeV]", "# of jets", "Leading Jet p_{T} [GeV]", "Leading Lepton Type", "Sub-Leading Lepton Type", "Sub-Leading Lepton #eta", "Leading Lepton #eta", "Sub-Leading Lepton MVA", "Sub-Leading Lepton RelIso", "FR weight", "# of Loose no Tight", "Sub-Leading Lepton p_{T}^{cone} [GeV]",
  };
  vector<double> ymaxs = {
    50, 100, 400, 100, 50, 50, 50, 50, 50, 300, 300, 300, 300, 300, 300, 300,
  };
  vector<int> rebins = {
    5, 10, 1, 1, 10, 1, 10, 1, 1, 5, 5, 5, 1, 1, 1, 5,
  };

  for(unsigned int k=0; k<regions.size(); k++){

    cout << endl;
    cout << "#### "<<regions.at(k)<< "####" << endl;
    cout << endl;

    for(unsigned int i=0; i<samples.size(); i++){

      TString sample = samples.at(i);
      cout << endl;
      cout << "["<<sample<<"]" << endl;

      TFile *file_Measured = new TFile(filepath+"Measured/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_v8-0-7.root");
      TFile *file_Predicted = new TFile(filepath+"Predicted/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_v8-0-7.root");

      TString ChargeSign = "SS";
      if(sample.Contains("WJets")) ChargeSign = "AllCharge";

      region = regions.at(k)+"_"+ChargeSign;

      for(unsigned int j=0; j<vars.size(); j++){

        TString var = vars.at(j);

        for(unsigned int l=0; l<channels.size(); l++){

          TString channel = channels.at(l);

          TString dirname = channel+"_"+region;
          TString histname = var+"_"+channel+"_"+region;

          //cout << histname << endl;
          TH1D *hist_Measured = (TH1D*)file_Measured->Get(dirname+"/"+histname);
          TH1D *hist_Predicted = (TH1D*)file_Predicted->Get(dirname+"/"+histname);
          TH1D *hist_Predicted_up = (TH1D*)file_Predicted->Get(dirname+"_up/"+histname+"_up");
          TH1D *hist_Predicted_down = (TH1D*)file_Predicted->Get(dirname+"_down/"+histname+"_down");

          if(!hist_Measured || !hist_Predicted) continue;


          if(hist_Predicted_up){
            for(int a=1; a<=hist_Predicted->GetXaxis()->GetNbins(); a++){
              double err_sumw2 = hist_Predicted->GetBinError(a);
              double err_propagated = hist_Predicted_up->GetBinContent(a)-hist_Predicted->GetBinContent(a);
              double newerr = sqrt(err_sumw2*err_sumw2+err_propagated*err_propagated);
              hist_Predicted->SetBinError(a, newerr);
            }
          }

          if(var=="Nevents"){

            cout << "["<<sample<<"]" << endl;
            cout << "Region : " << region << endl;
            cout << "Channel : " << channel << endl;
            cout << "Measured = " << hist_Measured->GetBinContent(1) << " +- " << hist_Measured->GetBinError(1) << " ("<<hist_Measured->GetEntries() << ")" << endl;
            cout << "Predicted = " << hist_Predicted->GetBinContent(1) << " +- " << hist_Predicted->GetBinError(1) << " ("<<hist_Predicted->GetEntries() << ")" << endl;
            cout << "=> (Measured-Predicted)/Predicted = " << std::fixed<<std::setprecision(1) << 100.*(hist_Measured->GetBinContent(1)-hist_Predicted->GetBinContent(1))/hist_Predicted->GetBinContent(1) << endl;
            TH1D *temp_measured = (TH1D*)hist_Measured->Clone();
            temp_measured->Divide(hist_Predicted);
            cout << "=> Measured/Predicted = " << temp_measured->GetBinContent(1) << " +- " << temp_measured->GetBinError(1) << endl;
            double SystExtra = 0.;
            double Deviation = fabs(1.-temp_measured->GetBinContent(1));
            double StatError = temp_measured->GetBinError(1);
            if(Deviation>StatError){
              SystExtra = sqrt(Deviation*Deviation-StatError*StatError);
            }
            cout << "=> Systematic Extra = " << std::fixed<<std::setprecision(1)<<100.*SystExtra << endl;

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
          if(var.Contains("weight_fr")) hist_Predicted->GetXaxis()->SetRangeUser(-0.2, 0.2);

          
          //double hist_ymax = max( hist_Measured->GetMaximum(), hist_Predicted->GetMaximum() );
          double hist_ymax = max( GetMaximum(hist_Measured), GetMaximum(hist_Predicted) );
          hist_Predicted->GetYaxis()->SetRangeUser(0., hist_ymax*1.5);

          TLegend *lg = new TLegend(0.7, 0.7, 0.93, 0.93);
          lg->SetFillStyle(0);
          lg->SetBorderSize(0);

          lg->AddEntry(hist_Predicted, "Predicted", "l");
          lg->AddEntry(hist_Measured, "Measured", "p");
          lg->Draw();

          hist_Predicted->GetXaxis()->SetTitle(xtitle.at(j));
          hist_Predicted->GetYaxis()->SetTitle("Events");

          gSystem->mkdir(plotpath+"/"+channel+"/"+region, kTRUE);
          c1->SaveAs(plotpath+"/"+channel+"/"+region+"/"+sample+"_"+var+".pdf");
          c1->Close();

        }

      }


    }
  }






}
















