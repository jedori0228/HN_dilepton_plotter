#!/bin/bash
for i in 300 600 800 1000 1200
do
  root -l -b -q "HNMuEl_"$i"_VBF.C" &> "log_HNMuEl_"$i"_VBF.log" &
done
