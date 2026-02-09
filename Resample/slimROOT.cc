//ROOT
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TH1D.h"
#include "TF1.h"
#include "TStyle.h"
#include <TVector3.h>
#include "TString.h"
#include <iostream>
#include <include/logging.h>
#include <include/io.h>




int main(int argc, char* argv[]) {

    if (argc != 5) { std::cout << "Usage: " << argv[0] << " <input root file> <output directory>" << std::endl; return 0; }

    TString in_file_name = argv[1];
    TString out_dir_name = argv[2];
    TString JZNumber = argv[3];
    TString Campaign = argv[4];
    // TString ntuple_path = "/data/jmsardain/JetCalib/Samples/"+in_file_name+"/*_mltree_calocluster.root";
    // TString ntuple_path = "/eos/user/i/issainzs/nn-topocluster-calibration/nn-topocluster-data/data/mc20_v1/user.cdelitzs.3647*root/*root";
    TString ntuple_path = "root://eosuser.cern.ch//eos/user/i/issainzs/nn-topocluster-calibration/nn-topocluster-data/data/mc20_v1/user.cdelitzs.36470"+JZNumber+".Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ"+JZNumber+"WithSW.mc20"+Campaign+"_withPU_eta2p0_26July25_v0_mltree_cluster_calo.root/user.cdelitzs.*.root";

    std::cout << " In: " << ntuple_path << std::endl
              << " " << out_dir_name << std::endl
              << " JZNumber " << JZNumber << std::endl
              << " Campaign: MC20" << Campaign
              << std::endl;

    gROOT->SetBatch(true);
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kRainBow);
    gStyle->SetNumberContours(256);

    // ROOT::EnableImplicitMT();
    // ROOT::EnableImplicitMT(1);

    gInterpreter->Declare("#include <include/io.h>");

    auto computeZ = [](float clusterPt, float clusterEta, float clusterPhi,
                   float jetPt, float jetEta, float jetPhi) {
                TVector3 c; c.SetPtEtaPhi(clusterPt, clusterEta, clusterPhi);
                TVector3 j; j.SetPtEtaPhi(jetPt, jetEta, jetPhi);
                return std::make_tuple(c.Pt()/j.Pt(), c.Dot(j)/j.Mag2(), c.Cross(j).Mag()/j.Mag2());
            };

    auto df_inclusive = ROOT::RDataFrame("ClusterTree", ntuple_path)
        // .Filter("runNumber == 300000", "2017 only")
        // .Range(10000)
        ;

    auto df_calibration = df_inclusive
        .Filter("cluster_ENG_CALIB_TOT > 0.3", "E^{dep} > 0.3")
        .Filter("clusterE > 0", "E^{EM} > 0.")
        .Filter("cluster_FIRST_ENG_DENS > 0", "rho (signal density) > 0.")
        .Filter("cluster_CENTER_LAMBDA > 0", "lambda (depth in calorimeter) > 0.")
        .Define("r_e_calculated", "clusterE / cluster_ENG_CALIB_TOT")
        ;

    auto df_pu = df_inclusive
        .Define("r_e_calculated", "cluster_ENG_CALIB_TOT != 0 ? clusterE / cluster_ENG_CALIB_TOT : -999")
        .Define("diffEta", "clusterEta - jetCalEta")
        .Define("labels", "(cluster_ENG_CALIB_TOT > 0.3) && (r_e_calculated > 0.2) && (r_e_calculated < 4) ? 1 : 0")
        .Define("zVars", computeZ, {"clusterPt", "clusterEta", "clusterPhi", "jetRawPt", "jetRawEta", "jetRawPhi"})
        .Define("zT", "std::get<0>(zVars)")
        .Define("zL", "std::get<1>(zVars)")
        .Define("zRel", "std::get<2>(zVars)")

        // .Define("zT",   "TVector3 c; c.SetPtEtaPhi(clusterPt, clusterEta, clusterPhi); "
        //                 "TVector3 j; j.SetPtEtaPhi(jetRawPt, jetRawEta, jetRawPhi); "
        //                 "return c.Pt() / j.Pt();")
        // .Define("zL",   "TVector3 c; c.SetPtEtaPhi(clusterPt, clusterEta, clusterPhi); "
        //                 "TVector3 j; j.SetPtEtaPhi(jetRawPt, jetRawEta, jetRawPhi); "
        //                 "return c.Dot(j) / j.Mag2();")
        // .Define("zRel", "TVector3 c; c.SetPtEtaPhi(clusterPt, clusterEta, clusterPhi); "
        //                 "TVector3 j; j.SetPtEtaPhi(jetRawPt, jetRawEta, jetRawPhi); "
        //                 "return c.Cross(j).Mag() / j.Mag2();")

        ;




    ROOT::RDF::RSnapshotOptions opts;
    opts.fMode = "RECREATE";

    std::vector<std::string> const columns_calib =
        {"r_e_calculated", "eventNumber", "jetCnt",
        "clusterE", "clusterEta", "cluster_SIGNIFICANCE", "cluster_time",
        "cluster_SECOND_TIME", "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG", "cluster_ENG_FRAC_EM_INCL",
        "cluster_FIRST_ENG_DENS", "cluster_LONGITUDINAL", "cluster_LATERAL", "cluster_PTD",
        "cluster_ISOLATION", "nPrimVtx", "avgMu"
        };
    std::vector<std::string> const columns_pu =
        {"labels", "eventNumber", "jetCnt",
        "clusterE", "clusterEta", "clusterPhi",
        "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG", "cluster_ENG_FRAC_EM_INCL",
        "cluster_FIRST_ENG_DENS", "cluster_LATERAL", "cluster_LONGITUDINAL",
        "cluster_PTD", "cluster_time", "cluster_ISOLATION",
        "cluster_SECOND_TIME", "cluster_SIGNIFICANCE", "cluster_nCells",
        "zT", "zL", "zRel", "diffEta", "jetRawE", "nPrimVtx", "avgMu"
        };

    auto columns_calib_all = df_calibration.GetColumnNames();
    auto columns_pu_all    = df_pu.GetColumnNames();


    const Long64_t chunkSize = 500000;
    Long64_t nEntries_calib = *df_calibration.Count();
    Long64_t nEntries_pu    = *df_pu.Count();
    std::cout << "Total entries (calib) = " << nEntries_calib << std::endl;
    std::cout << "Total entries (pu) = " << nEntries_pu << std::endl;


    // for (Long64_t start = 0; start < nEntries_calib; start += chunkSize) {
    //   // Long64_t len = chunkSize;
    //   // if (start + len > nEntries_calib) { len = nEntries_calib - start; }
    //   Long64_t end = start + chunkSize;
    //   if (end > nEntries_calib) end = nEntries_calib;

    //   std::cout << "Calibration: Saving entries " << start << " → " << end << std::endl;

    //   // Select range
    //   // auto df_chunk = df_calibration.Range(start, len);
    //   auto df_chunk = df_calibration.Range(start, end);
    //   // Output filename
    //   TString outname = Form("chunk_%lld", start / chunkSize);

    //   // Snapshot
    //   df_chunk.Snapshot(
    //     "ClusterTree",
    //     out_dir_name + "/MC20" + Campaign + "_JZ" + JZNumber + "_calibration_snapshot_" + outname +".root",
    //     columns_calib,
    //     opts
    //   );
    // }

    // for (Long64_t start = 0; start < nEntries_pu; start += chunkSize) {
    //   // Long64_t len = chunkSize;
    //   // if (start + len > nEntries_pu) { len = nEntries_pu - start; }

    //   Long64_t end = start + chunkSize;
    //   if (end > nEntries_pu) end = nEntries_pu;

    //   std::cout << "PUTagging: Saving entries " << start << " → " << end << std::endl;

    //   // Select range
    //   // auto df_chunk = df_pu.Range(start, len);
    //   auto df_chunk = df_pu.Range(start, end);

    //   // Output filename
    //   TString outname = Form("chunk_%lld", start / chunkSize);

    //   // Snapshot
    //   df_chunk.Snapshot(
    //     "ClusterTree",
    //     out_dir_name + "/MC20" + Campaign + "_JZ" + JZNumber + "_putagging_snapshot_" + outname +".root",
    //     columns_pu,
    //     opts
    //   );
    // }

    df_calibration.Snapshot(
        "ClusterTree",
        out_dir_name + "/MC20" + Campaign + "_JZ" + JZNumber + "_calibration_snapshot.root",
        columns_calib_all,
        opts
      );

    df_pu.Snapshot(
        "ClusterTree",
        out_dir_name + "/MC20" + Campaign + "_JZ" + JZNumber + "_putagging_snapshot.root",
        columns_pu_all,
        opts
      );
    




    return 0;


}
