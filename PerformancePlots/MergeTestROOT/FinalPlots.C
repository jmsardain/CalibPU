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
   
   TH1D * hScore_signal = new TH1D("", "", 100, 0, 1);
   TH1D * hScore_pileup = new TH1D("", "", 100, 0, 1);

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


   TH2D* h2_area     = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_Edep     = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_labelsig = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_ml       = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
    
   TH2D* h2_sigtimescore = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
   TH2D* h2_piltimescore = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
   // TH2D* h2_sigtimescoretrans = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
   // TH2D* h2_piltimescoretrans = new TH2D("", "", Nbins, -50, 50, 100, 0, 1);
    
   TH2D* h2_npvscore_sig = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   TH2D* h2_npvscore_pil = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_npvscore_sigtrans = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_npvscore_piltrans = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);

   TH2D* h2_etascore_sig = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);
   TH2D* h2_etascore_pil = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);
   // TH2D* h2_etascore_sigtrans = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);
   // TH2D* h2_etascore_piltrans = new TH2D("", "", Nbins, -3, 3, 100, 0, 1);

   TH2D* h2_muscore_sig = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   TH2D* h2_muscore_pil = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_muscore_sigtrans = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);
   // TH2D* h2_muscore_piltrans = new TH2D("", "", Nbins, 0, 100, 100, 0, 1);

   TH2D* h2_lambdascore_sig = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);
   TH2D* h2_lambdascore_pil = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);
   // TH2D* h2_lambdascore_sigtrans = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);
   // TH2D* h2_lambdascore_piltrans = new TH2D("", "", Nbins, 0, 8000, 100, 0, 1);

   TH2D* h2_xscore_sig = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   TH2D* h2_xscore_pil = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_xscore_sigtrans = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_xscore_piltrans = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);

   TH2D* h2_yscore_sig = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   TH2D* h2_yscore_pil = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_yscore_sigtrans = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);
   // TH2D* h2_yscore_piltrans = new TH2D("", "", Nbins, -4000, 4000, 100, 0, 1);

   TH2D* h2_zscore_sig = new TH2D("", "", Nbins, 0, 6000, 100, 0, 1);
   TH2D* h2_zscore_pil = new TH2D("", "", Nbins, 0, 6000, 100, 0, 1);
   // TH2D* h2_zscore_sigtrans = new TH2D("", "", Nbins, 0, 6000, 100, 0, 1);
   // TH2D* h2_zscore_piltrans = new TH2D("", "", Nbins, 0, 6000, 100, 0, 1);

   TH2D* h2_rzscore1sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore1pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore2sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore2pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore3sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore3pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore4sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore4pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore5sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore5pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore6sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore6pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore7sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore7pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore8sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore8pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore9sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore9pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

   TH2D* h2_rzscore10sig = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);
   TH2D* h2_rzscore10pil = new TH2D("", "", Nbins, -6000, 6000, 100, 0, 4000);

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
      double sum_ClusE_label = 0; 
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
         if (labels_test[i] == 1) { sum_ClusE_label += clusterE[i]; }  
         // sum cluster (score function)
         sum_ClusE_ml += clusterE[i] * funcScore(nodes_out[i]);
          

         if (labels_test[i] == 1) {h2_sigtimescore->Fill(cluster_time[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_piltimescore->Fill(cluster_time[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_npvscore_sig->Fill(nPrimVtx[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_npvscore_pil->Fill(nPrimVtx[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_etascore_sig->Fill(clusterEta[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_etascore_pil->Fill(clusterEta[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_muscore_sig->Fill(avgMu[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_muscore_pil->Fill(avgMu[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_lambdascore_sig->Fill(cluster_CENTER_LAMBDA[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_lambdascore_pil->Fill(cluster_CENTER_LAMBDA[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_xscore_sig->Fill(cluster_CENTER_X[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_xscore_pil->Fill(cluster_CENTER_X[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_yscore_sig->Fill(cluster_CENTER_Y[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_yscore_pil->Fill(cluster_CENTER_Y[i], funcScore(nodes_out[i]));}

         if (labels_test[i] == 1) {h2_zscore_sig->Fill(cluster_CENTER_Z[i], funcScore(nodes_out[i]));}
         if (labels_test[i] == 0) {h2_zscore_pil->Fill(cluster_CENTER_Z[i], funcScore(nodes_out[i]));}


         if ((0 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.1))) {
             if (labels_test[i] == 1) {h2_rzscore1sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore1pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.1 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.2))) {
             if (labels_test[i] == 1) {h2_rzscore2sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore2pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.2 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.3))) {
             if (labels_test[i] == 1) {h2_rzscore3sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore3pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.3 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.4))) {
             if (labels_test[i] == 1) {h2_rzscore4sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore4pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.4 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.5))) {
             if (labels_test[i] == 1) {h2_rzscore5sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore5pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.5 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.6))) {
             if (labels_test[i] == 1) {h2_rzscore6sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore6pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.6 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.7))) {
             if (labels_test[i] == 1) {h2_rzscore7sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore7pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.7 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.8))) {
             if (labels_test[i] == 1) {h2_rzscore8sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore8pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.8 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] < 0.9))) {
             if (labels_test[i] == 1) {h2_rzscore9sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore9pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }
         if ((0.9 <= funcScore(nodes_out[i])) && (funcScore(nodes_out[i] <= 1))) {
             if (labels_test[i] == 1) {h2_rzscore10sig->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
             if (labels_test[i] == 0) {h2_rzscore10pil->Fill(cluster_CENTER_Z[i], TMath::Power(TMath::Power(cluster_CENTER_X[i], 2) + TMath::Power(cluster_CENTER_Y[i], 2), 0.5));}
         }

         
         if (labels_test[i] == 1) { hScore_signal->Fill(nodes_out[i]); }
         if (labels_test[i] == 0) { hScore_pileup->Fill(nodes_out[i]); }
      }
      hSumClusterE->Fill(sumClusE_EM);
      // std::cout << " jetRawE: " << jetRawE
      //           << " sum: " << sumClusE_EM 
      //           << std::endl;

      h2_area->Fill(    jetCalE, jetAreaE        / truthJetE);
      h2_Edep->Fill(    jetCalE, sum_ClusE_dep   / truthJetE);
      h2_labelsig->Fill(jetCalE, sum_ClusE_label / truthJetE);
      h2_ml->Fill(      jetCalE, sum_ClusE_ml    / truthJetE);

   }

   TCanvas*c = new TCanvas("", "", 500, 500);
   c->SetLogy();
   hScore_signal->SetLineColor(kBlue);
   hScore_pileup->SetLineColor(kOrange);

   hScore_signal->GetXaxis()->SetTitle("Scores");
   hScore_signal->GetYaxis()->SetTitle("Number of clusters");
   hScore_signal->Draw("H");
   hScore_pileup->Draw("HSAME");
   c->SaveAs("./plots/scores.png");
   
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
   h2_ml->Draw("colz");
   d->SaveAs("./plots/h2_response/h2_ml.png");
   h2_labelsig->Draw("colz");
   d->SaveAs("./plots/h2_response/h2_label.png");
   d->Close();

   TCanvas*t = new TCanvas("", "", 500, 500);
   t->SetLogz();
   h2_sigtimescore->Draw("colz");
   t->SaveAs("./plots/h2_time/timescore_sig.png");
   h2_piltimescore->Draw("colz");
   t->SaveAs("./plots/h2_time/timescore_pil.png");
   t->Close();

   TCanvas*n = new TCanvas("", "", 500, 500);
   n->SetLogz();
   h2_npvscore_sig->Draw("colz");
   n->SaveAs("./plots/h2_npv/npvscore_sig.png");
   h2_npvscore_pil->Draw("colz");
   n->SaveAs("./plots/h2_npv/npvscore_pil.png");
   n->Close();

   TCanvas*e = new TCanvas("", "", 500, 500);
   e->SetLogz();
   h2_etascore_sig->Draw("colz");
   e->SaveAs("./plots/h2_eta/etascore_sig.png");
   h2_etascore_pil->Draw("colz");
   e->SaveAs("./plots/h2_eta/etascore_pil.png");
   e->Close();

   TCanvas*m = new TCanvas("", "", 500, 500);
   m->SetLogz();
   h2_muscore_sig->Draw("colz");
   m->SaveAs("./plots/h2_mu/muscore_sig.png");
   h2_muscore_pil->Draw("colz");
   m->SaveAs("./plots/h2_mu/muscore_pil.png");
   m->Close();

   TCanvas*a = new TCanvas("", "", 500, 500);
   a->SetLogz();
   h2_lambdascore_sig->Draw("colz");
   a->SaveAs("./plots/h2_lambda/lambdascore_sig.png");
   h2_lambdascore_pil->Draw("colz");
   a->SaveAs("./plots/h2_lambda/lambdascore_pil.png");
   a->Close();

   TCanvas*x = new TCanvas("", "", 500, 500);
   x->SetLogz();
   h2_xscore_sig->Draw("colz");
   x->SaveAs("./plots/h2_x/xscore_sig.png");
   h2_xscore_pil->Draw("colz");
   x->SaveAs("./plots/h2_x/xscore_pil.png");
   x->Close();

   TCanvas*y = new TCanvas("", "", 500, 500);
   y->SetLogz();
   h2_yscore_sig->Draw("colz");
   y->SaveAs("./plots/h2_y/yscore_sig.png");
   h2_yscore_pil->Draw("colz");
   y->SaveAs("./plots/h2_y/yscore_pil.png");
   y->Close();

   TCanvas*z = new TCanvas("", "", 500, 500);
   z->SetLogz();
   h2_zscore_sig->Draw("colz");
   z->SaveAs("./plots/h2_z/zscore_sig.png");
   h2_zscore_pil->Draw("colz");
   z->SaveAs("./plots/h2_z/zscore_pil.png");
   z->Close();

    
   TCanvas*r1 = new TCanvas("", "", 500, 500);
   r1->SetLogz();
   h2_rzscore1sig->Draw("colz");
   r1->SaveAs("./plots/h2_rz/rzscore1_sig.png");
   h2_rzscore1pil->Draw("colz");
   r1->SaveAs("./plots/h2_rz/rzscore1_pil.png");
   r1->Close();
    
   TCanvas*r2 = new TCanvas("", "", 500, 500);
   r2->SetLogz();
   h2_rzscore2sig->Draw("colz");
   r2->SaveAs("./plots/h2_rz/rzscore2_sig.png");
   h2_rzscore2pil->Draw("colz");
   r2->SaveAs("./plots/h2_rz/rzscore2_pil.png");
   r2->Close();
    
   TCanvas*r3 = new TCanvas("", "", 500, 500);
   r3->SetLogz();
   h2_rzscore3sig->Draw("colz");
   r3->SaveAs("./plots/h2_rz/rzscore3_sig.png");
   h2_rzscore3pil->Draw("colz");
   r3->SaveAs("./plots/h2_rz/rzscore3_pil.png");
   r3->Close();

   TCanvas*r4 = new TCanvas("", "", 500, 500);
   r4->SetLogz();
   h2_rzscore4sig->Draw("colz");
   r4->SaveAs("./plots/h2_rz/rzscore4_sig.png");
   h2_rzscore4pil->Draw("colz");
   r4->SaveAs("./plots/h2_rz/rzscore4_pil.png");
   r4->Close();

   TCanvas*r5 = new TCanvas("", "", 500, 500);
   r5->SetLogz();
   h2_rzscore5sig->Draw("colz");
   r5->SaveAs("./plots/h2_rz/rzscore5_sig.png");
   h2_rzscore5pil->Draw("colz");
   r5->SaveAs("./plots/h2_rz/rzscore5_pil.png");
   r5->Close();

   TCanvas*r6 = new TCanvas("", "", 500, 500);
   r6->SetLogz();
   h2_rzscore6sig->Draw("colz");
   r6->SaveAs("./plots/h2_rz/rzscore6_sig.png");
   h2_rzscore6pil->Draw("colz");
   r6->SaveAs("./plots/h2_rz/rzscore6_pil.png");
   r6->Close();

   TCanvas*r7 = new TCanvas("", "", 500, 500);
   r7->SetLogz();
   h2_rzscore7sig->Draw("colz");
   r7->SaveAs("./plots/h2_rz/rzscore7_sig.png");
   h2_rzscore7pil->Draw("colz");
   r7->SaveAs("./plots/h2_rz/rzscore7_pil.png");
   r7->Close();

   TCanvas*r8 = new TCanvas("", "", 500, 500);
   r8->SetLogz();
   h2_rzscore8sig->Draw("colz");
   r8->SaveAs("./plots/h2_rz/rzscore8_sig.png");
   h2_rzscore8pil->Draw("colz");
   r8->SaveAs("./plots/h2_rz/rzscore8_pil.png");
   r8->Close();

   TCanvas*r9 = new TCanvas("", "", 500, 500);
   r9->SetLogz();
   h2_rzscore9sig->Draw("colz");
   r9->SaveAs("./plots/h2_rz/rzscore9_sig.png");
   h2_rzscore9pil->Draw("colz");
   r9->SaveAs("./plots/h2_rz/rzscore9_pil.png");
   r9->Close();

   TCanvas*r10 = new TCanvas("", "", 500, 500);
   r10->SetLogz();
   h2_rzscore10sig->Draw("colz");
   r10->SaveAs("./plots/h2_rz/rzscore10_sig.png");
   h2_rzscore10pil->Draw("colz");
   r10->SaveAs("./plots/h2_rz/rzscore10_pil.png");
   r10->Close();
    
    
   TH1D* h_area_median     = new TH1D("", "", Nbins, bins);
   TH1D* h_Edep_median     = new TH1D("", "", Nbins, bins);
   TH1D* h_labelsig_median = new TH1D("", "", Nbins, bins);
   TH1D* h_ml_median       = new TH1D("", "", Nbins, bins);

   TH1D* h_area_iqr     = new TH1D("", "", Nbins, bins);
   TH1D* h_Edep_iqr     = new TH1D("", "", Nbins, bins);
   TH1D* h_labelsig_iqr = new TH1D("", "", Nbins, bins);
   TH1D* h_ml_iqr       = new TH1D("", "", Nbins, bins);

   FillHisto_MedianIQR(h_area_median, h_area_iqr, h2_area);
   FillHisto_MedianIQR(h_Edep_median, h_Edep_iqr, h2_Edep);
   FillHisto_MedianIQR(h_labelsig_median, h_labelsig_iqr, h2_labelsig);
   FillHisto_MedianIQR(h_ml_median, h_ml_iqr, h2_ml);

   h_area_median->SetLineColor(kAzure + 7);
   h_Edep_median->SetLineColor(TColor::GetColor("#FF8C00"));
   h_labelsig_median->SetLineColor(TColor::GetColor("#008026"));
   h_ml_median->SetLineColor(TColor::GetColor("#732982"));

   h_area_iqr->SetLineColor(kAzure + 7);
   h_Edep_iqr->SetLineColor(TColor::GetColor("#FF8C00"));
   h_labelsig_iqr->SetLineColor(TColor::GetColor("#008026"));
   h_ml_iqr->SetLineColor(TColor::GetColor("#732982"));

   TLegend* lMed = new TLegend(0.7, 0.7, 0.9, 0.9);
   lMed->AddEntry(h_area_median, "ATLAS", "l");
   lMed->AddEntry(h_Edep_median, "Truth", "l");
   lMed->AddEntry(h_labelsig_median, "Label", "l");
   lMed->AddEntry(h_ml_median, "ML", "l");

   TCanvas*cMedian = new TCanvas("", "", 500, 500);
   cMedian->SetLogx();
 
   h_area_median->GetYaxis()->SetRangeUser(0, 2);
   h_area_median->GetXaxis()->SetRangeUser(10, 2000);
   h_area_median->Draw("H");
   h_Edep_median->Draw("HSAME");
   h_labelsig_median->Draw("HSAME");
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
   h_labelsig_iqr->Draw("HSAME");
   h_ml_iqr->Draw("HSAME");
   lMed->Draw("SAME");
   cIQR->SaveAs("./plots/iqr.png");
   

   //////////////////////////////////////////////////
   //////////////////////////////////////////////////

  

}
