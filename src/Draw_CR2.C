#include "Plotter.cc"
#include <fstream>

void Draw_CR2(bool ScaleMC=true, int XXX=0){

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
  
  m.data_class = dataset+"/Regions2/";
  
  //================================
  //==== set prefixes and suffixes
  //================================
  
  m.filename_prefix = "DiLeptonAnalyzer_CR";
  m.filename_suffix = "_cat_"+catversion+".root";
  
  //=========================
  //==== set sample mapping
  //=========================
  
  m.map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets"};
  m.map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_powheg",
    "WZto2L2Q_amcatnlo",
    "ZZTo4L_powheg", "ZZTo2L2Nu_Powheg", "ZZTo2L2Q_Powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
    "WWTo2L2Nu", "ggWWto2L2Nu",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  //m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_mllmin01"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TT_powheg"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  m.map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["Zgamma"] = {"ZGto2LG"};
  m.map_sample_string_to_list["Wgamma"] = {"WGtoLNuG"};
  m.map_sample_string_to_list["tgamma"] = {"TG", "TTG"};
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
  m.map_sample_string_to_legendinfo["Zgamma"] = make_pair("Z + #gamma", kViolet);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W + #gamma", kOrange);
  m.map_sample_string_to_legendinfo["tgamma"] = make_pair("top + #gamma", kSpring-7);
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
    m.samples_to_use = {"WZ_excl", "Wgamma", "ZZ_excl", "Zgamma", "fake_Dijet", "tgamma", "VVV", "top"};

    m.histname_suffix = {


      "_DiMuon_ThreeLepton_WZ",
      "_DiMuon_ThreeLepton_WZ_NotAllSameFlavour",
      "_DiMuon_ThreeLepton_ZGamma",
      "_DiMuon_ThreeLepton_WGamma",
      "_DiMuon_FourLepton_ZZ",
      "_DiMuon_FourLepton_ZZ_NotAllSameFlavour",
      "_DiMuon_FourLepton_ZZ_AllSameFlavour",

      "_DiElectron_ThreeLepton_WZ",
      "_DiElectron_ThreeLepton_WZ_NotAllSameFlavour",
      "_DiElectron_ThreeLepton_ZGamma",
      "_DiElectron_ThreeLepton_WGamma",
      "_DiElectron_FourLepton_ZZ",
      "_DiElectron_FourLepton_ZZ_NotAllSameFlavour",
      "_DiElectron_FourLepton_ZZ_AllSameFlavour",

      "_DiLepton_ThreeLepton_WZ",
      "_DiLepton_ThreeLepton_ZGamma",
      "_DiLepton_ThreeLepton_WGamma",
      "_DiLepton_FourLepton_ZZ",


      //"_DiLepton_ThreeLepton_WZ",
      //"_DiLepton_ThreeLepton_WGamma",

    };
  }
  //==== Log
  //==== Use DY
  if(XXX==1){
    //m.samples_to_use = {"VV_excl", "Xgamma_noDY", "fake_Dijet", "VVV", "top", "DY", "WW_double"};
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
      "_DiMuon_0jets_OnZ_OS",
      //"_DiElectron_0jets_OnZ_OS",
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
    "m_ll", "m_lll", "m_OSSF_smallest",
    "Njets", "Njets_nolepveto", "Nfwdjets", "Nbjets", "Nbjets_nolepveto", "Nbfwdjets",
    "leadingLepton_Pt", "leadingLepton_Eta", "leadingLepton_Type",
    "secondLepton_Pt", "secondLepton_Eta", "secondLepton_Type",
    "thirdLepton_Pt", "thirdLepton_Eta", "thirdLepton_Type",
    "fourthLepton_Pt", "fourthLepton_Eta", "fourthLepton_Type",
    "leadingJet_Pt", "leadingJet_Eta", 
    "secondJet_Pt", "secondJet_Eta",
    "leadingForwardJet_Pt", "leadingForwardJet_Eta", 
    "secondForwardJet_Pt", "secondForwardJet_Eta",
    "leadingNoLepVetoJet_Pt", "leadingNoLepVetoJet_Eta", 
    "secondNoLepVetoJet_Pt", "secondNoLepVetoJet_Eta",
    "PFMET", "PFMET_phi", "HT", "ST",
    "MET2overST",
    "Nvtx", "DeltaRl1l2", "Nevents", "MT", "MZcand",
    "Z_leadingLepton_Pt", "Z_secondLepton_Pt", "ExtraLepton_Pt",
  };

  m.x_title = {
    "m(ll) (GeV)", "m(lll) (GeV)", "m(ll)_{min} (GeV)",
    "# of jets", "# of No-LeptonVeto jets", "# of forward jets", "# of b-jets", "# of No-LeptonVeto b-jets", "# of forward b-jets",
    "Leading Lepton p_{T} (GeV)", "Leading Lepton #eta", "Leading Lepton Type",
    "Subleading Lepton p_{T} (GeV)", "Subleading Lepton #eta", "Subleading Lepton Type",
    "Trailing Lepton p_{T} (GeV)", "Trailing Lepton #eta", "Trailing Lepton Type",
    "Fourth Lepton p_{T} (GeV)", "Fourth Lepton #eta", "Fourth Lepton Type",
    "Leading Jet p_{T} (GeV)", "Leading Jet #eta",
    "Subleading Jet p_{T} (GeV)", "Subleading Jet #eta",
    "Leading Forward Jet p_{T} (GeV)", "Leading Forward Jet #eta",
    "Subleading Forward Jet p_{T} (GeV)", "Subleading Forward Jet #eta",
    "Leading No-LeptonVeto Jet p_{T} (GeV)", "Leading No-LeptonVeto Jet #eta",
    "Subleading No-LeptonVeto Jet p_{T} (GeV)", "Subleading No-LeptonVeto Jet #eta",
    "#slash{E}_{T}^{miss} (GeV)", "#phi of #slash{E}_{T}^{miss}", "H_{T} (GeV)", "S_{T} (GeV)",
    "#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)",
    "# of vertices", "#DeltaR(l_{1},l_{2})", "onebin", "M_{T}(W-tagged Lepton, #slash{E}_{T}^{miss}) (GeV)", "m(Z-candidate) (GeV)",
    "Leading Z-tagged Lepton p_{T} (GeV)", "Subleading Z-tagged Lepton p_{T} (GeV)", "W-tagged Lepton p_{T} (GeV)"
  };

  m.units = {
    "GeV", "GeV", "GeV",
    "int", "int", "int", "int", "int", "int",
    "GeV", "", "int",
    "GeV", "", "int",
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
    "int", "", "int", "GeV", "GeV",
    "GeV", "GeV", "GeV",
  };

  if(!( m.histname.size()==m.x_title.size() && m.x_title.size() == m.units.size()) ){
    cout << "m.histname.size() = " << m.histname.size() << endl;
    cout << "m.x_title.size() = " << m.x_title.size() << endl;
    cout << "m.units.size() = " << m.units.size() << endl;
    return;
  }

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    //==== PD
    if(m.histname_suffix.at(i).Contains("DiMuon")){
      m.PrimaryDataset.push_back("DoubleMuon");
    }
    else if(m.histname_suffix.at(i).Contains("DiElectron")){
      m.PrimaryDataset.push_back("DoubleEG");
    }
    else if(m.histname_suffix.at(i).Contains("EMu")){
      m.PrimaryDataset.push_back("MuonEG");
    }
    else if(m.histname_suffix.at(i).Contains("DiLepton")){
      m.PrimaryDataset.push_back("DiLepton");
    }

    if(m.histname_suffix.at(i).Contains("FourLepton")){
      m.LeptonChannels.push_back(40);
    }
    else if(m.histname_suffix.at(i).Contains("ThreeLepton")){
      m.LeptonChannels.push_back(30);
    }
    else{
      cout << "ERROR : Lepton channel wrong" << endl;
      return;
    }

    if(m.histname_suffix.at(i).Contains("WZ")){
      m.RegionType.push_back(-101);
    }
    else if(m.histname_suffix.at(i).Contains("ZGamma")){
      m.RegionType.push_back(-102);
    }
    else if(m.histname_suffix.at(i).Contains("WGamma")){
      m.RegionType.push_back(-103);
    }
    else if(m.histname_suffix.at(i).Contains("ZZ")){
      m.RegionType.push_back(-104);
    }
    else{
      cout << "ERROR : Region type wrong" << endl;
      return;
    }


    //==== Log plot boolean
    if(XXX==0) m.UseLogy.push_back(-1);
    else if(XXX==1) m.UseLogy.push_back(-1);
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
    m.LeptonChannels = {0};
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
  m.histname = {"Nevents"};
  m.x_title = {"#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)"};
  m.units = {"GeV"};
*/
/*
  //==== FIXME test
  m.histname = {"m_ll", "m_lll",};
  m.x_title = {"m(ll) (GeV)", "m(lll) (GeV)",};
  m.units = {"GeV", "GeV",};
*/
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
  ofstream skeleton_rebins("./data/CR2_rebins.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_rebins
      //<< "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_rebins.close();


  m.SetRebins(WORKING_DIR+"/data/"+dataset+"/CR2_rebins.txt");

  //=============
  //==== y_maxs
  //=============
  

  //==== script to generate rebins
  ofstream skeleton_y_maxs("./data/CR2_yaxis.txt", ios::trunc);
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

  m.SetYAxis(WORKING_DIR+"/data/"+dataset+"/CR2_yaxis.txt"); 

  //=============
  //==== x_mins
  //=============


  //==== script to generate rebins
  ofstream skeleton_x_mins("./data/CR2_xaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
  for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_x_mins
      //<< "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<"\t"<<-999<<endl;
    }
  }
  skeleton_x_mins.close();



  m.SetXAxis(WORKING_DIR+"/data/"+dataset+"/CR2_xaxis.txt");

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






