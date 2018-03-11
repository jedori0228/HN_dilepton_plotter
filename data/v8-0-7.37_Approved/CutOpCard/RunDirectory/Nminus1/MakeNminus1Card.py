import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses_Tch = [300, 600, 800, 1000, 1200, 1500]


counter = 0
for ch in channels:
  for LowORHigh in range(0,2):
    for Bin in Bins:

      ## Bin1
      ## Low Mass

      masses = [20, 30, 40, 50, 60, 70, 75, 80]
      varorder = [
      "Njets",
      "DeltaRl1l2",
      "leadingLepton_Pt",
      "secondLepton_Pt",
      "m_lljj_lljjWclosest",
      "m_Leadljj_lljjWclosest",
      "m_SubLeadljj_lljjWclosest",
      "m_ll",
      "PFMET",
      ]

      ## Bin2
      ## Low Mass

      if LowORHigh == 0 and Bin == "Bin1":
        masses = [20, 30, 40, 50, 60, 70, 75, 80]
        varorder = [
        "Njets",
        "DeltaRl1l2",
        "leadingLepton_Pt",
        "secondLepton_Pt",
        "m_lljj_lljjWclosest",
        "m_Leadljj_lljjWclosest",
        "m_SubLeadljj_lljjWclosest",
        "m_ll",
        "PFMET",
        ]

      if LowORHigh == 1:
        #masses = [85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]
        masses = [85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
        varorder = [
        "Njets",
        "leadingJet_lljjWclosest_pt",
        "DeltaRSubLeadl_jjWclosest",
        "leadingLepton_Pt",
        "secondLepton_Pt",
        "m_jj_jjWclosest",
        "m_lljj_jjWclosest",
        "ljj",
        "MET2ST",
        ]

      for mass in masses:
        lines = open('Cards_'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.txt').readlines()

        for a in range(0,len(varorder)+2):

          newout = open('Cards_'+ch+'_'+Bin+'/step'+str(a)+'_HN'+ch+'_'+str(mass)+'.txt','w')
          for line in lines:

            # e.g., line = leadingpt > 10
            # loop over var list, and a+1~end th var is commented out

            newline = line

            if a==0:
              newline = "#"+line

            elif a==len(varorder)+1:
              newline = newline

            else:
              thisvar = varorder[a-1]
              if mass <= 200 and thisvar=="ljj":
                thisvar = "m_SubLeadljj_jjWclosest"

              if thisvar == line.split()[0]:
                newline = "#"+line

            newout.write(newline)

          newout.close()

          filename = "HN"+ch+"_"+str(mass)
          cfilename = "CyclesForOptimization_"+ch+"_"+Bin+"/"+filename+".C"
          os.system('mkdir -p Outputs_step'+str(a))
          cmd = 'root -l -b -q "'+cfilename+'('+str(a)+')"'+' > Outputs_step'+str(a)+'/log_'+Bin+"_"+filename+'.log &'
          print cmd

          if counter!=0 and counter%30==0:
            print "sleep 10"
          counter = counter+1
