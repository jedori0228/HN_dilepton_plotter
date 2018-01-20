import os

def GetMassVarString(mass):
  if mass <= 200:
    return 'm_SubLeadljj_jjWclosest'
  else:
    return 'ljj'

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin2"]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for ch in channels:

  print '##### '+ch+' #####'

  for Bin in Bins:

    dirname = 'Cards_'+ch+'_'+Bin

    mins = []
    maxs = []

    for mass in masses:

      lines = open(dirname+'/HN'+ch+'_'+str(mass)+'.txt')

      mllvarname = GetMassVarString(mass)

      minval = 0.
      maxval = 0.

      for line in lines:
        words = line.split()
        if words[0]==mllvarname:
          if ">" in words[1]:
            minval = words[2]
          if "<" in words[1]:
            maxval = words[2]

      mins.append( float(minval) )
      maxs.append( float(maxval) )

      #print ch+'\t'+str(mass)+'\t'+str(minval)+'\t'+str(maxval)

    for a in range(0,len(masses)-1):
      #print str(masses[a])+'\t'+str(masses[a+1])
      if maxs[a] < mins[a+1]:
        print 'Below is not overlapped:'
        print str(masses[a])+'\t'+str(mins[a])+'\t'+str(maxs[a])
        print str(masses[a+1])+'\t'+str(mins[a+1])+'\t'+str(maxs[a+1])
        print 'Changing it to'
        print str(masses[a])+'\t'+str(mins[a])+'\t'+str(mins[a+1])
        print str(masses[a+1])+'\t'+str(maxs[a])+'\t'+str(maxs[a+1])
        print ''


        lines1 = open(dirname+'/HN'+ch+'_'+str(masses[a])+'.txt').readlines()
        newout1 = open(dirname+'/HN'+ch+'_'+str(masses[a])+'.txt','w')
        for line in lines1:
          mllvarname = GetMassVarString(masses[a])
          words = line.split()

          line = line.strip('\n')
          if words[0]==mllvarname:
            if "<" in words[1]:
              print line
              print '->'
              line = words[0]+'\t'+words[1]+'\t'+str(mins[a+1])+'\t'+str(mins[a+1])+'\t1'
              print line

          newout1.write(line+'\n')
        newout1.close()

        lines2 = open(dirname+'/HN'+ch+'_'+str(masses[a+1])+'.txt').readlines()
        newout2 = open(dirname+'/HN'+ch+'_'+str(masses[a+1])+'.txt','w')
        for line in lines2:
          mllvarname = GetMassVarString(masses[a+1])
          words = line.split()

          line = line.strip('\n')
          if words[0]==mllvarname:
            if ">" in words[1]:
              print line
              print '->'
              line = words[0]+'\t'+words[1]+'\t'+str(maxs[a])+'\t'+str(maxs[a])+'\t1'
              print line

          newout2.write(line+'\n')
        newout2.close()

      print '#############################\n'






