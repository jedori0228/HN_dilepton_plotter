#!/bin/bash
for i in 40 50 60 70 80
do
  root -l -b -q "Bin2_HNMuEl_"$i".C" &> "log_Bin2_HNMuEl_"$i".log" &
done
