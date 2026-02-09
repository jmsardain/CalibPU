#include <iostream>
#include "TString.h"
#include "GetValue.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main(int argc, char* argv[]){

	TString theLink = "/data/jmsardain/CalibPU/datasets/pu/JetTree_all_train.root";
	TString treeName = "JetTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	GetValue * myAnalysis ;
	myAnalysis =  new GetValue( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
