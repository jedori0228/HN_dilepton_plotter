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

scpdir = '/data7/Users/jskim/CMSSW_7_4_7/src/HiggsAnalysis/CombinedLimit/data/hn_di/'

pwd = os.getcwd()

for d in dirs:
  os.chdir(d+'/Cycles/')
  os.system('python make_datacard.py')
  if "High" in d or "MuEl" in d:
    os.system('python make_datacard_VBF.py')
  os.chdir('Datacards')

  channel = ""
  if "MuMu" in d:
    channel = "DiMuon"
  elif "ElEl" in d:
    channel = "DiElectron"
  elif "MuEl" in d:
    channel = "EMu"

  if "Bin2" in d:
    channel = channel+"_Bin2"

  os.system('ls -alh *')
  os.system('scp *.txt jskim@147.47.242.34:'+scpdir+channel)

  os.chdir(pwd)
