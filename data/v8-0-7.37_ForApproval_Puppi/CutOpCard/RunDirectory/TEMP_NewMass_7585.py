import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [75, 85]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses:

      copymass = 0
      if mass == 75:
        copymass = 80
      if mass == 85:
        copymass = 90

      filename_40GeV = 'HN'+ch+"_"+str(copymass)+".txt"
      cmd = 'cp '+dirname+'/'+filename_40GeV+' '+dirname+'/HN'+ch+"_"+str(mass)+".txt"
      print cmd
      os.system(cmd)
