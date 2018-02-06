#include "RunNtupleBase.C"

void HNElEl_125(){

  bool DoDebug = false;

  TString CutOpCardDir = "CyclesForOptimization_ElEl_Bin1/Cards/";

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("FILE_PATH");

  //==== Declare Object

  RunNtupleBase m;
  m.DoDebug = DoDebug;

  //==== Skim selection for tree (tree name : Ntp_<skim>)

  m.treeskim = "High_TwoJet_NoFatjet_SS";
  m.channel = "DiElectron";

  //==== Dataset/channel

  m.DataPD = "DoubleEG";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/Skimmed_High_TwoJet_NoFatjet/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {
    "HNElEl_125",
  };
  m.MinEffPresel = 0.;
  m.FillSignalInfo();
  m.AddSamplesToList( m.signals );

  //==== Backgrounds

  vector<TString> bkgs = {
    "fake_Dijet",
    "chargeflip",
    "ZGto2LG", "WGtoLNuG_weighted",
    "WZTo3LNu_powheg", "ZZTo4L_powheg",
  };
  m.AddSamplesToList( bkgs );

  if(DoDebug) m.PrintSampleList();

  //==== Fill MCNorm SF

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

  //==== Get Systematics

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  m.SetSourceSystematics();

  //==== Set CutCard

  TString cutfilename = "HNElEl_125.txt";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/RunDirectory/"+CutOpCardDir+"/"+cutfilename);

  m.Run();

}
