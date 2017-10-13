#include "canvas_margin.h"
#include "AnalysisInputs.h"

void GetMCNormSF(){

  bool DoNorm = false;

  gStyle->SetOptStat(0);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_PLOT_PATH+"/"+dataset+"/Regions2/CR/use_FR_method/fake_Dijet/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/MCNormSF/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  AnalysisInputs analysisInputs;
  analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  double FakeSyst = analysisInputs.CalculatedSysts["FakeLooseID"];
  cout << "FakeSyst = " << FakeSyst << endl;

  vector<TString> regions = {
    "WZ",
    "ZGamma",
    "ZZ"
  };

  vector< vector<TString> > subregions  = {

    {"DiElectron_ThreeLepton_WZ", "DiMuon_ThreeLepton_WZ"},
    {"DiElectron_ThreeLepton_ZGamma", "DiMuon_ThreeLepton_ZGamma"},
    {"DiElectron_FourLepton_ZZ_NotAllSameFlavour", "DiElectron_FourLepton_ZZ_AllSameFlavour", "DiMuon_FourLepton_ZZ_AllSameFlavour"},

  };

  vector< vector<TString> > signals = {
    {"WZTo3LNu_powheg"},
    {"ZGto2LG"},//, "WGtoLNuG"},
    //{"WZTo3LNu_mllmin01"},
    //{"ZGto2LG"},
    {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"},
  };

  vector< double > SFs = {
    0.9761,
    0.8256,
    0.9225,
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

  TH1D *hist_empty = new TH1D("hist_empty", "", 3, 0., 3.);
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


  TH1D *hist_data = new TH1D("hist_empty", "", 3, 0., 3.);

  hist_data->SetMarkerStyle(20);
  hist_data->SetMarkerSize(1.6);

  THStack *this_stack = new THStack("this_stack", "");
  TH1D *MC_stacked_allerr = new TH1D("MC_stacked_allerr", "", 3, 0., 3);
  MC_stacked_allerr->SetMarkerColorAlpha(kAzure-9, 0);
  MC_stacked_allerr->SetFillStyle(3013);
  MC_stacked_allerr->SetFillColor(kBlack);
  MC_stacked_allerr->SetLineColor(0);

  TH1D *MC_stacked_staterr = new TH1D("MC_stacked_staterr", "", 3, 0., 3);

  TLegend *lg = NULL;

  TMatrix matrixA(3, 3);
  TMatrix matrixA_err(3, 3);
  TMatrix matrixD(3, 1);
  TMatrix matrixD_nonsig(3, 1);
  TMatrix matrixC(3, 1);
  TMatrix matrixC_err(3, 1);

  for(unsigned int i=0; i<regions.size(); i++){

    TString region = regions.at(i);
    vector<TString> subregion = subregions.at(i);

    cout << "## "<<region<<" ##" << endl;

    double y_total_data(0.), y_total_bkgd(0.);
    double e_total_data(0.), e_total_bkgd(0.);
    vector<double> matrixA_rows = {0., 0., 0.};
    vector<double> matrixA_err_rows = {0., 0., 0.};
    double y_non_signal(0.);
    double e_non_signal(0.);

    //map<TString, TH1D *> map_hists;
    map<Color_t, TH1D *> map_hists;

    for(unsigned int j=0; j<subregion.size(); j++){

      TString fullfilename = "";
      if(DoNorm) fullfilename = filepath+"MCNormSFed_"+subregion.at(j)+"/hists.root";
      else fullfilename = filepath+"_"+subregion.at(j)+"/hists.root";

      TFile *file = new TFile(fullfilename);
      TCanvas *c1 = (TCanvas*)file->Get("Nevents");
      TPad *pad = (TPad*)c1->GetPrimitive("c1");
      TPad *pad_down = (TPad*)c1->GetPrimitive("c1_down");

      //==== Get Legend
      if(!lg){
        lg = (TLegend *)pad->GetPrimitive("TPave");
      }

      //==== Read Top Histograms
      TH1D *data = (TH1D*)pad->GetPrimitive("Nevents_"+subregion.at(j)+"_data");

      TH1D *bkgd = (TH1D*)pad->GetPrimitive("MC_stacked_allerr");

      double y_data = data->GetBinContent(1);
      double y_bkgd = bkgd->GetBinContent(1);

      double e_data = data->GetBinError(1);
      double e_bkgd = bkgd->GetBinError(1);

      y_total_data += y_data;
      y_total_bkgd += y_bkgd;
      y_non_signal += y_data;
      e_non_signal += e_data*e_data;

      e_total_data += e_data*e_data;
      e_total_bkgd += e_bkgd*e_bkgd;

      //==== Read Bottom Histgrams

      TH1D *original_allerr = (TH1D*)pad_down->GetPrimitive("Nevents_"+subregion.at(j)+"_data_allerr");
      TH1D *original_staterr = (TH1D*)pad_down->GetPrimitive("Nevents_"+subregion.at(j)+"_data_staterr");
      original_allerr->Scale(y_bkgd);
      original_staterr->Scale(y_bkgd);

      TH1D *new_allerr = new TH1D("new_allerr", "", 3, 0., 3);
      TH1D *new_staterr = new TH1D("new_staterr", "", 3, 0., 3);

      new_allerr->SetBinContent(i+1, original_allerr->GetBinContent(1));
      new_allerr->SetBinError(i+1, original_allerr->GetBinError(1));
      new_staterr->SetBinContent(i+1, original_staterr->GetBinContent(1));
      new_staterr->SetBinError(i+1, original_staterr->GetBinError(1));

      MC_stacked_allerr->Add( new_allerr );
      MC_stacked_staterr->Add( new_staterr );

      //cout << e_bkgd << "\t" << hist_allerr->GetBinError(1) << endl;

      THStack *MC_stacked = (THStack *)pad->GetPrimitive("MC_stacked");
      TList *bkgdlist = MC_stacked->GetHists();
      for(int k=0; k<bkgdlist->Capacity(); k++){

        TH1D *new_hist = new TH1D("new_hist", "", 3, 0., 3);
        TH1D *original_hist = (TH1D*)bkgdlist->At(k);

        TString this_name = original_hist->GetName();
        if(this_name.Contains("fake")){
          cout << "FAKE : " << this_name << endl;
          for(int zzz=1; zzz<=original_hist->GetXaxis()->GetNbins(); zzz++){
            double sumw2 = original_hist->GetBinError(zzz);
            double fakesyst = FakeSyst*(original_hist->GetBinContent(zzz));
            original_hist->SetBinError(zzz, sqrt(sumw2*sumw2+fakesyst*fakesyst));
          }
        }
        TString sample = this_name;
        TString suffix = "Nevents_"+subregion.at(j)+"_";
        sample.Remove(0, suffix.Length());

        int signal_index = -1;
        for(unsigned int l=0; l<signals.size(); l++){
          if( std::find( signals.at(l).begin(), signals.at(l).end(), sample ) != signals.at(l).end() ) signal_index = l;
        }

        if(signal_index!=-1){
          matrixA_rows.at(signal_index) += original_hist->GetBinContent(1);
          matrixA_err_rows.at(signal_index) += (original_hist->GetBinError(1))*(original_hist->GetBinError(1));
        }
        else{
          y_non_signal -= original_hist->GetBinContent(1);
          e_non_signal += (original_hist->GetBinError(1))*(original_hist->GetBinError(1));
        }

        //cout << this_name << "\t" << sample << endl;

        new_hist->SetBinContent(i+1, original_hist->GetBinContent(1));
        new_hist->SetBinError(i+1, original_hist->GetBinError(1));
        new_hist->SetFillColor( original_hist->GetFillColor() );
        new_hist->SetLineColor( original_hist->GetLineColor() );
        new_hist->SetName(original_hist->GetName());

/*
        if(!map_hists[sample]){
          map_hists[sample] = (TH1D*)new_hist->Clone();
        }
        else{
          map_hists[sample]->Add(new_hist);
        }
*/

        if(!map_hists[original_hist->GetFillColor()]){
          map_hists[original_hist->GetFillColor()] = (TH1D*)new_hist->Clone();
        }
        else{
          map_hists[original_hist->GetFillColor()]->Add(new_hist);
        }


      } // END Loop bkgd

    } // END Loop subregions

    //for(map<TString, TH1D *>::iterator it = map_hists.begin(); it != map_hists.end(); it++){
    for(map<Color_t, TH1D *>::iterator it = map_hists.begin(); it != map_hists.end(); it++){
      cout << it->second->GetName() << endl;
      this_stack->Add( it->second );
    }

    e_total_data = sqrt(e_total_data);
    e_total_bkgd = sqrt(e_total_bkgd);

    double re_total_data = e_total_data/y_total_data;
    double re_total_bkgd = e_total_bkgd/y_total_bkgd;
    double re_total_sf = re_total_data+re_total_bkgd;

    double y_total_sf = y_total_data/y_total_bkgd;
    double e_total_sf = re_total_sf*y_total_sf;

    hist_data->SetBinContent(i+1, y_total_data);
    hist_data->SetBinError(i+1, e_total_data);

    //cout << region << "\t" << std::fixed<<std::setprecision(3) << y_total_sf << "\t" << e_total_sf << endl;

    for(unsigned int l=0; l<signals.size(); l++){
      matrixA(i, l) = matrixA_rows.at(l);
      matrixA_err(i, l) = sqrt(matrixA_err_rows.at(l));
    }
    matrixC(i, 0) = y_non_signal;
    matrixC_err(i, 0) = e_non_signal;
    matrixD(i, 0) = y_total_data;

  } // END Loop regions

  c1_up->cd();
  this_stack->Draw("histsame");
  MC_stacked_allerr->Draw("sameE2");
  hist_data->Draw("PE1same");
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
  hist_axis(hist_empty, ratio_allerr);

  ratio_staterr->SetFillColor(kCyan);
  ratio_staterr->SetMarkerSize(0);
  ratio_staterr->SetMarkerStyle(0);
  ratio_staterr->SetLineColor(kWhite);
  ratio_staterr->Draw("E2same");

  ratio_point->Draw("PE1same");

  TLegend *lg_ratio = new TLegend(0.2, 0.8, 0.6, 0.9);
  lg_ratio->SetFillStyle(0);
  lg_ratio->SetBorderSize(0);
  lg_ratio->SetNColumns(3);
  lg_ratio->AddEntry(ratio_staterr, "Stat.", "f");
  lg_ratio->AddEntry(ratio_allerr, "Stat.+Syst.", "f");
  lg_ratio->AddEntry(ratio_point, "Obs./Pred.", "p");
  lg_ratio->Draw();

  //==== y=1 line
  g1->Draw("same");

  ratio_allerr->GetXaxis()->SetLabelSize(0.3);
  ratio_allerr->GetXaxis()->SetLabelOffset(0.01);
  ratio_allerr->GetXaxis()->SetBinLabel(1, "WZ");
  ratio_allerr->GetXaxis()->SetBinLabel(2, "Z#gamma");
  ratio_allerr->GetXaxis()->SetBinLabel(3, "ZZ");

  if(!DoNorm) c1->SaveAs(plotpath+"/BeforeNorm.pdf");
  else c1->SaveAs(plotpath+"/AfterNorm.pdf");
  c1->Close();

  for(unsigned int i=0; i<3; i++){
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
  TMatrix matrixB(3, 1);
  TMatrix matrixB_err1(3, 1);

  for(unsigned int i=0; i<3; i++){
    matrixB(i,0) = 0.;
    matrixB_err1(i, 0) = 0.;
  }
  for(unsigned int i=0; i<3; i++){
    for(unsigned int j=0; j<3; j++){
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
  TMatrix matrixB_err2(3,1);
  TMatrix matrixinvAdA(3, 3);
  for(unsigned int i=0; i<3; i++){
    for(unsigned int j=0; j<3; j++){
      for(unsigned int k=0; k<3; k++){
        matrixinvAdA(i,0) += inverse(i,k)*matrixA_err(k,j);
      }
    }
  }
  for(unsigned int i=0; i<3; i++){
    for(unsigned int j=0; j<3; j++){
      matrixB_err2(i,0) += matrixinvAdA(i,j)*matrixB(j,0);
    }
  }

  cout << "###################" << endl;
  cout << "## Matrix B_err2 ##" << endl;
  cout << "###################" << endl;
  matrixB_err2.Print();

  TMatrix matrixB_allerr(3,1);
  for(unsigned int i=0; i<3; i++){
    double e1 = matrixB_err1(i,0);
    double e2 = matrixB_err2(i,0);
    matrixB_allerr(i,0) = sqrt(e1*e1+e2*e2);
  }

  cout << "#####################" << endl;
  cout << "## Matrix B_allerr ##" << endl;
  cout << "#####################" << endl;
  matrixB_allerr.Print();

  //====  matrixB, matrixB_allerr
  for(unsigned int i=0; i<signals.size(); i++){

    vector<TString> signal = signals.at(i);

    for(unsigned int j=0; j<signal.size(); j++){

      cout << signal.at(j) << " " << matrixB(i,0) << " " << matrixB_allerr(i,0) << endl;

    }

  }


  TMatrix Check(3,1);
  for(unsigned int i=0; i<3; i++){
    for(unsigned int j=0; j<3; j++){
      Check(i,0) += matrixA(i,j)*matrixB(j,0);
    }
  }
  Check.Print();


}









