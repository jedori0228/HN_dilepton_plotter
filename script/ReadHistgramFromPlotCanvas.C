TCanvas *c1 = (TCanvas*)_file0->Get("Nevents");
TPad *pad = (TPad*)c1->GetPrimitive("c1");
TH1D *data = (TH1D*)pad->GetPrimitive("Nevents_DiMuon_ThreeLepton_WZ_NotAllSameFlavour_data");
TH1D *bkgd = (TH1D*)pad->GetPrimitive("MC_stacked_allerr");



