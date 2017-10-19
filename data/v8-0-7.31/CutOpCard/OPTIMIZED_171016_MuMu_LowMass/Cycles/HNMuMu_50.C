#include "RunNtupleBase.C"

void HNMuMu_50(){

  bool DoDebug = false;

  TString CutOpCardDir = "OPTIMIZED_171016_MuMu_LowMass";

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("FILE_PATH");

  //==== Declare Object

  RunNtupleBase m;
  m.DoDebug = DoDebug;
  m.RunSystematic = true;

  //==== Skim selection for tree (tree name : Ntp_<skim>)

  m.treeskim = "Low_SS";

  //==== Dataset/channel

  m.DataPD = "DoubleMuon";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/Skimmed_LowMass/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {
    "HNMuMu_50",
  };
  m.MinEffPresel = 0.;
  m.AddSamplesToList( m.signals );

  //==== Backgrounds

  vector<TString> bkgs = {"fake_Dijet", "WZTo3LNu_powheg", "WGtoLNuG", "ZGto2LG", "ZZTo4L_powheg", "ttW", "WWW"};
  m.AddSamplesToList( bkgs );

  if(DoDebug) m.PrintSampleList();

  //==== Fill MCNorm SF

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

  //==== Get Systematics

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  m.SetSourceSystematics();

  //==== Set CutCard

  TString cutfilename = "HNMuMu_50.txt";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/"+CutOpCardDir+"/"+cutfilename);

  vector<TString> systs = {
    "",
    "_MuonEn_up", "_MuonEn_down",
    "_JetEn_up", "_JetEn_down",
    "_JetRes_up", "_JetRes_down",
    "_Unclustered_up", "_Unclustered_down",
    "_MuonIDSF_up", "_MuonIDSF_down",
    "_PU_down", "_PU_up",
    "_TriggerSF_up", "_TriggerSF_down",
    "_ElectronIDSF_up", "_ElectronIDSF_down",
    "_ElectronEn_up", "_ElectronEn_down",
  };


  vector<double> y_total_bkgs, y_fake_bkgs, y_prompt_bkgs, y_cf_bkgs, y_signals;
  vector<TString> reldiff_sources, reldiff_sig_sources;
  vector<double> reldiff_means, reldiff_sig_means;
  double y_bkg_central, y_fake_central, y_prompt_central, y_cf_central, y_signal_central;

  double reldiff_up, reldiff_down;
  double reldiff_sig_up, reldiff_sig_down;

  double syst_total_bkg(0.);
  double syst_sig(0.);

  for(unsigned int i=0; i<systs.size(); i++){

    TString this_syst = systs.at(i);

    m.channel = "DiMuon"+this_syst;
    m.channel_for_jetres = "DiMuon";
    m.ClearSignalInfo();
    m.FillSignalInfo();
    m.cutrangeinfo.k_end = false;
    m.Run();

    y_total_bkgs.push_back( m.total_bkgs );
    y_fake_bkgs.push_back( m.fake_bkgs );
    y_prompt_bkgs.push_back( m.prompt_bkgs );
    y_cf_bkgs.push_back( m.cf_bkgs );
    y_signals.push_back( m.signal_rate.at(0) );

    if(i==0){

      y_bkg_central = m.total_bkgs;
      y_fake_central = m.fake_bkgs;
      y_prompt_central = m.prompt_bkgs;
      y_cf_central = m.cf_bkgs;

      double CalculatedSyst = m.total_bkgs_err/m.total_bkgs;
      syst_total_bkg += (CalculatedSyst)*(CalculatedSyst);

      y_signal_central = m.signal_rate.at(0);
      this_syst = "Central";

    }

    double reldiff = (y_total_bkgs.at(i)-y_bkg_central)/y_bkg_central;
    double reldiff_sig = (m.signal_rate.at(0)-y_signal_central)/y_signal_central;

    if(i!=0){

      //==== i=1 : up / i=2 : down

      if(i%2==1){
        reldiff_up = reldiff;
        reldiff_sig_up = reldiff_sig;
      }
      else{
        reldiff_down = reldiff;
        reldiff_sig_down = reldiff_sig;

        double reldiff_mean = sqrt( 0.5 * (reldiff_up*reldiff_up+reldiff_down*reldiff_down) );
        double reldiff_sig_mean = sqrt( 0.5 * (reldiff_sig_up*reldiff_sig_up+reldiff_sig_down*reldiff_sig_down) );

        reldiff_sources.push_back( this_syst );
        reldiff_means.push_back( reldiff_mean );
        reldiff_sig_means.push_back( reldiff_sig_mean );

      }

    }

    //cout << this_syst << "	" << y_total_bkgs.at(i) << "	" << std::fixed<<std::setprecision(3) << 100.*reldiff << endl;
    //cout << this_syst << "	" << m.total_bkgs << "	" << m.fake_bkgs << "	" << m.prompt_bkgs << "	" << m.cf_bkgs << endl;

  }

  cout << endl;
  cout << "################ result ################" << endl;
  for(unsigned int i=0; i<reldiff_means.size(); i++){

    TString this_syst = reldiff_sources.at(i);

    //cout << this_syst << "	" << y_total_bkgs.at(i) << "	" << std::fixed<<std::setprecision(3) << 100.*reldiff_means.at(i) << endl;

    syst_total_bkg += reldiff_means.at(i)*reldiff_means.at(i);
    syst_sig += reldiff_sig_means.at(i)*reldiff_sig_means.at(i);

  }

  //==== Lumi syst for signal
  double syst_lumi = m.analysisInputs.CalculatedSysts["Luminosity"];
  syst_sig += syst_lumi*syst_lumi;



  //===============
  //==== Finalize
  //===============

  syst_total_bkg = sqrt(syst_total_bkg);
  syst_sig = sqrt(syst_sig);

  //cout << y_bkg_central << "	" << std::fixed<<std::setprecision(3) << 100.*syst_total_bkg << endl;
  //cout << y_signal_central << "	" << 100.*syst_sig << endl;

  cout << y_bkg_central << " " << std::fixed<<std::setprecision(3) << 1.+syst_total_bkg << endl;
  cout << y_signal_central << " " << 1.+syst_sig << endl;



}
