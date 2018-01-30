import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [1700, 2000]

masses_empty = [1700, 2000]
for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses_empty:
      filename = 'HN'+ch+"_"+str(mass)+".txt"

      filename_neighbor = 'HN'+ch+"_"+str(1500)+".txt"
      lines = open(dirname+'/'+filename_neighbor).readlines()

      out = open(dirname+'/'+filename,'w')

      for line in lines:
        if "#" in line:
          continue

        words = line.split()
        value = float(words[2])

        if  "ljj" in line:
          
          if ">" in line and Bin=="Bin2":
            line = 'ljj |> '+str(value+(mass-1500))+' '+str(value+(mass-1500))+' 1'
          if "<" in line:
            line = 'ljj |< '+str(value+(mass-1500))+' '+str(value+(mass-1500))+' 1'

        line = line.strip('\n')
        out.write(line+'\n')
