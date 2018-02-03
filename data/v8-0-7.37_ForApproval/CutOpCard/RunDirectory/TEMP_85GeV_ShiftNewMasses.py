import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses_empty = [85]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses_empty:
      filename = 'HN'+ch+"_"+str(mass)+".txt"

      filename_neighbor = 'HN'+ch+"_"+str(90)+".txt"
      lines = open(dirname+'/'+filename_neighbor).readlines()

      out = open(dirname+'/'+filename,'w')

      for line in lines:
        if "#" in line:
          continue

        words = line.split()
        value = float(words[2])
        shifted = value+(mass-90)

        Additional_shifted = 0

        if "m_SubLeadljj_jjWclosest" in line:
          
          if Bin=="Bin2":
            continue

          if ">" in line:
            line = 'm_SubLeadljj_jjWclosest > '+str(shifted-Additional_shifted)+' '+str(shifted-Additional_shifted)+' 1'
          if "<" in line:
            line = 'm_SubLeadljj_jjWclosest < '+str(shifted)+' '+str(shifted)+' 1'

        line = line.strip('\n')
        out.write(line+'\n')
