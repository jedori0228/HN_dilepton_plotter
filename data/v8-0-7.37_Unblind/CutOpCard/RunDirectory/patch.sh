#!/bin/bash
python CopyCards.py
python TEMP_AddNJet_JetPt.py
python TEMP_HighMass_RemoveSecondPt.py
python TEMP_LowMass_mll.py
python TEMP_MiddleMass_Change_mljj.py
python TEMP_MiddleMass2_Change_mjj.py
python TEMP_LowMass_2030.py ## last
cd Outputs_Optimization
python makecard.py
cd ../
#python TEMP_HighMass_SR2_MakeThemOverlap.py
