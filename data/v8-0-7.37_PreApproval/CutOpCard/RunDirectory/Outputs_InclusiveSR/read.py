import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]
LH = ["Low", "High"]

for ch in channels:
  for lh in LH:
    for Bin in Bins:

      lines = open('CyclesForInclusiveSR_'+ch+'_'+Bin+'_'+lh+'.txt').readlines()

      print ""
      print "###################"
      print ch+'_'+Bin+'_'+lh
      print "###################\n"

      for a in range(0,len(lines)):
        if "Sources" in lines[a]:

          for b in range(a+1, len(lines)):

            line = lines[b]

            #line = line.replace('   ',' ')
            #line = line.replace('  ',' ')
            #line = line.replace(' ','\t')

            print line,

            if "- CF" in lines[b]:
              break

          break

