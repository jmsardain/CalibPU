#define GetWeights_cxx
#include "GetWeights.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>


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

void GetWeights::Loop()
{
//   In a ROOT session, you can do:
//      root> .L GetWeights.C
//      root> GetWeights t
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

   TFile *fdata = new TFile("/home/dsmith/CalibPU/weights/data_hist/data_hist.root");
   TFile *fmc = new TFile("/home/dsmith/CalibPU/weights/mc_hist/mc_hist.root");

   TH2D* h2_clust_pt_eta_data = (TH2D*)fdata->Get("h2_clust_pt_eta");
   TH1D* h_mu_data = (TH1D*)fdata->Get("h_mu");

   TH2D* h2_clust_pt_eta_mc = (TH2D*)fmc->Get("h2_clust_pt_eta");
   TH1D* h_mu_mc = (TH1D*)fmc->Get("h_mu");
   TH1D* h_E_mc = (TH1D*)fmc->Get("h_clusterE");
   TH1D* h_zT_mc = (TH1D*)fmc->Get("h_zT");
   TH1D* h_zL_mc = (TH1D*)fmc->Get("h_zL");
   TH1D* h_zRel_mc = (TH1D*)fmc->Get("h_zRel");
   TH1D* h_diffEta_mc = (TH1D*)fmc->Get("h_diffEta");
   TH1D* h_npv_mc = (TH1D*)fmc->Get("h_npv");
   TH1D* h_ncells_mc = (TH1D*)fmc->Get("h_nCells");
   TH1D* h_eta_mc = (TH1D*)fmc->Get("h_eta");
   TH1D* h_phi_mc = (TH1D*)fmc->Get("h_phi");
   TH1D* h_time_mc = (TH1D*)fmc->Get("h_time");
   TH1D* h_eng_dens_mc = (TH1D*)fmc->Get("h_eng_dens");
   TH1D* h_lateral_mc = (TH1D*)fmc->Get("h_lateral");
   TH1D* h_longitudinal_mc = (TH1D*)fmc->Get("h_longitudinal");
   TH1D* h_second_time_mc = (TH1D*)fmc->Get("h_second_time");
   TH1D* h_ptd_mc = (TH1D*)fmc->Get("h_ptd");
   TH1D* h_iso_mc = (TH1D*)fmc->Get("h_iso");
   TH1D* h_signif_mc = (TH1D*)fmc->Get("h_signif");
   TH1D* h_lambda_mc = (TH1D*)fmc->Get("h_lambda");
   TH1D* h_fracEm_mc = (TH1D*)fmc->Get("h_fracEm");
   TH1D* h_mag_mc = (TH1D*)fmc->Get("h_mag");


   TH2D* divide_Pt_Eta = new TH2D(*h2_clust_pt_eta_mc);
   divide_Pt_Eta->Divide(h2_clust_pt_eta_data);

   TH1D* divide_mu = new TH1D(*h_mu_mc);
   divide_mu->Divide(h_mu_data);

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

   TH1D* weight_clusterE = new TH1D("", "", Nbins, bins);
   TH1D* weight_zT = new TH1D("", "", Nbins, 0, 2);
   TH1D* weight_zL = new TH1D("", "", Nbins, 0, 1);
   TH1D* weight_zRel = new TH1D("", "", Nbins, -3, 0.2);
   TH1D* weight_diffEta = new TH1D("", "", Nbins, -1, 1);
   TH1D* weight_npv = new TH1D("", "", Nbins, 0, 100);
   TH1D* weight_ncells = new TH1D("", "", Nbins, 0, 100);
   TH1D* weight_eta = new TH1D("", "", Nbins, -5, 5);
   TH1D* weight_phi = new TH1D("", "", Nbins, -3.5, 3.5);
   TH1D* weight_time = new TH1D("", "", Nbins, -100, 100);
   TH1D* weight_eng_dens = new TH1D("", "", Nbins, 0, 100);
   TH1D* weight_lateral = new TH1D("", "", Nbins, 0, 1);
   TH1D* weight_longitudinal = new TH1D("", "", Nbins, 0, 1);
   TH1D* weight_second_time = new TH1D("", "", Nbins, -100, 100);
   TH1D* weight_ptd = new TH1D("", "", Nbins, 0, 1);
   TH1D* weight_iso = new TH1D("", "", Nbins, 0, 1);
   TH1D* weight_signif = new TH1D("", "", Nbins, 0, 100);
   TH1D* weight_lambda = new TH1D("", "", Nbins, -0.2, 12);
   TH1D* weight_fracEm = new TH1D("", "", Nbins, 0, 1);
   TH1D* weight_mag = new TH1D("", "", Nbins, 0, 2000);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if ((clusterPt > 10) && (clusterPt < 630.95734448)){
         double weight1 = divide_Pt_Eta->GetBinContent(divide_Pt_Eta->GetXaxis()->FindBin(clusterEta), divide_Pt_Eta->GetYaxis()->FindBin(clusterPt));
         double weight2 = divide_mu->GetBinContent(divide_mu->GetXaxis()->FindBin(avgMu));
         double weight = weight1 * weight2;
         weight_clusterE->Fill(clusterE, weight);
         weight_zT->Fill(clusterE / jetRawPt, weight);
         weight_zL->Fill(clusterE / jetRawE, weight);
         weight_zRel->Fill(clusterE / jetRawE - clusterE / jetRawPt, weight);
         weight_diffEta->Fill(clusterEta - jetRawEta, weight);
         weight_npv->Fill(nPrimVtx, weight);
         weight_ncells->Fill(cluster_nCells, weight);
         weight_eta->Fill(clusterEta, weight);
         weight_phi->Fill(clusterPhi, weight);
         weight_time->Fill(cluster_time, weight);
         weight_eng_dens->Fill(cluster_FIRST_ENG_DENS, weight);
         weight_lateral->Fill(cluster_LATERAL, weight);
         weight_longitudinal->Fill(cluster_LONGITUDINAL, weight);
         weight_second_time->Fill(cluster_SECOND_TIME, weight);
         weight_ptd->Fill(cluster_PTD, weight);
         weight_iso->Fill(cluster_ISOLATION, weight);
         weight_signif->Fill(cluster_SIGNIFICANCE, weight);
         weight_lambda->Fill(cluster_CENTER_LAMBDA, weight);
         weight_fracEm->Fill(cluster_fracE, weight);
         weight_mag->Fill(cluster_CENTER_MAG, weight);

      }
   }


   // TFile *fout = new TFile("./output/divide_hist.root", "RECREATE");
   // divide_Pt_Eta->Write("divide_Pt_Eta");
   // divide_mu->Write("divide_mu");
   // fout->Close();


   TLegend *l = new TLegend(0.7, 0.7, 0.9, 0.9);
   l->AddEntry(weight_clusterE, "Norm Weighted Data", "l");
   l->AddEntry(h_E_mc, "Norm MC", "l");


   TCanvas *c1 = new TCanvas("", "", 500, 500);
   c1->SetLogz();
   c1->SetLogy();
   divide_Pt_Eta->GetYaxis()->SetMoreLogLabels();
   divide_Pt_Eta->GetYaxis()->SetTitle("Cluster Pt");
   divide_Pt_Eta->GetXaxis()->SetTitle("Cluster #eta");
   divide_Pt_Eta->GetZaxis()->SetTitle("Entries (MC/Data)");
   divide_Pt_Eta->Draw("COLZ");
   c1->SaveAs("./output/pt_eta/weights_Pt_Eta.png");

   TCanvas *c2 = new TCanvas("", "", 500, 500);
   c2->SetLogy();
   divide_mu->GetYaxis()->SetMoreLogLabels();
   divide_mu->GetXaxis()->SetTitle("Avg #mu");
   divide_mu->GetYaxis()->SetTitle("Entries");
   divide_mu->Draw("HIST");
   l->Draw();
   c2->SaveAs("./output/scaled_mu.png");

   TCanvas *c3 = new TCanvas("", "", 500, 500);
   c3->SetLogy();
   c3->SetLogx();
   weight_clusterE->GetYaxis()->SetMoreLogLabels();
   weight_clusterE->GetXaxis()->SetMoreLogLabels();
   weight_clusterE->GetXaxis()->SetTitle("Cluster E");
   weight_clusterE->GetYaxis()->SetTitle("Entries");
   weight_clusterE->SetLineColorAlpha(kRed, 0.5);
   h_E_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_clusterE->Draw("HIST");
   h_E_mc->Draw("HIST SAME");
   l->Draw();
   c3->SaveAs("./output/scaled_E.png");

   TCanvas *c4 = new TCanvas("", "", 500, 500);
   c4->SetLogy();
   weight_npv->GetYaxis()->SetMoreLogLabels();
   weight_npv->GetXaxis()->SetTitle("NPV");
   weight_npv->GetYaxis()->SetTitle("Entries");
   weight_npv->SetLineColorAlpha(kRed, 0.5);
   h_npv_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_npv->Draw("HIST");
   h_npv_mc->Draw("HIST SAME");
   l->Draw();
   c4->SaveAs("./output/scaled_npv.png");

   TCanvas *c5 = new TCanvas("", "", 500, 500);
   c5->SetLogy();
   weight_ncells->GetYaxis()->SetMoreLogLabels();
   weight_ncells->GetXaxis()->SetTitle("NCells");
   weight_ncells->GetYaxis()->SetTitle("Entries");
   weight_ncells->SetLineColorAlpha(kRed, 0.5);
   h_ncells_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_ncells->Draw("HIST");
   h_ncells_mc->Draw("HIST SAME");
   l->Draw();
   c5->SaveAs("./output/scaled_ncells.png");

   TCanvas *c6 = new TCanvas("", "", 500, 500);
   c6->SetLogy();
   weight_zT->GetYaxis()->SetMoreLogLabels();
   weight_zT->GetXaxis()->SetTitle("zT");
   weight_zT->GetYaxis()->SetTitle("Entries");
   weight_zT->SetLineColorAlpha(kRed, 0.5);
   h_zT_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_zT->Draw("HIST");
   h_zT_mc->Draw("HIST SAME");
   l->Draw();
   c6->SaveAs("./output/scaled_zT.png");

   TCanvas *c7 = new TCanvas("", "", 500, 500);
   c7->SetLogy();
   weight_zL->GetYaxis()->SetMoreLogLabels();
   weight_zL->GetXaxis()->SetTitle("zL");
   weight_zL->GetYaxis()->SetTitle("Entries");
   weight_zL->SetLineColorAlpha(kRed, 0.5);
   h_zL_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_zL->Draw("HIST");
   h_zL_mc->Draw("HIST SAME");
   l->Draw();
   c7->SaveAs("./output/scaled_zL.png");

   TCanvas *c8 = new TCanvas("", "", 500, 500);
   c8->SetLogy();
   weight_zRel->GetYaxis()->SetMoreLogLabels();
   weight_zRel->GetXaxis()->SetTitle("zRel");
   weight_zRel->GetYaxis()->SetTitle("Entries");
   weight_zRel->SetLineColorAlpha(kRed, 0.5);
   h_zRel_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_zRel->Draw("HIST");
   h_zRel_mc->Draw("HIST SAME");
   l->Draw();
   c8->SaveAs("./output/scaled_zRel.png");

   TCanvas *c9 = new TCanvas("", "", 500, 500);
   c9->SetLogy();
   weight_diffEta->GetYaxis()->SetMoreLogLabels();
   weight_diffEta->GetXaxis()->SetTitle("diffEta");
   weight_diffEta->GetYaxis()->SetTitle("Entries");
   weight_diffEta->SetLineColorAlpha(kRed, 0.5);
   h_diffEta_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_diffEta->Draw("HIST");
   h_diffEta_mc->Draw("HIST SAME");
   l->Draw();
   c9->SaveAs("./output/scaled_diffEta.png");

   TCanvas *c10 = new TCanvas("", "", 500, 500);
   c10->SetLogy();
   weight_eta->GetYaxis()->SetMoreLogLabels();
   weight_eta->GetXaxis()->SetTitle("Cluster #eta");
   weight_eta->GetYaxis()->SetTitle("Entries");
   weight_eta->SetLineColorAlpha(kRed, 0.5);
   h_eta_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_eta->Draw("HIST");
   h_eta_mc->Draw("HIST SAME");
   l->Draw();
   c10->SaveAs("./output/scaled_Eta.png");

   TCanvas *c11 = new TCanvas("", "", 500, 500);
   c11->SetLogy();
   weight_phi->GetYaxis()->SetMoreLogLabels();
   weight_phi->GetXaxis()->SetTitle("Cluster #phi");
   weight_phi->GetYaxis()->SetTitle("Entries");
   weight_phi->SetLineColorAlpha(kRed, 0.5);
   h_phi_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_phi->Draw("HIST");
   h_phi_mc->Draw("HIST SAME");
   l->Draw();
   c11->SaveAs("./output/scaled_Phi.png");

   TCanvas *c12 = new TCanvas("", "", 500, 500);
   c12->SetLogy();
   weight_lambda->GetYaxis()->SetMoreLogLabels();
   weight_lambda->GetXaxis()->SetTitle("Cluster #lambda");
   weight_lambda->GetYaxis()->SetTitle("Entries");
   weight_lambda->SetLineColorAlpha(kRed, 0.5);
   h_lambda_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_lambda->Draw("HIST");
   h_lambda_mc->Draw("HIST SAME");
   l->Draw();
   c12->SaveAs("./output/scaled_Lambda.png");

   TCanvas *c13 = new TCanvas("", "", 500, 500);
   c13->SetLogy();
   weight_mag->GetYaxis()->SetMoreLogLabels();
   weight_mag->GetXaxis()->SetTitle("Cluster |p|");
   weight_mag->GetYaxis()->SetTitle("Entries");
   weight_mag->SetLineColorAlpha(kRed, 0.5);
   h_mag_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_mag->Draw("HIST");
   h_mag_mc->Draw("HIST SAME");
   l->Draw();
   c13->SaveAs("./output/scaled_mag.png");

   TCanvas *c14 = new TCanvas("", "", 500, 500);
   c14->SetLogy();
   weight_fracEm->GetYaxis()->SetMoreLogLabels();
   weight_fracEm->GetXaxis()->SetTitle("Cluster frac_em");
   weight_fracEm->GetYaxis()->SetTitle("Entries");
   weight_fracEm->SetLineColorAlpha(kRed, 0.5);
   h_fracEm_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_fracEm->Draw("HIST");
   h_fracEm_mc->Draw("HIST SAME");
   l->Draw();
   c14->SaveAs("./output/scaled_frac_em.png");

   TCanvas *c15 = new TCanvas("", "", 500, 500);
   c15->SetLogy();
   weight_eng_dens->GetYaxis()->SetMoreLogLabels();
   weight_eng_dens->GetXaxis()->SetTitle("Cluster eng_dens");
   weight_eng_dens->GetYaxis()->SetTitle("Entries");
   weight_eng_dens->SetLineColorAlpha(kRed, 0.5);
   h_eng_dens_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_eng_dens->Draw("HIST");
   h_eng_dens_mc->Draw("HIST SAME");
   l->Draw();
   c15->SaveAs("./output/scaled_eng_dens.png");

   TCanvas *c16 = new TCanvas("", "", 500, 500);
   c16->SetLogy();
   weight_lateral->GetYaxis()->SetMoreLogLabels();
   weight_lateral->GetXaxis()->SetTitle("Cluster lateral");
   weight_lateral->GetYaxis()->SetTitle("Entries");
   weight_lateral->SetLineColorAlpha(kRed, 0.5);
   h_lateral_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_lateral->Draw("HIST");
   h_lateral_mc->Draw("HIST SAME");
   l->Draw();
   c16->SaveAs("./output/scaled_lateral.png");

   TCanvas *c17 = new TCanvas("", "", 500, 500);
   c17->SetLogy();
   weight_longitudinal->GetYaxis()->SetMoreLogLabels();
   weight_longitudinal->GetXaxis()->SetTitle("Cluster longitudinal");
   weight_longitudinal->GetYaxis()->SetTitle("Entries");
   weight_longitudinal->SetLineColorAlpha(kRed, 0.5);
   h_longitudinal_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_longitudinal->Draw("HIST");
   h_longitudinal_mc->Draw("HIST SAME");
   l->Draw();
   c17->SaveAs("./output/scaled_longitudinal.png");

   TCanvas *c18 = new TCanvas("", "", 500, 500);
   c18->SetLogy();
   weight_second_time->GetYaxis()->SetMoreLogLabels();
   weight_second_time->GetXaxis()->SetTitle("Cluster second_time");
   weight_second_time->GetYaxis()->SetTitle("Entries");
   weight_second_time->SetLineColorAlpha(kRed, 0.5);
   h_second_time_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_second_time->Draw("HIST");
   h_second_time_mc->Draw("HIST SAME");
   l->Draw();
   c18->SaveAs("./output/scaled_second_time.png");

   TCanvas *c19 = new TCanvas("", "", 500, 500);
   c19->SetLogy();
   weight_ptd->GetYaxis()->SetMoreLogLabels();
   weight_ptd->GetXaxis()->SetTitle("Cluster ptd");
   weight_ptd->GetYaxis()->SetTitle("Entries");
   weight_ptd->SetLineColorAlpha(kRed, 0.5);
   h_ptd_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_ptd->Draw("HIST");
   h_ptd_mc->Draw("HIST SAME");
   l->Draw();
   c19->SaveAs("./output/scaled_ptd.png");

   TCanvas *c20 = new TCanvas("", "", 500, 500);
   c20->SetLogy();
   weight_time->GetYaxis()->SetMoreLogLabels();
   weight_time->GetXaxis()->SetTitle("Cluster time");
   weight_time->GetYaxis()->SetTitle("Entries");
   weight_time->SetLineColorAlpha(kRed, 0.5);
   h_time_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_time->Draw("HIST");
   h_time_mc->Draw("HIST SAME");
   l->Draw();
   c20->SaveAs("./output/scaled_time.png");

   TCanvas *c21 = new TCanvas("", "", 500, 500);
   c21->SetLogy();
   weight_iso->GetYaxis()->SetMoreLogLabels();
   weight_iso->GetXaxis()->SetTitle("Cluster iso");
   weight_iso->GetYaxis()->SetTitle("Entries");
   weight_iso->SetLineColorAlpha(kRed, 0.5);
   h_iso_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_iso->Draw("HIST");
   h_iso_mc->Draw("HIST SAME");
   l->Draw();
   c21->SaveAs("./output/scaled_iso.png");

   TCanvas *c22 = new TCanvas("", "", 500, 500);
   c22->SetLogy();
   weight_signif->GetYaxis()->SetMoreLogLabels();
   weight_signif->GetXaxis()->SetTitle("Cluster signif");
   weight_signif->GetYaxis()->SetTitle("Entries");
   weight_signif->SetLineColorAlpha(kRed, 0.5);
   h_signif_mc->SetLineColorAlpha(kBlue, 0.5);
   weight_signif->Draw("HIST");
   h_signif_mc->Draw("HIST SAME");
   l->Draw();
   c22->SaveAs("./output/scaled_signif.png");


}
