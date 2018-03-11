#!/bin/bash
for i in 90 100 125 150 200 250 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500
do
  root -l -b -q "Bin2_HNMuEl_"$i".C" &> "log_Bin2_HNMuEl_"$i".log" &
done
