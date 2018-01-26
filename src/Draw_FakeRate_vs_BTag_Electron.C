#include "canvas_margin.h"
#include "mylib.h"

TString DoubleToString(double a);

void Draw_FakeRate_vs_BTag_Electron(){

  TString Sample = "Data_v7_5";
  TString Lepton = "Electron";

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/FakeRateRootfiles/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/FakeRateVSBTag/"+Lepton+"_"+Sample+"/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TFile *file = new TFile(filepath+"LQOUT_"+Lepton+"_"+Sample+".root");

  const int N_pt_out = 9;
  float ptarray[N_pt_out+1] = {10., 15., 20., 23., 30., 35., 40., 50., 60., 70.};
  float etaarray[4] = {0., 0.8, 1.479, 2.5};

  TH1D *dummy = new TH1D("dummy", "", N_pt_out, ptarray);

  vector<TString> bjetconfigs = {"", "_withbjet_Medium", "_withoutbjet_Medium"};
  vector<TString> bjetconfigsForLatex = {"Inclusive", "With b-jet", "Without b-jet"};
  vector<Color_t> colors = {kBlack, kRed, kBlue};

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
    dummy->GetXaxis()->SetRangeUser(10., 60.);
    dummy->GetYaxis()->SetRangeUser(0., 0.6);

    TLegend *lg = new TLegend(0.5, 0.7, 0.93, 0.93);
    lg->SetBorderSize(0);
    lg->SetFillStyle(0);

    //==== bjet config loop
    for(int b=0; b<bjetconfigs.size(); b++){

      TString histname = "Single"+Lepton+"Trigger_Dijet_Awayjet_40"+bjetconfigs.at(b)+"_events_pt_cone_vs_eta";

      TH2D *hist_FR2D_F0 = (TH2D *)file->Get(histname+"_F0");
      TH2D *hist_FR2D_F = (TH2D *)file->Get(histname+"_F");
      hist_FR2D_F->Divide(hist_FR2D_F0);

      TH1D *hist_FR1D = (TH1D *)dummy->Clone();
      for(int ix=1; ix<=N_pt_out; ix++){
        hist_FR1D->SetBinContent(ix, hist_FR2D_F->GetBinContent(ix, j+1));
        hist_FR1D->SetBinError(ix, 0.);
      }

      TGraphAsymmErrors *gr = hist_to_graph(hist_FR1D);
      gr->SetLineColor(colors.at(b));
      gr->SetLineWidth(3);
      gr->Draw("pesame");

      lg->AddEntry(gr, bjetconfigsForLatex.at(b), "l");

    } // END b-jet config loop

    TString etaregions = DoubleToString(etaarray[j])+" < |#eta| < "+DoubleToString(etaarray[j+1]);

    lg->Draw();
    c1->SaveAs(plotpath+"/Eta_bin"+TString::Itoa(j,10)+".pdf");
    c1->Close();

  } // END Eta Loop



}




TString DoubleToString(double a){

  if(a==0) return "0";

  int Digit1 = int(a);
  int Digit0p1 = 10*a-10*Digit1;

  return TString::Itoa(Digit1,10)+"."+TString::Itoa(Digit0p1,10);

}
