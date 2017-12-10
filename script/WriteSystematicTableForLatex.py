import os
import csv

WORKING_DIR = os.environ['PLOTTER_WORKING_DIR']
dataset = os.environ['CATANVERSION']
ENV_PLOT_PATH = os.environ['PLOT_PATH']

filepath = ENV_PLOT_PATH+dataset+"/CutOptimizationResults/DiLeptonSystTable/";

channels = ["DiMuon", "DiElectron", "EMu"]
channels_for_tex = ["$\\mu\\mu$", "$ee$", "$e\\mu$"]

regions = ["Low_TwoJet", "Low_OneJet", "High_TwoJet", "High_FatJet"]
regions_for_tex = ['low mass region with "two jets"', 'low mass region with "one jet"', 'high mass region with "two jets"', 'high mass region with "fat jet"']


chcounter = 0
for ch in channels:
  regioncounter = 0
  for region in regions:
    filename = ch+"_"+region+"-"+ch+"_"+region

    with open(filepath+filename+".csv", 'rb') as csvfile:
      spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')

      print "\\begin{table*}[!tbh]"
      print "  \\caption{"
      print "  Systematic uncertainties at "+channels_for_tex[chcounter]+" "+regions_for_tex[regioncounter]
      print "  }"
      print "  \\label{table:syst_"+ch+"_"+region+"}"
      print "  \\begin{center}"
      if ch != "DiElectron":
        print "    \\begin{tabular}{c|c|cc|c}"
      else:
        print "    \\begin{tabular}{c|c|ccc|c}"
      print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"

      counter = 0
      for row in spamreader:

        if "Total Systematic" in row:
          print "\\hline"

        if ch != "DiElectron":
          if "CF" in row[0]:
            continue

        ## anem
        if counter == 0:

          #for a in range(0,len(row)):
#
#            if ch != "DiElectron":
#              if a == 4:
#                continue
#
#            if a == 0:
#              print row[a]+" & ",
#            elif a != len(row)-1:
#              print row[a]+" & ",
#            else:
#              print row[a]+" \\\\"
#

          if ch != "DiElectron":
            print " & Systematic & Systematic & Systematic & \\\\"
            print "Source & per & per & per & Signal $m_{N} = "+row[len(row)-1]+"~\GeV$ \\\\"
            print " & total bkgd. & prompt bkgd. & fake bkgd. & \\\\"
          else:
            print " & Systematic & Systematic & Systematic & Systematic & \\\\"
            print "Source & per & per & per & per & Signal $m_{N} = "+row[len(row)-1]+"~\GeV$ \\\\"
            print " & total bkgd. & prompt bkgd. & fake bkgd. & cf bkgd. & \\\\"

          print "\\hline"

        ## value
        else:
          for a in range(0,len(row)):

            if ch != "DiElectron":
              if a == 4:
                continue

            if a == 0:
              print row[a]+" &",
            elif a != len(row)-1:
              if row[a]=="-":
                print "$-$ &",
              else:
                print "$"+row[a]+"~\\%$ &",
            else:
              if row[a]=="-":
                print "$-$ \\\\"
              else:
                print "$"+row[a]+"~\\%$ \\\\"
        counter = counter+1

        if "Total Systematic" in row:
          break



      print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
      print "    \\end{tabular}"
      print "  \\end{center}"
      print "\\end{table*}"


    regioncounter = regioncounter+1
  chcounter = chcounter+1


