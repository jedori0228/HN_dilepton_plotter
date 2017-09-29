#include "canvas_margin.h"
#include "mylib.h"

void LooseMuon_Optimization(){

  bool DrawPlots = true;

  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = kError;
  TH1::AddDirectory(kFALSE);

  TString dirname  = "MUON_HN_NOCUT_IPsame":
  TString sample = "WJets";

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/LooseMuonOptimization/"+dirname+"/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/LooseMuonOptimization/"+dirname+"/"+sample+"/";

  TFile *output = new TFile(plotpath+"FRs.root", "RECREATE");

  if( !gSystem->mkdir(plotpath, kTRUE) || !gSystem->mkdir(plotpath+"/Diff/", kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }
  gSystem->mkdir(plotpath+"/Diff/", kTRUE);

  const int n_pt = 7;
  float ptarray[n_pt+1] = {5., 10., 20., 30., 40., 50., 60., 70.};

  TFile *file = new TFile(filepath+sample+".root");

  TString LeastDiff="";
  double YMAX = 999999999;

  double MaxSIP = 3, dMaxSIP = 0.5;
  for(int a=0; a<60; a++){

    double MaxChi2 = 10., dMaxChi2 = 10.;
    for(int b=0; b<15; b++){

      TString SIP_Chi2 = TString::Itoa(MaxSIP*10,10)+"_"+TString::Itoa(MaxChi2,10);
      //cout << MaxSIP<<"\t"<<MaxChi2<<" ==> " << SIP_Chi2 << endl;

      TH2D *Heavy_F0 = (TH2D*)file->Get(SIP_Chi2+"_HeavyFlavour_pt_cone_vs_eta_F0");
      TH2D *Heavy_F = (TH2D*)file->Get(SIP_Chi2+"_HeavyFlavour_pt_cone_vs_eta_F");
      TH1D *Heavy_1D = new TH1D("Heavy_1D", "", n_pt, ptarray);

      double Heavy_den(0.), Heavy_num(0.);
      for(int ix=1; ix<=Heavy_F->GetXaxis()->GetNbins(); ix++){
        double den(0.), num(0.);
        for(int iy=1; iy<=Heavy_F->GetYaxis()->GetNbins(); iy++){
          den += Heavy_F0->GetBinContent(ix, iy);
          num += Heavy_F->GetBinContent(ix, iy);
        }
        Heavy_den += den;
        Heavy_num += num;
        double this_FR(0.);
        if(den!=0.){
          this_FR = num/den;
        }
        Heavy_1D->SetBinContent(ix, this_FR);
        Heavy_1D->SetBinError(ix, 0);
      }

      TH2D *Light_F0 = (TH2D*)file->Get(SIP_Chi2+"_LightFlavour_pt_cone_vs_eta_F0");
      TH2D *Light_F = (TH2D*)file->Get(SIP_Chi2+"_LightFlavour_pt_cone_vs_eta_F");
      TH1D *Light_1D = new TH1D("Light_1D", "", n_pt, ptarray);

      double Light_den(0.), Light_num(0.);
      for(int ix=1; ix<=Light_F->GetXaxis()->GetNbins(); ix++){
        double den(0.), num(0.);
        for(int iy=1; iy<=Light_F->GetYaxis()->GetNbins(); iy++){
          den += Light_F0->GetBinContent(ix, iy);
          num += Light_F->GetBinContent(ix, iy);
        }
        Light_den += den;
        Light_num += num;
        double this_FR(0.);
        if(den!=0.){
          this_FR = num/den;
        }
        Light_1D->SetBinContent(ix, this_FR);
        Light_1D->SetBinError(ix, 0);
      }

      TH2D *Average_F0 = (TH2D*)Heavy_F0->Clone();
      Average_F0->Add(Light_F0);
      TH2D *Average_F = (TH2D*)Heavy_F->Clone();
      Average_F->Add(Light_F);
      TH1D *Average_1D = new TH1D("Average_1D", "", n_pt, ptarray);

      double Average_den(0.), Average_num(0.);
      for(int ix=1; ix<=Average_F->GetXaxis()->GetNbins(); ix++){
        double den(0.), num(0.);
        for(int iy=1; iy<=Average_F->GetYaxis()->GetNbins(); iy++){
          den += Average_F0->GetBinContent(ix, iy);
          num += Average_F->GetBinContent(ix, iy);
        }
        Average_den += den;
        Average_num += num;
        double this_FR(0.);
        if(den!=0.){
          this_FR = num/den;
        }
        Average_1D->SetBinContent(ix, this_FR);
        Average_1D->SetBinError(ix, 0);
      }
      output->cd();
      Average_1D->SetName(SIP_Chi2);
      Average_1D->Write();

      double Heavy_FR = Heavy_num/Heavy_den;
      double Light_FR = Light_num/Light_den;

      cout << MaxSIP<<"\t"<<MaxChi2<<" ==> " << Heavy_FR << "\t" << Light_FR << endl;

      TCanvas *c1 = new TCanvas("c1","", 800, 800);
      canvas_margin(c1);
      c1->cd();

      TH1D *dummy = new TH1D("dummy", "", n_pt, ptarray);
      dummy->Draw("hist");
      hist_axis(dummy);
      dummy->GetXaxis()->SetTitle("p_{T}^{cone} [GeV]");
      dummy->GetXaxis()->SetRangeUser(10., 70.);
      dummy->GetYaxis()->SetTitle("Fake Rate");
      dummy->GetYaxis()->SetRangeUser(0., 0.2);

      TGraphAsymmErrors *gr_Heavy = hist_to_graph(Heavy_1D);
      gr_Heavy->SetLineColor(kRed);
      gr_Heavy->SetLineWidth(3);
      gr_Heavy->Draw("lpsame");

      TGraphAsymmErrors *gr_Light = hist_to_graph(Light_1D);
      gr_Light->SetLineColor(kBlue);
      gr_Light->SetLineWidth(3);
      gr_Light->Draw("lpsame");

      TGraphAsymmErrors *gr_Average = hist_to_graph(Average_1D);
      gr_Average->SetLineColor(kBlack);
      gr_Average->SetLineWidth(3);
      gr_Average->SetLineStyle(2);
      gr_Average->Draw("lpsame");

      TLegend *lg = new TLegend(0.7, 0.7, 0.93, 0.93);
      lg->SetBorderSize(0);
      lg->SetFillStyle(0);
      lg->AddEntry(gr_Heavy, "Heavy", "l");
      lg->AddEntry(gr_Light, "Light", "l");
      lg->AddEntry(gr_Average, "Average", "l");
      lg->Draw();

      TLatex latex;
      latex.SetNDC();
      latex.SetTextSize(0.035);

      //TString SIP_Chi2 = TString::Itoa(MaxSIP*10,10)+"_"+TString::Itoa(MaxChi2,10);
      latex.DrawLatex(0.2, 0.8, SIP_Chi2);

      if(DrawPlots) c1->SaveAs(plotpath+SIP_Chi2+".pdf");
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
      if(y_max < YMAX){
        YMAX = y_max;
        LeastDiff = SIP_Chi2;
      }
      TGraphAsymmErrors *gr_Diff = hist_to_graph(Diff_1D);
      gr_Diff->Draw("lpsame");
      Diff_1D->SetLineColor(0);
      Diff_1D->Draw("textsame");
      if(DrawPlots) c2->SaveAs(plotpath+"Diff/"+SIP_Chi2+"_Diff.pdf");
      c2->Close();

      MaxChi2 += dMaxChi2;
    }


    MaxSIP += dMaxSIP;
  }

  cout << "###########################" << endl;
  cout << sample << endl;
  cout << LeastDiff << endl;
  cout << YMAX << endl;

  output->Close();

}

























