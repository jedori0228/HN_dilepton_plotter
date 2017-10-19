import os

filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
#filenames = ['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 
#filenames = ['CR2_rebins.txt', 'CR2_xaxis.txt', 'CR2_yaxis.txt']

From = "_DiMuon_Low_SS"
Tos   = [

      #//==== DiMuon
      #"_DiMuon_Preselection_SS", // nobjet, jet>=2;
      #"_DiMuon_Low_SS",
      #"_DiMuon_Low_TwoJet_NoFatjet_SS",
      #"_DiMuon_Low_OneJet_SS",
      #"_DiMuon_High_SS",
      #"_DiMuon_High_TwoJet_NoFatJet_SS",
      #"_DiMuon_High_OneFatJet_SS",
      #"_DiMuon_Preselection_secondptge20_SS",

      #//==== DiElectron
      #"_DiElectron_Preselection_SS", // OffZ, nobjet, jet>=2;
      #"_DiElectron_Low_SS",
      "_DiElectron_Low_TwoJet_NoFatjet_SS",
      "_DiElectron_Low_OneJet_SS",
      #"_DiElectron_High_SS",
      #"_DiElectron_High_TwoJet_NoFatJet_SS",
      #"_DiElectron_High_OneFatJet_SS",

      #//==== EMu
      #"_EMu_Preselection_SS", // nobjet, jet>=2;
      #"_EMu_Low_SS",
      "_EMu_Low_TwoJet_NoFatjet_SS",
      "_EMu_Low_OneJet_SS",
      #"_EMu_High_SS",
      #"_EMu_High_TwoJet_NoFatJet_SS",
      #"_EMu_High_OneFatJet_SS",
      #"_EMu_Preselection_ElectronSubLead_SS",
      #"_EMu_Preselection_MuonSubLead_SS",

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
  
