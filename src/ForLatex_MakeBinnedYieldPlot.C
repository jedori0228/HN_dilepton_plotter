#include "RunNtupleForBinnedYieldPlot.C"
#include "canvas_margin.h"

void ForLatex_MakeBinnedYieldPlot(int x=0){

  TString channel = "MuMu";
  if(x==1) channel = "ElEl";
  if(x==2) channel = "MuEl";

  TString V2 = "|V_{N#mu}|^{2}";
  if(channel=="ElEl") V2 = "|V_{Ne}|^{2}";
  if(channel=="MuEl") V2 = "|V_{Nl}|^{2}";

  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> MCsector_first_index;

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
  //m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG"};
  map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  map_sample_string_to_list["fake_Dijet_LooseBJet"] = {"fake_Dijet_LooseBJet"};
  map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  map_sample_string_to_list["prompt"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted", "WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ", "WWW", "WWZ", "WZZ", "ZZZ", "ttW", "ttZ", "ttH_nonbb", "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};

  map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  map_sample_string_to_legendinfo["top_tt"] = make_pair("top", kRed);
  map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_Dijet_LooseBJet"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["chargeflip"] = make_pair("Mismeas. charge background", kYellow);
  map_sample_string_to_legendinfo["prompt"] = make_pair("Prompt background", kSpring-1);

  vector<TString> samples_to_use = {"fake_Dijet", "prompt"};
  if(channel=="ElEl") samples_to_use = {"chargeflip", "fake_Dijet", "prompt"};

  TLegend *lg = new TLegend(0.60, 0.60, 0.96, 0.92);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);
  //==== error bar
  TH1D *histtmperr = new TH1D("histtmperr", "", 1, 0., 1.);
  histtmperr->SetMarkerColorAlpha(kAzure-9, 0);
  histtmperr->SetFillStyle(3013);
  histtmperr->SetFillColor(kBlack);
  histtmperr->SetLineColor(0);
  lg->AddEntry(histtmperr, "Stat.+Syst. Uncert.", "f");
  //==== data
  TH1D *histtmpdata = new TH1D("histtmpdata", "", 1, 0., 1.);
  histtmpdata->SetMarkerStyle(20);
  histtmpdata->SetMarkerSize(1.6);
  histtmpdata->SetMarkerColor(kBlack);
  histtmpdata->SetLineColor(kBlack);
  lg->AddEntry(histtmpdata, "Data", "ple");
  
  for(int i=samples_to_use.size()-1; i>=0; i--){
    TH1D *histtmp = new TH1D(samples_to_use.at(i), "", 1, 0., 1.);
    histtmp->SetLineColor(map_sample_string_to_legendinfo[samples_to_use.at(i)].second);
    histtmp->SetFillColor(map_sample_string_to_legendinfo[samples_to_use.at(i)].second);
    lg->AddEntry(histtmp, map_sample_string_to_legendinfo[samples_to_use.at(i)].first, "f");
  }

  vector<TString> bkglist;
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    MCsector_first_index.push_back( bkglist.size() );
    bkglist.insert(bkglist.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
  bkglist.push_back("data");
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<bkglist.size(); i++) cout << " " << bkglist[i] << endl;

  gStyle->SetOptStat(0);
  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  bool DoDebug = false;

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
    "Low Mass SR1",
    "Low Mass SR2",
    "High Mass SR1",
    "High Mass SR2",
  };
  
  for(unsigned int it_region=0; it_region<WhichRegions.size(); it_region++){

    TString WhichRegion = WhichRegions.at(it_region);
    TString TreeDirName = TreeDirNames.at(it_region);
    TString CutCarDirName = "";
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

    if(WhichRegion.Contains("TwoJet")) CutCarDirName = "Cards_"+channel+"_Bin1";
    else CutCarDirName = "Cards_"+channel+"_Bin2";

    cout << "#### " << WhichRegion << " ####" << endl;
    cout << "#### " << TreeDirName << " ####" << endl;
    cout << "#### " << CutCarDirName << " ####" << endl;
    cout << "#### " << DataPD << " ####" << endl;
    cout << "#### " << ChannelName << " ####" << endl;

    TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/BinnedYieldPlot/";

    vector<int> masses = {85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700};
    vector<int> ref_sigs = {100, 500, 1000, 1500};
    vector<Color_t> ref_sigs_style = {1,3,5,7};
    vector<double> ref_scale = {0.001, 0.1, 1, 1};

    if(WhichRegion.Contains("Low")){
      masses = {20, 30, 40, 50, 60, 70, 75};
      ref_sigs = {40, 60, 70};
      ref_scale = {0.00001, 0.00001, 0.001};
    }

    const int N_mass = masses.size();
    TH1D *hist_bkgd = new TH1D("hist_bkgd", "", N_mass, 0., 1.*N_mass);
    TH1D *hist_obs = new TH1D("hist_obs", "", N_mass, 0., 1.*N_mass);

    THStack *stack_bkgd = new THStack("stack_bkgd", "");

    vector<TH1D *> hist_sigs;
    for(unsigned int i=0; i<ref_sigs.size(); i++){
      TH1D *tmp = new TH1D("hist_sigs_"+TString::Itoa(ref_sigs.at(i),10), "", N_mass, 0., 1.*N_mass);
      hist_sigs.push_back(tmp);
    }

    for(unsigned it_mass=0; it_mass<masses.size(); it_mass++){

      TString mass = TString::Itoa(masses.at(it_mass),10);

      //==== Declare Object

      RunNtupleForBinnedYieldPlot m;
      m.DoDebug = DoDebug;
      m.DrawBinnedYieldPlot = true;
      m.MakeYieldTable = false;

      //==== Skim selection for tree (tree name : Ntp_<skim>)

      m.treeskim = WhichRegion;

      //==== Plotting

      m.map_sample_string_to_list = map_sample_string_to_list;
      m.map_sample_string_to_legendinfo = map_sample_string_to_legendinfo;
      m.MCsector_first_index = MCsector_first_index;
      m.onlybkgd = bkglist;
      m.samples_to_use = samples_to_use;

      //==== Dataset/channel

      m.DataPD = DataPD;
      m.channel = ChannelName;

      //==== Filename info

      m.filename_prefix = "DiLeptonAnalyzer";
      m.filename_suffix = "cat_"+catversion+".root";

      //==== Input/Output

      m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/"+TreeDirName+"/";
      m.plotpath = ENV_PLOT_PATH+"/"+dataset+"/cutop/";

      //==== Signal Info

      m.preselection = "Preselection_SS";
      for(unsigned int i=0; i<ref_sigs.size(); i++){
        m.signals.push_back("HN"+channel+"_"+TString::Itoa(ref_sigs.at(i),10));
      }
      m.MinEffPresel = 0.;
      m.FillSignalInfo();
      m.AddSamplesToList( m.signals );

      //==== Backgrounds

      m.AddSamplesToList( bkglist );

      if(DoDebug) m.PrintSampleList();

      //==== Fill MCNorm SF

      m.analysisInputs.DoPrint = false;
      m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

      //==== Get Systematics

      m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
      m.SetSourceSystematics();

      //==== Set CutCard

      TString cutfilename = "HN"+channel+"_"+mass+".txt";
      m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/RunDirectory/"+CutCarDirName+"/"+cutfilename);

      m.Run();

      TList *bkgdlist = m.MC_stacked->GetHists();
      for(int k=0; k<bkgdlist->Capacity(); k++){

        TH1D *new_hist = new TH1D("new_hist", "", N_mass, 0., 1.*N_mass);
        TH1D *original_hist = (TH1D*)bkgdlist->At(k);

        TString this_name = original_hist->GetName();

        double this_yield = original_hist->GetBinContent(1);
        double this_err = original_hist->GetBinError(1);
        if(this_name.Contains("fake")){
          //cout << "This fake yield = " << original_hist->GetBinContent(1) << "\t" << endl;

          if(original_hist->GetBinContent(1)<=0.){
            double frmax = 0.169201;
            if(channel=="MuMu"){
              frmax=0.103305;
            }
            double thisweight = frmax/(1.-frmax);
            double ZeroFakeStatError = 1.8*thisweight;
            //cout << "--> additional error = " << ZeroFakeStatError << endl;
            this_yield = 0.;
            this_err = ZeroFakeStatError;
          }
        }
        if(original_hist->GetBinContent(1)<=0.) this_yield = 0.;

        new_hist->SetBinContent(it_mass+1, this_yield);
        new_hist->SetBinError(it_mass+1, this_err);

        if(this_name.Contains("fake")){
          //cout << new_hist->GetBinContent(it_mass+1) << "\t" << new_hist->GetBinError(it_mass+1) << endl;
        }

        new_hist->SetFillColor( original_hist->GetFillColor() );
        new_hist->SetLineColor( original_hist->GetLineColor() );
        new_hist->SetName(original_hist->GetName());
        stack_bkgd->Add(new_hist);
        hist_bkgd->Add(new_hist);

      }

      //hist_bkgd->SetBinContent(it_mass+1, m.total_bkgs);
      //hist_bkgd->SetBinError(it_mass+1, m.total_bkgs_err);

      hist_obs->SetBinContent(it_mass+1, m.y_observed);
      hist_obs->SetBinError(it_mass+1, sqrt(m.y_observed));

      for(unsigned int i=0; i<ref_sigs.size(); i++){
        hist_sigs.at(i)->SetBinContent(it_mass+1, m.signal_rate.at(i));
      }

    } // END mass loop

    //==== Draw

    TCanvas* c1 = new TCanvas("c1", "", 800, 800);
    c1->Draw();
    TPad *c1_up;
    TPad *c1_down;
    c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
    c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

    canvas_margin(c1, c1_up, c1_down);

    c1_up->Draw();
    c1_down->Draw();
    c1_up->cd();

    TH1D *hist_empty = (TH1D *)hist_bkgd->Clone();
    hist_empty->SetLineWidth(0);
    hist_empty->SetLineColor(0);
    hist_empty->SetMarkerSize(0);
    hist_empty->SetMarkerColor(0);
    hist_empty->Draw("hist");
    hist_axis(hist_empty);
    hist_empty->GetYaxis()->SetTitle("Events / Signal Region");

    double y_max = 500;
    double y_min = 0.02;
    if(WhichRegion.Contains("Low")){
      y_max = 500;
      y_min = 5;
    }
    hist_empty->GetYaxis()->SetRangeUser(y_min, y_max);
    for(int i=0; i<hist_empty->GetXaxis()->GetNbins(); i++){
      TString mass = TString::Itoa(masses.at(i),10);
      hist_empty->GetXaxis()->SetBinLabel(i+1, mass);
    }

    stack_bkgd->Draw("histsame");

    hist_bkgd->SetMarkerColorAlpha(kAzure-9, 0);
    hist_bkgd->SetFillStyle(3013);
    hist_bkgd->SetFillColor(kBlack);
    hist_bkgd->SetLineColor(0);
    hist_bkgd->Draw("sameE2");

    vector<float> err_up_tmp;
    vector<float> err_down_tmp;
    const double alpha = 1 - 0.6827;
    TGraphAsymmErrors *gr_obs = new TGraphAsymmErrors(hist_obs);
    for(int i=0; i<gr_obs->GetN(); ++i){
      int N = gr_obs->GetY()[i];
      double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
      double U =  (N==0) ? ( ROOT::Math::gamma_quantile_c(alpha,N+1,1) ) : ( ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) );
      if( N!=0 ){
        gr_obs->SetPointEYlow(i, N-L );
        gr_obs->SetPointEXlow(i, 0);
        gr_obs->SetPointEYhigh(i, U-N );
        gr_obs->SetPointEXhigh(i, 0);
        err_down_tmp.push_back(N-L);
        err_up_tmp.push_back(U-N);
       }
      else{
        double zerodata_err_low = 0.1;
        double zerodata_err_high = 1.8;

        double xlow = gr_obs->GetX()[i]-gr_obs->GetEXlow()[i];
        double xhigh = gr_obs->GetX()[i]+gr_obs->GetEXhigh()[i];

        gr_obs->SetPointEYlow(i, zerodata_err_low);
        gr_obs->SetPointEXlow(i, 0.);
        gr_obs->SetPointEYhigh(i, zerodata_err_high);
        gr_obs->SetPointEXhigh(i, 0.);
        err_down_tmp.push_back(zerodata_err_low);
        err_up_tmp.push_back(zerodata_err_high);
      }
    }
    gr_obs->SetLineWidth(2.0);
    gr_obs->SetMarkerSize(0.);
    gr_obs->SetMarkerColor(kBlack);
    gr_obs->SetLineColor(kBlack);
    hist_obs->SetMarkerStyle(20);
    hist_obs->SetMarkerSize(1.6);
    hist_obs->Draw("phistsame");
    gr_obs->Draw("p0same");


    TLegend *lg_this = (TLegend *)lg->Clone();
    for(unsigned int i=0; i<ref_sigs.size(); i++){
      //hist_sigs.at(i)->Draw("histsame");
      hist_sigs.at(i)->SetLineColor(kBlack);
      hist_sigs.at(i)->SetLineStyle(ref_sigs_style.at(i));
      hist_sigs.at(i)->SetLineWidth(3);
      hist_sigs.at(i)->Scale(ref_scale.at(i)/0.01);

      TString signalname = "";
      double log_coupling = TMath::Log10(ref_scale.at(i));

      TString FDchannel = "Sch";

      if(log_coupling == 0) signalname = FDchannel+" HN"+TString::Itoa(ref_sigs.at(i), 10)+", "+V2+"=1";
      else signalname = FDchannel+" HN"+TString::Itoa(ref_sigs.at(i), 10)+", "+V2+"=10^{"+TString::Itoa(log_coupling, 10)+"}";

      //lg_this->AddEntry(hist_sigs.at(i), signalname, "l");
    }

    lg_this->Draw();
    c1_up->SetLogy();

    c1->cd();
    TLatex channelname;
    channelname.SetNDC();
    channelname.SetTextSize(0.035);
    TString channelForTex = "#mu#mu";
    if(channel=="ElEl") channelForTex = "ee";
    if(channel=="MuEl") channelForTex = "e#mu";

    channelname.DrawLatex(0.2, 0.80, channelForTex+" "+WhichRegionsForTex.at(it_region));

    TLatex latex_CMSPriliminary, latex_Lumi;
    latex_CMSPriliminary.SetNDC();
    latex_Lumi.SetNDC();

    latex_CMSPriliminary.SetTextSize(0.050);
    latex_CMSPriliminary.DrawLatex(0.20, 0.90, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");

    latex_Lumi.SetTextSize(0.035);
    latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

    c1_up->cd();
    hist_empty->Draw("axissame");

    c1_down->cd();

    TString name_suffix = hist_obs->GetName();
    TH1D *ratio = (TH1D *)hist_obs->Clone();
    ratio->SetName(name_suffix+"_central");

    TH1D *tmp_ratio = (TH1D *)hist_obs->Clone();
    tmp_ratio->Divide(hist_bkgd);
    TGraphAsymmErrors *gr_ratio = new TGraphAsymmErrors(tmp_ratio);
    gr_ratio->SetName("gr_"+name_suffix+"_central");
    gr_ratio->SetLineWidth(2.0);
    gr_ratio->SetMarkerSize(0.);
    gr_ratio->SetLineColor(kBlack);

    TH1D *ratio_allerr = (TH1D *)hist_obs->Clone();
    ratio_allerr->SetName(name_suffix+"_allerr");
    for(int i=1; i<=ratio->GetXaxis()->GetNbins(); i++){
      //==== FIXME for zero? how?
      if(hist_bkgd->GetBinContent(i)!=0){

        //==== ratio point
        //==== BinContent = Data/Bkgd
        //==== BinError = DataError/Bkgd
        ratio->SetBinContent( i, ratio->GetBinContent(i) / hist_bkgd->GetBinContent(i) );
        ratio->SetBinError ( i, ratio->GetBinError(i) / hist_bkgd->GetBinContent(i) );

        if(err_down_tmp.at(i-1)  !=0.) {
          gr_ratio->SetPointEYlow(i-1, err_down_tmp.at(i-1) / hist_bkgd->GetBinContent(i) );
          gr_ratio->SetPointEXlow(i-1, 0);
          gr_ratio->SetPointEYhigh(i-1, err_up_tmp.at(i-1) /hist_bkgd->GetBinContent(i));
          gr_ratio->SetPointEXhigh(i-1, 0);
        }
        else{
          gr_ratio->SetPointEYlow(i-1, 0);
          gr_ratio->SetPointEXlow(i-1, 0);
          gr_ratio->SetPointEYhigh(i-1, 1.8 / hist_bkgd->GetBinContent(i));
          gr_ratio->SetPointEXhigh(i-1, 0);
        }

        //==== ratio allerr
        //==== BinContent = 1
        //==== BinError = Bkgd(Stat+Syst)Error/Bkgd
        ratio_allerr->SetBinContent( i, 1. );
        ratio_allerr->SetBinError( i, hist_bkgd->GetBinError(i)/ hist_bkgd->GetBinContent(i) );
      }
    }

    if(WhichRegion.Contains("High")) ratio_allerr->SetMaximum(10.0);
    else ratio_allerr->SetMaximum(2.0);
    ratio_allerr->SetMinimum(0.0);
    ratio_allerr->GetYaxis()->SetTitle("#frac{Obs.}{Pred.}");
    ratio_allerr->SetFillColor(kOrange);
    ratio_allerr->SetMarkerSize(0);
    ratio_allerr->SetMarkerStyle(0);
    ratio_allerr->SetLineColor(kWhite);
    ratio_allerr->Draw("E2same");
    hist_axis(hist_empty, ratio_allerr);

    ratio->Draw("p9histsame");
    gr_ratio->Draw("p0same");

    ratio_allerr->Draw("axissame");
    ratio_allerr->GetXaxis()->SetTitle("Signal Region (m_{N} in GeV)");
    ratio_allerr->GetXaxis()->SetLabelSize(0.1);
    for(int i=0; i<ratio_allerr->GetXaxis()->GetNbins(); i++){
      TString mass = TString::Itoa(masses.at(i),10);
      ratio_allerr->GetXaxis()->SetBinLabel(i+1, mass);
    }

    TLegend *lg_ratio = new TLegend(0.2, 0.8, 0.5, 0.9);
    lg_ratio->SetFillStyle(0);
    lg_ratio->SetBorderSize(0);
    lg_ratio->SetNColumns(2);
    //lg_ratio->AddEntry(ratio_staterr, "Stat.", "f");
    lg_ratio->AddEntry(ratio_allerr, "Stat.+Syst.", "f");
    lg_ratio->AddEntry(ratio, "Obs./Pred.", "p");
    lg_ratio->Draw();

    double x_1[2], y_1[2];
    x_1[0] = 5000;  y_1[0] = 1;
    x_1[1] = -5000;  y_1[1] = 1;
    TGraph *g1 = new TGraph(2, x_1, y_1);
    g1->Draw("same");


    gSystem->mkdir(plotpath+"/"+channel, kTRUE);
    c1->SaveAs(plotpath+"/"+channel+"/"+channel+"_"+WhichRegion+".pdf");
    c1->SaveAs(plotpath+"/"+channel+"/"+channel+"_"+WhichRegion+".png");
    c1->Close();
    delete c1;
    delete hist_bkgd;
    delete hist_empty;
    delete hist_obs;
    delete ratio;
    delete ratio_allerr;
    for(unsigned int i=0; i<ref_sigs.size(); i++){
      delete hist_sigs.at(i);
    }


  } // END Loop Region

}

