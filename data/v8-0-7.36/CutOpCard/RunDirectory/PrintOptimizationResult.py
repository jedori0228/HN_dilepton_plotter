import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

for ch in channels:
  for LowORHigh in range(0,2):
    for Bin in Bins:

      ## Low Mass
      masses = [40, 50, 60, 70, 80]
      varorder = [
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
      names = [
      "pt1 <\t",
      "pt2\t",
      "",
      "m(lljj) <\t",
      "m(l1jj) <\t",
      "m(l2jj) <\t",
      "m(ll)\t",
      "",
      "MET <\t",
      ]
      varsinboth = []

      if LowORHigh == 1:
        masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
        varorder = [
        "leadingLepton_Pt >",
        "secondLepton_Pt >",

        "m_jj_jjWclosest >",
        "m_jj_jjWclosest <",

        "m_lljj_jjWclosest >",

        "ljj |>",
        "ljj |<",

        "MET2ST <",
        ]
        names = [
        "pt1 >\t",
        "pt2 >\t",

        "m(jj)\t",
        "",

        "m(lljj) >\t",

        "m(ljj)\t",
        "",

        "MET2/ST <\t",
        ]
        varsinboth = [
        "m_jj_jjWclosest >",
        "ljj |>",
        "m_SubLeadljj_jjWclosest >"
        ]

      #print 'm(N) [GeV]\t',
      #for name in names:
      #  print name,
      #print "Bkgd\tSignal Efficiency"

      for mass in masses:
        lines = open('Cards_'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.txt').readlines()

        print str(mass)+'\t',
        counter = 0
        for var in varorder:

          if mass >= 90 and mass <= 200:
            if "ljj " in var:
              var = var.replace("ljj","m_SubLeadljj_jjWclosest")
              var = var.replace("|","")

          for line in lines:
            words = line.split()
            this_var = words[0]+" "+words[1]
            if not (this_var == var):
              continue

            value = str(int(float(words[2])))

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
            if "ljj |<" in var:
              print "15\t",


          counter = counter+1

        logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log'

        runlog = open(logname).readlines()
        bkgd = runlog[len(runlog)-2].split()[0]
       
        float_eff = float(runlog[len(runlog)-3].split()[2])
        eff = str(float_eff*1.)

        print bkgd+'\t'+eff

















