#!/bin/bash
for i in 40 50 60 70 80
do
  root -l -b -q "HNMuEl_"$i".C" &> "log_HNMuEl_"$i".log" &
done
