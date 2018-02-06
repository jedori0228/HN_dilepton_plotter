import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [90]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses:
      filename = 'HN'+ch+"_"+str(mass)+".txt"

      lines = open(dirname+'/'+filename).readlines()
      newout = open('temp_'+filename,'w')

      for line in lines:
        words = line.split()
        if "#" in line:
          continue
        if words[0]=="secondLepton_Pt":
          if ch=="ElEl":
            line = 'secondLepton_Pt > 15.0 15.0 1'
          else:
            line = 'secondLepton_Pt > 10.0 10.0 1'

        line = line.strip('\n')
        newout.write(line+'\n')

      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
