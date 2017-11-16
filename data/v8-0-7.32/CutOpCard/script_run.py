import os

dirs = [
'OPTIMIZED_171021_MuMu_LowMass',
'OPTIMIZED_171021_MuMu_LowMass_Bin2',
'OPTIMIZED_171107_MuMu_HighMass',
'OPTIMIZED_171108_MuMu_HighMass_Bin2',

'OPTIMIZED_171021_ElEl_LowMass',
'OPTIMIZED_171021_ElEl_LowMass_Bin2',
'OPTIMIZED_171107_ElEl_HighMass',
'OPTIMIZED_171108_ElEl_HighMass_Bin2',

'OPTIMIZED_171030_MuEl',
'OPTIMIZED_171030_MuEl_Bin2',
'OPTIMIZED_171107_MuEl_HighMass',
'OPTIMIZED_171108_MuEl_HighMass_Bin2',
]

out = open('script_run.sh','w')

out.write("#!/bin/bash\n")

for d in dirs:

  out.write('## '+d+' ##\n')
  out.write('cd '+d+'/Cycles/\n')
  out.write('source run.sh\n')
  if "High" in d:
    out.write('sleep 60\n')
    out.write('source runvbf.sh\n')
    out.write('sleep 60\n')
  else:
    out.write('sleep 15\n')

  out.write('cd -\n')

  out.write('\n')

