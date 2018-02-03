import os
import csv

WORKING_DIR = os.environ['PLOTTER_WORKING_DIR']
dataset = os.environ['CATANVERSION']
ENV_PLOT_PATH = os.environ['PLOT_PATH']

filepath = ENV_PLOT_PATH+dataset+"/CutOptimizationResults/PAS_CutOptSummary_NEW_use_l1jjorl2jj/";

regions = ["Low", "High_SR1", "High_SR2"]
regions_for_tex = ["low-mass", "high-mass SR1", "high-mass SR2"]

#      len-2         len-1
# ...  Bkgd   & Signal Efficiency
RowEndIndex = 0

regioncounter = 0
for region in regions:
  chcounter = 0
  filename = region+"-"+region

  RowSkipIndex = [3,4,11,12,13]
  if "High_SR1" in region:
    RowSkipIndex = [2,3,4,7,11,12]
  if "High_SR2" in region:
    RowSkipIndex = [2,3,4,7,8,10,11,12]

  with open(filepath+filename+".csv", 'rb') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')

    print "\\begin{table}[!hptb]"
    print "  \\centering"
    print "  \\caption{"
    print "  Selection requirements on discriminating variables determined by the optimization for each Majorana neutrino mass point in the "+regions_for_tex[regioncounter]+". The last column shows the overall signal acceptance."
    print "  }"
    print "  \\label{table:cutop_"+region+"}"
    print "  \\begin{center}"
    #print "    \\footnotesize"
    print "    \\resizebox{\\columnwidth}{!}{"
    if "Low" in region:
      print "      \\begin{tabular}{c|c|c|cccccc|c|c|c}"
    if "High_SR1" in region:
      print "      \\begin{tabular}{c|c|cccccc|c|c|cc}"
    if "High_SR2" in region:
      print "      \\begin{tabular}{c|c|cccc|c|c}"
    print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"

    for row in spamreader:

      MaxRowIndex = len(row)-RowEndIndex

      ## First Row
      if "Signal Region" in row or "(\GeV)" in row:
        for a in range(0,MaxRowIndex-1):

          if a in RowSkipIndex:
            continue

          thisword = row[a]
          thisword = thisword.replace('$\Delta R(\ell 2 jj) <$','$\Delta R(\ell 2, jj) <$')
          thisword = thisword.replace('$\Delta R(\ell 1 \ell 2) <$','$\Delta R(\ell 1, \ell 2) <$')
          print thisword+" &",

        thisword = row[MaxRowIndex-1]
        print thisword+" \\\\"

      else:

        start_index = 2
        if "High" in region :
          start_index = 1

        mass = int(float(row[start_index]))

        for a in range(start_index,MaxRowIndex):
          row[a] = row[a].replace('%','')

          if a==0:

            if "$" in row[0]:
              nmassstr = "14"
              if "High" in region:
                nmassstr = "19"
              print "\\hline"
              print "\multirow{"+nmassstr+"}{*}{"+row[0]+"} &",
            else:
              print " &",

          elif a==1 and "Low" in region:
            if "SR" in row[1]:
              nmassstr = "7"
              print "\multirow{"+nmassstr+"}{*}{"+row[1]+"} &",
            else:
              print " &",
          elif a in RowSkipIndex:
            continue
          else:
            toprint = row[a]
            if toprint != "":
              toprint = toprint

            ## HOTFIX 1 ##
            if region=="Low":
              if a==5:
                if row[a]=="80":
                  toprint = "20 - 80"
                if row[a]=="70":
                  toprint = "25 - 70"
                if row[a]=="60":
                  toprint = "25 - 60"

              if a==7 or a==8 or a==9:
                toprint = "$< "+toprint+"$"

              if a==14:
                toprint = "$"+row[a]+"\\pm"
                print toprint,
                continue
              if a==15:
                toprint =  row[a]+"$"

            ## HOTFIX 2 ##
            if "High" in region:

              if a==5 or a==6 or a==8:
                toprint = "$> "+toprint+"$"

              if a==6 and mass>=600:
                print "$ - $ &",
                continue

              if a==10:
                toprint = "$< "+toprint+"$"


              if a==13:
                toprint = "$"+row[a]+"\\pm"
                print toprint,
                continue
              if a==14:
                toprint =  row[a]+"$"
                print toprint,
                continue

              if a==15:
                if toprint!= "":
                  toprint = "[$"+row[a]+"\\pm"
                  print toprint,
                  continue
                else:
                  continue
              if a==16:
                if toprint!= "":
                  toprint =  row[a]+"$]"
                else:
                  toprint = toprint

            if a != MaxRowIndex-1:
              print toprint+" &",
            else:
              print toprint+" \\\\"

    print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    print "      \\end{tabular}"
    print "    }"
    print "  \\end{center}"
    print "\\end{table}"


  regioncounter = regioncounter+1
