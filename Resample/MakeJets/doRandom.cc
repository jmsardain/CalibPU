#include <iostream>
#include "TString.h"
#include "Randomize.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main(int argc, char* argv[]){

	std::string jzslice(argv[1]);

	TString JZSlice  = TString(jzslice.c_str());
	TString theLink;
	TString path = "/data/jmsardain/CalibPU/datasets/pu/";

	if(JZSlice=="all"){
		theLink = path + "JetTree_all.root";
	} else if(JZSlice=="JZ0"){
		theLink  = "/data/jmsardain/CalibPU/datasets/pu/JetTree_JZ0.root";
	} else {
		std::cout << " Choose data or JZ*" << std::endl;
		return 0;
	}

	TString treeName = "JetTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	Randomize * myAnalysis ;
	myAnalysis =  new Randomize( myChain ) ;
	myAnalysis->Loop(JZSlice);
	
	return 0;

}
