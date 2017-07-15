#include "cutop.C"
#include "cutrangeinfo.h"

double PunziFunction(double eff_sig, double bkg_tot, double bkg_err2);

void Run_cutop(){

  //================================
  //==== Get Envrionment Variables
  //================================

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("FILE_PATH");

  //=====================
  //==== Basic Settings
  //=====================

  bool DoDebug = false;
  bool ShowData = false;
  bool PrintYield = true;
  Long64_t LogEvery = 1;

  //=====================
  //==== set data class
  //=====================

  TString DataPD = "DoubleEG";
  TString channel = "DiElectron";
  TString data_class = dataset+"/Ntuple/";
  TString filename_prefix = "DiLeptonAnalyzer";
  TString filename_suffix = "_cat_"+catversion+".root";

  //===================
  //==== Input/Output 
  //===================

  TString filepath = WORKING_DIR+"/rootfiles/"+data_class;
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //=============================
  //===== Set Up Samples to Use
  //=============================
/*
  map< TString, vector<TString> > map_sample_string_to_list;

  map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  map_sample_string_to_list["WJets"] = {"WJets"};
  map_sample_string_to_list["VV_excl"] = {
    "WZTo3LNu_powheg", "WZto2L2Q_amcatnlo",
    "ZZTo4L_powheg", "ZZTo2L2Nu_Powheg", "ZZTo2L2Q_Powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau",
    "WWTo2L2Nu", "ggWWto2L2Nu",
  };
  map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  map_sample_string_to_list["ttbar"] = {"TTJets_aMC"};
  map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  map_sample_string_to_list["top"] = {"TTLL_powheg", "ttW", "ttZ", "ttH_nonbb"};
  map_sample_string_to_list["Wgamma"] = {"WgstarToLNuEE", "WgstarToLNuMuMu"};
  map_sample_string_to_list["Zgamma"] = {"ZGto2LG"};
  map_sample_string_to_list["Vgamma"] = {"WgstarToLNuEE", "WgstarToLNuMuMu", "ZGto2LG"};
  map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "WgstarToLNuEE", "WgstarToLNuMuMu", "ZGto2LG"};
  map_sample_string_to_list["Xgamma_noDY"] = {"TG", "TTG", "WgstarToLNuEE", "WgstarToLNuMuMu"};
  map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS"};
  map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  vector<TString> samples_to_use = {"chargeflip", "fake_Dijet", "Xgamma", "VV_excl", "VVV", "top", "WW_double"};
  vector<TString> samples;
  //==== push_back data
  samples.push_back("data");
  //==== push_back backgroud
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    samples.insert(samples.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
*/

  //samples = {"chargeflip"}; //FOR DEBUG
  //==== Samples has > 1% contribution @ preselection
  samples = {"data", "fake_Dijet", "WZTo3LNu_powheg", "WgstarToLNuEE", "chargeflip", "ZGto2LG", "ZZTo4L_powheg", "ttW", "WWW"};

  //==== Check samples
  cout << "################" << endl;
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<samples.size(); i++) cout << " " << samples[i] << endl;
  cout << "################" << endl << endl;

  //=====================
  //==== Signals To Use
  //=====================

  //=====================================
  //==== Setting calculated systematics
  //=====================================

  map<TString, double> CalculatedSysts;

  string elline_syst;
  ifstream in_syst(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  //cout << "#### Setting calculated systematics ####" << endl;
  while(getline(in_syst,elline_syst)){
    std::istringstream is( elline_syst );
    TString source;
    double value;
    is >> source;
    is >> value;
    //cout << source << " : " << value << endl;
    CalculatedSysts[source] = value;
  }

  double uncert_lumi = CalculatedSysts["Luminosity"];
  double uncert_cf = CalculatedSysts["ChrageFlipSyst"];
  double uncert_fake = CalculatedSysts["FakeLooseID"];

  //============================================
  //==== Setting MC Normalization Scale Factor
  //============================================

  map<TString, double> MCNormSF, MCNormSF_uncert;
  for(unsigned int i=0; i<samples.size(); i++){
    if(samples.at(i)=="data") continue;
    if(samples.at(i)=="chargeflip") continue;
    if(samples.at(i).Contains("fake")) continue;

    MCNormSF[samples.at(i)] = 1.;
    MCNormSF_uncert[samples.at(i)] = 0.;
  }

  string elline_MCSF;
  ifstream in_MCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt");
  //cout << "#### Setting MCSF ####" << endl;
  while(getline(in_MCSF,elline_MCSF)){
    std::istringstream is( elline_MCSF );
    TString sample;
    double MCSF, MCSF_err;
    is >> sample;
    is >> MCSF;
    is >> MCSF_err;

    if(DoDebug) cout << sample << " : " << "MCSF = " << MCSF << ", MCSF_err = " << MCSF_err << endl;

    MCNormSF[sample] = MCSF;
    MCNormSF_uncert[sample] = MCSF_err;

  }

  //====================
  //==== Read Cut Card
  //====================

  TString cutfilename = "test.txt";
  cutrangeinfo CutRangeInfo(WORKING_DIR+"/data/"+dataset+"/CutOpCard/"+cutfilename);
  CutRangeInfo.DoDebug = DoDebug;
  cout
  << "##################################################" << endl
  << "####TOTAL # of Loop = " << CutRangeInfo.TotalIteration << endl
  << "##################################################" << endl << endl;
  if(DoDebug) CutRangeInfo.Print();

  //========================
  //==== CutRangeInfo Loop
  //========================

  cout << "##############################" << endl;
  cout << "#### OPTIMIZATION STARTED ####" << endl;
  cout << "##############################" << endl << endl;


  while( !CutRangeInfo.isEnd() ){

    //==================
    //==== Sample Loop
    //==================

    double data_unweighted_yield(0.), data_weighted_yield(0.);
    double chargeflip_unweighted_yield(0.), chargeflip_weighted_yield(0.), chargeflip_weighted_yield_stat(0.);
    double fake_unweighted_yield(0.), fake_weighted_yield(0.), fake_weighted_yield_stat(0.);

    double prompt_unweighted_yield(0.), prompt_weighted_yield(0.);
    TH1D *hist_prompt_total = new TH1D("hist_prompt_total", "", 1, 0., 1.); // Use TH1D::Add, to use GetBinError
    TH1D *hist_prompt_total_up = new TH1D("hist_prompt_total_up", "", 1, 0., 1.); // Just fill content, and only use GetBinContent

    for(unsigned int i=0; i<samples.size(); i++){

      TString sample = samples.at(i);

      TString filename = filename_prefix+"_SK"+sample+"_dilep"+filename_suffix;
      if(sample=="data") filename = "DiLeptonAnalyzer_data_"+DataPD+"_cat_"+catversion+".root";
      if(sample=="chargeflip") filename = "DiLeptonAnalyzer_SKchargeflip_"+DataPD+"_dilep_cat_"+catversion+".root";
      if(sample.Contains("fake")) filename = "DiLeptonAnalyzer_SK"+sample+"_"+DataPD+"_dilep_cat_"+catversion+".root";

      cutop m(filepath+filename, "Ntp_"+channel);
      m.DoDebug = DoDebug;

      //==== Fill cutinfo
      vector<cutinfo> cis;
      CutRangeInfo.FillCurrentCutInfoVector(cis);
      for(unsigned int ii=0;ii<cis.size();ii++) m.SetCutVariablesToUse(cis.at(ii));

      //==== Run
      m.Loop();

      //==== Sum yield
      if(sample=="data"){
        data_unweighted_yield = m.unweighted_yield;
        data_weighted_yield = m.weighted_yield;
      }
      else if(sample=="chargeflip"){
        chargeflip_unweighted_yield = m.unweighted_yield;
        chargeflip_weighted_yield = m.weighted_yield;

        chargeflip_weighted_yield_stat = m.hist_for_error->GetBinError(1);
        double cf_propagation = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        chargeflip_weighted_yield_stat = sqrt( chargeflip_weighted_yield_stat*chargeflip_weighted_yield_stat + cf_propagation*cf_propagation );
      }
      else if(sample.Contains("fake")){
        fake_unweighted_yield = m.unweighted_yield;
        fake_weighted_yield = m.weighted_yield;

        fake_weighted_yield_stat = m.hist_for_error->GetBinError(1);
        double fr_propagation = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        fake_weighted_yield_stat = sqrt( fake_weighted_yield_stat*fake_weighted_yield_stat + fr_propagation*fr_propagation );
      }
      else{
        prompt_unweighted_yield += m.unweighted_yield;

        prompt_weighted_yield += m.weighted_yield * MCNormSF[sample];
        hist_prompt_total->Add( m.hist_for_error );
        hist_prompt_total_up->Fill(0., m.weighted_yield * (MCNormSF[sample]+MCNormSF_uncert[sample]));
        
      }

      //==== Print this samples yield for Debugging
      if(PrintYield){
				if(sample=="data"){
					if(!ShowData) cout << sample << "\t" << "BLIND" << endl;
				}
				else{
					cout << sample << "\t" << m.weighted_yield << "\t" << m.hist_for_error->GetBinContent(1) << "\t" << m.hist_for_error->GetBinError(1) << "\t" << m.unweighted_yield << endl;
				}
      }

    } // END sample loop

    //==== Stat. + Syst.
    double chargeflip_weighted_yield_syst = chargeflip_weighted_yield * uncert_cf;
    double chargeflip_weighted_yield_err = sqrt( chargeflip_weighted_yield_stat*chargeflip_weighted_yield_stat + chargeflip_weighted_yield_syst*chargeflip_weighted_yield_syst );
    if(PrintYield){
      cout << "chargeflip_weighted_yield = " << chargeflip_weighted_yield << endl;
      cout << "  chargeflip_weighted_yield_stat = " << chargeflip_weighted_yield_stat << endl;
      cout << "  chargeflip_weighted_yield_syst = " << chargeflip_weighted_yield_syst << endl;
      cout << "  => chargeflip_weighted_yield_err = " << chargeflip_weighted_yield_err << endl;
    }

    double fake_weighted_yield_syst = fake_weighted_yield * uncert_fake;
    double fake_weighted_yield_err = sqrt( fake_weighted_yield_stat*fake_weighted_yield_stat + fake_weighted_yield_syst*fake_weighted_yield_syst );
    if(PrintYield){
      cout << "fake_weighted_yield = " << fake_weighted_yield << endl;
      cout << "  fake_weighted_yield_stat = " << fake_weighted_yield_stat << endl;
      cout << "  fake_weighted_yield_syst = " << fake_weighted_yield_syst << endl;
      cout << "  => fake_weighted_yield_err = " << fake_weighted_yield_err << endl;
    }

    double prompt_weighted_yield_stat = hist_prompt_total->GetBinError(1);
    double prompt_weighted_yield_syst_lumi = prompt_weighted_yield * uncert_lumi;
    double prompt_weighted_yield_syst_MCSF = hist_prompt_total_up->GetBinContent(1) - hist_prompt_total->GetBinContent(1);
    double prompt_weighted_yield_err = sqrt( prompt_weighted_yield_stat*prompt_weighted_yield_stat + prompt_weighted_yield_syst_lumi*prompt_weighted_yield_syst_lumi + prompt_weighted_yield_syst_MCSF*prompt_weighted_yield_syst_MCSF );
    if(PrintYield){
      cout << "prompt_weighted_yield = " << prompt_weighted_yield << endl;
      cout << "  prompt_weighted_yield_stat = " << prompt_weighted_yield_stat << endl;
      cout << "  prompt_weighted_yield_syst_lumi = " << prompt_weighted_yield_syst_lumi << endl;
      cout << "  prompt_weighted_yield_syst_MCSF = " << prompt_weighted_yield_syst_MCSF << endl;
      cout << "  => prompt_weighted_yield_err = " << prompt_weighted_yield_err << endl;
    }

    double total_bkg_err_2 = chargeflip_weighted_yield_err*chargeflip_weighted_yield_err+fake_weighted_yield_err*fake_weighted_yield_err+prompt_weighted_yield_err*prompt_weighted_yield_err;

    //==== Print

    if(CutRangeInfo.CurrentIteration%LogEvery==0){

      double bkg_weighted_yield = prompt_weighted_yield+chargeflip_weighted_yield+fake_weighted_yield;
      cout << endl;
      cout << "Current Iteration = " << CutRangeInfo.CurrentIteration << " ("<<100.*CutRangeInfo.CurrentIteration/CutRangeInfo.TotalIteration<<" %)"<<endl;
      CutRangeInfo.PrintCurrent();
      cout << "CF" << "\t" << chargeflip_weighted_yield << " +- " << chargeflip_weighted_yield_err << endl;
      cout << "Fake" << "\t" << fake_weighted_yield << " +- " << fake_weighted_yield_err << endl;
      cout << "Prompt" << "\t" << prompt_weighted_yield << " +- " << prompt_weighted_yield_err << endl;

      cout << "prompt_weighted_yield = " << prompt_weighted_yield << endl;
      cout << "chargeflip_weighted_yield = " << chargeflip_weighted_yield << endl;
      cout << "fake_weighted_yield = " << fake_weighted_yield << endl;
      cout << "=> total bkg = " << bkg_weighted_yield << endl;
      cout << "=====================================================================" << endl << endl;

    }
    


    CutRangeInfo.Next();

  } //END CutRangeInfo loop



}



double PunziFunction(double eff_sig, double bkg_tot, double bkg_err2){

  double den = 1 + sqrt( bkg_tot + bkg_err2 );

  return eff_sig/den;

}















