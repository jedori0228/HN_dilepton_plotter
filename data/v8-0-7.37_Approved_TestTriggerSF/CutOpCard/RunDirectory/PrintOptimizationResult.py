import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses_Tch = [300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]

for ch in channels:
  for LowORHigh in range(0,2):
    for Bin in Bins:

      ## Low Mass
      masses = [20, 30, 40, 50, 60, 70, 75, 80]
      varorder = [
      "Njets <",

      "DeltaRl1l2 <",

      "leadingLepton_Pt <",

      "secondLepton_Pt >",
      "secondLepton_Pt <",

      "m_lljj_lljjWclosest <",
      "m_Leadljj_lljjWclosest <",
      "m_SubLeadljj_lljjWclosest <",

      "m_ll >",
      "m_ll <",

      "PFMET <",
      ]
      varsinboth = []

      if LowORHigh == 1:
        masses = [85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]
        varorder = [
        "Njets <",

        "leadingJet_lljjWclosest_pt >",
        "DeltaRSubLeadl_jjWclosest <",

        "leadingLepton_Pt >",
        "secondLepton_Pt >",

        "m_jj_jjWclosest >",
        "m_jj_jjWclosest <",

        "m_lljj_jjWclosest >",

        "ljj |>",
        "ljj |<",

        "MET2ST <",
        ]
        varsinboth = [
        "m_jj_jjWclosest >",
        "ljj |>",
        "m_SubLeadljj_jjWclosest >"
        ]

      for mass in masses:
        lines = open('Cards_'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.txt').readlines()

        print str(mass)+'\t',
        counter = 0
        for var in varorder:

          ## # of jets only for Bin1
          if Bin == "Bin2":
            if "Njets" in var:
              print "-\t",

          ## leading jet pt
          if mass >= 85 and Bin == "Bin2":
            if "leadingJet_lljjWclosest_pt" in var:
              print "-\t",

          ## medium mass l2jj
          if mass >= 85 and mass <= 200:
            if "ljj " in var:
              var = var.replace("ljj","m_SubLeadljj_jjWclosest")
              var = var.replace("|","")

          ## Delta R only for medium mass, Bin1
          if mass >= 250 or Bin == "Bin2":
            if "DeltaRSubLeadl_jjWclosest" in var:
              print "-\t",
              continue

          ## M>=600GeV, no second pt cut
          if mass >=600:
            if "secondLepton_Pt" in var:
              print "-\t",

          for line in lines:
            words = line.split()
            this_var = words[0]+" "+words[1]
            if not (this_var == var):
              continue

            value = str(int(float(words[2])))
            if "DeltaRSubLeadl_jjWclosest" in var or "DeltaRl1l2" in var:
              value = str(float(words[2]))

            if LowORHigh == 0:
              if var=="secondLepton_Pt >" or var=="m_ll >":
                print value+" -",
              else:
                print value+'\t',
            else:
              if var in varsinboth:
                print value+" -",
              else:
                print value+'\t',

          if Bin == "Bin2" and  LowORHigh == 1:
            if "secondLepton_Pt" in var:
              print "40 - 130\t-\t",
              if mass==85:
                print "-\t",
            if ("ljj |<" in var) or ("m_SubLeadljj_jjWclosest <" in var):
              print "15\t",


          counter = counter+1

        logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log'

        ## FIXME TEMP, no s-ch for 1700 and 2000
        if mass>=1700:
          logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'_VBFOnly.log'

        runlog = open(logname).readlines()
        bkgd = runlog[len(runlog)-2].split()[0]
        obs = str(int(float(runlog[len(runlog)-6].split()[2])))
       
        float_eff = float(runlog[len(runlog)-3].split()[2])
        eff_S = str(float_eff*1.)
        eff_S_staterr = 0.

        for linelog in runlog:
          if "Stat" in linelog:
            eff_S_staterr = 0.01*float(linelog.split()[5])*float_eff


        if (LowORHigh==1) and (mass in masses_Tch):
          lines_T = open('Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'_VBFOnly.log').readlines()
          float_eff_T = float(lines_T[len(lines_T)-3].split()[2])
          eff_T = str(float_eff_T*1.)
          eff_T_staterr = 0.
          for linelog in lines_T:
            if "Stat" in linelog:
              eff_T_staterr = 0.01*float(linelog.split()[5])*float_eff_T

          print bkgd+'\t'+obs+'\t'+eff_S+"\t"+str(eff_S_staterr)+"\t"+eff_T+"\t"+str(eff_T_staterr)

        else:
          print bkgd+'\t'+obs+'\t'+eff_S+"\t"+str(eff_S_staterr)


















