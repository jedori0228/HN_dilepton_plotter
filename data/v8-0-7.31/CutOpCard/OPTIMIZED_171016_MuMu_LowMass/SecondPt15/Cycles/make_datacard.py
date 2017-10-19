import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40, 50, 60, 70, 80]

os.system('mkdir -p Datacards')

# ################ result ################
# 11.3591 1.268
# 1206.372 1.189

channel = "MuMu"

for mass in masses:

  lines = open('log_HN'+channel+'_'+str(mass)+'.log').readlines()

  lastline_index = len(lines)-1

  LINE_total_bkg = lines[lastline_index-1].strip('\n')
  LINE_signal_rate = lines[lastline_index].strip('\n')

  total_bkg = float(LINE_total_bkg.split()[0])
  bkg_yield_err = float(LINE_total_bkg.split()[1])
  signal_rate = float(LINE_signal_rate.split()[0])
  signal_yield_err = float(LINE_signal_rate.split()[1])

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

  out = open('Datacards/HN'+channel+"_"+str(mass)+'.txt','w')

  out.write("imax 1  number of channels\n")
  out.write("jmax 1  number of backgrounds\n")
  out.write("kmax 2  number of nuisance parameters (sources of systematical uncertainties)\n")
  out.write("------------\n")
  out.write("# we have just one channel, in which we observe 0 events\n")
  out.write("bin 1\n")
  out.write("observation "+str(total_bkg)+"\n")
  out.write("------------\n")
  out.write("# now we list the expected events for signal and all backgrounds in that bin\n")
  out.write("# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n")
  out.write("# then we list the independent sources of uncertainties, and give their effect (syst. error)\n")
  out.write("# on each process and bin\n")
  out.write("bin\t1\t1\n")
  out.write("process\tHN"+str(mass)+"\tbkgd\n")
  out.write("process\t0\t1\n")
  out.write("rate\t"+str(signal_rate)+"\t"+str(total_bkg)+"\n")
  out.write("------------\n")
  out.write("sigerr\tlnN\t"+str(signal_yield_err)+"\t-\n")
  out.write("bkgerr\tlnN\t-\t"+str(bkg_yield_err)+"\n")

  out.close()

  print str(mass)+'\t'+str(total_bkg)


