import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [20, 30, 40, 50, 60, 70, 75, 80, 85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]

lines_PDFValues = open('PDFSyst.txt').readlines()

counter = 0
for ch in channels:

  PDName = "DoubleMuon"
  Lepch = "DiMuon"
  AddCF = ""
  if ch == "ElEl":
    PDName = "DoubleEG"
    Lepch = "DiElectron"
    AddCF = '"chargeflip",'
  if ch == "MuEl":
    PDName = "MuonEG"
    Lepch = "EMu"

  for Bin in Bins:

    # HNMuEl_1400.txt
    CutCardDirName_Opt = 'Cards_'+ch+"_"+Bin
    CutCardDirName = 'Nminus1/Cards_'+ch+"_"+Bin

    PDFSyst_low = ""
    PDFSyst_high = ""
    for line in lines_PDFValues:
      words = line.split()
      if ch == words[0] and Bin == words[1]:
        PDFSyst_low = words[2]
        PDFSyst_high = words[3]

    for mass in masses:

      filename = "HN"+ch+"_"+str(mass)

      os.system("mkdir -p CyclesForOptimization_"+ch+"_"+Bin)
      out = open("CyclesForOptimization_"+ch+"_"+Bin+"/"+filename+".C","w")

      TreeSkim = ""
      SkimmedTreeDir = ""
      PDFSyst = ""
      if mass <= 80:
        if Bin=="Bin1":
          TreeSkim = "Low_TwoJet_NoFatjet_SS"
          SkimmedTreeDir = "Skimmed_Low_TwoJet_NoFatjet"
        else:
          TreeSkim = "Low_OneJet_NoFatjet_SS"
          SkimmedTreeDir = "Skimmed_Low_OneJet_NoFatjet"
        PDFSyst = PDFSyst_low
      else:
        if Bin=="Bin1":
          TreeSkim = "High_TwoJet_NoFatjet_SS"
          SkimmedTreeDir = "Skimmed_High_TwoJet_NoFatjet"
        else:
          TreeSkim = "High_OneFatJet_SS"
          SkimmedTreeDir = "Skimmed_High_OneFatJet"
        PDFSyst = PDFSyst_high

      SignalSampleName = "HN{5}_"+str(mass)

      print>>out,'''#include "RunNtupleBase.C"

void {4}(int step){{

  bool DoDebug = false;

  TString CutOpCardDir = "{3}";

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
  m.channel = "{7}";

  //==== Dataset/channel

  m.DataPD = "{6}";

  //==== Filename info

  m.filename_prefix = "DiLeptonAnalyzer";
  m.filename_suffix = "cat_"+catversion+".root";

  //==== Input/Output

  m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/{1}/";
  m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

  //==== Signal Info

  m.preselection = "Preselection_SS";
  m.signals = {{
    "HN{5}_{2}",
  }};
  m.MinEffPresel = 0.;
  m.FillSignalInfo();
  m.AddSamplesToList( m.signals );

  //==== Backgrounds

  vector<TString> bkgs = {{
    "fake_Dijet",
    {8}
    "TG", "TTG",
    "ZGto2LG", "WGtoLNuG_weighted",
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
    "WWW", "WWZ", "WZZ", "ZZZ",
    "ttW", "ttZ", "ttH_nonbb",
    "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD",
  }};
  m.AddSamplesToList( bkgs );

  if(DoDebug) m.PrintSampleList();

  //==== Fill MCNorm SF

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

  //==== Get Systematics

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
  m.SetSourceSystematics();

  //==== Set CutCard

  TString cutfilename = "step"+TString::Itoa(step,10)+"_HN{5}_{2}.txt";
  m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/RunDirectory/"+CutOpCardDir+"/"+cutfilename);

  m.Run();

}}'''.format(TreeSkim, SkimmedTreeDir, str(mass), CutCardDirName, filename, ch, PDName, Lepch, AddCF, PDFSyst)
##              0            1             2            3            4       5  6         7      8       9














