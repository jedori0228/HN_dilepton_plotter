import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [300, 600, 800, 1000, 1200, 1500]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses:
      sch_filename = 'HN'+ch+"_"+str(mass)+".txt"
      filename = 'HN'+ch+"_"+str(mass)+"_VBFADDED.txt"

      lines = open(dirname+'/'+sch_filename).readlines()
      newout = open('temp_'+filename,'w')

      for line in lines:
        if "#" in line:
          continue

        if  "secondLepton_Pt" in line:
          if mass >= 600:
            continue

        line = line.strip('\n')
        newout.write(line+'\n')


      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
