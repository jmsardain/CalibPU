import numpy as np
import pandas as pd
import argparse
import ROOT



def main():

    parser = argparse.ArgumentParser(description='Make data for CalibPU studies (jet-safe)')
    parser.add_argument('--step', dest='step', type=str, required=True, help='calib or pu')
    parser.add_argument('--batch-size', dest='batch_size', type=int, default=500000,
                        help='Approximate number of clusters per batch (jets kept intact)')
    parser.add_argument('--seed', dest='seed', type=int, default=42, help='Shuffle seed (used once)')
    args = parser.parse_args()


    if args.step == 'calib':
        columns = [
            "r_e_calculated", "eventNumber", "jetCnt",
            "clusterE", "clusterEta", "cluster_SIGNIFICANCE", "cluster_time",
            "cluster_SECOND_TIME", "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG",
            "cluster_ENG_FRAC_EM_INCL", "cluster_FIRST_ENG_DENS",
            "cluster_LONGITUDINAL", "cluster_LATERAL", "cluster_PTD",
            "cluster_ISOLATION", "nPrimVtx", "avgMu",
        ]
        name_root_file = 'mc20_isa_calibration_snapshot'
        label_column = "r_e_calculated"

    elif args.step == 'pu':
        columns = [
            "labels", "eventNumber", "jetCnt",
            "clusterE", "clusterEta", "cluster_time",
            "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG",
            "cluster_ENG_FRAC_EM_INCL", "cluster_FIRST_ENG_DENS",
            "cluster_LATERAL", "cluster_LONGITUDINAL",
            "cluster_PTD", "cluster_ISOLATION",
            "cluster_SECOND_TIME", "cluster_SIGNIFICANCE",
            "nPrimVtx", "avgMu",
            "clusterPhi", "diffEta",
            "zT", "zL", "zRel",
            "cluster_nCells", "jetRawE",
        ]
        name_root_file = 'mc20_isa_putagging_snapshot'
        label_column = "labels"
    else:
        raise RuntimeError('Choose calib or pu')


    rdf = ROOT.RDataFrame("ClusterTree", f"/data/jmsardain/CalibPU/{name_root_file}.root")
    print(rdf.Count().GetValue())
    df = pd.DataFrame(rdf.AsNumpy(columns))


    jet_groups = list(df.groupby(["eventNumber", "jetCnt"], sort=False))

    rng = np.random.default_rng(args.seed)
    rng.shuffle(jet_groups)

    n_jets = len(jet_groups)
    n_train = int(0.8 * n_jets)

    train_jets = jet_groups[:n_train]
    test_jets  = jet_groups[n_train:]

    def build_batches(jets, split_name):
        batches_X = []
        batches_y = []

        current_X = []
        current_y = []
        current_size = 0

        for (_, _), jet_df in jets:

            jet_array = jet_df.to_numpy()
            jet_size = len(jet_array)

            # Flush batch if adding this jet would exceed size
            if current_size + jet_size > args.batch_size and current_size > 0:
                batches.append(np.vstack(current_batch))
                current_batch = []
                current_size = 0

            current_batch.append(jet_array)
            current_size += jet_size

        if current_size > 0:
            batches.append(np.vstack(current_batch))

        for i, batch in enumerate(batches):
            np.save(f"/data/jmsardain/CalibPU/datasets/{args.step}/{split_name}_batch_{i}.npy", batch)

    # ------------------------------------------------------------------
    # Build datasets
    # ------------------------------------------------------------------
    build_batches(train_jets, "train")
    build_batches(test_jets,  "test")


if __name__ == "__main__":
    main()
