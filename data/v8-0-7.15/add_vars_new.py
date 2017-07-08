import os

filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
#filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt']

cust_rebin = 1
cust_xaxis_min = 0
cust_xaxis_max = 6

var_last = 'Nvtx'
NewVars = ['DeltaRl1l2']

for filename in filenames:

  tempfile = open('test_'+filename,'w')

  lines = open(filename).readlines()

  savethem=[]

  for line in lines:

    tempfile.write(line)
    words = line.split()
    if words[1] == var_last:

      for NewVar in NewVars:
        newline = line.replace(var_last, NewVar)

        if "xaxis" in filename:
          newline = words[0]+'\t'+NewVar+'\t0\t50\n'

        tempfile.write(newline)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
