#include <iostream>
#include "TString.h"
#include "dataTransforms.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std ;

int main(int argc, char* argv[]){

    TString theLink = "/data/dsmith/data_for_test/user.cdelitzs.45207441._000199.mltree_cluster_calo.root";
    TString treeName = "ClusterTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	dataTransforms * myAnalysis ;
	myAnalysis =  new dataTransforms( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
