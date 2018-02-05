#include "RunNtupleForBinnedYieldPlot.C"
#include "canvas_margin.h"
#include "AnalysisInputs.h"
#include "mylib.h"

void ForLatex_MakeCRYieldTable(int lepch=0, int CRsection=0){

  TString DataPD = "";
  TString ChannelName = "";
  TString ChannelNameForTex = "";
  TString V2ForTex = "";

  if(lepch==0){
    DataPD = "DoubleMuon";
    ChannelName = "DiMuon";
    ChannelNameForTex = "dimuon";
    V2ForTex = "|V_{N \\mu}|^{2}";
  }
  else if(lepch==1){
    DataPD = "DoubleEG";
    ChannelName = "DiElectron";
    ChannelNameForTex = "dielectron";
    V2ForTex = "|V_{N e}|^{2}";
  }
  else if(lepch==2){
    DataPD = "MuonEG";
    ChannelName = "EMu";
    ChannelNameForTex = "emu";
    V2ForTex = "|V_{N \\ell}|^{2}";
  }

  vector<int> ref_sigs = {50, 100, 200, 500, 1100};
  vector<double> ref_scale = {0.0001, 0.01, 0.01, 0.1, 1};
  vector<TString> ref_scaleForTex = {"0.0001", "0.01", "0.01", "0.1", "1"};

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/Regions/";

  AnalysisInputs analysisInputs;
  analysisInputs.DoPrint = false;
  analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  double FakeSyst = analysisInputs.CalculatedSysts["FakeLooseID"];
  double LumiSyst = analysisInputs.CalculatedSysts["Luminosity"];
  double FlipSyst = analysisInputs.CalculatedSysts["ChrageFlipSyst"];

  vector< vector<TString> > bkglists = {
    {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD",},
    {"ttW", "ttZ", "ttH_nonbb",},
    {"WWW", "WWZ", "WZZ", "ZZZ",},
    {"WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",},
    {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted",},
    {"chargeflip",},
    {"fake_Dijet",},
  };

  vector<TString> allbkgs = {
    "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD",
    "ttW", "ttZ", "ttH_nonbb",
    "WWW", "WWZ", "WZZ", "ZZZ",
    "WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
    "TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted",
    "chargeflip",
    "fake_Dijet",
  };
  analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", allbkgs);

  int index_ENDMC = 4;
  vector<TString> bkgdtypes = {
    "DoubleWW",
    "top",
    "triboson",
    "diboson",
    "$X + \\gamma$",
    "Charge-flip background",
    "Fake lepton background",
  };

  vector<TString> regions, regionsForTex;
  vector<TString> tmp_regions;

  if(CRsection==0){
    tmp_regions = {
      "Inclusive1nlbjets",
      "0jets_0nlbjets_dRllge2p5",
      "LowCR_TwoJet_NoFatJet",
    };
    regionsForTex = {
      "Non-prompt CR1",
      "Non-prompt CR2",
      "Low Mass CR1",
    };
  }
  else if(CRsection==1){
    tmp_regions = {
      "LowCR_OneJet_NoFatJet",
      "HighCR_TwoJet_NoFatJet",
      "HighCR_OneFatJet",
    };
    regionsForTex = {
      "Low Mass CR2",
      "High Mass CR1",
      "High Mass CR2",
    };
  }


  for(unsigned int j=0; j<tmp_regions.size(); j++){

    if(lepch==0) regions.push_back( "DiMuon_"+tmp_regions.at(j)+"_SS" );
    if(lepch==1){
      if(tmp_regions.at(j).Contains("Low") || tmp_regions.at(j).Contains("High")) regions.push_back( "DiElectron_"+tmp_regions.at(j)+"_SS" );
      else regions.push_back( "DiElectron_"+tmp_regions.at(j)+"_OffZ_SS" );
    }
    if(lepch==2) regions.push_back( "EMu_"+tmp_regions.at(j)+"_SS" );

  }

  const int nCR = regions.size();

  cout << "\\begin{table}[!hptb]" << endl;
  cout << "  \\centering" << endl;
  cout << "  \\caption{" << endl;
  cout << "  Observed event yields and estimated backgrounds with statistical and systematic uncertainties for the "+ChannelNameForTex+" events in various control regions." << endl;
  cout << "  The uncertainties shown are the statistical and systematic components, respectively." << endl;
  cout << "  }" << endl;
  cout << "  \\label{table:yield_CR_"+ChannelName+TString::Itoa(CRsection,10)+"}" << endl;
  cout << "  \\begin{center}" << endl;
  cout << "    \\resizebox{\\columnwidth}{!}{" << endl;
  cout << "      \\begin{tabular}{l |";for(int i=0;i<nCR;i++) cout<<" l";cout<<"}" << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "\\hline \\hline" << endl;
  cout << "\\multirow{2}{*}{Source} & \\multicolumn{"<<nCR<<"}{c}{Events} \\\\ \\cline{2-"<<nCR+1<<"}" << endl;
  for(int i=0;i<nCR;i++) cout<<"& "<<regionsForTex.at(i);cout<<" \\\\" << endl;
  cout << "\\hline" << endl;
  cout << "{\\bf Monte Carlo:}    ";for(int i=0;i<nCR;i++) cout<<"& ";cout<<" \\\\" << endl;

  vector<double> MC_yield = {0., 0., 0., 0., 0., 0.};
  vector<double> MC_stat = {0., 0., 0., 0., 0., 0.};
  vector<double> MC_syst = {0., 0., 0., 0., 0., 0.}; //SAME AS # of CHANNEL
  vector<double> Total_yield = {0., 0., 0., 0., 0., 0.};
  vector<double> Total_stat = {0., 0., 0., 0., 0., 0.};
  vector<double> Total_syst = {0., 0., 0., 0., 0., 0.}; //SAME AS # of CHANNEL

  //==== Bkgdlists : each row
  for(unsigned int it_bkglist=0; it_bkglist<bkglists.size(); it_bkglist++){

    vector<TString> samples = bkglists.at(it_bkglist);

    bool isFake = false;
    bool isCF = false;
    bool isMC = false;
    for(unsigned int it_sample=0; it_sample<samples.size(); it_sample++){
      TString sample = samples.at(it_sample);
      if(sample.Contains("fake")){
        isFake = true;
      }
      else if(sample.Contains("chargeflip")){
        isCF = true;
        if(!ChannelName && isCF) continue;
      }
      else{
        isMC = true;
      }
    }

    if(isCF){
      cout << "{\\bf Data-driven background estimate:} & & & \\\\" << endl;
    }
    cout << bkgdtypes.at(it_bkglist);

    for(unsigned int it_region=0; it_region<regions.size(); it_region++){

      TString region = regions.at(it_region);

      //cout << "## " << region << " ##" << endl;

      TString histname = region+"/Nevents_"+region;

      double yield_central(0.), staterror(0.), systerror(0.);
      for(unsigned int it_sample=0; it_sample<samples.size(); it_sample++){

        TString sample = samples.at(it_sample);

        //-- DataPD = "DoubleMuon";
        //-- ChannelName = "DiMuon";

        TString filename = "DiLeptonAnalyzer_SK"+sample+"_dilep_cat_"+catversion+".root";
        if(sample.Contains("fake")){
          filename = "DiLeptonAnalyzer_SKfake_Dijet_"+DataPD+"_dilep_cat_"+catversion+".root";
        }
        else if(sample.Contains("chargeflip")){
          filename = "DiLeptonAnalyzer_SKchargeflip_DoubleEG_dilep_cat_v8-0-7.root";
        }
        else{
        }
        TFile *file = new TFile(filepath+"/"+filename);

        TH1D *original_hist = (TH1D *)file->Get(histname);
        if(!original_hist){
          //cout << endl;
          //cout << filename << "\t" << histname << endl;
          continue;
        }
        if(original_hist->GetBinContent(1)<0) continue;

        //==== Scale MCSF
        double MCSF_uncert = 0.;
        if( isMC ){
          double before_scale = original_hist->GetBinContent(1);
          original_hist->Scale(analysisInputs.MCNormSF[sample]);
          MCSF_uncert = before_scale*(analysisInputs.MCNormSF_uncert[sample]);
          //cout << sample << "\t" << before_scale << "\t" << MCSF_uncert << endl;
        }

        yield_central += original_hist->GetBinContent(1);

/*
        //===================================
        //==== Set Stat Error Here (fake..)
        //===================================

        //==== Stat Error Propations for Fake
        if( sample.Contains("fake") ){
          TH1D *original_hist_up = (TH1D *)file->Get(region+"_up/Nevents_"+region+"_up");
          double error_propagated = original_hist_up->GetBinContent(1)-original_hist->GetBinContent(1);
          double error_sumw2 = original_hist->GetBinError(1);
          double error_combined = sqrt( error_propagated*error_propagated + error_sumw2*error_sumw2 );

          original_hist->SetBinError(1, error_combined);
        }
*/

        staterror += (original_hist->GetBinError(1))*(original_hist->GetBinError(1));

        //========================================
        //==== Remove Stat, and get  Systematics
        //========================================

        if( sample.Contains("fake") ){
          double error_stat = 0;
          double error_syst = FakeSyst*(original_hist->GetBinContent(1));
          double error_combined = sqrt( error_stat*error_stat+error_syst*error_syst );

          original_hist->SetBinError(1, error_combined);
        }
        else if( sample.Contains("chargeflip") ){
          double error_stat = 0;;
          double error_syst = FlipSyst*(original_hist->GetBinContent(1));

          TH1D *original_hist_up = (TH1D *)file->Get(region+"_up/Nevents_"+region+"_up");
          double error_propagated = original_hist_up->GetBinContent(1)-original_hist->GetBinContent(1);
          error_syst = sqrt(error_syst*error_syst+error_propagated*error_propagated);

          double error_combined = sqrt( error_stat*error_stat+error_syst*error_syst );

          original_hist->SetBinError(1, error_combined);
        }
        else{
          TH1D *thishist_systyields = (TH1D *)file->Get("Systematics/Yields_"+region);

          double error_stat = 0;
          double error_syst = GetYieldSystematics(thishist_systyields);

          double error_lumi = LumiSyst*(original_hist->GetBinContent(1));

          double error_combined = sqrt( error_stat*error_stat + error_syst*error_syst + error_lumi*error_lumi +MCSF_uncert*MCSF_uncert );

          original_hist->SetBinError(1, error_combined);

        }

        systerror += (original_hist->GetBinError(1))*(original_hist->GetBinError(1));

        //cout << endl << sample << "\t" << original_hist->GetBinContent(1) << "\t" << original_hist->GetBinError(1) << endl;
      } // END loop samples in each bkglists

      if(isMC){
        MC_yield.at(it_region) += yield_central;
        MC_stat.at(it_region) += staterror;
        MC_syst.at(it_region) += systerror;
      }
      Total_yield.at(it_region) += yield_central;
      Total_stat.at(it_region) += staterror;
      Total_syst.at(it_region) += systerror;

      staterror = sqrt(staterror);
      systerror = sqrt(systerror);

      cout << " & $" << std::fixed<<std::setprecision(2) << yield_central << " \\pm " << staterror << " \\pm " << systerror << "$";

    } // END loop regions

    cout << " \\\\" << endl;

    if(it_bkglist==index_ENDMC){
      cout << "\\hline" << endl;
      cout << "Total Monte Carlo ";
      for(unsigned int it_region=0; it_region<regions.size(); it_region++){
        cout << "& $" << MC_yield.at(it_region) << " \\pm " << sqrt(MC_stat.at(it_region)) << " \\pm " << sqrt(MC_syst.at(it_region)) << "$ ";
      }
      cout << " \\\\" << endl;
      cout << "\\hline" << endl;
    }

  } // END loop bkglists

  cout << "\\hline" << endl;
  cout << "Total background ";
  for(unsigned int it_region=0; it_region<regions.size(); it_region++){
    cout << "& $" << Total_yield.at(it_region) << " \\pm " << sqrt(Total_stat.at(it_region)) << " \\pm " << sqrt(Total_syst.at(it_region)) << "$ ";
  }
  cout << " \\\\" << endl;
  cout << "\\hline" << endl;

  //==== Signal

  cout << "{\\bf Majorana neutrino signal} ";for(int i=0;i<nCR;i++) cout<<"& ";cout<<" \\\\" << endl;
  for(unsigned int it_sig=0;it_sig<ref_sigs.size();it_sig++){

    TString sigmass = TString::Itoa(ref_sigs.at(it_sig),10);
    TString siglepch = "MuMu";
    if(ChannelName=="DiElectron") siglepch = "ElEl";
    if(ChannelName=="EMu") siglepch = "MuEl";

    TString signame = "HNMoriondLL"+siglepch+"_"+TString::Itoa(ref_sigs.at(it_sig),10);
    TString bkgdtype = "$m_N = "+TString::Itoa(ref_sigs.at(it_sig),10)+"$~\\GeVcc, $"+V2ForTex+" = "+ref_scaleForTex.at(it_sig)+"$";

    cout << bkgdtype;

    for(unsigned int it_region=0;it_region<nCR;it_region++){

      TString region = regions.at(it_region);

      TString filename = "DiLeptonAnalyzer_SKHN"+siglepch+"_"+sigmass+"_cat_"+catversion+".root";
      TFile *file_sig = new TFile(filepath+"/Signal/"+filename);
      TString histname = region+"/Nevents_"+region;

      TH1D *hist_sig = (TH1D *)file_sig->Get(histname);
      double yield_sig = 0.;
      double stat_sig = 0.;
      double syst_sig = 0.;

      if(hist_sig){
        yield_sig = hist_sig->GetBinContent(1);
        stat_sig = hist_sig->GetBinError(1);

        TH1D *thishist_systyields = (TH1D *)file_sig->Get("Systematics/Yields_"+region);

        double error_stat = 0;
        double error_syst = GetYieldSystematics(thishist_systyields);
        double error_lumi = LumiSyst*(hist_sig->GetBinContent(1));

        double error_combined = sqrt( error_stat*error_stat + error_syst*error_syst + error_lumi*error_lumi );

        syst_sig = error_combined;


        yield_sig *= ref_scale.at(it_sig);
        stat_sig *= ref_scale.at(it_sig);
        syst_sig *= ref_scale.at(it_sig);
        
      }

      cout << " & $" << std::fixed<<std::setprecision(2) << yield_sig << " \\pm " << stat_sig << " \\pm " << syst_sig << "$";

    }
    cout << " \\\\" << endl;
    
  }


  //==== Data

  cout << "\\hline" << endl;
  cout << "Observed in data (36.5 fb$^{-1}$)";
  for(unsigned int it_region=0;it_region<nCR;it_region++){

    TString region = regions.at(it_region);

    TString filename = "DiLeptonAnalyzer_data_"+DataPD+"_cat_"+catversion+".root";
    TFile *file_data = new TFile(filepath+"/"+filename);
    TString histname = region+"/Nevents_"+region;

    TH1D *hist_data = (TH1D *)file_data->Get(histname);

    int y_data = 0;
    if(hist_data){
      y_data = hist_data->GetBinContent(1);
    }

    cout <<" & $"<<y_data<<"$";
  }
  cout<<" \\\\" << endl;
  cout << "\\hline" << endl;
  cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << "      \\end{tabular}" << endl;
  cout << "    }" << endl;
  cout << "  \\end{center}" << endl;
  cout << "\\end{table}" << endl;


}



