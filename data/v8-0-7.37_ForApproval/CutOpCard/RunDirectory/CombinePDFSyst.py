import os,math

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]
out = open('PDFSyst_SandT_Combined.txt','w')
for ch in channels:

  for Bin in Bins:

    for mass in masses:

      filename = "HN"+ch+"_"+str(mass)

      lines_VBFOnly = open('Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'_VBFOnly.log').readlines()
      pdf_VBFOnly = 0.
      rate_VBFOnly = float(lines_VBFOnly[len(lines_VBFOnly)-1].split()[0])
      for line in lines_VBFOnly:
        if "PDF" in line:
          words = line.split()
          pdf_VBFOnly = float(words[5])
      pdf_VBFOnly = 0.01*pdf_VBFOnly


      pdf = 0.
      rate = 0.
      if mass<1500:
        lines = open('Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log').readlines()
        rate = float(lines[len(lines)-1].split()[0])
        pdf = 0.
        for line in lines:
          if "PDF" in line:
            words = line.split()
            pdf = float(words[5])
        pdf = 0.01*pdf

      backup_pdf = pdf
      backup_pdf_VBFOnly = pdf_VBFOnly

      total_rate = rate_VBFOnly+rate
      pdf_VBFOnly = pdf_VBFOnly*rate_VBFOnly
      pdf = pdf*rate

      #print 'rate = '+str(rate)
      #print 'rate_VBFOnly = '+str(rate_VBFOnly)

      total_pdf = math.sqrt(pdf_VBFOnly*pdf_VBFOnly + pdf*pdf)/total_rate
      total_pdf = round(total_pdf,3)

      #print ch+' '+Bin+' '+str(mass)+' '+str(backup_pdf)+' '+str(backup_pdf_VBFOnly)+' '+str(total_pdf)
      out.write(ch+' '+Bin+' '+str(mass)+' '+str(total_pdf)+'\n')
      #print ch+' '+Bin+' '+str(mass)+' '+str(rate_VBFOnly)
      #out.write(ch+' '+Bin+' '+str(mass)+' '+str(pdf)+'\n')
