import os,math

def AddPhantomZero(a, align, digit_int, digit_frac):

  if align=="r":
    number_maxdigit = 0
    for j in range(0,11):
      i = 10-j
      if a/math.pow(10,i)>=1.:
        number_maxdigit = i
        break
    for i in range(0,digit_int-(number_maxdigit+1)):
      sys.stdout.write('\\phantom{0}')
      sys.stdout.flush()
    sys.stdout.write(str(round(a,digit_frac)))
    sys.stdout.flush()

  elif align=="l":
    target_total_digit = digit_int+digit_frac
    number_maxdigit = 0
    for j in range(0,11):
      i = 10-j
      if a/math.pow(10,i)>=1.:
        number_maxdigit = i
        break
    sys.stdout.write(str(round(a,digit_frac)))
    sys.stdout.flush()
    for i in range(0,target_total_digit-(number_maxdigit+1)-digit_frac):
      sys.stdout.write('\\phantom{0}')
      sys.stdout.flush()



def StringToFloat(a):
  if "nan" in a:
    return 0.
  if "-" in a:
    return 0.
  return float(a)

def MakeYield(a,b,c,nround):

  central_yield = str(round(a,nround))
  '''if central_yield=="0.0":
    nround = nround+1
    central_yield = str(round(a,nround))
  if central_yield=="0.0":
    nround = nround+1
    central_yield = str(round(a,nround))
  if central_yield=="0.0":
    nround = nround+1
    central_yield = str(round(a,nround))
  if central_yield=="0.0":
    nround = nround+1
    central_yield = str(round(a,nround))'''

  out = '$'+central_yield+' \\pm '+str(round(b,nround))+' \\pm '+str(round(c,nround))+'$'

  return out

channels = ["MuMu", "ElEl", "MuEl"]
channelsForLatex = ["$\mu \mu$", "$\Pe \Pe$", "$\Pe \mu$"]

for LowORHigh in range(0,3):

  for it_ch in range(0,len(channels)):
    ch = channels[it_ch]

    Bins = ["Bin1", "Bin2"]
    if LowORHigh==1:
      Bins = ["Bin1"]
    if LowORHigh==2:
      Bins = ["Bin2"]

    for Bin in Bins:

      ## Low Mass
      masses = [20, 30, 40, 50, 60, 70, 75, 80]
      n_multirow = len(masses)-1 ## no 80 GeV for now

      if LowORHigh != 0:
        masses = [85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]
        n_multirow = len(masses)

      counter = 0
      for mass in masses:

        logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log'
        ## FIXME TEMP no s-ch for 1700 and 2000
        if mass>=1700:
          logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'_VBFOnly.log'

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
        obs = 0
        for a in range(index_systable,len(runlog)):
          if "Total Background" in runlog[a]:
            prompt = StringToFloat( runlog[a+1].split()[2] )
            fake = StringToFloat( runlog[a+2].split()[2] )
            cf = StringToFloat( runlog[a+3].split()[2] )
            obs = StringToFloat( runlog[a+4].split()[2] )
        total = prompt+fake+cf

        nround = 1
        if LowORHigh!=0:
          nround = 3

        out = '$'+str(mass)+'$ & '
        out = out + MakeYield(prompt,prompt*(0.01*prompt_stat),prompt*(0.01*prompt_syst),nround)+' & '

        if fake<=0.:
            maxFR = 0.169201;
            if ch=="MuMu":
               maxFR = 0.103305;
            fake_stat = 1.8*(maxFR)/(1.-maxFR);
            out = out + MakeYield(fake,fake_stat,fake*(0.01*fake_syst),nround)+' & '
        else:
          out = out + MakeYield(fake,fake*(0.01*fake_stat),fake*(0.01*fake_syst),nround)+' & '

        if ch=="ElEl":
          out = out + MakeYield(cf,cf*(0.01*cf_stat),cf*(0.01*cf_syst),nround)+' & '
        else:
          out = out + "-- & "

        if fake<=0.:
          totalstaterr = total*(0.01*total_stat)
          totalstaterr = math.sqrt( totalstaterr*totalstaterr + fake_stat*fake_stat )
          out = out + MakeYield(total,totalstaterr,total*(0.01*total_syst),nround)+' & '
        else:
          out = out + MakeYield(total,total*(0.01*total_stat),total*(0.01*total_syst),nround)+' & '

        out = out + '$'+str(int(obs))+'$ \\\\'

        if LowORHigh==0:
          if counter==0:
            if Bin=="Bin1":
              print '\\multirow{'+str(2*n_multirow)+'}{*}{'+channelsForLatex[it_ch]+'} & \\multirow{'+str(n_multirow)+'}{*}{SR1}'
            if Bin=="Bin2":
              print '\cline{2-8}'
              print '& \multirow{'+str(n_multirow)+'}{*}{SR2}'

            out = '   & '+out

          else:
            out = ' &  & '+out


        else:
          if counter==0:
            print '\multirow{'+str(n_multirow)+'}{*}{'+channelsForLatex[it_ch]+'}'
          out = ' & '+out

        print out

        counter = counter+1

    print '\\hline'

  print ""
  print "#################"
  print ""











