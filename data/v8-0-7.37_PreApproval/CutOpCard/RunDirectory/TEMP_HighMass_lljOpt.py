import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin2"]

masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for ch in channels:
  for Bin in Bins:
    dirname = 'Cards_'+ch+"_"+Bin

    for mass in masses:
      filename = 'HN'+ch+"_"+str(mass)+".txt"

      lines = open(dirname+'/'+filename).readlines()
      newout = open('temp_'+filename,'w')

      print dirname+'/'+filename
      print lines

      leftstart = mass-300
      rightstart = mass+300
      nbins = 60

      if leftstart<0:
        leftstart = mass-200
        nbins = 40
      if leftstart<0:
        leftstart = mass-150
        nbins = 30
      if leftstart<0:
        leftstart = mass-100
        nbins = 29
      if leftstart<0:
        leftstart = mass-50
        nbins = 10

      for line in lines:
        if "#" in line:
          continue

        if  "ljj" in line and mass > 200:
          if ">" in line:
            line = 'ljj |> '+str(leftstart)+' '+str(mass)+' 60'
          if "<" in line:
            line = 'ljj |< '+str(rightstart)+' '+str(mass)+' 60'

        if "m_SubLeadljj_jjWclosest" in line and mass <= 200:
          if ">" in line:
            line = 'm_SubLeadljj_jjWclosest > '+str(leftstart)+' '+str(mass)+' 60'
          if "<" in line:
            line = 'm_SubLeadljj_jjWclosest < '+str(rightstart)+' '+str(mass)+' 60'

        line = line.strip('\n')
        newout.write(line+'\n')

      os.system('mv temp_'+filename+' '+dirname+'/'+filename)
