import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [50, 100, 200, 500, 1100]

for ch in channels:

  for Bin in Bins:

    for mass in masses:

      filename = "HN"+ch+"_"+str(mass)

      lines = open("Outputs_PDF/CyclesForPDF_"+ch+"_"+Bin+"_"+filename+".txt").readlines()
      print ch+' '+Bin+' '+str(mass)+' '+lines[len(lines)-1].strip('\n')
