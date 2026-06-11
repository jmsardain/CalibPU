#include <iostream>
#include "TString.h"
#include "dataHist.h"
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

	// TString theLink = "/data/jmsardain/CalibPU/user.cdelitzs.00339435.physics_Main.Ntuples_June15_v0_mltree_cluster_calo.root/user.cdelitzs.45207441._0001*.mltree_cluster_calo.root";
	// TString theLink = "/data/jmsardain/CalibPU/user.cdelitzs.00339435.physics_Main.Ntuples_June15_v0_mltree_cluster_calo.root/user.cdelitzs.45207441._*.mltree_cluster_calo.root";
	// TString theLink = "/data/dsmith/weights/user.cdelitzs.45207441._000199.mltree_cluster_calo.root";
	TString theLink = "/data/jmsardain/CalibPU/new/run/user.jmsardain.00339435.physics_Main.Ntuples_20April26_eta2p0_v1_mltree_cluster_calo.root/user.jmsardain.49860379._*.mltree_cluster_calo.root";
	TString treeName = "ClusterTree";
	TChain * myChain = new TChain( treeName ) ;
	myChain->Add( theLink );
	cout << "my chain = " << myChain->GetEntries() << endl ;

	dataHist * myAnalysis ;
	myAnalysis =  new dataHist( myChain ) ;
	myAnalysis->Loop();
	
	return 0;

}
