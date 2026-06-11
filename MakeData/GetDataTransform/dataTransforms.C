#define dataTransforms_cxx
#include "dataTransforms.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TMath.h>

void dataTransforms::Loop()
{
//   In a ROOT session, you can do:
//      root> .L dataTransforms.C
//      root> dataTransforms t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // double nClusters = 0; 
   double clusterE_sqrt = 0.; 
   double cluster_CENTER_LAMBDA_sqrt = 0.; 
   double cluster_FIRST_ENG_DENS_sqrt = 0.; 
   double cluster_SECOND_TIME_sqrt = 0.; 
   double cluster_SIGNIFICANCE_sqrt = 0.; 
   double cluster_CENTER_MAG_sqrt = 0.; 

   std::vector<double> clusterE_vec;
   std::vector<double> cluster_CENTER_LAMBDA_vec;
   std::vector<double> cluster_FIRST_ENG_DENS_vec;
   std::vector<double> cluster_SECOND_TIME_vec;
   std::vector<double> cluster_SIGNIFICANCE_vec;
   std::vector<double> cluster_CENTER_MAG_vec;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(clusterE !=0)               { clusterE_vec.push_back(TMath::Log(clusterE)); }
      if(cluster_CENTER_LAMBDA !=0)  { cluster_CENTER_LAMBDA_vec.push_back(TMath::Log(cluster_CENTER_LAMBDA)); }
      if(cluster_FIRST_ENG_DENS !=0) { cluster_FIRST_ENG_DENS_vec.push_back(TMath::Log(cluster_FIRST_ENG_DENS)); }
      if(cluster_SECOND_TIME !=0)    { cluster_SECOND_TIME_vec.push_back(TMath::Log(cluster_SECOND_TIME)); }
      if(cluster_SIGNIFICANCE !=0)   { cluster_SIGNIFICANCE_vec.push_back(TMath::Log(cluster_SIGNIFICANCE)); }
      if(cluster_CENTER_MAG !=0)     { cluster_CENTER_MAG_vec.push_back(TMath::Log(cluster_CENTER_MAG)); }
   
   }

   double clusterE_sum = std::accumulate(clusterE_vec.begin(), clusterE_vec.end(), 0.0);
   double cluster_CENTER_LAMBDA_sum = std::accumulate(cluster_CENTER_LAMBDA_vec.begin(), cluster_CENTER_LAMBDA_vec.end(), 0.0);
   double cluster_FIRST_ENG_DENS_sum = std::accumulate(cluster_FIRST_ENG_DENS_vec.begin(), cluster_FIRST_ENG_DENS_vec.end(), 0.0);
   double cluster_SECOND_TIME_sum = std::accumulate(cluster_SECOND_TIME_vec.begin(), cluster_SECOND_TIME_vec.end(), 0.0);
   double cluster_SIGNIFICANCE_sum = std::accumulate(cluster_SIGNIFICANCE_vec.begin(), cluster_SIGNIFICANCE_vec.end(), 0.0);
   double cluster_CENTER_MAG_sum = std::accumulate(cluster_CENTER_MAG_vec.begin(), cluster_CENTER_MAG_vec.end(), 0.0);

   double clusterE_mean = clusterE_sum / clusterE_vec.size();
   double cluster_CENTER_LAMBDA_mean = cluster_CENTER_LAMBDA_sum / cluster_CENTER_LAMBDA_vec.size();
   double cluster_FIRST_ENG_DENS_mean = cluster_FIRST_ENG_DENS_sum / cluster_FIRST_ENG_DENS_vec.size();
   double cluster_SECOND_TIME_mean = cluster_SECOND_TIME_sum / cluster_SECOND_TIME_vec.size();
   double cluster_SIGNIFICANCE_mean = cluster_SIGNIFICANCE_sum / cluster_SIGNIFICANCE_vec.size();
   double cluster_CENTER_MAG_mean = cluster_CENTER_MAG_sum / cluster_CENTER_MAG_vec.size();


   for (double val : clusterE_vec)               { clusterE_sqrt               += (val - clusterE_mean) * (val - clusterE_mean); }
   for (double val : cluster_CENTER_LAMBDA_vec)  { cluster_CENTER_LAMBDA_sqrt  += (val - cluster_CENTER_LAMBDA_mean) * (val - cluster_CENTER_LAMBDA_mean); }
   for (double val : cluster_FIRST_ENG_DENS_vec) { cluster_FIRST_ENG_DENS_sqrt += (val - cluster_FIRST_ENG_DENS_mean) * (val - cluster_FIRST_ENG_DENS_mean); }
   for (double val : cluster_SECOND_TIME_vec)    { cluster_SECOND_TIME_sqrt    += (val - cluster_SECOND_TIME_mean) * (val - cluster_SECOND_TIME_mean); }
   for (double val : cluster_SIGNIFICANCE_vec)   { cluster_SIGNIFICANCE_sqrt   += (val - cluster_SIGNIFICANCE_mean) * (val - cluster_SIGNIFICANCE_mean); }
   for (double val : cluster_CENTER_MAG_vec)     { cluster_CENTER_MAG_sqrt     += (val - cluster_CENTER_MAG_mean) * (val - cluster_CENTER_MAG_mean); }


   double clusterE_std               = std::sqrt(clusterE_sqrt / clusterE_vec.size());
   double cluster_CENTER_LAMBDA_std  = std::sqrt(cluster_CENTER_LAMBDA_sqrt / cluster_CENTER_LAMBDA_vec.size());
   double cluster_FIRST_ENG_DENS_std = std::sqrt(cluster_FIRST_ENG_DENS_sqrt / cluster_FIRST_ENG_DENS_vec.size());
   double cluster_SECOND_TIME_std    = std::sqrt(cluster_SECOND_TIME_sqrt / cluster_SECOND_TIME_vec.size());
   double cluster_SIGNIFICANCE_std   = std::sqrt(cluster_SIGNIFICANCE_sqrt / cluster_SIGNIFICANCE_vec.size());
   double cluster_CENTER_MAG_std     = std::sqrt(cluster_CENTER_MAG_sqrt / cluster_CENTER_MAG_vec.size());

   std::cout << " clusterE : Mean : " << clusterE_mean << " +/- " << clusterE_std << std::endl;
   std::cout << " cluster_CENTER_LAMBDA : Mean : " << cluster_CENTER_LAMBDA_mean << " +/- " << cluster_CENTER_LAMBDA_std << std::endl;
   std::cout << " cluster_FIRST_ENG_DENS : Mean : " << cluster_FIRST_ENG_DENS_mean << " +/- " << cluster_FIRST_ENG_DENS_std << std::endl;
   std::cout << " cluster_SECOND_TIME : Mean : " << cluster_SECOND_TIME_mean << " +/- " << cluster_SECOND_TIME_std << std::endl;
   std::cout << " cluster_SIGNIFICANCE : Mean : " << cluster_SIGNIFICANCE_mean << " +/- " << cluster_SIGNIFICANCE_std << std::endl;
   std::cout << " cluster_CENTER_MAG : Mean : " << cluster_CENTER_MAG_mean << " +/- " << cluster_CENTER_MAG_std << std::endl;

}
