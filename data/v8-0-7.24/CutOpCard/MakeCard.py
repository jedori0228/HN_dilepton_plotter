import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [1000]

for mass in masses:
  out = open('HNElEl_'+str(mass)+'.txt','w')

  if mass <= 80:
    print>>out,'''m_ll < 150 100  5
m_lljj_lljjWclosest < 350 100 250'''

  else:
    print>>out,'''m_jj_jjWclosest  < 110 80  6
m_jj_jjWclosest  > 50 80  6
MET2ST  < 15 0  15
m_Leadljj_jjWclosest	>	{0}	{1}	{2}'''.format("0" ,str(mass), "10")


  out.close()
