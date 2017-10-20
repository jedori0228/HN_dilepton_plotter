import os

dirname = "Cycles"
os.system("mkdir -p "+dirname)

card_dirname = ""

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40, 50, 60, 70, 80]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for mass in masses:

  out = open(dirname+"/HNElEl_"+str(mass)+".C","w")

  TreeSkim = ""
  SkimmedTreeDir = ""
  if mass <= 80:
    TreeSkim = "Low_SS"
    SkimmedTreeDir = "Skimmed_LowMass"
  else:
    TreeSkim = "High_SS"
    SkimmedTreeDir = "Skimmed_HighMass"

  SignalSampleName = "HNElEl_"+str(mass)
  CutCardName = "HNElEl_"+str(mass)+".txt"

  print>>out,"""#include "RunNtupleBase.C"

void {2}(){{

  bool DoDebug = false;

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("FILE_PATH");

  //==== Declare Object

  RunNtupleBase m;
  m.DoDebug = DoDebug;

  //==== Skim selection for tree (tree name : Ntp_<skim>)

  m.treeskim = "{0}";

  //==== Dataset/channel

  m.DataPD = "DoubleEG";
  m.channel = "DiElectron";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/{1}/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {{
    "{2}",
  }};
  m.MinEffPresel = 0.;
  m.FillSignalInfo();
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

  TString cutfilename = "{3}";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/{4}/"+cutfilename);



  m.Run();




}}""".format(TreeSkim, SkimmedTreeDir, SignalSampleName, CutCardName, card_dirname)

  out.close()
