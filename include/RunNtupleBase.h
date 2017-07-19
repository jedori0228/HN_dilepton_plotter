#ifndef RunNtupleBase_h
#define RunNtupleBase_h

#include "cutop.C"
#include "cutrangeinfo.h"
#include "AnalysisInputs.h"

class RunNtupleBase{
public:

  bool DoDebug, PrintYield, ShowData;
  Long64_t LogEvery;

  TString treeskim;
  TString preselection; // To Get Relative Efficiency, we need to call Nevents_<preselection>

  TString DataPD, channel;
  TString filepath, plotpath, filename_prefix, filename_suffix;
  vector<TString> samples;
  AnalysisInputs analysisInputs;
  void SetSourceSystematics();
  double uncert_lumi, uncert_cf, uncert_fake;

  //==== Signals
  vector<TString> signals;
  vector<double> MaxPunzis;
  double MinEffPresel;
  vector<double> signal_yield_nocut, signal_yield_preselection;

  //==== Cut
  cutrangeinfo CutRangeInfo;

  //==== functions
  RunNtupleBase();
  double PunziFunction(double eff_sig, double bkg_tot, double bkg_err2);
  void printcurrunttime();
  void mkdir(TString path);

  void FillSignalInfo();
  void AddSamplesToList(vector<TString> bkgs);
  void PrintSampleList();
  void SetCutCard(TString path);
  void Run();

};

RunNtupleBase::RunNtupleBase() : 
DoDebug(false), PrintYield(false), ShowData(false), LogEvery(100),
plotpath("")
{

}


double RunNtupleBase::PunziFunction(double eff_sig, double bkg_tot, double bkg_err2){

  double den = 1 + sqrt( bkg_tot + bkg_err2 );

  return eff_sig/den;

}


void RunNtupleBase::printcurrunttime(){

  TDatime datime;
  cout << datime.GetYear()<<"/"<<datime.GetMonth()<<"/"<<datime.GetDay()<<" "<<datime.GetHour()<<":"<<datime.GetMinute()<<":"<<datime.GetSecond();

}

void RunNtupleBase::mkdir(TString path){

  if(plotpath==""){
    cout << "[RunNtupleBase::mkdir] plotpath is not set" << endl;
    return;
  }

  if( !gSystem->mkdir(path, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << path << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

}

void RunNtupleBase::FillSignalInfo(){

  if(signals.size()==0){

    cout << "[RunNtupleBase::FillSignalInfo] Not using signal" << endl;
    return;

  }

  //==== Get NoCut/Preselection Entry
  for(unsigned int i=0; i<signals.size(); i++){
    TString filename = "DiLeptonAnalyzer_SK"+signals.at(i)+"_cat_v8-0-7.root";
    TFile *file = new TFile(filepath+filename);
    TH1D *hist_nocut = (TH1D*)file->Get("Cutflow_"+channel+"_NoCut");
    TH1D *hist_preselection = (TH1D*)file->Get("Nevents_"+channel+"_"+preselection);

    signal_yield_nocut.push_back( hist_nocut->GetBinContent(1) );
    signal_yield_preselection.push_back( hist_preselection->GetBinContent(1) );

    //==== initialize MaxPunzis
    MaxPunzis.push_back(-1);
  }

}

void RunNtupleBase::AddSamplesToList(vector<TString> v){

  for(unsigned int i=0; i<v.size(); i++){
    samples.push_back( v.at(i) );
  }

}

void RunNtupleBase::PrintSampleList(){

  cout << "################" << endl;
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<samples.size(); i++) cout << " " << samples[i] << endl;
  cout << "################" << endl << endl;

}

void RunNtupleBase::SetSourceSystematics(){

  uncert_lumi = analysisInputs.CalculatedSysts["Luminosity"];
  uncert_cf = analysisInputs.CalculatedSysts["ChrageFlipSyst"];
  uncert_fake = analysisInputs.CalculatedSysts["FakeLooseID"];

}

void RunNtupleBase::SetCutCard(TString path){

  CutRangeInfo.ReadCutCard(path);
  cout
  << endl
  << "##################################################" << endl
  << "#### TOTAL # of Loop = " << CutRangeInfo.TotalIteration << endl
  << "##################################################" << endl
  << endl;
  CutRangeInfo.Print();
  cout << endl;

}












#endif
