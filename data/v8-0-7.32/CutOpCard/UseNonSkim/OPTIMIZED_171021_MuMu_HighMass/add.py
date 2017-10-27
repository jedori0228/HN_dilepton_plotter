import os

channel = "MuMu"
DoBin1 = True

#masses = [40, 50, 60, 70, 80]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for mass in masses:
  out = open('HN'+channel+'_'+str(mass)+'.txt','a')
  out.write('\n')
  if mass <= 80:
    if DoBin1:
      out.write('Njets >= 2 2 1\n')
      out.write('Nfatjets == 0 0 1\n')
      out.write('Nbjets_nolepveto == 0 0 1\n')
    else:
      out.write('Njets == 1 1 1\n')
      out.write('Nfatjets == 0 0 1\n')
      out.write('Nbjets_nolepveto == 0 0 1\n')

  else:
    if DoBin1:
      out.write('Njets >= 2 2 1\n')
      out.write('Nfatjets == 0 0 1\n')
      out.write('Nbjets_nolepveto == 0 0 1\n')
    else:
      out.write('Nfatjets >= 1 1 1\n')
      out.write('Nbjets_nolepveto == 0 0 1\n')

  out.close()



