import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1"]

masses = [20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses:
      filename = 'HN'+ch+"_"+str(mass)+".txt"

      lines = open(dirname+'/'+filename).readlines()
      newout = open('temp_'+filename,'w')

      for line in lines:
        if "#" in line:
          continue

        line = line.strip('\n')
        newout.write(line+'\n')

      newout.write('Njets < 4 4 1\n')

      if mass >= 90:
        newout.write('leadingJet_lljjWclosest_pt > 25 25 1\n')
        if mass <= 200:
          newout.write('DeltaRSubLeadl_jjWclosest < 3.1 3.1 1')

      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
