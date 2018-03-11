import os,math

channels = ["MuMu", "ElEl", "MuEl"]
masses = [20, 30, 40, 50, 60, 70, 75, 80, 85, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]#, 1700, 2000]
Bins = ["Bin1", "Bin2"]

print len(masses)
print masses

#channels = ["MuMu"]
#masses = [20, 30, 40, 50, 60, 70, 75, 80]
#Bins = ["Bin1"]

for ch in channels:
  for Bin in Bins:
    print ch+"\t"+Bin

    for mass in masses:

      logname = 'Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log'
      lines = open(logname).readlines()
      n_lines = len(lines)

#Signal Eff  0.008370
      line_eff = lines[n_lines-3]
      line_eff_toterr = lines[n_lines-1]

#Stat 9.57 17.64  9.89  -nan  4.05
      line_stat = ""
      for line in lines:
        if "Stat" in line:
            line_stat = line
            break
#Total Systematic 20.64 27.39  30.00  -nan  12.00
      line_syst = ""
      for line in lines:
        if "Total Systematic" in line:
            line_syst = line
            break

      sig_eff = float(line_eff.split()[2])
      sig_yield = float(line_eff_toterr.split()[0])

      if mass==80:
        Wrong = 2.01340
        Correct = 0.4525
        correction = Correct/Wrong;
        sig_yield = sig_yield*correction

      sig_eff_toterr = float(line_eff_toterr.split()[1])-1
      sig_err_stat = float(line_stat.split()[5])*0.01
      sig_err_syst = float(line_syst.split()[6])*0.01

      ## DEBUG ##
      #print str(mass)+"\t"+str(sig_eff)+"\t"+str(sig_eff_toterr)+"\t"+str(sig_err_stat)+"\t"+str(sig_err_syst)
      #print str(sig_eff)+',',
      print str(sig_eff_toterr)+',',
      #print str(sig_yield)+',',

    print ''




