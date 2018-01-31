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
        shifted = value+(mass-1500)

        if ch=="MuEl" and Bin=="Bin2":
          if mass==1700:
            if  "ljj" in line:
              
              if ">" in line and Bin=="Bin2":
                line = 'ljj |> 1400 1400 1'
              if "<" in line:
                line = 'ljj |< 1800 1800 1'
          if mass==2000:
            if  "ljj" in line:
           
              if ">" in line and Bin=="Bin2":
                line = 'ljj |> 1800 1800 1'
              if "<" in line:
                line = 'ljj |< 2300 2300 1'


        else:

          if  "ljj" in line:
            
            if ">" in line and Bin=="Bin2":
              line = 'ljj |> '+str(shifted)+' '+str(shifted)+' 1'
            if "<" in line:
              line = 'ljj |< '+str(shifted)+' '+str(shifted)+' 1'

        line = line.strip('\n')
        out.write(line+'\n')
