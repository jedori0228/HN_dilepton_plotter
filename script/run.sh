#!/bin/bash
whichRun=$1

if [ $whichRun = "SR" ]; then
  if [ -z "$2" ]; then
    root -l -b -q "src/Draw_SR.C(true,0)"
  else
    applySF=$2
    root -l -b -q "src/Draw_SR.C($applySF,0)"
  fi
fi

if [ $whichRun = "CR" ]; then
  if [ -z "$2" ]; then
    root -l -b -q "src/Draw_CR.C(true,0)"
    root -l -b -q "src/Draw_CR.C(true,1)"
    root -l -b -q "src/Draw_CR.C(true,2)"
  else
    applySF=$2
    root -l -b -q "src/Draw_CR.C($applySF,0)"
    root -l -b -q "src/Draw_CR.C($applySF,1)"
    root -l -b -q "src/Draw_CR.C($applySF,2)"
  fi
fi

if [ $whichRun = "FRMu" ]; then
  dXYSig=$2
  RelIso=$3

  if [ $dXYSig = "all" ]; then
    for i in 3.0 4.0 5.0
    do
      for j in 0.2 0.3 0.4 0.6 0.8 1.0
      do
        root -l -b -q "src/fake_calculator_Mu_dilep.C($i, $j)"
      done
    done
  else
    root -l -b -q "src/fake_calculator_Mu_dilep.C($dXYSig, $RelIso)" 
  fi
fi

if [ $whichRun = "FREl" ]; then
  dXYSig=$2
  RelIso=$3

  if [ $dXYSig = "all" ]; then
    for i in 4.0 4.5 5.0
    do
      for j in 0.2 0.3 0.4 0.6 0.8 1.0
      do
        root -l -b -q "src/fake_calculator_El_dilep.C($i, $j)"
      done
    done
  else
    root -l -b -q "src/fake_calculator_El_dilep.C($dXYSig, $RelIso)"
  fi
fi

#NLimit syst_UpDowns(int sig_mass, bool printnumber=true, bool forlatex=false, bool inclusive=false, bool fillNlimit=false){
if [ $whichRun = "syst" ]; then
  channel=$2
  if [ $channel = "mme" ]; then
    echo "Running MuMuE"
    for mass in 5 10 20 30 40 50 60 70 90 100 150 200 300 400 500 700 1000
    do
      root -l -b -q "src/syst_UpDowns_MuMuE.C($mass,true, true, false, false)" &> $PLOTTER_WORKING_DIR/tmp.txt
      python script/syst_latex_output_cleanup.py $PLOTTER_WORKING_DIR/tmp.txt
    done
  fi
  if [ $channel = "mmm" ]; then
    echo "Running MuMuMu"
    for mass in 5 10 20 30 40 50 60 70
    do
      root -l -b -q "src/syst_UpDowns_MuMuMu.C($mass,true, true, false, false)" &> $PLOTTER_WORKING_DIR/tmp.txt
      python script/syst_latex_output_cleanup.py $PLOTTER_WORKING_DIR/tmp.txt
    done

    for mass in 90 100 150 200 300 400 500 700 1000
    do
      root -l -b -q "src/syst_UpDowns_MuMuMu.C($mass,true, true, false, false)" &> $PLOTTER_WORKING_DIR/tmp.txt
      python script/syst_latex_output_cleanup.py $PLOTTER_WORKING_DIR/tmp.txt
    done
  fi
fi

if [ $whichRun = "MCSF" ]; then
  root -l -b -q "src/MCNormalizationSF.C(true)"
  root -l -b -q "src/MCNormalizationSF.C(false)"
fi

if [ $whichRun = "cut" ]; then
  root -l -b -q script/CutStudy_bjet.C
  root -l -b -q script/CutStudy_mlll.C
  root -l -b -q script/CutStudy_mll_os.C
  root -l -b -q script/CutStudy_mz.C
fi
