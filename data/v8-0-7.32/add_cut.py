import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames = ['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 
#filenames = ['CR2_rebins.txt', 'CR2_xaxis.txt', 'CR2_yaxis.txt']

From = "_EMu_LowCR_SS"
Tos   = [
      "_DiMuon_WpWp_CR_SS",
      "_DiElectron_WpWp_CR_SS",
      "_EMu_WpWp_CR_SS",
]

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:
    if From in line:
      savethem.append(line)
    tempfile.write(line)

  for To in Tos:
    for line in savethem:
      line = line.replace(From,To)
      tempfile.write(line)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
