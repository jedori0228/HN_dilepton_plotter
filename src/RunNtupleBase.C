#include "RunNtupleBase.h"

void RunNtupleBase::Run(){

  //========================
  //==== CutRangeInfo Loop
  //========================

  cout << "##############################" << endl;
  cout << "#### OPTIMIZATION STARTED ####" << endl;
  cout << "##############################" << endl << endl;

  vector<cutinfo> OptimizedCutInfo;
  double final_cf(0.), final_cf_err(0.);
  double final_fake(0.), final_fake_err(0.);
  double final_prompt(0.), final_prompt_err(0.);
  vector<double> final_signal, final_signal_eff, final_signal_eff_preselection;
  for(unsigned int i=0; i<signals.size(); i++){
    final_signal.push_back(0.);
    final_signal_eff.push_back(0.);
    final_signal_eff_preselection.push_back(0.);
  }

  while( !CutRangeInfo.isEnd() ){

    if(CutRangeInfo.CurrentIteration%LogEvery==0){
      cout << "["; printcurrunttime(); cout <<"] ";
      cout << CutRangeInfo.CurrentIteration << " / " << CutRangeInfo.TotalIteration << " ("<<100.*CutRangeInfo.CurrentIteration/CutRangeInfo.TotalIteration<<" %)"<<endl;
      for(unsigned int i=0; i<OptimizedCutInfo.size(); i++){
        OptimizedCutInfo.at(i).Print();
      }
    }

    //==================
    //==== Sample Loop
    //==================

    double data_unweighted_yield(0.), data_weighted_yield(0.);
    double chargeflip_unweighted_yield(0.), chargeflip_weighted_yield(0.), chargeflip_weighted_yield_stat(0.);
    double fake_unweighted_yield(0.), fake_weighted_yield(0.), fake_weighted_yield_stat(0.);
    double prompt_unweighted_yield(0.), prompt_weighted_yield(0.);

    TH1D *hist_prompt_total = new TH1D("hist_prompt_total", "", 1, 0., 1.); // Use TH1D::Add, to use GetBinError
    TH1D *hist_prompt_total_up = new TH1D("hist_prompt_total_up", "", 1, 0., 1.); // Just fill content, and only use GetBinContent

    vector<double> signal_unweighted_yield, signal_weighted_yield, signal_weighted_yield_stat;
    bool SignalEffLow = false;
    for(unsigned int ii=0; ii<samples.size(); ii++){

      TString sample = samples.at(ii);

      TString                     filename = filename_prefix+"_SK"+     sample      +"_dilep_"+filename_suffix;
      if(sample=="data")          filename = filename_prefix+"_data_"+DataPD+"_"              +filename_suffix;
      if(sample=="chargeflip")    filename = filename_prefix+"_SKchargeflip_"+DataPD+"_dilep_"+filename_suffix;
      if(sample.Contains("fake")) filename = filename_prefix+"_SK"+sample+"_"+DataPD+"_dilep_"+filename_suffix;
      if(sample.Contains("HN"))   filename = filename_prefix+"_SK"      +sample           +"_"+filename_suffix;

      cutop m(filepath+filename, "Ntp_"+channel+"_"+treeskim);
      m.DoDebug = DoDebug;

      //==== Fill cutinfo
      vector<cutinfo> cis;
      CutRangeInfo.FillCurrentCutInfoVector(cis);
      for(unsigned int iii=0;iii<cis.size();iii++) m.SetCutVariablesToUse(cis.at(iii));

      //==== Run
      m.Loop();

      //==== Sum yield
      if(sample.Contains("HN")){
        signal_unweighted_yield.push_back( m.unweighted_yield );
        signal_weighted_yield.push_back( m.weighted_yield );
        signal_weighted_yield_stat.push_back( m.hist_for_error->GetBinError(1) );

        double eff_preselection = m.weighted_yield/signal_yield_preselection.at(ii);
        if(PrintYield) cout << "SignalEff@Preselection : " << sample << "\t" << eff_preselection << "\t" << m.unweighted_yield << endl;

        //==== If signal efficiency is lower than targer, finish the sample loop
        if(eff_preselection < MinEffPresel){
          SignalEffLow = true;
          break;
        }
      }
      else if(sample=="chargeflip"){
        chargeflip_unweighted_yield = m.unweighted_yield;
        chargeflip_weighted_yield = m.weighted_yield;

        chargeflip_weighted_yield_stat = m.hist_for_error->GetBinError(1);
        double cf_propagation = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        chargeflip_weighted_yield_stat = sqrt( chargeflip_weighted_yield_stat*chargeflip_weighted_yield_stat + cf_propagation*cf_propagation );
      }
      else if(sample.Contains("fake")){
        fake_unweighted_yield = m.unweighted_yield;
        fake_weighted_yield = m.weighted_yield;

        fake_weighted_yield_stat = m.hist_for_error->GetBinError(1);
        double fr_propagation = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        fake_weighted_yield_stat = sqrt( fake_weighted_yield_stat*fake_weighted_yield_stat + fr_propagation*fr_propagation );
      }
      else if(sample=="data"){
        data_unweighted_yield = m.unweighted_yield;
        data_weighted_yield = m.weighted_yield;
      }
      else{
        prompt_unweighted_yield += m.unweighted_yield;

        prompt_weighted_yield += m.weighted_yield * analysisInputs.MCNormSF[sample];
        hist_prompt_total->Add( m.hist_for_error );
        hist_prompt_total_up->Fill(0., m.weighted_yield * (analysisInputs.MCNormSF[sample]+analysisInputs.MCNormSF_uncert[sample]));
        
      }

      //==== Print this samples yield for Debugging
      if(PrintYield){
        if(sample=="data"){
          if(!ShowData) cout << sample << "\t" << "BLIND" << endl;
        }
        else{
          cout << sample << "\t" << m.weighted_yield << "\t" << m.hist_for_error->GetBinContent(1) << "\t" << m.hist_for_error->GetBinError(1) << "\t" << m.unweighted_yield << endl;
        }
      }

    } // END sample loop

    //==== If SignalEffLow, go to next CutInfo.
    //==== XXX DON'T FORGET TO RESET MEMORY XXX
    if(SignalEffLow){
      CutRangeInfo.Next();
      delete hist_prompt_total;
      delete hist_prompt_total_up;
      continue;
    }

    //==== Stat. + Syst.
    double chargeflip_weighted_yield_syst = chargeflip_weighted_yield * uncert_cf;
    double chargeflip_weighted_yield_err = sqrt( chargeflip_weighted_yield_stat*chargeflip_weighted_yield_stat + chargeflip_weighted_yield_syst*chargeflip_weighted_yield_syst );
    if(PrintYield){
      cout << "chargeflip_weighted_yield = " << chargeflip_weighted_yield << endl;
      cout << "  chargeflip_weighted_yield_stat = " << chargeflip_weighted_yield_stat << endl;
      cout << "  chargeflip_weighted_yield_syst = " << chargeflip_weighted_yield_syst << endl;
      cout << "  => chargeflip_weighted_yield_err = " << chargeflip_weighted_yield_err << endl;
    }

    double fake_weighted_yield_syst = fake_weighted_yield * uncert_fake;
    double fake_weighted_yield_err = sqrt( fake_weighted_yield_stat*fake_weighted_yield_stat + fake_weighted_yield_syst*fake_weighted_yield_syst );
    if(PrintYield){
      cout << "fake_weighted_yield = " << fake_weighted_yield << endl;
      cout << "  fake_weighted_yield_stat = " << fake_weighted_yield_stat << endl;
      cout << "  fake_weighted_yield_syst = " << fake_weighted_yield_syst << endl;
      cout << "  => fake_weighted_yield_err = " << fake_weighted_yield_err << endl;
    }

    double prompt_weighted_yield_stat = hist_prompt_total->GetBinError(1);
    double prompt_weighted_yield_syst_lumi = prompt_weighted_yield * uncert_lumi;
    double prompt_weighted_yield_syst_MCSF = hist_prompt_total_up->GetBinContent(1) - hist_prompt_total->GetBinContent(1);
    double prompt_weighted_yield_err = sqrt( prompt_weighted_yield_stat*prompt_weighted_yield_stat + prompt_weighted_yield_syst_lumi*prompt_weighted_yield_syst_lumi + prompt_weighted_yield_syst_MCSF*prompt_weighted_yield_syst_MCSF );
    if(PrintYield){
      cout << "prompt_weighted_yield = " << prompt_weighted_yield << endl;
      cout << "  prompt_weighted_yield_stat = " << prompt_weighted_yield_stat << endl;
      cout << "  prompt_weighted_yield_syst_lumi = " << prompt_weighted_yield_syst_lumi << endl;
      cout << "  prompt_weighted_yield_syst_MCSF = " << prompt_weighted_yield_syst_MCSF << endl;
      cout << "  => prompt_weighted_yield_err = " << prompt_weighted_yield_err << endl;
    }

    double total_bkg = prompt_weighted_yield+chargeflip_weighted_yield+fake_weighted_yield;
    double total_bkg_err_2 = chargeflip_weighted_yield_err*chargeflip_weighted_yield_err+fake_weighted_yield_err*fake_weighted_yield_err+prompt_weighted_yield_err*prompt_weighted_yield_err;

    delete hist_prompt_total;
    delete hist_prompt_total_up;

    //==== Signals
    bool ToUpdate = true;
    vector<double> sig_eff, punzis;
    for(unsigned int ii=0; ii<signals.size(); ii++){
      double eff_nocut = signal_weighted_yield.at(ii)/signal_yield_nocut.at(ii);
      double this_punzi = PunziFunction(eff_nocut, total_bkg, total_bkg_err_2);
      if(DoDebug) cout << signals.at(ii) << "\t" << signal_weighted_yield.at(ii) << "\t" << this_punzi << "\t" << signal_unweighted_yield.at(ii) << endl;

      sig_eff.push_back( eff_nocut );
      punzis.push_back( this_punzi );

      if(this_punzi < MaxPunzis.at(ii)){
        ToUpdate = false;
      }

    }

    if(ToUpdate){

      OptimizedCutInfo = CutRangeInfo.GetCurrentCutInfo();

      cout << endl;
      cout << "!!!!!!!!!!!!!!!!!" << endl;
      cout << "!!!! UPDATED !!!!" << endl;
      cout << "!!!!!!!!!!!!!!!!!" << endl;
      cout << endl;
      CutRangeInfo.PrintCurrent();
      cout << "CF" << "\t" << chargeflip_weighted_yield << " +- " << chargeflip_weighted_yield_err << endl;
      cout << "Fake" << "\t" << fake_weighted_yield << " +- " << fake_weighted_yield_err << endl;
      cout << "Prompt" << "\t" << prompt_weighted_yield << " +- " << prompt_weighted_yield_err << endl;
      cout << "=> total bkg = " << total_bkg << endl;
      cout << "Signal\tYield\tEfficiency\tEfficiency@Presel\tPunzi" << endl;
      for(unsigned int iii=0; iii<signals.size(); iii++){
        final_signal.at(iii) = signal_weighted_yield.at(iii);
        final_signal_eff.at(iii) = signal_weighted_yield.at(iii)/signal_yield_nocut.at(iii);
        final_signal_eff_preselection.at(iii) = signal_weighted_yield.at(iii)/signal_yield_preselection.at(iii);
        MaxPunzis.at(iii) = punzis.at(iii);
        cout << signals.at(iii) << "\t" << signal_weighted_yield.at(iii) << "\t" << signal_weighted_yield.at(iii)/signal_yield_nocut.at(iii) << "\t" << signal_weighted_yield.at(iii)/signal_yield_preselection.at(iii) << "\t" << punzis.at(iii) << endl;
      }
      cout << "=====================================================================" << endl << endl;
      final_cf = chargeflip_weighted_yield;
      final_cf_err = chargeflip_weighted_yield_err;
      final_fake = fake_weighted_yield;
      final_fake_err = fake_weighted_yield_err;
      final_prompt = prompt_weighted_yield;
      final_prompt_err = prompt_weighted_yield_err;

    }

    CutRangeInfo.Next();

  } //END CutRangeInfo loop


  cout << endl;
  cout << "##################" << endl;
  cout << "#### FINISHED ####" << endl;
  cout << "##################" << endl << endl;

  for(unsigned int i=0; i<OptimizedCutInfo.size(); i++){
    OptimizedCutInfo.at(i).Print();
  }
  cout << "CF" << "\t" << final_cf << " +- " << final_cf_err << endl;
  cout << "Fake" << "\t" << final_fake << " +- " << final_fake_err << endl;
  cout << "Prompt" << "\t" << final_prompt << " +- " << final_prompt_err << endl;
  cout << "=> total bkg = " << final_cf+final_fake+final_prompt << endl;
  cout << "Signal\tYield\tEfficiency\tEfficiency@Presel\tPunzi" << endl;
  for(unsigned int i=0; i<signals.size(); i++){
    cout << signals.at(i) << "\t" << final_signal.at(i) << "\t" << final_signal_eff.at(i) << "\t" << final_signal_eff_preselection.at(i) << "\t" << MaxPunzis.at(i) << endl;
  }

}













