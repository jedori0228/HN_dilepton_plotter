#include "RunNtupleBase.C"

void HNMuMu_500(){

  bool DoDebug = false;

  TString CutOpCardDir = "CyclesForOptimization_MuMu_Bin2/Cards/";

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("FILE_PATH");

  //==== Declare Object

  RunNtupleBase m;
  m.DoDebug = DoDebug;

  //==== Skim selection for tree (tree name : Ntp_<skim>)

  m.treeskim = "High_OneFatJet_SS";
  m.channel = "DiMuon";

  //==== Dataset/channel

  m.DataPD = "DoubleMuon";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/Skimmed_High_OneFatJet/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {
    "HNMuMu_500",
  };
  m.MinEffPresel = 0.;
  m.FillSignalInfo();
  m.AddSamplesToList( m.signals );

  //==== Backgrounds

  vector<TString> bkgs = {
    "fake_Dijet",
    
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

  TString cutfilename = "HNMuMu_500.txt";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/RunDirectory/"+CutOpCardDir+"/"+cutfilename);

  m.Run();

}
