#define DoPlot_cxx
#include "DoPlot.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

void DoPlot::Loop(){
   gStyle->SetOptStat(0); 
   TH1D* hJetRawE = new TH1D("", "", 100, 0, 500);
   TH1D* hSumClusterE = new TH1D("", "", 100, 0, 500);
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      hJetRawE->Fill(jetRawE);
      double sum = 0; 

      for (unsigned int i=0; i<clusterE->size(); i++) { 
         sum += clusterE->at(i);
      }
      hSumClusterE->Fill(sum);


   }

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

   c1->SaveAs(("./plot.png"));

}
