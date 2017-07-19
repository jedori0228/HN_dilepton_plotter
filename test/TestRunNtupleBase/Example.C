//==== Usage :
//==== root -l -b -q Example.C
//====

#include "RunNtupleBase.C"

void Example(){

  bool DoDebug = false;

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("FILE_PATH");

  //==== Declare Object

  RunNtupleBase m;
  m.DoDebug = DoDebug;
  m.LogEvery = 1;

  //==== Skim selection for tree (tree name : Ntp_<skim>)

  m.treeskim = "Preselection_SS";

  //==== Dataset/channel

  m.DataPD = "DoubleEG";
  m.channel = "DiElectron";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {
    "HNElEl_40",
    "HNElEl_50",
    "HNElEl_60",
    "HNElEl_70",
    "HNElEl_80",
    "HNElEl_90",
    "HNElEl_100",
    "HNElEl_125",
    "HNElEl_150",
    "HNElEl_200",
    "HNElEl_250",
    "HNElEl_300",
    "HNElEl_400",
    "HNElEl_500",
    "HNElEl_600",
    "HNElEl_700",
    "HNElEl_800",
    "HNElEl_900",
    "HNElEl_1000",
    "HNElEl_1100",
    "HNElEl_1200",
    "HNElEl_1300",
    "HNElEl_1400",
    "HNElEl_1500",
  };
  m.MinEffPresel = 0.;
  m.FillSignalInfo();
  m.AddSamplesToList( m.signals );

  //==== Backgrounds

  vector<TString> bkgs = {"fake_Dijet", "WZTo3LNu_powheg", "WgstarToLNuEE", "chargeflip", "ZGto2LG", "ZZTo4L_powheg", "ttW", "WWW"};
  m.AddSamplesToList( bkgs );

  if(DoDebug) m.PrintSampleList();

  //==== Fill MCNorm SF

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

  //==== Get Systematics

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  m.SetSourceSystematics();

  //==== Set CutCard

  TString cutfilename = "LowMass_test.txt";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/"+cutfilename);

  //==== Run
  m.Run();




}
