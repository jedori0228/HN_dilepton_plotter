#include "canvas_margin.h"
#include "mylib.h"

TString DoubleToString(double a);

void Draw_FakeSampleDistribution(){

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
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/FakeRateRootfiles/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  TFile *file = new TFile(filepath+"LQOUT_"+Lepton+"_"+Sample+".root");

  vector<TString> triggers = {"HLT_Mu3_PFJet40_v", "HLT_Mu8_v" ,"HLT_Mu17_v"};
  if(Lepton=="Electron") triggers = {"HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v", "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v" ,"HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v", "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v"};

  vector<TString> vars = {"RelIso", "dXY", "dZ"};
  vector<TString> xtitle = {"RelIso", "dXY [cm]", "dZ [cm]"};

  const int N_pt_out = 5;
  float ptarray[N_pt_out+1] = {10., 20., 30., 40., 50., 60.};
  float etaarray[4] = {0., 0.8, 1.479, 2.5};

  TFile *outroot = new TFile(plotpath+Lepton+"_"+Sample+"_FR.root", "RECREATE");
  TH1D *dummy = new TH1D("dummy", "", 14, 0., 70.);

  TString jetpt[4] = {"20", "30", "40", "60"};
  TString bjetconfig[5] = {"", "_withbjet_Medium", "_withoutbjet_Medium", "_withbjet_Loose", "_withoutbjet_Loose"};

  //==== AwayJet Pt Loop
  for(int a=0; a<4; a++){

    //==== bjet config
    for(int b=0; b<5; b++){

      //==== variables
      for(unsigned int c=0; c<vars.size(); c++){

        for(unsigned int i=0; i<triggers.size(); i++){

        TString var = vars.at(c);

        TCanvas *c_all = new TCanvas("c_all", "", 800, 800);
        canvas_margin(c_all);
        c_all->cd();
        TH1D *dummy2 = new TH1D("dummy2", "", N_pt_out, ptarray);
        hist_axis(dummy2);
        dummy2->Draw("hist");
        dummy2->GetYaxis()->SetRangeUser(0., 0.25);
        dummy2->GetYaxis()->SetTitle("Fake Rate");
        dummy2->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");
        TLegend *lg2 = new TLegend(0.5, 0.5, 0.93, 0.93);
        lg2->SetFillStyle(0);
        lg2->SetBorderSize(0);

        TH2D *histout = new TH2D(Lepton+"_"+Sample+"_FR_Awayjet"+jetpt[a]+bjetconfig[b], "", N_pt_out, ptarray, 3, etaarray);

        TString trigger = triggers.at(i);

        TH1D *hist2d_F0 = (TH1D*)file->Get(trigger+"_Single"+Lepton+"Trigger_Dijet_Awayjet_"+jetpt[a]+bjetconfig[b]+"_"+var+"_F0");
        TH1D *hist2d_F = (TH1D*)file->Get(trigger+"_Single"+Lepton+"Trigger_Dijet_Awayjet_"+jetpt[a]+bjetconfig[b]+"_"+var+"_F");

        double AutoYmax = max( GetMaximum(hist2d_F0), GetMaximum(hist2d_F) );
        dummy->GetYaxis()->SetRangeUser(0., 1.2*AutoYmax);

        hist2d_F0->Draw("hist");
        hist2d_F0->GetXaxis()->SetTitle(xtitle.at(c));
        if(var=="dXY") hist2d_F0->GetXaxis()->SetRangeUser(0., 0.2);
        hist2d_F0->SetTitle("");
        hist2d_F0->SetLineColor(kBlack);
        hist2d_F->SetLineColor(kRed);

        hist2d_F0->Draw("hist");
        hist2d_F->Draw("histsame");

        TString thisplotpath = plotpath+"Variables/"+trigger+"/";
        gSystem->mkdir(thisplotpath, kTRUE);
        c_all->SaveAs(thisplotpath+Lepton+"_"+jetpt[a]+bjetconfig[b]+"_"+Sample+"_"+var+".pdf");
        c_all->Close();


        }
      }

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
