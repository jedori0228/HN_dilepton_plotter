import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [20, 30]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses:
      filename_40GeV = 'HN'+ch+"_"+str(40)+".txt"
      cmd = 'cp '+dirname+'/'+filename_40GeV+' '+dirname+'/HN'+ch+"_"+str(mass)+".txt"
      #print cmd
      os.system(cmd)
