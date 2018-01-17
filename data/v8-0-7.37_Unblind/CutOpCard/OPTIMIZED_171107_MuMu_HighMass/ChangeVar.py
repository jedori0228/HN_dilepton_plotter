import os

masses = [600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]
width =  [200, 225, 260, 290,  320, 350,  400,  425,  450,  500]

channel = 'MuMu'

counter = 0
for mass in masses:

  filename = 'HN'+channel+'_'+str(mass)+'.txt'
  out = open('tmp_'+filename,'w')

  lines = open(filename).readlines()

  ljj_min = str(mass-width[counter])
  ljj_max = str(mass+width[counter])

  for line in lines:
    if ("ljj" in line) and ("|>" in line):
      out.write('ljj |> '+ljj_min+' '+ljj_min+' 1\n')
    elif ("ljj" in line) and ("|<" in line):
      out.write('ljj |< '+ljj_max+' '+ljj_max+' 1\n')
    else:
      out.write(line)

  os.system('mv '+'tmp_'+filename+' '+filename)

  counter = counter+1

