import os

masses = [1000, 1100, 1200, 1300, 1400, 1500]
width =  [230,  220,  210,  210,  210,  210]

channel = 'MuEl'

counter = 0
for mass in masses:

  filename = 'HN'+channel+'_'+str(mass)+'.txt'
  out = open('tmp_'+filename,'w')

  lines = open(filename).readlines()

  ljj_min = str(mass-width[counter])
  if mass-width[counter]<805:
    ljj_min = "805"
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

