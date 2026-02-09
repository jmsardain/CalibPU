{ 

    TFile *f1 = TFile::Open("mc20_calibration_snapshot.root");
    TH1D*h1 = (TH1D*)f1->Get("mc20_calibration_cutflow");
    TFile *f2 = TFile::Open("mc20_putagging_snapshot.root");
    TH1D*h2 = (TH1D*)f2->Get("mc20_putagging_cutflow");
    
    TCanvas*c = new TCanvas("", "", 1000, 500);
    c->Divide(2, 1);
    c->cd(1);
    gPad->SetLogy();
    h1->Draw();

    c->cd(2);
    gPad->SetLogy();
    h2->Draw();

    c->SaveAs("./cutflows.png");




}