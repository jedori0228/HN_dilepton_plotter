import os

filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
#filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt'] 

From = 'm_ll'
Tos = ['m_jj', 'm_lljj', 'm_Leadljj', 'm_SubLeadljj']

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:

    tempfile.write(line)
    if From in line:
      for To in Tos:
        addthis = line.replace(From,To)
        tempfile.write(addthis)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
  
