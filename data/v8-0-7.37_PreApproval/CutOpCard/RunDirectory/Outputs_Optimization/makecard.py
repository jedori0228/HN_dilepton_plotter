import os

channels = ["MuMu", "ElEl", "MuEl"]

masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
carddir = '/data8/Users/jskim/HN_dilepton_plotter/data/v8-0-7.37_PreApproval/CutOpCard/RunDirectory/'

for ch in channels:
  for mass in masses:
    lines = open(ch+'_Bin2/HN'+ch+'_'+str(mass)+'.log').readlines()

    out = open(carddir+'/Cards_'+ch+'_Bin2/HN'+ch+'_'+str(mass)+'.txt','w')

    index_finished = 0
    for a in range(0,len(lines)):
      b = len(lines)-1-a
      if "FINISHED" in lines[b]:
        index_finished = b
        break

    for a in range(b,len(lines)):
      if "CF" in lines[a]:
        break
      if "CutInfo" in lines[a]:
        line = lines[a]
        line = line.strip('\n')
        line = line.replace('[CutInfo::PrintCutInfo] ','')
        words = line.split()
        value = str(words[2])

        out.write(line+' '+value+' 1\n')

    out.close()
