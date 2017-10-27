import os
import math

masses = [300, 600, 800, 1000, 1200]
for mass in masses:
  lines_sch = open('log_HNMuMu_'+str(mass)+'.log').readlines()
  lines_vbf = open('log_HNMuMu_'+str(mass)+'_VBF.log').readlines()

  words_sch = lines_sch[len(lines_sch)-1].split()
  words_vbf = lines_vbf[len(lines_vbf)-1].split()


  y_sch = float(words_sch[0])
  e_sch = float(words_sch[1])
  e_sch = y_sch*(e_sch-1)

  print words_vbf
  y_vbf = float(words_vbf[0])
  e_vbf = float(words_vbf[1])
  e_vbf = y_vbf*(e_vbf-1)

  s_vbf = y_sch+y_sch
  e_sch = math.sqrt(e_sch*e_sch+e_vbf*e_vbf)
  e_sch = 1+e_sch/s_vbf

  print words_sch
  print words_vbf
  print str(s_vbf)+'\t'+str(e_sch)
