#include <iostream>
#include "TString.h"
#include "mcCompare.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main(int argc, char* argv[]){

	std::string pathFile(argv[1]);
	// TString theLink = "/data/jmsardain/CalibPU/trainings/pu/ckpts/Feb42026/final.root";
	// TString theLink = "/data/jmsardain/CalibPU/trainings/pu/ckpts/Feb52026/final.root";
	TString theLink = TString(pathFile.c_str());
	TString treeName = "ClusterTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	mcCompare * myAnalysis ;
	myAnalysis =  new mcCompare( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
