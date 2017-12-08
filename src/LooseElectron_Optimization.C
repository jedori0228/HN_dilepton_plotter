#include "canvas_margin.h"
#include "mylib.h"

void LooseElectron_Optimization(){

  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = kError;
  TH1::AddDirectory(kFALSE);

  TString sample = "WJets_v4_3";

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/LooseElectronOptimization/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/LooseElectronOptimization/"+sample+"/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }


  const int n_pt = 9;
  float ptarray[n_pt+1] = {10., 15., 20., 23., 30., 35., 40., 50., 60., 70.};

  TString etaregion_name[3] = {"InnerBarrel", "OuterBarrel", "EndCap"};

  TFile *file = new TFile(filepath+sample+".root");

  for(int a=0; a<3; a++){

    TString EtaRegion = etaregion_name[a];

    gSystem->mkdir(plotpath+EtaRegion, kTRUE);
    gSystem->mkdir(plotpath+EtaRegion+"/Diff/", kTRUE);

    TString LeastDiff="";
    double YMAX = 999999999;
    double MinMVA = -1.;
    double MaxPTROI = 35;

    for(int b=0; b<200; b++){

      TString StringMVA = TString::Itoa(100.*MinMVA,10)+"_"+EtaRegion;

      TH2D *Heavy_F0 = (TH2D*)file->Get(StringMVA+"_HeavyFlavour_pt_cone_vs_eta_F0");
      TH2D *Heavy_F = (TH2D*)file->Get(StringMVA+"_HeavyFlavour_pt_cone_vs_eta_F");
      if(!Heavy_F0||!Heavy_F) continue;
      TH1D *Heavy_1D = new TH1D("Heavy_1D", "", n_pt, ptarray);

      double Heavy_den(0.), Heavy_num(0.);
      for(int ix=1; ix<=Heavy_F->GetXaxis()->GetNbins(); ix++){
        double den(0.), num(0.);

        double x_left = Heavy_F->GetXaxis()->GetBinLowEdge(ix);
        double x_right = Heavy_F->GetXaxis()->GetBinUpEdge(ix);
        bool IsROI = (x_right<=MaxPTROI);

        for(int iy=1; iy<=Heavy_F->GetYaxis()->GetNbins(); iy++){
          den += Heavy_F0->GetBinContent(ix, iy);
          num += Heavy_F->GetBinContent(ix, iy);
        }
        if(IsROI){
          Heavy_den += den;
          Heavy_num += num;
        }
        double this_FR(0.);
        if(den!=0.){
          this_FR = num/den;
        }
        Heavy_1D->SetBinContent(ix, this_FR);
        Heavy_1D->SetBinError(ix, 0);
      }

      TH2D *Light_F0 = (TH2D*)file->Get(StringMVA+"_LightFlavour_pt_cone_vs_eta_F0");
      TH2D *Light_F = (TH2D*)file->Get(StringMVA+"_LightFlavour_pt_cone_vs_eta_F");
      if(!Light_F0||!Light_F) continue;
      TH1D *Light_1D = new TH1D("Light_1D", "", n_pt, ptarray);

      double Light_den(0.), Light_num(0.);
      for(int ix=1; ix<=Light_F->GetXaxis()->GetNbins(); ix++){
        double den(0.), num(0.);

        double x_left = Heavy_F->GetXaxis()->GetBinLowEdge(ix);
        double x_right = Heavy_F->GetXaxis()->GetBinUpEdge(ix);
        bool IsROI = (x_right<=MaxPTROI);

        for(int iy=1; iy<=Light_F->GetYaxis()->GetNbins(); iy++){
          den += Light_F0->GetBinContent(ix, iy);
          num += Light_F->GetBinContent(ix, iy);
        }
        if(IsROI){
          Light_den += den;
          Light_num += num;
        }
        double this_FR(0.);
        if(den!=0.){
          this_FR = num/den;
        }
        Light_1D->SetBinContent(ix, this_FR);
        Light_1D->SetBinError(ix, 0);
      }

      Heavy_den = Heavy_F0->GetEntries();
      Heavy_num = Heavy_F->GetEntries();
      Light_den = Light_F0->GetEntries();
      Light_num = Light_F->GetEntries();


      double Heavy_FR = Heavy_num/Heavy_den;
      double Light_FR = Light_num/Light_den;

      //cout << MaxSIP<<"\t"<<MaxChi2<<" ==> " << Heavy_FR << "\t" << Light_FR << endl;

      TCanvas *c1 = new TCanvas("c1","", 800, 800);
      canvas_margin(c1);
      c1->cd();

      TH1D *dummy = new TH1D("dummy", "", n_pt, ptarray);
      dummy->Draw("hist");
      hist_axis(dummy);
      dummy->GetYaxis()->SetRangeUser(0., 0.2);

      TGraphAsymmErrors *gr_Heavy = hist_to_graph(Heavy_1D);
      gr_Heavy->SetLineColor(kRed);
      gr_Heavy->SetLineWidth(3);
      gr_Heavy->Draw("lpsame");

      TGraphAsymmErrors *gr_Light = hist_to_graph(Light_1D);
      gr_Light->SetLineColor(kBlue);
      gr_Light->SetLineWidth(3);
      gr_Light->Draw("lpsame");

      c1->SaveAs(plotpath+EtaRegion+"/"+TString::Itoa(100.*MinMVA,10)+".pdf");
      c1->Close();


      TCanvas *c2 = new TCanvas("c2","", 800, 800);
      canvas_margin(c2);
      c2->cd();
      dummy->Draw("hist");
      hist_axis(dummy);
      TH1D *Diff_1D = (TH1D *)Heavy_1D->Clone();
      Diff_1D->Add(Light_1D, -1.);
      Diff_1D->Divide(Light_1D);
      for(int ix=1; ix<=Diff_1D->GetXaxis()->GetNbins(); ix++){
        Diff_1D->SetBinContent(ix, fabs(Diff_1D->GetBinContent(ix)));
      }
      double y_max = GetMaximum(Diff_1D);
      dummy->GetYaxis()->SetRangeUser(0., 1.2*y_max);
/*
      if(y_max < YMAX){
        YMAX = y_max;
        LeastDiff = StringMVA;
      }
*/
      TGraphAsymmErrors *gr_Diff = hist_to_graph(Diff_1D);
      gr_Diff->Draw("lpsame");
      Diff_1D->SetLineColor(0);
      Diff_1D->Draw("textsame");
      c2->SaveAs(plotpath+EtaRegion+"/Diff/"+TString::Itoa(100.*MinMVA,10)+"_Diff.pdf");
      c2->Close();


      double FR_reldiff = fabs(Heavy_FR-Light_FR)/Light_FR;
      FR_reldiff = fabs(Heavy_FR-Light_FR)/Light_FR;

      if(FR_reldiff < YMAX){
        YMAX = FR_reldiff;
        LeastDiff = StringMVA;
      }

      MinMVA += 0.01;
    } // Eta Region

    cout << "###########################" << endl;
    cout << sample << endl;
    cout << LeastDiff << endl;
    cout << YMAX << endl;

  }



}

























