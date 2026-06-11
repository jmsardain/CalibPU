#define MC_ptScore_cxx
#include "MC_ptScore.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void MC_ptScore::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MC_ptScore.C
//      root> MC_ptScore t
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
   std::cout << "creating histograms..." << std::endl;
   TH1D* h_score10pt15 = new TH1D("MC", "jetCalpT 10-15 GeV", 100, 0, 1);
   TH1D* h_score15pt22 = new TH1D("MC", "jetCalpT 15-22 GeV", 100, 0, 1);
   TH1D* h_score22pt33 = new TH1D("MC", "jetCalpT 22-33 GeV", 100, 0, 1);
   TH1D* h_score33pt50 = new TH1D("MC", "jetCalpT 33-50 GeV", 100, 0, 1);
   TH1D* h_score50pt76 = new TH1D("MC", "jetCalpT 50-76 GeV", 100, 0, 1);
   TH1D* h_score76pt115 = new TH1D("MC", "jetCalpT 76-115 GeV", 100, 0, 1);
   TH1D* h_score115pt175 = new TH1D("MC", "jetCalpT 115-175 GeV", 100, 0, 1);
   TH1D* h_score175pt265 = new TH1D("MC", "jetCalpT 175-265 GeV", 100, 0, 1);
   TH1D* h_score265pt400 = new TH1D("MC", "jetCalpT 265-400 GeV", 100, 0, 1);
   TH1D* h_score400pt630 = new TH1D("MC", "jetCalpT 400-630 GeV", 100, 0, 1);

   std::cout << "filling histograms..." << std::endl;
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      for (unsigned int i=0; i<nclusterE; i++){
         if ((10 <= jetCalPt) && (15 > jetCalPt)) {
            h_score10pt15->Fill(nodes_out[i]);
         }
         if ((15 <= jetCalPt) && (22 > jetCalPt)) {
            h_score15pt22->Fill(nodes_out[i]);
         }
         if ((22 <= jetCalPt) && (33 > jetCalPt)) {
            h_score22pt33->Fill(nodes_out[i]);
         }
         if ((33 <= jetCalPt) && (50 > jetCalPt)) {
            h_score33pt50->Fill(nodes_out[i]);
         }
         if ((50 <= jetCalPt) && (76 > jetCalPt)) {
            h_score50pt76->Fill(nodes_out[i]);
         }
         if ((76 <= jetCalPt) && (115 > jetCalPt)) {
            h_score76pt115->Fill(nodes_out[i]);
         }
         if ((115 <= jetCalPt) && (175 > jetCalPt)) {
            h_score115pt175->Fill(nodes_out[i]);
         }
         if ((175 <= jetCalPt) && (265 > jetCalPt)) {
            h_score175pt265->Fill(nodes_out[i]);
         }
         if ((265 <= jetCalPt) && (400 > jetCalPt)) {
            h_score265pt400->Fill(nodes_out[i]);
         }
         if ((400 <= jetCalPt) && (630 > jetCalPt)) {
            h_score400pt630->Fill(nodes_out[i]);
         }
      }
   }

   std::cout << "drawing histograms..." << std::endl;

   TCanvas* c1 = new TCanvas("", "", 500, 500);
   c1->SetLogy();
   h_score10pt15->SetXTitle("Score");
   h_score10pt15->GetYaxis()->SetMoreLogLabels();
   h_score10pt15->Draw();
   c1->SaveAs("./MC/Score10pT15.png");
   c1->Close();

   TCanvas* c2 = new TCanvas("", "", 500, 500);
   c2->SetLogy();
   h_score15pt22->SetXTitle("Score");
   h_score15pt22->GetYaxis()->SetMoreLogLabels();
   h_score15pt22->Draw();
   c2->SaveAs("./MC/Score15pT22.png");
   c2->Close();

   TCanvas* c3 = new TCanvas("", "", 500, 500);
   c3->SetLogy();
   h_score22pt33->SetXTitle("Score");
   h_score22pt33->GetYaxis()->SetMoreLogLabels();
   h_score22pt33->Draw();
   c3->SaveAs("./MC/Score22pT33.png");
   c3->Close();

   TCanvas* c4 = new TCanvas("", "", 500, 500);
   c4->SetLogy();
   h_score33pt50->SetXTitle("Score");
   h_score33pt50->GetYaxis()->SetMoreLogLabels();
   h_score33pt50->Draw();
   c4->SaveAs("./MC/Score33pT50.png");
   c4->Close();

   TCanvas* c5 = new TCanvas("", "", 500, 500);
   c5->SetLogy();
   h_score50pt76->SetXTitle("Score");
   h_score50pt76->GetYaxis()->SetMoreLogLabels();
   h_score50pt76->Draw();
   c5->SaveAs("./MC/Score50pT76.png");
   c5->Close();

   TCanvas* c6 = new TCanvas("", "", 500, 500);
   c6->SetLogy();
   h_score76pt115->SetXTitle("Score");
   h_score76pt115->GetYaxis()->SetMoreLogLabels();
   h_score76pt115->Draw();
   c6->SaveAs("./MC/Score76pT115.png");
   c6->Close();

   TCanvas* c7 = new TCanvas("", "", 500, 500);
   c7->SetLogy();
   h_score115pt175->SetXTitle("Score");
   h_score115pt175->GetYaxis()->SetMoreLogLabels();
   h_score115pt175->Draw();
   c7->SaveAs("./MC/Score115pT175.png");
   c7->Close();

   TCanvas* c8 = new TCanvas("", "", 500, 500);
   c8->SetLogy();
   h_score175pt265->SetXTitle("Score");
   h_score175pt265->GetYaxis()->SetMoreLogLabels();
   h_score175pt265->Draw();
   c8->SaveAs("./MC/Score175pT265.png");
   c8->Close();

   TCanvas* c9 = new TCanvas("", "", 500, 500);
   c9->SetLogy();
   h_score265pt400->SetXTitle("Score");
   h_score265pt400->GetYaxis()->SetMoreLogLabels();
   h_score265pt400->Draw();
   c9->SaveAs("./MC/Score265pT400.png");
   c9->Close();

   TCanvas* c10 = new TCanvas("", "", 500, 500);
   c10->SetLogy();
   h_score400pt630->SetXTitle("Score");
   h_score400pt630->GetYaxis()->SetMoreLogLabels();
   h_score400pt630->Draw();
   c10->SaveAs("./MC/Score400pT630.png");
   c10->Close();
}
