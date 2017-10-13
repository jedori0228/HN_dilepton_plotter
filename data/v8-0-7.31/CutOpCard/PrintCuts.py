import os

dirname = "OPTIMIZED_170920_ElEl_MCSF_applied_OPTIMIZEDCARD_OF_170904_second_quick"

channels = ["ElEl"]


masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for channel in channels:
  
  for mass in masses:

    filename = "HN"+channel+"_"+str(mass)+".txt"

    lines = open(dirname+"/"+filename).readlines()

    #print "#######################################################"
    #print channel+" "+str(mass)
    print str(mass)+'\t',
    for line in lines:
      words = line.split()

      print words[0]+'\t'+words[1]+' '+words[2]+'\t',

    print '\n',
