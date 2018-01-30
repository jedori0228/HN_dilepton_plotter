#!/bin/bash
## Run T-ch only first ##
source run_MixingLimitVBFOnly.sh
sleep 30
## Then write T-ch PDF in PDFSyst_Tch_FinalSelection.txt"
python ReadPDF.py
## Then Run S-ch only ##
source run_MixingLimit.sh
