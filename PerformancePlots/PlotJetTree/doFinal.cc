#include <iostream>
#include "TString.h"
#include "DoPlot.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <string>

using namespace std ;


int main(int argc, char* argv[]) {

  // which model
  TString ROOTFile = "/data/jmsardain/CalibPU/datasets/pu/JetTree_all_test.root";
  TChain * myChain = new TChain( "JetTree" ) ;

	cout << ROOTFile << endl ;
	myChain->Add( ROOTFile );
  
	cout << "my chain = " << myChain->GetEntries() << endl ;

  // PreparePlots * myAnalysis ;
  // myAnalysis =  new PreparePlots( myChain ) ;
  // myAnalysis->Loop();

  DoPlot * myAnalysis ;
  myAnalysis =  new DoPlot( myChain ) ;
  myAnalysis->Loop();

	return 0;

}
