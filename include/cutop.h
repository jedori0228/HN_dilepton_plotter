//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 14 17:25:37 2017 by ROOT version 6.08/00
// from TTree Ntp_DiElectron/Ntp_DiElectron
// found on file: DiLeptonAnalyzer_data_DoubleEG_cat_v8-0-7.root
//////////////////////////////////////////////////////////

#ifndef cutop_h
#define cutop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "cutinfo.h"

// Header file for the classes stored in the TTree if any.

class cutop {
public :
  TTree       *fChain;  //!pointer to the analyzed TTree or TChain
  Int_t        fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Double_t      l_1_pt;
  Double_t      l_2_pt;
  Double_t      DeltaRl1l2;
  Double_t      m_ll;
  Double_t      isSS;
  Double_t      isOffZ;
  Double_t      njets;
  Double_t      nbjets;
  Double_t      njets_nolepveto;
  Double_t      nbjets_nolepveto;
  Double_t      njets_fwd;
  Double_t      nbjets_fwd;
  Double_t      j_1_pt;
  Double_t      j_2_pt;
  Double_t      DeltaRjjptorder;
  Double_t      m_jjptorder;
  Double_t      m_Leadljjptorder;
  Double_t      m_SubLeadljjptorder;
  Double_t      m_lljjptorder;
  Double_t      j_1_jjWclosest_pt;
  Double_t      j_2_jjWclosest_pt;
  Double_t      m_jj_jjWclosest;
  Double_t      m_Leadljj_jjWclosest;
  Double_t      m_SubLeadljj_jjWclosest;
  Double_t      m_lljj_jjWclosest;
  Double_t      DeltaRjjWclosest;
  Double_t      DeltaRLeadl_jjWclosest;
  Double_t      DeltaRSubLeadl_jjWclosest;
  Double_t      DeltaRLeadl_SubLeadljjWclosest;
  Double_t      DeltaRSubLeadl_LeadljjWclosest;
  Double_t      j_1_lljjWclosest_pt;
  Double_t      j_2_lljjWclosest_pt;
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
  inline Double_t MET2ST() { return PFMET*PFMET/ST; }

  //==== Function to call above varialbes
  double GetVar(TString var);

  // List of branches
  TBranch      *b_l_1_pt;  //!
  TBranch      *b_l_2_pt;  //!
  TBranch      *b_DeltaRl1l2;  //!
  TBranch      *b_m_ll;  //!
  TBranch      *b_isSS;  //!
  TBranch      *b_isOffZ;  //!
  TBranch      *b_njets;  //!
  TBranch      *b_nbjets;  //!
  TBranch      *b_njets_nolepveto;  //!
  TBranch      *b_nbjets_nolepveto;  //!
  TBranch      *b_njets_fwd;  //!
  TBranch      *b_nbjets_fwd;  //!
  TBranch      *b_j_1_pt;  //!
  TBranch      *b_j_2_pt;  //!
  TBranch      *b_DeltaRjjptorder;  //!
  TBranch      *b_m_jjptorder;  //!
  TBranch      *b_m_Leadljjptorder;  //!
  TBranch      *b_m_SubLeadljjptorder;  //!
  TBranch      *b_m_lljjptorder;  //!
  TBranch      *b_j_1_jjWclosest_pt;  //!
  TBranch      *b_j_2_jjWclosest_pt;  //!
  TBranch      *b_m_jj_jjWclosest;  //!
  TBranch      *b_m_Leadljj_jjWclosest;  //!
  TBranch      *b_m_SubLeadljj_jjWclosest;  //!
  TBranch      *b_m_lljj_jjWclosest;  //!
  TBranch      *b_DeltaRjjWclosest;  //!
  TBranch      *b_DeltaRLeadl_jjWclosest;  //!
  TBranch      *b_DeltaRSubLeadl_jjWclosest;  //!
  TBranch      *b_DeltaRLeadl_SubLeadljjWclosest;  //!
  TBranch      *b_DeltaRSubLeadl_LeadljjWclosest;  //!
  TBranch      *b_j_1_lljjWclosest_pt;  //!
  TBranch      *b_j_2_lljjWclosest_pt;  //!
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

  cutop(TString filename, TString treename);
  virtual ~cutop();
  virtual Int_t   GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void    Init(TTree *tree);
  virtual void    Loop();
  
  vector<TString> CutVariables;
  vector<TString> CutDirections;
  vector<double> CutValues;
  void SetCutVariablesToUse(TString var, TString cutdir, double cutvalue);
  TH1D *hist_for_error, *hist_for_error_up;

  vector<cutinfo> CutInfos;
  void SetCutVariablesToUse(cutinfo ci);

  bool Pass();

  bool DoDebug;
  bool PrintBool(bool b);

  //==== Variables To Save
  double unweighted_yield, weighted_yield;

};

#endif

#ifdef cutop_cxx
cutop::cutop(TString filename, TString treename) :
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

cutop::~cutop()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t cutop::GetEntry(Long64_t entry)
{
// Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t cutop::LoadTree(Long64_t entry)
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

void cutop::Init(TTree *tree)
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

   fChain->SetBranchAddress("l_1_pt", &l_1_pt, &b_l_1_pt);
   fChain->SetBranchAddress("l_2_pt", &l_2_pt, &b_l_2_pt);
   fChain->SetBranchAddress("DeltaRl1l2", &DeltaRl1l2, &b_DeltaRl1l2);
   fChain->SetBranchAddress("m_ll", &m_ll, &b_m_ll);
   fChain->SetBranchAddress("isSS", &isSS, &b_isSS);
   fChain->SetBranchAddress("isOffZ", &isOffZ, &b_isOffZ);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("nbjets", &nbjets, &b_nbjets);
   fChain->SetBranchAddress("njets_nolepveto", &njets_nolepveto, &b_njets_nolepveto);
   fChain->SetBranchAddress("nbjets_nolepveto", &nbjets_nolepveto, &b_nbjets_nolepveto);
   fChain->SetBranchAddress("njets_fwd", &njets_fwd, &b_njets_fwd);
   fChain->SetBranchAddress("nbjets_fwd", &nbjets_fwd, &b_nbjets_fwd);
   fChain->SetBranchAddress("j_1_pt", &j_1_pt, &b_j_1_pt);
   fChain->SetBranchAddress("j_2_pt", &j_2_pt, &b_j_2_pt);
   fChain->SetBranchAddress("DeltaRjjptorder", &DeltaRjjptorder, &b_DeltaRjjptorder);
   fChain->SetBranchAddress("m_jjptorder", &m_jjptorder, &b_m_jjptorder);
   fChain->SetBranchAddress("m_Leadljjptorder", &m_Leadljjptorder, &b_m_Leadljjptorder);
   fChain->SetBranchAddress("m_SubLeadljjptorder", &m_SubLeadljjptorder, &b_m_SubLeadljjptorder);
   fChain->SetBranchAddress("m_lljjptorder", &m_lljjptorder, &b_m_lljjptorder);
   fChain->SetBranchAddress("j_1_jjWclosest_pt", &j_1_jjWclosest_pt, &b_j_1_jjWclosest_pt);
   fChain->SetBranchAddress("j_2_jjWclosest_pt", &j_2_jjWclosest_pt, &b_j_2_jjWclosest_pt);
   fChain->SetBranchAddress("m_jj_jjWclosest", &m_jj_jjWclosest, &b_m_jj_jjWclosest);
   fChain->SetBranchAddress("m_Leadljj_jjWclosest", &m_Leadljj_jjWclosest, &b_m_Leadljj_jjWclosest);
   fChain->SetBranchAddress("m_SubLeadljj_jjWclosest", &m_SubLeadljj_jjWclosest, &b_m_SubLeadljj_jjWclosest);
   fChain->SetBranchAddress("m_lljj_jjWclosest", &m_lljj_jjWclosest, &b_m_lljj_jjWclosest);
   fChain->SetBranchAddress("DeltaRjjWclosest", &DeltaRjjWclosest, &b_DeltaRjjWclosest);
   fChain->SetBranchAddress("DeltaRLeadl_jjWclosest", &DeltaRLeadl_jjWclosest, &b_DeltaRLeadl_jjWclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_jjWclosest", &DeltaRSubLeadl_jjWclosest, &b_DeltaRSubLeadl_jjWclosest);
   fChain->SetBranchAddress("DeltaRLeadl_SubLeadljjWclosest", &DeltaRLeadl_SubLeadljjWclosest, &b_DeltaRLeadl_SubLeadljjWclosest);
   fChain->SetBranchAddress("DeltaRSubLeadl_LeadljjWclosest", &DeltaRSubLeadl_LeadljjWclosest, &b_DeltaRSubLeadl_LeadljjWclosest);
   fChain->SetBranchAddress("j_1_lljjWclosest_pt", &j_1_lljjWclosest_pt, &b_j_1_lljjWclosest_pt);
   fChain->SetBranchAddress("j_2_lljjWclosest_pt", &j_2_lljjWclosest_pt, &b_j_2_lljjWclosest_pt);
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

}

double cutop::GetVar(TString var){

  if(var=="l_1_pt") return l_1_pt;
  else if(var=="l_2_pt") return l_2_pt;
  else if(var=="DeltaRl1l2") return DeltaRl1l2;
  else if(var=="m_ll") return m_ll;
  else if(var=="isSS") return isSS;
  else if(var=="isOffZ") return isOffZ;
  else if(var=="njets") return njets;
  else if(var=="nbjets") return nbjets;
  else if(var=="njets_nolepveto") return njets_nolepveto;
  else if(var=="nbjets_nolepveto") return nbjets_nolepveto;
  else if(var=="njets_fwd") return njets_fwd;
  else if(var=="nbjets_fwd") return nbjets_fwd;
  else if(var=="j_1_pt") return j_1_pt;
  else if(var=="j_2_pt") return j_2_pt;
  else if(var=="DeltaRjjptorder") return DeltaRjjptorder;
  else if(var=="m_jjptorder") return m_jjptorder;
  else if(var=="m_Leadljjptorder") return m_Leadljjptorder;
  else if(var=="m_SubLeadljjptorder") return m_SubLeadljjptorder;
  else if(var=="m_lljjptorder") return m_lljjptorder;
  else if(var=="j_1_jjWclosest_pt") return j_1_jjWclosest_pt;
  else if(var=="j_2_jjWclosest_pt") return j_2_jjWclosest_pt;
  else if(var=="m_jj_jjWclosest") return m_jj_jjWclosest;
  else if(var=="m_Leadljj_jjWclosest") return m_Leadljj_jjWclosest;
  else if(var=="m_SubLeadljj_jjWclosest") return m_SubLeadljj_jjWclosest;
  else if(var=="m_lljj_jjWclosest") return m_lljj_jjWclosest;
  else if(var=="DeltaRjjWclosest") return DeltaRjjWclosest;
  else if(var=="DeltaRLeadl_jjWclosest") return DeltaRLeadl_jjWclosest;
  else if(var=="DeltaRSubLeadl_jjWclosest") return DeltaRSubLeadl_jjWclosest;
  else if(var=="DeltaRLeadl_SubLeadljjWclosest") return DeltaRLeadl_SubLeadljjWclosest;
  else if(var=="DeltaRSubLeadl_LeadljjWclosest") return DeltaRSubLeadl_LeadljjWclosest;
  else if(var=="j_1_lljjWclosest_pt") return j_1_lljjWclosest_pt;
  else if(var=="j_2_lljjWclosest_pt") return j_2_lljjWclosest_pt;
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

  //==== function
  else if(var=="MET2ST") return MET2ST();
  else{
    cout << "[cutop::GetVar] "<<var<<": Wrong Variable Name" << endl;
    return -999;
  }

}

void cutop::SetCutVariablesToUse(TString var, TString cutdir, double cutvalue){

  if(DoDebug){
    cout << "[cutop::SetCutVariablesToUse] "<<var<<" "<<cutdir<<" "<<cutvalue << endl;
  }
  CutVariables.push_back( var );
  CutDirections.push_back( cutdir );
  CutValues.push_back( cutvalue );

}

void cutop::SetCutVariablesToUse(cutinfo ci){

  if(DoDebug){
    cout << "[cutop::SetCutVariablesToUse] "<<ci.var<<" "<<ci.cutdir<<" "<<ci.cutvalue << endl;
  }
  CutInfos.push_back( ci );

}

bool cutop::Pass(){

  bool outpass = true;

/*
  for(unsigned int i=0; i<CutVariables.size(); i++){

    TString var = CutVariables.at(i);
    TString cutdir = CutDirections.at(i);
    double cutvalue = CutValues.at(i);
*/

  for(unsigned int i=0; i<CutInfos.size(); i++){

    TString var    = CutInfos.at(i).var;
    TString cutdir = CutInfos.at(i).cutdir;
    double cutvalue = CutInfos.at(i).cutvalue;

    double value = GetVar(var);

    if(DoDebug){
      cout << "[cutop::Pass] "<<var<<" "<<value<<" "<<cutdir<<" "<<cutvalue << endl;
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
			cout << "[cutop::Cut] cutdir should be >/>=/</<=/==/!=" << endl;
			return PrintBool(false);
		}

  }

  return PrintBool(outpass);

}

bool cutop::PrintBool(bool b){

  if(DoDebug){
    if(b) cout << "[cutop::PrintBool] returning True" << endl;
    else cout << "[cutop::PrintBool] returning False" << endl;
  }
  return b;

}



#endif // #ifdef cutop_cxx








