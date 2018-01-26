#include "RunNtupleForBinnedYieldPlot.C"
#include "canvas_margin.h"
#include "AnalysisInputs.h"
#include "mylib.h"

void GetMCNormSF(bool DoNorm=false){

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/Regions2/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/MCNormSF/";

  gSystem->mkdir(plotpath,kTRUE);

  AnalysisInputs analysisInputs;
  analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  double FakeSyst = analysisInputs.CalculatedSysts["FakeLooseID"];
  double LumiSyst = analysisInputs.CalculatedSysts["Luminosity"];

  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> MCsector_first_index;

  map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ"};
  map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  map_sample_string_to_list["Zgamma"] = {"ZGto2LG"};
  map_sample_string_to_list["Wgamma"] = {"WGtoLNuG"};
  map_sample_string_to_list["tgamma"] = {"TG", "TTG"};
  map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  
  map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  map_sample_string_to_legendinfo["Zgamma"] = make_pair("Z + #gamma", kViolet);
  map_sample_string_to_legendinfo["Wgamma"] = make_pair("W + #gamma", kOrange);
  map_sample_string_to_legendinfo["tgamma"] = make_pair("top + #gamma", kSpring-7);
  map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Non-prompt", 870);
  map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Non-prompt", 870);
  map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Non-prompt", 870);
  map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Non-prompt", 870);
  map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Non-prompt", 870);
  map_sample_string_to_legendinfo["chargeflip"] = make_pair("Charge-flip", kYellow);

  vector<TString> samples_to_use = {"WZ_excl", "Wgamma", "ZZ_excl", "Zgamma", "fake_Dijet", "tgamma", "VVV", "top"};

  TLegend *lg = new TLegend(0.69, 0.20, 0.96, 0.92);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  //==== error bar
  TH1D *histtmperr = new TH1D("histtmperr", "", 1, 0., 1.);
  histtmperr->SetMarkerColorAlpha(kAzure-9, 0);
  histtmperr->SetFillStyle(3013);
  histtmperr->SetFillColor(kBlack);
  histtmperr->SetLineColor(0);
  lg->AddEntry(histtmperr, "Stat.+Syst. Uncert.", "f");
  //==== Data
  TH1D *histtmpdata = new TH1D("histtmpdata", "", 1, 0., 1.);
  histtmpdata->SetMarkerStyle(20);
  histtmpdata->SetMarkerSize(1.6);
  histtmpdata->SetMarkerColor(kBlack);
  histtmpdata->SetLineColor(kBlack);
  lg->AddEntry(histtmpdata, "data", "ple");
  
  for(int i=samples_to_use.size()-1; i>=0; i--){
    TH1D *histtmp = new TH1D(samples_to_use.at(i), "", 1, 0., 1.);
    histtmp->SetLineColor(map_sample_string_to_legendinfo[samples_to_use.at(i)].second);
    histtmp->SetFillColor(map_sample_string_to_legendinfo[samples_to_use.at(i)].second);
    lg->AddEntry(histtmp, map_sample_string_to_legendinfo[samples_to_use.at(i)].first, "f");
  }

  vector<TString> samples;
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    MCsector_first_index.push_back( samples.size() );
    samples.insert(samples.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<samples.size(); i++) cout << " " << i << "\t" << samples.at(i) << endl;
  cout << "MCsector_first_index :" << endl;
  for(unsigned int i=0; i<MCsector_first_index.size(); i++) cout << " " << MCsector_first_index.at(i) << endl;
  analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", samples);

  vector<TString> regions = {
    "DiLepton_ThreeLepton_WZ",
    "DiLepton_ThreeLepton_ZGamma",
    "DiLepton_FourLepton_ZZ",
  };
  const int nCR = regions.size();

  vector< vector<TString> > vec_TargetSamples = {
    {"WZTo3LNu_powheg"},
    {"ZGto2LG"},
    {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ"},
  };
  vector<TString> SampleNames = {
    "WZ",
    "Z#gamma",
    "ZZ",
  };

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

  TH1D *hist_empty = new TH1D("hist_empty", "", nCR, 0., 1.*nCR);
  hist_empty->GetYaxis()->SetTitle("Entries"); //FIXME
  hist_empty->SetLineWidth(0);
  hist_empty->SetLineColor(0);
  hist_empty->SetMarkerSize(0);
  hist_empty->SetMarkerColor(0);
  hist_empty->GetYaxis()->SetRangeUser(0., 2000.);
  hist_empty->Draw("hist");

  double x_1[2], y_1[2];
  x_1[0] = 1000;  y_1[0] = 1;
  x_1[1] = -1000;  y_1[1] = 1;
  TGraph *g1 = new TGraph(2, x_1, y_1);

  TH1D *hist_data = new TH1D("hist_data", "", nCR, 0., 1.*nCR);

  hist_data->SetMarkerStyle(20);
  hist_data->SetMarkerSize(1.6);

  THStack *this_stack = new THStack("this_stack", "");
  TH1D *MC_stacked_allerr = new TH1D("MC_stacked_allerr", "", nCR, 0., 1.*nCR);
  MC_stacked_allerr->SetMarkerColorAlpha(kAzure-9, 0);
  MC_stacked_allerr->SetFillStyle(3013);
  MC_stacked_allerr->SetFillColor(kBlack);
  MC_stacked_allerr->SetLineColor(0);

  TH1D *MC_stacked_staterr = new TH1D("MC_stacked_staterr", "", nCR, 0., 1.*nCR);

  TMatrix matrixA(nCR, nCR);
  TMatrix matrixA_err(nCR, nCR);
  TMatrix matrixD(nCR, 1);
  TMatrix matrixD_nonsig(nCR, 1);
  TMatrix matrixC(nCR, 1);
  TMatrix matrixC_err(nCR, 1);

  for(unsigned int it_region=0; it_region<regions.size(); it_region++){

    TString region = regions.at(it_region);

    vector<TString> TargetSamples = vec_TargetSamples.at(it_region);

    cout << "## "<<region<<" ##" << endl;

    double y_total_data(0.), y_total_bkgd(0.);
    double e_total_data(0.), e_total_bkgd(0.);
    vector<double> matrixA_rows = {0., 0., 0., 0.};
    vector<double> matrixA_err_rows = {0., 0., 0., 0.};
    double y_non_signal(0.);
    double e_non_signal(0.);

    //==== Data by hand

    TFile *file_data = new TFile(filepath+"/DiLeptonAnalyzer_CR_data_DiLepton_cat_"+catversion+".root");
    TString histname = region+"/Nevents_"+region;
    TH1D *thishist_data = (TH1D *)file_data->Get(histname);

    y_total_data = thishist_data->GetBinContent(1);
    e_total_data = thishist_data->GetBinError(1);

    y_non_signal += y_total_data;
    e_non_signal += e_total_data*e_total_data;

    hist_data->SetBinContent(it_region+1, y_total_data);
    hist_data->SetBinError(it_region+1, e_total_data);

    file_data->Close();

    //==== Bkgd
    for(unsigned int it_sample=0; it_sample<samples.size(); it_sample++){

      TString sample = samples.at(it_sample);

      TString current_MCsector = samples_to_use.back();
      for(unsigned int i=0; i<MCsector_first_index.size()-1; i++){
        if(MCsector_first_index.at(i) <= it_sample && it_sample < MCsector_first_index.at(i+1)){
          current_MCsector = samples_to_use.at(i);
          break;
        }
      }

      Color_t thiscolor = map_sample_string_to_legendinfo[current_MCsector].second;

      TString filename = "DiLeptonAnalyzer_CR_SK"+sample+"_dilep_cat_"+catversion+".root";
      if(sample.Contains("fake")) filename = "DiLeptonAnalyzer_CR_SKfake_Dijet_DiLepton_dilep_cat_"+catversion+".root";
      TFile *file = new TFile(filepath+"/"+filename);

      TH1D *original_hist = (TH1D *)file->Get(histname);
      if(!original_hist) continue;
      if(original_hist->GetBinContent(1)<0) continue;

      //==== Scale MCSF
      if( DoNorm && !sample.Contains("fake") ){
        original_hist->Scale(analysisInputs.MCNormSF[sample]);
      }

      //===================================
      //==== Set Stat Error Here (fake..)
      //===================================

/*
      //==== Stat Error Propations for Fake
      if( sample.Contains("fake") ){
        TH1D *original_hist_up = (TH1D *)file->Get(region+"_up/Nevents_"+region+"_up");
        double error_propagated = original_hist_up->GetBinContent(1)-original_hist->GetBinContent(1);
        double error_sumw2 = original_hist->GetBinError(1);
        double error_combined = sqrt( error_propagated*error_propagated + error_sumw2*error_sumw2 );

        original_hist->SetBinError(1, error_combined);
      }
*/

      TH1D *new_hist = new TH1D("new_hist", "", nCR, 0., 1.*nCR);
      new_hist->SetBinContent(it_region+1, original_hist->GetBinContent(1));
      new_hist->SetBinError(it_region+1, original_hist->GetBinError(1));
      new_hist->SetFillColor( thiscolor );
      new_hist->SetLineColor( thiscolor );
      MC_stacked_staterr->Add(new_hist);

      //======================
      //==== Add Systematics
      //======================

      if( sample.Contains("fake") ){
        double error_stat = original_hist->GetBinError(1);
        double error_syst = FakeSyst*(original_hist->GetBinContent(1));
        double error_combined = sqrt( error_stat*error_stat+error_syst*error_syst );

        original_hist->SetBinError(1, error_combined);
      }
      else{
        TH1D *thishist_systyields = (TH1D *)file->Get("Systematics/Yields_"+region);

        double error_stat = original_hist->GetBinError(1);
        double error_syst = GetYieldSystematics(thishist_systyields);

        double error_lumi = LumiSyst*(original_hist->GetBinContent(1));

        double error_combined = sqrt( error_stat*error_stat + error_syst*error_syst + error_lumi*error_lumi );

        original_hist->SetBinError(1, error_combined);

        cout << sample << "\t" << error_stat << "\t" << error_syst << "\t" << error_lumi << endl;

      }

      new_hist->SetBinContent(it_region+1, original_hist->GetBinContent(1));
      new_hist->SetBinError(it_region+1, original_hist->GetBinError(1));

      this_stack->Add(new_hist);
      MC_stacked_allerr->Add(new_hist);

      int signal_index = -1;
      for(unsigned int l=0; l<vec_TargetSamples.size(); l++){
        if( std::find( vec_TargetSamples.at(l).begin(), vec_TargetSamples.at(l).end(), sample ) != vec_TargetSamples.at(l).end() ) signal_index = l;
      }

      if(signal_index!=-1){
        matrixA_rows.at(signal_index) += original_hist->GetBinContent(1);
        matrixA_err_rows.at(signal_index) += (original_hist->GetBinError(1))*(original_hist->GetBinError(1));
      }
      else{
        y_non_signal -= original_hist->GetBinContent(1);
        e_non_signal += (original_hist->GetBinError(1))*(original_hist->GetBinError(1));
      }

    } // END loop samples

    for(unsigned int l=0; l<vec_TargetSamples.size(); l++){
      matrixA(it_region, l) = matrixA_rows.at(l);
      matrixA_err(it_region, l) = sqrt(matrixA_err_rows.at(l));
    }
    matrixC(it_region, 0) = y_non_signal;
    matrixC_err(it_region, 0) = e_non_signal;
    matrixD(it_region, 0) = y_total_data;

  } // END loop regions

  c1_up->cd();
  this_stack->Draw("histsame");
  MC_stacked_allerr->Draw("sameE2");
  cout << MC_stacked_allerr->GetBinContent(1) << endl;
  cout << MC_stacked_allerr->GetBinContent(2) << endl;
  cout << MC_stacked_allerr->GetBinContent(3) << endl;
  hist_data->Draw("PE1same");
  hist_data->SetLineWidth(2);
  cout << hist_data->GetBinContent(1) << endl;
  cout << hist_data->GetBinContent(2) << endl;
  cout << hist_data->GetBinContent(3) << endl;
  lg->Draw();

  c1_down->cd();
  TH1D *ratio_point = (TH1D *)hist_data->Clone();
  TH1D *ratio_staterr = (TH1D *)hist_data->Clone();
  TH1D *ratio_allerr = (TH1D *)hist_data->Clone();
  for(int i=1; i<=ratio_point->GetXaxis()->GetNbins(); i++){
    //==== FIXME for zero? how?
    if(MC_stacked_allerr->GetBinContent(i)!=0){
    //==== ratio point
    ratio_point->SetBinContent( i, ratio_point->GetBinContent(i) / MC_stacked_allerr->GetBinContent(i) );
    ratio_point->SetBinError  ( i, ratio_point->GetBinError(i)   / MC_stacked_allerr->GetBinContent(i) );
    //==== ratio staterr
    ratio_staterr->SetBinContent( i, 1. );
    ratio_staterr->SetBinError( i, MC_stacked_staterr->GetBinError(i)/ MC_stacked_staterr->GetBinContent(i) );
    //==== ratio allerr
    ratio_allerr->SetBinContent( i, 1. );
    ratio_allerr->SetBinError( i, MC_stacked_allerr->GetBinError(i)/ MC_stacked_allerr->GetBinContent(i) );
    }
  }
  ratio_allerr->SetMaximum(1.2);
  ratio_allerr->SetMinimum(0.8);
  //ratio_allerr->GetXaxis()->SetTitle("Control Regions");
  ratio_allerr->SetYTitle("#frac{Obs.}{Pred.}");
  ratio_allerr->SetFillColor(kOrange);
  ratio_allerr->SetMarkerSize(0);
  ratio_allerr->SetMarkerStyle(0);
  ratio_allerr->SetLineColor(kWhite);
  ratio_allerr->Draw("E2same");
  for(int i=0; i<SampleNames.size(); i++){
    ratio_allerr->GetXaxis()->SetBinLabel(i+1, SampleNames.at(i));
  }

  hist_axis(hist_empty, ratio_allerr);
  ratio_allerr->GetXaxis()->SetLabelSize(0.25);

  ratio_staterr->SetFillColor(kCyan);
  ratio_staterr->SetMarkerSize(0);
  ratio_staterr->SetMarkerStyle(0);
  ratio_staterr->SetLineColor(kWhite);
  ratio_staterr->Draw("E2same");

  ratio_point->Draw("PE1same");

  if(!DoNorm){
    c1->SaveAs(plotpath+"/BeforeNorm.pdf");
    c1->SaveAs(plotpath+"/BeforeNorm.png");
  }
  else{
    c1->SaveAs(plotpath+"/AfterNorm.pdf");
    c1->SaveAs(plotpath+"/AfterNorm.png");
  }
  c1->Close();

  for(unsigned int i=0; i<nCR; i++){
    matrixC_err(i,0) = sqrt(matrixC_err(i,0));
  }

  cout << "#####################" << endl;
  cout << "## Solving A*B = C ##" << endl;
  cout << "#####################" << endl << endl;;
  cout << "##############" << endl;
  cout << "## Matrix A ##" << endl;
  cout << "##############" << endl;
  matrixA.Print();
  cout << "##################" << endl;
  cout << "## Matrix A_err ##" << endl;
  cout << "##################" << endl;
  matrixA_err.Print();
  cout << "##############" << endl;
  cout << "## Matrix D ##" << endl;
  cout << "##############" << endl;
  matrixD.Print();
  cout << "##############" << endl;
  cout << "## Matrix C ##" << endl;
  cout << "##############" << endl;
  matrixC.Print();
  cout << "##################" << endl;
  cout << "## Matrix C_err ##" << endl;
  cout << "##################" << endl;
  matrixC_err.Print();

  TMatrix inverse(TMatrix::kInverted, matrixA);
  cout << "###################" << endl;
  cout << "## Matrix A^(-1) ##" << endl;
  cout << "###################" << endl;
  inverse.Print();

  cout << "## Calculating B ##" << endl;
  TMatrix matrixB(nCR, 1);
  TMatrix matrixB_err1(nCR, 1);

  for(unsigned int i=0; i<nCR; i++){
    matrixB(i,0) = 0.;
    matrixB_err1(i, 0) = 0.;
  }
  for(unsigned int i=0; i<nCR; i++){
    for(unsigned int j=0; j<nCR; j++){
      matrixB(i,0) += inverse(i,j)*matrixC(j,0);
      matrixB_err1(i,0) += inverse(i,j)*matrixC_err(j,0);
    }
  }

  cout << "##############" << endl;
  cout << "## Matrix B ##" << endl;
  cout << "##############" << endl;
  matrixB.Print();
  cout << "###################" << endl;
  cout << "## Matrix B_err1 ##" << endl;
  cout << "###################" << endl;
  matrixB_err1.Print();

  //==== B = invA*C + invA*dC - invA*(dA)*B
  TMatrix matrixB_err2(nCR,1);
  TMatrix matrixinvAdA(nCR, nCR);
  for(unsigned int i=0; i<nCR; i++){
    for(unsigned int j=0; j<nCR; j++){
      for(unsigned int k=0; k<nCR; k++){
        matrixinvAdA(i,0) += inverse(i,k)*matrixA_err(k,j);
      }
    }
  }
  for(unsigned int i=0; i<nCR; i++){
    for(unsigned int j=0; j<nCR; j++){
      matrixB_err2(i,0) += matrixinvAdA(i,j)*matrixB(j,0);
    }
  }

  cout << "###################" << endl;
  cout << "## Matrix B_err2 ##" << endl;
  cout << "###################" << endl;
  matrixB_err2.Print();

  TMatrix matrixB_allerr(nCR,1);
  for(unsigned int i=0; i<nCR; i++){
    double e1 = matrixB_err1(i,0);
    double e2 = matrixB_err2(i,0);
    matrixB_allerr(i,0) = sqrt(e1*e1+e2*e2);
  }

  cout << "#####################" << endl;
  cout << "## Matrix B_allerr ##" << endl;
  cout << "#####################" << endl;
  matrixB_allerr.Print();

  //====  matrixB, matrixB_allerr
  for(unsigned int i=0; i<vec_TargetSamples.size(); i++){

    vector<TString> signal = vec_TargetSamples.at(i);

    for(unsigned int j=0; j<signal.size(); j++){

      cout << signal.at(j) << " " << matrixB(i,0) << " " << matrixB_allerr(i,0) << endl;

    }

  }


  TMatrix Check(nCR,1);
  for(unsigned int i=0; i<nCR; i++){
    for(unsigned int j=0; j<nCR; j++){
      Check(i,0) += matrixA(i,j)*matrixB(j,0);
    }
  }
  Check.Print();



}



