TCanvas *c1 = (TCanvas*)_file0->Get("Nfwdjets");
TPad *pad = (TPad*)c1->GetPrimitive("c1");
TH1D *bkgd = (TH1D*)pad->GetPrimitive("MC_stacked_err");
