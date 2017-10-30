#include "canvas_margin.h"

void Draw_TnP_ID(int period){
  
  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);
  
  bool DrawFitResult = true;
  
  TString DataPeriod = "";
  if(period==1) DataPeriod="BCDEF";
  else if(period==2) DataPeriod="GH";
  else{
    cout << "period wrong" << endl;
    return;
  }

  vector<TString> systs = {"Central", "NMassBins30", "NMassBins50", "MassRange_60_130", "MassRange_70_120", "SignalShapeCB", "TagPt20IsoInf", "TagPt30Iso0p08", "ProbeMult99"};
  //systs = {"Central"};

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/TnP_Results/IDSF/";
  TString base_plotpath = ENV_PLOT_PATH+"/TnP_Results/IDSF/"+DataPeriod+"/";
  
  vector<double> abseta = {0., 0.9, 1.2, 2.1, 2.4};

  for(unsigned int it_syst=0; it_syst<systs.size(); it_syst++){

    TString syst = systs.at(it_syst);

    TString filepath = base_filepath+syst+"/";
    TString plotpath = base_plotpath+syst+"/";

    if( !gSystem->mkdir(plotpath, kTRUE) ){
      cout
      << "###################################################" << endl
      << "Directoy " << plotpath << " is created" << endl
      << "###################################################" << endl
      << endl;
    }

    vector<double> pt = {10, 20, 25, 30, 40, 50, 60, 120};

    gSystem->mkdir(plotpath, kTRUE);
    gSystem->mkdir(plotpath+"fitresult/", kTRUE);
    gSystem->mkdir(plotpath+"fitresult/Data", kTRUE);
    gSystem->mkdir(plotpath+"fitresult/MC", kTRUE);

    TFile *file_ID_Data = new TFile(filepath+"TnP_Muon_ID_Data_"+DataPeriod+".root");
    TFile *file_ID_MC = new TFile(filepath+"TnP_Muon_ID_MC_"+DataPeriod+".root");

    TString dirname = "tpTree/HN_ID_pt_eta";

    //==== Dir with fitcanvas + effplots
    TDirectory *dir_Data = (TDirectory *)file_ID_Data->Get(dirname);
    TDirectory *dir_MC = (TDirectory *)file_ID_MC->Get(dirname);

    //==== Dir with effplots only
    TDirectory *dir_eff_Data = (TDirectory *)dir_Data->Get("fit_eff_plots");
    TDirectory *dir_eff_MC = (TDirectory *)dir_MC->Get("fit_eff_plots");
    
    //==== FitResult
    if(DrawFitResult){
      //==== Data
      for(int i=0; i<dir_Data->GetListOfKeys()->Capacity(); i++){

        TKey *this_key = (TKey *)dir_Data->GetListOfKeys()->At(i);
        TString this_name = dir_Data->GetListOfKeys()->At(i)->GetName();
        TString this_classname = this_key->GetClassName();
        if( (this_classname=="TDirectoryFile") && (this_name.Contains("abseta")) ){

          TCanvas *c_Data = (TCanvas *)dir_Data->Get(this_name+"/fit_canvas");
          c_Data->SaveAs(plotpath+"/fitresult/Data/"+this_name+".pdf");

        }
      }
      //==== MC
      for(int i=0; i<dir_MC->GetListOfKeys()->Capacity(); i++){

        TKey *this_key = (TKey *)dir_MC->GetListOfKeys()->At(i);
        TString this_name = dir_MC->GetListOfKeys()->At(i)->GetName();
        TString this_classname = this_key->GetClassName();
        if( (this_classname=="TDirectoryFile") && (this_name.Contains("abseta")) ){

          TCanvas *c_MC = (TCanvas *)dir_MC->Get(this_name+"/fit_canvas");
          c_MC->SaveAs(plotpath+"/fitresult/MC/"+this_name+".pdf");

        }
      }
    }

    TString outputIDEffname = "MuonIDEfficiency_HNDILEP_Run"+DataPeriod+".root";
    TFile *file_IDEff = new TFile(plotpath+outputIDEffname, "RECREATE");
    
    //==== Eff vs pt for each eta region
    for(unsigned int i_eta = 0; i_eta<abseta.size()-1; i_eta++){
      
      TGraphAsymmErrors *eff_Data = (TGraphAsymmErrors*)dir_eff_Data->Get("pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10))->FindObject("hxy_fit_eff");
      TGraphAsymmErrors *eff_MC = (TGraphAsymmErrors*)dir_eff_MC->Get("pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10))->FindObject("hxy_fit_eff");

      eff_Data->SetName("pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10)+"_Data");
      eff_MC->SetName("pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10)+"_MC");

      file_IDEff->cd();
      eff_Data->Write();
      eff_MC->Write();

      TCanvas *c_eff = new TCanvas("c_eff", "", 800, 800);
      c_eff->Draw();
      TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
      TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
      canvas_margin(c_eff, c1_up, c1_down);
      c1_down->SetGridx();
      c1_down->SetGridy();
      c1_up->Draw();
      c1_down->Draw();
      c1_up->cd();
      
      eff_Data->SetLineColor(kBlack);
      eff_Data->SetMarkerColor(kBlack);
      eff_Data->SetMarkerStyle(21);
      eff_Data->SetMarkerSize(1);
      eff_MC->SetLineColor(kBlue);
      eff_MC->SetMarkerColor(kBlue);
      eff_MC->SetMarkerStyle(21);
      eff_MC->SetMarkerSize(1);
      
      eff_Data->Draw("ap");
      eff_MC->Draw("psame");
      
      TLegend *lg = new TLegend(0.5, 0.5, 0.8, 0.8);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->AddEntry(eff_Data, "Run "+DataPeriod, "lp");
      lg->AddEntry(eff_MC, "MC", "lp");
      lg->Draw();
      
      eff_Data->SetTitle("");
      eff_Data->GetYaxis()->SetTitle("Efficiency");
      eff_Data->GetYaxis()->SetRangeUser(0, 1.1);
      
      c1_down->cd();
      
      if (eff_Data->GetN() == 0 || eff_MC->GetN() == 0) return;
      TGraphAsymmErrors *ratio = new TGraphAsymmErrors(eff_Data->GetN());
      double max = 0;
      for (size_t i = 0, n = eff_Data->GetN(); i < n; ++i) {
        double r   = eff_Data->GetY()[i]/eff_MC->GetY()[i];
        double rup = (eff_Data->GetY()[i] == 0 ? eff_Data->GetErrorYhigh(i)/(eff_MC->GetY()[i]) :
                      r*TMath::Hypot(eff_Data->GetErrorYhigh(i)/eff_Data->GetY()[i], eff_MC->GetErrorYlow(i)/eff_MC->GetY()[i]));
        double rdn = (eff_Data->GetY()[i] == 0 ? 0 :
                      r*TMath::Hypot(eff_Data->GetErrorYlow(i)/eff_Data->GetY()[i],  eff_MC->GetErrorYhigh(i)/eff_MC->GetY()[i]));
        max = TMath::Max(max, fabs(r-1+rup));
        max = TMath::Max(max, fabs(r-1-rdn));
        ratio->SetPoint(i, eff_Data->GetX()[i], r);
        ratio->SetPointError(i, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
      }
      
      ratio->SetLineWidth(2);
      ratio->SetLineColor(kBlack);
      ratio->SetMarkerColor(kBlack);
      ratio->SetMarkerStyle(20);
      ratio->SetMarkerSize(1.6);
      ratio->Draw("AP");
      ratio->GetXaxis()->SetTitle("p_{T} [GeV]");
      ratio->GetYaxis()->SetTitle("Data/MC");
      ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
      
      /*
       for(size_t i = 0, n = eff_Data->GetN(); i < n; ++i){
       double a,b;
       eff_Data->GetPoint(i, a, b);
       cout << "x = " << a << ", Data = " << b << endl;
       eff_MC->GetPoint(i, a, b);
       cout << "x = " << a << ", MC = " << b << endl;
       ratio->GetPoint(i, a, b);
       cout << "x = " << a << ", ratio = " << b << endl <<  endl;
       }
       */
      
      hist_axis(eff_Data, ratio);
      
      TLine line(ratio->GetX()[0]-ratio->GetErrorXlow(0), 1, ratio->GetX()[ratio->GetN()-1]+ratio->GetErrorXhigh(ratio->GetN()-1), 1);
      line.SetLineWidth(2);
      line.SetLineColor(kRed);
      line.DrawClone("SAME");
      
      c_eff->cd();
      TLatex latex_CMSPriliminary, latex_Lumi;
      latex_CMSPriliminary.SetNDC();
      latex_Lumi.SetNDC();
      latex_CMSPriliminary.SetTextSize(0.035);
      latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
      latex_Lumi.SetTextSize(0.035);
      if(DataPeriod=="BCDEF") latex_Lumi.DrawLatex(0.7, 0.96, "20.1 fb^{-1} (13 TeV)");
      else if(DataPeriod=="GH") latex_Lumi.DrawLatex(0.7, 0.96, "16.3 fb^{-1} (13 TeV)");
      
      c_eff->SaveAs(plotpath+"/pt_PLOT_abseta_bin"+TString::Itoa(i_eta,10)+".pdf");
      
      c_eff->Close();
      
      delete c_eff;
      
    }
    
    //==== Eff vs abseta for each pt region
    for(unsigned int i_pt = 0; i_pt<pt.size()-1; i_pt++){
      
      TGraphAsymmErrors *eff_Data = (TGraphAsymmErrors*)dir_eff_Data->Get("abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10))->FindObject("hxy_fit_eff");
      TGraphAsymmErrors *eff_MC = (TGraphAsymmErrors*)dir_eff_MC->Get("abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10))->FindObject("hxy_fit_eff");

      eff_Data->SetName("abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10)+"_Data");
      eff_MC->SetName("abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10)+"_MC");

      file_IDEff->cd();
      eff_Data->Write();
      eff_MC->Write();

      TCanvas *c_eff = new TCanvas("c_eff", "", 800, 800);
      c_eff->Draw();
      TPad *c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
      TPad *c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);
      canvas_margin(c_eff, c1_up, c1_down);
      c1_down->SetGridx();
      c1_down->SetGridy();
      c1_up->Draw();
      c1_down->Draw();
      c1_up->cd();
      
      eff_Data->SetLineColor(kBlack);
      eff_Data->SetMarkerColor(kBlack);
      eff_Data->SetMarkerStyle(21);
      eff_Data->SetMarkerSize(1);
      eff_MC->SetLineColor(kBlue);
      eff_MC->SetMarkerColor(kBlue);
      eff_MC->SetMarkerStyle(21);
      eff_MC->SetMarkerSize(1);

      eff_Data->Draw("ap");
      eff_MC->Draw("psame");
      
      TLegend *lg = new TLegend(0.5, 0.5, 0.8, 0.8);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      if(DataPeriod=="BCDEF") lg->AddEntry(eff_Data, "Run BCDEF", "lp");
      else if(DataPeriod=="GH") lg->AddEntry(eff_Data, "Run GH", "lp");
      lg->AddEntry(eff_MC, "MC", "lp");
      lg->Draw();
      
      eff_Data->SetTitle("");
      eff_Data->GetYaxis()->SetTitle("Efficiency");
      eff_Data->GetYaxis()->SetRangeUser(0, 1.1);
      
      c1_down->cd();
      
      if (eff_Data->GetN() == 0 || eff_MC->GetN() == 0) return;
      TGraphAsymmErrors *ratio = new TGraphAsymmErrors(eff_Data->GetN());
      double max = 0;
      for (size_t i = 0, n = eff_Data->GetN(); i < n; ++i) {
        double r   = eff_Data->GetY()[i]/eff_MC->GetY()[i];
        double rup = (eff_Data->GetY()[i] == 0 ? eff_Data->GetErrorYhigh(i)/(eff_MC->GetY()[i]) :
                      r*TMath::Hypot(eff_Data->GetErrorYhigh(i)/eff_Data->GetY()[i], eff_MC->GetErrorYlow(i)/eff_MC->GetY()[i]));
        double rdn = (eff_Data->GetY()[i] == 0 ? 0 :
                      r*TMath::Hypot(eff_Data->GetErrorYlow(i)/eff_Data->GetY()[i],  eff_MC->GetErrorYhigh(i)/eff_MC->GetY()[i]));
        max = TMath::Max(max, fabs(r-1+rup));
        max = TMath::Max(max, fabs(r-1-rdn));
        ratio->SetPoint(i, eff_Data->GetX()[i], r);
        ratio->SetPointError(i, eff_Data->GetErrorXlow(i), eff_Data->GetErrorXhigh(i), rdn, rup);
      }
      
      ratio->SetLineWidth(2);
      ratio->SetLineColor(kBlack);
      ratio->SetMarkerColor(kBlack);
      ratio->SetMarkerStyle(20);
      ratio->SetMarkerSize(1.6);
      ratio->Draw("AP");
      ratio->GetXaxis()->SetTitle("|#eta|");
      ratio->GetYaxis()->SetTitle("Data/MC");
      ratio->GetYaxis()->SetRangeUser(0.8, 1.2);
      
      hist_axis(eff_Data, ratio);
      
      TLine line(ratio->GetX()[0]-ratio->GetErrorXlow(0), 1, ratio->GetX()[ratio->GetN()-1]+ratio->GetErrorXhigh(ratio->GetN()-1), 1);
      line.SetLineWidth(2);
      line.SetLineColor(kRed);
      line.DrawClone("SAME");
      
      c_eff->cd();
      TLatex latex_CMSPriliminary, latex_Lumi;
      latex_CMSPriliminary.SetNDC();
      latex_Lumi.SetNDC();
      latex_CMSPriliminary.SetTextSize(0.035);
      latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
      latex_Lumi.SetTextSize(0.035);
      if(DataPeriod=="BCDEF") latex_Lumi.DrawLatex(0.7, 0.96, "20.1 fb^{-1} (13 TeV)");
      else if(DataPeriod=="GH") latex_Lumi.DrawLatex(0.7, 0.96, "16.3 fb^{-1} (13 TeV)");
      
      
      c_eff->SaveAs(plotpath+"/abseta_PLOT_pt_bin"+TString::Itoa(i_pt,10)+".pdf");
      
      c_eff->Close();
      delete c_eff;
      
    }
    
    //==== make SF root file

    TString name_2D_Data = "";
    for(int i=0; i<dir_eff_Data->GetListOfKeys()->Capacity(); i++){
      TString this_name = dir_eff_Data->GetListOfKeys()->At(i)->GetName();
      if(this_name.Contains("abseta_pt_PLOT")){
        name_2D_Data = this_name;
        break;
      }
    }

    TCanvas *c_IDEff_Data = (TCanvas*)dir_eff_Data->Get(name_2D_Data);
    TCanvas *c_IDEff_MC = (TCanvas*)dir_eff_MC->Get(name_2D_Data);

    TH2F *hist_IDEff_Data = (TH2F*)c_IDEff_Data->GetPrimitive(name_2D_Data)->Clone();
    TH2F *hist_IDEff_MC = (TH2F*)c_IDEff_MC->GetPrimitive(name_2D_Data)->Clone();

    c_IDEff_Data->Close();
    c_IDEff_MC->Close();

    hist_IDEff_Data->SetName("IDEff_HNDilepton_"+DataPeriod+"_Data");
    hist_IDEff_MC->SetName("IDEff_HNDilepton_"+DataPeriod+"_MC");

    file_IDEff->cd();
    hist_IDEff_Data->Write();
    hist_IDEff_MC->Write();
    file_IDEff->Close();

    //=== draw MC efficiency 
    TCanvas *c_eff_MC = new TCanvas("c_eff_MC", "", 800, 800);
    canvas_margin(c_eff_MC);
    c_eff_MC->cd();
    gStyle->SetPaintTextFormat("0.4f");
    hist_IDEff_MC->Draw("texte1");
    hist_axis(hist_IDEff_MC);
    hist_IDEff_MC->GetXaxis()->SetTitle("muon |#eta|");
    hist_IDEff_MC->GetYaxis()->SetTitle("muon p_{T} [GeV]");
    c_eff_MC->SaveAs(plotpath+"/abseta_pt_MC.pdf");
    c_eff_MC->Close();

    //=== draw Data efficiency 
    TCanvas *c_eff_Data = new TCanvas("c_eff_Data", "", 800, 800);
    canvas_margin(c_eff_Data);
    c_eff_Data->cd();
    gStyle->SetPaintTextFormat("0.4f");
    hist_IDEff_Data->Draw("texte1");
    hist_axis(hist_IDEff_Data);
    hist_IDEff_Data->GetXaxis()->SetTitle("muon |#eta|");
    hist_IDEff_Data->GetYaxis()->SetTitle("muon p_{T} [GeV]");
    c_eff_Data->SaveAs(plotpath+"/abseta_pt_Data.pdf");
    //==== ratio
    hist_IDEff_Data->Divide(hist_IDEff_MC);
    hist_IDEff_Data->Draw("texte1");
    c_eff_Data->SaveAs(plotpath+"/abseta_pt_SF.pdf");
    c_eff_Data->Close();

  } // Systematic loop
    
}











