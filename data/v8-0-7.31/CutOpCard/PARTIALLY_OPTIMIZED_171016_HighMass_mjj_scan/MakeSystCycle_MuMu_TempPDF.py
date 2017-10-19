import os

CutCardDirName = "PARTIALLY_OPTIMIZED_171016_HighMass_mjj_scan"

os.system("mkdir -p Cycles/")

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for mass in masses:

  out = open("Cycles/HNMuMu_"+str(mass)+".C","w")

  TreeSkim = ""
  SkimmedTreeDir = ""
  if mass <= 80:
    TreeSkim = "Low_SS"
    SkimmedTreeDir = "Skimmed_LowMass"
  else:
    TreeSkim = "High_SS"
    SkimmedTreeDir = "Skimmed_HighMass"

  SignalSampleName = "HNMuMu_"+str(mass)
  CutCardName = "HNElEl_"+str(mass)+".txt"

  print>>out,'''#include "RunNtupleBase.C"

void HNMuMu_{2}(){{

  bool DoDebug = false;

  TString CutOpCardDir = "{3}";

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

  m.treeskim = "{0}";

  //==== Dataset/channel

  m.DataPD = "DoubleMuon";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/{1}/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {{
    "HNMuMu_{2}",
  }};
  m.MinEffPresel = 0.;
  m.AddSamplesToList( m.signals );

  //==== Backgrounds

  vector<TString> bkgs = {{"fake_Dijet", "WZTo3LNu_powheg", "WGtoLNuG", "ZGto2LG", "ZZTo4L_powheg", "ttW", "WWW"}};
  m.AddSamplesToList( bkgs );

  if(DoDebug) m.PrintSampleList();

  //==== Fill MCNorm SF

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

  //==== Get Systematics

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  m.SetSourceSystematics();

  //==== Set CutCard

  TString cutfilename = "HNMuMu_{2}.txt";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/"+CutOpCardDir+"/"+cutfilename);

  vector<TString> systs = {{
    "",
    "_MuonEn_up", "_MuonEn_down",
    "_MuonIDSF_up", "_MuonIDSF_down",
    "_ElectronEn_up", "_ElectronEn_down",
    "_ElectronIDSF_up", "_ElectronIDSF_down",
    "_TriggerSF_up", "_TriggerSF_down",
    "_PU_up", "_PU_down",
    "_JetEn_up", "_JetEn_down",
    "_JetRes_up", "_JetRes_down",
    "_Unclustered_up", "_Unclustered_down",
    "_BTagSFEff_up", "_BTagSFEff_down",
    "_BTagSFMiss_up", "_BTagSFMiss_down"
  }};


  vector<double> y_total_bkgs, y_fake_bkgs, y_prompt_bkgs, y_cf_bkgs, y_signals;
  vector<TString> reldiff_sources, reldiff_sig_sources;
  vector<double> reldiff_means, reldiff_prompt_means, reldiff_fake_means, reldiff_cf_means, reldiff_sig_means;
  double y_bkg_central, y_fake_central, y_prompt_central, y_cf_central, y_signal_central;

  double reldiff_up, reldiff_down;
  double reldiff_prompt_up, reldiff_prompt_down;
  double reldiff_fake_up, reldiff_fake_down;
  double reldiff_cf_up, reldiff_cf_down;
  double reldiff_sig_up, reldiff_sig_down;

  //==== Add up errors
  //==== THIS INCLUDES STAT ERRORS
  //==== Systematic only will be calculated later..
  double syst_total_bkg(0.);
  double syst_sig(0.);

  double prompt_calculated_syst(0.); // MCSF
  double fake_calculated_syst(0.); // Fake Syst
  double cf_calculated_syst(0.); // CF Syst
  double signal_calculated_syst(0.); // Pdf Syst

  for(unsigned int i=0; i<systs.size(); i++){{

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

    if(i==0){{

      this_syst = "Central";

      y_bkg_central = m.total_bkgs;
      y_fake_central = m.fake_bkgs;
      y_prompt_central = m.prompt_bkgs;
      y_cf_central = m.cf_bkgs;

      //==== m.total_bkgs_err with Central Ntuple contains;
      //==== 1) Prompt
      //==== - Stat
      //==== - Lumi
      //==== - MCSF
      //==== 2) Fake
      //==== - Stat + FR-Stat-Propagation
      //==== - Systematic
      //==== 3) CF
      //==== - Stat
      //==== - Systematic

      double CalculatedSyst = m.total_bkgs_err/m.total_bkgs;
      syst_total_bkg += (CalculatedSyst)*(CalculatedSyst);

      //==== Signal
      //==== - Stat
      //==== - Lumi

      y_signal_central = m.signal_rate.at(0);
      syst_sig += (m.signal_err.at(0)/m.signal_rate.at(0))*(m.signal_err.at(0)/m.signal_rate.at(0));

      m.pdfsyst.Yield_Central = y_signal_central;
      //m.pdfsyst.CalculatePdfSystematic();

      prompt_calculated_syst = m.prompt_bkgs_syst;
      fake_calculated_syst = m.fake_bkgs_syst;
      cf_calculated_syst = m.cf_bkgs_syst;
      //signal_calculated_syst = (m.pdfsyst.Syst_Pdf_Total)*y_signal_central;
      signal_calculated_syst = (0.03)*y_signal_central;

    }}

    double reldiff = (m.total_bkgs-y_bkg_central)/y_bkg_central;
    double reldiff_prompt = (m.prompt_bkgs-y_prompt_central)/y_prompt_central;
    double reldiff_fake = (m.fake_bkgs-y_fake_central)/m.fake_bkgs;
    double reldiff_cf = (m.cf_bkgs-y_cf_central)/m.cf_bkgs;
    double reldiff_sig = (m.signal_rate.at(0)-y_signal_central)/y_signal_central;

    if(i!=0){{

      //==== i=1 : up / i=2 : down

      if(i%2==1){{
        reldiff_up = reldiff;
        reldiff_prompt_up = reldiff_prompt;
        reldiff_fake_up = reldiff_fake;
        reldiff_cf_up = reldiff_cf;
        reldiff_sig_up = reldiff_sig;
      }}
      else{{
        reldiff_down = reldiff;
        reldiff_prompt_down = reldiff_prompt;
        reldiff_fake_down = reldiff_fake;
        reldiff_cf_down = reldiff_cf;
        reldiff_sig_down = reldiff_sig;

        double reldiff_mean = sqrt( 0.5 * (reldiff_up*reldiff_up+reldiff_down*reldiff_down) );
        double reldiff_prompt_mean = sqrt( 0.5 * (reldiff_prompt_up*reldiff_prompt_up+reldiff_prompt_down*reldiff_prompt_down) );
        double reldiff_fake_mean = sqrt( 0.5 * (reldiff_fake_up*reldiff_fake_up+reldiff_fake_down*reldiff_fake_down) );
        double reldiff_cf_mean = sqrt( 0.5 * (reldiff_cf_up*reldiff_cf_up+reldiff_cf_down*reldiff_cf_down) );
        double reldiff_sig_mean = sqrt( 0.5 * (reldiff_sig_up*reldiff_sig_up+reldiff_sig_down*reldiff_sig_down) );

        reldiff_sources.push_back( this_syst );
        reldiff_means.push_back( reldiff_mean );
        reldiff_prompt_means.push_back( reldiff_prompt_mean );
        reldiff_fake_means.push_back( reldiff_fake_mean );
        reldiff_cf_means.push_back( reldiff_cf_mean );
        reldiff_sig_means.push_back( reldiff_sig_mean );

      }}

    }} // Not Central, add systematics

    //==== Print
    cout << this_syst << "\t" << m.prompt_bkgs << "\t" << m.fake_bkgs << "\t" << m.cf_bkgs << endl;

  }}

  vector<TString> sourcealias = {{
    "Muon Energy Scale",
    "Muon ID",
    "Electron Energy Scale",
    "Electron ID",
    "Trigger SF",
    "PU",
    "Jet Energy Scale",
    "Jet Energy Resolution",
    "Unclustered Energy",
    "B-tagging Eff",
    "B-taggin Miss",
  }};

  cout << endl;
  cout << "################ Sources ################" << endl;
  cout << "Source\tSystTotal\tSystPrompt\tSystFake\tSignal" << endl;

  double ONLYSYST_bkg(0.), ONLYSYST_prompt(0.), ONLYSYST_fake(0.), ONLYSYST_cf(0.), ONLYSYST_sig(0.);

  double syst_lumi = m.analysisInputs.CalculatedSysts["Luminosity"];

  cout << "Lumi" << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*syst_lumi*y_prompt_central/y_bkg_central << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*syst_lumi << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*syst_lumi << endl;
  ONLYSYST_bkg += (syst_lumi*y_prompt_central/y_bkg_central)*(syst_lumi*y_prompt_central/y_bkg_central);
  ONLYSYST_prompt += syst_lumi*syst_lumi;
  ONLYSYST_sig += syst_lumi*syst_lumi;

  cout << "PDF" << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*signal_calculated_syst/y_signal_central << endl;
  ONLYSYST_sig += (signal_calculated_syst/y_signal_central)*(signal_calculated_syst/y_signal_central);
  syst_sig += (signal_calculated_syst/y_signal_central)*(signal_calculated_syst/y_signal_central);

  for(unsigned int i=0; i<reldiff_means.size(); i++){{

    //TString this_syst = reldiff_sources.at(i);
    TString this_syst = sourcealias.at(i);

    //cout << this_syst << "  " << y_total_bkgs.at(i) << "  " << std::fixed<<std::setprecision(2) << 100.*reldiff_means.at(i) << " %" << endl;
    cout << this_syst << "\t";
    cout << std::fixed<<std::setprecision(2) << 100.*reldiff_means.at(i) << "\t";
    cout << std::fixed<<std::setprecision(2) << 100.*reldiff_prompt_means.at(i) << "\t";
    cout << std::fixed<<std::setprecision(2) << 100.*reldiff_fake_means.at(i) << "\t";
    cout << std::fixed<<std::setprecision(2) << 100.*reldiff_sig_means.at(i) << endl;

    ONLYSYST_bkg += reldiff_means.at(i)*reldiff_means.at(i);
    ONLYSYST_prompt += reldiff_prompt_means.at(i)*reldiff_prompt_means.at(i);
    ONLYSYST_fake += reldiff_fake_means.at(i)*reldiff_fake_means.at(i);
    ONLYSYST_sig += reldiff_sig_means.at(i)*reldiff_sig_means.at(i);

    syst_total_bkg += reldiff_means.at(i)*reldiff_means.at(i);
    syst_sig += reldiff_sig_means.at(i)*reldiff_sig_means.at(i);

  }}

  cout << "MCNorm" << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*prompt_calculated_syst/y_bkg_central << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*prompt_calculated_syst/y_prompt_central << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << endl;
  ONLYSYST_bkg += (prompt_calculated_syst/y_bkg_central)*(prompt_calculated_syst/y_bkg_central);
  ONLYSYST_prompt += (prompt_calculated_syst/y_prompt_central)*(prompt_calculated_syst/y_prompt_central);

  cout << "Fake" << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*fake_calculated_syst/y_bkg_central << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << "\t";
  cout << std::fixed<<std::setprecision(2) << 100.*fake_calculated_syst/y_fake_central << "\t";
  cout << std::fixed<<std::setprecision(2) << 0. << endl;
  ONLYSYST_bkg += (fake_calculated_syst/y_bkg_central)*(fake_calculated_syst/y_bkg_central);
  ONLYSYST_fake += (fake_calculated_syst/y_fake_central)*(fake_calculated_syst/y_fake_central);

  ONLYSYST_bkg = sqrt(ONLYSYST_bkg);
  ONLYSYST_prompt = sqrt(ONLYSYST_prompt);
  ONLYSYST_fake = sqrt(ONLYSYST_fake);
  ONLYSYST_sig = sqrt(ONLYSYST_sig);

  cout << "Total Systematic" << "\t" << 100.*ONLYSYST_bkg << "\t" << 100.*ONLYSYST_prompt << "\t" << 100.*ONLYSYST_fake << "\t" << 100.*ONLYSYST_sig << endl;
  cout << endl;

  cout << "Total Background" << "\t" << y_bkg_central << endl;
  cout << "- Prompt" << "\t" << y_prompt_central << endl;
  cout << "- Fake" << "\t" << y_fake_central << endl;
  cout << "- CF" << "\t" << y_cf_central << endl;




  //===============
  //==== Finalize
  //===============

  cout << endl;
  cout << "####### Result #######" << endl;

  syst_total_bkg = sqrt(syst_total_bkg);
  syst_sig = sqrt(syst_sig);

  //cout << y_bkg_central << "  " << std::fixed<<std::setprecision(3) << 100.*syst_total_bkg << endl;
  //cout << y_signal_central << "  " << 100.*syst_sig << endl;

  cout << y_bkg_central << " " << std::fixed<<std::setprecision(3) << 1.+syst_total_bkg << endl;
  cout << y_signal_central << " " << 1.+syst_sig << endl;



}}'''.format(TreeSkim, SkimmedTreeDir, str(mass), CutCardDirName)

