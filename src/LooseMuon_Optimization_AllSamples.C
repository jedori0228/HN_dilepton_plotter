#include "canvas_margin.h"
#include "mylib.h"

void LooseMuon_Optimization_AllSamples(){

  bool DrawPlots = false;

  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = kError;
  TH1::AddDirectory(kFALSE);

  //==== QCD first always
  vector<TString> samples = {"QCD", "WJets", "TT_powheg"};
  vector<Color_t> colors = {kBlack, kBlue, kRed};
  vector<TString> alias = {"QCD", "WJets", "t#bar{t}"};

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_PLOT_PATH+"/"+dataset+"/LooseMuonOptimization/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/LooseMuonOptimization/AllSamples/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  const int n_pt = 7;
  float ptarray[n_pt+1] = {5., 10., 20., 30., 40., 50., 60., 70.};

  double MaxSIP = 3, dMaxSIP = 0.5;
  for(int a=0; a<60; a++){

    double MaxChi2 = 10., dMaxChi2 = 10.;
    for(int b=0; b<15; b++){

      TString SIP_Chi2 = TString::Itoa(MaxSIP*10,10)+"_"+TString::Itoa(MaxChi2,10);
      cout << MaxSIP<<"\t"<<MaxChi2<<" ==> " << SIP_Chi2 << endl;

      TCanvas* c1 = new TCanvas("c1", "", 800, 800);
      c1->Draw();
      TPad *c1_up;
      TPad *c1_down;
      c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
      c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

      canvas_margin(c1, c1_up, c1_down);

      c1_up->Draw();
      c1_down->Draw();
      c1_up->cd();

      TH1D *dummy = new TH1D("dummy", "", n_pt, ptarray);
      dummy->Draw("hist");
      dummy->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");
      dummy->GetXaxis()->SetRangeUser(10., 70.);
      dummy->GetYaxis()->SetRangeUser(0., 0.2);

      TLatex latex;
      latex.SetNDC();
      latex.SetTextSize(0.035);
      //TString SIP_Chi2 = TString::Itoa(MaxSIP*10,10)+"_"+TString::Itoa(MaxChi2,10);
      latex.DrawLatex(0.2, 0.8, SIP_Chi2);

      TLegend *lg = new TLegend(0.7, 0.7, 0.93, 0.93);
      lg->SetBorderSize(0);
      lg->SetFillStyle(0);

      vector<TH1D *> hists;

      for(unsigned int i=0; i<samples.size(); i++){

        TString sample = samples.at(i);

        TFile *file = new TFile(filepath+sample+"/FRs.root");

        TH1D *hist = (TH1D *)file->Get(SIP_Chi2)->Clone(); 
        TString thisname = hist->GetName();
        hist->SetName(thisname+"_"+sample);
        hists.push_back(hist);

        TGraphAsymmErrors *gr = hist_to_graph(hist);

        gr->SetLineColor(colors.at(i));
        gr->SetLineWidth(3);
        gr->Draw("lpsame");

        lg->AddEntry(gr, alias.at(i), "l");

        file->Close();
      }
      lg->Draw();

      c1_down->cd();
      TH1D *dummy_down = new TH1D("dummy_down", "", n_pt, ptarray);
      dummy_down->Draw("hist");
      dummy_down->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");
      dummy_down->GetXaxis()->SetRangeUser(10., 70.);
      dummy_down->GetYaxis()->SetRangeUser(-0.5, 0.5);
      dummy_down->GetYaxis()->SetTitle("Rel. Diff.");
      hist_axis(dummy, dummy_down);

      TH1D *hist_QCD = (TH1D*)hists.at(0)->Clone();
      for(unsigned int i=0; i<hists.size(); i++){
        hists.at(i)->Add(hist_QCD, -1.);
        hists.at(i)->Divide(hist_QCD);
        //cout << hists.at(i)->GetName() << "\t" << hists.at(i)->GetBinContent(2) << endl;
        TGraphAsymmErrors *gr = hist_to_graph(hists.at(i));
        gr->SetLineColor(colors.at(i));
        gr->SetLineWidth(2);
        if(i==0) gr->SetLineWidth(4);
        gr->Draw("psame");
      }
      //==== y=-0.3 line
      double x_0[2], y_0[2];
      x_0[0] = -1000;  y_0[0] = -0.3;
      x_0[1] = 1000;  y_0[1] = -0.3;
      TGraph *g0 = new TGraph(2, x_0, y_0);
      //==== y=+0.3 line
      double x_1[2], y_1[2];
      x_1[0] = 1000;  y_1[0] = +0.3;
      x_1[1] = -1000;  y_1[1] = +0.3;
      TGraph *g1 = new TGraph(2, x_1, y_1);

      g0->Draw("same");
      g1->Draw("same");

      c1->SaveAs(plotpath+SIP_Chi2+".pdf");
      c1->Close();

      MaxChi2 += dMaxChi2;
    }


    MaxSIP += dMaxSIP;
  }


}

























