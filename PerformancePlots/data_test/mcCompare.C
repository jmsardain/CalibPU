#define mcCompare_cxx
#include "mcCompare.h"
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

void mcCompare::Loop()
{
//   In a ROOT session, you can do:
//      root> .L mcCompare.C
//      root> mcCompare t
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


   TH2D* h2_jet_pt_eta = new TH2D("", "", Nbins, -5, 5, Nbins, bins);
   TH2D* h2_clust_pt_eta = new TH2D("", "", Nbins, -5, 5, Nbins, bins);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      h2_jet_pt_eta->Fill(jetCalEta, jetCalPt);
      h2_clust_pt_eta->Fill(clusterEtaCalib, clusterPtCalib);
      //h2_clust_pt_eta->Fill(clusterEta, clusterPt);

   }
   TCanvas*c1 = new TCanvas("", "", 500, 500);
   c1->SetLogz();
   c1->SetLogy();
   h2_jet_pt_eta->GetYaxis()->SetTitle("Jet p_{T}");
   h2_jet_pt_eta->GetXaxis()->SetTitle("Jet #eta");
   h2_jet_pt_eta->Draw("COLZ");
   c1->SaveAs("./plots/mc/ptEta/mc_jet_eta_pt.png");

   TCanvas*c2 = new TCanvas("", "", 500, 500);
   c2->SetLogz();
   c2->SetLogy();
   h2_clust_pt_eta->GetYaxis()->SetTitle("Cluster p_{T}");
   h2_clust_pt_eta->GetXaxis()->SetTitle("Cluster #eta");
   h2_clust_pt_eta->Draw("COLZ");
   c2->SaveAs("./plots/mc/ptEta/mc_cluster_eta_pt.png");
}
