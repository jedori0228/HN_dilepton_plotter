#include "Plotter.cc"
#include <fstream>

void Draw_SR(bool ScaleMC=true, int XXX=0){
  
  //==============
  //==== get env
  //==============
  
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

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
    "WZTo3LNu_powheg", "WZto2L2Q_amcatnlo",
    "ZZTo4L_powheg", "ZZTo2L2Nu_Powheg", "ZZTo2L2Q_Powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau",
    "WWTo2L2Nu", "ggWWto2L2Nu",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TTJets_aMC"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  m.map_sample_string_to_list["top"] = {"TTLL_powheg", "ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["Wgamma"] = {"WgstarToLNuEE", "WgstarToLNuMuMu"};
  m.map_sample_string_to_list["Zgamma"] = {"ZGto2LG"};
  m.map_sample_string_to_list["Vgamma"] = {"WgstarToLNuEE", "WgstarToLNuMuMu", "ZGto2LG"};
  m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "WgstarToLNuEE", "WgstarToLNuMuMu", "ZGto2LG"};
  m.map_sample_string_to_list["Xgamma_noDY"] = {"TG", "TTG", "WgstarToLNuEE", "WgstarToLNuMuMu"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("VV", kSpring-1);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("VV", kSpring-1);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("VVV", kSpring+10);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Zgamma"] = make_pair("Z#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Vgamma"] = make_pair("V#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Xgamma_noDY"] = make_pair("X#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Non-prompt", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Non-prompt", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Non-prompt", 870);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Non-prompt", 870);
  m.map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Non-prompt", 870);
  m.map_sample_string_to_legendinfo["chargeflip"] = make_pair("Charge-flip", kYellow);
  
  //===============================
  //==== set and make sample list
  //===============================

  //==== _Di<Lepton>_<JetSel>_<ifOffZ>_<charge>

  //==== SS
  if(XXX==0){
    m.samples_to_use = {"chargeflip", "fake_Dijet", "Xgamma", "VV_excl", "VVV", "top", "WW_double"};

    m.histname_suffix = {
      // dimu
      // diel
      "_DiElectron_Preselection_SS",
      "_DiElectron_Preselection_Inclusive2jets_SS",
      "_DiElectron_Preselection_Inclusive1fatjets_SS",
      //"_DiElectron_Low_SS",
      //"_DiElectron_Medium_SS",
      //"_DiElectron_High_SS",
    };
  }
  //==== OS
  if(XXX==1){
    m.samples_to_use = {"VV_excl", "Xgamma_noDY", "fake_Dijet", "VVV", "top", "DY", "WW_double"};
    m.histname_suffix = {
      // dimu
      //"_DiMuon_Low_OS",
      //"_DiMuon_Medium_OS",
      //"_DiMuon_High_OS",
      // diel
      "_DiElectron_Preselection_OS",
      //"_DiElectron_Low_OS",
      //"_DiElectron_Medium_OS",
      //"_DiElectron_High_OS",
    };
  }
  if(XXX==2){
    m.samples_to_use = {"chargeflip", "fake_Dijet", "VV_excl", "VVV", "top", "WW_double", "DY"};

    m.histname_suffix = {
      // dimu
      // diel
      "_DiElectron_Preselection_OS",
      //"_DiElectron_Low_SS",
      //"_DiElectron_Medium_SS",
      //"_DiElectron_High_SS",
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
    "m_jjptorder", "m_lljjptorder", "m_Leadljjptorder", "m_SubLeadljjptorder",
    "Njets", "Njets_nolepveto", "Nfwdjets", "Nbjets", "Nbjets_nolepveto", "Nbfwdjets",
    "leadingLepton_Pt", "leadingLepton_Eta",
    "secondLepton_Pt", "secondLepton_Eta",
    "leadingJet_Pt", "leadingJet_Eta", 
    "secondJet_Pt", "secondJet_Eta",
    "leadingForwardJet_Pt", "leadingForwardJet_Eta", 
    "secondForwardJet_Pt", "secondForwardJet_Eta",
    "leadingNoLepVetoJet_Pt", "leadingNoLepVetoJet_Eta", 
    "secondNoLepVetoJet_Pt", "secondNoLepVetoJet_Eta",
    "PFMET", "PFMET_phi", "HT", "ST", "MET2overST", "MCT",
    "Nvtx", "DeltaRl1l2",
    //==== FatJet Leading
    "FatJet_Pt", "FatJet_Eta", "FatJet_PrunedMass", "FatJet_SoftDropMass", "FatJet_Tau21", "FatJet_Tau32",
    "m_fatjet", "m_llfatjet", "m_Leadlfatjet", "m_SubLeadlfatjet",
    "DeltaRLeadl_fatjet", "DeltaRSubLeadl_fatjet", "DeltaRLeadl_SubLeadlfatjet", "DeltaRSubLeadl_Leadlfatjet",
    //==== FatJet Closeset to W
    "FatJet_Wclosest_Pt", "FatJet_Wclosest_Eta", "FatJet_Wclosest_PrunedMass", "FatJet_Wclosest_SoftDropMass", "FatJet_Wclosest_Tau21", "FatJet_Wclosest_Tau32", 
    "m_fatjet_Wclosest", "m_llfatjet_Wclosest", "m_Leadlfatjet_Wclosest", "m_SubLeadlfatjet_Wclosest",
    "DeltaRLeadl_fatjet_Wclosest", "DeltaRSubLeadl_fatjet_Wclosest", "DeltaRLeadl_SubLeadlfatjet_Wclosest", "DeltaRSubLeadl_Leadlfatjet_Wclosest",
  };

  m.x_title = {
    "m(ll) [GeV]",
    //==== Jets for High Mass
    "m(jj_{W}) [GeV]",  "m(lljj_{W}) [GeV]", "m(Leading Lepton+jj_{W}) [GeV]", "m(Sub-Leading Lepton+jj_{W}) [GeV]",
    "#DeltaR(jj_{W})",
    "#DeltaR(Leading Lepton,jj_{W})", "#DeltaR(Sub-Leading Lepton,jj_{W})", 
    "#DeltaR(Leading Lepton,Sub-Leading Lepton+jj_{W})", "#DeltaR(Sub-Leading Lepton,Leading Lepton+jj_{W})",
    //==== Jets for Low Mass
    "m(jj_{W}) [GeV]",  "m(lljj_{W}) [GeV]", "m(Leading Lepton+jj_{W}) [GeV]", "m(Sub-Leading Lepton+jj_{W}) [GeV]",
    "#DeltaR(jj_{W})",
    "#DeltaR(Leading Lepton,jj_{W})", "#DeltaR(Sub-Leading Lepton,jj_{W})",
    "#DeltaR(Leading Lepton,Sub-Leading Lepton+jj_{W})", "#DeltaR(Sub-Leading Lepton,Leading Lepton+jj_{W})",
    //==== Laeding dijet
    "m(j_{1}j_{2}) [GeV]",  "m(llj_{1}j_{2}) [GeV]", "m(Leading Lepton+j_{1}j_{2}) [GeV]", "m(Sub-Leading Lepton+j_{1}j_{2}) [GeV]",
    "# of jets", "# of No-LeptonVeto jets", "# of forward jets", "# of b-jets", "# of No-LeptonVeto b-jets", "# of forward b-jets",
    "Leading Lepton p_{T} [GeV]", "Leading Lepton #eta",
    "Sub-Leading Lepton p_{T} [GeV]", "Sub-Leading Lepton #eta",
    "Leading Jet p_{T} [GeV]", "Leading Jet #eta",
    "Sub-Leading Jet p_{T} [GeV]", "Sub-Leading Jet #eta",
    "Leading Forward Jet p_{T} [GeV]", "Leading Forward Jet #eta",
    "Sub-Leading Forward Jet p_{T} [GeV]", "Sub-Leading Forward Jet #eta",
    "Leading No-LeptonVeto Jet p_{T} [GeV]", "Leading No-LeptonVeto Jet #eta",
    "Sub-Leading No-LeptonVeto Jet p_{T} [GeV]", "Sub-Leading No-LeptonVeto Jet #eta",
    "#slash{E}_{T}^{miss} [GeV]", "#phi of #slash{E}_{T}^{miss}", "H_{T} [GeV]", "S_{T} [GeV]", "#slash{E}_{T}^{miss}^{2}/S_{T} [GeV]", "m_{CT}(j_{1},j_{2}) [GeV]",
    "# of vertices", "#DeltaR(l_{1},l_{2})",
    //==== FatJet Leading
    "Leading Fat Jet p_{T} [GeV]", "Leading Fat Jet #eta", "Leading Fat Jet Pruned Mass [GeV]", "Leading Fat Jet Soft Drop Mass [GeV]", "Leading Fat Jet #tau_{2}/#tau_{1}", "Leading Fat Jet #tau_{3}/#tau_{2}",
    "m(Leading Fat Jet) [GeV]", "m(ll+Fat Jet) [GeV]", "m(Leading Lepton+Fat Jet) [GeV]", "m(Sub-Leading Lepton+Fat Jet) [GeV]",
    "DeltaR(Leading Lepton,Fat Jet)", "DeltaR(Sub-Leading Lepton,Fat Jet)", "DeltaR(Leading Lepton,Sub-Leading Lepton+FatJet)", "DeltaR(Sub-Leading Lepton,Leading Lepton+FatJet)",
    //==== FatJet Closeset to W
    "Leading Fat Jet p_{T} [GeV]", "Leading Fat Jet #eta", "Leading Fat Jet Pruned Mass [GeV]", "Leading Fat Jet Soft Drop Mass [GeV]", "Leading Fat Jet #tau_{2}/#tau_{1}", "Leading Fat Jet #tau_{3}/#tau_{2}",
    "m(Leading Fat Jet) [GeV]", "m(ll+Fat Jet) [GeV]", "m(Leading Lepton+Fat Jet) [GeV]", "m(Sub-Leading Lepton+Fat Jet) [GeV]",        
    "DeltaR(Leading Lepton,Fat Jet)", "DeltaR(Sub-Leading Lepton,Fat Jet)", "DeltaR(Leading Lepton,Sub-Leading Lepton+FatJet)", "DeltaR(Sub-Leading Lepton,Leading Lepton+FatJet)",
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
    "GeV", "GeV", "GeV", "GeV",
    "int", "int", "int", "int", "int", "int",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "", "GeV", "GeV", "GeV", "GeV",
    "int", "",
    //==== Laeding dijet
    "GeV", "", "GeV", "GeV", "", "",
    "GeV", "GeV", "GeV", "GeV",
    "", "", "", "",
    //==== FatJet Leading
    "GeV", "", "GeV", "GeV", "", "",
    "GeV", "GeV", "GeV", "GeV",
    "", "", "", "",
  };

  //==== TEST
  if(XXX==-1){
    m.samples_to_use = {"chargeflip", "fake_Dijet", "VV_excl", "VVV", "top", "WW_double", "Vgamma"};

    m.histname_suffix = {"_DiElectron_2jets_OffZ_SS"};
    m.PrimaryDataset = {"DoubleEG"};
    m.UseLogy = {-1};
    m.histname = {"m_ll"};
    m.x_title = {"m(ll) [GeV]"};
    m.units = {"GeV"};

  }

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    //==== PD
    if(m.histname_suffix.at(i).Contains("DiMuon")) m.PrimaryDataset.push_back("DoubleMuon");
    if(m.histname_suffix.at(i).Contains("DiElectron")) m.PrimaryDataset.push_back("DoubleEG");

    //==== Log plot boolean
    if(XXX==0) m.UseLogy.push_back(-1);
    else if(XXX==1) m.UseLogy.push_back(100);
    else if(XXX==2) m.UseLogy.push_back(-1);
    else m.UseLogy.push_back(-1);

    if(ScaleMC) m.ApplyMCNormSF.push_back(true);
    else m.ApplyMCNormSF.push_back(false);
    m.drawdata.push_back(false);
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
  
  //m.signal_mass = {40, 60, 200, 500, 1000, -200, -500, -1000};
  //m.signal_color = {kRed, kMagenta, kBlue, kGray, kBlack, kBlue, kGray, kBlack};

  m.signal_mass =  {40,   60,      70,        100,     200,    500,     700,   1000,   -200,  -500,     -1000};
  m.signal_color = {kRed, kOrange, kYellow+2, kGreen,  kBlue,  kViolet, kGray, kBlack, kBlue, kViolet,  kBlack};

  m.signal_draw = {true, true, true, true, true, true, true, true, true, true, true};

  //====================================
  //==== set signal coupling constants
  //====================================

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    //==== SS
    if(XXX!=2){
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 40)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 60)] = 0.0001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 70)] = 0.001;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 100)] = 0.01;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 200)] = 0.1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 500)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 700)] = 1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 1000)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -200)] = 0.1;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -500)] = 1.;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -1000)] = 10.;
    }

    //==== OS
    else{
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 40)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 60)] = 10;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 200)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 500)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), 1000)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -200)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -500)] = 100;
      m.coupling_constants[make_pair(m.histname_suffix.at(i), -1000)] = 100;
    }
  }


  //=====================================
  //==== set signal mass for each class
  //=====================================

  m.map_class_to_signal_mass[Plotter::class1] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  m.map_class_to_signal_mass[Plotter::class2] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  m.map_class_to_signal_mass[Plotter::lowmass] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  m.map_class_to_signal_mass[Plotter::class3] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  m.map_class_to_signal_mass[Plotter::class4] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  m.map_class_to_signal_mass[Plotter::mediummass] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};
  m.map_class_to_signal_mass[Plotter::highmass] = {5, 10, 20, 30, 40, 50, 60, 70, 90, 100, 150, 200, 300, 400, 500, 700, 1000};

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
  
  m.make_plot_directory();
  
  //==========================
  //==== finally, draw plots
  //==========================
  
  m.draw_hist();
  
}






