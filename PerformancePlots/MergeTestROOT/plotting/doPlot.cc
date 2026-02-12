#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include <string>
#include "AtlasStyle.h"
#include "AtlasLabels.h"
#include "AtlasUtils.h"
using namespace std ;

TCanvas* DrawJetResponse(TH1D*jetarea, TH1D*jetEdep, TH1D*jetLabel, TH1D*jetML, TString xlabel, TString ylabel, bool logxaxis){
	jetarea->SetLineColor(TColor::GetColor("#ef476f"));
    jetEdep->SetLineColor(TColor::GetColor("#f78c6b"));
    jetLabel->SetLineColor(TColor::GetColor("#ffd166"));
    jetML->SetLineColor(TColor::GetColor("#06d6a0"));

	jetarea->GetXaxis()->SetTitle(xlabel); 
	jetarea->GetYaxis()->SetTitle(ylabel); 

	if (ylabel.Contains("Median")) { jetarea->GetYaxis()->SetRangeUser(0., 1.8);}
	if (ylabel.Contains("Resolution")) { jetarea->GetYaxis()->SetRangeUser(0., 1.6);}
	
	TLegend* l = new TLegend(0.7, 0.7, 0.9, 0.9); 
	l->AddEntry(jetarea,  "E_{jet}^{area} / E_{jet}^{true}", "l");
	l->AddEntry(jetEdep,  "E_{jet}^{dep} / E_{jet}^{true}", "l");
	l->AddEntry(jetLabel, "E_{jet}^{signal} / E_{jet}^{true}", "l");
	l->AddEntry(jetML,    "E_{jet}^{ML} / E_{jet}^{true}", "l");
	
    TCanvas* c = new TCanvas("", "", 600, 600);
	// TPad* pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	// pad1->SetBottomMargin(0); 
	// pad1->Draw();
	// pad1->cd();
	// if(logxaxis){ pad1->SetLogx(); }
	if(logxaxis){ c->SetLogx(); }
	jetarea->Draw("H");
	jetEdep->Draw("H SAME");
	jetLabel->Draw("H SAME");
	jetML->Draw("H SAME");
	l->Draw("SAME");

	// c->cd();
	// TPad* pad2 = new TPad("pad2","pad2",0,0,1,0.3);
	// pad2->SetTopMargin(0);
	// pad2->SetBottomMargin(0.3);
	// if(logxaxis){ pad2->SetLogx(); }
	// pad2->Draw();
	// pad2->cd();

	// // Draw ratios
	// TH1D* hRatio_area = (TH1D*)jetEdep->Clone("jetEdep");

	// hRatio->Divide(hJetRawE);

	// hRatio->SetLineColor(kRed);

	// hRatio->SetTitle("");
	// hRatio->GetYaxis()->SetTitle("Ratio");
	// hRatio->GetYaxis()->SetNdivisions(505);
	// hRatio->GetYaxis()->SetTitleSize(0.15);
	// hRatio->GetYaxis()->SetTitleOffset(0.3);
	// hRatio->GetYaxis()->SetLabelSize(0.12);

	// hRatio->GetXaxis()->SetTitle("Energy");
	// hRatio->GetXaxis()->SetLabelSize(0.12);
	// hRatio->GetXaxis()->SetTitleSize(0.15);
	// hRatio->GetYaxis()->SetRangeUser(0.8, 1.2);

	// hRatio->Draw("H");
	return c; 
}

TCanvas* DrawTH2DPlots(TH2D* h, TString xlabel, TString ylabel, bool logxaxis, bool logyaxis/*,TString label*/){ 

	h->GetXaxis()->SetTitle(xlabel); 
	h->GetYaxis()->SetTitle(ylabel); 
	
	TCanvas* c = new TCanvas("", "", 600, 600);
	c->SetRightMargin(0.2);
    c->SetLogz();
	if(logxaxis) { c->SetLogx(); }
	if(logyaxis) { c->SetLogy(); }
	h->Draw("colz");

	// ATLASLabel(0.20, 0.88,"Simulation Preliminary"); 
	// myText(0.20, 0.84,kBlack, "#sqrt{s} = 13 TeV, Pythia 8, dijet");
	// myText(0.20, 0.80,kBlack, "p_{T}^{JES} > 20 GeV, |y^{JES} < 2|");
	// myText(0.20, 0.76,kBlack, "anti-k_{T} R = 0.4 EMTopo jets");
	// myText(0.20, 0.74,kBlack, label);
	return c; 

}
   
TCanvas* DrawClassificationScores(TH1D* hScore_signal, TH1D* hScore_pileup){

	
	hScore_signal->SetLineColor(TColor::GetColor("#FF8C00"));
	hScore_pileup->SetLineColor(TColor::GetColor("#008026"));

    hScore_signal->GetXaxis()->SetTitle("Scores");
    hScore_signal->GetYaxis()->SetTitle("Number of clusters");

	TLegend* l = new TLegend(0.7, 0.7, 0.9, 0.9); 
	l->AddEntry(hScore_signal, "Signal", "l");
	l->AddEntry(hScore_pileup, "Pileup", "l");

	TCanvas* c = new TCanvas("", "", 600, 600);
	c->SetLogy();
	hScore_signal->Draw("H");
	hScore_pileup->Draw("H SAME");
	l->Draw("SAME");
	// ATLASLabel(0.20, 0.88,"Simulation Preliminary"); 
	// myText(0.20, 0.84,kBlack, "#sqrt{s} = 13 TeV, Pythia 8, dijet");
	// myText(0.20, 0.80,kBlack, "p_{T}^{JES} > 20 GeV, |y^{JES} < 2|");
	// myText(0.20, 0.76,kBlack, "anti-k_{T} R = 0.4 EMTopo jets");

	return c;
}

TCanvas* DrawTH1DSame(TH1D* hSumClusterE, TH1D* hJetRawE){

	hSumClusterE->SetLineColor(kRed);
    hJetRawE->SetLineColor(kBlack);

    hSumClusterE->GetXaxis()->SetTitle("Energy [GeV]");
    hSumClusterE->GetYaxis()->SetTitle("Number of clusters");

	TLegend* l = new TLegend(0.7, 0.7, 0.9, 0.9); 
	l->AddEntry(hJetRawE, "E_{jet}^{EM}", "l");
	l->AddEntry(hSumClusterE, "sum E_{clus}^{EM}", "l");
	
    TCanvas* c = new TCanvas("", "", 600, 600);
	TPad* pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	pad1->SetBottomMargin(0); 
	pad1->Draw();
	pad1->cd();
	pad1->SetLogy();
	hJetRawE->Draw("H");
	hSumClusterE->Draw("H SAME");
	l->Draw("SAME");

	c->cd();
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


    return c;
}


int main(int argc, char* argv[]){
	SetAtlasStyle();
 	
	// data
	std::string filename(argv[1]);
	TFile*f = TFile::Open(TString(filename.c_str())); 
	cout << TString(filename.c_str()) << endl ;

	TH1D* hSumClusterE = (TH1D*)f->Get("sumClusterE");
	TH1D* hJetRawE = (TH1D*)f->Get("jetRawE");
	TCanvas*c = DrawTH1DSame(hSumClusterE, hJetRawE); 
	c->SaveAs("./plots/sumClusterE_jetRawE.png");

	TH1D* hScore_signal = (TH1D*)f->Get("score_signal");
	TH1D* hScore_pileup = (TH1D*)f->Get("score_pileup");
	c = DrawClassificationScores(hScore_signal, hScore_pileup); 
	c->SaveAs("./plots/Classification.png");

	// /// 
	TH2D* h2_Edep_Eem_all    = (TH2D*)f->Get("Edep_Eem_all"); 
	TH2D* h2_Edep_Eem_signal = (TH2D*)f->Get("Edep_Eem_signal"); 
	TH2D* h2_Edep_Eem_pileup = (TH2D*)f->Get("Edep_Eem_pileup"); 
	TCanvas*c1, *c2, *c3;
	c1 = DrawTH2DPlots(h2_Edep_Eem_all, "E_{clus}^{dep} [GeV]", "E_{clus}^{EM} [GeV]", true, true);
	c2 = DrawTH2DPlots(h2_Edep_Eem_signal, "E_{clus}^{dep} [GeV]", "E_{clus}^{EM} [GeV]", true, true);
	c3 = DrawTH2DPlots(h2_Edep_Eem_pileup, "E_{clus}^{dep} [GeV]", "E_{clus}^{EM} [GeV]", true, true);
	c1->SaveAs("./plots/Edep_Eem_all.png");
	c2->SaveAs("./plots/Edep_Eem_signal.png");
	c3->SaveAs("./plots/Edep_Eem_pileup.png");

	///////////// Signal 
	TCanvas*cSignal1, *cSignal2, *cSignal3, *cSignal4, *cSignal5, *cSignal6;
	// ML output score
	TH2D* h2_Edep_signal = (TH2D*)f->Get("score_Edep_signal"); 
	TH2D* h2_Eem_signal  = (TH2D*)f->Get("score_Eem_signal"); 
	TH2D* h2_long_signal = (TH2D*)f->Get("score_long_signal"); 
	TH2D* h2_lat_signal  = (TH2D*)f->Get("score_lat_signal"); 
	TH2D* h2_isol_signal = (TH2D*)f->Get("score_isol_signal"); 
	TH2D* h2_time_signal = (TH2D*)f->Get("score_time_signal"); 
	cSignal1 = DrawTH2DPlots(h2_Edep_signal, "E_{clus}^{dep} [GeV]", "Score", true, false);
	cSignal2 = DrawTH2DPlots(h2_Eem_signal, "E_{clus}^{EM} [GeV]", "Score", true, false);
	cSignal3 = DrawTH2DPlots(h2_long_signal, "\\langle m_{\\mathrm{long}}^{2}\\rangle", "Score", false, false);
	cSignal4 = DrawTH2DPlots(h2_lat_signal, "\\langle m_{\\mathrm{lat}}^{2}\\rangle", "Score", false, false);
	cSignal5 = DrawTH2DPlots(h2_isol_signal, "f_{\\mathrm{iso}}", "Score", false, false);
	cSignal6 = DrawTH2DPlots(h2_time_signal, "t [ns]", "Score", false, false);
	cSignal1->SaveAs("./plots/score_Edep_signal.png");
	cSignal2->SaveAs("./plots/score_Eem_signal.png");
	cSignal3->SaveAs("./plots/score_long_signal.png");
	cSignal4->SaveAs("./plots/score_lat_signal.png");
	cSignal5->SaveAs("./plots/score_isol_signal.png");
	cSignal6->SaveAs("./plots/score_time_signal.png");
	// Transformed score
	TH2D* h2_Edep_signal_new = (TH2D*)f->Get("funcscore_Edep_signal"); 
	TH2D* h2_Eem_signal_new  = (TH2D*)f->Get("funcscore_Eem_signal"); 
	TH2D* h2_long_signal_new = (TH2D*)f->Get("funcscore_long_signal"); 
	TH2D* h2_lat_signal_new  = (TH2D*)f->Get("funcscore_lat_signal"); 
	TH2D* h2_isol_signal_new = (TH2D*)f->Get("funcscore_isol_signal"); 
	TH2D* h2_time_signal_new = (TH2D*)f->Get("funcscore_time_signal"); 
	cSignal1 = DrawTH2DPlots(h2_Edep_signal_new, "E_{clus}^{dep} [GeV]", "Transformed score", true, false);
	cSignal2 = DrawTH2DPlots(h2_Eem_signal_new, "E_{clus}^{EM} [GeV]", "Transformed score", true, false);
	cSignal3 = DrawTH2DPlots(h2_long_signal_new, "\\langle m_{\\mathrm{long}}^{2}\\rangle", "Transformed score", false, false);
	cSignal4 = DrawTH2DPlots(h2_lat_signal_new, "\\langle m_{\\mathrm{lat}}^{2}\\rangle", "Transformed score", false, false);
	cSignal5 = DrawTH2DPlots(h2_isol_signal_new, "f_{\\mathrm{iso}}", "Transformed score", false, false);
	cSignal6 = DrawTH2DPlots(h2_time_signal_new, "t [ns]", "Transformed score", false, false);
	cSignal1->SaveAs("./plots/funcscore_Edep_signal.png");
	cSignal2->SaveAs("./plots/funcscore_Eem_signal.png");
	cSignal3->SaveAs("./plots/funcscore_long_signal.png");
	cSignal4->SaveAs("./plots/funcscore_lat_signal.png");
	cSignal5->SaveAs("./plots/funcscore_isol_signal.png");
	cSignal6->SaveAs("./plots/funcscore_time_signal.png");

	///////////// Pileup
	TCanvas*cPileup1, *cPileup2, *cPileup3, *cPileup4, *cPileup5, *cPileup6;
	// ML output score
	TH2D* h2_Edep_pileup = (TH2D*)f->Get("score_Edep_pileup"); 
	TH2D* h2_Eem_pileup  = (TH2D*)f->Get("score_Eem_pileup"); 
	TH2D* h2_long_pileup = (TH2D*)f->Get("score_long_pileup"); 
	TH2D* h2_lat_pileup  = (TH2D*)f->Get("score_lat_pileup"); 
	TH2D* h2_isol_pileup = (TH2D*)f->Get("score_isol_pileup"); 
	TH2D* h2_time_pileup = (TH2D*)f->Get("score_time_pileup"); 
	cPileup1 = DrawTH2DPlots(h2_Edep_pileup, "E_{clus}^{dep} [GeV]", "Score", true, false);
	cPileup2 = DrawTH2DPlots(h2_Eem_pileup, "E_{clus}^{EM} [GeV]", "Score", true, false);
	cPileup3 = DrawTH2DPlots(h2_long_pileup, "\\langle m_{\\mathrm{long}}^{2}\\rangle", "Score", false, false);
	cPileup4 = DrawTH2DPlots(h2_lat_pileup, "\\langle m_{\\mathrm{lat}}^{2}\\rangle", "Score", false, false);
	cPileup5 = DrawTH2DPlots(h2_isol_pileup, "f_{\\mathrm{iso}}", "Score", false, false);
	cPileup6 = DrawTH2DPlots(h2_time_pileup, "t [ns]", "Score", false, false);
	cPileup1->SaveAs("./plots/score_Edep_pileup.png");
	cPileup2->SaveAs("./plots/score_Eem_pileup.png");
	cPileup3->SaveAs("./plots/score_long_pileup.png");
	cPileup4->SaveAs("./plots/score_lat_pileup.png");
	cPileup5->SaveAs("./plots/score_isol_pileup.png");
	cPileup6->SaveAs("./plots/score_time_pileup.png");
	
	// Transformed score
	TH2D* h2_Edep_pileup_new = (TH2D*)f->Get("funcscore_Edep_pileup"); 
	TH2D* h2_Eem_pileup_new  = (TH2D*)f->Get("funcscore_Eem_pileup"); 
	TH2D* h2_long_pileup_new = (TH2D*)f->Get("funcscore_long_pileup"); 
	TH2D* h2_lat_pileup_new  = (TH2D*)f->Get("funcscore_lat_pileup"); 
	TH2D* h2_isol_pileup_new = (TH2D*)f->Get("funcscore_isol_pileup"); 
	TH2D* h2_time_pileup_new = (TH2D*)f->Get("funcscore_time_pileup"); 
	cPileup1 = DrawTH2DPlots(h2_Edep_pileup_new, "E_{clus}^{dep} [GeV]", "Transformed score", true, false);
	cPileup2 = DrawTH2DPlots(h2_Eem_pileup_new, "E_{clus}^{EM} [GeV]", "Transformed score", true, false);
	cPileup3 = DrawTH2DPlots(h2_long_pileup_new, "\\langle m_{\\mathrm{long}}^{2}\\rangle", "Transformed score", false, false);
	cPileup4 = DrawTH2DPlots(h2_lat_pileup_new, "\\langle m_{\\mathrm{lat}}^{2}\\rangle", "Transformed score", false, false);
	cPileup5 = DrawTH2DPlots(h2_isol_pileup_new, "f_{\\mathrm{iso}}", "Transformed score", false, false);
	cPileup6 = DrawTH2DPlots(h2_time_pileup_new, "t [ns]", "Transformed score", false, false);
	cPileup1->SaveAs("./plots/funcscore_Edep_pileup.png");
	cPileup2->SaveAs("./plots/funcscore_Eem_pileup.png");
	cPileup3->SaveAs("./plots/funcscore_long_pileup.png");
	cPileup4->SaveAs("./plots/funcscore_lat_pileup.png");
	cPileup5->SaveAs("./plots/funcscore_isol_pileup.png");
	cPileup6->SaveAs("./plots/funcscore_time_pileup.png");

	///////////// Jet Response plots
	// Median
	TH1D* h_area_median     = (TH1D*)f->Get("JetResponse_median_area"); 
	TH1D* h_Edep_median     = (TH1D*)f->Get("JetResponse_median_edep"); 
	TH1D* h_labelsig_median = (TH1D*)f->Get("JetResponse_median_labelsig"); 
	TH1D* h_ml_median       = (TH1D*)f->Get("JetResponse_median_ml"); 
	TCanvas*cMedian; 
	cMedian = DrawJetResponse(h_area_median, h_Edep_median, h_labelsig_median, h_ml_median, "E_{jet}^{JES} [GeV]", "Jet Response Median", true);
	cMedian->SaveAs("./plots/JetResponseMedian.png");
	// IQR 	
	TH1D* h_area_iqr     = (TH1D*)f->Get("JetResponse_iqr_area"); 
	TH1D* h_Edep_iqr     = (TH1D*)f->Get("JetResponse_iqr_edep"); 
	TH1D* h_labelsig_iqr = (TH1D*)f->Get("JetResponse_iqr_labelsig"); 
	TH1D* h_ml_iqr       = (TH1D*)f->Get("JetResponse_iqr_ml"); 
	TCanvas*cIQR; 
	cIQR = DrawJetResponse(h_area_iqr, h_Edep_iqr, h_labelsig_iqr, h_ml_iqr, "E_{jet}^{JES} [GeV]", "Jet Response Resolution", true);
	cIQR->SaveAs("./plots/JetResponseResolution.png");


	return 0;

}
