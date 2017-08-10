import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 

From = "_DiElectron_Inclusive1nlbjets_SS"
Tos   = [
      ## DiMuon
      #"_DiMuon_0jets_SS", ## SS 0jet CR
      #"_DiMuon_1jets_SS", ## SS 1jet CR
      "_DiMuon_Inclusive1nlbjets_SS", ## SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      ##=== DiElectron
      #"_DiElectron_0jets_SS", ## SS 0jet CR
      #"_DiElectron_1jets_SS", ## SS 1jet CR
      #"_DiElectron_0jets_OnZ_SS", ## SS 0jet+OnZ CR (CF)
      #"_DiElectron_1jets_OnZ_SS", ## SS 1jet+OnZ CR (CF)
      #"_DiElectron_Inclusive1nlbjets_SS", ## SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      #"_DiElectron_0jets_OffZ_SS",
      #"_DiElectron_1jets_OffZ_SS",
      ## EMu
      #"_EMu_0jets_SS", ## SS 0jet CR
      #"_EMu_1jets_SS", ## SS 1jet CR
      "_EMu_Inclusive1nlbjets_SS", ## SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
]

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:
    if From in line:
      savethem.append(line)
    tempfile.write(line)

  for To in Tos:
    for line in savethem:
      line = line.replace(From,To)
      tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
