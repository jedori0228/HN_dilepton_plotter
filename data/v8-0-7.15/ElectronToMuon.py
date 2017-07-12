import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:

    tempfile.write(line)
    savethem.append( line.replace('Electron','Muon') )

  for line in savethem:
    tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
