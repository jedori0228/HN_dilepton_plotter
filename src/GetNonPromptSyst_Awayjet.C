void GetNonPromptSyst_Awayjet(){

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/NonPromptSyst_AwayJet/";
  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/NonPromptSyst_AwayJet/";

  TFile *file = new TFile(filepath+"/data_yields.root");

  vector<TString> histnames = {
    "FRsyst_FakeRate_ptcorr_eta20",
    "FRsyst_FakeRate_ptcorr_eta30",
    "FRsyst_FakeRate_ptcorr_eta40",
    "FRsyst_FakeRate_ptcorr_eta60",
  };
  vector<double> yields;

  for(unsigned int i=0; i<histnames.size(); i++){

    TH1D *hist = (TH1D*)file->Get(histnames.at(i));
    yields.push_back( hist->GetBinContent(1) );

  }

  for(unsigned int i=0; i<yields.size(); i++){
    cout << histnames.at(i) << "\t" << yields.at(i) << "\t" << yields.at(i)-yields.at(2) << "\t" << (yields.at(i)-yields.at(2))/yields.at(2) << endl;
  }

}
