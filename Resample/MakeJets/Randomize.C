#define Randomize_cxx
#include "Randomize.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <random>
#include <vector>
#include <iostream>

void Randomize::Loop(TString JZSlice){

   if (fChain == 0) return;

   TFile* ftrain = TFile::Open("/data/jmsardain/CalibPU/datasets/pu/JetTree_"+JZSlice+"_train.root", "RECREATE");
   TFile* ftest  = TFile::Open("/data/jmsardain/CalibPU/datasets/pu/JetTree_"+JZSlice+"_test.root", "RECREATE");


   ftrain->cd();
   TTree* ttrain = fChain->CloneTree(0);

   ftest->cd();
   TTree* ttest  = fChain->CloneTree(0);

   Long64_t nentries = fChain->GetEntriesFast();

   std::map<std::pair<int, int>, bool> jetClusters;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      std::pair<int, int> key{eventNumber, jetCnt};
      jetClusters[key] = false; 
   }

   std::vector<std::pair<int,int>> keys;
   keys.reserve(jetClusters.size());

   for (const auto& kv : jetClusters) {
      keys.push_back(kv.first);
   }

   std::mt19937 rng(123456);
   std::shuffle(keys.begin(), keys.end(), rng);

   size_t nTrain = static_cast<size_t>(0.8 * keys.size());
   for (size_t i = 0; i < nTrain; ++i) {
      jetClusters[keys[i]] = true;   // true = train
   }

   for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
      LoadTree(jentry);
      fChain->GetEntry(jentry);

      std::pair<int,int> key{eventNumber, jetCnt};

      if (jetClusters[key]) {
         ttrain->Fill();
      } else {
         ttest->Fill();
      }
   }

   std::cout << " Train: " << ttrain->GetEntries() << std::endl;
   std::cout << " Test: " << ttest->GetEntries() << std::endl;
   
   ftrain->cd();
   ttrain->Write();

   ftest->cd();
   ttest->Write();

   ftrain->Close();
   ftest->Close();

}
