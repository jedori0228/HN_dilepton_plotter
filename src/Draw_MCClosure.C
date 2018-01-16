#include "canvas_margin.h"
#include "mylib.h"

void Draw_MCClosure(){

  bool DrawPlot = true;
  bool DoLatex = true;
  bool PrintSyst = false;

  double WJets_reweight = 0.684044;
  double DYJets_reweight = 0.670033;

  gStyle->SetOptStat(0);
  //gErrorIgnoreLevel = kError;

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
    "DiElectron",
    "DiMuon",
    "EMu",
  };
  vector<TString> channelsForLatex = {
    "ee",
    "#mu#mu",
    "e#mu",
  };

  vector<TString> regions = {
    "Preselection",
    "Preselection_ElectronSubLead",
    "Preselection_MuonSubLead",

    //"Low_TwoJet_NoFatJet",
    //"Low_OneJet_NoFatJet",
    //"High_TwoJet_NoFatJet",
    //"High_OneFatJet_NoFatJet",

  };
  vector<TString> regionsfortex = {
    "Preselection",
    "Preselection, e-trailing",
    "Preseleciton, $\\mu$-trailing",

    //"Low\\_TwoJet\\_NoFatJet",
    //"Low\\_OneJet\\_NoFatJet",
    //"High\\_TwoJet\\_NoFatJet",
    //"High\\_OneFatJet\\_NoFatJet",

  };

  vector<TString> samples = {
    "TT_powheg",
    "DYJets_positive",
    "WJets_positive",
  };
  vector<TString> samplesalias = {
    "t#bar{t}",
    "DY+Jets",
    "W+Jets",
  };
  vector<TString> samplesfortex = {
    "TT\\_powheg",
    "DYJets\\_positive",
    "WJets\\_positive",
  };
  vector<Color_t> colors = {
    kRed,
    kYellow,
    870,
  };

  TLegend *lg = new TLegend(0.69, 0.65, 0.96, 0.92);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  //==== error bar
  TH1D *histtmperr = new TH1D("histtmperr", "", 1, 0., 1.);
  histtmperr->SetMarkerColorAlpha(kAzure-9, 0);
  histtmperr->SetFillStyle(3013);
  histtmperr->SetFillColor(kBlack);
  histtmperr->SetLineColor(0);
  lg->AddEntry(histtmperr, "Stat. Uncert.", "f");
  //==== Data
  TH1D *histtmpdata = new TH1D("histtmpdata", "", 1, 0., 1.);
  histtmpdata->SetMarkerStyle(20);
  histtmpdata->SetMarkerSize(1.6);
  histtmpdata->SetMarkerColor(kBlack);
  histtmpdata->SetLineColor(kBlack);
  lg->AddEntry(histtmpdata, "Measured", "ple");
  for(int i=samples.size()-1; i>=0; i--){
    TH1D *histtmp = new TH1D(samples.at(i), "", 1, 0., 1.);
    histtmp->SetLineColor(colors.at(i));
    histtmp->SetFillColor(colors.at(i));
    lg->AddEntry(histtmp, samplesalias.at(i), "f");
  }

  //==== y=1 line
  double x_1[2], y_1[2];
  x_1[0] = 5000;  y_1[0] = 1;
  x_1[1] = -5000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);

  vector<TString> vars = {
    "leadingLepton_Pt", "secondLepton_Pt",
    "Nevents", "Nbjets_nolepveto", "PFMET", "Njets",
    "secondJet_Pt", "leadingLepton_Type",
    "secondLepton_Type", "secondLepton_Eta",
    "leadingLepton_Eta", "secondLepton_mva",
    "secondLepton_RelIso", "weight_fr",
    "NLooseNotTight_weight1", "secondLepton_Pt_cone",
  };
  vector<TString> xtitle = {
    "Leading Lepton p_{T} [GeV]", "Sub-Leading Lepton p_{T} [GeV]",
    "onebin", "# of b-jets", "E_{T}^{miss} [GeV]", "# of jets",
    "Leading Jet p_{T} [GeV]", "Leading Lepton Type",
    "Sub-Leading Lepton Type", "Sub-Leading Lepton #eta",
    "Leading Lepton #eta", "Sub-Leading Lepton MVA",
    "Sub-Leading Lepton RelIso", "FR weight",
    "# of Loose no Tight", "Sub-Leading Lepton p_{T}^{cone} [GeV]",
  };
  vector<double> ymaxs = {
    50, 100,
    400, 100, 50, 50,
    50, 50,
    50, 300,
    300, 300,
    300, 300,
    300, 300,
  };
  vector<int> rebins = {
    5, 5,
    1, 1, 10, 1,
    10, 1,
    1, 5,
    5, 5,
    1, 1,
    1, 5,
  };

  for(unsigned int k=0; k<regions.size(); k++){

    //cout << "#### "<<regions.at(k)<< "####" << endl;

    for(unsigned int l=0; l<channels.size(); l++){

      TString channel = channels.at(l);

      if(regions.at(k).Contains("SubLead") && channel!="EMu") continue;

      int n_samples = samples.size();
      TH1D *hist_allsample_measured = new TH1D("hist_allsample_measured", "", n_samples, 0., 1.*n_samples);
      TH1D *hist_allsample_predicted = new TH1D("hist_allsample_prediected", "", n_samples, 0., 1.*n_samples);

      for(unsigned int j=0; j<vars.size(); j++){

        TString var = vars.at(j);

        //cout << "############### " << var << " ###############" << endl;

        TH1D *hist_summed_Predicted = NULL;
        THStack *stack_summed_Predicted = new THStack("stack_summed_Predicted", "");
        TH1D *hist_summed_Measured = NULL;

        const int N_sample = samplesalias.size();
        TH1D *hist_binned_Predicted = new TH1D("hist_binned_Predicted", "", N_sample, 0., 1.*N_sample);
        TH1D *hist_binned_Measured = new TH1D("hist_binned_Measured", "", N_sample, 0., 1.*N_sample);

        for(unsigned int i=0; i<samples.size(); i++){

          TString sample = samples.at(i);

          TFile *file_Measured = new TFile(filepath+"Measured/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_v8-0-7.root");
          TFile *file_Predicted = new TFile(filepath+"Predicted/DiLeptonAnalyzer_SK"+sample+"_dilep_cat_v8-0-7.root");

          TString ChargeSign = "SS";
          if(sample.Contains("WJets")) ChargeSign = "AllCharge";

          TString region = regions.at(k)+"_"+ChargeSign;


          TString dirname = channel+"_"+region;
          TString histname = var+"_"+channel+"_"+region;

          TH1D *hist_Measured = (TH1D*)file_Measured->Get(dirname+"/"+histname);
          TH1D *hist_Predicted = (TH1D*)file_Predicted->Get(dirname+"/"+histname);
          TH1D *hist_Predicted_up = (TH1D*)file_Predicted->Get(dirname+"_up/"+histname+"_up");
          TH1D *hist_Predicted_down = (TH1D*)file_Predicted->Get(dirname+"_down/"+histname+"_down");

          if(!hist_Measured || !hist_Predicted){
            file_Measured->Close();
            file_Predicted->Close();
            continue;
          }

          if(sample=="WJets_positive"){
            hist_Measured->Scale(WJets_reweight);
            hist_Predicted->Scale(WJets_reweight);
            hist_Predicted_up->Scale(WJets_reweight);
            hist_Predicted_down->Scale(WJets_reweight);
          }
          if(sample=="DYJets_positive"){
            hist_Measured->Scale(DYJets_reweight);
            hist_Predicted->Scale(DYJets_reweight);
            hist_Predicted_up->Scale(DYJets_reweight);
            hist_Predicted_down->Scale(DYJets_reweight);
          }


/*
          if(hist_Predicted_up){
            for(int a=1; a<=hist_Predicted->GetXaxis()->GetNbins(); a++){
              double err_sumw2 = hist_Predicted->GetBinError(a);
              double err_propagated = hist_Predicted_up->GetBinContent(a)-hist_Predicted->GetBinContent(a);
              double newerr = sqrt(err_sumw2*err_sumw2+err_propagated*err_propagated);
              hist_Predicted->SetBinError(a, newerr);
            }
          }
*/

          if(var=="Nevents"){

            //==== Calculate Systematics

            double SystExtra = 0.;

            double y_m = hist_Measured->GetBinContent(1);
            double e_m = hist_Measured->GetBinError(1);
            double y_p = hist_Predicted->GetBinContent(1);
            double e_p = hist_Predicted->GetBinError(1);

            //==== One Binned

            hist_binned_Predicted->SetBinContent(i+1, y_p);
            hist_binned_Predicted->SetBinError(i+1, e_p);
            hist_binned_Measured->SetBinContent(i+1, y_m);
            hist_binned_Measured->SetBinError(i+1, e_m);

            //==== Over Prediction
            if( y_p >= y_m ){
              double diff = (y_p-e_p)-(y_m+e_m);
              if(diff<=0) SystExtra = 0.;
              else{
                SystExtra = sqrt( (e_p+diff)*(e_p+diff) - e_p*e_p );
              }
            }
            //==== Under Prediction
            else{
              double diff = (y_m-e_m)-(y_p+e_p);
              if(diff<=0) SystExtra = 0.;
              else{
                SystExtra = sqrt( (e_p+diff)*(e_p+diff) - e_p*e_p );
              }
            }

            SystExtra = SystExtra/y_p;


            TH1D *temp_measured = (TH1D*)hist_Measured->Clone();
            temp_measured->Divide(hist_Predicted);

/*
            double SystExtra = 0.;
            double Deviation = fabs(1.-temp_measured->GetBinContent(1));
            double StatError = temp_measured->GetBinError(1);
            if(Deviation>StatError){
              SystExtra = sqrt(Deviation*Deviation-StatError*StatError);
            }
*/

            if(PrintSyst){
              cout << "["<<sample<<"]" << endl;
              cout << "Region : " << region << endl;
              cout << "Channel : " << channel << endl;
              cout << "Measured = " << hist_Measured->GetBinContent(1) << " +- " << hist_Measured->GetBinError(1) << " ("<<hist_Measured->GetEntries() << ")" << endl;
              cout << "Predicted = " << hist_Predicted->GetBinContent(1) << " +- " << hist_Predicted->GetBinError(1) << " ("<<hist_Predicted->GetEntries() << ")" << endl;
              cout << "=> (Measured-Predicted)/Predicted = " << std::fixed<<std::setprecision(1) << 100.*(hist_Measured->GetBinContent(1)-hist_Predicted->GetBinContent(1))/hist_Predicted->GetBinContent(1) << endl;
              cout << "=> Measured/Predicted = " << temp_measured->GetBinContent(1) << " +- " << temp_measured->GetBinError(1) << endl;
              cout << "=> Systematic Extra = " << std::fixed<<std::setprecision(1)<<100.*SystExtra << endl << endl;
            }

            if(DoLatex){

              TString texfilepath = plotpath+"/"+channel+"/"+region+"/"+sample+"/tex/";
              gSystem->mkdir(texfilepath, kTRUE);

              ofstream ofile_tex(texfilepath+"/Yields.tex",ios::trunc);
              ofile_tex.setf(ios::fixed,ios::floatfield);
              ofile_tex << "\\documentclass[10pt]{article}" << endl;
              ofile_tex << "\\usepackage{epsfig,subfigure,setspace,xtab,xcolor,array,colortbl}" << endl;
              ofile_tex << "\\usepackage{makecell}" << endl;
              ofile_tex << "\\begin{document}" << endl;
              ofile_tex << "\\input{"+texfilepath+"/Table.txt}" << endl;
              ofile_tex << "\\end{document}" << endl;

              ofstream ofile(texfilepath+"/Table.txt",ios::trunc);
              ofile.precision(2);
              ofile.setf(ios::fixed,ios::floatfield);
              ofile << "\\begin{table}[!tbh]" << endl;
              ofile << "  \\caption{" << endl;
              ofile << "    MC closure test result at " << channel << " " << regionsfortex.at(k) << ", using " << samplesfortex.at(i) << endl;
              ofile << "  }" << endl;
              ofile << "  \\begin{center}" << endl;
              ofile << "    \\begin{tabular}{c|cc}" << endl;
              ofile << "\\hline" << endl;

              ofile << "\\makecell{"
                    << "\\textcolor{black}{" << channel << "} \\\\ "
                    << "\\textcolor{blue}{" << regionsfortex.at(k) << "} \\\\ "
                    << "\\textcolor{red}{" << samplesfortex.at(i) << "}} & Weighted Yield & Unweighted Yield \\\\" << endl;
              ofile << "\\hline" << endl;
              ofile << " Measured & $" << hist_Measured->GetBinContent(1) << " \\pm " << hist_Measured->GetBinError(1) << " $ & " << int(hist_Measured->GetEntries()) << "\\\\"  << endl;
              ofile << " Predicted & $" << hist_Predicted->GetBinContent(1) << " \\pm " << hist_Predicted->GetBinError(1) << " $ & " << int(hist_Predicted->GetEntries()) << "\\\\"  << endl;
              ofile << "\\hline" << endl;
              ofile << "\\hline" << endl;
              ofile << "\\multicolumn{3}{c}{(Measured-Predicted)$/$Predicted = $"
                    << 100.*(hist_Measured->GetBinContent(1)-hist_Predicted->GetBinContent(1))/hist_Predicted->GetBinContent(1)
                    << "$~\\\%} \\\\ "<< endl;
              ofile << "\\hline" << endl;
              ofile << "\\multicolumn{3}{c}{Systematic = $"
                    << 100.*SystExtra 
                    << "$~\\\%} \\\\ "<< endl;
              ofile << "\\hline" << endl;
              ofile << "    \\end{tabular}" << endl;
              ofile << "  \\end{center}" << endl;
              ofile << "\\end{table}" << endl;

              system("latex "+texfilepath+"/Yields.tex");
              system("dvipdf Yields.dvi");
              system("rm *aux");
              system("rm *log");
              system("rm *dvi");
              system("mv Yields.pdf "+texfilepath);

            }

          }

          if(var.Contains("Pt")){
/*
            const int n_pt_muon = 11;
            double ptarray_muon[n_pt_muon+1] = {0., 5., 10., 15., 20., 25., 30., 40., 50., 60., 70., 200};

            const int n_pt_electron = 11;
            double ptarray_electron[n_pt_electron+1] = {0., 10., 15., 20., 23., 30., 35., 40., 50., 60., 70., 200};
*/
/*
            const int n_pt_muon = 10;
            double ptarray_muon[n_pt_muon+1] = {0., 5., 10., 20., 25., 30., 40., 50., 60., 70., 200};

            const int n_pt_electron = 10;
            double ptarray_electron[n_pt_electron+1] = {0., 10., 20., 23., 30., 35., 40., 50., 60., 70., 200};
*/

            const int n_pt_muon = 10;
            double ptarray_muon[n_pt_muon+1] = {0., 5., 10., 20., 25., 30., 40., 50., 60., 70., 200};

            const int n_pt_electron = 10;
            double ptarray_electron[n_pt_electron+1] = {0., 5., 10., 20., 25., 30., 40., 50., 60., 70., 200};

            if(channel=="DiMuon"){
              hist_Measured = (TH1D *)hist_Measured->Rebin(n_pt_muon,"hnew1", ptarray_muon);
              hist_Predicted = (TH1D *)hist_Predicted->Rebin(n_pt_muon,"hnew1", ptarray_muon);
            }
            if(channel=="DiElectron"){
              hist_Measured = (TH1D *)hist_Measured->Rebin(n_pt_electron,"hnew1", ptarray_electron);
              hist_Predicted = (TH1D *)hist_Predicted->Rebin(n_pt_electron,"hnew1", ptarray_electron);
            }


            if(channel=="EMu"){

              if(var.Contains("leading")){
              hist_Measured = (TH1D *)hist_Measured->Rebin(n_pt_muon,"hnew1", ptarray_muon);
              hist_Predicted = (TH1D *)hist_Predicted->Rebin(n_pt_muon,"hnew1", ptarray_muon);
              }
              if(var.Contains("second")){
              hist_Measured = (TH1D *)hist_Measured->Rebin(n_pt_electron,"hnew1", ptarray_electron);
              hist_Predicted = (TH1D *)hist_Predicted->Rebin(n_pt_electron,"hnew1", ptarray_electron);
              }
/*
              if(var.Contains("Pt")){
                hist_Measured->Rebin(5);
                hist_Predicted->Rebin(5);
              }
*/
            }

          }
          else{
            hist_Measured->Rebin(rebins.at(j));
            hist_Predicted->Rebin(rebins.at(j));
          }

          TCanvas *c1 = new TCanvas("c1", "", 800, 800);
          canvas_margin(c1);
          c1->Draw();

          hist_Measured->SetLineColor(kBlack);
          hist_Measured->SetMarkerColor(kBlack);
          hist_Measured->SetMarkerStyle(20);
          hist_Measured->SetMarkerSize(1.6);

          hist_Predicted->SetLineColor(kRed);
          hist_Predicted->SetLineWidth(3);

          hist_Predicted->Draw("histsamee1");
          hist_Measured->Draw("psamee1");

          hist_axis(hist_Predicted);
          if(var.Contains("leadingLepton_Pt")) hist_Predicted->GetXaxis()->SetRangeUser(0, 150);
          if(var.Contains("secondLepton_Pt")) hist_Predicted->GetXaxis()->SetRangeUser(0, 70);
          if(channel=="EMu"){
            if(var.Contains("leadingLepton_Pt")) hist_Predicted->GetXaxis()->SetRangeUser(0, 70);
            if(var.Contains("secondLepton_Pt")) hist_Predicted->GetXaxis()->SetRangeUser(0, 70);
          }
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

          TLatex latex_CMSPriliminary, latex_Lumi;
          latex_CMSPriliminary.SetNDC();
          latex_Lumi.SetNDC();
          latex_CMSPriliminary.SetTextSize(0.035);
          latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
          latex_Lumi.SetTextSize(0.035);
          latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

          TString str_channel = "#splitline{"+samplesalias.at(i)+"}{"+region+"}";
          TLatex channelname;
          channelname.SetNDC();
          channelname.SetTextSize(0.037);
          channelname.DrawLatex(0.2, 0.88, str_channel);

          if(DrawPlot){
            gSystem->mkdir(plotpath+"/"+channel+"/"+region+"/"+sample, kTRUE);
            c1->SaveAs(plotpath+"/"+channel+"/"+region+"/"+sample+"/"+sample+"_"+var+".pdf");
            c1->SaveAs(plotpath+"/"+channel+"/"+region+"/"+sample+"/"+sample+"_"+var+".png");
          }
          c1->Close();

          //==== Summed plot

          if(sample.Contains("WJets")){
            hist_Predicted->Scale(0.5);
            hist_Measured->Scale(0.5);
          }

          TDirectory *origDir = gDirectory;
          TDirectory *tempDir1 = MakeTemporaryDirectory();
          tempDir1->cd();

          TH1D *tmphist_Predicted = (TH1D *)hist_Predicted->Clone();
          TH1D *tmphist_Measured = (TH1D *)hist_Measured->Clone();

          tmphist_Predicted->SetFillColor(colors.at(i));
          tmphist_Predicted->SetLineColor(colors.at(i));

          if(!hist_summed_Predicted){
            hist_summed_Predicted = (TH1D *)hist_Predicted->Clone();
            hist_summed_Measured = (TH1D *)hist_Measured->Clone();
          }
          else{
            hist_summed_Predicted->Add(tmphist_Predicted);
            hist_summed_Measured->Add(tmphist_Measured);
          }

          stack_summed_Predicted->Add(tmphist_Predicted);

          origDir->cd();

          file_Measured->Close();
          file_Predicted->Close();

        } // END sample loop

        if(!hist_summed_Predicted){
          delete hist_binned_Predicted;
          delete hist_binned_Measured;
          continue;
        }

        TCanvas *c_summed = new TCanvas("c_summed", "", 600, 600);
        c_summed->Draw();
        TPad *c1_up;
        TPad *c1_down;
        c1_up = new TPad("c1_up", "", 0, 0.25, 1, 1);
        c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

        canvas_margin(c_summed, c1_up, c1_down);

        c1_up->Draw();
        c1_down->Draw();
        c1_up->cd();

        TH1D *dummy_top = (TH1D *)hist_summed_Predicted->Clone();
        dummy_top->SetLineWidth(0);
        dummy_top->SetLineColor(0);
        dummy_top->SetMarkerSize(0);
        dummy_top->SetMarkerColor(0);
        double y_max = max( GetMaximum(hist_summed_Predicted), GetMaximum(hist_summed_Measured) );
        dummy_top->GetYaxis()->SetRangeUser(0., y_max*1.2);
        dummy_top->GetYaxis()->SetTitle("Events");
        dummy_top->Draw("hist");

        if(var.Contains("leadingLepton_Pt")) dummy_top->GetXaxis()->SetRangeUser(0, 150);
        if(var.Contains("secondLepton_Pt")) dummy_top->GetXaxis()->SetRangeUser(0, 70);
        if(channel=="EMu"){
          if(var.Contains("leadingLepton_Pt")) dummy_top->GetXaxis()->SetRangeUser(0, 70);
          if(var.Contains("secondLepton_Pt")) dummy_top->GetXaxis()->SetRangeUser(0, 70);
        }
        if(var.Contains("PFMET")) dummy_top->GetXaxis()->SetRangeUser(0, 200);
        if(var.Contains("weight_fr")) dummy_top->GetXaxis()->SetRangeUser(-0.2, 0.2);

        stack_summed_Predicted->Draw("histsame");

        hist_summed_Predicted->SetMarkerColorAlpha(kAzure-9, 0);
        hist_summed_Predicted->SetFillStyle(3013);
        hist_summed_Predicted->SetFillColor(kBlack);
        hist_summed_Predicted->SetLineColor(0);
        hist_summed_Predicted->Draw("sameE2");

        hist_summed_Measured->Draw("pe1same");

        lg->Draw();

        c1_down->cd();

        TH1D *bottom_point = (TH1D *)hist_summed_Measured->Clone();
        TH1D *bottom_error = (TH1D *)hist_summed_Predicted->Clone();

        //cout << channel << "\t" << regions.at(k) << "\t" << var << endl;
        for(int a=1; a<=hist_summed_Measured->GetXaxis()->GetNbins(); a++){

          if(hist_summed_Predicted->GetBinContent(a)==0) continue;

          //cout << "hist_summed_Measured->GetBinContent(a) = " << hist_summed_Measured->GetBinContent(a) << endl;
          //cout << "hist_summed_Predicted->GetBinContent(a) = " << hist_summed_Predicted->GetBinContent(a) << endl;

          bottom_point->SetBinContent( a, hist_summed_Measured->GetBinContent(a)/hist_summed_Predicted->GetBinContent(a));
          bottom_point->SetBinError( a, hist_summed_Measured->GetBinError(a)/hist_summed_Predicted->GetBinContent(a));

          bottom_error->SetBinContent( a, 1. );
          bottom_error->SetBinError( a, hist_summed_Predicted->GetBinError(a)/hist_summed_Predicted->GetBinContent(a));

          //cout << "==>" << endl;
          //cout << "bottom_point->GetBinContent(a) =  " << bottom_point->GetBinContent(a) << endl;
          //cout << "bottom_point->GetBinError(a) =  " << bottom_point->GetBinError(a) << endl;
          //cout << "bottom_error->GetBinContent(a) =  " << bottom_error->GetBinContent(a) << endl;
          //cout << "bottom_error->GetBinError(a) =  " << bottom_error->GetBinError(a) << endl;

        }   

        TH1D *dummy_bottom = (TH1D *)bottom_error->Clone();
        dummy_bottom->SetLineWidth(0);
        dummy_bottom->SetLineColor(0);
        dummy_bottom->SetFillColor(0);
        dummy_bottom->SetFillStyle(0);
        dummy_bottom->SetMarkerSize(0);
        dummy_bottom->SetMarkerColor(0);
        dummy_bottom->SetMaximum(1.5);
        dummy_bottom->SetMinimum(0.5);
        dummy_bottom->GetXaxis()->SetTitle(xtitle.at(j));
        dummy_bottom->SetYTitle("#frac{Meas.}{Pred.}");
        if(var.Contains("leadingLepton_Pt")) dummy_bottom->GetXaxis()->SetRangeUser(0, 150);
        if(var.Contains("secondLepton_Pt")) dummy_bottom->GetXaxis()->SetRangeUser(0, 70);
        if(channel=="EMu"){
          if(var.Contains("leadingLepton_Pt")) dummy_bottom->GetXaxis()->SetRangeUser(0, 70);
          if(var.Contains("secondLepton_Pt")) dummy_bottom->GetXaxis()->SetRangeUser(0, 70);
        }
        if(var.Contains("PFMET")) dummy_bottom->GetXaxis()->SetRangeUser(0, 200);
        if(var.Contains("weight_fr")) dummy_bottom->GetXaxis()->SetRangeUser(-0.2, 0.2);
        hist_axis(dummy_top, dummy_bottom);
        dummy_bottom->Draw("hist");

        bottom_error->SetFillColor(kOrange);
        bottom_error->SetMarkerSize(0);
        bottom_error->SetMarkerStyle(0);
        bottom_error->SetLineColor(kWhite);
        bottom_error->Draw("e2same");

        bottom_point->Draw("PE1same");

        g1->Draw("same");

        //==== write lumi on the top
        c_summed->cd();
        TLatex latex_CMSPriliminary, latex_Lumi;
        latex_CMSPriliminary.SetNDC();
        latex_Lumi.SetNDC();
        latex_CMSPriliminary.SetTextSize(0.035);
        latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
        latex_Lumi.SetTextSize(0.035);
        latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

        TString str_channel = regions.at(k);
        TLatex channelname;
        channelname.SetNDC();
        channelname.SetTextSize(0.037);
        channelname.DrawLatex(0.2, 0.88, str_channel);

        gSystem->mkdir(plotpath+"/"+channel+"/Stacked/"+regions.at(k), kTRUE);
        c_summed->SaveAs(plotpath+"/"+channel+"/Stacked/"+regions.at(k)+"/"+var+".pdf");
        c_summed->SaveAs(plotpath+"/"+channel+"/Stacked/"+regions.at(k)+"/"+var+".png");
        c_summed->Close();


        //==== Binned

        if(var=="Nevents"){

          TCanvas *c_binned = new TCanvas("c_binned", "", 600, 600);

          TPad *c1_binned_up;
          TPad *c1_binned_down;
          c1_binned_up = new TPad("c1_binned_up", "", 0, 0.25, 1, 1);
          c1_binned_down = new TPad("c1_binned_down", "", 0, 0, 1, 0.25);

          canvas_margin(c_binned, c1_binned_up, c1_binned_down);

          c1_binned_up->Draw();
          c1_binned_down->Draw();
          c1_binned_up->cd();

          hist_binned_Predicted->SetFillColor(kOrange);
          hist_binned_Predicted->SetLineColor(kOrange);
          hist_binned_Measured->SetMarkerStyle(20);

          //TH1D *dummy_binned = new TH1D("dummy_binned", "", );

          hist_binned_Predicted->Draw("hist");
          hist_axis(hist_binned_Predicted);
          hist_binned_Measured->Draw("pe1same");

          double y_max = max(GetMaximum(hist_binned_Predicted), GetMaximum(hist_binned_Predicted));
          hist_binned_Predicted->GetYaxis()->SetRangeUser(0, 1.2*y_max);
          hist_binned_Predicted->GetYaxis()->SetTitle("Events");

          TH1D *hist_binned_Predicted_err = (TH1D *)hist_binned_Predicted->Clone();
          hist_binned_Predicted_err->SetMarkerColorAlpha(kAzure-9, 0);
          hist_binned_Predicted_err->SetFillStyle(3013);
          hist_binned_Predicted_err->SetFillColor(kBlack);
          hist_binned_Predicted_err->SetLineColor(0);
          hist_binned_Predicted_err->Draw("sameE2");

          //==== bottom

          c1_binned_down->cd();

          TH1D *bottom_binned_point = (TH1D *)hist_binned_Measured->Clone();
          TH1D *bottom_binned_error = (TH1D *)hist_binned_Predicted->Clone();

          for(int a=1; a<=hist_binned_Measured->GetXaxis()->GetNbins(); a++){

            if(hist_binned_Predicted->GetBinContent(a)==0) continue;


            bottom_binned_point->SetBinContent( a, hist_binned_Measured->GetBinContent(a)/hist_binned_Predicted->GetBinContent(a));
            bottom_binned_point->SetBinError( a, hist_binned_Measured->GetBinError(a)/hist_binned_Predicted->GetBinContent(a));

            bottom_binned_error->SetBinContent( a, 1. );
            bottom_binned_error->SetBinError( a, hist_binned_Predicted->GetBinError(a)/hist_binned_Predicted->GetBinContent(a));

          }

          TH1D *dummy_bottom_binned = new TH1D("dummy_bottom_binned", "", n_samples, 0., 1.*n_samples);
          dummy_bottom_binned->SetLineWidth(0);
          dummy_bottom_binned->SetLineColor(0);
          dummy_bottom_binned->SetFillColor(0);
          dummy_bottom_binned->SetFillStyle(0);
          dummy_bottom_binned->SetMarkerSize(0);
          dummy_bottom_binned->SetMarkerColor(0);
          dummy_bottom_binned->SetMaximum(1.5);
          dummy_bottom_binned->SetMinimum(0.5);
          dummy_bottom_binned->GetXaxis()->SetTitle(xtitle.at(j));
          dummy_bottom_binned->SetYTitle("#frac{Meas.}{Pred.}");
          hist_axis(hist_binned_Predicted, dummy_bottom_binned);
          dummy_bottom_binned->Draw("hist");
          for(int aaa=0;aaa<samplesalias.size();aaa++){
            dummy_bottom_binned->GetXaxis()->SetBinLabel(aaa+1, samplesalias.at(aaa));
          }
          dummy_bottom_binned->GetXaxis()->SetLabelSize(0.25);
          dummy_bottom_binned->GetXaxis()->SetTitle(0);

          bottom_binned_error->SetFillColor(kOrange);
          bottom_binned_error->SetMarkerSize(0);
          bottom_binned_error->SetMarkerStyle(0);
          bottom_binned_error->SetLineColor(kWhite);
          bottom_binned_error->Draw("e2same");

          bottom_binned_point->Draw("PE1same");

          g1->Draw("same");


          //==== legend

          c1_binned_up->cd();

          TLegend *lg_binned = new TLegend(0.2, 0.5, 0.5, 0.8);
          lg_binned->SetFillStyle(0);
          lg_binned->SetBorderSize(0);
          lg_binned->AddEntry(hist_binned_Measured, "Measured", "pe");
          lg_binned->AddEntry(hist_binned_Predicted, "Predicted", "f");
          lg_binned->Draw();

          //==== latex

          c_binned->cd();
          TLatex latex_CMSPriliminary, latex_Lumi;
          latex_CMSPriliminary.SetNDC();
          latex_Lumi.SetNDC();
          latex_CMSPriliminary.SetTextSize(0.035);
          latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
          latex_Lumi.SetTextSize(0.035);
          latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

          TString str_channel = channelsForLatex.at(l);
          TLatex channelname;
          channelname.SetNDC();
          channelname.SetTextSize(0.037);
          channelname.DrawLatex(0.2, 0.88, str_channel);

          gSystem->mkdir(plotpath+"/"+channel+"/Binned/"+regions.at(k), kTRUE);
          c_binned->SaveAs(plotpath+"/"+channel+"/Binned/"+regions.at(k)+"/OneBinned.pdf");
          c_binned->SaveAs(plotpath+"/"+channel+"/Binned/"+regions.at(k)+"/OneBinned.png");

          c_binned->Close();
          delete dummy_bottom_binned;

        }

        delete hist_binned_Predicted;
        delete hist_binned_Measured;

        

        //cout << "==> " << var << " END" << endl;

      } // END var loop


      delete hist_allsample_measured;
      delete hist_allsample_predicted;

    } // END mm,ee,em loop


  } // END region loop






}
















