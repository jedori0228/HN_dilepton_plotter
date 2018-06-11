import os,math

def AddPhantomZero(a,left,right,align):
  vals = a.split('.')
  val_int = vals[0]
  val_fra = vals[1]

  phantoms = "\phantom{"

  for a in range(0, left-len(val_int)):
    phantoms = phantoms+"0"
    #val_int = "\\phantom{0}"+val_int
  #phantoms = phantoms+"."

  for a in range(0, right-len(val_fra)):
    phantoms = phantoms+"0"
    #val_fra = val_fra+"\\phantom{0}"
  phantoms = phantoms+"}"

  if align == "r":
    return phantoms+val_int+"."+val_fra
  else:
    return val_int+"."+val_fra+phantoms

def StringToFloat(a):
  if "nan" in a:
    return 0.
  if "-" in a:
    return 0.
  return float(a)

def CheckStringDigit(str_a,n):

  for i in range(0,len(str_a)):
    if str_a[i]==".":
      n_written_digit = len(str_a)-1-i

      for j in range(0, n-n_written_digit):
        str_a += "0"

      return str_a

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

  #out = '$'+central_yield+' \\pm '+str(round(b,nround))+' \\pm '+str(round(c,nround))+'$'

  tot = math.sqrt(b*b+c*c)
  str_tot = str(round(tot,nround))

  backup_nround = nround
  if central_yield == "0.0" and str_tot == "0.0":
    nround = nround+1
    central_yield = str(round(a,nround))
    str_tot = str(round(tot,nround))

  central_yield = CheckStringDigit(central_yield,backup_nround)
  str_tot = CheckStringDigit(str_tot,backup_nround)


  if a < tot:
    out = AddPhantomZero(central_yield,2,1,"r")+'^{\phantom{0}+\phantom{0}'+AddPhantomZero(str_tot,2,1,"l")+'\phantom{0}}_{\phantom{0}-\phantom{0}'+AddPhantomZero(central_yield,2,1,"l")+'\phantom{0}}'
  else:
    out = AddPhantomZero(central_yield,2,1,"r")+' \\pm '+AddPhantomZero(str_tot,2,1,"l")

  #out = central_yield+'\t'+str_tot

  return out

channels = ["ElEl", "MuMu", "MuEl"]
channelsForLatex = ["$\Pe\Pe$", "$\mu\mu$", "$\Pe\mu$"]

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

      if LowORHigh != 0:
        masses = [85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1700, 2000]

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

        nround = 2
        #if LowORHigh!=0:
        #  nround = 2

        out = '$'+str(mass)+'$ & '
        out = out + MakeYield(prompt,prompt*(0.01*prompt_stat),prompt*(0.01*prompt_syst),nround)+' & '

        if fake<=0.:
          maxFR = 0.169201;
          if ch=="MuMu":
            maxFR = 0.103305;
            fake_stat = 1.8*(maxFR)/(1.-maxFR);

          totalstaterr = total*(0.01*total_stat)
          totalstaterr = math.sqrt( totalstaterr*totalstaterr + fake_stat*fake_stat )
          out = MakeYield(total,totalstaterr,total*(0.01*total_syst),nround)

        else:
          out = MakeYield(total,total*(0.01*total_stat),total*(0.01*total_syst),nround)

        

        print out

        counter = counter+1


  print "#################\n"









