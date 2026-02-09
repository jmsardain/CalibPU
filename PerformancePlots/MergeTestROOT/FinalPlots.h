//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb  3 14:59:40 2026 by ROOT version 6.36.02
// from TTree JetTree/
// found on file: /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb32026/final.root
//////////////////////////////////////////////////////////

#ifndef FinalPlots_h
#define FinalPlots_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class FinalPlots {
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
   Int_t           navgMu;
   Double_t        avgMu[59];   //[navgMu]
   Int_t           nclusterE;
   Double_t        clusterE[59];   //[nclusterE]
   Int_t           nclusterECalib;
   Double_t        clusterECalib[59];   //[nclusterECalib]
   Int_t           nclusterEta;
   Double_t        clusterEta[59];   //[nclusterEta]
   Int_t           nclusterEtaCalib;
   Double_t        clusterEtaCalib[59];   //[nclusterEtaCalib]
   Int_t           nclusterIndex;
   Double_t        clusterIndex[59];   //[nclusterIndex]
   Int_t           nclusterPhi;
   Double_t        clusterPhi[59];   //[nclusterPhi]
   Int_t           nclusterPhiCalib;
   Double_t        clusterPhiCalib[59];   //[nclusterPhiCalib]
   Int_t           nclusterPt;
   Double_t        clusterPt[59];   //[nclusterPt]
   Int_t           nclusterPtCalib;
   Double_t        clusterPtCalib[59];   //[nclusterPtCalib]
   Int_t           ncluster_AVG_LAR_Q;
   Double_t        cluster_AVG_LAR_Q[59];   //[ncluster_AVG_LAR_Q]
   Int_t           ncluster_AVG_TILE_Q;
   Double_t        cluster_AVG_TILE_Q[59];   //[ncluster_AVG_TILE_Q]
   Int_t           ncluster_BADLARQ_FRAC;
   Double_t        cluster_BADLARQ_FRAC[59];   //[ncluster_BADLARQ_FRAC]
   Int_t           ncluster_BAD_CELLS_CORR_E;
   Double_t        cluster_BAD_CELLS_CORR_E[59];   //[ncluster_BAD_CELLS_CORR_E]
   Int_t           ncluster_CELL_SIGNIFICANCE;
   Double_t        cluster_CELL_SIGNIFICANCE[59];   //[ncluster_CELL_SIGNIFICANCE]
   Int_t           ncluster_CELL_SIG_SAMPLING;
   Double_t        cluster_CELL_SIG_SAMPLING[59];   //[ncluster_CELL_SIG_SAMPLING]
   Int_t           ncluster_CENTER_LAMBDA;
   Double_t        cluster_CENTER_LAMBDA[59];   //[ncluster_CENTER_LAMBDA]
   Int_t           ncluster_CENTER_MAG;
   Double_t        cluster_CENTER_MAG[59];   //[ncluster_CENTER_MAG]
   Int_t           ncluster_CENTER_X;
   Double_t        cluster_CENTER_X[59];   //[ncluster_CENTER_X]
   Int_t           ncluster_CENTER_Y;
   Double_t        cluster_CENTER_Y[59];   //[ncluster_CENTER_Y]
   Int_t           ncluster_CENTER_Z;
   Double_t        cluster_CENTER_Z[59];   //[ncluster_CENTER_Z]
   Int_t           ncluster_DELTA_ALPHA;
   Double_t        cluster_DELTA_ALPHA[59];   //[ncluster_DELTA_ALPHA]
   Int_t           ncluster_DELTA_PHI;
   Double_t        cluster_DELTA_PHI[59];   //[ncluster_DELTA_PHI]
   Int_t           ncluster_DELTA_THETA;
   Double_t        cluster_DELTA_THETA[59];   //[ncluster_DELTA_THETA]
   Int_t           ncluster_DM_WEIGHT;
   Double_t        cluster_DM_WEIGHT[59];   //[ncluster_DM_WEIGHT]
   Int_t           ncluster_EM_PROBABILITY;
   Double_t        cluster_EM_PROBABILITY[59];   //[ncluster_EM_PROBABILITY]
   Int_t           ncluster_ENG_BAD_CELLS;
   Double_t        cluster_ENG_BAD_CELLS[59];   //[ncluster_ENG_BAD_CELLS]
   Int_t           ncluster_ENG_BAD_HV_CELLS;
   Double_t        cluster_ENG_BAD_HV_CELLS[59];   //[ncluster_ENG_BAD_HV_CELLS]
   Int_t           ncluster_ENG_CALIB_DEAD_TOT;
   Double_t        cluster_ENG_CALIB_DEAD_TOT[59];   //[ncluster_ENG_CALIB_DEAD_TOT]
   Int_t           ncluster_ENG_CALIB_FRAC_EM;
   Double_t        cluster_ENG_CALIB_FRAC_EM[59];   //[ncluster_ENG_CALIB_FRAC_EM]
   Int_t           ncluster_ENG_CALIB_FRAC_HAD;
   Double_t        cluster_ENG_CALIB_FRAC_HAD[59];   //[ncluster_ENG_CALIB_FRAC_HAD]
   Int_t           ncluster_ENG_CALIB_FRAC_REST;
   Double_t        cluster_ENG_CALIB_FRAC_REST[59];   //[ncluster_ENG_CALIB_FRAC_REST]
   Int_t           ncluster_ENG_CALIB_OUT_L;
   Double_t        cluster_ENG_CALIB_OUT_L[59];   //[ncluster_ENG_CALIB_OUT_L]
   Int_t           ncluster_ENG_CALIB_OUT_M;
   Double_t        cluster_ENG_CALIB_OUT_M[59];   //[ncluster_ENG_CALIB_OUT_M]
   Int_t           ncluster_ENG_CALIB_OUT_T;
   Double_t        cluster_ENG_CALIB_OUT_T[59];   //[ncluster_ENG_CALIB_OUT_T]
   Int_t           ncluster_ENG_CALIB_TOT;
   Double_t        cluster_ENG_CALIB_TOT[59];   //[ncluster_ENG_CALIB_TOT]
   Int_t           ncluster_ENG_FRAC_CORE;
   Double_t        cluster_ENG_FRAC_CORE[59];   //[ncluster_ENG_FRAC_CORE]
   Int_t           ncluster_ENG_FRAC_EM;
   Double_t        cluster_ENG_FRAC_EM[59];   //[ncluster_ENG_FRAC_EM]
   Int_t           ncluster_ENG_FRAC_EM_INCL;
   Double_t        cluster_ENG_FRAC_EM_INCL[59];   //[ncluster_ENG_FRAC_EM_INCL]
   Int_t           ncluster_ENG_FRAC_MAX;
   Double_t        cluster_ENG_FRAC_MAX[59];   //[ncluster_ENG_FRAC_MAX]
   Int_t           ncluster_ENG_POS;
   Double_t        cluster_ENG_POS[59];   //[ncluster_ENG_POS]
   Int_t           ncluster_FIRST_ENG_DENS;
   Double_t        cluster_FIRST_ENG_DENS[59];   //[ncluster_FIRST_ENG_DENS]
   Int_t           ncluster_FIRST_ETA;
   Double_t        cluster_FIRST_ETA[59];   //[ncluster_FIRST_ETA]
   Int_t           ncluster_FIRST_PHI;
   Double_t        cluster_FIRST_PHI[59];   //[ncluster_FIRST_PHI]
   Int_t           ncluster_HAD_WEIGHT;
   Double_t        cluster_HAD_WEIGHT[59];   //[ncluster_HAD_WEIGHT]
   Int_t           ncluster_ISOLATION;
   Double_t        cluster_ISOLATION[59];   //[ncluster_ISOLATION]
   Int_t           ncluster_LATERAL;
   Double_t        cluster_LATERAL[59];   //[ncluster_LATERAL]
   Int_t           ncluster_LONGITUDINAL;
   Double_t        cluster_LONGITUDINAL[59];   //[ncluster_LONGITUDINAL]
   Int_t           ncluster_MASS;
   Double_t        cluster_MASS[59];   //[ncluster_MASS]
   Int_t           ncluster_N_BAD_CELLS;
   Double_t        cluster_N_BAD_CELLS[59];   //[ncluster_N_BAD_CELLS]
   Int_t           ncluster_N_BAD_CELLS_CORR;
   Double_t        cluster_N_BAD_CELLS_CORR[59];   //[ncluster_N_BAD_CELLS_CORR]
   Int_t           ncluster_N_BAD_HV_CELLS;
   Double_t        cluster_N_BAD_HV_CELLS[59];   //[ncluster_N_BAD_HV_CELLS]
   Int_t           ncluster_OOC_WEIGHT;
   Double_t        cluster_OOC_WEIGHT[59];   //[ncluster_OOC_WEIGHT]
   Int_t           ncluster_PTD;
   Double_t        cluster_PTD[59];   //[ncluster_PTD]
   Int_t           ncluster_SECOND_ENG_DENS;
   Double_t        cluster_SECOND_ENG_DENS[59];   //[ncluster_SECOND_ENG_DENS]
   Int_t           ncluster_SECOND_LAMBDA;
   Double_t        cluster_SECOND_LAMBDA[59];   //[ncluster_SECOND_LAMBDA]
   Int_t           ncluster_SECOND_R;
   Double_t        cluster_SECOND_R[59];   //[ncluster_SECOND_R]
   Int_t           ncluster_SECOND_TIME;
   Double_t        cluster_SECOND_TIME[59];   //[ncluster_SECOND_TIME]
   Int_t           ncluster_SIGNIFICANCE;
   Double_t        cluster_SIGNIFICANCE[59];   //[ncluster_SIGNIFICANCE]
   Int_t           ncluster_fracE;
   Double_t        cluster_fracE[59];   //[ncluster_fracE]
   Int_t           ncluster_fracECalib;
   Double_t        cluster_fracECalib[59];   //[ncluster_fracECalib]
   Int_t           ncluster_fracECalib_ref;
   Double_t        cluster_fracECalib_ref[59];   //[ncluster_fracECalib_ref]
   Int_t           ncluster_fracE_ref;
   Double_t        cluster_fracE_ref[59];   //[ncluster_fracE_ref]
   Int_t           ncluster_nCells;
   Double_t        cluster_nCells[59];   //[ncluster_nCells]
   Int_t           ncluster_nCells_tot;
   Double_t        cluster_nCells_tot[59];   //[ncluster_nCells_tot]
   Int_t           ncluster_sumCellE;
   Double_t        cluster_sumCellE[59];   //[ncluster_sumCellE]
   Int_t           ncluster_sumCellECalib;
   Double_t        cluster_sumCellECalib[59];   //[ncluster_sumCellECalib]
   Int_t           ncluster_time;
   Double_t        cluster_time[59];   //[ncluster_time]
   Int_t           ndiffEta;
   Double_t        diffEta[59];   //[ndiffEta]
   Int_t           nlabels;
   Long64_t        labels[59];   //[nlabels]
   Int_t           nnPrimVtx;
   Long64_t        nPrimVtx[59];   //[nnPrimVtx]
   Int_t           nr_e_calculated;
   Double_t        r_e_calculated[59];   //[nr_e_calculated]
   Int_t           nzL;
   Double_t        zL[59];   //[nzL]
   Int_t           nzRel;
   Double_t        zRel[59];   //[nzRel]
   Int_t           nzT;
   Double_t        zT[59];   //[nzT]
   Int_t           nlabels_test;
   Double_t        labels_test[59];   //[nlabels_test]
   Int_t           nnodes_out;
   Double_t        nodes_out[59];   //[nnodes_out]

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
   TBranch        *b_navgMu;   //!
   TBranch        *b_avgMu;   //!
   TBranch        *b_nclusterE;   //!
   TBranch        *b_clusterE;   //!
   TBranch        *b_nclusterECalib;   //!
   TBranch        *b_clusterECalib;   //!
   TBranch        *b_nclusterEta;   //!
   TBranch        *b_clusterEta;   //!
   TBranch        *b_nclusterEtaCalib;   //!
   TBranch        *b_clusterEtaCalib;   //!
   TBranch        *b_nclusterIndex;   //!
   TBranch        *b_clusterIndex;   //!
   TBranch        *b_nclusterPhi;   //!
   TBranch        *b_clusterPhi;   //!
   TBranch        *b_nclusterPhiCalib;   //!
   TBranch        *b_clusterPhiCalib;   //!
   TBranch        *b_nclusterPt;   //!
   TBranch        *b_clusterPt;   //!
   TBranch        *b_nclusterPtCalib;   //!
   TBranch        *b_clusterPtCalib;   //!
   TBranch        *b_ncluster_AVG_LAR_Q;   //!
   TBranch        *b_cluster_AVG_LAR_Q;   //!
   TBranch        *b_ncluster_AVG_TILE_Q;   //!
   TBranch        *b_cluster_AVG_TILE_Q;   //!
   TBranch        *b_ncluster_BADLARQ_FRAC;   //!
   TBranch        *b_cluster_BADLARQ_FRAC;   //!
   TBranch        *b_ncluster_BAD_CELLS_CORR_E;   //!
   TBranch        *b_cluster_BAD_CELLS_CORR_E;   //!
   TBranch        *b_ncluster_CELL_SIGNIFICANCE;   //!
   TBranch        *b_cluster_CELL_SIGNIFICANCE;   //!
   TBranch        *b_ncluster_CELL_SIG_SAMPLING;   //!
   TBranch        *b_cluster_CELL_SIG_SAMPLING;   //!
   TBranch        *b_ncluster_CENTER_LAMBDA;   //!
   TBranch        *b_cluster_CENTER_LAMBDA;   //!
   TBranch        *b_ncluster_CENTER_MAG;   //!
   TBranch        *b_cluster_CENTER_MAG;   //!
   TBranch        *b_ncluster_CENTER_X;   //!
   TBranch        *b_cluster_CENTER_X;   //!
   TBranch        *b_ncluster_CENTER_Y;   //!
   TBranch        *b_cluster_CENTER_Y;   //!
   TBranch        *b_ncluster_CENTER_Z;   //!
   TBranch        *b_cluster_CENTER_Z;   //!
   TBranch        *b_ncluster_DELTA_ALPHA;   //!
   TBranch        *b_cluster_DELTA_ALPHA;   //!
   TBranch        *b_ncluster_DELTA_PHI;   //!
   TBranch        *b_cluster_DELTA_PHI;   //!
   TBranch        *b_ncluster_DELTA_THETA;   //!
   TBranch        *b_cluster_DELTA_THETA;   //!
   TBranch        *b_ncluster_DM_WEIGHT;   //!
   TBranch        *b_cluster_DM_WEIGHT;   //!
   TBranch        *b_ncluster_EM_PROBABILITY;   //!
   TBranch        *b_cluster_EM_PROBABILITY;   //!
   TBranch        *b_ncluster_ENG_BAD_CELLS;   //!
   TBranch        *b_cluster_ENG_BAD_CELLS;   //!
   TBranch        *b_ncluster_ENG_BAD_HV_CELLS;   //!
   TBranch        *b_cluster_ENG_BAD_HV_CELLS;   //!
   TBranch        *b_ncluster_ENG_CALIB_DEAD_TOT;   //!
   TBranch        *b_cluster_ENG_CALIB_DEAD_TOT;   //!
   TBranch        *b_ncluster_ENG_CALIB_FRAC_EM;   //!
   TBranch        *b_cluster_ENG_CALIB_FRAC_EM;   //!
   TBranch        *b_ncluster_ENG_CALIB_FRAC_HAD;   //!
   TBranch        *b_cluster_ENG_CALIB_FRAC_HAD;   //!
   TBranch        *b_ncluster_ENG_CALIB_FRAC_REST;   //!
   TBranch        *b_cluster_ENG_CALIB_FRAC_REST;   //!
   TBranch        *b_ncluster_ENG_CALIB_OUT_L;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_L;   //!
   TBranch        *b_ncluster_ENG_CALIB_OUT_M;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_M;   //!
   TBranch        *b_ncluster_ENG_CALIB_OUT_T;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_T;   //!
   TBranch        *b_ncluster_ENG_CALIB_TOT;   //!
   TBranch        *b_cluster_ENG_CALIB_TOT;   //!
   TBranch        *b_ncluster_ENG_FRAC_CORE;   //!
   TBranch        *b_cluster_ENG_FRAC_CORE;   //!
   TBranch        *b_ncluster_ENG_FRAC_EM;   //!
   TBranch        *b_cluster_ENG_FRAC_EM;   //!
   TBranch        *b_ncluster_ENG_FRAC_EM_INCL;   //!
   TBranch        *b_cluster_ENG_FRAC_EM_INCL;   //!
   TBranch        *b_ncluster_ENG_FRAC_MAX;   //!
   TBranch        *b_cluster_ENG_FRAC_MAX;   //!
   TBranch        *b_ncluster_ENG_POS;   //!
   TBranch        *b_cluster_ENG_POS;   //!
   TBranch        *b_ncluster_FIRST_ENG_DENS;   //!
   TBranch        *b_cluster_FIRST_ENG_DENS;   //!
   TBranch        *b_ncluster_FIRST_ETA;   //!
   TBranch        *b_cluster_FIRST_ETA;   //!
   TBranch        *b_ncluster_FIRST_PHI;   //!
   TBranch        *b_cluster_FIRST_PHI;   //!
   TBranch        *b_ncluster_HAD_WEIGHT;   //!
   TBranch        *b_cluster_HAD_WEIGHT;   //!
   TBranch        *b_ncluster_ISOLATION;   //!
   TBranch        *b_cluster_ISOLATION;   //!
   TBranch        *b_ncluster_LATERAL;   //!
   TBranch        *b_cluster_LATERAL;   //!
   TBranch        *b_ncluster_LONGITUDINAL;   //!
   TBranch        *b_cluster_LONGITUDINAL;   //!
   TBranch        *b_ncluster_MASS;   //!
   TBranch        *b_cluster_MASS;   //!
   TBranch        *b_ncluster_N_BAD_CELLS;   //!
   TBranch        *b_cluster_N_BAD_CELLS;   //!
   TBranch        *b_ncluster_N_BAD_CELLS_CORR;   //!
   TBranch        *b_cluster_N_BAD_CELLS_CORR;   //!
   TBranch        *b_ncluster_N_BAD_HV_CELLS;   //!
   TBranch        *b_cluster_N_BAD_HV_CELLS;   //!
   TBranch        *b_ncluster_OOC_WEIGHT;   //!
   TBranch        *b_cluster_OOC_WEIGHT;   //!
   TBranch        *b_ncluster_PTD;   //!
   TBranch        *b_cluster_PTD;   //!
   TBranch        *b_ncluster_SECOND_ENG_DENS;   //!
   TBranch        *b_cluster_SECOND_ENG_DENS;   //!
   TBranch        *b_ncluster_SECOND_LAMBDA;   //!
   TBranch        *b_cluster_SECOND_LAMBDA;   //!
   TBranch        *b_ncluster_SECOND_R;   //!
   TBranch        *b_cluster_SECOND_R;   //!
   TBranch        *b_ncluster_SECOND_TIME;   //!
   TBranch        *b_cluster_SECOND_TIME;   //!
   TBranch        *b_ncluster_SIGNIFICANCE;   //!
   TBranch        *b_cluster_SIGNIFICANCE;   //!
   TBranch        *b_ncluster_fracE;   //!
   TBranch        *b_cluster_fracE;   //!
   TBranch        *b_ncluster_fracECalib;   //!
   TBranch        *b_cluster_fracECalib;   //!
   TBranch        *b_ncluster_fracECalib_ref;   //!
   TBranch        *b_cluster_fracECalib_ref;   //!
   TBranch        *b_ncluster_fracE_ref;   //!
   TBranch        *b_cluster_fracE_ref;   //!
   TBranch        *b_ncluster_nCells;   //!
   TBranch        *b_cluster_nCells;   //!
   TBranch        *b_ncluster_nCells_tot;   //!
   TBranch        *b_cluster_nCells_tot;   //!
   TBranch        *b_ncluster_sumCellE;   //!
   TBranch        *b_cluster_sumCellE;   //!
   TBranch        *b_ncluster_sumCellECalib;   //!
   TBranch        *b_cluster_sumCellECalib;   //!
   TBranch        *b_ncluster_time;   //!
   TBranch        *b_cluster_time;   //!
   TBranch        *b_ndiffEta;   //!
   TBranch        *b_diffEta;   //!
   TBranch        *b_nlabels;   //!
   TBranch        *b_labels;   //!
   TBranch        *b_nnPrimVtx;   //!
   TBranch        *b_nPrimVtx;   //!
   TBranch        *b_nr_e_calculated;   //!
   TBranch        *b_r_e_calculated;   //!
   TBranch        *b_nzL;   //!
   TBranch        *b_zL;   //!
   TBranch        *b_nzRel;   //!
   TBranch        *b_zRel;   //!
   TBranch        *b_nzT;   //!
   TBranch        *b_zT;   //!
   TBranch        *b_nlabels_test;   //!
   TBranch        *b_labels_test;   //!
   TBranch        *b_nnodes_out;   //!
   TBranch        *b_nodes_out;   //!

   FinalPlots(TTree *tree=0);
   virtual ~FinalPlots();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FinalPlots_cxx
FinalPlots::FinalPlots(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/jmsardain/CalibPU/trainings/pu/ckpts/Feb32026/final.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data/jmsardain/CalibPU/trainings/pu/ckpts/Feb32026/final.root");
      }
      f->GetObject("JetTree",tree);

   }
   Init(tree);
}

FinalPlots::~FinalPlots()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FinalPlots::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FinalPlots::LoadTree(Long64_t entry)
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

void FinalPlots::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

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
   fChain->SetBranchAddress("navgMu", &navgMu, &b_navgMu);
   fChain->SetBranchAddress("avgMu", avgMu, &b_avgMu);
   fChain->SetBranchAddress("nclusterE", &nclusterE, &b_nclusterE);
   fChain->SetBranchAddress("clusterE", clusterE, &b_clusterE);
   fChain->SetBranchAddress("nclusterECalib", &nclusterECalib, &b_nclusterECalib);
   fChain->SetBranchAddress("clusterECalib", clusterECalib, &b_clusterECalib);
   fChain->SetBranchAddress("nclusterEta", &nclusterEta, &b_nclusterEta);
   fChain->SetBranchAddress("clusterEta", clusterEta, &b_clusterEta);
   fChain->SetBranchAddress("nclusterEtaCalib", &nclusterEtaCalib, &b_nclusterEtaCalib);
   fChain->SetBranchAddress("clusterEtaCalib", clusterEtaCalib, &b_clusterEtaCalib);
   fChain->SetBranchAddress("nclusterIndex", &nclusterIndex, &b_nclusterIndex);
   fChain->SetBranchAddress("clusterIndex", clusterIndex, &b_clusterIndex);
   fChain->SetBranchAddress("nclusterPhi", &nclusterPhi, &b_nclusterPhi);
   fChain->SetBranchAddress("clusterPhi", clusterPhi, &b_clusterPhi);
   fChain->SetBranchAddress("nclusterPhiCalib", &nclusterPhiCalib, &b_nclusterPhiCalib);
   fChain->SetBranchAddress("clusterPhiCalib", clusterPhiCalib, &b_clusterPhiCalib);
   fChain->SetBranchAddress("nclusterPt", &nclusterPt, &b_nclusterPt);
   fChain->SetBranchAddress("clusterPt", clusterPt, &b_clusterPt);
   fChain->SetBranchAddress("nclusterPtCalib", &nclusterPtCalib, &b_nclusterPtCalib);
   fChain->SetBranchAddress("clusterPtCalib", clusterPtCalib, &b_clusterPtCalib);
   fChain->SetBranchAddress("ncluster_AVG_LAR_Q", &ncluster_AVG_LAR_Q, &b_ncluster_AVG_LAR_Q);
   fChain->SetBranchAddress("cluster_AVG_LAR_Q", cluster_AVG_LAR_Q, &b_cluster_AVG_LAR_Q);
   fChain->SetBranchAddress("ncluster_AVG_TILE_Q", &ncluster_AVG_TILE_Q, &b_ncluster_AVG_TILE_Q);
   fChain->SetBranchAddress("cluster_AVG_TILE_Q", cluster_AVG_TILE_Q, &b_cluster_AVG_TILE_Q);
   fChain->SetBranchAddress("ncluster_BADLARQ_FRAC", &ncluster_BADLARQ_FRAC, &b_ncluster_BADLARQ_FRAC);
   fChain->SetBranchAddress("cluster_BADLARQ_FRAC", cluster_BADLARQ_FRAC, &b_cluster_BADLARQ_FRAC);
   fChain->SetBranchAddress("ncluster_BAD_CELLS_CORR_E", &ncluster_BAD_CELLS_CORR_E, &b_ncluster_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("cluster_BAD_CELLS_CORR_E", cluster_BAD_CELLS_CORR_E, &b_cluster_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("ncluster_CELL_SIGNIFICANCE", &ncluster_CELL_SIGNIFICANCE, &b_ncluster_CELL_SIGNIFICANCE);
   fChain->SetBranchAddress("cluster_CELL_SIGNIFICANCE", cluster_CELL_SIGNIFICANCE, &b_cluster_CELL_SIGNIFICANCE);
   fChain->SetBranchAddress("ncluster_CELL_SIG_SAMPLING", &ncluster_CELL_SIG_SAMPLING, &b_ncluster_CELL_SIG_SAMPLING);
   fChain->SetBranchAddress("cluster_CELL_SIG_SAMPLING", cluster_CELL_SIG_SAMPLING, &b_cluster_CELL_SIG_SAMPLING);
   fChain->SetBranchAddress("ncluster_CENTER_LAMBDA", &ncluster_CENTER_LAMBDA, &b_ncluster_CENTER_LAMBDA);
   fChain->SetBranchAddress("cluster_CENTER_LAMBDA", cluster_CENTER_LAMBDA, &b_cluster_CENTER_LAMBDA);
   fChain->SetBranchAddress("ncluster_CENTER_MAG", &ncluster_CENTER_MAG, &b_ncluster_CENTER_MAG);
   fChain->SetBranchAddress("cluster_CENTER_MAG", cluster_CENTER_MAG, &b_cluster_CENTER_MAG);
   fChain->SetBranchAddress("ncluster_CENTER_X", &ncluster_CENTER_X, &b_ncluster_CENTER_X);
   fChain->SetBranchAddress("cluster_CENTER_X", cluster_CENTER_X, &b_cluster_CENTER_X);
   fChain->SetBranchAddress("ncluster_CENTER_Y", &ncluster_CENTER_Y, &b_ncluster_CENTER_Y);
   fChain->SetBranchAddress("cluster_CENTER_Y", cluster_CENTER_Y, &b_cluster_CENTER_Y);
   fChain->SetBranchAddress("ncluster_CENTER_Z", &ncluster_CENTER_Z, &b_ncluster_CENTER_Z);
   fChain->SetBranchAddress("cluster_CENTER_Z", cluster_CENTER_Z, &b_cluster_CENTER_Z);
   fChain->SetBranchAddress("ncluster_DELTA_ALPHA", &ncluster_DELTA_ALPHA, &b_ncluster_DELTA_ALPHA);
   fChain->SetBranchAddress("cluster_DELTA_ALPHA", cluster_DELTA_ALPHA, &b_cluster_DELTA_ALPHA);
   fChain->SetBranchAddress("ncluster_DELTA_PHI", &ncluster_DELTA_PHI, &b_ncluster_DELTA_PHI);
   fChain->SetBranchAddress("cluster_DELTA_PHI", cluster_DELTA_PHI, &b_cluster_DELTA_PHI);
   fChain->SetBranchAddress("ncluster_DELTA_THETA", &ncluster_DELTA_THETA, &b_ncluster_DELTA_THETA);
   fChain->SetBranchAddress("cluster_DELTA_THETA", cluster_DELTA_THETA, &b_cluster_DELTA_THETA);
   fChain->SetBranchAddress("ncluster_DM_WEIGHT", &ncluster_DM_WEIGHT, &b_ncluster_DM_WEIGHT);
   fChain->SetBranchAddress("cluster_DM_WEIGHT", cluster_DM_WEIGHT, &b_cluster_DM_WEIGHT);
   fChain->SetBranchAddress("ncluster_EM_PROBABILITY", &ncluster_EM_PROBABILITY, &b_ncluster_EM_PROBABILITY);
   fChain->SetBranchAddress("cluster_EM_PROBABILITY", cluster_EM_PROBABILITY, &b_cluster_EM_PROBABILITY);
   fChain->SetBranchAddress("ncluster_ENG_BAD_CELLS", &ncluster_ENG_BAD_CELLS, &b_ncluster_ENG_BAD_CELLS);
   fChain->SetBranchAddress("cluster_ENG_BAD_CELLS", cluster_ENG_BAD_CELLS, &b_cluster_ENG_BAD_CELLS);
   fChain->SetBranchAddress("ncluster_ENG_BAD_HV_CELLS", &ncluster_ENG_BAD_HV_CELLS, &b_ncluster_ENG_BAD_HV_CELLS);
   fChain->SetBranchAddress("cluster_ENG_BAD_HV_CELLS", cluster_ENG_BAD_HV_CELLS, &b_cluster_ENG_BAD_HV_CELLS);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_DEAD_TOT", &ncluster_ENG_CALIB_DEAD_TOT, &b_ncluster_ENG_CALIB_DEAD_TOT);
   fChain->SetBranchAddress("cluster_ENG_CALIB_DEAD_TOT", cluster_ENG_CALIB_DEAD_TOT, &b_cluster_ENG_CALIB_DEAD_TOT);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_FRAC_EM", &ncluster_ENG_CALIB_FRAC_EM, &b_ncluster_ENG_CALIB_FRAC_EM);
   fChain->SetBranchAddress("cluster_ENG_CALIB_FRAC_EM", cluster_ENG_CALIB_FRAC_EM, &b_cluster_ENG_CALIB_FRAC_EM);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_FRAC_HAD", &ncluster_ENG_CALIB_FRAC_HAD, &b_ncluster_ENG_CALIB_FRAC_HAD);
   fChain->SetBranchAddress("cluster_ENG_CALIB_FRAC_HAD", cluster_ENG_CALIB_FRAC_HAD, &b_cluster_ENG_CALIB_FRAC_HAD);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_FRAC_REST", &ncluster_ENG_CALIB_FRAC_REST, &b_ncluster_ENG_CALIB_FRAC_REST);
   fChain->SetBranchAddress("cluster_ENG_CALIB_FRAC_REST", cluster_ENG_CALIB_FRAC_REST, &b_cluster_ENG_CALIB_FRAC_REST);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_OUT_L", &ncluster_ENG_CALIB_OUT_L, &b_ncluster_ENG_CALIB_OUT_L);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_L", cluster_ENG_CALIB_OUT_L, &b_cluster_ENG_CALIB_OUT_L);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_OUT_M", &ncluster_ENG_CALIB_OUT_M, &b_ncluster_ENG_CALIB_OUT_M);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_M", cluster_ENG_CALIB_OUT_M, &b_cluster_ENG_CALIB_OUT_M);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_OUT_T", &ncluster_ENG_CALIB_OUT_T, &b_ncluster_ENG_CALIB_OUT_T);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_T", cluster_ENG_CALIB_OUT_T, &b_cluster_ENG_CALIB_OUT_T);
   fChain->SetBranchAddress("ncluster_ENG_CALIB_TOT", &ncluster_ENG_CALIB_TOT, &b_ncluster_ENG_CALIB_TOT);
   fChain->SetBranchAddress("cluster_ENG_CALIB_TOT", cluster_ENG_CALIB_TOT, &b_cluster_ENG_CALIB_TOT);
   fChain->SetBranchAddress("ncluster_ENG_FRAC_CORE", &ncluster_ENG_FRAC_CORE, &b_ncluster_ENG_FRAC_CORE);
   fChain->SetBranchAddress("cluster_ENG_FRAC_CORE", cluster_ENG_FRAC_CORE, &b_cluster_ENG_FRAC_CORE);
   fChain->SetBranchAddress("ncluster_ENG_FRAC_EM", &ncluster_ENG_FRAC_EM, &b_ncluster_ENG_FRAC_EM);
   fChain->SetBranchAddress("cluster_ENG_FRAC_EM", cluster_ENG_FRAC_EM, &b_cluster_ENG_FRAC_EM);
   fChain->SetBranchAddress("ncluster_ENG_FRAC_EM_INCL", &ncluster_ENG_FRAC_EM_INCL, &b_ncluster_ENG_FRAC_EM_INCL);
   fChain->SetBranchAddress("cluster_ENG_FRAC_EM_INCL", cluster_ENG_FRAC_EM_INCL, &b_cluster_ENG_FRAC_EM_INCL);
   fChain->SetBranchAddress("ncluster_ENG_FRAC_MAX", &ncluster_ENG_FRAC_MAX, &b_ncluster_ENG_FRAC_MAX);
   fChain->SetBranchAddress("cluster_ENG_FRAC_MAX", cluster_ENG_FRAC_MAX, &b_cluster_ENG_FRAC_MAX);
   fChain->SetBranchAddress("ncluster_ENG_POS", &ncluster_ENG_POS, &b_ncluster_ENG_POS);
   fChain->SetBranchAddress("cluster_ENG_POS", cluster_ENG_POS, &b_cluster_ENG_POS);
   fChain->SetBranchAddress("ncluster_FIRST_ENG_DENS", &ncluster_FIRST_ENG_DENS, &b_ncluster_FIRST_ENG_DENS);
   fChain->SetBranchAddress("cluster_FIRST_ENG_DENS", cluster_FIRST_ENG_DENS, &b_cluster_FIRST_ENG_DENS);
   fChain->SetBranchAddress("ncluster_FIRST_ETA", &ncluster_FIRST_ETA, &b_ncluster_FIRST_ETA);
   fChain->SetBranchAddress("cluster_FIRST_ETA", cluster_FIRST_ETA, &b_cluster_FIRST_ETA);
   fChain->SetBranchAddress("ncluster_FIRST_PHI", &ncluster_FIRST_PHI, &b_ncluster_FIRST_PHI);
   fChain->SetBranchAddress("cluster_FIRST_PHI", cluster_FIRST_PHI, &b_cluster_FIRST_PHI);
   fChain->SetBranchAddress("ncluster_HAD_WEIGHT", &ncluster_HAD_WEIGHT, &b_ncluster_HAD_WEIGHT);
   fChain->SetBranchAddress("cluster_HAD_WEIGHT", cluster_HAD_WEIGHT, &b_cluster_HAD_WEIGHT);
   fChain->SetBranchAddress("ncluster_ISOLATION", &ncluster_ISOLATION, &b_ncluster_ISOLATION);
   fChain->SetBranchAddress("cluster_ISOLATION", cluster_ISOLATION, &b_cluster_ISOLATION);
   fChain->SetBranchAddress("ncluster_LATERAL", &ncluster_LATERAL, &b_ncluster_LATERAL);
   fChain->SetBranchAddress("cluster_LATERAL", cluster_LATERAL, &b_cluster_LATERAL);
   fChain->SetBranchAddress("ncluster_LONGITUDINAL", &ncluster_LONGITUDINAL, &b_ncluster_LONGITUDINAL);
   fChain->SetBranchAddress("cluster_LONGITUDINAL", cluster_LONGITUDINAL, &b_cluster_LONGITUDINAL);
   fChain->SetBranchAddress("ncluster_MASS", &ncluster_MASS, &b_ncluster_MASS);
   fChain->SetBranchAddress("cluster_MASS", cluster_MASS, &b_cluster_MASS);
   fChain->SetBranchAddress("ncluster_N_BAD_CELLS", &ncluster_N_BAD_CELLS, &b_ncluster_N_BAD_CELLS);
   fChain->SetBranchAddress("cluster_N_BAD_CELLS", cluster_N_BAD_CELLS, &b_cluster_N_BAD_CELLS);
   fChain->SetBranchAddress("ncluster_N_BAD_CELLS_CORR", &ncluster_N_BAD_CELLS_CORR, &b_ncluster_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("cluster_N_BAD_CELLS_CORR", cluster_N_BAD_CELLS_CORR, &b_cluster_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("ncluster_N_BAD_HV_CELLS", &ncluster_N_BAD_HV_CELLS, &b_ncluster_N_BAD_HV_CELLS);
   fChain->SetBranchAddress("cluster_N_BAD_HV_CELLS", cluster_N_BAD_HV_CELLS, &b_cluster_N_BAD_HV_CELLS);
   fChain->SetBranchAddress("ncluster_OOC_WEIGHT", &ncluster_OOC_WEIGHT, &b_ncluster_OOC_WEIGHT);
   fChain->SetBranchAddress("cluster_OOC_WEIGHT", cluster_OOC_WEIGHT, &b_cluster_OOC_WEIGHT);
   fChain->SetBranchAddress("ncluster_PTD", &ncluster_PTD, &b_ncluster_PTD);
   fChain->SetBranchAddress("cluster_PTD", cluster_PTD, &b_cluster_PTD);
   fChain->SetBranchAddress("ncluster_SECOND_ENG_DENS", &ncluster_SECOND_ENG_DENS, &b_ncluster_SECOND_ENG_DENS);
   fChain->SetBranchAddress("cluster_SECOND_ENG_DENS", cluster_SECOND_ENG_DENS, &b_cluster_SECOND_ENG_DENS);
   fChain->SetBranchAddress("ncluster_SECOND_LAMBDA", &ncluster_SECOND_LAMBDA, &b_ncluster_SECOND_LAMBDA);
   fChain->SetBranchAddress("cluster_SECOND_LAMBDA", cluster_SECOND_LAMBDA, &b_cluster_SECOND_LAMBDA);
   fChain->SetBranchAddress("ncluster_SECOND_R", &ncluster_SECOND_R, &b_ncluster_SECOND_R);
   fChain->SetBranchAddress("cluster_SECOND_R", cluster_SECOND_R, &b_cluster_SECOND_R);
   fChain->SetBranchAddress("ncluster_SECOND_TIME", &ncluster_SECOND_TIME, &b_ncluster_SECOND_TIME);
   fChain->SetBranchAddress("cluster_SECOND_TIME", cluster_SECOND_TIME, &b_cluster_SECOND_TIME);
   fChain->SetBranchAddress("ncluster_SIGNIFICANCE", &ncluster_SIGNIFICANCE, &b_ncluster_SIGNIFICANCE);
   fChain->SetBranchAddress("cluster_SIGNIFICANCE", cluster_SIGNIFICANCE, &b_cluster_SIGNIFICANCE);
   fChain->SetBranchAddress("ncluster_fracE", &ncluster_fracE, &b_ncluster_fracE);
   fChain->SetBranchAddress("cluster_fracE", cluster_fracE, &b_cluster_fracE);
   fChain->SetBranchAddress("ncluster_fracECalib", &ncluster_fracECalib, &b_ncluster_fracECalib);
   fChain->SetBranchAddress("cluster_fracECalib", cluster_fracECalib, &b_cluster_fracECalib);
   fChain->SetBranchAddress("ncluster_fracECalib_ref", &ncluster_fracECalib_ref, &b_ncluster_fracECalib_ref);
   fChain->SetBranchAddress("cluster_fracECalib_ref", cluster_fracECalib_ref, &b_cluster_fracECalib_ref);
   fChain->SetBranchAddress("ncluster_fracE_ref", &ncluster_fracE_ref, &b_ncluster_fracE_ref);
   fChain->SetBranchAddress("cluster_fracE_ref", cluster_fracE_ref, &b_cluster_fracE_ref);
   fChain->SetBranchAddress("ncluster_nCells", &ncluster_nCells, &b_ncluster_nCells);
   fChain->SetBranchAddress("cluster_nCells", cluster_nCells, &b_cluster_nCells);
   fChain->SetBranchAddress("ncluster_nCells_tot", &ncluster_nCells_tot, &b_ncluster_nCells_tot);
   fChain->SetBranchAddress("cluster_nCells_tot", cluster_nCells_tot, &b_cluster_nCells_tot);
   fChain->SetBranchAddress("ncluster_sumCellE", &ncluster_sumCellE, &b_ncluster_sumCellE);
   fChain->SetBranchAddress("cluster_sumCellE", cluster_sumCellE, &b_cluster_sumCellE);
   fChain->SetBranchAddress("ncluster_sumCellECalib", &ncluster_sumCellECalib, &b_ncluster_sumCellECalib);
   fChain->SetBranchAddress("cluster_sumCellECalib", cluster_sumCellECalib, &b_cluster_sumCellECalib);
   fChain->SetBranchAddress("ncluster_time", &ncluster_time, &b_ncluster_time);
   fChain->SetBranchAddress("cluster_time", cluster_time, &b_cluster_time);
   fChain->SetBranchAddress("ndiffEta", &ndiffEta, &b_ndiffEta);
   fChain->SetBranchAddress("diffEta", diffEta, &b_diffEta);
   fChain->SetBranchAddress("nlabels", &nlabels, &b_nlabels);
   fChain->SetBranchAddress("labels", labels, &b_labels);
   fChain->SetBranchAddress("nnPrimVtx", &nnPrimVtx, &b_nnPrimVtx);
   fChain->SetBranchAddress("nPrimVtx", nPrimVtx, &b_nPrimVtx);
   fChain->SetBranchAddress("nr_e_calculated", &nr_e_calculated, &b_nr_e_calculated);
   fChain->SetBranchAddress("r_e_calculated", r_e_calculated, &b_r_e_calculated);
   fChain->SetBranchAddress("nzL", &nzL, &b_nzL);
   fChain->SetBranchAddress("zL", zL, &b_zL);
   fChain->SetBranchAddress("nzRel", &nzRel, &b_nzRel);
   fChain->SetBranchAddress("zRel", zRel, &b_zRel);
   fChain->SetBranchAddress("nzT", &nzT, &b_nzT);
   fChain->SetBranchAddress("zT", zT, &b_zT);
   fChain->SetBranchAddress("nlabels_test", &nlabels_test, &b_nlabels_test);
   fChain->SetBranchAddress("labels_test", labels_test, &b_labels_test);
   fChain->SetBranchAddress("nnodes_out", &nnodes_out, &b_nnodes_out);
   fChain->SetBranchAddress("nodes_out", nodes_out, &b_nodes_out);
   Notify();
}

bool FinalPlots::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void FinalPlots::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FinalPlots::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FinalPlots_cxx
