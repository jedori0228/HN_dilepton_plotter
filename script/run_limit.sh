#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9
do
  echo $i

  ## Asymp
  #root -l -b -q "src/HiggsCombindedLimit.C("$i") "
  #root -l -b -q "src/HiggsCombindedLimit_Xsec.C("$i") "

  ## Full CLs
  root -l -b -q "src/HiggsCombindedLimit.C("$i",\"\",0,true) "
  root -l -b -q "src/HiggsCombindedLimit_Xsec.C("$i") "

  ## TEMP
  #root -l -b -q "src/HiggsCombindedLimit.C("$i",\"180223_BeforeOverlap\") "

done



for i in 1 2 3
do

  for j in 0 1
  do
    echo $j
    root -l -b -q "src/HiggsCombindedLimit_AllChannel.C($i,$j)"

  done


done
