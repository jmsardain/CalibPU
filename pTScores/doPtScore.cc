#include <iostream>
#include "TString.h"
#include "ptScore.h"
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

	TString theLink = "/data/jmsardain/CalibPU/trainings/pu/ckpts/Apr212026/final_new.root";

	TString treeName = "JetTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "loading data..." << endl ;
	cout << "my chain = " << myChain->GetEntries() << endl ;

	ptScore * myAnalysis ;
	myAnalysis =  new ptScore( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
