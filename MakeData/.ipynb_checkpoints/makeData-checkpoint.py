import numpy as np
import pandas as pd
import argparse
import ROOT

def main():

    parser = argparse.ArgumentParser(description='Make data for CalibPU studies')
    parser.add_argument('--step',   dest='step',   type=str, default='', help='calib or pu')
    args = parser.parse_args()
    columns = []
    name_root_file = ''
    if args.step == 'calib':
        columns = ["r_e_calculated", "eventNumber", "jetCnt",
                    "clusterE", "clusterEta", "cluster_SIGNIFICANCE", "cluster_time",
                    "cluster_SECOND_TIME", "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG", "cluster_ENG_FRAC_EM_INCL",
                    "cluster_FIRST_ENG_DENS", "cluster_LONGITUDINAL", "cluster_LATERAL", "cluster_PTD",
                    "cluster_ISOLATION", "nPrimVtx", "avgMu"
                  ]
        name_root_file = 'mc20_isa_calibration_snapshot'
    elif args.step == 'pu':
        columns = ["labels", "eventNumber", "jetCnt",
                    "clusterE", "clusterEta", "cluster_time",
                    "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG", "cluster_ENG_FRAC_EM_INCL",
                    "cluster_FIRST_ENG_DENS", "cluster_LATERAL", "cluster_LONGITUDINAL",
                    "cluster_PTD", "cluster_ISOLATION", "cluster_SECOND_TIME", "cluster_SIGNIFICANCE",
                    "nPrimVtx", "avgMu",
                    "clusterPhi", "diffEta",
                    "zT", "zL", "zRel",
                    "cluster_nCells", "jetRawE",
                  ]
        name_root_file = 'mc20_isa_putagging_snapshot'

    else:
        print('Choose calib or pu')
        return


    df = ROOT.RDataFrame("ClusterTree", "/data/jmsardain/CalibPU/"+name_root_file+".root")
    n = df.Count().GetValue()
    batch_size = 500000


    val_limit   = int(0.8 * n)

    train_idx = val_idx = test_idx = 0
    counter = 0


    for batch_start in range(0, n, batch_size):

        batch_end = min(batch_start + batch_size, n)

        crosses_val   = (batch_start < val_limit < batch_end)

        if crosses_val:
            print(f"Skipping rows from {batch_start} to {batch_end} (boundary crossing)")
            continue


        batch_df = df.Range(batch_start, batch_end)
        batch_np_dict = batch_df.AsNumpy(columns=columns)

        arr = np.vstack([batch_np_dict[c] for c in columns]).T

        if batch_end < val_limit:
            np.save(f"/data/jmsardain/CalibPU/datasets/{args.step}/train_{args.step}_batch_{train_idx}.npy", arr)
            train_idx += 1

        elif batch_start >= val_limit:
            np.save(f"/data/jmsardain/CalibPU/datasets/{args.step}/test_{args.step}_batch_{test_idx}.npy", arr)
            test_idx += 1

        print(f"Saved rows from {batch_start} to {batch_end}")
        counter += 1

    print(f"Counter {counter}")



    return


if __name__ == "__main__":
    main()
    pass
