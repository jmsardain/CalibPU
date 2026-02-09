//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 26 12:17:21 2026 by ROOT version 6.36.02
// from TTree JetTree/One entry per jet
// found on file: /data/jmsardain/CalibPU/datasets/pu/JetTree_all.root
//////////////////////////////////////////////////////////

#ifndef GetValue_h
#define GetValue_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
using namespace std;
class GetValue {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         LCWJetMatchRadius;
   Float_t         areaRho;
   Int_t           eventNumber;
   Float_t         jetArea;
   Float_t         jetAreaE;
   Float_t         jetAreaEta;
   Float_t         jetAreaFM;
   Float_t         jetAreaM;
   Float_t         jetAreaPhi;
   Float_t         jetAreaPt;
   Float_t         jetCalE;
   Float_t         jetCalEta;
   Float_t         jetCalM;
   Float_t         jetCalPhi;
   Float_t         jetCalPt;
   Int_t           jetCnt;
   Float_t         jetNConst;
   Float_t         jetRawE;
   Float_t         jetRawEta;
   Float_t         jetRawM;
   Float_t         jetRawPhi;
   Float_t         jetRawPt;
   Float_t         matchedLCWJetRawE;
   Float_t         matchedLCWJetRawM;
   Float_t         matchedLCWJetRawPhi;
   Float_t         matchedLCWJetRawPt;
   Float_t         matchedLCWJetRawRap;
   Float_t         medianRho;
   Float_t         nCluster;
   Float_t         runNumber;
   Float_t         seqNumber;
   Float_t         sigmaRho;
   Float_t         truthJetE;
   Float_t         truthJetM;
   Float_t         truthJetMatchRadius;
   Float_t         truthJetPhi;
   Float_t         truthJetPt;
   Float_t         truthJetRap;
   vector<float>   *avgMu;
   vector<float>   *clusterE;
   vector<float>   *clusterECalib;
   vector<float>   *clusterEta;
   vector<float>   *clusterEtaCalib;
   vector<float>   *clusterIndex;
   vector<float>   *clusterPhi;
   vector<float>   *clusterPhiCalib;
   vector<float>   *clusterPt;
   vector<float>   *clusterPtCalib;
   vector<float>   *cluster_AVG_LAR_Q;
   vector<float>   *cluster_AVG_TILE_Q;
   vector<float>   *cluster_BADLARQ_FRAC;
   vector<float>   *cluster_BAD_CELLS_CORR_E;
   vector<float>   *cluster_CELL_SIGNIFICANCE;
   vector<float>   *cluster_CELL_SIG_SAMPLING;
   vector<float>   *cluster_CENTER_LAMBDA;
   vector<float>   *cluster_CENTER_MAG;
   vector<float>   *cluster_CENTER_X;
   vector<float>   *cluster_CENTER_Y;
   vector<float>   *cluster_CENTER_Z;
   vector<float>   *cluster_DELTA_ALPHA;
   vector<float>   *cluster_DELTA_PHI;
   vector<float>   *cluster_DELTA_THETA;
   vector<float>   *cluster_DM_WEIGHT;
   vector<float>   *cluster_EM_PROBABILITY;
   vector<float>   *cluster_ENG_BAD_CELLS;
   vector<float>   *cluster_ENG_BAD_HV_CELLS;
   vector<float>   *cluster_ENG_CALIB_DEAD_TOT;
   vector<float>   *cluster_ENG_CALIB_FRAC_EM;
   vector<float>   *cluster_ENG_CALIB_FRAC_HAD;
   vector<float>   *cluster_ENG_CALIB_FRAC_REST;
   vector<float>   *cluster_ENG_CALIB_OUT_L;
   vector<float>   *cluster_ENG_CALIB_OUT_M;
   vector<float>   *cluster_ENG_CALIB_OUT_T;
   vector<float>   *cluster_ENG_CALIB_TOT;
   vector<float>   *cluster_ENG_FRAC_CORE;
   vector<float>   *cluster_ENG_FRAC_EM;
   vector<float>   *cluster_ENG_FRAC_EM_INCL;
   vector<float>   *cluster_ENG_FRAC_MAX;
   vector<float>   *cluster_ENG_POS;
   vector<float>   *cluster_FIRST_ENG_DENS;
   vector<float>   *cluster_FIRST_ETA;
   vector<float>   *cluster_FIRST_PHI;
   vector<float>   *cluster_HAD_WEIGHT;
   vector<float>   *cluster_ISOLATION;
   vector<float>   *cluster_LATERAL;
   vector<float>   *cluster_LONGITUDINAL;
   vector<float>   *cluster_MASS;
   vector<float>   *cluster_N_BAD_CELLS;
   vector<float>   *cluster_N_BAD_CELLS_CORR;
   vector<float>   *cluster_N_BAD_HV_CELLS;
   vector<float>   *cluster_OOC_WEIGHT;
   vector<float>   *cluster_PTD;
   vector<float>   *cluster_SECOND_ENG_DENS;
   vector<float>   *cluster_SECOND_LAMBDA;
   vector<float>   *cluster_SECOND_R;
   vector<float>   *cluster_SECOND_TIME;
   vector<float>   *cluster_SIGNIFICANCE;
   vector<float>   *cluster_fracE;
   vector<float>   *cluster_fracECalib;
   vector<float>   *cluster_fracECalib_ref;
   vector<float>   *cluster_fracE_ref;
   vector<float>   *cluster_nCells;
   vector<float>   *cluster_nCells_tot;
   vector<float>   *cluster_sumCellE;
   vector<float>   *cluster_sumCellECalib;
   vector<float>   *cluster_time;
   vector<float>   *diffEta;
   vector<int>     *labels;
   vector<int>     *nPrimVtx;
   vector<float>   *r_e_calculated;
   vector<float>   *zL;
   vector<float>   *zRel;
   vector<float>   *zT;

   // List of branches
   TBranch        *b_LCWJetMatchRadius;   //!
   TBranch        *b_areaRho;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_jetArea;   //!
   TBranch        *b_jetAreaE;   //!
   TBranch        *b_jetAreaEta;   //!
   TBranch        *b_jetAreaFM;   //!
   TBranch        *b_jetAreaM;   //!
   TBranch        *b_jetAreaPhi;   //!
   TBranch        *b_jetAreaPt;   //!
   TBranch        *b_jetCalE;   //!
   TBranch        *b_jetCalEta;   //!
   TBranch        *b_jetCalM;   //!
   TBranch        *b_jetCalPhi;   //!
   TBranch        *b_jetCalPt;   //!
   TBranch        *b_jetCnt;   //!
   TBranch        *b_jetNConst;   //!
   TBranch        *b_jetRawE;   //!
   TBranch        *b_jetRawEta;   //!
   TBranch        *b_jetRawM;   //!
   TBranch        *b_jetRawPhi;   //!
   TBranch        *b_jetRawPt;   //!
   TBranch        *b_matchedLCWJetRawE;   //!
   TBranch        *b_matchedLCWJetRawM;   //!
   TBranch        *b_matchedLCWJetRawPhi;   //!
   TBranch        *b_matchedLCWJetRawPt;   //!
   TBranch        *b_matchedLCWJetRawRap;   //!
   TBranch        *b_medianRho;   //!
   TBranch        *b_nCluster;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_seqNumber;   //!
   TBranch        *b_sigmaRho;   //!
   TBranch        *b_truthJetE;   //!
   TBranch        *b_truthJetM;   //!
   TBranch        *b_truthJetMatchRadius;   //!
   TBranch        *b_truthJetPhi;   //!
   TBranch        *b_truthJetPt;   //!
   TBranch        *b_truthJetRap;   //!
   TBranch        *b_avgMu;   //!
   TBranch        *b_clusterE;   //!
   TBranch        *b_clusterECalib;   //!
   TBranch        *b_clusterEta;   //!
   TBranch        *b_clusterEtaCalib;   //!
   TBranch        *b_clusterIndex;   //!
   TBranch        *b_clusterPhi;   //!
   TBranch        *b_clusterPhiCalib;   //!
   TBranch        *b_clusterPt;   //!
   TBranch        *b_clusterPtCalib;   //!
   TBranch        *b_cluster_AVG_LAR_Q;   //!
   TBranch        *b_cluster_AVG_TILE_Q;   //!
   TBranch        *b_cluster_BADLARQ_FRAC;   //!
   TBranch        *b_cluster_BAD_CELLS_CORR_E;   //!
   TBranch        *b_cluster_CELL_SIGNIFICANCE;   //!
   TBranch        *b_cluster_CELL_SIG_SAMPLING;   //!
   TBranch        *b_cluster_CENTER_LAMBDA;   //!
   TBranch        *b_cluster_CENTER_MAG;   //!
   TBranch        *b_cluster_CENTER_X;   //!
   TBranch        *b_cluster_CENTER_Y;   //!
   TBranch        *b_cluster_CENTER_Z;   //!
   TBranch        *b_cluster_DELTA_ALPHA;   //!
   TBranch        *b_cluster_DELTA_PHI;   //!
   TBranch        *b_cluster_DELTA_THETA;   //!
   TBranch        *b_cluster_DM_WEIGHT;   //!
   TBranch        *b_cluster_EM_PROBABILITY;   //!
   TBranch        *b_cluster_ENG_BAD_CELLS;   //!
   TBranch        *b_cluster_ENG_BAD_HV_CELLS;   //!
   TBranch        *b_cluster_ENG_CALIB_DEAD_TOT;   //!
   TBranch        *b_cluster_ENG_CALIB_FRAC_EM;   //!
   TBranch        *b_cluster_ENG_CALIB_FRAC_HAD;   //!
   TBranch        *b_cluster_ENG_CALIB_FRAC_REST;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_L;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_M;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_T;   //!
   TBranch        *b_cluster_ENG_CALIB_TOT;   //!
   TBranch        *b_cluster_ENG_FRAC_CORE;   //!
   TBranch        *b_cluster_ENG_FRAC_EM;   //!
   TBranch        *b_cluster_ENG_FRAC_EM_INCL;   //!
   TBranch        *b_cluster_ENG_FRAC_MAX;   //!
   TBranch        *b_cluster_ENG_POS;   //!
   TBranch        *b_cluster_FIRST_ENG_DENS;   //!
   TBranch        *b_cluster_FIRST_ETA;   //!
   TBranch        *b_cluster_FIRST_PHI;   //!
   TBranch        *b_cluster_HAD_WEIGHT;   //!
   TBranch        *b_cluster_ISOLATION;   //!
   TBranch        *b_cluster_LATERAL;   //!
   TBranch        *b_cluster_LONGITUDINAL;   //!
   TBranch        *b_cluster_MASS;   //!
   TBranch        *b_cluster_N_BAD_CELLS;   //!
   TBranch        *b_cluster_N_BAD_CELLS_CORR;   //!
   TBranch        *b_cluster_N_BAD_HV_CELLS;   //!
   TBranch        *b_cluster_OOC_WEIGHT;   //!
   TBranch        *b_cluster_PTD;   //!
   TBranch        *b_cluster_SECOND_ENG_DENS;   //!
   TBranch        *b_cluster_SECOND_LAMBDA;   //!
   TBranch        *b_cluster_SECOND_R;   //!
   TBranch        *b_cluster_SECOND_TIME;   //!
   TBranch        *b_cluster_SIGNIFICANCE;   //!
   TBranch        *b_cluster_fracE;   //!
   TBranch        *b_cluster_fracECalib;   //!
   TBranch        *b_cluster_fracECalib_ref;   //!
   TBranch        *b_cluster_fracE_ref;   //!
   TBranch        *b_cluster_nCells;   //!
   TBranch        *b_cluster_nCells_tot;   //!
   TBranch        *b_cluster_sumCellE;   //!
   TBranch        *b_cluster_sumCellECalib;   //!
   TBranch        *b_cluster_time;   //!
   TBranch        *b_diffEta;   //!
   TBranch        *b_labels;   //!
   TBranch        *b_nPrimVtx;   //!
   TBranch        *b_r_e_calculated;   //!
   TBranch        *b_zL;   //!
   TBranch        *b_zRel;   //!
   TBranch        *b_zT;   //!

   GetValue(TTree *tree=0);
   virtual ~GetValue();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef GetValue_cxx
GetValue::GetValue(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/jmsardain/CalibPU/datasets/pu/JetTree_all.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data/jmsardain/CalibPU/datasets/pu/JetTree_all.root");
      }
      f->GetObject("JetTree",tree);

   }
   Init(tree);
}

GetValue::~GetValue()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GetValue::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GetValue::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void GetValue::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   avgMu = 0;
   clusterE = 0;
   clusterECalib = 0;
   clusterEta = 0;
   clusterEtaCalib = 0;
   clusterIndex = 0;
   clusterPhi = 0;
   clusterPhiCalib = 0;
   clusterPt = 0;
   clusterPtCalib = 0;
   cluster_AVG_LAR_Q = 0;
   cluster_AVG_TILE_Q = 0;
   cluster_BADLARQ_FRAC = 0;
   cluster_BAD_CELLS_CORR_E = 0;
   cluster_CELL_SIGNIFICANCE = 0;
   cluster_CELL_SIG_SAMPLING = 0;
   cluster_CENTER_LAMBDA = 0;
   cluster_CENTER_MAG = 0;
   cluster_CENTER_X = 0;
   cluster_CENTER_Y = 0;
   cluster_CENTER_Z = 0;
   cluster_DELTA_ALPHA = 0;
   cluster_DELTA_PHI = 0;
   cluster_DELTA_THETA = 0;
   cluster_DM_WEIGHT = 0;
   cluster_EM_PROBABILITY = 0;
   cluster_ENG_BAD_CELLS = 0;
   cluster_ENG_BAD_HV_CELLS = 0;
   cluster_ENG_CALIB_DEAD_TOT = 0;
   cluster_ENG_CALIB_FRAC_EM = 0;
   cluster_ENG_CALIB_FRAC_HAD = 0;
   cluster_ENG_CALIB_FRAC_REST = 0;
   cluster_ENG_CALIB_OUT_L = 0;
   cluster_ENG_CALIB_OUT_M = 0;
   cluster_ENG_CALIB_OUT_T = 0;
   cluster_ENG_CALIB_TOT = 0;
   cluster_ENG_FRAC_CORE = 0;
   cluster_ENG_FRAC_EM = 0;
   cluster_ENG_FRAC_EM_INCL = 0;
   cluster_ENG_FRAC_MAX = 0;
   cluster_ENG_POS = 0;
   cluster_FIRST_ENG_DENS = 0;
   cluster_FIRST_ETA = 0;
   cluster_FIRST_PHI = 0;
   cluster_HAD_WEIGHT = 0;
   cluster_ISOLATION = 0;
   cluster_LATERAL = 0;
   cluster_LONGITUDINAL = 0;
   cluster_MASS = 0;
   cluster_N_BAD_CELLS = 0;
   cluster_N_BAD_CELLS_CORR = 0;
   cluster_N_BAD_HV_CELLS = 0;
   cluster_OOC_WEIGHT = 0;
   cluster_PTD = 0;
   cluster_SECOND_ENG_DENS = 0;
   cluster_SECOND_LAMBDA = 0;
   cluster_SECOND_R = 0;
   cluster_SECOND_TIME = 0;
   cluster_SIGNIFICANCE = 0;
   cluster_fracE = 0;
   cluster_fracECalib = 0;
   cluster_fracECalib_ref = 0;
   cluster_fracE_ref = 0;
   cluster_nCells = 0;
   cluster_nCells_tot = 0;
   cluster_sumCellE = 0;
   cluster_sumCellECalib = 0;
   cluster_time = 0;
   diffEta = 0;
   labels = 0;
   nPrimVtx = 0;
   r_e_calculated = 0;
   zL = 0;
   zRel = 0;
   zT = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("LCWJetMatchRadius", &LCWJetMatchRadius, &b_LCWJetMatchRadius);
   fChain->SetBranchAddress("areaRho", &areaRho, &b_areaRho);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("jetArea", &jetArea, &b_jetArea);
   fChain->SetBranchAddress("jetAreaE", &jetAreaE, &b_jetAreaE);
   fChain->SetBranchAddress("jetAreaEta", &jetAreaEta, &b_jetAreaEta);
   fChain->SetBranchAddress("jetAreaFM", &jetAreaFM, &b_jetAreaFM);
   fChain->SetBranchAddress("jetAreaM", &jetAreaM, &b_jetAreaM);
   fChain->SetBranchAddress("jetAreaPhi", &jetAreaPhi, &b_jetAreaPhi);
   fChain->SetBranchAddress("jetAreaPt", &jetAreaPt, &b_jetAreaPt);
   fChain->SetBranchAddress("jetCalE", &jetCalE, &b_jetCalE);
   fChain->SetBranchAddress("jetCalEta", &jetCalEta, &b_jetCalEta);
   fChain->SetBranchAddress("jetCalM", &jetCalM, &b_jetCalM);
   fChain->SetBranchAddress("jetCalPhi", &jetCalPhi, &b_jetCalPhi);
   fChain->SetBranchAddress("jetCalPt", &jetCalPt, &b_jetCalPt);
   fChain->SetBranchAddress("jetCnt", &jetCnt, &b_jetCnt);
   fChain->SetBranchAddress("jetNConst", &jetNConst, &b_jetNConst);
   fChain->SetBranchAddress("jetRawE", &jetRawE, &b_jetRawE);
   fChain->SetBranchAddress("jetRawEta", &jetRawEta, &b_jetRawEta);
   fChain->SetBranchAddress("jetRawM", &jetRawM, &b_jetRawM);
   fChain->SetBranchAddress("jetRawPhi", &jetRawPhi, &b_jetRawPhi);
   fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
   fChain->SetBranchAddress("matchedLCWJetRawE", &matchedLCWJetRawE, &b_matchedLCWJetRawE);
   fChain->SetBranchAddress("matchedLCWJetRawM", &matchedLCWJetRawM, &b_matchedLCWJetRawM);
   fChain->SetBranchAddress("matchedLCWJetRawPhi", &matchedLCWJetRawPhi, &b_matchedLCWJetRawPhi);
   fChain->SetBranchAddress("matchedLCWJetRawPt", &matchedLCWJetRawPt, &b_matchedLCWJetRawPt);
   fChain->SetBranchAddress("matchedLCWJetRawRap", &matchedLCWJetRawRap, &b_matchedLCWJetRawRap);
   fChain->SetBranchAddress("medianRho", &medianRho, &b_medianRho);
   fChain->SetBranchAddress("nCluster", &nCluster, &b_nCluster);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("seqNumber", &seqNumber, &b_seqNumber);
   fChain->SetBranchAddress("sigmaRho", &sigmaRho, &b_sigmaRho);
   fChain->SetBranchAddress("truthJetE", &truthJetE, &b_truthJetE);
   fChain->SetBranchAddress("truthJetM", &truthJetM, &b_truthJetM);
   fChain->SetBranchAddress("truthJetMatchRadius", &truthJetMatchRadius, &b_truthJetMatchRadius);
   fChain->SetBranchAddress("truthJetPhi", &truthJetPhi, &b_truthJetPhi);
   fChain->SetBranchAddress("truthJetPt", &truthJetPt, &b_truthJetPt);
   fChain->SetBranchAddress("truthJetRap", &truthJetRap, &b_truthJetRap);
   fChain->SetBranchAddress("avgMu", &avgMu, &b_avgMu);
   fChain->SetBranchAddress("clusterE", &clusterE, &b_clusterE);
   fChain->SetBranchAddress("clusterECalib", &clusterECalib, &b_clusterECalib);
   fChain->SetBranchAddress("clusterEta", &clusterEta, &b_clusterEta);
   fChain->SetBranchAddress("clusterEtaCalib", &clusterEtaCalib, &b_clusterEtaCalib);
   fChain->SetBranchAddress("clusterIndex", &clusterIndex, &b_clusterIndex);
   fChain->SetBranchAddress("clusterPhi", &clusterPhi, &b_clusterPhi);
   fChain->SetBranchAddress("clusterPhiCalib", &clusterPhiCalib, &b_clusterPhiCalib);
   fChain->SetBranchAddress("clusterPt", &clusterPt, &b_clusterPt);
   fChain->SetBranchAddress("clusterPtCalib", &clusterPtCalib, &b_clusterPtCalib);
   fChain->SetBranchAddress("cluster_AVG_LAR_Q", &cluster_AVG_LAR_Q, &b_cluster_AVG_LAR_Q);
   fChain->SetBranchAddress("cluster_AVG_TILE_Q", &cluster_AVG_TILE_Q, &b_cluster_AVG_TILE_Q);
   fChain->SetBranchAddress("cluster_BADLARQ_FRAC", &cluster_BADLARQ_FRAC, &b_cluster_BADLARQ_FRAC);
   fChain->SetBranchAddress("cluster_BAD_CELLS_CORR_E", &cluster_BAD_CELLS_CORR_E, &b_cluster_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("cluster_CELL_SIGNIFICANCE", &cluster_CELL_SIGNIFICANCE, &b_cluster_CELL_SIGNIFICANCE);
   fChain->SetBranchAddress("cluster_CELL_SIG_SAMPLING", &cluster_CELL_SIG_SAMPLING, &b_cluster_CELL_SIG_SAMPLING);
   fChain->SetBranchAddress("cluster_CENTER_LAMBDA", &cluster_CENTER_LAMBDA, &b_cluster_CENTER_LAMBDA);
   fChain->SetBranchAddress("cluster_CENTER_MAG", &cluster_CENTER_MAG, &b_cluster_CENTER_MAG);
   fChain->SetBranchAddress("cluster_CENTER_X", &cluster_CENTER_X, &b_cluster_CENTER_X);
   fChain->SetBranchAddress("cluster_CENTER_Y", &cluster_CENTER_Y, &b_cluster_CENTER_Y);
   fChain->SetBranchAddress("cluster_CENTER_Z", &cluster_CENTER_Z, &b_cluster_CENTER_Z);
   fChain->SetBranchAddress("cluster_DELTA_ALPHA", &cluster_DELTA_ALPHA, &b_cluster_DELTA_ALPHA);
   fChain->SetBranchAddress("cluster_DELTA_PHI", &cluster_DELTA_PHI, &b_cluster_DELTA_PHI);
   fChain->SetBranchAddress("cluster_DELTA_THETA", &cluster_DELTA_THETA, &b_cluster_DELTA_THETA);
   fChain->SetBranchAddress("cluster_DM_WEIGHT", &cluster_DM_WEIGHT, &b_cluster_DM_WEIGHT);
   fChain->SetBranchAddress("cluster_EM_PROBABILITY", &cluster_EM_PROBABILITY, &b_cluster_EM_PROBABILITY);
   fChain->SetBranchAddress("cluster_ENG_BAD_CELLS", &cluster_ENG_BAD_CELLS, &b_cluster_ENG_BAD_CELLS);
   fChain->SetBranchAddress("cluster_ENG_BAD_HV_CELLS", &cluster_ENG_BAD_HV_CELLS, &b_cluster_ENG_BAD_HV_CELLS);
   fChain->SetBranchAddress("cluster_ENG_CALIB_DEAD_TOT", &cluster_ENG_CALIB_DEAD_TOT, &b_cluster_ENG_CALIB_DEAD_TOT);
   fChain->SetBranchAddress("cluster_ENG_CALIB_FRAC_EM", &cluster_ENG_CALIB_FRAC_EM, &b_cluster_ENG_CALIB_FRAC_EM);
   fChain->SetBranchAddress("cluster_ENG_CALIB_FRAC_HAD", &cluster_ENG_CALIB_FRAC_HAD, &b_cluster_ENG_CALIB_FRAC_HAD);
   fChain->SetBranchAddress("cluster_ENG_CALIB_FRAC_REST", &cluster_ENG_CALIB_FRAC_REST, &b_cluster_ENG_CALIB_FRAC_REST);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_L", &cluster_ENG_CALIB_OUT_L, &b_cluster_ENG_CALIB_OUT_L);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_M", &cluster_ENG_CALIB_OUT_M, &b_cluster_ENG_CALIB_OUT_M);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_T", &cluster_ENG_CALIB_OUT_T, &b_cluster_ENG_CALIB_OUT_T);
   fChain->SetBranchAddress("cluster_ENG_CALIB_TOT", &cluster_ENG_CALIB_TOT, &b_cluster_ENG_CALIB_TOT);
   fChain->SetBranchAddress("cluster_ENG_FRAC_CORE", &cluster_ENG_FRAC_CORE, &b_cluster_ENG_FRAC_CORE);
   fChain->SetBranchAddress("cluster_ENG_FRAC_EM", &cluster_ENG_FRAC_EM, &b_cluster_ENG_FRAC_EM);
   fChain->SetBranchAddress("cluster_ENG_FRAC_EM_INCL", &cluster_ENG_FRAC_EM_INCL, &b_cluster_ENG_FRAC_EM_INCL);
   fChain->SetBranchAddress("cluster_ENG_FRAC_MAX", &cluster_ENG_FRAC_MAX, &b_cluster_ENG_FRAC_MAX);
   fChain->SetBranchAddress("cluster_ENG_POS", &cluster_ENG_POS, &b_cluster_ENG_POS);
   fChain->SetBranchAddress("cluster_FIRST_ENG_DENS", &cluster_FIRST_ENG_DENS, &b_cluster_FIRST_ENG_DENS);
   fChain->SetBranchAddress("cluster_FIRST_ETA", &cluster_FIRST_ETA, &b_cluster_FIRST_ETA);
   fChain->SetBranchAddress("cluster_FIRST_PHI", &cluster_FIRST_PHI, &b_cluster_FIRST_PHI);
   fChain->SetBranchAddress("cluster_HAD_WEIGHT", &cluster_HAD_WEIGHT, &b_cluster_HAD_WEIGHT);
   fChain->SetBranchAddress("cluster_ISOLATION", &cluster_ISOLATION, &b_cluster_ISOLATION);
   fChain->SetBranchAddress("cluster_LATERAL", &cluster_LATERAL, &b_cluster_LATERAL);
   fChain->SetBranchAddress("cluster_LONGITUDINAL", &cluster_LONGITUDINAL, &b_cluster_LONGITUDINAL);
   fChain->SetBranchAddress("cluster_MASS", &cluster_MASS, &b_cluster_MASS);
   fChain->SetBranchAddress("cluster_N_BAD_CELLS", &cluster_N_BAD_CELLS, &b_cluster_N_BAD_CELLS);
   fChain->SetBranchAddress("cluster_N_BAD_CELLS_CORR", &cluster_N_BAD_CELLS_CORR, &b_cluster_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("cluster_N_BAD_HV_CELLS", &cluster_N_BAD_HV_CELLS, &b_cluster_N_BAD_HV_CELLS);
   fChain->SetBranchAddress("cluster_OOC_WEIGHT", &cluster_OOC_WEIGHT, &b_cluster_OOC_WEIGHT);
   fChain->SetBranchAddress("cluster_PTD", &cluster_PTD, &b_cluster_PTD);
   fChain->SetBranchAddress("cluster_SECOND_ENG_DENS", &cluster_SECOND_ENG_DENS, &b_cluster_SECOND_ENG_DENS);
   fChain->SetBranchAddress("cluster_SECOND_LAMBDA", &cluster_SECOND_LAMBDA, &b_cluster_SECOND_LAMBDA);
   fChain->SetBranchAddress("cluster_SECOND_R", &cluster_SECOND_R, &b_cluster_SECOND_R);
   fChain->SetBranchAddress("cluster_SECOND_TIME", &cluster_SECOND_TIME, &b_cluster_SECOND_TIME);
   fChain->SetBranchAddress("cluster_SIGNIFICANCE", &cluster_SIGNIFICANCE, &b_cluster_SIGNIFICANCE);
   fChain->SetBranchAddress("cluster_fracE", &cluster_fracE, &b_cluster_fracE);
   fChain->SetBranchAddress("cluster_fracECalib", &cluster_fracECalib, &b_cluster_fracECalib);
   fChain->SetBranchAddress("cluster_fracECalib_ref", &cluster_fracECalib_ref, &b_cluster_fracECalib_ref);
   fChain->SetBranchAddress("cluster_fracE_ref", &cluster_fracE_ref, &b_cluster_fracE_ref);
   fChain->SetBranchAddress("cluster_nCells", &cluster_nCells, &b_cluster_nCells);
   fChain->SetBranchAddress("cluster_nCells_tot", &cluster_nCells_tot, &b_cluster_nCells_tot);
   fChain->SetBranchAddress("cluster_sumCellE", &cluster_sumCellE, &b_cluster_sumCellE);
   fChain->SetBranchAddress("cluster_sumCellECalib", &cluster_sumCellECalib, &b_cluster_sumCellECalib);
   fChain->SetBranchAddress("cluster_time", &cluster_time, &b_cluster_time);
   fChain->SetBranchAddress("diffEta", &diffEta, &b_diffEta);
   fChain->SetBranchAddress("labels", &labels, &b_labels);
   fChain->SetBranchAddress("nPrimVtx", &nPrimVtx, &b_nPrimVtx);
   fChain->SetBranchAddress("r_e_calculated", &r_e_calculated, &b_r_e_calculated);
   fChain->SetBranchAddress("zL", &zL, &b_zL);
   fChain->SetBranchAddress("zRel", &zRel, &b_zRel);
   fChain->SetBranchAddress("zT", &zT, &b_zT);
   Notify();
}

bool GetValue::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void GetValue::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GetValue::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GetValue_cxx
