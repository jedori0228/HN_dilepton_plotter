import os

#filenames=['SR_rebins.txt', 'SR_xaxis.txt', 'SR_yaxis.txt'] 
filenames=['CR_rebins.txt', 'CR_xaxis.txt', 'CR_yaxis.txt']
#filenames=['CR2_rebins.txt', 'CR2_xaxis.txt', 'CR2_yaxis.txt']

cust_rebin = 1
cust_xaxis_min = -999
cust_xaxis_max = 50


    #"Nfatjets",
    #"leadingFatJet_Pt", "leadingFatJet_Eta", "leadingFatJet_Mass", "leadingFatJet_Tau21",
    #"m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest",

var_last = "leadingFatJet_Tau21"
NewVars = ["m_Leadlfj_fjWclosest", "m_SubLeadlfj_fjWclosest", "m_llfj_fjWclosest"]

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

        if "rebins" in filename:
          newline = words[0]+'\t'+NewVar+'\t20\n'
        if "xaxis" in filename:
          newline = words[0]+'\t'+NewVar+'\t-999\t-999\n'
        if "yaxis" in filename:
          newline = words[0]+'\t'+NewVar+'\t1000\n'

        tempfile.write(newline)

  tempfile.close()
  os.system('mv test_'+filename+' '+filename)
