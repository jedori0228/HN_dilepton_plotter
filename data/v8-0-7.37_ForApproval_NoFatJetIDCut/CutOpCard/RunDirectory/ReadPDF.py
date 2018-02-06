import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

## S-ch ##
masses = [50, 100, 200, 500, 1100]
for ch in channels:

  for Bin in Bins:

    for mass in masses:

      filename = "HN"+ch+"_"+str(mass)

      lines = open("Outputs_PDF/CyclesForPDF_"+ch+"_"+Bin+"_"+filename+".txt").readlines()
      print ch+' '+Bin+' '+str(mass)+' '+lines[len(lines)-1].strip('\n')


## T-ch ##
masses = [300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]
out = open('PDFSyst_Tch_FinalSelection.txt','w')
for ch in channels:

  for Bin in Bins:

    for mass in masses:

      filename = "HN"+ch+"_"+str(mass)

      lines = open('Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'_VBFOnly.log').readlines()

      pdf = 0.
      for line in lines:
        if "PDF" in line:
          words = line.split()
          pdf = float(words[5])
      pdf = 0.01*pdf

      print ch+' '+Bin+' '+str(mass)+' '+str(pdf)
      out.write(ch+' '+Bin+' '+str(mass)+' '+str(pdf)+'\n')
