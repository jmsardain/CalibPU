#include <iostream>
#include "TString.h"
#include "MC_ptScore.h"
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

	TString theLink = "/data/jmsardain/CalibPU/trainings/pu/ckpts/Apr212026/final.root";

	TString treeName = "JetTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "loading data..." << endl ;
	cout << "my chain = " << myChain->GetEntries() << endl ;

	MC_ptScore * myAnalysis ;
	myAnalysis =  new MC_ptScore( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
