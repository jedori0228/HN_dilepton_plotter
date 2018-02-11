import os
import csv

WORKING_DIR = os.environ['PLOTTER_WORKING_DIR']
dataset = os.environ['CATANVERSION']
ENV_PLOT_PATH = os.environ['PLOT_PATH']

filepath = ENV_PLOT_PATH+dataset+"/CutOptimizationResults/CutOptSummary_NEW_use_l1jjorl2jj/";

channels = ["DiMuon", "DiElectron", "EMu"]
channels_for_tex = ["$\\mu\\mu$", "$ee$", "$e\\mu$"]

regions = ["Low", "High"]
regions_for_tex = ["low", "high"]

#      len-2         len-1
# ...  Bkgd   & Signal Efficiency
RowEndIndex = 0

regioncounter = 0
for region in regions:
  chcounter = 0
  for ch in channels:
    filename = ch+"_"+region+"-"+ch+"_"+region

    with open(filepath+filename+".csv", 'rb') as csvfile:
      spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')

      print "\\begin{table}[!hptb]"
      print "  \\centering"
      print "  \\caption{"
      print "  Cut optimization results at "+channels_for_tex[chcounter]+" "+regions_for_tex[regioncounter]+" selection."
      print "  }"
      print "  \\label{table:cutop_"+ch+"_"+region+"}"
      #print "  \\begin{center}"
      #print "    \\footnotesize"
      print "    \\resizebox{\\columnwidth}{!}{"
      if "Low" in region:
        print "      \\begin{tabular}{c|c|ccccccccc|c|c|c}"
      elif "High in region":
        print "      \\begin{tabular}{c|c|ccccccccc|c|c|cc}"
      print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"

      for row in spamreader:

        MaxRowIndex = len(row)-RowEndIndex

        ## First Row
        if "Signal Region" in row[0]:
          for a in range(0,MaxRowIndex-1):
            thisword = row[a]
            thisword = thisword.replace('$\Delta R(\ell 2 jj) <$','$\Delta R(\ell 2, jj) <$')
            thisword = thisword.replace('$\Delta R(\ell 1 \ell 2) <$','$\Delta R(\ell 1, \ell 2) <$')
            print thisword+" &",

          thisword = row[MaxRowIndex-1]
          print thisword+" \\\\"

        
        else:
          for a in range(0,MaxRowIndex):
            row[a] = row[a].replace('%','~\\%')

            if a==0:

              if "SR" in row[0]:
                nmassstr = "7"
                if "High" in region:
                  nmassstr = "19"
                print "\\hline"
                print "\multirow{"+nmassstr+"}{*}{"+row[0]+"} &",
              else:
                print " &",

            else:
              toprint = row[a]
              if toprint != "":
                toprint = "$"+toprint+"$"

              if a != MaxRowIndex-1:
                print toprint+" &",
              else:
                print toprint+" \\\\"

      print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
      print "      \\end{tabular}"
      print "    }"
      #print "  \\end{center}"
      print "\\end{table}"

    chcounter = chcounter+1

  regioncounter = regioncounter+1
