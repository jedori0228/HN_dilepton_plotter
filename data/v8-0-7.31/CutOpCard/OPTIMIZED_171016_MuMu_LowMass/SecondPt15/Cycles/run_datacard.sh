#!/bin/bash
for i in 40 50 60 70 80
do
  #root -l -b -q "HNElEl_"$i".C" &> "log_HNElEl_"$i".log" &
  root -l -b -q "HNMuMu_"$i".C" &> "log_HNMuMu_"$i".log" &
done
