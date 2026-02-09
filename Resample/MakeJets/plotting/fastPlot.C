#include <vector>
#include <cmath>
#include <iostream>
#include <tuple>
#include <map>
#include <TH1D.h>
#include <TLegend.h>
struct BinConfig {
    bool log;      
    int nbins;
    double xmin;
    double xmax;
};

std::vector<double> makeLogBins(int nbins_log, double xmin, double xmax) {
    std::vector<double> bins(nbins_log + 1);
    double logmin = std::log10(xmin);
    double logmax = std::log10(xmax);
    for (int i = 0; i <= nbins_log; ++i)
        bins[i] = std::pow(10., logmin + i * (logmax - logmin) / nbins_log);
    return bins;
}


void fastPlot() {

    gStyle->SetOptStat(0);
    // Enable multithreading (optional but recommended)
    ROOT::EnableImplicitMT();

    // Create RDataFrame
    ROOT::RDataFrame df_all("JetTree", "/data/jmsardain/CalibPU/datasets/pu/JetTree_all.root");
    ROOT::RDataFrame df_train("JetTree", "/data/jmsardain/CalibPU/datasets/pu/JetTree_all_train.root");
    ROOT::RDataFrame df_test("JetTree", "/data/jmsardain/CalibPU/datasets/pu/JetTree_all_test.root");

    std::vector<TString> variables; 
    variables.push_back("jetCalPt");
    variables.push_back("clusterE");

    std::map<TString, BinConfig> varConfig;
    varConfig["jetCalPt"]     = {false, 50, 0, 500};      
    varConfig["clusterE"]     = {true, 50, 1e-3, 500};   
    varConfig["cluster_time"] = {false, 100, -50, 50};


    for (const auto& pair : varConfig) { 
        TString ivar = pair.first;
        BinConfig cfg = pair.second;

        auto hAll = cfg.log ? 
            df_all.Histo1D  ( {"h"+ivar, "; "+ivar+";Entries", (int)makeLogBins(cfg.nbins,cfg.xmin,cfg.xmax).size()-1, makeLogBins(cfg.nbins,cfg.xmin,cfg.xmax).data()}, ivar)
            :
            df_all.Histo1D  ( {"h"+ivar, "; "+ivar+";Entries", cfg.nbins, cfg.xmin, cfg.xmax}, ivar);
        ;
        
        auto hTrain = cfg.log ? 
            df_train.Histo1D  ( {"h"+ivar, "; "+ivar+";Entries", (int)makeLogBins(cfg.nbins,cfg.xmin,cfg.xmax).size()-1, makeLogBins(cfg.nbins,cfg.xmin,cfg.xmax).data()}, ivar)
            :
            df_train.Histo1D  ( {"h"+ivar, "; "+ivar+";Entries", cfg.nbins, cfg.xmin, cfg.xmax}, ivar);
        ;
        
        auto hTest = cfg.log ? 
            df_test.Histo1D  ( {"h"+ivar, "; "+ivar+";Entries", (int)makeLogBins(cfg.nbins,cfg.xmin,cfg.xmax).size()-1, makeLogBins(cfg.nbins,cfg.xmin,cfg.xmax).data()}, ivar)
            :
            df_test.Histo1D  ( {"h"+ivar, "; "+ivar+";Entries", cfg.nbins, cfg.xmin, cfg.xmax}, ivar);
        ;
        

        
        hAll->SetLineColor(kBlack);
        hTrain->SetLineColor(kRed);
        hTest->SetLineColor(kBlue);

        hAll->Scale(1. / hAll->GetEntries() );
        hTrain->Scale(1. / hTrain->GetEntries() );
        hTest->Scale(1. / hTest->GetEntries() );


    
        ////

        TLegend* l = new TLegend(0.7, 0.7, 0.9, 0.9); 
        l->AddEntry(hAll.GetPtr(), "No split", "l");
        l->AddEntry(hTrain.GetPtr(), "Train", "l");
        l->AddEntry(hTest.GetPtr(), "Test", "l");

        TCanvas* c1 = new TCanvas("", "", 800, 800);

        TPad* pad1 = new TPad("pad1","pad1",0,0.3,1,1);
        pad1->SetBottomMargin(0); 
        pad1->Draw();
        pad1->cd();
        if(cfg.log) pad1->SetLogx();
        pad1->SetLogy();
        hAll->Draw("H");
        hTrain->Draw("H SAME");
        hTest->Draw("H SAME");
        l->Draw("SAME");

        c1->cd();
        TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.3);
        pad2->SetTopMargin(0);
        pad2->SetBottomMargin(0.3);
        if(cfg.log) pad2->SetLogx();
        pad2->Draw();
        pad2->cd();

        // Draw ratios
        TH1D* hRatioTrain = (TH1D*)hTrain.GetPtr()->Clone("hRatioTrain");
        TH1D* hRatioTest  = (TH1D*)hTest.GetPtr()->Clone("hRatioTest");

        hRatioTrain->Divide(hAll.GetPtr());
        hRatioTest->Divide(hAll.GetPtr());

        hRatioTrain->SetLineColor(kRed);
        hRatioTest->SetLineColor(kBlue);

        hRatioTrain->SetTitle("");
        hRatioTrain->GetYaxis()->SetTitle("Ratio");
        hRatioTrain->GetYaxis()->SetNdivisions(505);
        hRatioTrain->GetYaxis()->SetTitleSize(0.15);
        hRatioTrain->GetYaxis()->SetTitleOffset(0.3);
        hRatioTrain->GetYaxis()->SetLabelSize(0.12);

        hRatioTrain->GetXaxis()->SetTitle(ivar);
        hRatioTrain->GetXaxis()->SetLabelSize(0.12);
        hRatioTrain->GetXaxis()->SetTitleSize(0.15);
        hRatioTrain->GetYaxis()->SetRangeUser(0.8, 1.2);
        if(cfg.log) pad2->SetLogx();

        hRatioTrain->Draw("H");
        hRatioTest->Draw("H SAME");

        c1->SaveAs(("./plots/"+ivar+"_ratio.png"));
        delete c1;

    }
   
}
