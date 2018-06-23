import os

def JSRound(a,forceint,IsThisLumi):
  b = float(a)

  if IsThisLumi:
    return str(round(b,1))

  if forceint:
    return str(int(round(b,0)))

  if b<1:
    if b<0.1:
      return str(round(b,2))
    else:
      return str(round(b,1))
  else:
    return str(int(round(b,0)))

low_mins = open('low_min.txt').readlines()
low_maxs = open('low_max.txt').readlines()
high_mins = open('high_min.txt').readlines()
high_maxs = open('high_max.txt').readlines()

for a in range(0,len(low_mins)):

  low_words_min = low_mins[a].split()
  low_words_max = low_maxs[a].split()
  high_words_min = high_mins[a].split()
  high_words_max = high_maxs[a].split()

  IsThisFirstPDF = False
  IsThisPDF = False
  IsThisLumi = False
  for b in range(0,len(low_words_min)):

    if b == 0:
      word = low_words_min[0]
      word = word.replace('SPACE',' ')
      if "statistical" in word:
        break

      if "Renormalization" in word:
        word = "PDF Scale"
      if word == "PDF ": ## arg.. I added " " to PDF!! arg
        IsThisFirstPDF = True

      if "PDF" in word or "alpha" in word or "Renormalization" in word:
        IsThisPDF = True

      if "luminosity" in word:
        IsThisLumi = True
      print word,
      continue

    low = ''
    high = ''
    if low_words_min[b]=='-' or low_words_max[b]=='-':
      low = '--'
    elif JSRound(low_words_min[b],True,IsThisLumi) == JSRound(low_words_max[b],True,IsThisLumi):
      if float(low_words_max[b]) < 1.:
        low = '0--'+JSRound(low_words_max[b],False,IsThisLumi)+''
      else:
        low = ''+JSRound(low_words_min[b],False,IsThisLumi)+''
    else:
      low = ''+JSRound(low_words_min[b],True,IsThisLumi)+'--'+JSRound(low_words_max[b],True,IsThisLumi)+''

    if high_words_min[b]=='-' or high_words_max[b]=='-':
      high = '--'
    elif JSRound(high_words_min[b],True,IsThisLumi) == JSRound(high_words_max[b],True,IsThisLumi):
      if float(high_words_max[b]) < 1.:
        high = '0--'+JSRound(high_words_max[b],False,IsThisLumi)+''
      else:
        high = ''+JSRound(high_words_min[b],False,IsThisLumi)+''
    else:
      high = ''+JSRound(high_words_min[b],True,IsThisLumi)+'--'+JSRound(high_words_max[b],True,IsThisLumi)+''


    thisval = low+' ('+high+')'
    if low=='--' and high=='--':
      thisval = '--'

      if IsThisPDF:
        if IsThisFirstPDF:
          thisval = '$\multirow{3}{*}{$<$15 ($<$20)}$'
        else:
          thisval = ' '

    print ' & '+thisval,

  print "\\\\"
