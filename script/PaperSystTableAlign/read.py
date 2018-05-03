import os

lines = open('original.txt').readlines()

for line in lines:
  line = line.strip('\n')
  if "underline" in line:
    print line
    continue
  # SM cross section  & --  & $12$--$14$ ($15$--$27$)  & --  & $13$--$18$ ($22$--$41$)  & --  & $12$--$14$ ($16$--$30$) \\
  # -->
  # ['SM cross section  ', ' --  ', ' $12$--$14$ ($15$--$27$)  ', ' --  ', ' $13$--$18$ ($22$--$41$)  ', ' --  ', ' $12$--$14$ ($16$--$30$) \\\\\n']
  words = line.split('&')
  if len(words)<6:
    print line
    continue
  print words[0],
  for i in range(1,6+1):
    word = words[i]
    if "\multirow" in word:
      print "&"+word.replace('\\\\',''),
      continue
    word = word.replace(' ','')
    word = word.replace('\\','')

    if len(word)==0:
      print "&",
      continue

    LowOrHigh = 0
    n_dash = [0,0]
    n_point = [0,0]
    n_number = [0,0]

    target_dash = [2,2]
    target_point = [1,1]
    target_number = [4,4]
    if i==1:
      target_number = [3,4]
    if i==2:
      target_number = [4,4]
    if i==3:
      target_number = [3,4]
    if i==4:
      target_number = [4,4]
    if i==5:
      target_number = [3,4]
    if i==6:
      target_number = [4,4]

    for a in word:
      if a=="(":
        LowOrHigh = 1

      if a=="-":
        n_dash[LowOrHigh] += 1
      elif a==".":
        n_point[LowOrHigh] += 1
      elif a!="$" and a!="(" and a!=")":
        n_number[LowOrHigh] += 1

    toadd = ["\phantom{","\phantom{"]
    for k in range(0,2):
      for j in range(0,target_dash[k]-n_dash[k]):
        toadd[k] = toadd[k]+"-"
      for j in range(0,target_point[k]-n_point[k]):
        toadd[k] = toadd[k]+"."
      for j in range(0,target_number[k]-n_number[k]):
        toadd[k] = toadd[k]+"0"

      toadd[k] = toadd[k]+"}"

    tempword = word.replace("("," (")
    word = toadd[0]+tempword+toadd[1]
    print "&"+word,

  print "\\\\"
