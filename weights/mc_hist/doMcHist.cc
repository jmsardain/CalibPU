#include <iostream>
#include "TString.h"
#include "mcHist.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main(){

	TString theLink = "/data/dsmith/weights/MC20d*.root";
	TString treeName = "ClusterTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	mcHist * myAnalysis ;
	myAnalysis =  new mcHist( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
