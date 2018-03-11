import os

channels = ["MuMu", "ElEl", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150, 200, 250, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]

for ch in channels:
  for Bin in Bins:
    os.system('mkdir -p Cards_'+ch+"_"+Bin)

lines_WhichCardsToUse = open('WhichCardsToUse.txt').readlines()
for line in lines_WhichCardsToUse:
  words = line.split()
  ## Copy Low Mass Card
  cmd = 'cp ../'+words[1]+'/*HN*.txt '+words[0]
  os.system(cmd)
  cmd = 'cp ../'+words[2]+'/*HN*.txt '+words[0]
  os.system(cmd)
