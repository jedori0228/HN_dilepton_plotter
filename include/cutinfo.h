#ifndef cutinfo_h
#define cutinfo_h

class cutinfo{
public :

  TString var;
  TString cutdir;
  double cutvalue;

  cutinfo();
  cutinfo(TString a, TString b, double c);
  void Print();

};


cutinfo::cutinfo() : var(""), cutdir(""), cutvalue(-999) { }

cutinfo::cutinfo(TString a, TString b, double c){

  var = a;
  cutdir = b;
  cutvalue = c;

}

void cutinfo::Print(){
  cout << "[cutinfo::PrintCutInfo] "<<var<<"\t"<<cutdir<<"\t"<<cutvalue<<endl;
}


#endif
