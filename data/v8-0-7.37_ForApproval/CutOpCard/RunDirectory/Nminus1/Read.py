import os
from decimal import Decimal

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses_Tch = [300, 600, 800, 1000, 1200, 1500]


counter = 0

for LowORHigh in range(0,2):

  for ch in channels:

    chlatex = "$\\mu \\mu$"
    if ch=="ElEl":
      chlatex = "$\Pe \Pe$"
    if ch=="MuEl":
      chlatex = "$\Pe \mu$"

    if LowORHigh==0:

      print '''\\begin{{table}}[!hptb]
  \\centering
  \\caption{{
  N-1 cut efficiency with respect to inclusive seleciton at {0} low-mass selection.
  }}
  \\label{{table:nminus1_{1}_Low}}
  \\begin{{center}}
    \\resizebox{{\columnwidth}}{{!}}{{
      \\begin{{tabular}}{{c|c|c|c||c|c|c|c|c|c|c|c|c||c}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Signal Region & $m_{{N}}$ (\GeV) & Source & Incl. & Number of AK4 jets $<$ & $\Delta R(\ell 1, \ell 2) <$ & $\pt_{{\ell 1}} <$ & $\pt_{{\ell 2}} <$ &  $m(\ell \ell jj) <$ &  $m(\ell_{{1}} jj) <$ &  $m(\ell_{{2}} jj) <$ & $m(\ell \ell)$ & $\\ETslash <$ & Final Selection \\\\
\\hline
'''.format(chlatex,ch)

    else:

      print '''\\begin{{table}}[!hptb]
  \\centering
  \\caption{{
  N-1 cut efficiency with respect to inclusive seleciton at {0} high-mass selection.
  }}
  \\label{{table:nminus1_{1}_High}}
  \\begin{{center}}
    \\resizebox{{\columnwidth}}{{!}}{{
      \\begin{{tabular}}{{c|c|c|c||c|c|c|c|c|c|c|c|c||c}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Signal Region & $m_{{{{N}}}}$ (\GeV) & Source & Incl. & Number of AK4 jets $<$ & $\pt_{{j 1}} >$ & $\Delta R(\ell 2, jj) <$ & $\pt_{{\ell 1}} >$ & $\pt_{{\ell 2}} >$ & $m(jj)$ &  $m(\ell \ell jj) >$ &  $m(\ell jj)$ & $\\ETslash^{{2}}/S_{{T}} <$ & Final Selection \\\\
\\hline
'''.format(chlatex,ch)

    for Bin in Bins:

      SR = "SR1"
      if Bin=="Bin2":
        SR = "SR2"

      ## Low Mass
      masses = [20, 30, 40, 50, 60, 70, 75]
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

      ToSkip = []

      if Bin=="Bin2" and LowORHigh==0:
        ToSkip.append("Njets")
      if Bin=="Bin2" and LowORHigh==1:
        ToSkip.append("Njets")
        ToSkip.append("leadingJet_lljjWclosest_pt")
        ToSkip.append("DeltaRSubLeadl_jjWclosest")
        ToSkip.append("m_lljj_jjWclosest")
        ToSkip.append("m_jj_jjWclosest")
        ToSkip.append("MET2ST")

      masscounter=0
      for mass in masses:
        ## Bkgd

        if masscounter==0:
          print '\\multirow{'+str(3*len(masses))+'}{*}{'+SR+'}'+' & \\multirow{3}{*}{'+str(mass)+'} & Bkgd.',
        else:
          print ' & \\multirow{3}{*}{'+str(mass)+'} & Bkgd.',

        totalbkg_incl = 0
        for a in range(0,len(varorder)+2):

          filename = "HN"+ch+"_"+str(mass)
          lines = open('Outputs_step'+str(a)+'/log_'+Bin+"_"+filename+'.log').readlines()

          line_totalbkg = lines[len(lines)-3]
          line_sigeff = lines[len(lines)-1]

          totalbkg = line_totalbkg.split()[4]
          sigeff = line_sigeff.split()[2]

          if a==0:
            totalbkg_incl = float(totalbkg)
            print " & $"+str(round(totalbkg_incl,1))+'$',
          elif a==len(varorder)+1:
            thisyield = float(totalbkg)
            print " & $"+str(round(100.*thisyield/totalbkg_incl,1))+'~\\%$',
          else:

            if varorder[a-1] in ToSkip:
              print ' & --',
              continue

            releff_totalbkg = 0.
            releff_sigeff = 0.

            if totalbkg_incl != 0:
              releff_totalbkg = float(totalbkg)/totalbkg_incl
            print " & $"+str(round(100.*releff_totalbkg,1))+'~\\%$',
        print "\\\\ "
        print "\\cline{3-14}"

        ## Sig
        print ' & & Sig.',
        sigeff_incl = 0
        for a in range(0,len(varorder)+2):

          filename = "HN"+ch+"_"+str(mass)
          lines = open('Outputs_step'+str(a)+'/log_'+Bin+"_"+filename+'.log').readlines()

          line_totalbkg = lines[len(lines)-3]
          line_sigeff = lines[len(lines)-1]

          totalbkg = line_totalbkg.split()[4]
          sigeff = line_sigeff.split()[2]

          if a==0:
            sigeff_incl = float(sigeff)
            print " & $"+str(round(100.*sigeff_incl,2))+'~\\%$',
          elif a==len(varorder)+1:
            thiseff = float(sigeff)
            print " & $"+str(round(100.*thiseff/sigeff_incl,1))+'~\\%$',
          else:

            if varorder[a-1] in ToSkip:
              print ' & --',
              continue

            releff_totalbkg = 0.
            releff_sigeff = 0.

            if sigeff_incl !=0 :
              releff_sigeff = float(sigeff)/sigeff_incl
            print " & $"+str(round(100.*releff_sigeff,1))+'~\\%$',

        print "\\\\ "
        print "\\cline{3-14}"

        ## Punzi
        print ' & & Punzi',
        for a in range(0,len(varorder)+2):

          filename = "HN"+ch+"_"+str(mass)
          lines = open('Outputs_step'+str(a)+'/log_'+Bin+"_"+filename+'.log').readlines()

          line_totalbkg = lines[len(lines)-3]
          line_sigeff = lines[len(lines)-1]

          totalbkg = line_totalbkg.split()[4]
          sigeff = line_sigeff.split()[2]
          punzi = line_sigeff.split()[4]

          if a==0:
            b = " & $%.2e$" % Decimal(punzi)
            b = b.replace("e","\\mathrm{e}")
            print b,
          elif a==len(varorder)+1:
            b = " & $%.2e$" % Decimal(punzi)
            b = b.replace("e","\\mathrm{e}")
            print b,
          else:

            if varorder[a-1] in ToSkip:
              print ' & --',
              continue

            b = " & $%.2e$" % Decimal(punzi)
            b = b.replace("e","\\mathrm{e}")
            print b,

        print "\\\\ "

        if mass!=masses[len(masses)-1]:
          print "\\cline{2-14}"

        masscounter = masscounter+1

      print '\\hline'

    print '''
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      \\end{tabular}
    }
  \\end{center}
\\end{table}
'''
