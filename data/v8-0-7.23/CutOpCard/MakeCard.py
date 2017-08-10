import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40]

for mass in masses:
  out = open('HNElEl_'+str(mass)+'.txt','w')

  if mass <= 80:
    print>>out,'''leadingLepton_Pt  < 150 105  5
secondLepton_Pt  < 80 40  5
PFMET < 60 30  6
ST  < 480 380 10
MET2ST  < 20  5  5
m_lljj_lljjWclosest < 350 250 10'''

  elif mass <= 200:
    print>>out,'''m_jj_jjWclosest  < 110 80  6
m_jj_jjWclosest  > 50 80  6
PFMET < 60 30  6
ST  < 480 380 10
MET2ST  < 20  5  5
m_lljj_lljjWclosest < 350 250 10'''


  out.close()
