#ifndef PdfSystematics_h
#define PdfSystematics_h

class PdfSystematics{
public :

  PdfSystematics();
  TDirectory *MakeTempDir();

  TH1D *hist_Pdf_Replica;
  TH1D *hist_Pdf_Alpha;
  TH1D *hist_Pdf_Scale;

  double Yield_Central;
  double Syst_Pdf_Replica;
  double Syst_Pdf_Alpha;
  double Syst_Pdf_Scale;
  double Syst_Pdf_Total;


  void CalculatePdfSystematic();

};


PdfSystematics::PdfSystematics(){

  Yield_Central = 0.;

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

  //cout << "Yield_Central = " << Yield_Central << endl;
  Syst_Pdf_Replica = 0.;
  for(unsigned int i=1; i<=hist_Pdf_Replica->GetXaxis()->GetNbins(); i++){
    double diff = hist_Pdf_Replica->GetBinContent(i)-Yield_Central;
    Syst_Pdf_Replica += diff*diff;
  }
  Syst_Pdf_Replica = sqrt(Syst_Pdf_Replica)/(hist_Pdf_Replica->GetXaxis()->GetNbins())/(Yield_Central);
  //cout << "Pdf Replica -> " << Syst_Pdf_Replica << endl;

  Syst_Pdf_Alpha = 0.;
  Syst_Pdf_Alpha = ( (hist_Pdf_Alpha->GetBinContent(1))-(hist_Pdf_Alpha->GetBinContent(2)) )/2./(Yield_Central);

  //cout << "Pdf Alpha -> " << Syst_Pdf_Alpha << endl;

  Syst_Pdf_Scale = -999.;
  for(unsigned int i=1; i<=hist_Pdf_Scale->GetXaxis()->GetNbins(); i++){
    double diff = fabs(hist_Pdf_Scale->GetBinContent(i)-Yield_Central);
    if(diff>Syst_Pdf_Scale){
      Syst_Pdf_Scale = diff;
    }

  }
  Syst_Pdf_Scale = Syst_Pdf_Scale/Yield_Central;
  //cout << "Pdf Scale -> " << Syst_Pdf_Scale << endl;

  Syst_Pdf_Total = sqrt(Syst_Pdf_Replica*Syst_Pdf_Replica+Syst_Pdf_Alpha*Syst_Pdf_Alpha+Syst_Pdf_Scale*Syst_Pdf_Scale);

  //cout << "==> Total = " << Syst_Pdf_Total << endl;


}


#endif
