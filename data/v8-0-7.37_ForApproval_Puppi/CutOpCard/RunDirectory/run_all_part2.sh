## Combine PDF systematic in PDFSyst_SandT_Combined.txt##
python CombinePDFSyst.py
## Remake cycle ##
python MakeCycleForMixingLimitVBF.py &> run_MixingLimitVBF.sh
sleep 30
source run_MixingLimitVBF.sh
