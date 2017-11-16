#include "canvas_margin.h"

void Draw_SignalResolution(){

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Regions/Signal/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalResolution/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  vector<int> masses = {40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
  vector<TString> channels = {"MuMu", "ElEl", "MuEl"};

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    for(unsigned int j=0; j<masses.size(); j++){

      TString mass = TString::Itoa(masses.at(j),10);

			vector<TString> regions, vars; 
			if(masses.at(j)<=80){ 
				regions = {"Low_TwoJet_NoFatJet", "Low_OneJet_NoFatJet"};
				vars = {"m_Leadljj_lljjWclosest", "m_SubLeadljj_lljjWclosest", "m_Leadlj", "m_SubLeadlj"};
      }
			else{
				regions = {"High_TwoJet_NoFatJet", "High_OneFatJet"};
				vars = {"m_Leadljj_jjWclosest", "m_SubLeadljj_jjWclosest", "m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest"};
			}

			for(unsigned int k=0; k<regions.size(); k++){
				TString region = regions.at(k);

				for(unsigned int l=0; l<vars.size(); l++){

					TString filename = "DiLeptonAnalyzer_SKHN"+channel+"_"+mass+"_cat_v8-0-7.root";
					TFile *file = new TFile(base_filepath+filename);

					TString PDName = "";
					if(channel=="MuMu") PDName = "DiMuon";
					if(channel=="ElEl") PDName = "DiElectron";
					if(channel=="MuEl") PDName = "EMu";

					TString histname = PDName+"_"+region+"_SS/"+vars.at(l)+"_"+PDName+"_"+region+"_SS";
					TH1D *hist = (TH1D *)file->Get(histname);
          if(!hist) continue;

          cout << channel << "\t" << mass << "\t" << region << "\t" << vars.at(l) << "\t" << hist->GetMean() << "\t" << hist->GetRMS() << endl;

					TCanvas *c1 = new TCanvas("c1", "", 600, 600);
					canvas_margin(c1);
					c1->Draw();
					c1->cd();
					hist->Draw("histsame");
					//c1->SaveAs(base_plotpath+"/HN"+channel+"_"+mass+"_"+vars.at(l)+".pdf");
					c1->Close();

			  }

      }


    }


  }

}
