import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 

ToKeeps = [

      ##==== DiMuon
      "_DiMuon_0jets_SS", ## SS 0jet CR
      "_DiMuon_1jets_SS", ## SS 1jet CR
      "_DiMuon_1jets_0nlbjets_SS",
      "_DiMuon_0nlbjets_SS",
      "_DiMuon_Inclusive1nlbjets_SS", ## SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_DiMuon_LowCR_SS",
      "_DiMuon_HighCR_SS",


      ##=== DiElectron
      "_DiElectron_0jets_SS", ## SS 0jet CR
      "_DiElectron_1jets_SS", ## SS 1jet CR
      "_DiElectron_0jets_OnZ_SS", ## SS 0jet+OnZ CR (CF)
      "_DiElectron_1jets_OnZ_SS", ## SS 1jet+OnZ CR (CF)
      "_DiElectron_Inclusive1nlbjets_SS", ## SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_DiElectron_0jets_OffZ_SS",
      "_DiElectron_1jets_OffZ_SS",
      "_DiElectron_LowCR_SS",
      "_DiElectron_HighCR_SS",
      "_DiElectron_1jets_0nlbjets_OffZ_SS",
      "_DiElectron_0nlbjets_OffZ_SS",

      ##==== EMu
      "_EMu_0jets_SS", ## SS 0jet CR
      "_EMu_1jets_SS", ## SS 1jet CR
      "_EMu_Inclusive1nlbjets_SS", ## SS bjet>=1 (Non-prompt) : now, preselection doesn't have bjetveto.. we can't use this as CR..
      "_EMu_LowCR_SS",
      "_EMu_HighCR_SS",
      "_EMu_1jets_0nlbjets_SS",
      "_EMu_0nlbjets_SS",

      ## OS

      "_DiMuon_0jets_OnZ_OS",
      "_DiElectron_0jets_OnZ_OS",

]

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  ## loop over ToKeeps first, to keep order
  for ToKeep in ToKeeps:

    for line in lines:
      words = line.split()
      if ToKeep==words[0]:
        tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
