#!/bin/bash
for i in 40 50 60 70 80 90 100 125 150 200 250 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500
for i in 40 50 60 70 80
for i in 90 100 125 150 200 250 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500
do
  root -l -b -q "HNMuMu_"$i".C" &> "log_HNMuMu_"$i".log" &
  root -l -b -q "HNElEl_"$i".C" &> "log_HNElEl_"$i".log" &

  root -l -b -q "Bin2_HNMuMu_"$i".C" &> "log_Bin2_HNMuMu_"$i".log" &
  root -l -b -q "Bin2_HNElEl_"$i".C" &> "log_Bin2_HNElEl_"$i".log" &
done
