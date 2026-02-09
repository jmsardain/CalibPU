#define GetValue_cxx
#include "GetValue.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TMath.h>

void GetValue::Loop(){

   if (fChain == 0) return;

   double nClusters = 0; 
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
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      for(unsigned int i=0; i<clusterE->size(); i++){

         if(clusterE->at(i)!=0)               { clusterE_vec.push_back(TMath::Log(clusterE->at(i))); }
         if(cluster_CENTER_LAMBDA->at(i)!=0)  { cluster_CENTER_LAMBDA_vec.push_back(TMath::Log(cluster_CENTER_LAMBDA->at(i))); }
         if(cluster_FIRST_ENG_DENS->at(i)!=0) { cluster_FIRST_ENG_DENS_vec.push_back(TMath::Log(cluster_FIRST_ENG_DENS->at(i))); }
         if(cluster_SECOND_TIME->at(i)!=0)    { cluster_SECOND_TIME_vec.push_back(TMath::Log(cluster_SECOND_TIME->at(i))); }
         if(cluster_SIGNIFICANCE->at(i)!=0)   { cluster_SIGNIFICANCE_vec.push_back(TMath::Log(cluster_SIGNIFICANCE->at(i))); }
         if(cluster_CENTER_MAG->at(i)!=0)     { cluster_CENTER_MAG_vec.push_back(TMath::Log(cluster_CENTER_MAG->at(i))); }
      }
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

   // for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //    Long64_t ientry = LoadTree(jentry);
   //    if (ientry < 0) break;
   //    nb = fChain->GetEntry(jentry);   nbytes += nb;
   //    // if (Cut(ientry) < 0) continue;

   //    for(unsigned int i=0; i<clusterE->size(); i++){
   //       nClusters++;
   //       clusterE_sum += TMath::Log(clusterE->at(i));
   //       cluster_CENTER_LAMBDA_sum += TMath::Log(cluster_CENTER_LAMBDA->at(i));
   //       cluster_FIRST_ENG_DENS_sum += TMath::Log(cluster_FIRST_ENG_DENS->at(i));
   //       cluster_SECOND_TIME_sum += TMath::Log(cluster_SECOND_TIME->at(i));
   //       cluster_SIGNIFICANCE_sum += TMath::Log(cluster_SIGNIFICANCE->at(i));
   //       cluster_CENTER_MAG_sum += TMath::Log(cluster_CENTER_MAG->at(i));
   //    }

   // }

   // double clusterE_mean = clusterE_sum / nClusters; 
   // double cluster_CENTER_LAMBDA_mean = cluster_CENTER_LAMBDA_sum / nClusters; 
   // double cluster_FIRST_ENG_DENS_mean = cluster_FIRST_ENG_DENS_sum / nClusters; 
   // double cluster_SECOND_TIME_mean = cluster_SECOND_TIME_sum / nClusters; 
   // double cluster_SIGNIFICANCE_mean = cluster_SIGNIFICANCE_sum / nClusters; 
   // double cluster_CENTER_MAG_mean = cluster_CENTER_MAG_sum / nClusters; 



   // for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //    Long64_t ientry = LoadTree(jentry);
   //    if (ientry < 0) break;
   //    nb = fChain->GetEntry(jentry);   nbytes += nb;
   //    // if (Cut(ientry) < 0) continue;

   //    for(unsigned int i=0; i<clusterE->size(); i++){
   //       clusterE_sqrt += (TMath::Log(clusterE->at(i)) - clusterE_mean)*(TMath::Log(clusterE->at(i)) - clusterE_mean);
   //       cluster_CENTER_LAMBDA_sqrt += (TMath::Log(cluster_CENTER_LAMBDA->at(i)) - cluster_CENTER_LAMBDA_mean)*(TMath::Log(cluster_CENTER_LAMBDA->at(i)) - cluster_CENTER_LAMBDA_mean);
   //       cluster_FIRST_ENG_DENS_sqrt += (TMath::Log(cluster_FIRST_ENG_DENS->at(i)) - cluster_FIRST_ENG_DENS_mean)*(TMath::Log(cluster_FIRST_ENG_DENS->at(i)) - cluster_FIRST_ENG_DENS_mean);
   //       cluster_SECOND_TIME_sqrt += (TMath::Log(cluster_SECOND_TIME->at(i)) - cluster_SECOND_TIME_mean)*(TMath::Log(cluster_SECOND_TIME->at(i)) - cluster_SECOND_TIME_mean);
   //       cluster_SIGNIFICANCE_sqrt += (TMath::Log(cluster_SIGNIFICANCE->at(i)) - cluster_SIGNIFICANCE_mean)*(TMath::Log(cluster_SIGNIFICANCE->at(i)) - cluster_SIGNIFICANCE_mean);
   //       cluster_CENTER_MAG_sqrt += (TMath::Log(cluster_CENTER_MAG->at(i)) - cluster_CENTER_MAG_mean)*(TMath::Log(cluster_CENTER_MAG->at(i)) - cluster_CENTER_MAG_mean);
   //    }

   // }

   // double clusterE_std = std::sqrt(clusterE_sqrt / nClusters);
   // double cluster_CENTER_LAMBDA_std = std::sqrt(cluster_CENTER_LAMBDA_sqrt / nClusters);
   // double cluster_FIRST_ENG_DENS_std = std::sqrt(cluster_FIRST_ENG_DENS_sqrt / nClusters);
   // double cluster_SECOND_TIME_std = std::sqrt(cluster_SECOND_TIME_sqrt / nClusters);
   // double cluster_SIGNIFICANCE_std = std::sqrt(cluster_SIGNIFICANCE_sqrt / nClusters);
   // double cluster_CENTER_MAG_std = std::sqrt(cluster_CENTER_MAG_sqrt / nClusters);

   


}
