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
#include <utility>
#include <cmath>

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


std::pair<TH1D*, TH1D*>FillHisto_MedianIQR(Int_t Nbins, const Double_t* bins, const TH2D* h2){ 

   TH1D* hmedian = new TH1D("", "", Nbins, bins);
   TH1D* hiqr    = new TH1D("", "", Nbins, bins);

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
   
   return {hmedian, hiqr};
   

}


std::vector<double> LogBins(double xmin_log10, double xmax_log10, int nbins){
   
   ////// 
   std::vector<double> bins(nbins + 1);

   const double width = (xmax_log10 - xmin_log10) / nbins;

   for (int i = 0; i <= nbins; ++i) {
      bins[i] = std::pow(10.0, xmin_log10 + i * width);
   }
   return bins;
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
   

   // 
   const int Nbins_E = 100;
   auto bins_E = LogBins(-3.0, 2.0, Nbins_E);

   TH2D* h2_area     = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_Edep     = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_labelsig = new TH2D("", "", Nbins, bins, 100, 0.05, 2);
   TH2D* h2_ml       = new TH2D("", "", Nbins, bins, 100, 0.05, 2);

   ////////////////////////////
   TH2D* h2_Edep_Eem_all        = new TH2D("", "", Nbins, bins_E.data(), Nbins, bins_E.data());
   TH2D* h2_Edep_Eem_signal     = new TH2D("", "", Nbins, bins_E.data(), Nbins, bins_E.data());
   TH2D* h2_Edep_Eem_pileup     = new TH2D("", "", Nbins, bins_E.data(), Nbins, bins_E.data());

   /// signal 
   TH2D* h2_Edep_signal   = new TH2D("", "", Nbins, bins_E.data(), 100, 0, 1);
   TH2D* h2_Eem_signal    = new TH2D("", "", Nbins, bins_E.data(), 100, 0, 1);
   TH2D* h2_long_signal   = new TH2D("", "", 100, 0, 1, 100, 0, 1);
   TH2D* h2_lat_signal    = new TH2D("", "", 100, 0, 1, 100, 0, 1);
   TH2D* h2_isol_signal   = new TH2D("", "", 100, 0, 1, 100, 0, 1);
   TH2D* h2_time_signal   = new TH2D("", "", 100, -50, 50, 100, 0, 1);

   /// pileup 
   TH2D* h2_Edep_pileup   = new TH2D("", "", Nbins, bins_E.data(), 100, 0, 1);
   TH2D* h2_Eem_pileup    = new TH2D("", "", Nbins, bins_E.data(), 100, 0, 1);
   TH2D* h2_long_pileup   = new TH2D("", "", 100, 0, 1, 100, 0, 1);
   TH2D* h2_lat_pileup    = new TH2D("", "", 100, 0, 1, 100, 0, 1);
   TH2D* h2_isol_pileup   = new TH2D("", "", 100, 0, 1, 100, 0, 1);
   TH2D* h2_time_pileup   = new TH2D("", "", 100, -50, 50, 100, 0, 1);

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
         
         h2_Edep_Eem_all->Fill(cluster_ENG_CALIB_TOT[i], clusterE[i]); 

         if (labels_test[i] == 1) { 
            hScore_signal->Fill(nodes_out[i]); 
            h2_Edep_Eem_signal->Fill(cluster_ENG_CALIB_TOT[i], clusterE[i]); 
            h2_Edep_signal->Fill(cluster_ENG_CALIB_TOT[i], nodes_out[i]); 
            h2_Eem_signal->Fill(clusterE[i], nodes_out[i]); 
            h2_long_signal->Fill(cluster_LONGITUDINAL[i], nodes_out[i]); 
            h2_lat_signal->Fill(cluster_LATERAL[i], nodes_out[i]); 
            h2_isol_signal->Fill(cluster_ISOLATION[i], nodes_out[i]);   
            h2_time_signal->Fill(cluster_time[i], nodes_out[i]);   
         }
         if (labels_test[i] == 0) { 
            hScore_pileup->Fill(nodes_out[i]); 
            h2_Edep_Eem_pileup->Fill(cluster_ENG_CALIB_TOT[i], clusterE[i]); 
            h2_Edep_pileup->Fill(cluster_ENG_CALIB_TOT[i], nodes_out[i]); 
            h2_Eem_pileup->Fill(clusterE[i], nodes_out[i]); 
            h2_long_pileup->Fill(cluster_LONGITUDINAL[i], nodes_out[i]); 
            h2_lat_pileup->Fill(cluster_LATERAL[i], nodes_out[i]); 
            h2_isol_pileup->Fill(cluster_ISOLATION[i], nodes_out[i]);   
            h2_time_pileup->Fill(cluster_time[i], nodes_out[i]);   

         }

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

   // Get median and IQR from 2D Plots 
   auto [h_area_median,     h_area_iqr]     = FillHisto_MedianIQR(Nbins, bins, h2_area);
   auto [h_Edep_median,     h_Edep_iqr]     = FillHisto_MedianIQR(Nbins, bins, h2_Edep);
   auto [h_labelsig_median, h_labelsig_iqr] = FillHisto_MedianIQR(Nbins, bins, h2_labelsig);
   auto [h_ml_median,       h_ml_iqr]       = FillHisto_MedianIQR(Nbins, bins, h2_ml);

   TFile*fOutput = new TFile("finalHistos.root", "RECREATE"); 

   hSumClusterE->Write("sumClusterE");
   hJetRawE->Write("jetRawE");
   hScore_signal->Write("score_signal");
   hScore_pileup->Write("score_pileup");

   /// 
   h2_Edep_Eem_all   ->Write("Edep_Eem_all"); 
   h2_Edep_Eem_signal->Write("Edep_Eem_signal"); 
   h2_Edep_Eem_pileup->Write("Edep_Eem_pileup"); 

   h2_Edep_signal->Write("score_Edep_signal"); 
   h2_Eem_signal ->Write("score_Eem_signal"); 
   h2_long_signal->Write("score_long_signal"); 
   h2_lat_signal ->Write("score_lat_signal"); 
   h2_isol_signal->Write("score_isol_signal"); 
   h2_time_signal->Write("score_time_signal"); 

   /// pileup 
   h2_Edep_pileup->Write("score_Edep_pileup"); 
   h2_Eem_pileup ->Write("score_Eem_pileup"); 
   h2_long_pileup->Write("score_long_pileup"); 
   h2_lat_pileup ->Write("score_lat_pileup"); 
   h2_isol_pileup->Write("score_isol_pileup"); 
   h2_time_pileup->Write("score_time_pileup"); 


   //
   h_area_median    ->Write("JetResponse_median_area"); 
   h_Edep_median    ->Write("JetResponse_median_edep"); 
   h_labelsig_median->Write("JetResponse_median_labelsig"); 
   h_ml_median      ->Write("JetResponse_median_ml"); 
   
   h_area_iqr    ->Write("JetResponse_iqr_area"); 
   h_Edep_iqr    ->Write("JetResponse_iqr_edep"); 
   h_labelsig_iqr->Write("JetResponse_iqr_labelsig"); 
   h_ml_iqr      ->Write("JetResponse_iqr_ml"); 

   fOutput->Close(); 
   
   //////////////////////////////////////////////////
   //////////////////////////////////////////////////
 
   //////////////////////////////////////////////////
   //////////////////////////////////////////////////
   // TH1D* h_area_median     = new TH1D("", "", Nbins, bins);
   // TH1D* h_Edep_median     = new TH1D("", "", Nbins, bins);
   // TH1D* h_labelsig_median = new TH1D("", "", Nbins, bins);
   // TH1D* h_ml_median       = new TH1D("", "", Nbins, bins);

   // TH1D* h_area_iqr     = new TH1D("", "", Nbins, bins);
   // TH1D* h_Edep_iqr     = new TH1D("", "", Nbins, bins);
   // TH1D* h_labelsig_iqr = new TH1D("", "", Nbins, bins);
   // TH1D* h_ml_iqr       = new TH1D("", "", Nbins, bins);

   // FillHisto_MedianIQR(h_area_median, h_area_iqr, h2_area);
   // FillHisto_MedianIQR(h_Edep_median, h_Edep_iqr, h2_Edep);
   // FillHisto_MedianIQR(h_labelsig_median, h_labelsig_iqr, h2_labelsig);
   // FillHisto_MedianIQR(h_ml_median, h_ml_iqr, h2_ml);

   // h_area_median->SetLineColor(kAzure + 7);
   // h_Edep_median->SetLineColor(TColor::GetColor("#FF8C00"));
   // h_labelsig_median->SetLineColor(TColor::GetColor("#008026"));
   // h_ml_median->SetLineColor(TColor::GetColor("#732982"));

   // h_area_iqr->SetLineColor(kAzure + 7);
   // h_Edep_iqr->SetLineColor(TColor::GetColor("#FF8C00"));
   // h_labelsig_iqr->SetLineColor(TColor::GetColor("#008026"));
   // h_ml_iqr->SetLineColor(TColor::GetColor("#732982"));

   // TLegend* lMed = new TLegend(0.7, 0.7, 0.9, 0.9);
   // lMed->AddEntry(h_area_median, "ATLAS", "l");
   // lMed->AddEntry(h_Edep_median, "Truth", "l");
   // lMed->AddEntry(h_labelsig_median, "Label", "l");
   // lMed->AddEntry(h_ml_median, "ML", "l");

   // TCanvas*cMedian = new TCanvas("", "", 500, 500);
   // cMedian->SetLogx();
 
   // h_area_median->GetYaxis()->SetRangeUser(0, 2);
   // h_area_median->GetXaxis()->SetRangeUser(10, 2000);
   // h_area_median->Draw("H");
   // h_Edep_median->Draw("HSAME");
   // h_labelsig_median->Draw("HSAME");
   // h_ml_median->Draw("HSAME");
   // lMed->Draw("SAME");
   // cMedian->SaveAs("./median.png");

   // TCanvas*cIQR = new TCanvas("", "", 500, 500);
   // cIQR->SetLogx();
  

   // h_area_iqr->GetYaxis()->SetRangeUser(0, 2);
   // h_area_iqr->GetXaxis()->SetRangeUser(10, 2000); 
   // h_area_iqr->Draw("H");
   // h_Edep_iqr->Draw("HSAME");
   // h_labelsig_iqr->Draw("HSAME");
   // h_ml_iqr->Draw("HSAME");
   // lMed->Draw("SAME");
   // cIQR->SaveAs("./iqr.png");
   

   //////////////////////////////////////////////////
   //////////////////////////////////////////////////

  

}
