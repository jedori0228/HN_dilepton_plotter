import os,math

channels = ["MuMu", "ElEl", "MuEl"]
masses = [40, 50, 60, 70, 80, 90, 100, 125, 150, 175, 200, 250, 300, 350, 400, 500]
xsecs = [1516, 1071.1, 607.7, 211.96, 19.07, 7.1047, 3.5618, 1.0767, 0.4594, 0.23266, 0.13127, 0.050928, 0.023214, 0.011705, 0.006332, 0.002154]

effs = []
efferrs = []
bkgs = []
bkgerrs = []
obss = []

MuMu_effs = [
0.69, 0.80, 0.64, 0.26, 1.15,
1.15, 4.65, 10.85, 13.43, 14.81, 15.83, 17.20, 15.22, 15.82, 15.38, 12.09,
]
MuMu_efferrs = [
0.03, 0.04, 0.03, 0.02, 0.03,
0.05, 0.09, 0.14, 0.15, 0.16, 0.16, 0.17, 0.16, 0.16, 0.16, 0.15,
]
MuMu_bkgs = [
9.75, 9.75, 9.75, 9.75, 9.75,
21.33, 20.40, 13.76, 9.91, 6.02, 4.23, 2.50, 0.97, 0.97, 0.97, 0.97,
]
MuMu_bkgstaterrs = [
0.97, 0.97, 0.97, 0.97, 0.97,
1.31, 1.22, 0.94, 0.75, 0.59, 0.49, 0.33, 0.25, 0.25, 0.25, 0.25,
]
MuMu_bkgsysterrs = [
1.98, 1.98, 1.98, 1.98, 1.98,
3.90, 3.67, 2.23, 1.57, 0.95, 0.69, 0.40, 0.17, 0.17, 0.17, 0.17,
]
MuMu_bkgerrs = []
for a in range(0,len(MuMu_bkgstaterrs)):
  stat = MuMu_bkgstaterrs[a]
  syst = MuMu_bkgsysterrs[a]
  MuMu_bkgerrs.append( math.sqrt(stat*stat+syst*syst) )
MuMu_obss = [
7, 7, 7, 7, 7,
19, 19, 8, 7, 7, 5, 3, 1, 1, 1, 1,
]
effs.append(MuMu_effs)
efferrs.append(MuMu_efferrs)
bkgs.append(MuMu_bkgs)
bkgerrs.append(MuMu_bkgerrs)
obss.append(MuMu_obss)

ElEl_effs = [
0.190025, 0.264662, 0.222238, 0.0875306, 0.321267, 0.463891, 1.89973, 4.19205, 6.52288, 6.39283, 8.36056, 10.5907, 13.9562, 16.0686, 17.1553, 16.6181
]
ElEl_efferrs = [
0.0322451, 0.0477451, 0.0443886, 0.0179594, 0.0500012, 0.0608811, 0.216357, 0.400087, 0.556503, 0.536408, 0.696483, 0.884989, 1.20761, 1.41723, 1.56753, 1.58687
]
ElEl_bkgs = [
8.56157, 8.56157, 8.56157, 8.56157, 8.56157, 17.8148, 15.3239, 11.017, 9.85018, 4.038, 4.26222, 3.77545, 2.59382, 2.42003, 2.42003, 2.42003
]
ElEl_bkgerrs = [
3.60522, 3.60522, 3.60522, 3.60522, 3.60522, 5.81128, 4.93185, 2.83889, 2.31493, 0.814223, 1.56005, 1.57871, 1.39912, 1.39658, 1.39658, 1.39658, 0, 0, 0, 0,
]
ElEl_obss = [
11, 11, 11, 11, 11, 23, 23, 11, 7, 3, 3, 4, 4, 4, 4, 4
]
effs.append(ElEl_effs)
efferrs.append(ElEl_efferrs)
bkgs.append(ElEl_bkgs)
bkgerrs.append(ElEl_bkgerrs)
obss.append(ElEl_obss)

MuEl_effs = [
0.394055, 0.46411, 0.381043, 0.13734, 0.575442, 0.567942, 1.71124, 5.24423, 9.54012, 10.8635, 11.7892, 15.6322, 16.0046, 16.1052, 16.2037, 14.1089
]
MuEl_efferrs = [
0.0651038, 0.0757566, 0.0640889, 0.0186074, 0.069438, 0.0490407, 0.142773, 0.371712, 0.60337, 0.63577, 0.678878, 0.900176, 0.997049, 1.07989, 1.13299, 1.04072
]
MuEl_bkgs = [
33.7, 33.7, 33.7, 33.7, 25.27, 20.05, 14.82, 12.302, 13.846, 9.28, 6.21, 4.74, 2.17, 1.63, 1.56, 1.56
]
MuEl_bkgerrs = [
11.1429, 11.1429, 11.1429, 11.1429, 6.56557, 5.09143, 3.30348, 2.48637, 2.72097, 1.84735, 1.3054, 0.997194, 0.557465, 0.48232, 0.483967, 0.488177, 0, 0, 0, 0,
]
MuEl_obss = [
33, 33, 33, 33, 29, 25, 20, 17, 16, 11, 7, 7, 4, 4, 4, 4
]
effs.append(MuEl_effs)
efferrs.append(MuEl_efferrs)
bkgs.append(MuEl_bkgs)
bkgerrs.append(MuEl_bkgerrs)
obss.append(MuEl_obss)


for a in range(0,len(channels)):
  ch = channels[a]
  carddir = 'Outputs_8TeVLimitCard/'+ch
  os.system('mkdir -p '+carddir)

  for b in range(0,len(masses)):
    mass = masses[b]
    out = open(carddir+'/HN'+ch+'_'+str(mass)+'.txt','w')

    obs = (obss[a])[b]
    exp = (bkgs[a])[b]
    sigrate = 19700.*xsecs[b]*(0.01* (effs[a])[b])*0.01 # last 0.01 for mixing2 0.01

    if mass <= 60:
      sigrate *= 0.01
    elif mass <= 100:
      sigrate *= 0.1
    elif mass <= 300:
      sigrate *= 1
    elif mass <= 700:
      sigrate *= 10
    else:
      sigrate *= 100

    sigrate *= 1.34

    #if ch=="MuEl":
    #  sigrate *= 2.

    bkgerr = 1.+(bkgerrs[a])[b]/(bkgs[a])[b]
    sigerr = 1.+(efferrs[a])[b]/(effs[a])[b]

    print >> out,'''imax 1  number of channels
jmax 1  number of backgrounds
kmax 1  number of nuisance parameters (sources of systematical uncertainties)
------------
# we have just one channel, in which we observe 0 events
bin 1
observation {1}
------------
# now we list the expected events for signal and all backgrounds in that bin
# the second 'process' line must have a positive number for backgrounds, and 0 for signal
# then we list the independent sources of uncertainties, and give their effect (syst. error)
# on each process and bin
bin 1 1
process bkgd  {0}
process 1 0
rate  {2} {3}
------------
err  lnN {4}  {5}
'''.format('HN'+str(mass), str(obs), str(exp), str(round(sigrate,4)), str(round(bkgerr,4)), str(round(sigerr,4)))

    out.close()

    #print 'combine -M HybridNew --frequentist --testStat LHC '+ch+'/HN'+ch+'_'+str(mass)+'.txt -n HN'+ch+'_'+str(mass)+' &> Outputs_Tool/'+ch+'/log_HN'+ch+'_'+str(mass)+'.log &'
    #print 'combine -M HybridNew --frequentist --testStat LHC '+ch+'_Combined/HN'+ch+'_'+str(mass)+'.txt -n HN'+ch+'_'+str(mass)+' &> Outputs_Tool/'+ch+'_Combined/log_HN'+ch+'_'+str(mass)+'.log &'

    #print 'combine -M Asymptotic '+ch+'/HN'+ch+'_'+str(mass)+'.txt -n HN'+ch+'_'+str(mass)+' &> Outputs_Tool/'+ch+'/log_HN'+ch+'_'+str(mass)+'.log &'
    print 'combine -M Asymptotic '+ch+'_Combined/HN'+ch+'_'+str(mass)+'.txt -n HN'+ch+'_'+str(mass)+' &> Outputs_Tool/'+ch+'_Combined/log_HN'+ch+'_'+str(mass)+'.log &'





