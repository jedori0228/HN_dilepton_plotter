#ifndef cutrangeinfo_h
#define cutrangeinfo_h

#include "cutinfo.h"

class cutrangeinfo{
public :

  map< TString, vector<cutinfo> > map_varANDdir_to_cutinfo;
  map< TString, int >             map_varANDdir_to_iterator;
  bool k_end, DoDebug;

  cutrangeinfo(TString filepath);
  void MakeCutInfo(TString var, TString cutdir, double start, double end, double nx);
  void Print();
  void PrintCurrent();
  void FillCurrentCutInfoVector(vector<cutinfo>& vec);
  vector<cutinfo> GetCurrentCutInfo();
  void Next();

  inline bool isEnd() { return k_end; };
  Long64_t CurrentIteration;
  Long64_t TotalIteration;


};

cutrangeinfo::cutrangeinfo(TString filepath) : 
k_end(false), DoDebug(false)
{

  map_varANDdir_to_cutinfo.clear();

  string elline;
  ifstream in(filepath);
  while(getline(in,elline)){
    std::istringstream is( elline );

    TString var;
    TString cutdir;
    double start;
    double end;
    double nx;

    is >> var;
    is >> cutdir;
    is >> start;
    is >> end;
    is >> nx;

    if(var.Contains("#")){
      continue;
    }

    MakeCutInfo(var, cutdir, start, end, nx);

  }

  CurrentIteration = 1;
  TotalIteration = 1;
  for(map< TString, vector<cutinfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){
    TotalIteration *= (it->second).size();
  }

}

void cutrangeinfo::MakeCutInfo(TString var, TString cutdir, double start, double end, double nx){

  map_varANDdir_to_cutinfo[var+"_"+cutdir].clear();
  map_varANDdir_to_iterator[var+"_"+cutdir] = 0;

  if(nx==0) nx = 1;
  double dx = (end-start)/nx;

  for(int i=0; i<=nx; i++){

    double this_cutvalue = start+i*dx;

    cutinfo tmp_cutinfo(var, cutdir, this_cutvalue);
    map_varANDdir_to_cutinfo[var+"_"+cutdir].push_back( tmp_cutinfo );

    if(start==end) break;

  }


}

void cutrangeinfo::FillCurrentCutInfoVector(vector<cutinfo>& vec){

  vec.clear();

  for(map< TString, vector<cutinfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    vec.push_back( (it->second).at( map_varANDdir_to_iterator[it->first] ) );

  }

}

void cutrangeinfo::Next(){

  CurrentIteration++;

  if(DoDebug) cout << "[cutrangeinfo::Next] called" << endl; 

  map< TString, vector<cutinfo> >::iterator it = map_varANDdir_to_cutinfo.begin();

  if(it == map_varANDdir_to_cutinfo.end()){
    k_end = true;
    return;
  }

  bool DONE = false;  

  while( !DONE ){

    TString this_varANDdir = it->first;
    vector<cutinfo> this_cutinfo = it->second;
    int this_iterator = map_varANDdir_to_iterator[this_varANDdir];

    if(DoDebug){
      cout << "[cutrangeinfo::Next] "<<this_varANDdir<<"\t"<<this_iterator<<"\t"<<this_cutinfo.size()<<endl;
    }

    //==== Last iterator of this cut
    if( this_iterator == this_cutinfo.size()-1 ){
      if(DoDebug) cout << "[cutrangeinfo::Next] This cutinfo is finished its loop. Going back to fisrt value" << endl;
      map_varANDdir_to_iterator[this_varANDdir] = 0;
      it++;

      //==== If this was the last cut, this is the end of all loop
      if(it==map_varANDdir_to_cutinfo.end()){
        k_end = true;
        if(DoDebug) cout << "[cutrangeinfo::Next] Loop ENDED" << endl;
        break;
      }

    }
    //==== If not, just increase iterator by 1
    else{
      if(DoDebug) cout << "[cutrangeinfo::Next] Okay, increasing this varialbe. DONE=true" << endl;
      map_varANDdir_to_iterator[this_varANDdir]++;
      DONE = true;
    }

  }

}

void cutrangeinfo::Print(){

  for(map< TString, vector<cutinfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    cout << "[cutrangeinfo::PrintCutRangeInfo] "<<it->first<<endl;
    for(unsigned int i=0; i<(it->second).size(); i++){
      it->second.at(i).Print();
    }


  }

}

vector<cutinfo> cutrangeinfo::GetCurrentCutInfo(){

  vector<cutinfo> out;

  for(map< TString, vector<cutinfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    out.push_back( it->second.at( map_varANDdir_to_iterator[it->first] ) );

  }

  return out;

}

void cutrangeinfo::PrintCurrent(){

  for(map< TString, vector<cutinfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    it->second.at( map_varANDdir_to_iterator[it->first] ).Print();

  }

}


#endif
