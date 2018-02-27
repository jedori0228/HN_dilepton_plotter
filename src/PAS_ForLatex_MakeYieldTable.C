#include "RunNtupleForBinnedYieldPlot.C"
#include "canvas_margin.h"
#include "mylib.h"

void PAS_ForLatex_MakeYieldTable(int lepch=0){

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  bool DoDebug = false;

  vector<TString> channels;
  TString channelForLatex = "";
  if(lepch==0){
    channels.push_back("MuMu");
    channelForLatex = "$\\mu\\mu$";
  }
  if(lepch==1){
    channels.push_back("ElEl");
    channelForLatex = "$ee$";
  }
  if(lepch==2){
    channels.push_back("MuEl");
    channelForLatex = "$e \\mu$";
  }

  vector<TString> WhichRegions = {
    "Low_TwoJet_NoFatjet_SS",
    "Low_OneJet_NoFatjet_SS",
    "High_TwoJet_NoFatjet_SS",
    "High_OneFatJet_SS",
  };
  vector<TString> TreeDirNames = {
    "Skimmed_Low_TwoJet_NoFatjet",
    "Skimmed_Low_OneJet_NoFatjet",
    "Skimmed_High_TwoJet_NoFatjet",
    "Skimmed_High_OneFatJet",
  };
  vector<TString> WhichRegionsForTex = {
    "Low-Mass SR1",
    "Low-Mass SR2",
    "High-Mass SR1",
    "High-Mass SR2",
  };

  vector<TString> allbkgs = {
    "fake_Dijet",
    "TG", "TTG",
    "ZGto2LG", "WGtoLNuG_weighted",
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
    "WWW", "WWZ", "WZZ", "ZZZ",
    "ttW", "ttZ", "ttH_nonbb",
    "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD",
  };

  vector< vector<TString> > bkglists = {
    {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD",},
    {"ttW", "ttZ", "ttH_nonbb",},
    {"WWW", "WWZ", "WZZ", "ZZZ",},
    {"WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",},
    {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted",},
    {"fake_Dijet",},
    {"chargeflip",},
    {"data"},
  };
  int index_ENDMC = 4;
  vector<TString> bkgdtypes = {
    "DoubleWW",
    "top",
    "triboson",
    "diboson",
    "$X + \\gamma$",
    "Fake lepton background",
    "Charge-flip background",
  };

  vector<TString> systs = {
    "",
    "_MuonEn_up", "_MuonEn_down",
    "_MuonIDSF_up", "_MuonIDSF_down",
    "_ElectronEn_up", "_ElectronEn_down",
    "_ElectronIDSF_up", "_ElectronIDSF_down",
    "_TriggerSF_up", "_TriggerSF_down",
    "_PU_up", "_PU_down",
    "_JetEn_up", "_JetEn_down",
    "_JetRes_up", "_JetRes_down",
    "_Unclustered_up", "_Unclustered_down",
    "_BTagSFEff_up", "_BTagSFEff_down",
    "_BTagSFMiss_up", "_BTagSFMiss_down",
    "_JetMass_up", "_JetMass_down",
    "_JetMassRes_up", "_JetMassRes_down",
    "_Tau21_up", "_Tau21_down",
  };
  
  for(unsigned int it_region=0; it_region<WhichRegions.size(); it_region++){

    TString WhichRegion = WhichRegions.at(it_region);
    TString TreeDirName = TreeDirNames.at(it_region);

    //cout << channelForLatex << " / "+WhichRegionsForTex.at(it_region)+" &" << endl;
    cout << WhichRegionsForTex.at(it_region);

    vector<int> ref_sigs;
    vector<double> ref_scale = {0.01, 0.01, 0.1, 1};
    vector<TString> ref_scaleForTex = {"0.01", "0.01", "0.1", "1"};

/*
    vector<int> ref_sigs = {1100};
    vector<double> ref_scale = {1};
    vector<TString> ref_scaleForTex = {"1"};

    if(WhichRegion.Contains("Low")){
      ref_sigs = {50};
      ref_scale = {0.0001};
      ref_scaleForTex = {"0.0001"};
    }
*/
    int index_signal = -1;
    int n_bkglist = bkglists.size();
    int n_refsig = ref_sigs.size();

    vector<double> MC_yield = {0., 0., 0.};
    vector<double> MC_stat = {0., 0., 0.};
    vector<double> MC_syst = {0., 0., 0.}; //SAME AS # of CHANNEL
    vector<double> Data_yield = {0., 0., 0.};
    vector<double> Total_yield = {0., 0., 0.};
    vector<double> Total_stat = {0., 0., 0.};
    vector<double> Total_syst = {0., 0., 0.}; //SAME AS # of CHANNEL

    for(int it_bkg = 0; it_bkg < n_bkglist+n_refsig; it_bkg++){

      vector<TString> bkglist;
      TString bkgdtype;

      bool isCF = false;
      bool isFake = false;
      bool isSignal = false;
      bool isData = false;

      if(it_bkg < n_bkglist){
        bkglist = bkglists.at(it_bkg);

        for(int a=0;a<bkglist.size();a++){
          if(bkglist.at(a).Contains("chargeflip")) isCF = true;
          if(bkglist.at(a).Contains("fake")) isFake = true;
          if(bkglist.at(a).Contains("data")) isData = true;
        }
        bool isMC = !isCF && !isFake;

        if(isCF){
          //cout << "{\\bf Data-driven background estimate:} & & & \\\\" << endl;
        }

        //cout << bkgdtypes.at(it_bkg);
      }
      else{
        isSignal = true;
        index_signal++;
      }

      for(unsigned it_channel=0; it_channel<channels.size(); it_channel++){

        TString channel = channels.at(it_channel);

        TString V2 = "|V_{N#mu}|^{2}";
        TString V2ForTex = "|V_{N \\mu}|^{2}";
        if(channel=="ElEl"){
          V2 = "|V_{Ne}|^{2}";
          V2ForTex = "|V_{N e}|^{2}";
        }
        if(channel=="MuEl"){
          V2 = "|V_{Nl}|^{2}";
          V2ForTex = "|V_{N \\ell}|^{2}";
        }

        if(isSignal){
          bkglist = {"HNMoriondLL"+channel+"_"+TString::Itoa(ref_sigs.at(index_signal),10)};
          bkgdtype = "$m_N = "+TString::Itoa(ref_sigs.at(index_signal),10)+"$~\\GeVcc, $"+V2ForTex+" = "+ref_scaleForTex.at(index_signal)+"$";
          if(it_channel==0){
            //if(index_signal==0) cout << "Majorana neutrino signal & & & \\\\" << endl;
            //cout << bkgdtype;
          }
        }

        bool isMC = !isCF && !isFake;

        if(channel!="ElEl" && isCF){
          //cout << " & -";
          continue;
        }

        TString DataPD = "";
        TString ChannelName = "";

        if(channel=="ElEl"){
          DataPD = "DoubleEG";
          ChannelName = "DiElectron";
        }
        else if(channel=="MuMu"){
          DataPD = "DoubleMuon";
          ChannelName = "DiMuon";
        }
        else if(channel=="MuEl"){
          DataPD = "MuonEG";
          ChannelName = "EMu";
        }

        double Yield = 0.;
        double StatError = 0.;
        double SystError(0.);

        vector<double> reldiff_means;
        double reldiff_up, reldiff_down;
        double reldiff_sig_up, reldiff_sig_down;

        int n_syst = systs.size();
        if(isData) n_syst=1;
        for(unsigned int i=0; i<n_syst; i++){

          TString this_syst = systs.at(i);

          //==== Declare Object

          RunNtupleForBinnedYieldPlot m;
          m.DoDebug = DoDebug;
          m.RunSystematic = true;
          m.MakeYieldTable = true;

          //==== Skim selection for tree (tree name : Ntp_<skim>)

          m.treeskim = WhichRegion;

          //==== Dataset/channel

          m.DataPD = DataPD;
          m.channel = ChannelName+this_syst;
          m.channel_for_jetres = ChannelName;

          //==== Filename info

          m.filename_prefix = "DiLeptonAnalyzer";
          m.filename_suffix = "cat_"+catversion+".root";

          //==== Input/Output

          m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/"+TreeDirName+"/";
          m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

          //==== Signal Info

          m.preselection = "Preselection_SS";
          m.MinEffPresel = 0.;

          //==== Fill MCNorm SF

          m.analysisInputs.DoPrint = false;
          m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", allbkgs);

          //==== Get Systematics

          m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
          m.SetSourceSystematics();

          //==== Set CutCard

          m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/Empty.txt");
          m.AddSamplesToList( bkglist );

          m.Run();

          if(i==0){
            Yield = m.total_bkgs;
            StatError = m.fake_bkgs_stat + m.prompt_bkgs_stat + m.cf_bkgs_stat;

            if(isMC){
              //==== Lumi
              double syst_lumi = m.analysisInputs.CalculatedSysts["Luminosity"];
              //cout << "Lumi : " << syst_lumi*Yield << endl;
              SystError += (syst_lumi*Yield)*(syst_lumi*Yield);
              //==== MCSF
              SystError += m.prompt_bkgs_syst*m.prompt_bkgs_syst;
              //cout << "MCSF : " << m.prompt_bkgs_syst << endl;
            }
            if(isFake){
              SystError += m.fake_bkgs_syst*m.fake_bkgs_syst;
            }
            if(isCF){
              SystError += m.cf_bkgs_syst*m.cf_bkgs_syst;
            }

            if(isSignal){
              m.pdfsyst.Yield_Central = Yield;
              m.pdfsyst.CalculatePdfSystematic();

              SystError += m.pdfsyst.Syst_Pdf_Total*m.pdfsyst.Syst_Pdf_Total*Yield*Yield;
            }

            if(isData){
              Data_yield.at(it_channel) = m.y_observed;
            }

          }

          double reldiff = (m.total_bkgs-Yield)/Yield;

          if(i!=0){

            //==== i=1 : up / i=2 : down

            if(i%2==1){
              reldiff_up = reldiff;
            }
            else{
              reldiff_down = reldiff;

              double reldiff_mean = sqrt( 0.5 * (reldiff_up*reldiff_up+reldiff_down*reldiff_down) );

              reldiff_means.push_back( reldiff_mean );

            }

          } // Not Central, add systematics


        } // END Loop Syst sources

        if(isData) continue;

        for(unsigned int i=0; i<reldiff_means.size(); i++){

          SystError += reldiff_means.at(i)*reldiff_means.at(i)*Yield*Yield;

        }

        SystError = sqrt(SystError);


        if(!isSignal){
          if(isFake||isCF){
            cout << " & $"; AddPhantomZero(Yield,"r",3,1); cout << " \\pm "; AddPhantomZero(StatError,"r",2,1); cout << " \\pm "; AddPhantomZero(SystError,"l",3,1);
            cout << "$";
            if(lepch!=1&&isFake) cout << " & -- ";
          }

           if(isMC){
             MC_yield.at(it_channel) += Yield;
             MC_stat.at(it_channel) += StatError*StatError;
             MC_syst.at(it_channel) += SystError*SystError;
           }
           Total_yield.at(it_channel) += Yield;
           Total_stat.at(it_channel) += StatError*StatError;
           Total_syst.at(it_channel) += SystError*SystError;

        }
        else{
          double scale = ref_scale.at(index_signal)/0.01;

          //cout << " & $" << std::fixed<<std::setprecision(2) << Yield*scale << " \\pm " << StatError*scale << "~\\stat \\pm " << SystError*scale << "~\\syst $";
        }

      } // END Loop mm ee em

      if(isData) continue;

      //cout << " \\\\" << endl;

      if(it_bkg==index_ENDMC){
        //cout << "\\hline" << endl;
        for(int i=0; i<channels.size(); i++){
          cout << "& $"; AddPhantomZero(MC_yield.at(i),"r",3,1); cout << " \\pm "; AddPhantomZero(sqrt(MC_stat.at(i)),"r",2,1);cout << " \\pm "; AddPhantomZero(sqrt(MC_syst.at(i)),"l",3,1);
          cout << "$ ";
        }
      }

      if(it_bkg==bkglists.size()-2){
        for(int i=0; i<channels.size(); i++){
          cout << "& $"; AddPhantomZero(Total_yield.at(i),"r",4,1);cout << " \\pm "; AddPhantomZero(sqrt(Total_stat.at(i)),"r",2,1);cout << " \\pm "; AddPhantomZero(sqrt(Total_syst.at(i)),"l",3,1);
          cout << "$ ";
        }
      }

    } // END bkglists

    //==== data
    cout << "& $" << int(Data_yield.at(0)) << "$ \\\\" << endl;


  } // END Loop Region

}

