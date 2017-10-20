import os

masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
masses = [40, 50, 60, 70, 80]
masses = [90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

channel = 'MuMu'

lines = open('numbers.txt').readlines()


for mass in masses:

  index = 0

  for a in range(0,len(lines)):
    if "#### "+str(mass)+" ####" in lines[a]:
      index = a

  out = open('HN'+channel+'_'+str(mass)+'.txt','w')
  for a in range(index+2,len(lines)):
    line = lines[a]
    words = line.split()

    if len(words) == 0:
      break

    out.write(line)

  out.close()
