#include "Plotter.cc"
#include <fstream>

void Draw_SR(int XXX=0){

  bool ScaleMC = true;

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
  m.map_sample_string_to_list["top_tt"] = {"TT_powheg", "ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted"};
  //m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  m.map_sample_string_to_list["fake_Dijet_LooseBJet"] = {"fake_Dijet_LooseBJet"};
  m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  m.map_sample_string_to_list["prompt"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted", "WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ", "WWW", "WWZ", "WZZ", "ZZZ", "ttW", "ttZ", "ttH_nonbb", "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};

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
  m.map_sample_string_to_legendinfo["top_tt"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_Dijet_LooseBJet"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["chargeflip"] = make_pair("Mismeas. charge background", kYellow);
  m.map_sample_string_to_legendinfo["prompt"] = make_pair("Prompt background", kSpring-1);
  
  //===============================
  //==== set and make sample list
  //===============================

  //==== _Di<Lepton>_<JetSel>_<ifOffZ>_<charge>

  //==== SS
  if(XXX==0){
    //m.samples_to_use = {"chargeflip", "Xgamma", "fake_Dijet", "VV_excl", "VVV", "top", "WW_double"};
    m.samples_to_use = {"chargeflip", "fake_Dijet", "prompt"};

    m.histname_suffix = {

      //==== DiMuon
      "_DiMuon_Preselection_SS", // nobjet, jet>=2;
      "_DiMuon_Low_SS",
      "_DiMuon_Low_TwoJet_NoFatJet_SS",
      "_DiMuon_Low_OneJet_NoFatJet_SS",
      "_DiMuon_High_SS",
      "_DiMuon_High_TwoJet_NoFatJet_SS",
      "_DiMuon_High_OneFatJet_SS",
      "_DiMuon_Preselection_secondptge20_SS",

      //==== DiElectron
      "_DiElectron_Preselection_SS", // OffZ, nobjet, jet>=2;
      "_DiElectron_Low_SS",
      "_DiElectron_Low_TwoJet_NoFatJet_SS",
      "_DiElectron_Low_OneJet_NoFatJet_SS",
      "_DiElectron_High_SS",
      "_DiElectron_High_TwoJet_NoFatJet_SS",
      "_DiElectron_High_OneFatJet_SS",

      //==== EMu
      "_EMu_Preselection_SS", // nobjet, jet>=2;
      "_EMu_Low_SS",
      "_EMu_Low_TwoJet_NoFatJet_SS",
      "_EMu_Low_OneJet_NoFatJet_SS",
      "_EMu_High_SS",
      "_EMu_High_TwoJet_NoFatJet_SS",
      "_EMu_High_OneFatJet_SS",
      "_EMu_Preselection_ElectronSubLead_SS",
      "_EMu_Preselection_MuonSubLead_SS",



    };
  }
  //==== Paper
  if(XXX==1){
    m.samples_to_use = {"chargeflip", "fake_Dijet", "prompt"};
    m.histname_suffix = {


      "_DiLepton_Preselection_SS", // OffZ, nobjet, jet>=2;
      "_DiLepton_Low_SS",
      "_DiLepton_Low_TwoJet_NoFatJet_SS",
      "_DiLepton_Low_OneJet_NoFatJet_SS",
      "_DiLepton_High_SS",
      "_DiLepton_High_TwoJet_NoFatJet_SS",
      "_DiLepton_High_OneFatJet_SS",


      //"_DiLepton_High_OneFatJet_SS",

    };
  }

  //============================
  //==== set variables to draw
  //============================
  
  m.histname = {
    "m_ll",
    //==== Jets for High Mass
    "m_jj_jjWclosest", "m_lljj_jjWclosest", "m_Leadljj_jjWclosest", "m_SubLeadljj_jjWclosest",
    "DeltaRjjWclosest",
    "DeltaRLeadl_jjWclosest", "DeltaRSubLeadl_jjWclosest",
    "DeltaRLeadl_SubLeadljjWclosest", "DeltaRSubLeadl_LeadljjWclosest",
    //==== Jets for Low Mass
    "m_jj_lljjWclosest", "m_lljj_lljjWclosest", "m_Leadljj_lljjWclosest", "m_SubLeadljj_lljjWclosest",
    "DeltaRlljjWclosest",
    "DeltaRLeadl_lljjWclosest", "DeltaRSubLeadl_lljjWclosest",
    "DeltaRLeadl_SubLeadllljjWclosest", "DeltaRSubLeadl_LeadllljjWclosest",
    //==== Laeding dijet
    //"m_jjptorder", "m_lljjptorder", "m_Leadljjptorder", "m_SubLeadljjptorder",
    "Njets", "Njets_nolepveto", "Nfwdjets", "Nbjets", "Nbjets_nolepveto", "Nbfwdjets",
    "leadingLepton_Pt", "leadingLepton_Eta", "leadingLepton_Type",
    "secondLepton_Pt", "secondLepton_Eta", "secondLepton_Type",
    "leadingJet_Pt", "leadingJet_Eta", 
    "secondJet_Pt", "secondJet_Eta",
    "leadingForwardJet_Pt", "leadingForwardJet_Eta", 
    "secondForwardJet_Pt", "secondForwardJet_Eta",
    "leadingNoLepVetoJet_Pt", "leadingNoLepVetoJet_Eta", 
    "secondNoLepVetoJet_Pt", "secondNoLepVetoJet_Eta",
    //==== SumPt
    "PFMET", "PFMET_phi", "HT", "ST", "MET2overST", "MCT",
    "Nvtx", "DeltaRl1l2", "Nevents",
    //==== Fatjet
    "Nfatjets",
    "WClosest_FatJet_Pt", "WClosest_FatJet_Eta", "WClosest_FatJet_Mass", "WClosest_FatJet_Tau21", "WClosest_FatJet_PrunedMass",
    //"m_Leadlfj_ptorder", "m_SubLeadlfj_ptorder", "m_llfj_ptorder",
    "m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest",
    //==== OneJet_NoFatJet
    "m_Leadlj", "m_SubLeadlj", "m_llj",
  };

  m.x_title = {
    "l^{#pm}l^{#pm} invariant mass (GeV)",
    //==== Jets for High Mass
    "jj_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}jj_{ak4} invariant mass (GeV)", "l_{1}jj_{ak4} invariant mass (GeV)", "l_{2}jj_{ak4} invariant mass (GeV)",
    "#DeltaR(jj_{W,ak4})",
    "#DeltaR(Leading lepton,jj_{W,ak4})", "#DeltaR(Subleading lepton,jj_{W,ak4})", 
    "#DeltaR(Leading lepton,Subleading lepton+jj_{W,ak4})", "#DeltaR(Subleading lepton,Leading lepton+jj_{W,ak4})",
    //==== Jets for Low Mass
    "jj_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}jj_{ak4} invariant mass (GeV)", "l_{1}jj_{ak4} invariant mass (GeV)", "l_{2}jj_{ak4} invariant mass (GeV)",
    "#DeltaR(jj_{W})",
    "#DeltaR(Leading lepton,jj_{W,ak4})", "#DeltaR(Subleading lepton,jj_{W,ak4})",
    "#DeltaR(Leading lepton,Subleading lepton+jj_{W,ak4})", "#DeltaR(Subleading lepton,Leading lepton+jj_{W,ak4})",
    //==== Laeding dijet
    //"m(j_{1}j_{2}) (GeV)",  "m(llj_{1}j_{2}) (GeV)", "m(Leading Lepton+j_{1}j_{2}) (GeV)", "m(Subleading Lepton+j_{1}j_{2}) (GeV)",
    "# of jets", "# of No-LeptonVeto jets", "# of forward jets", "# of b-jets", "# of No-LeptonVeto b-jets", "# of forward b-jets",
    "Leading lepton p_{T} (GeV)", "Leading lepton #eta", "Leading lepton Type",
    "Subleading lepton p_{T} (GeV)", "Subleading lepton #eta", "Subleading lepton type",
    "Leading j_{ak4} p_{T} (GeV)", "Leading j_{ak4} #eta",
    "Subleading j_{ak4} p_{T} (GeV)", "Subleading j_{ak4} #eta",
    "Leading forward j_{ak4} p_{T} (GeV)", "Leading forward j_{ak4} #eta",
    "SubleadingfForward j_{ak4} p_{T} (GeV)", "Subleading forward j_{ak4} #eta",
    "Leading no-leptonVeto j_{ak4} p_{T} (GeV)", "Leading no-leptonVeto j_{ak4} #eta",
    "Subleading no-leptonVeto j_{ak4} p_{T} (GeV)", "Subleading no-leptonVeto j_{ak4} #eta",
    //==== SumPt
    "#slash{E}_{T}^{miss} (GeV)", "#phi of #slash{E}_{T}^{miss}", "H_{T} (GeV)", "S_{T} (GeV)", "#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)", "m_{CT}(j_{1},j_{2}) (GeV)",
    "# of vertices", "#DeltaR(l_{1},l_{2})", "onebin",
    //==== Fatjet
    "# of j_{ak8}",
    "j_{ak8} p_{T} (GeV)", "j_{ak8} #eta", "j_{ak8} invariant mass (GeV)", "j_{ak8} #tau_{21}", "j_{ak8} pruned mass (GeV)",
    //"l_{1}j_{ak8} invariant mass (GeV)", "l_{2}j_{ak8} invariant mass (GeV)", "l^{#pm}l^{#pm}j_{ak8} invariant mass (GeV)",
    "l_{1}j_{ak8} invariant mass (GeV)", "l_{2}j_{ak8} invariant mass (GeV)", "l^{#pm}l^{#pm}j_{ak8} invariant mass (GeV)",
    //==== OneJet_NoFatJet
    "l_{1}j_{ak4} invariant mass (GeV)", "l_{2}j_{ak4} invariant mass (GeV)", "l^{#pm}l^{#pm}j_{ak4} invariant mass (GeV)",
  };

  m.units = {
    "GeV",
    //==== Jets for High Mass
    "GeV", "GeV", "GeV", "GeV",
    "",
    "", "",
    "", "",
    //==== Jets for Low Mass
    "GeV", "GeV", "GeV", "GeV",
    "",
    "", "",
    "", "",
    //==== Laeding dijet
    //"GeV", "GeV", "GeV", "GeV",
    "int", "int", "int", "int", "int", "int",
    "GeV", "", "int",
    "GeV", "", "int",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    //==== SumPt
    "GeV", "", "GeV", "GeV", "GeV", "GeV",
    "int", "", "int",
    //==== Fatjet
    "int",
    "GeV", "", "GeV", "", "GeV",
    //"GeV", "GeV", "GeV",
    "GeV", "GeV", "GeV",
    //==== OneJet_NoFatJet
    "GeV", "GeV", "GeV",
  };

  //==== TEST
  if(XXX==-1){
    m.samples_to_use = {"chargeflip", "Xgamma", "fake_Dijet", "VV_excl", "VVV", "top", "WW_double"};

    m.histname_suffix = {"_DiMuon_Preselection_SS"};
    m.PrimaryDataset = {"DoubleMuon"};
    m.LeptonChannels = {21};
    m.RegionType = {0};
    m.UseLogy = {-1};
    m.histname = {"m_lljj_lljjWclosest"};
    m.x_title = {"m(lljj_{W}) (GeV)"};
    m.units = {"GeV"};

  }

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

    if(m.histname_suffix.at(i).Contains("Preselection")){
      m.RegionType.push_back(1);
    }
    else if(m.histname_suffix.at(i).Contains("Low")){
      if(m.histname_suffix.at(i).Contains("TwoJet_NoFatJet")) m.RegionType.push_back(21);
      else if(m.histname_suffix.at(i).Contains("OneJet_NoFatJet")) m.RegionType.push_back(22);
      else m.RegionType.push_back(20);
    }
    else if(m.histname_suffix.at(i).Contains("High")){
      if(m.histname_suffix.at(i).Contains("TwoJet_NoFatJet")) m.RegionType.push_back(31);
      else if(m.histname_suffix.at(i).Contains("OneFatJet")) m.RegionType.push_back(32);
      else m.RegionType.push_back(30);
    }
    else{
      m.RegionType.push_back(0);
    }

    //==== Log plot boolean
    if(XXX==0) m.UseLogy.push_back(-1);
    else if(XXX==1) m.UseLogy.push_back(-1);
    else m.UseLogy.push_back(-1);

    if(ScaleMC) m.ApplyMCNormSF.push_back(true);
    else m.ApplyMCNormSF.push_back(false);

    //if(m.histname_suffix.at(i).Contains("Preselection")) m.drawdata.push_back(true);
    //else m.drawdata.push_back(false);

    //m.drawdata.push_back(false);

    m.drawdata.push_back(true);

    //if(m.histname_suffix.at(i).Contains("DiLepton")) m.drawratio.push_back(false);
    //else m.drawratio.push_back(true);

    m.drawratio.push_back(true);

  }

/*
  //==== FIXME test
  m.histname = {
    "m_Leadlfj_fjWclosest", 
//"m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest",
  };
  m.x_title = {
    "l_{1}j_{ak8} invariant mass (GeV)", 
//"l_{2}j_{ak8} invariant mass (GeV)", "l^{#pm}l^{#pm}j_{ak8} invariant mass (GeV)",
  };
  m.units = {
    "GeV", 
//"GeV", "GeV",
  };
*/
/*
  //==== FIXME test
  m.histname = {"m_Leadlj"};
  m.x_title = {"m(Leading Lepton+j) (GeV)"};
  m.units = {"GeV"};
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

  //=============================
  //==== set signal mass points
  //=============================

  if(XXX==0){
  //==== general AN
    m.signal_mass  = {40,   60,      70,        100,     300,    500,     800,   1200,   -800,  -1200};
    m.signal_color = {kRed, kOrange, kYellow+2, kGreen,  kBlue,  kViolet, kGray, kBlack, kGray, kBlack};
    m.signal_draw  = {true, true,    true,      true,    true,   true,    true,  true,   true,  true};
  }

  //==== PAS
  if(XXX==1){
    m.signal_mass  = {40,   60,    200,  400,   800,  -800, 1000};
    m.signal_color = {kRed, kBlue, kRed, kBlue, kRed, kRed, kBlue};
    m.signal_draw  = {true, true,  true, true,  true, true, true};
  }

  //====================================
  //==== set signal coupling constants
  //====================================

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    //==== SS
    if(XXX!=2){
/*
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 40)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 60)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 70)] = 0.001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 100)] = 0.01;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 300)] = 0.1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 500)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 800)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 1200)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -500)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -800)] = 100.;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -1200)] = 100.;
*/
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 40)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 50)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 60)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 70)] = 0.001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 100)] = 0.01;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 200)] = 0.1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 300)] = 0.1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 400)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 500)] = 0.1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 800)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 1000)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 1200)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -500)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -800)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -1200)] = 1.0;


    }

    //==== OS
    else{
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 40)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 60)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 300)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 500)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 1200)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -500)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -800)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -1200)] = 100;
    }
  }


  //=====================================
  //==== set signal mass for each class
  //=====================================

  for(unsigned int i=0; i<m.signal_mass.size(); i++){
    int this_mass = m.signal_mass.at(i);
    if(fabs(this_mass)<=80){
      m.map_class_to_signal_mass[Plotter::low].push_back( this_mass );
      m.map_class_to_signal_mass[Plotter::low_SR1].push_back( this_mass );
      m.map_class_to_signal_mass[Plotter::low_SR2].push_back( this_mass );
    }
    else{
      m.map_class_to_signal_mass[Plotter::high].push_back( this_mass );
      m.map_class_to_signal_mass[Plotter::high_SR1].push_back( this_mass );
      m.map_class_to_signal_mass[Plotter::high_SR2].push_back( this_mass );
    }
  }
  m.map_class_to_signal_mass[Plotter::high_SR1] = {200, 400};
  //m.map_class_to_signal_mass[Plotter::high_SR2] = {800, 1000, -800}; //FIXME
  m.map_class_to_signal_mass[Plotter::high_SR2] = {800, 1000};
  m.AllSignalClasses = {Plotter::no_class, Plotter::low_SR1, Plotter::low_SR2, Plotter::high_SR1, Plotter::high_SR2};

  //=============
  //==== rebins
  //=============
  
  //==== script to generate rebins
  ofstream skeleton_rebins("./data/SR_rebins.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_rebins
      //<< "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_rebins.close();

  m.SetRebins(WORKING_DIR+"/data/"+dataset+"/SR_rebins.txt");

  //=============
  //==== y_maxs
  //=============
  
  //==== script to generate rebins
  ofstream skeleton_y_maxs("./data/SR_yaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_y_maxs
      //<< "  m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_y_maxs.close();


  //==== default max
  m.default_y_max = 20.;
  m.default_y_min = 0.;

  m.SetYAxis(WORKING_DIR+"/data/"+dataset+"/SR_yaxis.txt"); 

  //=============
  //==== x_mins
  //=============


  //==== script to generate rebins
  ofstream skeleton_x_mins("./data/SR_xaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_x_mins
      //<< "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<"\t"<<-999<<endl;
    }
  }
  skeleton_x_mins.close();



  m.SetXAxis(WORKING_DIR+"/data/"+dataset+"/SR_xaxis.txt");

  //===============
  //==== k-factor
  //===============
  
  m.k_factor = 1;
  
  //=================================
  //==== mixing at generation level
  //=================================
  
  m.log_of_generation_mixing = -2.;
  
  //===============================
  //==== prepare plot directories
  //===============================
  
  m.plotpath = ENV_PLOT_PATH+"/"+m.data_class+"/SR/";
  m.make_plot_directory();
  
  //==========================
  //==== finally, draw plots
  //==========================
  
  m.draw_hist();
  
}






