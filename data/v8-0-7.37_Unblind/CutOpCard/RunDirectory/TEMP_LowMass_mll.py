import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [20, 30, 40, 50, 60, 70, 80]

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

        if mass == 80:
          if Bin == "Bin1":
            if words[0] == "m_ll" and "<" in words[1]:
              line = "m_ll < 100 100 1\n"
          if Bin == "Bin2":
            if words[0] == "m_ll" and "<" in words[1]:
              line = "m_ll < 80 80 1\n"

        if mass == 70:
          if words[0] == "m_ll" and "<" in words[1]:
            line = "m_ll < 75 75 1\n"

        line = line.strip('\n')
        newout.write(line+'\n')

      newout.write('DeltaRl1l2 < 3.2 3.2 1\n')


      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
