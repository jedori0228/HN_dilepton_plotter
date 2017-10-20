import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40, 50, 60, 70, 80]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

channel = "MuMu"

FirstRun = False

for mass in masses:

  varlist = [ ]
  mins = []
  maxs = []
  nbins = []
  chosen = []

  lines_chosen = open('HN'+channel+'_'+str(mass)+'.txt').readlines()
  lines_scan = open('../../HN'+channel+'_'+str(mass)+'.txt').readlines()

  punzi = ""
  bkgd = ""
  sigeff = ""
  totalit = 1

  for line in lines_scan:
    words = line.split()

    varlist.append(words[0]+' '+words[1])
    mins.append(words[2])
    maxs.append(words[3])
    nbins.append(words[4])

    totalit = totalit*(int(words[4])+1)

    for cline in lines_chosen:
      cwords = cline.split()

      if "punzi" in cwords[0]:
        punzi = cwords[1]
        continue
      if "bkgd" in cwords[0]:
        bkgd = cwords[1]
      if "sigeff" in cwords[0]:
        sigeff = cwords[1]

      if words[0]+' '+words[1] == cwords[0]+' '+cwords[1]:
        chosen.append(cwords[2])


  if FirstRun:
    print "######################\t\t\tSigEff\t"+sigeff
    print "#### "+str(mass)+" ####\t\t\tBkgd\t"+bkgd
    print "######################\t\t\tPunzi\t"+punzi
  else:
    print "\t\tSigEff\t"+sigeff
    print "\t\tBkgd\t"+bkgd
    print "\t\tPunzi\t"+punzi

  for a in range(0,len(varlist)):

    dx = (float(maxs[a])-float(mins[a]))/float(nbins[a])
    dx = abs(dx)

    nbin = int(nbins[a])

    if FirstRun:
      print varlist[a]+"\t"+mins[a]+"\t"+maxs[a]+"\t"+str(nbin)+"\t"+chosen[a]
    else:
      print                 mins[a]+"\t"+maxs[a]+"\t"+str(nbin)+"\t"+chosen[a]

  print "\t\t\t"+str(totalit)

