import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40, 50, 60, 70, 80]

OldDirName = "SecondPt15"
NewDirName = "SecondPt15_WithForwardJet"

os.system('mkdir -p '+NewDirName)

for mass in masses:
  filename = 'HNMuMu_'+str(mass)+'.txt'
  lines = open(OldDirName+"/"+filename).readlines()

  newfile = open(NewDirName+"/"+filename,'w')

  for line in lines:
    newfile.write(line)
  #newfile.write('\n')
  newfile.write('Nfwdjets >= 1 1 1\n')
  newfile.close()
