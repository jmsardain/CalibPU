#define FinalPlots_cxx
#include "FinalPlots.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <TColor.h>
#include <TMath.h>
#include <vector>

double funcScore(double score){
   // return score;
   return 1 / (1 + TMath::Exp(-10 * (score - 0.5)));

}


double median(std::vector<double> &v) {
   size_t size = v.size();
   if (size == 0) { return -1;}
   std::sort(v.begin(), v.end());

   if (size % 2 == 0) {
      return (v[size / 2 - 1] + v[size / 2]) / 2.0;
   } else {
      return v[size / 2];
   }
}

double get_percentile(std::vector<double>& v, double percentile) {
   if (v.empty()) return 0.0;
   std::sort(v.begin(), v.end());
   size_t n = v.size();
   double pos = percentile * ( n - 1) / 100.0;
   size_t idx = static_cast<size_t>(std::floor(pos));
   double frac = pos - idx;

   std::nth_element(v.begin(), v.begin() + idx, v.end());
   double lower = v[idx];
   if (frac > 0.0 && idx + 1 < n) {
      std::nth_element(v.begin(), v.begin() + idx + 1, v.end());
      double upper = v[idx + 1];
      return lower * (1 - frac) + upper * frac;
   } else {
      return lower;
   }
}


void FillHisto_MedianIQR(TH1* hmedian, TH1* hiqr, TH2* h2){

   for(int ibinx = 1; ibinx <= h2->GetNbinsX(); ++ibinx) {
      std::vector<double> values;
      for(int ibiny = 1; ibiny <= h2->GetNbinsY(); ++ibiny) {
         int count = static_cast<int>(h2->GetBinContent(ibinx, ibiny));
         double binCenter = h2->GetYaxis()->GetBinCenter(ibiny);
         values.insert(values.end(), count, binCenter);
      }

      hmedian->SetBinContent(ibinx, median(values));
      double p16 = get_percentile(values, 16.0);
      double p84 = get_percentile(values, 84.0);
      double iqr = p84 - p16;
      hiqr->SetBinContent(ibinx, iqr);
      values.clear();
   }
}

void FinalPlots::Loop(){

   
   gStyle->SetOptStat(0);

   TH1D * hJetRawE = new TH1D("", "", 100, 0, 500);
   TH1D * hSumClusterE = new TH1D("", "", 100, 0, 500);
   
   // TH1D * hScore_signal = new TH1D("", "", 100, 0, 1);
   // TH1D * hScore_pileup = new TH1D("", "", 100, 0, 1);

   ////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////
   //////////// For median and IQR
   const Int_t Nbins = 100;
   Double_t bins[Nbins + 1] = {10.        ,  10.42317429,  10.86425624,  11.32400363,
        11.80320636,  12.30268771,  12.82330583,  13.36595517,
        13.93156803,  14.52111618,  15.13561248,  15.7761127 ,
        16.44371723,  17.13957308,  17.86487575,  18.62087137,
        19.40885878,  20.23019179,  21.0862815 ,  21.97859873,
        22.90867653,  23.87811283,  24.88857318,  25.94179362,
        27.03958364,  28.18382931,  29.37649652,  30.61963434,
        31.91537855,  33.26595533,  34.67368505,  36.14098626,
        37.6703799 ,  39.26449354,  40.92606597,  42.65795188,
        44.46312675,  46.34469197,  48.3058802 ,  50.35006088,
        52.48074602,  54.70159629,  57.01642723,  59.42921586,
        61.94410751,  64.5654229 ,  67.29766563,  70.14552984,
        73.11390835,  76.207901  ,  79.43282347,  82.79421637,
        86.29785478,  89.94975815,  93.75620069,  97.7237221 ,
       101.85913881, 106.16955572, 110.6623784 , 115.34532578,
       120.22644346, 125.31411749, 130.61708881, 136.14446825,
       141.90575217, 147.91083882, 154.17004529, 160.6941253 ,
       167.4942876 , 174.58221529, 181.97008586, 189.67059212,
       197.69696401, 206.06299133, 214.78304741, 223.87211386,
       233.34580623, 243.22040091, 253.51286305, 264.24087573,
       275.42287033, 287.0780582 , 299.22646366, 311.88895841,
       325.08729739, 338.84415614, 353.18316979, 368.12897364,
       383.70724549, 399.94474976, 416.86938347, 434.51022417,
       452.8975799 , 472.06304126, 492.03953568, 512.86138399,
       534.5643594 , 557.18574893, 580.76441752, 605.34087475,
       630.95734448};

    Double_t bins2[Nbins + 1] = {1.00000000e-03, 1.12201845e-03, 1.25892541e-03, 1.41253754e-03,
       1.58489319e-03, 1.77827941e-03, 1.99526231e-03, 2.23872114e-03,
       2.51188643e-03, 2.81838293e-03, 3.16227766e-03, 3.54813389e-03,
       3.98107171e-03, 4.46683592e-03, 5.01187234e-03, 5.62341325e-03,
       6.30957344e-03, 7.07945784e-03, 7.94328235e-03, 8.91250938e-03,
       1.00000000e-02, 1.12201845e-02, 1.25892541e-02, 1.41253754e-02,
       1.58489319e-02, 1.77827941e-02, 1.99526231e-02, 2.23872114e-02,
       2.51188643e-02, 2.81838293e-02, 3.16227766e-02, 3.54813389e-02,
       3.98107171e-02, 4.46683592e-02, 5.01187234e-02, 5.62341325e-02,
       6.30957344e-02, 7.07945784e-02, 7.94328235e-02, 8.91250938e-02,
       1.00000000e-01, 1.12201845e-01, 1.25892541e-01, 1.41253754e-01,
       1.58489319e-01, 1.77827941e-01, 1.99526231e-01, 2.23872114e-01,
       2.51188643e-01, 2.81838293e-01, 3.16227766e-01, 3.54813389e-01,
       3.98107171e-01, 4.46683592e-01, 5.01187234e-01, 5.62341325e-01,
       6.30957344e-01, 7.07945784e-01, 7.94328235e-01, 8.91250938e-01,
       1.00000000e+00, 1.12201845e+00, 1.25892541e+00, 1.41253754e+00,
       1.58489319e+00, 1.77827941e+00, 1.99526231e+00, 2.23872114e+00,
       2.51188643e+00, 2.81838293e+00, 3.16227766e+00, 3.54813389e+00,
       3.98107171e+00, 4.46683592e+00, 5.01187234e+00, 5.62341325e+00,
       6.30957344e+00, 7.07945784e+00, 7.94328235e+00, 8.91250938e+00,
       1.00000000e+01, 1.12201845e+01, 1.25892541e+01, 1.41253754e+01,
       1.58489319e+01, 1.77827941e+01, 1.99526231e+01, 2.23872114e+01,
       2.51188643e+01, 2.81838293e+01, 3.16227766e+01, 3.54813389e+01,
       3.98107171e+01, 4.46683592e+01, 5.01187234e+01, 5.62341325e+01,
       6.30957344e+01, 7.07945784e+01, 7.94328235e+01, 8.91250938e+01,
       1.00000000e+02};


   TH2D* h2_area     = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_Edep     = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   // TH2D* h2_labelsig = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_ml       = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
    
   // TH2D* h2_sigtimefscore = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
   // TH2D* h2_piltimefscore = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
   // TH2D* h2_sigtimescore = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
   // TH2D* h2_piltimescore = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
    
   // TH2D* h2_npvfscore_sig = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_npvfscore_pil = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_npvscore_sig = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_npvscore_pil = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);

   // TH2D* h2_etafscore_sig = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);
   // TH2D* h2_etafscore_pil = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);
   // TH2D* h2_etascore_sig = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);
   // TH2D* h2_etascore_pil = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);

   // TH2D* h2_mufscore_sig = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_mufscore_pil = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_muscore_sig = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_muscore_pil = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);

   // TH2D* h2_lambdafscore_sig = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);
   // TH2D* h2_lambdafscore_pil = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);
   // TH2D* h2_lambdascore_sig = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);
   // TH2D* h2_lambdascore_pil = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);

   // TH2D* h2_phifscore_sig = new TH2D("", "", Nbins, -3.5, 3.5, 100, 0, 1);
   // TH2D* h2_phifscore_pil = new TH2D("", "", Nbins, -3.5, 3.5, 100, 0, 1);
   // TH2D* h2_phiscore_sig = new TH2D("", "", Nbins, -3.5, 3.5, 100, 0, 1);
   // TH2D* h2_phiscore_pil = new TH2D("", "", Nbins, -3.5, 3.5, 100, 0, 1);

   // TH2D* h2_xfscore_sig = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_xfscore_pil = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_xscore_sig = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_xscore_pil = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);

   // TH2D* h2_yfscore_sig = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_yfscore_pil = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_yscore_sig = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_yscore_pil = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);

   // TH2D* h2_zfscore_sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 1);
   // TH2D* h2_zfscore_pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 1);
   // TH2D* h2_zscore_sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 1);
   // TH2D* h2_zscore_pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 1);

   // TH2D* h2_massfscore_sig = new TH2D("", "", Nbins, bins2, 100, 0, 1);
   // TH2D* h2_massfscore_pil = new TH2D("", "", Nbins, bins2, 100, 0, 1);
   // TH2D* h2_massscore_sig = new TH2D("", "", Nbins, bins2, 100, 0, 1);
   // TH2D* h2_massscore_pil = new TH2D("", "", Nbins, bins2, 100, 0, 1);

   // TH2D* h2_magfscore_sig = new TH2D("", "", Nbins, 1000, 7000, 100, 0, 1);
   // TH2D* h2_magfscore_pil = new TH2D("", "", Nbins, 1000, 7000, 100, 0, 1);
   // TH2D* h2_magscore_sig = new TH2D("", "", Nbins, 1000, 7000, 100, 0, 1);
   // TH2D* h2_magscore_pil = new TH2D("", "", Nbins, 1000, 7000, 100, 0, 1);


   // TH2D* h2_rzscore1sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore1pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore2sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore2pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore3sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore3pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore4sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore4pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore5sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore5pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore6sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore6pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore7sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore7pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore8sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore8pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore9sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore9pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   // TH2D* h2_rzscore10sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   // TH2D* h2_rzscore10pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   ////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      // if (jentry>10) break;
      hJetRawE->Fill(jetRawE);
      double sumClusE_EM     = 0;
      double sum_ClusE_dep   = 0; 
      // double sum_ClusE_label = 0; 
      double sum_ClusE_ml    = 0; 
      
      // for (unsigned int i=0; i<clusterE.size(); i++){
      //    sumClusE_EM += clusterE->at(i);
      // }
      for (unsigned int i=0; i<nclusterE; i++){

         // sum cluster (EM Scale)
         sumClusE_EM += clusterE[i];
         // sum cluster (Deposited Energy)
         sum_ClusE_dep += cluster_ENG_CALIB_TOT[i]; 
         // sum cluster (EM Scale, Label == 1, i.e. signal)
         // if (labels_test[i] == 1) { sum_ClusE_label += clusterE[i]; }  
         // sum cluster (score function)
         sum_ClusE_ml += clusterE[i] * funcScore(nodes_out[i]);
          

         // if (labels_test[i] == 1) {h2_sigtimefscore->Fill(cluster_time[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_piltimefscore->Fill(cluster_time[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_npvfscore_sig->Fill(nPrimVtx[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_npvfscore_pil->Fill(nPrimVtx[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_etafscore_sig->Fill(clusterEta[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_etafscore_pil->Fill(clusterEta[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_mufscore_sig->Fill(avgMu[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_mufscore_pil->Fill(avgMu[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_lambdafscore_sig->Fill(cluster_CENTER_LAMBDA[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_lambdafscore_pil->Fill(cluster_CENTER_LAMBDA[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_xfscore_sig->Fill(cluster_CENTER_X[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_xfscore_pil->Fill(cluster_CENTER_X[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_yfscore_sig->Fill(cluster_CENTER_Y[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_yfscore_pil->Fill(cluster_CENTER_Y[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_zfscore_sig->Fill(cluster_CENTER_Z[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_zfscore_pil->Fill(cluster_CENTER_Z[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_massfscore_sig->Fill(cluster_MASS[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_massfscore_pil->Fill(cluster_MASS[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_phifscore_sig->Fill(clusterPhi[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_phifscore_pil->Fill(clusterPhi[i], funcScore(nodes_out[i]));}

         // if (labels_test[i] == 1) {h2_magfscore_sig->Fill(cluster_CENTER_MAG[i], funcScore(nodes_out[i]));}
         // if (labels_test[i] == 0) {h2_magfscore_pil->Fill(cluster_CENTER_MAG[i], funcScore(nodes_out[i]));}



         // if (labels_test[i] == 1) {h2_sigtimescore->Fill(cluster_time[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_piltimescore->Fill(cluster_time[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_npvscore_sig->Fill(nPrimVtx[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_npvscore_pil->Fill(nPrimVtx[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_etascore_sig->Fill(clusterEta[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_etascore_pil->Fill(clusterEta[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_muscore_sig->Fill(avgMu[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_muscore_pil->Fill(avgMu[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_lambdascore_sig->Fill(cluster_CENTER_LAMBDA[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_lambdascore_pil->Fill(cluster_CENTER_LAMBDA[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_xscore_sig->Fill(cluster_CENTER_X[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_xscore_pil->Fill(cluster_CENTER_X[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_yscore_sig->Fill(cluster_CENTER_Y[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_yscore_pil->Fill(cluster_CENTER_Y[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_zscore_sig->Fill(cluster_CENTER_Z[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_zscore_pil->Fill(cluster_CENTER_Z[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_massscore_sig->Fill(cluster_MASS[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_massscore_pil->Fill(cluster_MASS[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_phiscore_sig->Fill(clusterPhi[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_phiscore_pil->Fill(clusterPhi[i], nodes_out[i]);}

         // if (labels_test[i] == 1) {h2_magscore_sig->Fill(cluster_CENTER_MAG[i], nodes_out[i]);}
         // if (labels_test[i] == 0) {h2_magscore_pil->Fill(cluster_CENTER_MAG[i], nodes_out[i]);}



         // if ((0 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.1)) {
         //     if (labels_test[i] == 1) {h2_rzscore1sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore1pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.1 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.2)) {
         //     if (labels_test[i] == 1) {h2_rzscore2sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore2pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.2 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.3)) {
         //     if (labels_test[i] == 1) {h2_rzscore3sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore3pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.3 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.4)) {
         //     if (labels_test[i] == 1) {h2_rzscore4sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore4pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.4 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.5)) {
         //     if (labels_test[i] == 1) {h2_rzscore5sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore5pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.5 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.6)) {
         //     if (labels_test[i] == 1) {h2_rzscore6sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore6pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.6 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.7)) {
         //     if (labels_test[i] == 1) {h2_rzscore7sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore7pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.7 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.8)) {
         //     if (labels_test[i] == 1) {h2_rzscore8sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore8pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.8 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) < 0.9)) {
         //     if (labels_test[i] == 1) {h2_rzscore9sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore9pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }
         // if ((0.9 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i]) <= 1)) {
         //     if (labels_test[i] == 1) {h2_rzscore10sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         //     if (labels_test[i] == 0) {h2_rzscore10pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         // }

         
         // if (labels_test[i] == 1) { hScore_signal->Fill(nodes_out[i]); }
         // if (labels_test[i] == 0) { hScore_pileup->Fill(nodes_out[i]); }
      }
      hSumClusterE->Fill(sumClusE_EM);
      // std::cout << " jetRawE: " << jetRawE
      //           << " sum: " << sumClusE_EM 
      //           << std::endl;

      // h2_area->Fill(    jetCalPt, jetAreaE        / truthJetE);
      // h2_Edep->Fill(    jetCalPt, sum_ClusE_dep   / truthJetE);
      // // h2_labelsig->Fill(jetCalPt, sum_ClusE_label / truthJetE);
      // h2_ml->Fill(      jetCalPt, sum_ClusE_ml    / truthJetE);

      h2_area->Fill(    jetCalPt, jetAreaE        / jetCalE);
      h2_Edep->Fill(    jetCalPt, sum_ClusE_dep   / jetCalE);
      // // h2_labelsig->Fill(jetCalPt, sum_ClusE_label / truthJetE);
      h2_ml->Fill(      jetCalPt, sum_ClusE_ml    / jetCalE);

   }

   // TCanvas*c = new TCanvas("", "", 500, 500);
   // c->SetLogy();
   // hScore_signal->SetLineColor(kBlue);
   // hScore_pileup->SetLineColor(kOrange);

   // hScore_signal->GetXaxis()->SetTitle("Scores");
   // hScore_signal->GetYaxis()->SetTitle("Number of clusters");
   // hScore_signal->Draw("H");
   // hScore_pileup->Draw("HSAME");
   // c->SaveAs("./plots/scores.png");
   
   //////////////////////////////////////////////////
   //////////////////////////////////////////////////
   hSumClusterE->SetLineColor(kRed);

   TLegend* l = new TLegend(0.7, 0.7, 0.9, 0.9); 
   l->AddEntry(hJetRawE, "E_{jet}^{EM}", "l");
   l->AddEntry(hSumClusterE, "sum E_{clus}^{EM}", "l");
   TCanvas* c1 = new TCanvas("", "", 800, 800);

   TPad* pad1 = new TPad("pad1","pad1",0,0.3,1,1);
   pad1->SetBottomMargin(0); 
   pad1->Draw();
   pad1->cd();
   pad1->SetLogy();
   hJetRawE->Draw("H");
   hSumClusterE->Draw("H SAME");
   l->Draw("SAME");

   c1->cd();
   TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.3);
   pad2->Draw();
   pad2->cd();

   // Draw ratios
   TH1D* hRatio = (TH1D*)hSumClusterE->Clone("hSumClusterE");

   hRatio->Divide(hJetRawE);

   hRatio->SetLineColor(kRed);

   hRatio->SetTitle("");
   hRatio->GetYaxis()->SetTitle("Ratio");
   hRatio->GetYaxis()->SetNdivisions(505);
   hRatio->GetYaxis()->SetTitleSize(0.15);
   hRatio->GetYaxis()->SetTitleOffset(0.3);
   hRatio->GetYaxis()->SetLabelSize(0.12);

   hRatio->GetXaxis()->SetTitle("Energy");
   hRatio->GetXaxis()->SetLabelSize(0.12);
   hRatio->GetXaxis()->SetTitleSize(0.15);
   hRatio->GetYaxis()->SetRangeUser(0.8, 1.2);

   hRatio->Draw("H");

   c1->SaveAs(("./plots/plot.png"));

   //////////////////////////////////////////////////
   //////////////////////////////////////////////////

   TCanvas*d = new TCanvas("", "", 500, 500);
   d->SetLogx();
   h2_ml->SetYTitle("Response");
   h2_ml->SetXTitle("E (GeV)");
   h2_ml->Draw("colz");
   d->SaveAs("./plots/h2_response/h2_ml.png");
   // h2_labelsig->SetYTitle("Response");
   // h2_labelsig->SetXTitle("E (GeV)");
   // h2_labelsig->Draw("colz");
   d->SaveAs("./plots/h2_response/h2_label.png");
   d->Close();


// Func(Score) Feature Plots

//    TCanvas*t = new TCanvas("", "", 500, 500);
//    t->SetLogz();
//    h2_sigtimefscore->SetXTitle("Cluster Time");
//    h2_sigtimefscore->SetYTitle("func(Score)");
//    h2_sigtimefscore->Draw("colz");
//    t->SaveAs("./plots/h2_time/timefscore_sig.png");
//    h2_piltimefscore->SetXTitle("Cluster Time");
//    h2_piltimefscore->SetYTitle("func(Score)");
//    h2_piltimefscore->Draw("colz");
//    t->SaveAs("./plots/h2_time/timefscore_pil.png");
//    t->Close();

//    TCanvas*n = new TCanvas("", "", 500, 500);
//    n->SetLogz();
//    h2_npvfscore_sig->SetXTitle("nPrimVtx");
//    h2_npvfscore_sig->SetYTitle("func(Score)");
//    h2_npvfscore_sig->Draw("colz");
//    n->SaveAs("./plots/h2_npv/npvfscore_sig.png");
//    h2_npvfscore_pil->SetXTitle("nPrimVtx");
//    h2_npvfscore_pil->SetYTitle("func(Score)");
//    h2_npvfscore_pil->Draw("colz");
//    n->SaveAs("./plots/h2_npv/npvfscore_pil.png");
//    n->Close();

//    TCanvas*e = new TCanvas("", "", 500, 500);
//    e->SetLogz();
//    h2_etafscore_sig->SetXTitle("Cluster Eta");
//    h2_etafscore_sig->SetYTitle("func(Score)");
//    h2_etafscore_sig->Draw("colz");
//    e->SaveAs("./plots/h2_eta/etafscore_sig.png");
//    h2_etafscore_pil->SetXTitle("Cluster Eta");
//    h2_etafscore_pil->SetYTitle("func(Score)");
//    h2_etafscore_pil->Draw("colz");
//    e->SaveAs("./plots/h2_eta/etafscore_pil.png");
//    e->Close();

//    TCanvas*m = new TCanvas("", "", 500, 500);
//    m->SetLogz();
//    h2_mufscore_sig->SetXTitle("Cluster Mu");
//    h2_mufscore_sig->SetYTitle("func(Score)");
//    h2_mufscore_sig->Draw("colz");
//    m->SaveAs("./plots/h2_mu/mufscore_sig.png");
//    h2_mufscore_pil->SetXTitle("Cluster Mu");
//    h2_mufscore_pil->SetYTitle("func(Score)");
//    h2_mufscore_pil->Draw("colz");
//    m->SaveAs("./plots/h2_mu/mufscore_pil.png");
//    m->Close();

//    TCanvas*a = new TCanvas("", "", 500, 500);
//    a->SetLogz();
//    h2_lambdafscore_sig->SetXTitle("Cluster Lambda");
//    h2_lambdafscore_sig->SetYTitle("func(Score)");
//    h2_lambdafscore_sig->Draw("colz");
//    a->SaveAs("./plots/h2_lambda/lambdafscore_sig.png");
//    h2_lambdafscore_pil->SetXTitle("Cluster Lambda");
//    h2_lambdafscore_pil->SetYTitle("func(Score)");
//    h2_lambdafscore_pil->Draw("colz");
//    a->SaveAs("./plots/h2_lambda/lambdafscore_pil.png");
//    a->Close();

//    TCanvas*x = new TCanvas("", "", 500, 500);
//    x->SetLogz();
//    h2_xfscore_sig->SetXTitle("Cluster Center X");
//    h2_xfscore_sig->SetYTitle("func(Score)");
//    h2_xfscore_sig->Draw("colz");
//    x->SaveAs("./plots/h2_x/xfscore_sig.png");
//    h2_xfscore_pil->SetXTitle("Cluster Center X");
//    h2_xfscore_pil->SetYTitle("func(Score)");
//    h2_xfscore_pil->Draw("colz");
//    x->SaveAs("./plots/h2_x/xfscore_pil.png");
//    x->Close();

//    TCanvas*y = new TCanvas("", "", 500, 500);
//    y->SetLogz();
//    h2_yfscore_sig->SetXTitle("Cluster Center Y");
//    h2_yfscore_sig->SetYTitle("func(Score)");
//    h2_yfscore_sig->Draw("colz");
//    y->SaveAs("./plots/h2_y/yfscore_sig.png");
//    h2_yfscore_pil->SetXTitle("Cluster Center Y");
//    h2_yfscore_pil->SetYTitle("func(Score)");
//    h2_yfscore_pil->Draw("colz");
//    y->SaveAs("./plots/h2_y/yfscore_pil.png");
//    y->Close();

//    TCanvas*z = new TCanvas("", "", 500, 500);
//    z->SetLogz();
//    h2_zfscore_sig->SetXTitle("Cluster Center Z");
//    h2_zfscore_sig->SetYTitle("func(Score)");
//    h2_zfscore_sig->Draw("colz");
//    z->SaveAs("./plots/h2_z/zfscore_sig.png");
//    h2_zfscore_pil->SetXTitle("Cluster Center Z");
//    h2_zfscore_pil->SetYTitle("func(Score)");
//    h2_zfscore_pil->Draw("colz");
//    z->SaveAs("./plots/h2_z/zfscore_pil.png");
//    z->Close();

//    TCanvas*s = new TCanvas("", "", 500, 500);
//    s->SetLogz();
//    s->SetLogx();
//    h2_massfscore_sig->SetXTitle("Cluster Mass");
//    h2_massfscore_sig->SetYTitle("func(Score)");
//    h2_massfscore_sig->Draw("colz");
//    s->SaveAs("./plots/h2_mass/massfscore_sig.png");
//    h2_massfscore_pil->SetXTitle("Cluster Mass");
//    h2_massfscore_pil->SetYTitle("func(Score)");
//    h2_massfscore_pil->Draw("colz");
//    s->SaveAs("./plots/h2_mass/massfscore_pil.png");
//    s->Close();

//    TCanvas*p = new TCanvas("", "", 500, 500);
//    p->SetLogz();
//    h2_magfscore_sig->SetXTitle("Cluster Center Mag");
//    h2_magfscore_sig->SetYTitle("func(Score)");
//    h2_magfscore_sig->Draw("colz");
//    p->SaveAs("./plots/h2_mag/magfscore_sig.png");
//    h2_magfscore_pil->SetXTitle("Cluster Center Mag");
//    h2_magfscore_pil->SetYTitle("func(Score)");
//    h2_magfscore_pil->Draw("colz");
//    p->SaveAs("./plots/h2_mag/magfscore_pil.png");
//    p->Close();

//    TCanvas*g = new TCanvas("", "", 500, 500);
//    g->SetLogz();
//    h2_phifscore_sig->SetXTitle("Cluster Phi");
//    h2_phifscore_sig->SetYTitle("func(Score)");
//    h2_phifscore_sig->Draw("colz");
//    g->SaveAs("./plots/h2_phi/phifscore_sig.png");
//    h2_phifscore_pil->SetXTitle("Cluster Phi");
//    h2_phifscore_pil->SetYTitle("func(Score)");
//    h2_phifscore_pil->Draw("colz");
//    g->SaveAs("./plots/h2_phi/phifscore_pil.png");
//    g->Close();


// // Raw score feature plots

//    TCanvas*t2 = new TCanvas("", "", 500, 500);
//    t2->SetLogz();
//    h2_sigtimescore->SetXTitle("Cluster Time");
//    h2_sigtimescore->SetYTitle("Score");
//    h2_sigtimescore->Draw("colz");
//    t2->SaveAs("./plots/h2_time/timescore_sig.png");
//    h2_piltimescore->SetXTitle("Cluster Time");
//    h2_piltimescore->SetYTitle("Score");
//    h2_piltimescore->Draw("colz");
//    t2->SaveAs("./plots/h2_time/timescore_pil.png");
//    t2->Close();

//    TCanvas*n2 = new TCanvas("", "", 500, 500);
//    n2->SetLogz();
//    h2_npvscore_sig->SetXTitle("nPrimVtx");
//    h2_npvscore_sig->SetYTitle("Score");
//    h2_npvscore_sig->Draw("colz");
//    n2->SaveAs("./plots/h2_npv/npvscore_sig.png");
//    h2_npvscore_pil->SetXTitle("nPrimVtx");
//    h2_npvscore_pil->SetYTitle("Score");
//    h2_npvscore_pil->Draw("colz");
//    n2->SaveAs("./plots/h2_npv/npvscore_pil.png");
//    n2->Close();

//    TCanvas*e2 = new TCanvas("", "", 500, 500);
//    e2->SetLogz();
//    h2_etascore_sig->SetXTitle("Cluster Eta");
//    h2_etascore_sig->SetYTitle("Score");
//    h2_etascore_sig->Draw("colz");
//    e2->SaveAs("./plots/h2_eta/etascore_sig.png");
//    h2_etascore_pil->SetXTitle("Cluster Eta");
//    h2_etascore_pil->SetYTitle("Score");
//    h2_etascore_pil->Draw("colz");
//    e2->SaveAs("./plots/h2_eta/etascore_pil.png");
//    e2->Close();

//    TCanvas*m2 = new TCanvas("", "", 500, 500);
//    m2->SetLogz();
//    h2_muscore_sig->SetXTitle("Cluster Mu");
//    h2_muscore_sig->SetYTitle("Score");
//    h2_muscore_sig->Draw("colz");
//    m2->SaveAs("./plots/h2_mu/muscore_sig.png");
//    h2_muscore_pil->SetXTitle("Cluster Mu");
//    h2_muscore_pil->SetYTitle("Score");
//    h2_muscore_pil->Draw("colz");
//    m2->SaveAs("./plots/h2_mu/muscore_pil.png");
//    m2->Close();

//    TCanvas*a2 = new TCanvas("", "", 500, 500);
//    a2->SetLogz();
//    h2_lambdascore_sig->SetXTitle("Cluster Lambda");
//    h2_lambdascore_sig->SetYTitle("Score");
//    h2_lambdascore_sig->Draw("colz");
//    a2->SaveAs("./plots/h2_lambda/lambdascore_sig.png");
//    h2_lambdascore_pil->SetXTitle("Cluster Lambda");
//    h2_lambdascore_pil->SetYTitle("Score");
//    h2_lambdascore_pil->Draw("colz");
//    a2->SaveAs("./plots/h2_lambda/lambdascore_pil.png");
//    a2->Close();

//    TCanvas*x2 = new TCanvas("", "", 500, 500);
//    x2->SetLogz();
//    h2_xscore_sig->SetXTitle("Cluster Center X");
//    h2_xscore_sig->SetYTitle("Score");
//    h2_xscore_sig->Draw("colz");
//    x2->SaveAs("./plots/h2_x/xscore_sig.png");
//    h2_xscore_pil->SetXTitle("Cluster Center X");
//    h2_xscore_pil->SetYTitle("Score");
//    h2_xscore_pil->Draw("colz");
//    x2->SaveAs("./plots/h2_x/xscore_pil.png");
//    x2->Close();

//    TCanvas*y2 = new TCanvas("", "", 500, 500);
//    y2->SetLogz();
//    h2_yscore_sig->SetXTitle("Cluster Center Y");
//    h2_yscore_sig->SetYTitle("Score");
//    h2_yscore_sig->Draw("colz");
//    y2->SaveAs("./plots/h2_y/yscore_sig.png");
//    h2_yscore_pil->SetXTitle("Cluster Center Y");
//    h2_yscore_pil->SetYTitle("Score");
//    h2_yscore_pil->Draw("colz");
//    y2->SaveAs("./plots/h2_y/yscore_pil.png");
//    y2->Close();

//    TCanvas*z2 = new TCanvas("", "", 500, 500);
//    z2->SetLogz();
//    h2_zscore_sig->SetXTitle("Cluster Center Z");
//    h2_zscore_sig->SetYTitle("Score");
//    h2_zscore_sig->Draw("colz");
//    z2->SaveAs("./plots/h2_z/zscore_sig.png");
//    h2_zscore_pil->SetXTitle("Cluster Center Z");
//    h2_zscore_pil->SetYTitle("Score");
//    h2_zscore_pil->Draw("colz");
//    z2->SaveAs("./plots/h2_z/zscore_pil.png");
//    z2->Close();

//    TCanvas*s2 = new TCanvas("", "", 500, 500);
//    s2->SetLogz();
//    s2->SetLogx();
//    h2_massscore_sig->SetXTitle("Cluster Mass");
//    h2_massscore_sig->SetYTitle("Score");
//    h2_massscore_sig->Draw("colz");
//    s2->SaveAs("./plots/h2_mass/massscore_sig.png");
//    h2_massscore_pil->SetXTitle("Cluster Mass");
//    h2_massscore_pil->SetYTitle("Score");
//    h2_massscore_pil->Draw("colz");
//    s2->SaveAs("./plots/h2_mass/massscore_pil.png");
//    s2->Close();

//    TCanvas*p2 = new TCanvas("", "", 500, 500);
//    p2->SetLogz();
//    h2_phiscore_sig->SetXTitle("Cluster Phi");
//    h2_phiscore_sig->SetYTitle("Score");
//    h2_phiscore_sig->Draw("colz");
//    p2->SaveAs("./plots/h2_phi/phiscore_sig.png");
//    h2_phiscore_pil->SetXTitle("Cluster Phi");
//    h2_phiscore_pil->SetYTitle("Score");
//    h2_phiscore_pil->Draw("colz");
//    p2->SaveAs("./plots/h2_phi/phiscore_pil.png");
//    p2->Close();

//    TCanvas*g2 = new TCanvas("", "", 500, 500);
//    g2->SetLogz();
//    h2_magscore_sig->SetXTitle("Cluster Center Mag");
//    h2_magscore_sig->SetYTitle("Score");
//    h2_magscore_sig->Draw("colz");
//    g2->SaveAs("./plots/h2_mag/magscore_sig.png");
//    h2_magscore_pil->SetXTitle("Cluster Center Mag");
//    h2_magscore_pil->SetYTitle("Score");
//    h2_magscore_pil->Draw("colz");
//    g2->SaveAs("./plots/h2_mag/magscore_pil.png");
//    g2->Close();


//    // Detector plots

//    TCanvas*r1 = new TCanvas("", "", 500, 500);
//    r1->SetLogz();
//    h2_rzscore1sig->SetXTitle("Cluster Center Z");
//    h2_rzscore1sig->SetYTitle("Cluster Center R");
//    h2_rzscore1sig->Draw("colz");
//    r1->SaveAs("./plots/h2_rz/rzscore1_sig.png");
//    h2_rzscore1pil->SetXTitle("Cluster Center Z");
//    h2_rzscore1pil->SetYTitle("Cluster Center R");
//    h2_rzscore1pil->Draw("colz");
//    r1->SaveAs("./plots/h2_rz/rzscore1_pil.png");
//    r1->Close();
    
//    TCanvas*r2 = new TCanvas("", "", 500, 500);
//    r2->SetLogz();
//    h2_rzscore2sig->SetXTitle("Cluster Center Z");
//    h2_rzscore2sig->SetYTitle("Cluster Center R");
//    h2_rzscore2sig->Draw("colz");
//    r2->SaveAs("./plots/h2_rz/rzscore2_sig.png");
//    h2_rzscore2pil->SetXTitle("Cluster Center Z");
//    h2_rzscore2pil->SetYTitle("Cluster Center R");
//    h2_rzscore2pil->Draw("colz");
//    r2->SaveAs("./plots/h2_rz/rzscore2_pil.png");
//    r2->Close();
    
//    TCanvas*r3 = new TCanvas("", "", 500, 500);
//    r3->SetLogz();
//    h2_rzscore3sig->SetXTitle("Cluster Center Z");
//    h2_rzscore3sig->SetYTitle("Cluster Center R");
//    h2_rzscore3sig->Draw("colz");
//    r3->SaveAs("./plots/h2_rz/rzscore3_sig.png");
//    h2_rzscore3pil->SetXTitle("Cluster Center Z");
//    h2_rzscore3pil->SetYTitle("Cluster Center R");
//    h2_rzscore3pil->Draw("colz");
//    r3->SaveAs("./plots/h2_rz/rzscore3_pil.png");
//    r3->Close();

//    TCanvas*r4 = new TCanvas("", "", 500, 500);
//    r4->SetLogz();
//    h2_rzscore4sig->SetXTitle("Cluster Center Z");
//    h2_rzscore4sig->SetYTitle("Cluster Center R");
//    h2_rzscore4sig->Draw("colz");
//    r4->SaveAs("./plots/h2_rz/rzscore4_sig.png");
//    h2_rzscore4pil->SetXTitle("Cluster Center Z");
//    h2_rzscore4pil->SetYTitle("Cluster Center R");
//    h2_rzscore4pil->Draw("colz");
//    r4->SaveAs("./plots/h2_rz/rzscore4_pil.png");
//    r4->Close();

//    TCanvas*r5 = new TCanvas("", "", 500, 500);
//    r5->SetLogz();
//    h2_rzscore5sig->SetXTitle("Cluster Center Z");
//    h2_rzscore5sig->SetYTitle("Cluster Center R");
//    h2_rzscore5sig->Draw("colz");
//    r5->SaveAs("./plots/h2_rz/rzscore5_sig.png");
//    h2_rzscore5pil->SetXTitle("Cluster Center Z");
//    h2_rzscore5pil->SetYTitle("Cluster Center R");
//    h2_rzscore5pil->Draw("colz");
//    r5->SaveAs("./plots/h2_rz/rzscore5_pil.png");
//    r5->Close();

//    TCanvas*r6 = new TCanvas("", "", 500, 500);
//    r6->SetLogz();
//    h2_rzscore6sig->SetXTitle("Cluster Center Z");
//    h2_rzscore6sig->SetYTitle("Cluster Center R");
//    h2_rzscore6sig->Draw("colz");
//    r6->SaveAs("./plots/h2_rz/rzscore6_sig.png");
//    h2_rzscore6pil->SetXTitle("Cluster Center Z");
//    h2_rzscore6pil->SetYTitle("Cluster Center R");
//    h2_rzscore6pil->Draw("colz");
//    r6->SaveAs("./plots/h2_rz/rzscore6_pil.png");
//    r6->Close();

//    TCanvas*r7 = new TCanvas("", "", 500, 500);
//    r7->SetLogz();
//    h2_rzscore7sig->SetXTitle("Cluster Center Z");
//    h2_rzscore7sig->SetYTitle("Cluster Center R");
//    h2_rzscore7sig->Draw("colz");
//    r7->SaveAs("./plots/h2_rz/rzscore7_sig.png");
//    h2_rzscore7pil->SetXTitle("Cluster Center Z");
//    h2_rzscore7pil->SetYTitle("Cluster Center R");
//    h2_rzscore7pil->Draw("colz");
//    r7->SaveAs("./plots/h2_rz/rzscore7_pil.png");
//    r7->Close();

//    TCanvas*r8 = new TCanvas("", "", 500, 500);
//    r8->SetLogz();
//    h2_rzscore8sig->SetXTitle("Cluster Center Z");
//    h2_rzscore8sig->SetYTitle("Cluster Center R");
//    h2_rzscore8sig->Draw("colz");
//    r8->SaveAs("./plots/h2_rz/rzscore8_sig.png");
//    h2_rzscore8pil->SetXTitle("Cluster Center Z");
//    h2_rzscore8pil->SetYTitle("Cluster Center R");
//    h2_rzscore8pil->Draw("colz");
//    r8->SaveAs("./plots/h2_rz/rzscore8_pil.png");
//    r8->Close();

//    TCanvas*r9 = new TCanvas("", "", 500, 500);
//    r9->SetLogz();
//    h2_rzscore9sig->SetXTitle("Cluster Center Z");
//    h2_rzscore9sig->SetYTitle("Cluster Center R");
//    h2_rzscore9sig->Draw("colz");
//    r9->SaveAs("./plots/h2_rz/rzscore9_sig.png");
//    h2_rzscore9pil->SetXTitle("Cluster Center Z");
//    h2_rzscore9pil->SetYTitle("Cluster Center R");
//    h2_rzscore9pil->Draw("colz");
//    r9->SaveAs("./plots/h2_rz/rzscore9_pil.png");
//    r9->Close();

//    TCanvas*r10 = new TCanvas("", "", 500, 500);
//    r10->SetLogz();
//    h2_rzscore10sig->SetXTitle("Cluster Center Z");
//    h2_rzscore10sig->SetYTitle("Cluster Center R");
//    h2_rzscore10sig->Draw("colz");
//    r10->SaveAs("./plots/h2_rz/rzscore10_sig.png");
//    h2_rzscore10pil->SetXTitle("Cluster Center Z");
//    h2_rzscore10pil->SetYTitle("Cluster Center R");
//    h2_rzscore10pil->Draw("colz");
//    r10->SaveAs("./plots/h2_rz/rzscore10_pil.png");
//    r10->Close();
    
    
   TH1D* h_area_median     = new TH1D("", "", Nbins, bins);
   TH1D* h_Edep_median     = new TH1D("", "", Nbins, bins);
   // TH1D* h_labelsig_median = new TH1D("", "", Nbins, bins);
   TH1D* h_ml_median       = new TH1D("", "", Nbins, bins);

   TH1D* h_area_iqr     = new TH1D("", "", Nbins, bins);
   TH1D* h_Edep_iqr     = new TH1D("", "", Nbins, bins);
   // TH1D* h_labelsig_iqr = new TH1D("", "", Nbins, bins);
   TH1D* h_ml_iqr       = new TH1D("", "", Nbins, bins);

   FillHisto_MedianIQR(h_area_median, h_area_iqr, h2_area);
   FillHisto_MedianIQR(h_Edep_median, h_Edep_iqr, h2_Edep);
   // FillHisto_MedianIQR(h_labelsig_median, h_labelsig_iqr, h2_labelsig);
   FillHisto_MedianIQR(h_ml_median, h_ml_iqr, h2_ml);

   h_area_median->SetLineColor(kAzure + 7);
   h_Edep_median->SetLineColor(TColor::GetColor("#FF8C00"));
   // h_labelsig_median->SetLineColor(TColor::GetColor("#008026"));
   h_ml_median->SetLineColor(TColor::GetColor("#732982"));

   h_area_iqr->SetLineColor(kAzure + 7);
   h_Edep_iqr->SetLineColor(TColor::GetColor("#FF8C00"));
   // h_labelsig_iqr->SetLineColor(TColor::GetColor("#008026"));
   h_ml_iqr->SetLineColor(TColor::GetColor("#732982"));

   TLegend* lMed = new TLegend(0.7, 0.7, 0.9, 0.9);
   lMed->AddEntry(h_area_median, "ATLAS", "l");
   lMed->AddEntry(h_Edep_median, "Truth", "l");
   // lMed->AddEntry(h_labelsig_median, "Label", "l");
   lMed->AddEntry(h_ml_median, "ML", "l");

   TCanvas*cMedian = new TCanvas("", "", 500, 500);
   cMedian->SetLogx();
 
   h_area_median->GetYaxis()->SetRangeUser(0, 2);
   h_area_median->GetXaxis()->SetRangeUser(10, 2000);
   h_area_median->Draw("H");
   h_Edep_median->Draw("HSAME");
   // h_labelsig_median->Draw("HSAME");
   h_ml_median->Draw("HSAME");
   h_area_median->SetXTitle("E [GeV]");
   h_area_median->SetYTitle("Jet energy response, R_{E}");
   lMed->Draw("SAME");
   cMedian->SaveAs("./plots/median.png");

   TCanvas*cIQR = new TCanvas("", "", 500, 500);
   cIQR->SetLogx();
  

   h_area_iqr->GetYaxis()->SetRangeUser(0, 2);
   h_area_iqr->GetXaxis()->SetRangeUser(10, 2000); 
   h_area_iqr->Draw("H");
   h_area_iqr->SetXTitle("E [GeV]");
   h_area_iqr->SetYTitle("Jet energy resolution, #sigma(r_{E})");
   h_Edep_iqr->Draw("HSAME");
   // h_labelsig_iqr->Draw("HSAME");
   h_ml_iqr->Draw("HSAME");
   lMed->Draw("SAME");
   cIQR->SaveAs("./plots/iqr.png");
   

   //////////////////////////////////////////////////
   //////////////////////////////////////////////////

  

}
