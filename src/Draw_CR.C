#include "Plotter.cc"
#include <fstream>

void Draw_CR(bool ScaleMC=true){
  
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
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau",
    "WWTo2L2Nu", "ggWWto2L2Nu",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TTJets_aMC"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  m.map_sample_string_to_list["top"] = {"TTJets_aMC", "ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["Wgamma"] = {"WGtoLNuG"};
  m.map_sample_string_to_list["Zgamma"] = {"ZGto2LG"};
  m.map_sample_string_to_list["Vgamma"] = {"WGtoLNuG", "ZGto2LG"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  
  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow+2);
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
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kOrange);
  m.map_sample_string_to_legendinfo["Wgamma"] = make_pair("W#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Zgamma"] = make_pair("Z#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["Vgamma"] = make_pair("V#gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", kGreen);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misd", kAzure+10);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misd", kAzure+10);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Misd", kAzure+10);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misd", kAzure+10);
  m.map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Misd", kAzure+10);
  
  //===============================
  //==== set and make sample list
  //===============================

  //==== trilep CR
  //==== _Di<Lepton>_<JetSel>_<ifOffZ>_<charge>
	m.histname_suffix = {
    // dimu
    "_DiMuon_SS",
    "_DiMuon_Inclusive1bjets_SS", "_DiMuon_Inclusive1bjets_OS",
    "_DiMuon_Inclusive1bjets_OffZ_SS", "_DiMuon_Inclusive1bjets_OffZ_OS",
    "_DiMuon_OffZ_AllCharge", "_DiMuon_OffZ_SS", "_DiMuon_OffZ_OS",
    "_DiMuon_0jets_OS",
    // diel
    "_DiElectron_SS", "_DiElectron_OS",
    "_DiElectron_Inclusive1bjets_SS", "_DiElectron_Inclusive1bjets_OS",
    "_DiElectron_OffZ_AllCharge", "_DiElectron_OffZ_SS", "_DiElectron_OffZ_OS",
    "_DiElectron_0jets_OS",
	};
  m.PrimaryDataset = {
    // dimu
    "DoubleMuon",
    "DoubleMuon", "DoubleMuon",
    "DoubleMuon", "DoubleMuon",
    "DoubleMuon", "DoubleMuon", "DoubleMuon",
    "DoubleMuon",
    // diel
    "DoubleEG", "DoubleEG",
    "DoubleEG", "DoubleEG",
    "DoubleEG", "DoubleEG", "DoubleEG",
    "DoubleEG",
  };
	m.drawdata = {
    // dimu
    true,
    true, true,
    true, true,
    true, true, true,
    true,
    // diel
    true, true,
    true, true,
    true, true, true,
    true,
	};
  m.UseLogy = {
    // dimu
    -1,
    -1, 100,
    -1, 100,
    -1, -1, -1,
    100,
    // diel
    -1, 100,
    -1, 100,
    -1, -1, -1,
    100,
  };

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    if(ScaleMC) m.ApplyMCNormSF.push_back(true);
    else m.ApplyMCNormSF.push_back(false);
  }

	m.samples_to_use = {"fake_sfed_HighdXY", "VV_excl", "Vgamma", "VVV", "ttV_lep", "ttbar_ll", "DY", "WW_double"};
  
  //============================
  //==== set variables to draw
  //============================
  
  m.histname = {
    "m_ll",
    "Njets", "Nfwdjets", "Nbjets", "Nbfwdjets",
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
    "# of jets", "# of forward jets", "# of b-jets", "# of forward b-jets",
    "Leading Lepton p_{T} [GeV]", "Leading Lepton #eta",
    "Second Lepton p_{T} [GeV]", "Second Lepton #eta",
    "Leading Jet p_{T} [GeV]", "Leading Jet #eta",
    "Second Jet p_{T} [GeV]", "Second Jet #eta",
    "Leading Forward Jet p_{T} [GeV]", "Leading Forward Jet #eta",
    "Second Forward Jet p_{T} [GeV]", "Second Forward Jet #eta",
    "Leading No Lepton Veto Jet p_{T} [GeV]", "Leading No Lepton Veto Jet #eta",
    "Second No Lepton Veto Jet p_{T} [GeV]", "Second No Lepton Veto Jet #eta",
    "#slash{E}_{T}^{miss} [GeV]", "#phi of #slash{E}_{T}^{miss}", "H_{T} [GeV]", "S_{T} [GeV]",
    "# of vertices",
  };

  m.units = {
    "GeV",
    "int", "int", "int", "int",
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

  //====================
  //==== make bkg list
  //====================

  m.make_bkglist();

  //=====================
  //==== Fill MCNorm SF
  //=====================

  for(unsigned int i=0; i<m.bkglist.size(); i++){
    m.MCNormSF[m.bkglist.at(i)] = 1.;
    m.MCNormSF_uncert[m.bkglist.at(i)] = 0.;
  }
  m.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt");

  //======================
  //==== Get Systematics
  //======================

  m.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");

  /*
  //=============================
  //==== set signal mass points
  //=============================
  
  m.signal_mass = {40, 60, 150, 700};
  m.signal_color = {kRed, kBlue, kMagenta-7, kBlack};
  
  //====================================
  //==== set signal coupling constants
  //====================================
  
  m.coupling_constants[make_pair("_WZ", 40)] = 0.01;
  m.coupling_constants[make_pair("_WZ", 60)] = 0.01;
  m.coupling_constants[make_pair("_WZ", 150)] = 1;
  m.coupling_constants[make_pair("_WZ", 700)] = 0.01;
  m.coupling_constants[make_pair("_ZJets", 40)] = 0.001;
  m.coupling_constants[make_pair("_ZJets", 60)] = 0.001;
  m.coupling_constants[make_pair("_ZJets", 150)] = 0.001;
  m.coupling_constants[make_pair("_ZJets", 700)] = 0.001;
  
  //=====================================
  //==== set signal mass for each class
  //=====================================
  
  m.map_class_to_signal_mass[Plotter::class1] = {40};
  m.map_class_to_signal_mass[Plotter::class2] = {60};
  m.map_class_to_signal_mass[Plotter::lowmass] = {40, 60};
  m.map_class_to_signal_mass[Plotter::class3] = {150};
  m.map_class_to_signal_mass[Plotter::class4] = {700};
  m.map_class_to_signal_mass[Plotter::highmass] = {150, 700};
  */

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
  
  //===============================
  //==== declare output rootfiles
  //===============================
  
  m.outputfile = new TFile(m.plotpath+"/hists.root", "RECREATE");
  
  //==========================
  //==== finally, draw plots
  //==========================
  
  m.draw_hist();
  
}






