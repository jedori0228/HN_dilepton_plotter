void run(TString filename) {

   //==== File of Original Tree
   TFile *oldfile = new TFile("../"+filename);
   //==== Name of Original Tree
   TTree *oldtree = (TTree*)oldfile->Get("Ntp_DiElectron_Preselection_SS");
   Long64_t nentries = oldtree->GetEntries();

   //==== Read Skimming variables
   double Nfatjets;
   oldtree->SetBranchAddress("Nfatjets",&Nfatjets);

   //==== File for New Tree
   TFile *newfile = new TFile(filename,"recreate");
   //==== New Tree. Clone from Original Tree
   TTree *newtree = oldtree->CloneTree(0);
   //==== New Tree Name
   newtree->SetName("Ntp_DiElectron_Preselection_Inclusive1fatjets_SS");

   //==== Loop over Original Tree event
   for(Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);

      //==== Skimming
      if(Nfatjets==0) continue;

      //==== If pass, fill New Tree
      newtree->Fill();

   }

   //==== Save
   newtree->AutoSave();

   //==== If you have extra histograms to save...
   vector<TString> preselYieldToSave = {
     //==== To Get NoCut Signal Yields
     "Cutflow_DiElectron_NoCut",
     //==== To Get Preselection Signal Yeidls
     "Nevents_DiElectron_Preselection_SS",
     "Nevents_DiElectron_Preselection_Inclusive2jets_SS",
     "Nevents_DiElectron_Preselection_Inclusive1fatjets_SS",
     "Nevents_DiElectron_Preselection_Inclusive2jets_mjj50to110_SS"
   };

   //==== I only do this only for Signal
   if(filename.Contains("HN")){
     newfile->cd();
     for(unsigned int i=0; i<preselYieldToSave.size(); i++){
       TH1D *hist = (TH1D*)oldfile->Get(preselYieldToSave.at(i));
       hist->Write();
     }
   }

   //==== Done
   delete oldfile;
   delete newfile;
}

