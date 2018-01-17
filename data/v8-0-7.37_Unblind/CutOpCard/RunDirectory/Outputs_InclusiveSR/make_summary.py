import os

mins = open('min.txt').readlines()
maxs = open('max.txt').readlines()

for a in range(0,len(mins)):

  words_min = mins[a].split()
  words_max = maxs[a].split()

  for b in range(0,len(words_min)):
    if b != 0:
      print '\t',

    if words_min[b]=='-' or words_max[b]=='-':
      print '-',
    elif words_min[b] == words_max[b]:
      print words_min[b],
    else:
      print words_min[b]+'-'+words_max[b],
  print ""
