import os

def AddPhantomZero(a,left,right):
  vals = a.split('.')
  val_int = vals[0]
  val_fra = vals[1]

  #print ""
  #print "[AddPhantomZero] a = "+a
  #print "[AddPhantomZero] left-len(val_int) = "+str(left-len(val_int))
  #print "[AddPhantomZero] right-len(val_fra) = "+str(right-len(val_fra))

  for a in range(0, left-len(val_int)):
    val_int = "\\phantom{0}"+val_int

  for a in range(0, right-len(val_fra)):
    val_fra = val_fra+"0"

  return val_int+"."+val_fra


channels = ["ElEl", "MuMu", "MuEl"]
Bins = ["Bin1", "Bin2"]

masses = [50, 200, 1000]
targetV2  = [0.0001, 0.01, 1]

counter_mass=0
for mass in masses:

  print '$'+str(mass)+'$',

  for ch in channels:

    for Bin in Bins:
      lines = open('Outputs_MixingLimit/'+ch+'_'+Bin+'/HN'+ch+'_'+str(mass)+'.log').readlines()
      line_sig = lines[len(lines)-1]
      words = line_sig.split()
      rate = float(words[0])
      rate = rate*targetV2[counter_mass]/0.01

      #print ' & $'+str(round(rate,2))+'$',
      print ' & $'+AddPhantomZero(str(round(rate,2)),2,2)+'$',



  print '\\\\'

  counter_mass=counter_mass+1
