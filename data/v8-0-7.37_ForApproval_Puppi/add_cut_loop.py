import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames = ['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 
#filenames = ['CR2_rebins.txt', 'CR2_xaxis.txt', 'CR2_yaxis.txt']

regions = [
      "_DiElectron_0jets_SS",
      "_DiElectron_1jets_SS",
      "_DiElectron_0jets_OnZ_SS",
      "_DiElectron_1jets_OnZ_SS",
      "_DiElectron_Inclusive1nlbjets_SS",
      "_DiElectron_Inclusive1nlbjets_OffZ_SS",
      "_DiElectron_0jets_OffZ_SS",
      "_DiElectron_1jets_OffZ_SS",
      "_DiElectron_LowCR_SS",
      "_DiElectron_LowCR_TwoJet_NoFatJet_SS",
      "_DiElectron_LowCR_OneJet_NoFatJet_SS",
      "_DiElectron_HighCR_SS",
      "_DiElectron_HighCR_TwoJet_NoFatJet_SS",
      "_DiElectron_HighCR_OneFatJet_SS",
      "_DiElectron_1jets_0nlbjets_OffZ_SS",
      "_DiElectron_1jets_0nlbjets_mllge110_OffZ_SS",
      "_DiElectron_0nlbjets_OffZ_SS",
      "_DiElectron_0jets_0nlbjets_dRllge2p5_OffZ_SS",
      "_DiElectron_WpWp_CR_SS",
      "_DiElectron_OnZ_SS",
]


for From in regions:

  Tos = []
  Tos.append( From.replace("DiElectron","DiLepton")  )

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
  
