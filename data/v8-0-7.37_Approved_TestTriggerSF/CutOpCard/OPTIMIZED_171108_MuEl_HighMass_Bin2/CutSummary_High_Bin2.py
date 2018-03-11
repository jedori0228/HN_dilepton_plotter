import os

DoBin1 = False

masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

highermasses = [250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

varorder = [
"leadingLepton_Pt >",
"secondLepton_Pt >",

"m_jj_jjWclosest >",
"m_jj_jjWclosest <",

"m_lljj_jjWclosest >",

"ljj |>",
"ljj |<",

"MET2ST <",
]
names = [
"pt1 >\t",
"pt2 >\t",

"m(jj)\t",
"",

"m(lljj) >\t",

"m(ljj)\t",
"",

"MET2/ST <\t",
]

varsinboth = [
"m_jj_jjWclosest >",
"ljj |>"
]

print 'm(N) [GeV]\t',
for name in names:
  print name,
print ""

for mass in masses:
  lines = open('HNMuEl_'+str(mass)+'.txt').readlines()

  print str(mass)+'\t',
  counter = 0
  for var in varorder:

    if mass in highermasses:
      if "ljj >" in var:
        continue
      if "ljj <" in var:
        print "\t",
        continue

    for line in lines:
      words = line.split()
      this_var = words[0]+" "+words[1]
      if not (this_var == var):
        continue

      value = str(int(float(words[2])))

      if var in varsinboth:
        print value+" -",
      else:
        print value+'\t',

    if "secondLepton_Pt" in var:
      print "40 - 130\t-\t",
    if "ljj |<" in var:
      print "15\t",

    counter = counter+1


  logname = 'Cycles/log_HNMuEl_'+str(mass)+'.log'
  if not DoBin1:
    logname = 'Cycles/log_Bin2_HNMuEl_'+str(mass)+'.log'

  runlog = open(logname).readlines()
  bkgd = runlog[len(runlog)-2].split()[0]
  eff = runlog[len(runlog)-3].split()[2]
  print bkgd+'\t'+eff













