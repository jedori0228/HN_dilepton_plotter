//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 14 17:25:37 2017 by ROOT version 6.08/00
// from TTree Ntp_DiElectron/Ntp_DiElectron
// found on file: DiLeptonAnalyzer_data_DoubleEG_cat_v8-0-7.root
//////////////////////////////////////////////////////////

#ifndef DileptonNtuple_h
#define DileptonNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "CutInfo.h"

// Header file for the classes stored in the TTree if any.

class DileptonNtuple {
public :
  TTree       *fChain;  //!pointer to the analyzed TTree or TChain
  Int_t        fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Double_t      leadingLepton_Pt;
  Double_t      secondLepton_Pt;
  Double_t      DeltaRl1l2;
  Double_t      m_ll;
  Double_t      isSS;
  Double_t      isOffZ;
  Double_t      Njets;
  Double_t      Nbjets;
  Double_t      Njets_nolepveto;
  Double_t      Nbjets_nolepveto;
  Double_t      Nfwdjets;
  Double_t      Nbfwdjets;
  Double_t      leadingJet_Pt;
  Double_t      secondJet_Pt;
  Double_t      DeltaRjjptorder;
  Double_t      m_jjptorder;
  Double_t      m_Leadljjptorder;
  Double_t      m_SubLeadljjptorder;
  Double_t      m_lljjptorder;
  Double_t      leadingJet_jjWclosest_pt;
  Double_t      secondJet_jjWclosest_pt;
  Double_t      m_jj_jjWclosest;
  Double_t      m_Leadljj_jjWclosest;
  Double_t      m_SubLeadljj_jjWclosest;
  Double_t      m_lljj_jjWclosest;
  Double_t      DeltaRjjWclosest;
  Double_t      DeltaRLeadl_jjWclosest;
  Double_t      DeltaRSubLeadl_jjWclosest;
  Double_t      DeltaRLeadl_SubLeadljjWclosest;
  Double_t      DeltaRSubLeadl_LeadljjWclosest;
  Double_t      leadingJet_lljjWclosest_pt;
  Double_t      secondJet_lljjWclosest_pt;
  Double_t      m_jj_lljjWclosest;
  Double_t      m_Leadljj_lljjWclosest;
  Double_t      m_SubLeadljj_lljjWclosest;
  Double_t      m_lljj_lljjWclosest;
  Double_t      DeltaRlljjWclosest;
  Double_t      DeltaRLeadl_lljjWclosest;
  Double_t      DeltaRSubLeadl_lljjWclosest;
  Double_t      DeltaRLeadl_SubLeadllljjWclosest;
  Double_t      DeltaRSubLeadl_LeadllljjWclosest;
  Double_t      fwd_dRjj;
  Double_t      PFMET;
  Double_t      ST;
  Double_t      HT;
  Double_t      LT;
  Double_t      weight;
  Double_t      weight_err;
  Double_t      Nfatjets;
  Double_t      FatJet_Pt;
  Double_t      m_fatjet;
  Double_t      FatJet_PrunedMass;
  Double_t      FatJet_SoftDropMass;
  Double_t      FatJet_Tau21;
  Double_t      FatJet_Tau32;
  Double_t      m_Leadlfatjet;
  Double_t      m_SubLeadlfatjet;
  Double_t      m_llfatjet;
  Double_t      DeltaRLeadl_fatjet;
  Double_t      DeltaRSubLeadl_fatjet;
  Double_t      DeltaRLeadl_SubLeadlfatjet;
  Double_t      DeltaRSubLeadl_Leadlfatjet;
  Double_t      FatJet_Wclosest_Pt;
  Double_t      m_fatjet_Wclosest;
  Double_t      FatJet_Wclosest_PrunedMass;
  Double_t      FatJet_Wclosest_SoftDropMass;
  Double_t      FatJet_Wclosest_Tau21;
  Double_t      FatJet_Wclosest_Tau32;
  Double_t      m_Leadlfatjet_Wclosest;
  Double_t      m_SubLeadlfatjet_Wclosest;
  Double_t      m_llfatjet_Wclosest;
  Double_t      DeltaRLeadl_fatjet_Wclosest;
  Double_t      DeltaRSubLeadl_fatjet_Wclosest;
  Double_t      DeltaRLeadl_SubLeadlfatjet_Wclosest;
  Double_t      DeltaRSubLeadl_Leadlfatjet_Wclosest;
  inline Double_t MET2ST() { return PFMET*PFMET/ST; }

  //==== Function to call above varialbes
  double GetVar(TString var);

  // List of branches
  TBranch      *b_leadingLepton_Pt;  //!
  TBranch      *b_secondLepton_Pt;  //!
  TBranch      *b_DeltaRl1l2;  //!
  TBranch      *b_m_ll;  //!
  TBranch      *b_isSS;  //!
  TBranch      *b_isOffZ;  //!
  TBranch      *b_Njets;  //!
  TBranch      *b_Nbjets;  //!
  TBranch      *b_Njets_nolepveto;  //!
  TBranch      *b_Nbjets_nolepveto;  //!
  TBranch      *b_Nfwdjets;  //!
  TBranch      *b_Nbfwdjets;  //!
  TBranch      *b_leadingJet_Pt;  //!
  TBranch      *b_secondJet_Pt;  //!
  TBranch      *b_DeltaRjjptorder;  //!
  TBranch      *b_m_jjptorder;  //!
  TBranch      *b_m_Leadljjptorder;  //!
  TBranch      *b_m_SubLeadljjptorder;  //!
  TBranch      *b_m_lljjptorder;  //!
  TBranch      *b_leadingJet_jjWclosest_pt;  //!
  TBranch      *b_secondJet_jjWclosest_pt;  //!
  TBranch      *b_m_jj_jjWclosest;  //!
  TBranch      *b_m_Leadljj_jjWclosest;  //!
  TBranch      *b_m_SubLeadljj_jjWclosest;  //!
  TBranch      *b_m_lljj_jjWclosest;  //!
  TBranch      *b_DeltaRjjWclosest;  //!
  TBranch      *b_DeltaRLeadl_jjWclosest;  //!
  TBranch      *b_DeltaRSubLeadl_jjWclosest;  //!
  TBranch      *b_DeltaRLeadl_SubLeadljjWclosest;  //!
  TBranch      *b_DeltaRSubLeadl_LeadljjWclosest;  //!
  TBranch      *b_leadingJet_lljjWclosest_pt;  //!
  TBranch      *b_secondJet_lljjWclosest_pt;  //!
  TBranch      *b_m_jj_lljjWclosest;  //!
  TBranch      *b_m_Leadljj_lljjWclosest;  //!
  TBranch      *b_m_SubLeadljj_lljjWclosest;  //!
  TBranch      *b_m_lljj_lljjWclosest;  //!
  TBranch      *b_DeltaRlljjWclosest;  //!
  TBranch      *b_DeltaRLeadl_lljjWclosest;  //!
  TBranch      *b_DeltaRSubLeadl_lljjWclosest;  //!
  TBranch      *b_DeltaRLeadl_SubLeadllljjWclosest;  //!
  TBranch      *b_DeltaRSubLeadl_LeadllljjWclosest;  //!
  TBranch      *b_fwd_dRjj;  //!
  TBranch      *b_PFMET;  //!
  TBranch      *b_ST;  //!
  TBranch      *b_HT;  //!
  TBranch      *b_LT;  //!
  TBranch      *b_weight;  //!
  TBranch      *b_weight_err;  //!
  TBranch      *b_Nfatjets;  //!
  TBranch      *b_FatJet_Pt;  //!
  TBranch      *b_m_fatjet;  //!
  TBranch      *b_FatJet_PrunedMass;  //!
  TBranch      *b_FatJet_SoftDropMass;  //!
  TBranch      *b_FatJet_Tau21;  //!
  TBranch      *b_FatJet_Tau32;  //!
  TBranch      *b_m_Leadlfatjet;  //!
  TBranch      *b_m_SubLeadlfatjet;  //!
  TBranch      *b_m_llfatjet;  //!
  TBranch      *b_DeltaRLeadl_fatjet;  //!
  TBranch      *b_DeltaRSubLeadl_fatjet;  //!
  TBranch      *b_DeltaRLeadl_SubLeadlfatjet;  //!
  TBranch      *b_DeltaRSubLeadl_Leadlfatjet;  //!
  TBranch      *b_FatJet_Wclosest_Pt;  //!
  TBranch      *b_m_fatjet_Wclosest;  //!
  TBranch      *b_FatJet_Wclosest_PrunedMass;  //!
  TBranch      *b_FatJet_Wclosest_SoftDropMass;  //!
  TBranch      *b_FatJet_Wclosest_Tau21;  //!
  TBranch      *b_FatJet_Wclosest_Tau32;  //!
  TBranch      *b_m_Leadlfatjet_Wclosest;  //!
  TBranch      *b_m_SubLeadlfatjet_Wclosest;  //!
  TBranch      *b_m_llfatjet_Wclosest;  //!
  TBranch      *b_DeltaRLeadl_fatjet_Wclosest;  //!
  TBranch      *b_DeltaRSubLeadl_fatjet_Wclosest;  //!
  TBranch      *b_DeltaRLeadl_SubLeadlfatjet_Wclosest;  //!
  TBranch      *b_DeltaRSubLeadl_Leadlfatjet_Wclosest;  //!

  DileptonNtuple(TString filename, TString treename);
  virtual ~DileptonNtuple();
  virtual Int_t   GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void    Init(TTree *tree);
  virtual void    Loop();
  
  vector<TString> CutVariables;
  vector<TString> CutDirections;
  vector<double> CutValues;
  void SetCutVariablesToUse(TString var, TString cutdir, double cutvalue);
  TH1D *hist_for_error, *hist_for_error_up;

  vector<CutInfo> cutinfos;
  void SetCutVariablesToUse(CutInfo ci);

  bool Pass();

  bool DoDebug;
  bool PrintBool(bool b);

  //==== Variables To Save
  double unweighted_yield, weighted_yield;

};

#endif

#ifdef DileptonNtuple_cxx
DileptonNtuple::DileptonNtuple(TString filename, TString treename) :
fChain(0),
DoDebug(false),
unweighted_yield(0.), weighted_yield(0.)
{

  TH1::SetDefaultSumw2(true);

  TTree *tree;
  TFile *f = new TFile(filename);
  tree = (TTree*)f->Get(treename);

  Init(tree);

  CutVariables.clear();
  CutDirections.clear();
  CutValues.clear();

}

DileptonNtuple::~DileptonNtuple()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t DileptonNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t DileptonNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

void DileptonNtuple::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

   fChain->SetBranchAddress("leadingLepton_Pt", &leadingLepton_Pt, &b_leadingLepton_Pt);
   fChain->SetBranchAddress("secondLepton_Pt", &secondLepton_Pt, &b_secondLepton_Pt);
   fChain->SetBranchAddress("DeltaRl1l2", &DeltaRl1l2, &b_DeltaRl1l2);
   fChain->SetBranchAddress("m_ll", &m_ll, &b_m_ll);
   fChain->SetBranchAddress("isSS", &isSS, &b_isSS);
   fChain->SetBranchAddress("isOffZ", &isOffZ, &b_isOffZ);
   fChain->SetBranchAddress("Njets", &Njets, &b_Njets);
   fChain->SetBranchAddress("Nbjets", &Nbjets, &b_Nbjets);
   fChain->SetBranchAddress("Njets_nolepveto", &Njets_nolepveto, &b_Njets_nolepveto);
   fChain->SetBranchAddress("Nbjets_nolepveto", &Nbjets_nolepveto, &b_Nbjets_nolepveto);
   fChain->SetBranchAddress("Nfwdjets", &Nfwdjets, &b_Nfwdjets);
   fChain->SetBranchAddress("Nbfwdjets", &Nbfwdjets, &b_Nbfwdjets);
   fChain->SetBranchAddress("leadingJet_Pt", &leadingJet_Pt, &b_leadingJet_Pt);
   fChain->SetBranchAddress("secondJet_Pt", &secondJet_Pt, &b_secondJet_Pt);
   fChain->SetBranchAddress("DeltaRjjptorder", &DeltaRjjptorder, &b_DeltaRjjptorder);
   fChain->SetBranchAddress("m_jjptorder", &m_jjptorder, &b_m_jjptorder);
   fChain->SetBranchAddress("m_Leadljjptorder", &m_Leadljjptorder, &b_m_Leadljjptorder);
   fChain->SetBranchAddress("m_SubLeadljjptorder", &m_SubLeadljjptorder, &b_m_SubLeadljjptorder);
   fChain->SetBranchAddress("m_lljjptorder", &m_lljjptorder, &b_m_lljjptorder);
   fChain->SetBranchAddress("leadingJet_jjWclosest_pt", &leadingJet_jjWclosest_pt, &b_leadingJet_jjWclosest_pt);
   fChain->SetBranchAddress("secondJet_jjWclosest_pt", &secondJet_jjWclosest_pt, &b_secondJet_jjWclosest_pt);
   fChain->SetBranchAddress("m_jj_jjWclosest", &m_jj_jjWclosest, &b_m_jj_jjWclosest);
   fChain->SetBranchAddress("m_Leadljj_jjWclosest", &m_Leadljj_jjWclosest, &b_m_Leadljj_jjWclosest);
   fChain->SetBranchAddress("m_SubLeadljj_jjWclosest", &m_SubLeadljj_jjWclosest, &b_m_SubLeadljj_jjWclosest);
   fChain->SetBranchAddress("m_lljj_jjWclosest", &m_lljj_jjWclosest, &b_m_lljj_jjWclosest);
   fChain->SetBranchAddress("DeltaRjjWclosest", &DeltaRjjWclosest, &b_DeltaRjjWclosest);
   fChain->SetBranchAddress("DeltaRLeadl_jjWclosest", &DeltaRLeadl_jjWclosest, &b_DeltaRLeadl_jjWclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_jjWclosest", &DeltaRSubLeadl_jjWclosest, &b_DeltaRSubLeadl_jjWclosest);
   fChain->SetBranchAddress("DeltaRLeadl_SubLeadljjWclosest", &DeltaRLeadl_SubLeadljjWclosest, &b_DeltaRLeadl_SubLeadljjWclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_LeadljjWclosest", &DeltaRSubLeadl_LeadljjWclosest, &b_DeltaRSubLeadl_LeadljjWclosest);
   fChain->SetBranchAddress("leadingJet_lljjWclosest_pt", &leadingJet_lljjWclosest_pt, &b_leadingJet_lljjWclosest_pt);
   fChain->SetBranchAddress("secondJet_lljjWclosest_pt", &secondJet_lljjWclosest_pt, &b_secondJet_lljjWclosest_pt);
   fChain->SetBranchAddress("m_jj_lljjWclosest", &m_jj_lljjWclosest, &b_m_jj_lljjWclosest);
   fChain->SetBranchAddress("m_Leadljj_lljjWclosest", &m_Leadljj_lljjWclosest, &b_m_Leadljj_lljjWclosest);
   fChain->SetBranchAddress("m_SubLeadljj_lljjWclosest", &m_SubLeadljj_lljjWclosest, &b_m_SubLeadljj_lljjWclosest);
   fChain->SetBranchAddress("m_lljj_lljjWclosest", &m_lljj_lljjWclosest, &b_m_lljj_lljjWclosest);
   fChain->SetBranchAddress("DeltaRlljjWclosest", &DeltaRlljjWclosest, &b_DeltaRlljjWclosest);
   fChain->SetBranchAddress("DeltaRLeadl_lljjWclosest", &DeltaRLeadl_lljjWclosest, &b_DeltaRLeadl_lljjWclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_lljjWclosest", &DeltaRSubLeadl_lljjWclosest, &b_DeltaRSubLeadl_lljjWclosest);
   fChain->SetBranchAddress("DeltaRLeadl_SubLeadllljjWclosest", &DeltaRLeadl_SubLeadllljjWclosest, &b_DeltaRLeadl_SubLeadllljjWclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_LeadllljjWclosest", &DeltaRSubLeadl_LeadllljjWclosest, &b_DeltaRSubLeadl_LeadllljjWclosest);
   fChain->SetBranchAddress("fwd_dRjj", &fwd_dRjj, &b_fwd_dRjj);
   fChain->SetBranchAddress("PFMET", &PFMET, &b_PFMET);
   fChain->SetBranchAddress("ST", &ST, &b_ST);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("LT", &LT, &b_LT);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weight_err", &weight_err, &b_weight_err);
   fChain->SetBranchAddress("Nfatjets", &Nfatjets, &b_Nfatjets);
   fChain->SetBranchAddress("FatJet_Pt", &FatJet_Pt, &b_FatJet_Pt);
   fChain->SetBranchAddress("m_fatjet", &m_fatjet, &b_m_fatjet);
   fChain->SetBranchAddress("FatJet_PrunedMass", &FatJet_PrunedMass, &b_FatJet_PrunedMass);
   fChain->SetBranchAddress("FatJet_SoftDropMass", &FatJet_SoftDropMass, &b_FatJet_SoftDropMass);
   fChain->SetBranchAddress("FatJet_Tau21", &FatJet_Tau21, &b_FatJet_Tau21);
   fChain->SetBranchAddress("FatJet_Tau32", &FatJet_Tau32, &b_FatJet_Tau32);
   fChain->SetBranchAddress("m_Leadlfatjet", &m_Leadlfatjet, &b_m_Leadlfatjet);
   fChain->SetBranchAddress("m_SubLeadlfatjet", &m_SubLeadlfatjet, &b_m_SubLeadlfatjet);
   fChain->SetBranchAddress("m_llfatjet", &m_llfatjet, &b_m_llfatjet);
   fChain->SetBranchAddress("DeltaRLeadl_fatjet", &DeltaRLeadl_fatjet, &b_DeltaRLeadl_fatjet);
   fChain->SetBranchAddress("DeltaRSubLeadl_fatjet", &DeltaRSubLeadl_fatjet, &b_DeltaRSubLeadl_fatjet);
   fChain->SetBranchAddress("DeltaRLeadl_SubLeadlfatjet", &DeltaRLeadl_SubLeadlfatjet, &b_DeltaRLeadl_SubLeadlfatjet);
   fChain->SetBranchAddress("DeltaRSubLeadl_Leadlfatjet", &DeltaRSubLeadl_Leadlfatjet, &b_DeltaRSubLeadl_Leadlfatjet);
   fChain->SetBranchAddress("FatJet_Wclosest_Pt", &FatJet_Wclosest_Pt, &b_FatJet_Wclosest_Pt);
   fChain->SetBranchAddress("m_fatjet_Wclosest", &m_fatjet_Wclosest, &b_m_fatjet_Wclosest);
   fChain->SetBranchAddress("FatJet_Wclosest_PrunedMass", &FatJet_Wclosest_PrunedMass, &b_FatJet_Wclosest_PrunedMass);
   fChain->SetBranchAddress("FatJet_Wclosest_SoftDropMass", &FatJet_Wclosest_SoftDropMass, &b_FatJet_Wclosest_SoftDropMass);
   fChain->SetBranchAddress("FatJet_Wclosest_Tau21", &FatJet_Wclosest_Tau21, &b_FatJet_Wclosest_Tau21);
   fChain->SetBranchAddress("FatJet_Wclosest_Tau32", &FatJet_Wclosest_Tau32, &b_FatJet_Wclosest_Tau32);
   fChain->SetBranchAddress("m_Leadlfatjet_Wclosest", &m_Leadlfatjet_Wclosest, &b_m_Leadlfatjet_Wclosest);
   fChain->SetBranchAddress("m_SubLeadlfatjet_Wclosest", &m_SubLeadlfatjet_Wclosest, &b_m_SubLeadlfatjet_Wclosest);
   fChain->SetBranchAddress("m_llfatjet_Wclosest", &m_llfatjet_Wclosest, &b_m_llfatjet_Wclosest);
   fChain->SetBranchAddress("DeltaRLeadl_fatjet_Wclosest", &DeltaRLeadl_fatjet_Wclosest, &b_DeltaRLeadl_fatjet_Wclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_fatjet_Wclosest", &DeltaRSubLeadl_fatjet_Wclosest, &b_DeltaRSubLeadl_fatjet_Wclosest);
   fChain->SetBranchAddress("DeltaRLeadl_SubLeadlfatjet_Wclosest", &DeltaRLeadl_SubLeadlfatjet_Wclosest, &b_DeltaRLeadl_SubLeadlfatjet_Wclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_Leadlfatjet_Wclosest", &DeltaRSubLeadl_Leadlfatjet_Wclosest, &b_DeltaRSubLeadl_Leadlfatjet_Wclosest);

}

double DileptonNtuple::GetVar(TString var){

  if(var=="leadingLepton_Pt") return leadingLepton_Pt;
  else if(var=="secondLepton_Pt") return secondLepton_Pt;
  else if(var=="DeltaRl1l2") return DeltaRl1l2;
  else if(var=="m_ll") return m_ll;
  else if(var=="isSS") return isSS;
  else if(var=="isOffZ") return isOffZ;
  else if(var=="Njets") return Njets;
  else if(var=="Nbjets") return Nbjets;
  else if(var=="Njets_nolepveto") return Njets_nolepveto;
  else if(var=="Nbjets_nolepveto") return Nbjets_nolepveto;
  else if(var=="Nfwdjets") return Nfwdjets;
  else if(var=="Nbfwdjets") return Nbfwdjets;
  else if(var=="leadingJet_Pt") return leadingJet_Pt;
  else if(var=="secondJet_Pt") return secondJet_Pt;
  else if(var=="DeltaRjjptorder") return DeltaRjjptorder;
  else if(var=="m_jjptorder") return m_jjptorder;
  else if(var=="m_Leadljjptorder") return m_Leadljjptorder;
  else if(var=="m_SubLeadljjptorder") return m_SubLeadljjptorder;
  else if(var=="m_lljjptorder") return m_lljjptorder;
  else if(var=="leadingJet_jjWclosest_pt") return leadingJet_jjWclosest_pt;
  else if(var=="secondJet_jjWclosest_pt") return secondJet_jjWclosest_pt;
  else if(var=="m_jj_jjWclosest") return m_jj_jjWclosest;
  else if(var=="m_Leadljj_jjWclosest") return m_Leadljj_jjWclosest;
  else if(var=="m_SubLeadljj_jjWclosest") return m_SubLeadljj_jjWclosest;
  else if(var=="m_lljj_jjWclosest") return m_lljj_jjWclosest;
  else if(var=="DeltaRjjWclosest") return DeltaRjjWclosest;
  else if(var=="DeltaRLeadl_jjWclosest") return DeltaRLeadl_jjWclosest;
  else if(var=="DeltaRSubLeadl_jjWclosest") return DeltaRSubLeadl_jjWclosest;
  else if(var=="DeltaRLeadl_SubLeadljjWclosest") return DeltaRLeadl_SubLeadljjWclosest;
  else if(var=="DeltaRSubLeadl_LeadljjWclosest") return DeltaRSubLeadl_LeadljjWclosest;
  else if(var=="leadingJet_lljjWclosest_pt") return leadingJet_lljjWclosest_pt;
  else if(var=="secondJet_lljjWclosest_pt") return secondJet_lljjWclosest_pt;
  else if(var=="m_jj_lljjWclosest") return m_jj_lljjWclosest;
  else if(var=="m_Leadljj_lljjWclosest") return m_Leadljj_lljjWclosest;
  else if(var=="m_SubLeadljj_lljjWclosest") return m_SubLeadljj_lljjWclosest;
  else if(var=="m_lljj_lljjWclosest") return m_lljj_lljjWclosest;
  else if(var=="DeltaRlljjWclosest") return DeltaRlljjWclosest;
  else if(var=="DeltaRLeadl_lljjWclosest") return DeltaRLeadl_lljjWclosest;
  else if(var=="DeltaRSubLeadl_lljjWclosest") return DeltaRSubLeadl_lljjWclosest;
  else if(var=="DeltaRLeadl_SubLeadllljjWclosest") return DeltaRLeadl_SubLeadllljjWclosest;
  else if(var=="DeltaRSubLeadl_LeadllljjWclosest") return DeltaRSubLeadl_LeadllljjWclosest;
  else if(var=="fwd_dRjj") return fwd_dRjj;
  else if(var=="PFMET") return PFMET;
  else if(var=="ST") return ST;
  else if(var=="HT") return HT;
  else if(var=="LT") return LT;
  else if(var=="weight") return weight;
  else if(var=="weight_err") return weight_err;
  else if(var=="Nfatjets") return Nfatjets;
  else if(var=="FatJet_Pt") return FatJet_Pt;
  else if(var=="m_fatjet") return m_fatjet;
  else if(var=="FatJet_PrunedMass") return FatJet_PrunedMass;
  else if(var=="FatJet_SoftDropMass") return FatJet_SoftDropMass;
  else if(var=="FatJet_Tau21") return FatJet_Tau21;
  else if(var=="FatJet_Tau32") return FatJet_Tau32;
  else if(var=="m_Leadlfatjet") return m_Leadlfatjet;
  else if(var=="m_SubLeadlfatjet") return m_SubLeadlfatjet;
  else if(var=="m_llfatjet") return m_llfatjet;
  else if(var=="DeltaRLeadl_fatjet") return DeltaRLeadl_fatjet;
  else if(var=="DeltaRSubLeadl_fatjet") return DeltaRSubLeadl_fatjet;
  else if(var=="DeltaRLeadl_SubLeadlfatjet") return DeltaRLeadl_SubLeadlfatjet;
  else if(var=="DeltaRSubLeadl_Leadlfatjet") return DeltaRSubLeadl_Leadlfatjet;
  else if(var=="FatJet_Wclosest_Pt") return FatJet_Wclosest_Pt;
  else if(var=="m_fatjet_Wclosest") return m_fatjet_Wclosest;
  else if(var=="FatJet_Wclosest_PrunedMass") return FatJet_Wclosest_PrunedMass;
  else if(var=="FatJet_Wclosest_SoftDropMass") return FatJet_Wclosest_SoftDropMass;
  else if(var=="FatJet_Wclosest_Tau21") return FatJet_Wclosest_Tau21;
  else if(var=="FatJet_Wclosest_Tau32") return FatJet_Wclosest_Tau32;
  else if(var=="m_Leadlfatjet_Wclosest") return m_Leadlfatjet_Wclosest;
  else if(var=="m_SubLeadlfatjet_Wclosest") return m_SubLeadlfatjet_Wclosest;
  else if(var=="m_llfatjet_Wclosest") return m_llfatjet_Wclosest;
  else if(var=="DeltaRLeadl_fatjet_Wclosest") return DeltaRLeadl_fatjet_Wclosest;
  else if(var=="DeltaRSubLeadl_fatjet_Wclosest") return DeltaRSubLeadl_fatjet_Wclosest;
  else if(var=="DeltaRLeadl_SubLeadlfatjet_Wclosest") return DeltaRLeadl_SubLeadlfatjet_Wclosest;
  else if(var=="DeltaRSubLeadl_Leadlfatjet_Wclosest") return DeltaRSubLeadl_Leadlfatjet_Wclosest;

  //==== function
  else if(var=="MET2ST") return MET2ST();
  else{
    cout << "[DileptonNtuple::GetVar] "<<var<<": Wrong Variable Name" << endl;
    return -999;
  }

}

void DileptonNtuple::SetCutVariablesToUse(TString var, TString cutdir, double cutvalue){

  if(DoDebug){
    cout << "[DileptonNtuple::SetCutVariablesToUse] "<<var<<" "<<cutdir<<" "<<cutvalue << endl;
  }
  CutVariables.push_back( var );
  CutDirections.push_back( cutdir );
  CutValues.push_back( cutvalue );

}

void DileptonNtuple::SetCutVariablesToUse(CutInfo ci){

  if(DoDebug){
    cout << "[DileptonNtuple::SetCutVariablesToUse] "<<ci.var<<" "<<ci.cutdir<<" "<<ci.cutvalue << endl;
  }
  cutinfos.push_back( ci );

}

bool DileptonNtuple::Pass(){

  bool outpass = true;

/*
  for(unsigned int i=0; i<CutVariables.size(); i++){

    TString var = CutVariables.at(i);
    TString cutdir = CutDirections.at(i);
    double cutvalue = CutValues.at(i);
*/

  for(unsigned int i=0; i<cutinfos.size(); i++){

    TString var    = cutinfos.at(i).var;
    TString cutdir = cutinfos.at(i).cutdir;
    double cutvalue = cutinfos.at(i).cutvalue;

    double value = GetVar(var);

    if(DoDebug){
      cout << "[DileptonNtuple::Pass] "<<var<<" "<<value<<" "<<cutdir<<" "<<cutvalue << endl;
    }

		if(cutdir==">"){
			if( !(value>cutvalue) ) return PrintBool(false);
		}
    else if(cutdir==">="){
      if( !(value>=cutvalue) ) return PrintBool(false);
    }
		else if(cutdir=="<"){
			if( !(value<cutvalue) ) return PrintBool(false);
		}
    else if(cutdir=="<="){
      if( !(value<=cutvalue) ) return PrintBool(false);
    }
    else if(cutdir=="=="){
      if( !(value==cutvalue) ) return PrintBool(false);
    }
    else if(cutdir=="!="){
      if( !(value!=cutvalue) ) return PrintBool(false);
    }
		else{
			cout << "[DileptonNtuple::Cut] cutdir should be >/>=/</<=/==/!=" << endl;
			return PrintBool(false);
		}

  }

  return PrintBool(outpass);

}

bool DileptonNtuple::PrintBool(bool b){

  if(DoDebug){
    if(b) cout << "[DileptonNtuple::PrintBool] returning True" << endl;
    else cout << "[DileptonNtuple::PrintBool] returning False" << endl;
  }
  return b;

}



#endif // #ifdef DileptonNtuple_cxx








