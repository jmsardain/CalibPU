#include <iostream>
#include "TString.h"
#include "MakeJets.h"
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
	TString path = "/data/jmsardain/CalibPU/";

	if(JZSlice=="all"){
		theLink = path + "MC20d_JZ*.root";
	} else if(JZSlice=="JZ0"){
		theLink  = "/data/jmsardain/CalibPU/MC20d_JZ0_putagging_snapshot.root";
	} else {
		std::cout << " Choose data or JZ*" << std::endl;
		return 0;
	}

	TString treeName = "ClusterTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	MakeJets * myAnalysis ;
	myAnalysis =  new MakeJets( myChain ) ;
	myAnalysis->Loop(JZSlice);
	
	return 0;

}
