import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 

ToKeeps = [
      "_DiMuon_0jets_SS", # SS 0jet CR
      "_DiMuon_1jets_SS", # SS 1jet CR
      "_DiMuon_0jets_OnZ_SS", # SS-0jet+OnZ CR (CF)
      "_DiMuon_1jets_OnZ_SS", # SS-1jet+OnZ CR (CF)
      "_DiMuon_Inclusive1nlbjets_SS", # (TTBar Fake))
      "_DiMuon_Inclusive1nlbjets_METgt50_OffZ_OS", # (TTBar Prompt)

      "_DiElectron_0jets_SS", # SS 0jet CR
      "_DiElectron_1jets_SS", # SS 1jet CR
      "_DiElectron_0jets_OnZ_SS", # SS-0jet+OnZ CR (CF)
      "_DiElectron_1jets_OnZ_SS", # SS-1jet+OnZ CR (CF)
      "_DiElectron_Inclusive1nlbjets_SS", # (TTBar Fake))
      "_DiElectron_Inclusive1nlbjets_METgt50_OffZ_OS", # (TTBar Prompt)

      "_DiMuon_OnZ_OS", # OS OnZ CR (DY Prompt)
      "_DiMuon_0jets_OnZ_OS", # OS 0jet OnZ CR (DY Prompt)
      "_DiMuon_Inclusive1nlbjets_OS", # (TTBar Prompt)
      "_DiMuon_Inclusive1nlbjets_METgt50_OS", # (TTBar Prompt)

      "_DiElectron_OnZ_OS", # OS OnZ CR (DY Prompt)
      "_DiElectron_0jets_OnZ_OS", # OS 0jet OnZ CR (DY Prompt)
      "_DiElectron_1jets_OnZ_OS", # OS 1jet OnZ CR (DY+jet)
      "_DiElectron_Inclusive1nlbjets_OS", # (TTBar Prompt)
      "_DiElectron_Inclusive1nlbjets_METgt50_OS", # (TTBar Prompt)
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
  
