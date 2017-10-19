import os

#masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
#masses = [90, 100, 125, 150, 200]
masses = [250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

chosen_for_each_mass = []
bkgds = []
sigeffs = []

GetVarlist = False

varlist = []
if GetVarlist:
  template = "250"
  lines_chosen = open('HNMuMu_'+template+'.txt').readlines()
  for line in lines_chosen:
    words = line.split()
    if "#" in words[0]:
      continue
    varlist.append(words[0]+' '+words[1])
  print varlist
  import sys
  sys.exit()

if 90 in masses:
  varlist = ['leadingLepton_Pt >', 'secondLepton_Pt >', 'm_jj_jjWclosest >', 'm_jj_jjWclosest <', 'm_lljj_jjWclosest >', 'm_SubLeadljj_jjWclosest >', 'm_SubLeadljj_jjWclosest <', 'MET2ST <']
elif 250 in masses:
  varlist = ['leadingLepton_Pt >', 'secondLepton_Pt >', 'm_jj_jjWclosest >', 'm_jj_jjWclosest <', 'm_lljj_jjWclosest >', 'MET2ST <']

for mass in masses:

  chosen = []

  lines_chosen = open('HNMuMu_'+str(mass)+'.txt').readlines()

  punzi = ""
  bkgd = ""
  sigeff = ""

  for var in varlist:
    for cline in lines_chosen:
      cwords = cline.split()

      if "punzi" in cwords[0]:
        punzi = cwords[1]
        continue
      if "bkgd" in cwords[0]:
        bkgd = cwords[1]
      if "sigeff" in cwords[0]:
        sigeff = cwords[1]

      if var == cwords[0]+' '+cwords[1]:
        chosen.append(cwords[2])

  chosen_for_each_mass.append(chosen)
  bkgds.append(bkgd)

  sigeff = str( float(sigeff)*100. )
  sigeffs.append(sigeff)

## rename valist ##
BranchName = ["secondLepton_Pt", "m_lljj_lljjWclosest", "m_SubLeadljj_lljjWclosest", "m_Leadljj_lljjWclosest", "leadingLepton_Pt", "PFMET", "m_lljj_jjWclosest", "m_jj_jjWclosest", "m_SubLeadljj_jjWclosest", "MET2ST"]
Alias      = ["pt2",             "m(lljj)",             "m(l2jj)",                   "m(l1jj)",                "pt1",              "MET",   "m(lljj)",           "m(jj)",           "m(l2jj)",                 "MET2/ST"]

print "mass\t",
for a in range(0,len(varlist)):
  for b in range(0,len(BranchName)):
    if BranchName[b] in varlist[a]:
      varlist[a] = varlist[a].replace(BranchName[b], Alias[b])
  print varlist[a]+'\t',
print "Bkgd\tSig. Eff. [%]"

for a in range(0,len(masses)):
  print str(masses[a])+'\t',
  chosen = chosen_for_each_mass[a]
  for value in chosen:
    print value+'\t',
  print bkgds[a]+'\t'+sigeffs[a]











