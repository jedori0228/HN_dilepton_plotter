#ifndef PdfSystematics_h
#define PdfSystematics_h

class PdfSystematics{
public :

  PdfSystematics();
  TDirectory *MakeTempDir();

  TH1D *hist_Pdf_Replica;
  TH1D *hist_Pdf_Alpha;
  TH1D *hist_Pdf_Scale;

  TString SampleName;
  bool IsTch();

  double Yield_Central;
  double Syst_Pdf_Replica_Eff;
  double Syst_Pdf_Replica_Den;
  double Syst_Pdf_Alpha;
  double Syst_Pdf_Scale;
  double Syst_Pdf_Total;

  bool ForXsecLimitOnly;

  void CalculatePdfSystematic();

};


PdfSystematics::PdfSystematics(){

  Yield_Central = 0.;
  ForXsecLimitOnly = false;

}

TDirectory *PdfSystematics::MakeTempDir(){

  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:                                                                                                                    
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                                                                                                                             
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;

}

void PdfSystematics::CalculatePdfSystematic(){

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/SignalPDF/";

  TFile *file_Den = new TFile(filepath+"DiLeptonAnalyzer_"+SampleName+"_cat_v8-0-7.root");
  TH1D *hist_Replica_Den = (TH1D *)file_Den->Get("ForTree_PdfWeights");
  TH1D *hist_Scale_Den = (TH1D *)file_Den->Get("ForTree_ScaleWeights");
  TH1D *hist_central_Den = (TH1D *)file_Den->Get("ForTree_Central");

  double den_central = hist_central_Den->GetBinContent(1);
  double eff_central = Yield_Central/den_central;

  bool istch = IsTch();

  cout << "Yield_Central = " << Yield_Central << endl;
  cout << "Pseudo Efficiency = " << eff_central << endl;

  //==== PDF Error (eff)

  Syst_Pdf_Replica_Eff = 0.;
  int pdferror_start_bin = 0;
  if(istch) pdferror_start_bin = 1; //==== for t-ch, first bin is same as central

  //==== hist_Pdf_Replica : bin1~bin100 are filled
  //==== hist_Replica_Den : for t-ch, bin2~bin101 should be used
  for(unsigned int i=1; i<=hist_Pdf_Replica->GetXaxis()->GetNbins(); i++){
    double num = hist_Pdf_Replica->GetBinContent(i);
    double den = hist_Replica_Den->GetBinContent(i+pdferror_start_bin);
    double this_eff = num/den;

    double diff = (this_eff-eff_central)/eff_central;
    Syst_Pdf_Replica_Eff += diff*diff;

    //cout << "  this_eff = " << this_eff << " --> diff = " << diff;
    //cout << " --> this_rms = " << sqrt(Syst_Pdf_Replica_Eff/i) << " with i = " << i << endl;
  }
  Syst_Pdf_Replica_Eff = sqrt(Syst_Pdf_Replica_Eff/(hist_Pdf_Replica->GetXaxis()->GetNbins()-1));
  cout << "Pdf Replica Eff -> " << Syst_Pdf_Replica_Eff << endl;

  //==== PDF Error (den)
  Syst_Pdf_Replica_Den = 0.;
  for(unsigned int i=1; i<=hist_Replica_Den->GetXaxis()->GetNbins(); i++){
    double this_den = hist_Replica_Den->GetBinContent(i+pdferror_start_bin);

    double diff = (this_den-den_central)/den_central;
    Syst_Pdf_Replica_Den += diff*diff;
  }
  Syst_Pdf_Replica_Den = sqrt(Syst_Pdf_Replica_Den/(hist_Pdf_Replica->GetXaxis()->GetNbins()-1));
  cout << "Pdf Replica Den -> " << Syst_Pdf_Replica_Den << endl;

  //==== PDF Alpha

  Syst_Pdf_Alpha = 0.;
  if(istch){
    cout << "T-ch" << endl;
    for(unsigned int i=1; i<=hist_Pdf_Alpha->GetXaxis()->GetNbins(); i++){
      double diff = fabs(hist_Pdf_Alpha->GetBinContent(i)-Yield_Central)/Yield_Central;
      cout << diff << endl;
      Syst_Pdf_Alpha += diff*diff;
    }
    Syst_Pdf_Alpha = sqrt(Syst_Pdf_Alpha);
  }
  else{
    cout << "S-ch" << endl;
    Syst_Pdf_Alpha = ( (hist_Pdf_Alpha->GetBinContent(1))-(hist_Pdf_Alpha->GetBinContent(2)) )/2./(Yield_Central);
  }
  cout << "Pdf Alpha -> " << Syst_Pdf_Alpha << endl;

  //==== PDF SCale

  Syst_Pdf_Scale = -999.;
  for(unsigned int i=1; i<=hist_Pdf_Scale->GetXaxis()->GetNbins(); i++){
    double diff = fabs(hist_Pdf_Scale->GetBinContent(i)-Yield_Central);
    if(diff>Syst_Pdf_Scale){
      Syst_Pdf_Scale = diff;
    }

  }
  Syst_Pdf_Scale = Syst_Pdf_Scale/Yield_Central;
  cout << "Pdf Scale -> " << Syst_Pdf_Scale << endl;

  if(ForXsecLimitOnly){
    Syst_Pdf_Total = sqrt(Syst_Pdf_Replica_Eff*Syst_Pdf_Replica_Eff+Syst_Pdf_Alpha*Syst_Pdf_Alpha+Syst_Pdf_Scale*Syst_Pdf_Scale);
  }
  else{
    Syst_Pdf_Total = sqrt(Syst_Pdf_Replica_Eff*Syst_Pdf_Replica_Eff+Syst_Pdf_Replica_Den*Syst_Pdf_Replica_Den+Syst_Pdf_Alpha*Syst_Pdf_Alpha+Syst_Pdf_Scale*Syst_Pdf_Scale);
  }

  cout << "==> Total = " << Syst_Pdf_Total << endl;

  file_Den->Close();
  delete file_Den;

}

bool PdfSystematics::IsTch(){

  if(SampleName.Contains("Tchannel")) return true;
  else return false;

}

#endif
