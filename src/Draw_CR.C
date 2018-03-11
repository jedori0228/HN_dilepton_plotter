#include "Plotter.cc"
#include <fstream>

void Draw_CR(bool ScaleMC=true, int XXX=0){

  //==============
  //==== get env
  //==============
  
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  //====================
  //==== decalre class
  //====================
  
  Plotter m;
  m.DoDebug = false;
  
  //=====================
  //==== set data class
  //=====================
  
  m.data_class = dataset+"/Regions/";
  
  //================================
  //==== set prefixes and suffixes
  //================================
  
  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "_cat_"+catversion+".root";
  
  //=========================
  //==== set sample mapping
  //=========================
  
  m.map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets"};
  m.map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TT_powheg"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  m.map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted"};
  //m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG"};
  m.map_sample_string_to_list["Xgamma_noDY"] = {"TG", "TTG", "WGtoLNuG_weighted"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma_noDY"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["chargeflip"] = make_pair("Mismeas. charge background", kYellow);
  
  //===============================
  //==== set and make sample list
  //===============================

  //==== _Di<Lepton>_<JetSel>_<ifOffZ>_<charge>

  //==== Linear
  if(XXX==0){
    m.samples_to_use = {"fake_Dijet", "chargeflip", "VV_excl", "Xgamma", "VVV", "top", "WW_double"};
    //m.samples_to_use = {"fake_HighdXY", "chargeflip", "VV_excl", "Xgamma", "VVV", "top", "WW_double"};
    m.histname_suffix = {

      //==== DiMuon
      "_DiMuon_0jets_SS", // SS 0jet CR
      "_DiMuon_1jets_SS", // SS 1jet CR
      "_DiMuon_1jets_0nlbjets_SS",
      "_DiMuon_1jets_0nlbjets_mllge110_SS",
      "_DiMuon_0nlbjets_SS",
      "_DiMuon_Inclusive1nlbjets_SS", // SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_DiMuon_LowCR_SS",
      "_DiMuon_LowCR_TwoJet_NoFatJet_SS",
      "_DiMuon_LowCR_OneJet_NoFatJet_SS",
      "_DiMuon_HighCR_SS",
      "_DiMuon_HighCR_TwoJet_NoFatJet_SS",
      "_DiMuon_HighCR_OneFatJet_SS",
      "_DiMuon_0jets_0nlbjets_dRllge2p5_SS",
      "_DiMuon_WpWp_CR_SS",

      //=== DiElectron
      "_DiElectron_0jets_SS", // SS 0jet CR
      "_DiElectron_1jets_SS", // SS 1jet CR
      "_DiElectron_0jets_OnZ_SS", // SS 0jet+OnZ CR (CF)
      "_DiElectron_1jets_OnZ_SS", // SS 1jet+OnZ CR (CF)
      "_DiElectron_Inclusive1nlbjets_SS", // SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_DiElectron_Inclusive1nlbjets_OffZ_SS",
      "_DiElectron_0jets_OffZ_SS",
      "_DiElectron_1jets_OffZ_SS",
      "_DiElectron_LowCR_SS",
      "_DiElectron_LowCR_TwoJet_NoFatJet_SS",
      "_DiElectron_LowCR_OneJet_NoFatJet_SS",
      "_DiElectron_HighCR_SS",
      "_DiElectron_HighCR_TwoJet_NoFatJet_SS",
      "_DiElectron_HighCR_OneFatJet_SS",
      "_DiElectron_1jets_0nlbjets_OffZ_SS",
      "_DiElectron_1jets_0nlbjets_mllge110_OffZ_SS",
      "_DiElectron_0nlbjets_OffZ_SS",
      "_DiElectron_0jets_0nlbjets_dRllge2p5_OffZ_SS",
      "_DiElectron_WpWp_CR_SS",
      "_DiElectron_OnZ_SS",


      //==== EMu
      "_EMu_0jets_SS", // SS 0jet CR
      "_EMu_1jets_SS", // SS 1jet CR
      "_EMu_Inclusive1nlbjets_SS", // SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_EMu_LowCR_SS",
      "_EMu_LowCR_TwoJet_NoFatJet_SS",
      "_EMu_LowCR_OneJet_NoFatJet_SS",
      "_EMu_HighCR_SS",
      "_EMu_1jets_0nlbjets_SS",
      "_EMu_1jets_0nlbjets_mllge110_SS",
      "_EMu_0nlbjets_SS",
      "_EMu_HighCR_TwoJet_NoFatJet_SS",
      "_EMu_HighCR_OneFatJet_SS",
      "_EMu_0jets_0nlbjets_dRllge2p5_SS",
      "_EMu_WpWp_CR_SS",


      //==== Merged
      "_DiLepton_0jets_SS", // SS 0jet CR
      "_DiLepton_1jets_SS", // SS 1jet CR
      "_DiLepton_0jets_OnZ_SS", // SS 0jet+OnZ CR (CF)
      "_DiLepton_1jets_OnZ_SS", // SS 1jet+OnZ CR (CF)
      "_DiLepton_Inclusive1nlbjets_SS", // SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_DiLepton_Inclusive1nlbjets_OffZ_SS",
      "_DiLepton_0jets_OffZ_SS",
      "_DiLepton_1jets_OffZ_SS",
      "_DiLepton_LowCR_SS",
      "_DiLepton_LowCR_TwoJet_NoFatJet_SS",
      "_DiLepton_LowCR_OneJet_NoFatJet_SS",
      "_DiLepton_HighCR_SS",
      "_DiLepton_HighCR_TwoJet_NoFatJet_SS",
      "_DiLepton_HighCR_OneFatJet_SS",
      "_DiLepton_1jets_0nlbjets_OffZ_SS",
      "_DiLepton_1jets_0nlbjets_mllge110_OffZ_SS",
      "_DiLepton_0nlbjets_OffZ_SS",
      "_DiLepton_0jets_0nlbjets_dRllge2p5_OffZ_SS",
      "_DiLepton_WpWp_CR_SS",
      "_DiLepton_OnZ_SS",


      //"_DiElectron_1jets_OnZ_SS",

    };
  }
  //==== Log
  //==== Use DY
  if(XXX==1){
    m.samples_to_use = {"VV_excl", "Xgamma_noDY", "VVV", "top", "DY", "WW_double"};
    m.histname_suffix = {
/*
      "_DiElectron_OnZ_OS", // OS OnZ CR (DY Prompt)
      "_DiElectron_0jets_OnZ_OS", // OS 0jet OnZ CR (DY Prompt)
      "_DiElectron_1jets_OnZ_OS", // OS 1jet OnZ CR (DY+jet)
      "_DiElectron_Inclusive1nlbjets_OS", // OS bjet>=1 (Prompt+NonPrompt)
      "_DiMuon_OnZ_OS", // OS OnZ CR (DY Prompt)
      "_DiMuon_0jets_OnZ_OS", // OS 0jet OnZ CR (DY Prompt)
      "_DiMuon_1jets_OnZ_OS", // OS 1jet OnZ CR (DY+jet)
      "_DiMuon_Inclusive1nlbjets_OS", // OS bjet>=1 (Prompt+NonPrompt)
*/
      "_DiMuon_0jets_OS",
      "_DiElectron_0jets_OnZ_OS",
    };
  }
  if(XXX==2){
    m.samples_to_use = {"fake_Dijet", "Xgamma_noDY", "chargeflip", "VV_excl", "DY", "VVV", "top", "WW_double"};
    m.histname_suffix = {
      "_DiElectron_Inclusive1nlbjets_METge50_OffZ_OS", // (TTBar Prompt)
      "_DiElectron_0nlbjets_OffZ_OS", // Low Mass mll region..
    };
  } 

  //============================
  //==== set variables to draw
  //============================
  
  m.histname = {
    "m_ll",
    "Njets", "Njets_nolepveto", "Nfwdjets", "Nbjets", "Nbjets_nolepveto", "Nbfwdjets",
    "leadingLepton_Pt", "leadingLepton_Eta", "leadingLepton_Type",
    "secondLepton_Pt", "secondLepton_Eta", "secondLepton_Type",
    "leadingJet_Pt", "leadingJet_Eta", 
    "secondJet_Pt", "secondJet_Eta",
    "leadingForwardJet_Pt", "leadingForwardJet_Eta", 
    "secondForwardJet_Pt", "secondForwardJet_Eta",
    "leadingNoLepVetoJet_Pt", "leadingNoLepVetoJet_Eta", 
    "secondNoLepVetoJet_Pt", "secondNoLepVetoJet_Eta",
    "PFMET", "PFMET_phi", "HT", "ST",
    "MET2overST",
    "Nvtx", "DeltaRl1l2", "Nevents",
    //==== Fatjet
    "Nfatjets",
    "WClosest_FatJet_Pt", "WClosest_FatJet_Eta", "WClosest_FatJet_Mass", "WClosest_FatJet_Tau21", "WClosest_FatJet_PrunedMass",
    //"m_Leadlfj_ptorder", "m_SubLeadlfj_ptorder", "m_llfj_ptorder",
    "m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest",
    //==== OneJet_NoFatJet
    "m_Leadlj", "m_SubLeadlj", "m_llj",
    //==== SF TEST
    //"InnerBarrelLepton_Pt", "OuterBarrelLepton_Pt", "EndCapLepton_Pt",
    //"InnerBarrelLepton_Eta", "OuterBarrelLepton_Eta", "EndCapLepton_Eta",
    "m_jj_jjWclosest", "m_lljj_jjWclosest", "m_Leadljj_jjWclosest", "m_SubLeadljj_jjWclosest",
    "m_jj_lljjWclosest", "m_lljj_lljjWclosest", "m_Leadljj_lljjWclosest", "m_SubLeadljj_lljjWclosest",
  };

  m.x_title = {
    "m(ll) (GeV)",
    "# of jets", "# of No-LeptonVeto jets", "# of forward jets", "# of b-jets", "# of No-LeptonVeto b-jets", "# of forward b-jets",
    "Leading Lepton p_{T} (GeV)", "Leading Lepton #eta", "Leading Lepton Type",
    "Subleading Lepton p_{T} (GeV)", "Subleading Lepton #eta", "Subleading Lepton Type",
    "Leading Jet p_{T} (GeV)", "Leading Jet #eta",
    "Subleading Jet p_{T} (GeV)", "Subleading Jet #eta",
    "Leading Forward Jet p_{T} (GeV)", "Leading Forward Jet #eta",
    "Subleading Forward Jet p_{T} (GeV)", "Subleading Forward Jet #eta",
    "Leading No-LeptonVeto Jet p_{T} (GeV)", "Leading No-LeptonVeto Jet #eta",
    "Subleading No-LeptonVeto Jet p_{T} (GeV)", "Subleading No-LeptonVeto Jet #eta",
    "#slash{E}_{T}^{miss} (GeV)", "#phi of #slash{E}_{T}^{miss}", "H_{T} (GeV)", "S_{T} (GeV)",
    "#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)",
    "# of vertices", "#DeltaR(l_{1},l_{2})", "onebin",
    //==== Fatjet
    "# of Fatjet",
    "Fatjet p_{T} (GeV)", "Fatjet #eta", "Fatjet Mass (GeV)", "Fatjet #tau_{21}", "Fatjet Pruned Mass (GeV)",
    //"m(Leading Lepton+Fatjet) (GeV)", "Subleading Lepton+Fatjet (GeV)", "m(ll+Fatjet) (GeV)",
    "m(Leading Lepton+Fatjet) (GeV)", "Subleading Lepton+Fatjet (GeV)", "m(ll+Fatjet) (GeV)",
    //==== OneJet_NoFatJet
    "l_{1}j_{ak4} invariant mass (GeV)", "l_{2}j_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}j_{ak4} invariant mass (GeV)",
    //==== SF TEST
    //"IB Lepton p_{T} [GeV]", "OB Lepton p_{T} [GeV]","EC Lepton p_{T} [GeV]",
    //"IB Lepton #eta", "OB Lepton #eta", "EC Lepton #eta",
    "jj_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}jj_{ak4} invariant mass (GeV)", "l_{1}jj_{ak4} invariant mass (GeV)", "l_{2}jj_{ak4} invariant mass (GeV)",
    "jj_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}jj_{ak4} invariant mass (GeV)", "l_{1}jj_{ak4} invariant mass (GeV)", "l_{2}jj_{ak4} invariant mass (GeV)",
  };

  m.units = {
    "GeV",
    "int", "int", "int", "int", "int", "int",
    "GeV", "", "int",
    "GeV", "", "int",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "", "GeV", "GeV",
    "GeV",
    "int", "", "int",
    //==== Fatjet
    "int",
    "GeV", "", "GeV", "", "GeV",
    //"GeV", "GeV", "GeV",
    "GeV", "GeV", "GeV",
    //==== OneJet_NoFatJet
    "GeV", "GeV", "GeV",
    //==== SF TEST
    //"GeV", "GeV", "GeV",
    //"", "", "",
    "GeV", "GeV", "GeV", "GeV",
    "GeV", "GeV", "GeV", "GeV",
  };

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    //==== PD
    if(m.histname_suffix.at(i).Contains("DiMuon")){
      m.PrimaryDataset.push_back("DoubleMuon");
      m.LeptonChannels.push_back(21);
    }
    else if(m.histname_suffix.at(i).Contains("DiElectron")){
      m.PrimaryDataset.push_back("DoubleEG");
      m.LeptonChannels.push_back(22);
    }
    else if(m.histname_suffix.at(i).Contains("EMu")){
      m.PrimaryDataset.push_back("MuonEG");
      m.LeptonChannels.push_back(23);
    }
    else if(m.histname_suffix.at(i).Contains("DiLepton")){
      m.PrimaryDataset.push_back("DiLepton");
      m.LeptonChannels.push_back(20);
    }
    else{
      cout << "ERROR : PD not correct" << endl;
      return;
    }

    if(m.histname_suffix.at(i).Contains("Inclusive1nlbjets")){
      m.RegionType.push_back(-4);
    }
    else if(m.histname_suffix.at(i).Contains("0jets_0nlbjets_dRllge2p5")){
      m.RegionType.push_back(-5);
    }
    else if(m.histname_suffix.at(i).Contains("LowCR")){
      if(m.histname_suffix.at(i).Contains("TwoJet_NoFatJet")) m.RegionType.push_back(-21);
      else if(m.histname_suffix.at(i).Contains("OneJet_NoFatJet")) m.RegionType.push_back(-22);
      else m.RegionType.push_back(-20);
    }
    else if(m.histname_suffix.at(i).Contains("HighCR")){
      if(m.histname_suffix.at(i).Contains("TwoJet_NoFatJet")) m.RegionType.push_back(-31);
      else if(m.histname_suffix.at(i).Contains("OneFatJet")) m.RegionType.push_back(-32);
      else m.RegionType.push_back(-30);
    }
    else{
      m.RegionType.push_back(0);
    }

    //==== Log plot boolean
    if(XXX==0) m.UseLogy.push_back(-1);
    else if(XXX==1) m.UseLogy.push_back(10);
    else if(XXX==2) m.UseLogy.push_back(-1);
    else m.UseLogy.push_back(-1);

    if(ScaleMC) m.ApplyMCNormSF.push_back(true);
    else m.ApplyMCNormSF.push_back(false);

    m.drawdata.push_back(true);
    m.drawratio.push_back(true);

  }

  //==== For Quick Test
  //==== Ignore all, and reset all here
  if(XXX==-1){
    m.samples_to_use = {"fake_Dijet", "chargeflip", "VV_excl", "Xgamma", "VVV", "top", "WW_double"};
    m.histname_suffix = {"_DiElectron_0jets_SS"};
    m.PrimaryDataset = {"DoubleEG"};
    m.LeptonChannels = {22};
    m.RegionType = {0};
    m.drawdata = {true};
    m.drawratio = {true};
    m.UseLogy = {-1};
    m.histname = {"m_ll"};
    m.x_title = {"m(ll) (GeV)"};
    m.units = {"GeV"};
    if(ScaleMC) m.ApplyMCNormSF = {true};
    else m.ApplyMCNormSF = {false};
  }

/*
  //==== FIXME test
  m.histname = {
    //"m_jj_jjWclosest", "m_lljj_jjWclosest", "m_Leadljj_jjWclosest", "m_SubLeadljj_jjWclosest",
    //"m_SubLeadljj_jjWclosest",
"secondLepton_Pt",
//"WClosest_FatJet_Tau21"
"leadingLepton_Pt",
  };
  m.x_title = {
    //"jj_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}jj_{ak4} invariant mass (GeV)", "l_{1}jj_{ak4} invariant mass (GeV)", "l_{2}jj_{ak4} invariant mass (GeV)",
    //"l_{2}jj_{ak4} invariant mass (GeV)",
    "Subleading Lepton p_{T} (GeV)",
"Leading Lepton p_{T} (GeV)",
  };	
  m.units = {
    //"GeV", "GeV", "GeV", "GeV",
"GeV", "GeV",
  };
*/

  cout << "m.histname.size() = " <<  m.histname.size() << endl;
  cout << "m.x_title.size() = " << m.x_title.size() << endl;
  cout << "m.units.size() = " << m.units.size() << endl;
  if(m.histname.size()==m.x_title.size() && m.x_title.size()==m.units.size()){
    cout << "--> OKAY" << endl;
  }
  else{
    cout << "--> WRONG" << endl;
    return;
  }
  cout << "Histname\tXTitle\tUnit" << endl;
  for(unsigned int i=0; i<m.histname.size(); i++){
    cout << m.histname.at(i) << "\t" << m.x_title.at(i) << "\t" << m.units.at(i) << endl;
  }

  //====================
  //==== make bkg list
  //====================

  m.make_bkglist();

  //=====================
  //==== Fill MCNorm SF
  //=====================

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.bkglist);

  //======================
  //==== Get Systematics
  //======================

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");

  //=============
  //==== rebins
  //=============
  

  //==== script to generate rebins
  ofstream skeleton_rebins("./data/CR_rebins.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_rebins
      //<< "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_rebins.close();


  m.SetRebins(WORKING_DIR+"/data/"+dataset+"/CR_rebins.txt");

  //=============
  //==== y_maxs
  //=============
  

  //==== script to generate rebins
  ofstream skeleton_y_maxs("./data/CR_yaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_y_maxs
      //<< "  m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_y_maxs.close();


  //==== default max
  m.default_y_max = 2000.;
  m.default_y_min = 0.;

  m.SetYAxis(WORKING_DIR+"/data/"+dataset+"/CR_yaxis.txt"); 

  //=============
  //==== x_mins
  //=============


  //==== script to generate rebins
  ofstream skeleton_x_mins("./data/CR_xaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_x_mins
      //<< "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<"\t"<<-999<<endl;
    }
  }
  skeleton_x_mins.close();



  m.SetXAxis(WORKING_DIR+"/data/"+dataset+"/CR_xaxis.txt");

  //===============
  //==== k-factor
  //===============
  
  m.k_factor = 1.;
  
  //=================================
  //==== mixing at generation level
  //=================================
  
  m.log_of_generation_mixing = -2.;
  
  //===============================
  //==== prepare plot directories
  //===============================
  
  m.plotpath = ENV_PLOT_PATH+"/"+m.data_class+"/CR/";
  m.make_plot_directory();
  
  //==========================
  //==== finally, draw plots
  //==========================
  
  m.draw_hist();
  
}






