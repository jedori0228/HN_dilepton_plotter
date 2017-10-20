import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40, 50, 60, 70, 80]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

channel = "MuMu"

dirname = 'OptimizedCutCard'
os.system('mkdir -p '+dirname)

#
#[CutInfo::PrintCutInfo] leadingLepton_Pt  < 70
#[CutInfo::PrintCutInfo] m_SubLeadljj_lljjWclosest < 100
#[CutInfo::PrintCutInfo] m_ll  < 100
#[CutInfo::PrintCutInfo] m_lljj_lljjWclosest < 126
#[CutInfo::PrintCutInfo] secondLepton_Pt < 45
#CF  0.72828 +- 0.145995
#Fake  10.049 +- 3.20922
#Prompt  4.92607 +- 1.37597
#=> total bkg = 15.7033
#Signal  Yield Efficiency  Efficiency@Presel Punzi
#HNElEl_40 1334.31 0.0018684 0.254694  0.000297342

for mass in masses:

  lines = open('log_'+str(mass)+'.log').readlines()

  lastline_index = 0
  for a in range(0, len(lines)):
    b = len(lines)-1-a
    if "HN" in lines[b]:
      lastline_index = b
      break

  LINE_total_bkg = lines[lastline_index-2].strip('\n')
  total_bkg = LINE_total_bkg.replace('=> total bkg = ','')

  LINE_signal_rate = lines[lastline_index].strip('\n')
  punzi = LINE_signal_rate.split()[4]
  sigeff = LINE_signal_rate.split()[2]

  opcard = open(dirname+'/HN'+channel+'_'+str(mass)+'.txt','w')

  for a in range(0,len(lines)):
    b = len(lines)-1-a

    line = lines[b]

    if "FINISHED" in line or "TIME STAMP" in line:
      break

    if "CutInfo::PrintCutInfo" in lines[b]:
      started = True
      line = line.replace('[CutInfo::PrintCutInfo] ','')
      line = line.replace('\t',' ')
      value = float(line.split()[2])

      Noneside = 1
      dx = 0
      newline = line.split()[0]+' '+line.split()[1]+' '+str(value-Noneside*dx)+' '+str(value+Noneside*dx)+' '+str(1)+'\n'
      opcard.write(newline)

      if mass > 80:

        if "m_SubLeadljj_jjWclosest" in line:

          start = value
          diff = mass - value
          #print str(mass)+"\t"+str(diff)
          #opcard.write("m_SubLeadljj_lljjWclosest < "++" "++" 10")

        if "m_Leadljj_lljjWclosest" in line:

          start = value
          diff = mass - value
          #print str(mass)+"\t"+str(diff)
          #opcard.write("m_SubLeadljj_lljjWclosest < "++" "++" 10")

  if mass < 80:

    a = 1

  else:
    LLJJ_start = mass*0.5
    LLJJ_end = mass*1.5

    #opcard.write("m_lljj_jjWclosest > "+str(LLJJ_start)+" "+str(LLJJ_end)+" "+"10\n")


  opcard.write("##punzi\t"+punzi+"\n")
  opcard.write("##sigeff\t"+sigeff+"\n")
  opcard.write("##bkgd\t"+total_bkg)

  opcard.close()










