import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1"]

masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

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
        if words[0]=="m_jj_jjWclosest":
          if words[1]==">":
            line = "m_jj_jjWclosest > 50 50 1\n"
          else:
            line = "m_jj_jjWclosest < 120 120 1\n"

        line = line.strip('\n')
        newout.write(line+'\n')

      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
