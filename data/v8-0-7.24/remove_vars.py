import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 

ToRemoves = ['HT_phi', 'ST_phi']

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:

    words = line.split()
    if words[1] not in ToRemoves:
      tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
