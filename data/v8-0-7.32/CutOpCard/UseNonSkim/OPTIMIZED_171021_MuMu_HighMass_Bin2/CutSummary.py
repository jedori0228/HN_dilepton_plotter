import os

DoBin1 = False

masses = [40, 50, 60, 70, 80]

varorder = [
"leadingLepton_Pt <",

"secondLepton_Pt >",
"secondLepton_Pt <",

"m_lljj_lljjWclosest <",
"m_Leadljj_lljjWclosest <",
"m_SubLeadljj_lljjWclosest <",

"m_ll >",
"m_ll <",

"PFMET <",
]
names = [
"pt1 <\t",
"pt2\t",
"",
"m(lljj) <\t",
"m(l1jj) <\t",
"m(l2jj) <\t",
"m(ll)\t",
"",
"MET <\t",
]

print 'm(N) [GeV]\t',
for name in names:
  print name,
print "Bkgd\tSignal Efficiency"

for mass in masses:
  lines = open('HNMuMu_'+str(mass)+'.txt').readlines()

  print str(mass)+'\t',
  counter = 0
  for var in varorder:
    for line in lines:
      words = line.split()
      this_var = words[0]+" "+words[1]
      if not (this_var == var):
        continue

      value = str(int(float(words[2])))

      if var=="secondLepton_Pt >" or var=="m_ll >":
        print value+" -",
      else:
        print value+'\t',

    counter = counter+1

  logname = 'Cycles/log_HNMuMu_'+str(mass)+'.log'
  if not DoBin1:
    logname = 'Cycles/log_Bin2_HNMuMu_'+str(mass)+'.log'

  runlog = open(logname).readlines()
  bkgd = runlog[len(runlog)-2].split()[0]
  eff = runlog[len(runlog)-3].split()[2]
  print bkgd+'\t'+eff

















