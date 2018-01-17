import os

def StringToFloat(a):
  if "nan" in a:
    return 0.
  if "-" in a:
    return 0.
  return float(a)

def MakeYield(a,b,c):
  out = '$'+str(round(a,1))+' \\pm '+str(round(b,1))+' \\pm '+str(round(c,1))+'$'
  return out

channels = ["MuMu", "ElEl", "MuEl"]
channelsForLatex = ["$\mu \mu$", "$ee$", "$e \mu$"]

for LowORHigh in range(0,3):

  for it_ch in range(0,len(channels)):
    ch = channels[it_ch]

    Bins = ["Bin1", "Bin2"]
    if LowORHigh==1:
      Bins = ["Bin1"]
    if LowORHigh==2:
      Bins = ["Bin2"]

    for Bin in Bins:

      if LowORHigh==0:
        if Bin=="Bin1":
          print '\multirow{10}{*}{'+channelsForLatex[it_ch]+'} & \multirow{5}{*}{SR1}'
        else:
          print '\cline{2-8}'
          print ' & \multirow{5}{*}{SR2}'
      else:
        print '\multirow{19}{*}{'+channelsForLatex[it_ch]+'}'

      ## Low Mass
      masses = [40, 50, 60, 70, 80]

      if LowORHigh != 0:
        masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

      counter = 0
      for mass in masses:

        logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log'

        runlog = open(logname).readlines()

        index_systable = 0
        for a in range(0,len(runlog)):
          b = len(runlog)-1-a
          if "Sources" in runlog[b]:
            index_systable = b
            break

        total_stat = 0.
        prompt_stat = 0.
        fake_stat = 0.
        cf_stat = 0.
        for a in range(index_systable,len(runlog)):
          if "Stat" in runlog[a]:
            words = runlog[a].split()
            total_stat = StringToFloat(words[1])
            prompt_stat = StringToFloat(words[2])
            fake_stat = StringToFloat(words[3])
            cf_stat = StringToFloat(words[4])

        total_syst = 0.
        prompt_syst = 0.
        fake_syst = 0.
        cf_syst = 0.
        for a in range(index_systable,len(runlog)):
          if "Total Systematic" in runlog[a]:
            words = runlog[a].split()
            total_syst = StringToFloat(words[2])
            prompt_syst = StringToFloat(words[3])
            fake_syst = StringToFloat(words[4])
            cf_syst = StringToFloat(words[5])

        total = 0.
        prompt = 0.
        fake = 0.
        cf = 0.
        for a in range(index_systable,len(runlog)):
          if "Total Background" in runlog[a]:
            prompt = StringToFloat( runlog[a+1].split()[2] )
            fake = StringToFloat( runlog[a+2].split()[2] )
            cf = StringToFloat( runlog[a+3].split()[2] )
        total = prompt+fake+cf

        out = '$'+str(mass)+'$ & '
        out = out + MakeYield(prompt,prompt*(0.01*prompt_stat),prompt*(0.01*prompt_syst))+' & '
        out = out + MakeYield(fake,fake*(0.01*fake_stat),fake*(0.01*fake_syst))+' & '
        out = out + MakeYield(cf,cf*(0.01*cf_stat),cf*(0.01*cf_syst))+' & '
        out = out + MakeYield(total,total*(0.01*total_stat),total*(0.01*total_syst))+' & '
        out = out + 'BLIND \\\\'

        if LowORHigh==0:
          if counter==0:
            print '    & '+out
          else:
            print ' &  & '+out

        else:
          print ' & '+out

        counter = counter+1

    print '\\hline'

  print ""
  print "#################"
  print ""











