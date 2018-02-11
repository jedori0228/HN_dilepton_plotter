#include "canvas_margin.h"
#include "mylib.h"

void ForLatex_MakeCutFlowTable(){

  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = kError;

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/Regions/";
  TString NMCfilepath = WORKING_DIR+"/data/SignalN_MC.txt";

  //==== Sample list
  //==== copied from Draw_SR.C

  map< TString, vector<TString> > map_sample_string_to_list;
  map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  map_sample_string_to_list["WJets"] = {"WJets"};
  map_sample_string_to_list["VV_excl"] = {
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
  };
  map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  map_sample_string_to_list["ttbar"] = {"TT_powheg"};
  map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  map_sample_string_to_list["top_tt"] = {"TT_powheg", "ttW", "ttZ", "ttH_nonbb"};
  map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted"};
  //map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG"};
  map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  map_sample_string_to_list["fake_Dijet_LooseBJet"] = {"fake_Dijet_LooseBJet"};
  map_sample_string_to_list["chargeflip"] = {"chargeflip"};

  vector<TString> samples_to_use = {"chargeflip", "Xgamma", "fake_Dijet", "VV_excl", "VVV", "top", "WW_double"};
  vector<TString> bkglist;

  for(unsigned int i=0; i<samples_to_use.size(); i++){
    bkglist.insert(bkglist.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
  //cout << "We will use :" << endl;
  //for(unsigned int i=0; i<bkglist.size(); i++) cout << " " << bkglist[i] << endl;

  vector<TString> channels = {
    "MuMu",
    "ElEl",
    "MuEl",
  };

  vector<TString> CutFlowNames = {
    "MET_PV_Trig",
    "TwoLeptons",
    "SS",
    "NoExtraFlavourLepton",
    "LowDileptonMass",
    "JetRequirements",
  };
  vector<TString> CutFlowNames_ForLatex = {
    "{\\bf Trigger}",
    "{\\bf 2 $\\ell$}",
    "{\\bf $\\ell^{\\pm} \\ell^{\\pm}$}",
    "{\\bf 3rd $\\ell$ veto}",
    "{\\bf $m_{\\ell \\ell} < 10~\\GeV$}",
    "{\\bf Jet requirement}",
  };

  vector<int> signal_masses = {
    50, 100, 500, -800, 1100, -1200,
  };

  vector<double> ref_scale = {
    0.0001, 0.01, 0.1, 0.1, 1, 1,
  };
  vector<TString> ref_scaleForTex = {
    "0.0001", "0.01", "0.1", "0.1", "1", "1",
  };

  for(unsigned int it_ch=0; it_ch<channels.size(); it_ch++){

    TString channel = channels.at(it_ch);

    TString region = "DiMuon";
    if(channel=="ElEl"){
      region = "DiElectron";
    }
    if(channel=="MuEl"){
      region = "EMu";
    }

    cout << "\\begin{table}[!hptb]" << endl;
    cout << "  \\centering" << endl;
    cout << "  \\caption{" << endl;
    if(channel=="MuMu"){
      //cout << "  Expected yields for the background and several $\\N$ mass signals (with  $\\left| V_{\\mu N} \\right|^2 = 10^{-5}$), after several cuts applied for preselection." << endl;
      cout << "  Expected yields for the background and several dimuon channel $\\N$ mass signals, after several cuts applied for preselection." << endl;
    }
    if(channel=="ElEl"){
      //cout << "Expected yields for the background and several $\\N$ mass signals (with  $\\left| V_{e N} \\right|^2 = 10^{-5}$), after several cuts applied for preselection." << endl;
      cout << "  Expected yields for the background and several dielectron channel $\\N$ mass signals, after several cuts applied for preselection." << endl;
    }
    if(channel=="MuEl"){
      //cout << "Expected yields for the background and several $\\N$ mass signals (with  $\\left| V_{\\mu N}V_{e N} \\right| = 10^{-5}$), after several cuts applied for preselection." << endl;
      cout << "  Expected yields for the background and several emu channel $\\N$ mass signals, after several cuts applied for preselection." << endl;
    }
    cout << "  }" << endl;
    cout << "  \\label{table:cutflow_presel_"<< region <<"}" << endl;
    cout << "  \\begin{center}" << endl;
    cout << "    \\resizebox{\\columnwidth}{!}{" << endl;
    cout << "      \\begin{tabular}{c|c|c|c|c|c|c|c}" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "\\hline" << endl;
    cout << "& \\multirow{2}{*}{\\bf Total bkg.}" ;
    for(unsigned it_sig=0; it_sig<signal_masses.size(); it_sig++){
      cout << "& $m_{N}$ = "<<TString::Itoa(abs(signal_masses.at(it_sig)),10)<<"~$\\GeV$ ";
    }
    cout << " \\\\" << endl;
    cout << "& " ;
    for(unsigned it_sig=0; it_sig<signal_masses.size(); it_sig++){
      TString fdch = "s-ch";
      if(signal_masses.at(it_sig)<0) fdch = "t-ch";
      if(channel=="MuMu") cout << "& "+fdch+" $\\left| V_{\\mu N} \\right|^2 = "<< ref_scaleForTex.at(it_sig) << "$ ";
      if(channel=="ElEl") cout << "& "+fdch+" $\\left| V_{e N} \\right|^2 = "<< ref_scaleForTex.at(it_sig) << "$ ";
      if(channel=="MuEl") cout << "& "+fdch+" $\\left| V_{\ell N} \\right|^2 = "<< ref_scaleForTex.at(it_sig) << "$ ";
    }
    cout << " \\\\" << endl;
    //cout << "& {\\bf Total bkg.} & $m_{N}$ = 40~$\\GeV$ &  $m_{N}$ = 100~$\\GeV$ &  $m_{N}$ = 300~$\\GeV$ & $m_{N}$ = 1000~$\\GeV$ \\\\" << endl;
    cout << "\\hline" << endl;

    for(unsigned it_CutFlowName=0; it_CutFlowName<CutFlowNames.size(); it_CutFlowName++){
      TString CutFlowName = CutFlowNames.at(it_CutFlowName);
      cout << CutFlowNames_ForLatex.at(it_CutFlowName) << " & ";

      int n_pre = 2;
      cout << std::fixed << std::setprecision(n_pre);
      //cout << std::scientific;

      //==== Bkgd
      double bkgd_yield = 0.;
      for(unsigned int it_bkgd=0; it_bkgd<bkglist.size(); it_bkgd++){
        TString filename = "DiLeptonAnalyzer_SK"+bkglist.at(it_bkgd)+"_dilep_cat_"+catversion+".root";
        if(bkglist.at(it_bkgd).Contains("fake")){
          if(channel=="MuMu") filename = "DiLeptonAnalyzer_SKfake_Dijet_DoubleMuon_dilep_cat_"+catversion+".root";
          if(channel=="ElEl") filename = "DiLeptonAnalyzer_SKfake_Dijet_DoubleEG_dilep_cat_"+catversion+".root";
          if(channel=="MuEl") filename = "DiLeptonAnalyzer_SKfake_Dijet_MuonEG_dilep_cat_"+catversion+".root";
        }
        if(bkglist.at(it_bkgd).Contains("chargeflip")){
          if(channel=="ElEl") filename = "DiLeptonAnalyzer_SKchargeflip_DoubleEG_dilep_cat_"+catversion+".root";
          else continue;
        }
        TFile *file = new TFile(filepath+"/"+filename);
        TH1D *hist = (TH1D *)file->Get("Cutflow_"+region+"_"+CutFlowName);
        if(!hist) continue;
        bkgd_yield += hist->GetBinContent(1);
        file->Close();
        delete file;
      }
      cout << "$" << bkgd_yield << "$";

      //==== Signal
      for(unsigned it_sig=0; it_sig<signal_masses.size(); it_sig++){

        TString filename = "DiLeptonAnalyzer_SKHNMoriondLL"+channel+"_"+TString::Itoa(signal_masses.at(it_sig),10)+"_cat_"+catversion+".root";
        if(signal_masses.at(it_sig)<0) filename = "DiLeptonAnalyzer_SKHeavyNeutrinoTo"+channel+"_Tchannel_M"+TString::Itoa(abs(signal_masses.at(it_sig)),10)+"_cat_"+catversion+".root";
        TFile *file = new TFile(filepath+"/Signal/"+filename);
        TH1D *hist = (TH1D *)file->Get("Cutflow_"+region+"_"+CutFlowName);

        double scale = ref_scale.at(it_sig)/0.01;

        //==== Get N_MC
        TString signalname = "";
        if(signal_masses.at(it_sig)>0){
          signalname = "HNMoriondLL"+channel+"_"+TString::Itoa(signal_masses.at(it_sig),10);
        }
        else{
          signalname = "HeavyNeutrinoTo"+channel+"_Tchannel_M"+TString::Itoa(abs(signal_masses.at(it_sig)),10);
        }

        string elline;
        ifstream in(NMCfilepath);
        int N_MC = -999;
        while(getline(in,elline)){
          std::istringstream is( elline );
          TString samplename;
          is >> samplename;
          is >> N_MC;
          if(samplename==signalname){
            break;
          }
        }

        double eff_sig = hist->GetEntries()/N_MC;

        cout << " & $" << hist->GetBinContent(1)*scale << "$ $("<<100.*eff_sig<<"~\\%)$";
        //cout << " & $" << hist->GetBinContent(1)*scale << "$ $("<<hist->GetEntries()<<","<<N_MC<<"~\\%)$";
      }

      cout << " \\\\" << endl;
    }



    cout << "\\hline" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "      \\end{tabular}" << endl;
    cout << "    }" << endl;
    cout << "  \\end{center}" << endl;
    cout << "\\end{table}" << endl;
    cout << endl << endl;


  }



}
















