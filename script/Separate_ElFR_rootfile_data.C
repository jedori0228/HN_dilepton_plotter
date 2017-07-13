void Separate_ElFR_rootfile_data(TString inputdir, TString outdir, int ForWhichTrigger){

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString filepath = WORKING_DIR+"/rootfiles/"+dataset+"/FRCalculator_El_dxysig_DILEP/"+inputdir+"/";
  TString outpath = WORKING_DIR+"/rootfiles/"+dataset+"/FRCalculator_El_dxysig_DILEP/"+outdir+"/";


  TFile *file_all_DoubleEG = new TFile(filepath+"FRCalculator_El_dxysig_DILEP_data_DoubleEG_cat_"+catversion+".root");
  TFile *file_all_SingleElectron = new TFile(filepath+"FRCalculator_El_dxysig_DILEP_data_SingleElectron_cat_"+catversion+".root");

  TList *list_all = file_all_DoubleEG->GetListOfKeys();

/*
  HLT_ptrange["HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v"].push_back(10.);
  HLT_ptrange["HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v"].push_back(15.);
  HLT_ptrange["HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v"].push_back(15.);
  HLT_ptrange["HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v"].push_back(20.);
  HLT_ptrange["HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v"].push_back(20.);
  HLT_ptrange["HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v"].push_back(25.);
  HLT_ptrange["HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v"].push_back(25.);
  HLT_ptrange["HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v"].push_back(9999.);
*/

  vector<TString> HLTsToUse, WhichData, HLTsNotUse;

  //==== For HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
  if(ForWhichTrigger==0){
    HLTsToUse = {"HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30_v", "HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v", "HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v", "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v"};
    WhichData = {"DoubleEG", "DoubleEG", "DoubleEG", "DoubleEG"};
    HLTsNotUse = {};
  }
  //==== For HLT_Ele27_WPTight_Gsf_v
  else if(ForWhichTrigger==1){
  }

  map<TString, TH1D*> map_TH1D;
  map<TString, TH2D*> map_TH2D;

  for(int i=0; i<list_all->Capacity(); i++){
    TObject *this_obj = list_all->At(i);
    TString this_name = this_obj->GetName();

    bool SkipThis = false;
    for(unsigned int j=0;j<HLTsNotUse.size(); j++){
      if(this_name.Contains(HLTsNotUse.at(j))){
        SkipThis = true;
        break;
      }
    }
    if(SkipThis) continue;

    //cout << "this_name = " << this_name << endl;

    bool Used = false;

    for(unsigned int j=0;j<HLTsToUse.size(); j++){

      TString tmp_this_name = this_name;

      TFile *file_all = file_all_DoubleEG;
      if(WhichData.at(j)=="SingleElectron") file_all = file_all_SingleElectron;

      if(!tmp_this_name.Contains(HLTsToUse.at(j))) continue;

      TString MergedName = tmp_this_name.Remove(0, HLTsToUse.at(j).Length()+1);
      //cout << "  MergedName = " << MergedName << endl;
      Used = true;

      //==== TH2D
      if(this_name.Contains("events")){

        TH2D *this_hist = (TH2D*)file_all->Get(this_name);
        this_hist->SetName( MergedName );
        this_hist->SetTitle("");

        std::map<TString, TH2D*>::iterator mapit = map_TH2D.find(MergedName);
        //==== If not found, clone this one
        if(mapit == map_TH2D.end()){
          map_TH2D[MergedName] = (TH2D*)this_hist->Clone();
        }
        else{
          map_TH2D[MergedName]->Add( this_hist );
        }

      }
      //==== TH1D
      else{

        TH1D *this_hist = (TH1D*)file_all->Get(this_name);
        this_hist->SetName( MergedName );
        this_hist->SetTitle("");

        std::map<TString, TH1D*>::iterator mapit = map_TH1D.find(MergedName);
        //==== If not found, clone this one
        if(mapit == map_TH1D.end()){
          map_TH1D[MergedName] = (TH1D*)this_hist->Clone();
        }
        else{
          map_TH1D[MergedName]->Add( this_hist );
        }

      }

    } // HLT loop

    if(!Used){

      TFile *file_all = file_all_DoubleEG;

      //cout << "  Genearl Histogram" << endl;

      //==== TH2D
      if(this_name.Contains("events")){
        TH2D *this_hist = (TH2D*)file_all->Get(this_name);
        map_TH2D[this_name] = (TH2D*)this_hist->Clone();
      }
      //==== TH1D
      else{
        TH1D *this_hist = (TH1D*)file_all->Get(this_name);
        map_TH1D[this_name] = (TH1D*)this_hist->Clone();
      }

      continue;

    }

  }


  TString filename = "FRCalculator_El_dxysig_DILEP_data_DoubleEG_cat_"+catversion+".root";
  TFile *file_out = new TFile(outpath+filename, "RECREATE");
  file_out->cd();
  for(map<TString, TH1D*>::iterator it=map_TH1D.begin(); it!=map_TH1D.end(); it++){
    it->second->Write();
  }
  for(map<TString, TH2D*>::iterator it=map_TH2D.begin(); it!=map_TH2D.end(); it++){
    it->second->Write();
  }

  file_out->Close();





}
