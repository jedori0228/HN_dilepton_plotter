import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [90, 100, 125, 150, 200]

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
        if words[0]=="ljj":
          line = line.replace('ljj', 'm_SubLeadljj_jjWclosest')
          line = line.replace('|','')

        line = line.strip('\n')
        newout.write(line+'\n')

      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
