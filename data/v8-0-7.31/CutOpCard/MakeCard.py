import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

dirname = "./171010_Exact_8TeV_Cuts/"
os.system('mkdir -p '+dirname)

for mass in masses:
  out = open(dirname+'HNElEl_'+str(mass)+'.txt','w')

  if mass <= 80:
    print>>out,'''Nbjets_nolepveto == 0 0 1
PFMET < 30 30 1
m_jj_lljjWclosest < 120 120 1
m_lljj_lljjWclosest > 80 80 1
m_lljj_lljjWclosest < 160 160 1
m_SubLeadljj_lljjWclosest < 120 120 1
m_ll < 60 60  1'''

  elif mass <= 200:
    print>>out,'''Nbjets_nolepveto == 0 0 1
m_ll > 15 15  1
PFMET < 35 35 1
m_ll > 50 50  1
m_ll < 110 110  1
m_lljj_jjWclosest > 120 120 1
leadingLepton_Pt > 20 20 1
secondLepton_Pt > 15 15 1
SubLeadljj_jjWclosest > 60 60 1
SubLeadljj_jjWclosest < 120 120 1'''

  elif mass <= 500:
    print>>out,'''Nbjets_nolepveto == 0 0 1
m_ll > 15 15  1
PFMET < 35 35 1
m_ll > 50 50  1
m_ll < 110 110  1
m_lljj_jjWclosest > 300 300 1
leadingLepton_Pt > 120 120 1
secondLepton_Pt > 40 40 1'''

  else:
    print>>out,'''Nbjets_nolepveto == 0 0 1
m_ll > 15 15  1
PFMET < 35 35 1
m_ll > 50 50  1
m_ll < 110 110  1
m_lljj_jjWclosest > 360 360 1
leadingLepton_Pt > 120 120 1
secondLepton_Pt > 40 40 1'''


  out.close()
