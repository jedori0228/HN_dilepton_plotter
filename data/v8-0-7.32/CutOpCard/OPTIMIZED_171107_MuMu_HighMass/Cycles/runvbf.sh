#!/bin/bash
for i in 300 600 800 1000 1200
do
  root -l -b -q "HNMuMu_"$i"_VBF.C" &> "log_HNMuMu_"$i"_VBF.log" &
done
