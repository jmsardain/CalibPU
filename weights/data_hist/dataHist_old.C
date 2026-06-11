#define dataHist_cxx
#include "dataHist.h"
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

void dataHist::Loop()
{
//   In a ROOT session, you can do:
//      root> .L dataCompare.C
//      root> dataCompare t
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
   // Double_t bins[Nbins + 1] = {10.        ,  10.42317429,  10.86425624,  11.32400363,
   //      11.80320636,  12.30268771,  12.82330583,  13.36595517,
   //      13.93156803,  14.52111618,  15.13561248,  15.7761127 ,
   //      16.44371723,  17.13957308,  17.86487575,  18.62087137,
   //      19.40885878,  20.23019179,  21.0862815 ,  21.97859873,
   //      22.90867653,  23.87811283,  24.88857318,  25.94179362,
   //      27.03958364,  28.18382931,  29.37649652,  30.61963434,
   //      31.91537855,  33.26595533,  34.67368505,  36.14098626,
   //      37.6703799 ,  39.26449354,  40.92606597,  42.65795188,
   //      44.46312675,  46.34469197,  48.3058802 ,  50.35006088,
   //      52.48074602,  54.70159629,  57.01642723,  59.42921586,
   //      61.94410751,  64.5654229 ,  67.29766563,  70.14552984,
   //      73.11390835,  76.207901  ,  79.43282347,  82.79421637,
   //      86.29785478,  89.94975815,  93.75620069,  97.7237221 ,
   //     101.85913881, 106.16955572, 110.6623784 , 115.34532578,
   //     120.22644346, 125.31411749, 130.61708881, 136.14446825,
   //     141.90575217, 147.91083882, 154.17004529, 160.6941253 ,
   //     167.4942876 , 174.58221529, 181.97008586, 189.67059212,
   //     197.69696401, 206.06299133, 214.78304741, 223.87211386,
   //     233.34580623, 243.22040091, 253.51286305, 264.24087573,
   //     275.42287033, 287.0780582 , 299.22646366, 311.88895841,
   //     325.08729739, 338.84415614, 353.18316979, 368.12897364,
   //     383.70724549, 399.94474976, 416.86938347, 434.51022417,
   //     452.8975799 , 472.06304126, 492.03953568, 512.86138399,
   //     534.5643594 , 557.18574893, 580.76441752, 605.34087475,
   //     630.95734448};

   Double_t bins[Nbins + 1] = {1.00000000e-01, 1.09647820e-01, 1.20226443e-01, 1.31825674e-01,
 1.44543977e-01, 1.58489319e-01, 1.73780083e-01, 1.90546072e-01,
 2.08929613e-01, 2.29086765e-01, 2.51188643e-01, 2.75422870e-01,
 3.01995172e-01, 3.31131121e-01, 3.63078055e-01, 3.98107171e-01,
 4.36515832e-01, 4.78630092e-01, 5.24807460e-01, 5.75439937e-01,
 6.30957344e-01, 6.91830971e-01, 7.58577575e-01, 8.31763771e-01,
 9.12010839e-01, 1.00000000e+00, 1.09647820e+00, 1.20226443e+00,
 1.31825674e+00, 1.44543977e+00, 1.58489319e+00, 1.73780083e+00,
 1.90546072e+00, 2.08929613e+00, 2.29086765e+00, 2.51188643e+00,
 2.75422870e+00, 3.01995172e+00, 3.31131121e+00, 3.63078055e+00,
 3.98107171e+00, 4.36515832e+00, 4.78630092e+00, 5.24807460e+00,
 5.75439937e+00, 6.30957344e+00, 6.91830971e+00, 7.58577575e+00,
 8.31763771e+00, 9.12010839e+00, 1.00000000e+01, 1.09647820e+01,
 1.20226443e+01, 1.31825674e+01, 1.44543977e+01, 1.58489319e+01,
 1.73780083e+01, 1.90546072e+01, 2.08929613e+01, 2.29086765e+01,
 2.51188643e+01, 2.75422870e+01, 3.01995172e+01, 3.31131121e+01,
 3.63078055e+01, 3.98107171e+01, 4.36515832e+01, 4.78630092e+01,
 5.24807460e+01, 5.75439937e+01, 6.30957344e+01, 6.91830971e+01,
 7.58577575e+01, 8.31763771e+01, 9.12010839e+01, 1.00000000e+02,
 1.09647820e+02, 1.20226443e+02, 1.31825674e+02, 1.44543977e+02,
 1.58489319e+02, 1.73780083e+02, 1.90546072e+02, 2.08929613e+02,
 2.29086765e+02, 2.51188643e+02, 2.75422870e+02, 3.01995172e+02,
 3.31131121e+02, 3.63078055e+02, 3.98107171e+02, 4.36515832e+02,
 4.78630092e+02, 5.24807460e+02, 5.75439937e+02, 6.30957344e+02,
 6.91830971e+02, 7.58577575e+02, 8.31763771e+02, 9.12010839e+02,
 1.00000000e+03};


   TH2D* h2_jet_pt_eta = new TH2D("", "", Nbins, -5, 5, Nbins, bins);
   TH2D* h2_clust_pt_eta = new TH2D("", "", Nbins, -5, 5, Nbins, bins);

   TH1D* h_mu = new TH1D("", "", Nbins, 0, 100);
   TH1D* h_eng_dens = new TH1D("", "", Nbins, -1, 1);
   TH1D* h_lateral = new TH1D("", "", Nbins, 0, 1);
   TH1D* h_longitudinal = new TH1D("", "", Nbins, 0, 1);
   TH1D* h_second_time = new TH1D("", "", Nbins, -100, 100);
   TH1D* h_ptd = new TH1D("", "", Nbins, 0, 1);
   TH1D* h_iso = new TH1D("", "", Nbins, 0, 1);
   TH1D* h_signif = new TH1D("", "", Nbins, 0, 100);
   TH1D* h_lambda = new TH1D("", "", Nbins, -0.2, 100);
   TH1D* h_fracEm = new TH1D("", "", Nbins, 0, 1);
   TH1D* h_mag = new TH1D("", "", Nbins, 1200, 3000);
   TH1D* h_clusterE = new TH1D("", "", Nbins, bins);
   TH1D* h_zT = new TH1D("", "", Nbins, 0, 2);
   TH1D* h_zL = new TH1D("", "", Nbins, 0, 1);
   TH1D* h_zRel = new TH1D("", "", Nbins, -3, 0.2);
   TH1D* h_diffEta = new TH1D("", "", Nbins, -1, 1);
   TH1D* h_npv = new TH1D("", "", Nbins, 0, 100);
   TH1D* h_nCells = new TH1D("", "", Nbins, 0, 100);
   TH1D* h_eta = new TH1D("", "", Nbins, -5, 5);
   TH1D* h_phi = new TH1D("", "", Nbins, -3.5, 3.5);
   TH1D* h_time = new TH1D("", "", Nbins, -100, 100);


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      h2_clust_pt_eta->Fill(clusterEta, clusterPt);
      h2_jet_pt_eta->Fill(jetCalEta, jetCalPt);
      h_mu->Fill(avgMu);
      h_zT->Fill(clusterE / jetRawPt);
      h_zL->Fill(clusterE / jetRawE);
      h_zRel->Fill(clusterE / jetRawE - clusterE / jetRawPt);
      h_diffEta->Fill(clusterEta - jetRawEta);
      h_clusterE->Fill(clusterE);
      h_npv->Fill(nPrimVtx);
      h_nCells->Fill(cluster_nCells);
      h_eta->Fill(clusterEta);
      h_phi->Fill(clusterPhi);
      h_time->Fill(cluster_time);
      h_eng_dens->Fill(cluster_FIRST_ENG_DENS);
      h_lateral->Fill(cluster_LATERAL);
      h_longitudinal->Fill(cluster_LONGITUDINAL);
      h_second_time->Fill(cluster_SECOND_TIME);
      h_ptd->Fill(cluster_PTD);
      h_iso->Fill(cluster_ISOLATION);
      h_signif->Fill(cluster_SIGNIFICANCE);
      h_lambda->Fill(cluster_CENTER_LAMBDA);
      h_fracEm->Fill(cluster_fracE);
      h_mag->Fill(cluster_CENTER_MAG);

   }
   // h2_clust_pt_eta->Scale(1.0/h2_clust_pt_eta->Integral());
   // h_mu->Scale(1.0/h_mu->Integral());
   // h_clusterE->Scale(1.0/h_clusterE->Integral());
   // h_zT->Scale(1.0/h_zT->Integral());
   // h_zL->Scale(1.0/h_zL->Integral());
   // h_zRel->Scale(1.0/h_zRel->Integral());
   // h_diffEta->Scale(1.0/h_diffEta->Integral());
   // h_npv->Scale(1.0/h_npv->Integral());
   // h_nCells->Scale(1.0/h_nCells->Integral());
   // h_eta->Scale(1.0/h_eta->Integral());
   // h_phi->Scale(1.0/h_phi->Integral());
   // h_time->Scale(1.0/h_time->Integral());
   // h_eng_dens->Scale(1.0/h_eng_dens->Integral());
   // h_lateral->Scale(1.0/h_lateral->Integral());
   // h_longitudinal->Scale(1.0/h_longitudinal->Integral());
   // h_second_time->Scale(1.0/h_second_time->Integral());
   // h_ptd->Scale(1.0/h_ptd->Integral());
   // h_iso->Scale(1.0/h_iso->Integral());
   // h_signif->Scale(1.0/h_signif->Integral());
   // h_lambda->Scale(1.0/h_lambda->Integral());
   // h_fracEm->Scale(1.0/h_fracEm->Integral());
   // h_mag->Scale(1.0/h_mag->Integral());

   TFile *fout = new TFile("/home/dsmith/CalibPU/weights/data_hist/data_hist.root", "RECREATE");
   h2_clust_pt_eta->Write("h2_clust_pt_eta");
   h2_jet_pt_eta->Write("h2_jet_pt_eta");
   h_mu->Write("h_mu");
   h_clusterE->Write("h_clusterE");
   h_zT->Write("h_zT");
   h_zL->Write("h_zL");
   h_zRel->Write("h_zRel");
   h_diffEta->Write("h_diffEta");
   h_npv->Write("h_npv");
   h_nCells->Write("h_nCells");
   h_eta->Write("h_eta");
   h_phi->Write("h_phi");
   h_time->Write("h_time");
   h_eng_dens->Write("h_eng_dens");
   h_lateral->Write("h_lateral");
   h_longitudinal->Write("h_longitudinal");
   h_second_time->Write("h_second_time");
   h_ptd->Write("h_ptd");
   h_iso->Write("h_iso");
   h_signif->Write("h_signif");
   h_lambda->Write("h_lambda");
   h_fracEm->Write("h_fracEm");
   h_mag->Write("h_mag");
   fout->Close();

   h2_clust_pt_eta->Scale(1.0/h2_clust_pt_eta->Integral());
   h_mu->Scale(1.0/h_mu->Integral());

   TCanvas *mu = new TCanvas("", "", 500, 500);
   mu->SetLogy();
   h_mu->GetYaxis()->SetMoreLogLabels();
   h_mu->GetXaxis()->SetTitle("Cluster #mu");
   h_mu->GetYaxis()->SetTitle("Entries");
   h_mu->Draw();
   mu->SaveAs("/home/dsmith/CalibPU/weights/data_hist/data_mu.png");

   TCanvas*c2 = new TCanvas("", "", 500, 500);
   c2->SetLogz();
   c2->SetLogy();
   h2_clust_pt_eta->GetYaxis()->SetMoreLogLabels();
   h2_clust_pt_eta->GetYaxis()->SetTitle("Cluster p_{T}");
   h2_clust_pt_eta->GetXaxis()->SetTitle("Cluster #eta");
   h2_clust_pt_eta->Draw("COLZ");
   c2->SaveAs("/home/dsmith/CalibPU/weights/data_hist/data_cluster_eta_pt.png");

   TCanvas*c3 = new TCanvas("", "", 500, 500);
   c3->SetLogz();
   c3->SetLogy();
   h2_jet_pt_eta->GetYaxis()->SetMoreLogLabels();
   h2_jet_pt_eta->GetYaxis()->SetTitle("Jet p_{T}");
   h2_jet_pt_eta->GetXaxis()->SetTitle("Jet #eta");
   h2_jet_pt_eta->Draw("COLZ");
   c3->SaveAs("/home/dsmith/CalibPU/weights/data_hist/data_jet_eta_pt.png");
}
