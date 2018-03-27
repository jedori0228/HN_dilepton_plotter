import os

channels = ["ElEl", "MuMu", "MuEl"]
channelsForLatex = ["$\Pe\Pe$", "$\mu \mu$", "$\Pe\mu$"]

masses = [50, 500]

for it_ch in range(0,len(channels)):
  ch = channels[it_ch]
  for mass in masses:
    line_Bin1 = open('Outputs_MixingLimit/'+ch+'_Bin1/HN'+ch+'_'+str(mass)+'.log').readlines()
    line_Bin2 = open('Outputs_MixingLimit/'+ch+'_Bin2/HN'+ch+'_'+str(mass)+'.log').readlines()

    index_totsyst = 0
    for it_line in range(0,len(line_Bin1)):
      if "Total Systematic" in line_Bin1[it_line]:
        index_totsyst = it_line
        break
    words_systs_Bin1 = line_Bin1[index_totsyst].split()

    index_totsyst = 0
    for it_line in range(0,len(line_Bin2)):
      if "Total Systematic" in line_Bin2[it_line]:
        index_totsyst = it_line
        break
    words_systs_Bin2 = line_Bin2[index_totsyst].split()

    ##########
    ## Bin1 ##
    ##########

    syst_prompt_Bin1 = 0.01*float(words_systs_Bin1[3])
    syst_fake_Bin1 = 0.01*float(words_systs_Bin1[4])
    syst_cf_Bin1 = 0.
    if ch=="ElEl":
      syst_cf_Bin1 = 0.01*float(words_systs_Bin1[5])

    prompt_Bin1 = float(line_Bin1[index_totsyst+3].split()[2])
    fake_Bin1 = float(line_Bin1[index_totsyst+4].split()[2])
    cf_Bin1 = float(line_Bin1[index_totsyst+5].split()[2])

    totalsyst_Bin1 = 0.
    if prompt_Bin1!=0:
      totalsyst_Bin1 += syst_prompt_Bin1*prompt_Bin1
    if fake_Bin1!=0:
      totalsyst_Bin1 += syst_fake_Bin1*fake_Bin1
    if cf_Bin1!=0:
      totalsyst_Bin1 += syst_cf_Bin1*cf_Bin1

    relsyst_prompt_Bin1 = '$'+str(round(100.*syst_prompt_Bin1*prompt_Bin1/totalsyst_Bin1,1))+'$'
    relsyst_fake_Bin1 = '$'+str(round(100.*syst_fake_Bin1*fake_Bin1/totalsyst_Bin1,1))+'$'
    relsyst_cf_Bin1 = "--"
    if ch=="ElEl":
      relsyst_cf_Bin1 = '$'+str(round(100.*syst_cf_Bin1*cf_Bin1/totalsyst_Bin1,1))+'$'

    if prompt_Bin1==0.:
      relsyst_prompt_Bin1 = '$0$'
    if fake_Bin1==0.:
      relsyst_fake_Bin1 = '$0$'
    if cf_Bin1==0. and ch=="ElEl":
      relsyst_cf_Bin1 = '$0$'

    #print str(prompt_Bin1)+'\t'+str(fake_Bin1)+'\t'+str(cf_Bin1)
    #print str(syst_prompt_Bin1)+'\t'+str(syst_fake_Bin1)+'\t'+str(syst_fake_Bin1)
    #print totalsyst_Bin1
    #print '  '+relsyst_prompt_Bin1+'\t'+relsyst_fake_Bin1+'\t'+relsyst_cf_Bin1
    #continue

    ##########
    ## Bin2 ##
    ##########

    syst_prompt_Bin2 = 0.01*float(words_systs_Bin2[3])
    syst_fake_Bin2 = 0.01*float(words_systs_Bin2[4])
    syst_cf_Bin2 = 0.
    if ch=="ElEl":
      syst_cf_Bin2 = 0.01*float(words_systs_Bin2[5])

    prompt_Bin2 = float(line_Bin2[index_totsyst+3].split()[2])
    fake_Bin2 = float(line_Bin2[index_totsyst+4].split()[2])
    cf_Bin2 = float(line_Bin2[index_totsyst+5].split()[2])

    totalsyst_Bin2 = 0.
    if prompt_Bin2!=0:
      totalsyst_Bin2 += syst_prompt_Bin2*prompt_Bin2
    if fake_Bin2!=0:
      totalsyst_Bin2 += syst_fake_Bin2*fake_Bin2
    if cf_Bin2!=0:
      totalsyst_Bin2 += syst_cf_Bin2*cf_Bin2

    relsyst_prompt_Bin2 = '$'+str(round(100.*syst_prompt_Bin2*prompt_Bin2/totalsyst_Bin2,1))+'$'
    relsyst_fake_Bin2 = '$'+str(round(100.*syst_fake_Bin2*fake_Bin2/totalsyst_Bin2,1))+'$'
    relsyst_cf_Bin2 = "--"
    if ch=="ElEl":
      relsyst_cf_Bin2 = '$'+str(round(100.*syst_cf_Bin2*cf_Bin2/totalsyst_Bin2,1))+'$'

    if prompt_Bin2==0.:
      relsyst_prompt_Bin2 = '$0$'
    if fake_Bin2==0.:
      relsyst_fake_Bin2 = '$0$'
    if cf_Bin2==0. and ch=="ElEl":
      relsyst_cf_Bin2 = '$0$'

    out = channelsForLatex[it_ch]+' & '+'$'+str(mass)+'$'
    out += ' & '+relsyst_prompt_Bin1+' ('+relsyst_prompt_Bin2+')'
    out += ' & '+relsyst_fake_Bin1+' ('+relsyst_fake_Bin2+')'
    out += ' & '+relsyst_cf_Bin1+' ('+relsyst_cf_Bin2+')'
    out += ' \\\\'
    

    print out

  print '\\hline'

#$\mu\mu$   & 100 & 0.4 [0.4] & 99.4 [99.4] & 0.2 [0.2]   \\

#Total Systematic 18.64 20.39  30.00  -nan  11.40

