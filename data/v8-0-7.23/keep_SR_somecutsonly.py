import os

filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 

ToKeeps = [

      "_DiElectron_Preselection_SS",

]

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  ## loop over ToKeeps first, to keep order
  for ToKeep in ToKeeps:

    for line in lines:
      words = line.split()
      if ToKeep==words[0]:
        tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
