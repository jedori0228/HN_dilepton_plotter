#include "canvas_margin.h"
#include "mylib.h"

TString DoubleToString(double a);

void Draw_FakeRate_Electron(){

  TString Sample = "Data";
  TString Lepton = "Electron";

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/FakeRateRootfiles/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/FakeRateRootfiles/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TFile *file = new TFile(filepath+"LQOUT_"+Lepton+"_"+Sample+".root");

  vector<TString> triggers = {"HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v", "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v" ,"HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v", "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v"};
  vector<double> ptinit = {10., 15., 20., 25.};
  vector<Color_t> colors = {kRed, kBlack, kBlue, kGreen};

  TLegend *lg = new TLegend(0.5, 0.5, 0.93, 0.93);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);

  float ptarray[8] = {10., 15., 20., 30., 40., 50., 60., 70.};
  float etaarray[4] = {0., 0.8, 1.479, 2.5};
  Double_t xbins[9] = {0., 10., 15., 20., 30., 40., 50., 60., 70.};

  TFile *outroot = new TFile(plotpath+Lepton+"_"+Sample+"_FR.root", "RECREATE");
  TH1D *dummy = new TH1D("dummy", "", 14, 0., 70.);

  TString jetpt[4] = {"20", "30", "40", "60"};

  for(int a=0; a<4; a++){

    TCanvas *c_all = new TCanvas("c_all", "", 800, 800);
    canvas_margin(c_all);
    c_all->cd();
    TH1D *dummy2 = new TH1D("dummy2", "", 7, ptarray);
    hist_axis(dummy2);
    dummy2->Draw("hist");
    dummy2->GetYaxis()->SetRangeUser(0., 0.40);
    dummy2->GetYaxis()->SetTitle("Fake Rate");
    dummy2->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");
    TLegend *lg2 = new TLegend(0.5, 0.5, 0.93, 0.93);
    lg2->SetFillStyle(0);
    lg2->SetBorderSize(0);

    TH2D *histout = new TH2D(Lepton+"_"+Sample+"_FR_Awayjet"+jetpt[a], "", 7, ptarray, 3, etaarray);

    //==== Eta Loop
    for(int j=0; j<3; j++){
      TCanvas *c1 = new TCanvas("c1", "", 800, 800);
      canvas_margin(c1);
      c1->cd();
      hist_axis(dummy);
      dummy->Draw("hist");
      dummy->GetYaxis()->SetRangeUser(0., 0.60);
      dummy->GetYaxis()->SetTitle("Fake Rate");
      dummy->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");

      TH1D *merge = new TH1D("merge", "", 7, ptarray);

      for(unsigned int i=0; i<triggers.size(); i++){

        TString trigger = triggers.at(i);
        TH2D *hist2d_F0 = (TH2D*)file->Get(trigger+"_Single"+Lepton+"Trigger_Dijet_Awayjet_"+jetpt[a]+"_events_pt_cone_vs_eta_F0");
        TH2D *hist2d_F = (TH2D*)file->Get(trigger+"_Single"+Lepton+"Trigger_Dijet_Awayjet_"+jetpt[a]+"_events_pt_cone_vs_eta_F");

        TH1D *hist_F0 = new TH1D("hist_F0", "", 14, 0., 70.);
        TH1D *hist_F = new TH1D("hist_F", "", 14, 0., 70.);
        for(int k=1; k<=14; k++){
          hist_F0->SetBinContent(k, hist2d_F0->GetBinContent(k, j+1));
          hist_F0->SetBinError(k, hist2d_F0->GetBinError(k, j+1));
          hist_F->SetBinContent(k, hist2d_F->GetBinContent(k, j+1));
          hist_F->SetBinError(k, hist2d_F->GetBinError(k, j+1));
        }

        //==== make them {0., 10., 15., 20., 30., 40., 50., 60., 70.};
        hist_F0 = (TH1D*)hist_F0->Rebin(8, "hnew1",xbins);
        hist_F = (TH1D*)hist_F->Rebin(8, "hnew1",xbins);

        hist_F->Divide(hist_F0);
        for(int k=1; k<=14; k++){
          if( hist_F->GetXaxis()->GetBinUpEdge(k)-0.1 < ptinit.at(i) ){
            //hist_F->SetBinContent(k, 0.);
            //hist_F->SetBinError(k, 0.);
          }
        }

        //====            1    2    3    4    5    6    7    8
        //==== hist_F : 0., 10., 15., 20., 30., 40., 50., 60., 70.
        //====                 1    2    3    4    5    6    7
        //==== merge :      10., 15., 20., 30., 40., 50., 60., 70.
        //==== i=0 (ele8)  -> 10-15, 15-20
        //==== i=1 (ele12) -> 20-30
        //==== i=2 (ele17) -> 30~40 <- trash
        //==== i=3 (ele23) -> 30~

        if(i==0){
          histout->SetBinContent(1, j+1, hist_F->GetBinContent(1+1));
          histout->SetBinError(1, j+1, hist_F->GetBinError(1+1));
          histout->SetBinContent(2, j+1,  hist_F->GetBinContent(2+1));
          histout->SetBinError(2, j+1,  hist_F->GetBinError(2+1));

          merge->SetBinContent(1, hist_F->GetBinContent(1+1));
          merge->SetBinError(1, hist_F->GetBinError(1+1));
          merge->SetBinContent(2, hist_F->GetBinContent(2+1));
          merge->SetBinError(2, hist_F->GetBinError(2+1));
        }
        if(i==1){
          histout->SetBinContent(3, j+1,  hist_F->GetBinContent(3+1));
          histout->SetBinError(3, j+1,  hist_F->GetBinError(3+1));

          merge->SetBinContent(3, hist_F->GetBinContent(3+1));
          merge->SetBinError(3, hist_F->GetBinError(3+1));
        }
        if(i==2){
          histout->SetBinContent(4, j+1,  hist_F->GetBinContent(4+1));
          histout->SetBinError(4, j+1,  hist_F->GetBinError(4+1));

          merge->SetBinContent(4, hist_F->GetBinContent(4+1));
          merge->SetBinError(4, hist_F->GetBinError(4+1));
        }
        if(i==3){
          for(int k=5; k<=7; k++){
            histout->SetBinContent(k, j+1, hist_F->GetBinContent(k+1));
            histout->SetBinError(k, j+1, hist_F->GetBinError(k+1));

            merge->SetBinContent(k, hist_F->GetBinContent(k+1));
            merge->SetBinError(k, hist_F->GetBinError(k+1));
          }
        }

        TGraphAsymmErrors *gr = hist_to_graph(hist_F);
        gr->SetLineColor(colors.at(i));
        gr->SetLineWidth(3);
        gr->Draw("lpsame");

        if(j==0){
          lg->AddEntry(gr, trigger, "l");
        }
      }

      lg->Draw();
      c1->SaveAs(plotpath+Lepton+"_"+jetpt[a]+"_"+Sample+"_Eta_bin"+TString::Itoa(j,10)+".pdf");
      c1->Close();
      delete c1;

      c_all->cd();
      if(j==0) dummy->Draw("histsame");
      TGraphAsymmErrors *gr_merge = hist_to_graph(merge);
      gr_merge->SetLineColor(colors.at(j));
      gr_merge->SetLineWidth(3);
      gr_merge->Draw("lsame");

      TString alias = DoubleToString(etaarray[j])+" < |#eta| < "+DoubleToString(etaarray[j+1]);
      lg2->AddEntry(gr_merge, alias, "l");

    } // END Eta Loop

    outroot->cd();
    histout->Write();

    c_all->cd();
    lg2->Draw();
    c_all->SaveAs(plotpath+Lepton+"_"+jetpt[a]+"_"+Sample+"_alleta.pdf");
    c_all->Close();

  }


  outroot->Close();

}




TString DoubleToString(double a){

  if(a==0) return "0";

  int Digit1 = int(a);
  int Digit0p1 = 10*a-10*Digit1;

  return TString::Itoa(Digit1,10)+"."+TString::Itoa(Digit0p1,10);

}
