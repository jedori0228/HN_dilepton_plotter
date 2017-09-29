import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

dirname = "./170920_DiElectron_8TeV/"
os.system('mkdir -p '+dirname)

for mass in masses:
  out = open(dirname+'HNElEl_'+str(mass)+'.txt','w')

  if mass <= 80:
    print>>out,'''m_ll < 60 60  1
m_SubLeadljj_lljjWclosest < 120 120 1
m_lljj_lljjWclosest < 160 160 1
m_lljj_lljjWclosest > 80 80 1'''

  elif mass <= 200:
    print>>out,'''m_lljj_jjWclosest > 100 150 1
leadingLepton_Pt > 20 20 1
secondLepton_Pt > 15 15 1
m_SubLeadljj_lljjWclosest > 100 150 1
m_SubLeadljj_lljjWclosest < 100 150 1'''

  else:
    print>>out,'''m_lljj_jjWclosest > 100 150 1
leadingLepton_Pt > 20 20 1
secondLepton_Pt > 15 15 1'''


  out.close()
