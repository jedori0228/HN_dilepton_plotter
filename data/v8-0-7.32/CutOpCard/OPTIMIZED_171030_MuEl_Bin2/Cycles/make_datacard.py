import os

DoBin1 = False
channel = "MuEl"

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

os.system('mkdir -p Datacards')

# ################ result ################
# 11.3591 1.268
# 1206.372 1.189

for mass in masses:

  signal_rate = 1.
  if mass <= 60:
    signal_rate *= 0.01
  elif mass <= 100:
    signal_rate *= 0.1
  elif mass <= 300:
    signal_rate *= 1
  elif mass <= 700:
    signal_rate *= 10
  else:
    signal_rate *= 100

  #### HOT FIX ####
  if mass == 80:
    Wrong = 2.01340
    Correct = 0.4525
    signal_rate *= Correct/Wrong


  logfilename = 'log_HN'+channel+'_'+str(mass)+'.log'
  if not DoBin1:
    logfilename = 'log_Bin2_HN'+channel+'_'+str(mass)+'.log'

  lines = open(logfilename).readlines()

  ## fine yield first ##
  bkgd = 0
  prompt = 0
  fake = 0
  cf = 0

  for a in range(0,len(lines)):
    if "Total Background" in lines[a]:
      line_prompt = lines[a+1]
      line_fake = lines[a+2]
      line_cf = lines[a+3]

      prompt = float( line_prompt.split()[2] )
      fake = float( line_fake.split()[2] )
      cf = float( line_cf.split()[2] )

      bkgd = prompt+fake+cf
      break

  ## 4135.629 1.160
  print lines[len(lines)-1]
  signal_rate = float(lines[len(lines)-1].split()[0])*signal_rate

  outname = 'Datacards/HN'+channel+"_"+str(mass)+'.txt'
  if not DoBin1:
    outname = 'Datacards/Bin2_HN'+channel+"_"+str(mass)+'.txt'
  out = open(outname,'w')

  out.write("imax 1  number of channels\n")
  out.write("jmax 3  number of backgrounds\n")
  out.write("kmax 20  number of nuisance parameters (sources of systematical uncertainties)\n")
  out.write("------------\n")
  out.write("# we have just one channel, in which we observe 0 events\n")
  out.write("bin 1\n")
  out.write("observation "+str(bkgd)+"\n")
  out.write("------------\n")
  out.write("# now we list the expected events for signal and all backgrounds in that bin\n")
  out.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
  out.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
  out.write("# on each process and bin\n")
  out.write("bin\t1\t1\t1\t1\n")
  out.write("process\tprompt\tfake\tcf\tHN"+str(mass)+"\n")
  out.write("process\t1\t2\t3\t0\n")
  out.write("rate\t"+str(prompt)+"\t"+str(fake)+"\t"+str(cf)+"\t"+str(signal_rate)+"\n")
  out.write("------------\n")

  firstline_index = 0
  for a in range(0,len(lines)):
    if "Sources" in lines[a]:
      firstline_index = a

  for a in range(firstline_index+2,len(lines)):
    line = lines[a]
    line = line.replace('-nan','-')
    line = line.replace('nan','-')
    line = line.strip('\n')
    if "Total Systematic" in line:
      break

    words = line.split()
    ## BMiss	1.14	2.62	-	1.11
    #  -> MuonPt  lnN     1.01107 1.0176  1.01112
    thisline = words[0]+"\tlnN"
    for b in range(2,len(words)):
      if words[b]=="-":
        thisline = thisline+"\t"+words[b]
      else:
        syst=float(words[b])*0.01+1.
        thisline = thisline+"\t"+str(syst)
    out.write(thisline+"\n")

    



