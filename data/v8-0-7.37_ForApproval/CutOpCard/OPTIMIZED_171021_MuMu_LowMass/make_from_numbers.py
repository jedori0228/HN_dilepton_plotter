import os

masses = [40, 50, 60, 70, 80]

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

  #### If you want to add something ####
  out.write("secondLepton_Pt\t>\t15\t15\t1\n")

  out.close()
