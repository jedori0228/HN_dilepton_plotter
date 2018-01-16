#include "canvas_margin.h"
#include "mylib.h"

TString DoubleToString(double a);

void Draw_FakeRate_Muon(){

  TString Sample = "QCD";
  TString Lepton = "Muon";

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/FakeRateRootfiles/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/FakeRateRootfiles/"+Lepton+"_"+Sample+"/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TFile *file = new TFile(filepath+"LQOUT_"+Lepton+"_"+Sample+".root");

  vector<TString> triggers = {"HLT_Mu3_PFJet40_v", "HLT_Mu8_TrkIsoVVL_v" ,"HLT_Mu17_TrkIsoVVL_v"};
  vector<double> ptinit = {5., 10., 20.};
  vector<Color_t> colors = {kRed, kBlack, kBlue};

  vector<double> vec_pt_bins = {5., 10., 15., 20., 30., 40., 50., 60., 70.};
  if(Sample.Contains("QCD")) vec_pt_bins = {5., 10., 15., 20., 25., 30., 40., 50., 60., 70.};

  const int N_pt_out = vec_pt_bins.size()-1;
  float ptarray[N_pt_out+1];
  for(int i=0; i<N_pt_out+1; i++) ptarray[i] = vec_pt_bins.at(i);// = {5., 10., 15., 20., 25., 30., 40., 50., 60., 70.};
  float etaarray[4] = {0., 0.8, 1.479, 2.5};

  TFile *outroot = new TFile(plotpath+Lepton+"_"+Sample+"_FR.root", "RECREATE");
  TH1D *dummy = new TH1D("dummy", "", N_pt_out, ptarray);

  vector<TString> jetpt = {"20", "30", "40", "60"};
  if(!Sample.Contains("Data") || Sample.Contains("HighdXY")){
    jetpt.clear();
    jetpt = {"40"};
  }
  TString bjetconfig[5] = {"", "_withbjet_Medium", "_withoutbjet_Medium", "_withbjet_Loose", "_withoutbjet_Loose"};

  //==== AwayJet Pt Loop
  for(int a=0; a<jetpt.size(); a++){

    //==== bjet config loop
    for(int b=0; b<5; b++){

      //======================
      //==== Fake Rate plots
      //======================

      TCanvas *c_alleta = new TCanvas("c_alleta", "", 800, 800);
      canvas_margin(c_alleta);
      c_alleta->cd();
      TH1D *dummy_merged = new TH1D("dummy_merged", "", N_pt_out, ptarray);
      hist_axis(dummy_merged);
      dummy_merged->Draw("hist");
      dummy_merged->GetYaxis()->SetRangeUser(0., 0.25);
      dummy_merged->GetYaxis()->SetTitle("Fake Rate");
      dummy_merged->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");
      dummy_merged->GetXaxis()->SetRangeUser(10., 60.);
      //==== Eta Regions
      TLegend *lg2 = new TLegend(0.5, 0.6, 0.93, 0.93);
      lg2->SetFillStyle(0);
      lg2->SetBorderSize(0);

      TH2D *histout = new TH2D(Lepton+"_"+Sample+"_FR_Awayjet"+jetpt.at(a)+bjetconfig[b], "", N_pt_out, ptarray, 3, etaarray);

      TString histname = "Single"+Lepton+"Trigger_Dijet_Awayjet_"+jetpt.at(a)+bjetconfig[b]+"_events_pt_cone_vs_eta";
      if(Sample.Contains("HighdXY")) histname = "Single"+Lepton+"Trigger_HighdXY_events_pt_cone_vs_eta";

      TH2D *hist_FR2D_F0 = (TH2D *)file->Get(histname+"_F0");
      TH2D *hist_FR2D_F = (TH2D *)file->Get(histname+"_F");
      hist_FR2D_F->Divide(hist_FR2D_F0);

      //==== Eta Loop
      for(int j=0; j<3; j++){
        TCanvas *c1 = new TCanvas("c1", "", 800, 800);
        canvas_margin(c1);
        c1->cd();
        hist_axis(dummy);
        dummy->Draw("hist");
        dummy->GetYaxis()->SetRangeUser(0., 0.25);
        dummy->GetYaxis()->SetTitle("Fake Rate");
        dummy->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");

        TH1D *merge = new TH1D("merge", "", N_pt_out, ptarray);

        //==== Trigger
        TLegend *lg = new TLegend(0.5, 0.5, 0.93, 0.93);
        lg->SetFillStyle(0);
        lg->SetBorderSize(0);

        for(unsigned int i=0; i<triggers.size(); i++){

          TString trigger = triggers.at(i);

          TString histname_trigger = trigger+"_Single"+Lepton+"Trigger_Dijet_Awayjet_"+jetpt.at(a)+bjetconfig[b]+"_events_pt_cone_vs_eta";
          if(Sample.Contains("HighdXY")) histname_trigger = trigger+"_Single"+Lepton+"Trigger_HighdXY_events_pt_cone_vs_eta";

          TH2D *hist2d_F0 = (TH2D*)file->Get(histname_trigger+"_F0");
          TH2D *hist2d_F = (TH2D*)file->Get(histname_trigger+"_F");

          TH1D *hist_F0 = new TH1D("hist_F0", "", N_pt_out, ptarray);
          TH1D *hist_F = new TH1D("hist_F", "", N_pt_out, ptarray);
          for(int k=1; k<=N_pt_out; k++){
            hist_F0->SetBinContent(k, hist2d_F0->GetBinContent(k, j+1));
            hist_F0->SetBinError(k, hist2d_F0->GetBinError(k, j+1));
            hist_F->SetBinContent(k, hist2d_F->GetBinContent(k, j+1));
            hist_F->SetBinError(k, hist2d_F->GetBinError(k, j+1));
          }

          hist_F->Divide(hist_F0);
          for(int k=1; k<=N_pt_out; k++){
            if( hist_F->GetXaxis()->GetBinUpEdge(k)-0.1 < ptinit.at(i) ){
              //hist_F->SetBinContent(k, 0.);
              //hist_F->SetBinError(k, 0.);
            }
          }

          //====            1    2    3    4    5    6    7   8    9
          //==== hist_F : 5., 10., 15., 20., 25., 30., 40., 50., 60., 70.
          //==== merge :  5., 10., 15., 20., 25., 30., 40., 50., 60., 70.
          //==== i=0 (mu3)  -> 5-10, 10-15
          //==== i=1 (mu8)  -> 15-20, 20-25, 25-30
          //==== i=2 (mu17) -> 30~

          if(i==0){

            for(int k=1; k<=2; k++){
              histout->SetBinContent(k, j+1, hist_F->GetBinContent(k));
              histout->SetBinError(k, j+1, hist_F->GetBinError(k));

              merge->SetBinContent(k, hist_F->GetBinContent(k));
              merge->SetBinError(k, hist_F->GetBinError(k));
            }

          }
          if(i==1){
            int this_end = 4;
            if(Sample.Contains("QCD")) this_end = 5;
            for(int k=3; k<=this_end; k++){
              histout->SetBinContent(k, j+1, hist_F->GetBinContent(k));
              histout->SetBinError(k, j+1, hist_F->GetBinError(k));

              merge->SetBinContent(k, hist_F->GetBinContent(k));
              merge->SetBinError(k, hist_F->GetBinError(k));
            }

          }
          if(i==2){
            int this_start = 5;
            if(Sample.Contains("QCD")) this_start = 6;
            for(int k=this_start; k<=N_pt_out; k++){
              histout->SetBinContent(k, j+1, hist_F->GetBinContent(k));
              histout->SetBinError(k, j+1, hist_F->GetBinError(k));

              merge->SetBinContent(k, hist_F->GetBinContent(k));
              merge->SetBinError(k, hist_F->GetBinError(k));
            }

          }

          TGraphAsymmErrors *gr = hist_to_graph(hist_F);
          gr->SetLineColor(colors.at(i));
          gr->SetLineWidth(3);
          gr->Draw("pesame");

          lg->AddEntry(gr, trigger, "l");
        }

        lg->Draw();
        c1->SaveAs(plotpath+Lepton+"_"+jetpt.at(a)+bjetconfig[b]+"_"+Sample+"_Eta_bin"+TString::Itoa(j,10)+".pdf");
        c1->SaveAs(plotpath+Lepton+"_"+jetpt.at(a)+bjetconfig[b]+"_"+Sample+"_Eta_bin"+TString::Itoa(j,10)+".png");
        c1->Close();
        delete c1;

        c_alleta->cd();
        if(j==0) dummy->Draw("histsame");
        TGraphAsymmErrors *gr_merge = hist_to_graph(merge,1, 3, j);
        gr_merge->SetLineColor(colors.at(j));
        gr_merge->SetLineWidth(3);
        gr_merge->Draw("pesame");

        TString alias = DoubleToString(etaarray[j])+" < |#eta| < "+DoubleToString(etaarray[j+1]);
        lg2->AddEntry(gr_merge, alias, "l");

      } // END Eta Loop

      outroot->cd();

      hist_FR2D_F->SetName( histout->GetName() );

      TString newname = TString(histout->GetName())+"_jskim";
      histout->SetName( newname );

      histout->Write();
      hist_FR2D_F->Write();

      c_alleta->cd();
      lg2->Draw();
      c_alleta->SaveAs(plotpath+Lepton+"_"+jetpt.at(a)+bjetconfig[b]+"_"+Sample+"_alleta.pdf");
      c_alleta->SaveAs(plotpath+Lepton+"_"+jetpt.at(a)+bjetconfig[b]+"_"+Sample+"_alleta.png");
      c_alleta->Close();

      //==== Inclusive Eta

      TH2D *hist2_FR2D_F0 = (TH2D *)file->Get(histname+"_F0");
      TH2D *hist2_FR2D_F = (TH2D *)file->Get(histname+"_F");

      TH1D *FR_InclusvieEta = new TH1D("", "", N_pt_out, ptarray);
      TString newname2 = TString(hist_FR2D_F->GetName())+"_InclusiveEta";
      FR_InclusvieEta->SetName(newname2);

      for(int ix=1; ix<=hist2_FR2D_F->GetXaxis()->GetNbins(); ix++){
        double den = 0., num = 0.;
        for(int iy=1; iy<=hist2_FR2D_F->GetYaxis()->GetNbins(); iy++){
          den += hist2_FR2D_F0->GetBinContent(ix, iy);
          num += hist2_FR2D_F->GetBinContent(ix, iy);
        }
        double this_fr = 0.;
        if(den!=0) this_fr = num/den;
        FR_InclusvieEta->SetBinContent(ix, this_fr);
      }
      FR_InclusvieEta->Write();

    } // END b-jet config loop

  } // END Awayjet pt loop


  outroot->Close();

}




TString DoubleToString(double a){

  if(a==0) return "0";

  int Digit1 = int(a);
  int Digit0p1 = 10*a-10*Digit1;

  return TString::Itoa(Digit1,10)+"."+TString::Itoa(Digit0p1,10);

}
