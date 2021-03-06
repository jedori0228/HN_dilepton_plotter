#include "Plotter.cc"
#include <fstream>

void Draw_CR(bool ScaleMC=true, int XXX=0){

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

  //==== Linear
  if(XXX==0){
    m.samples_to_use = {"fake_Dijet", "chargeflip", "VV_excl", "Xgamma", "VVV", "top", "WW_double"};
    m.histname_suffix = {
      // dimu
      //"_DiMuon_0jets_SS", // SS 0jet CR
      //"_DiMuon_1jets_SS", // SS 1jet CR
      //"_DiMuon_0jets_OnZ_SS", // SS-0jet+OnZ CR (CF)
      //"_DiMuon_1jets_OnZ_SS", // SS-1jet+OnZ CR (CF)
      //"_DiMuon_Inclusive1nlbjets_SS", // (TTBar Fake))
      // diel
      "_DiElectron_0jets_SS", // SS 0jet CR
      "_DiElectron_1jets_SS", // SS 1jet CR
      "_DiElectron_0jets_OnZ_SS", // SS 0jet+OnZ CR (CF)
      "_DiElectron_1jets_OnZ_SS", // SS 1jet+OnZ CR (CF)
      "_DiElectron_Inclusive1nlbjets_SS", // SS bjet>=1 (Non-prompt)
    };
  }
  //==== Log
  //==== Use DY
  if(XXX==1){
    m.samples_to_use = {"VV_excl", "Xgamma_noDY", "fake_Dijet", "VVV", "top", "DY", "WW_double"};
    m.histname_suffix = {
      // dimu
      //"_DiMuon_OnZ_OS", // OS OnZ CR (DY Prompt)
      //"_DiMuon_0jets_OnZ_OS", // OS 0jet OnZ CR (DY Prompt)
      //"_DiMuon_Inclusive1nlbjets_OS", // (TTBar Prompt)
      //"_DiMuon_Inclusive1nlbjets_METge50_OS", // (TTBar Prompt)
      // diel
      "_DiElectron_OnZ_OS", // OS OnZ CR (DY Prompt)
      "_DiElectron_0jets_OnZ_OS", // OS 0jet OnZ CR (DY Prompt)
      "_DiElectron_1jets_OnZ_OS", // OS 1jet OnZ CR (DY+jet)
      "_DiElectron_Inclusive1nlbjets_OS", // OS bjet>=1 (Prompt+NonPrompt)
    };
  }
  if(XXX==2){
    m.samples_to_use = {"fake_Dijet", "Xgamma_noDY", "chargeflip", "VV_excl", "DY", "VVV", "top", "WW_double"};
    m.histname_suffix = {
      // dimu
      //"_DiMuon_Inclusive1nlbjets_METge50_OffZ_OS", // (TTBar Prompt)
      // diel
      "_DiElectron_Inclusive1nlbjets_METge50_OffZ_OS", // (TTBar Prompt)
    };
  }

  //============================
  //==== set variables to draw
  //============================
  
  m.histname = {
    "m_ll",
    "Njets", "Njets_nolepveto", "Nfwdjets", "Nbjets", "Nbjets_nolepveto", "Nbfwdjets",
    "leadingLepton_Pt", "leadingLepton_Eta",
    "secondLepton_Pt", "secondLepton_Eta",
    "leadingJet_Pt", "leadingJet_Eta", 
    "secondJet_Pt", "secondJet_Eta",
    "leadingForwardJet_Pt", "leadingForwardJet_Eta", 
    "secondForwardJet_Pt", "secondForwardJet_Eta",
    "leadingNoLepVetoJet_Pt", "leadingNoLepVetoJet_Eta", 
    "secondNoLepVetoJet_Pt", "secondNoLepVetoJet_Eta",
    "PFMET", "PFMET_phi", "HT", "ST",
    "Nvtx",
  };

  m.x_title = {
    "m(ll) [GeV]",
    "# of jets", "# of No-LeptonVeto jets", "# of forward jets", "# of b-jets", "# of No-LeptonVeto b-jets", "# of forward b-jets",
    "Leading Lepton p_{T} [GeV]", "Leading Lepton #eta",
    "Sub-Leading Lepton p_{T} [GeV]", "Sub-Leading Lepton #eta",
    "Leading Jet p_{T} [GeV]", "Leading Jet #eta",
    "Sub-Leading Jet p_{T} [GeV]", "Sub-Leading Jet #eta",
    "Leading Forward Jet p_{T} [GeV]", "Leading Forward Jet #eta",
    "Sub-Leading Forward Jet p_{T} [GeV]", "Sub-Leading Forward Jet #eta",
    "Leading No-LeptonVeto Jet p_{T} [GeV]", "Leading No-LeptonVeto Jet #eta",
    "Sub-Leading No-LeptonVeto Jet p_{T} [GeV]", "Sub-Leading No-LeptonVeto Jet #eta",
    "#slash{E}_{T}^{miss} [GeV]", "#phi of #slash{E}_{T}^{miss}", "H_{T} [GeV]", "S_{T} [GeV]",
    "# of vertices",
  };

  m.units = {
    "GeV",
    "int", "int", "int", "int", "int", "int",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "", "GeV", "GeV",
    "int",
  };

  //==== FatJet varialbes
  if(XXX==3){
    m.samples_to_use = {"fake_Dijet", "Xgamma_noDY", "chargeflip", "VV_excl", "DY", "VVV", "top", "WW_double"};
    m.histname_suffix = {
      // dimu
      //"_DiMuon_Inclusive1nlbjets_METge50_OffZ_OS", // (TTBar Prompt)
      // diel
      "_DiElectron_Inclusive1fatjets_OnZ_OS", // (W->(fatjet)Z->(dilep))
    };

    vector<TString> TOADD_histname = {
    //==== FatJet Leading
    "FatJet_Pt", "FatJet_Eta", "FatJet_PrunedMass", "FatJet_SoftDropMass", "FatJet_Tau21", "FatJet_Tau32",
    "m_fatjet", "m_llfatjet", "m_Leadlfatjet", "m_SubLeadlfatjet",
    "DeltaRLeadl_fatjet", "DeltaRSubLeadl_fatjet", "DeltaRLeadl_SubLeadlfatjet", "DeltaRSubLeadl_Leadlfatjet",
    //==== FatJet Closeset to W
    "FatJet_Wclosest_Pt", "FatJet_Wclosest_Eta", "FatJet_Wclosest_PrunedMass", "FatJet_Wclosest_SoftDropMass", "FatJet_Wclosest_Tau21", "FatJet_Wclosest_Tau32",
    "m_fatjet_Wclosest", "m_llfatjet_Wclosest", "m_Leadlfatjet_Wclosest", "m_SubLeadlfatjet_Wclosest",
    "DeltaRLeadl_fatjet_Wclosest", "DeltaRSubLeadl_fatjet_Wclosest", "DeltaRLeadl_SubLeadlfatjet_Wclosest", "DeltaRSubLeadl_Leadlfatjet_Wclosest",
    };
    vector<TString> TOADD_x_title = {
    //==== FatJet Leading
    "Leading Fat Jet p_{T} [GeV]", "Leading Fat Jet #eta", "Leading Fat Jet Pruned Mass [GeV]", "Leading Fat Jet Soft Drop Mass [GeV]", "Leading Fat Jet #tau_{2}/#tau_{1}", "Leading Fat Jet #tau_{3}/#tau_{2}",
    "m(Leading Fat Jet) [GeV]", "m(ll+Fat Jet) [GeV]", "m(Leading Lepton+Fat Jet) [GeV]", "m(Sub-Leading Lepton+Fat Jet) [GeV]",
    "DeltaR(Leading Lepton,Fat Jet)", "DeltaR(Sub-Leading Lepton,Fat Jet)", "DeltaR(Leading Lepton,Sub-Leading Lepton+FatJet)", "DeltaR(Sub-Leading Lepton,Leading Lepton+FatJet)",
    //==== FatJet Closeset to W
    "Leading Fat Jet p_{T} [GeV]", "Leading Fat Jet #eta", "Leading Fat Jet Pruned Mass [GeV]", "Leading Fat Jet Soft Drop Mass [GeV]", "Leading Fat Jet #tau_{2}/#tau_{1}", "Leading Fat Jet #tau_{3}/#tau_{2}",
    "m(Leading Fat Jet) [GeV]", "m(ll+Fat Jet) [GeV]", "m(Leading Lepton+Fat Jet) [GeV]", "m(Sub-Leading Lepton+Fat Jet) [GeV]",
    "DeltaR(Leading Lepton,Fat Jet)", "DeltaR(Sub-Leading Lepton,Fat Jet)", "DeltaR(Leading Lepton,Sub-Leading Lepton+FatJet)", "DeltaR(Sub-Leading Lepton,Leading Lepton+FatJet)",
    };
    vector<TString> TOADD_units = {
    //==== Laeding dijet
    "GeV", "", "GeV", "GeV", "", "",
    "GeV", "GeV", "GeV", "GeV",
    "", "", "", "",
    //==== FatJet Leading
    "GeV", "", "GeV", "GeV", "", "",
    "GeV", "GeV", "GeV", "GeV",
    "", "", "", "",
    };

    m.histname.insert( m.histname.end(), TOADD_histname.begin(), TOADD_histname.end() );
    m.x_title.insert( m.x_title.end(), TOADD_x_title.begin(), TOADD_x_title.end() );
    m.units.insert( m.units.end(), TOADD_units.begin(), TOADD_units.end() );

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

    m.drawdata.push_back(true);

  }

  //==== For Quick Test
  //==== Ignore all, and reset all here
  if(XXX==-1){
    m.samples_to_use = {"fake_Dijet", "chargeflip", "VV_excl", "Xgamma", "VVV", "top", "WW_double"};
    m.histname_suffix = {"_DiElectron_0jets_SS"};
    m.PrimaryDataset = {"DoubleEG"};
    m.drawdata = {true};
    m.UseLogy = {-1};
    m.histname = {"m_ll"};
    m.x_title = {"m(ll) [GeV]"};
    m.units = {"GeV"};
    if(ScaleMC) m.ApplyMCNormSF = {true};
    else m.ApplyMCNormSF = {false};
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
  
  m.k_factor = 1.34;
  
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






