#!/bin/bash

WhatToRun=0

if [ $WhatToRun = 0 ]; then
  outputdir=DiElectron
  mkdir -p $PLOTTER_WORKING_DIR/rootfiles/$CATANVERSION/FRCalculator_El_dxysig_DILEP/$outputdir
  root -l -b -q "script/Separate_ElFR_rootfile_data.C(\"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKDY_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKQCD_em_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKsingletop_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKTTJets_aMC_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKVGamma_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKVV_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKWJets_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKHNEmEm_100_cat_v8-0-7.root\", \"\", \"$outputdir\", 0)"
fi

if [ $WhatToRun = 1 ]; then
  outputdir=NoBias
  mkdir -p $PLOTTER_WORKING_DIR/rootfiles/$CATANVERSION/FRCalculator_El_dxysig_DILEP/$outputdir
  root -l -b -q "script/Separate_ElFR_rootfile_data.C(\"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKDY_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKQCD_em_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKsingletop_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKTTJets_aMC_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKVGamma_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKVV_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKWJets_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKHNEmEm_100_cat_v8-0-7.root\", \"\", \"$outputdir\", 1)"
fi

if [ $WhatToRun = 2 ]; then
  inputdir=HalfSample
  outputdir=HalfSample/DiMuonTrkVVL
  mkdir -p $PLOTTER_WORKING_DIR/rootfiles/$CATANVERSION/FRCalculator_El_dxysig_DILEP/$outputdir
  root -l -b -q "script/Separate_ElFR_rootfile_data.C(\"$inputdir\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKDY_cat_v8-0-7.root\", \"$inputdir\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKsingletop_cat_v8-0-7.root\", \"$inputdir\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKTTJets_aMC_cat_v8-0-7.root\", \"$inputdir\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKVGamma_cat_v8-0-7.root\", \"$inputdir\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKVV_cat_v8-0-7.root\", \"$inputdir\", \"$outputdir\", 0)"
  root -l -b -q "script/Separate_ElFR_rootfile.C(\"FRCalculator_El_dxysig_DILEP_SKWJets_cat_v8-0-7.root\", \"$inputdir\", \"$outputdir\", 0)"
fi
