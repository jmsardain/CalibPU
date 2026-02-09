import numpy as np
import pandas as pd
import uproot
import os
import torch
from torch_geometric.data import Data
from torch.utils.data import TensorDataset, DataLoader
import pickle
import networkx as nx
from sklearn.model_selection import train_test_split
import argparse
import uproot
import awkward as ak
import numpy as np


def transform(variable):
    '''
    Derived from train data sample, it should be used to transform train AND test ! 
    '''
    mean, std = 0, 0
    if variable=="clusterE": mean, std =  0.515713 , 1.69164
    if variable=="cluster_CENTER_LAMBDA": mean, std =  5.32953 , 1.14798
    if variable=="cluster_FIRST_ENG_DENS": mean, std =  -14.4064 , 1.43416
    if variable=="cluster_SECOND_TIME": mean, std =  -1.65613 , 7.00348
    if variable=="cluster_SIGNIFICANCE": mean, std =  1.42644 , 1.24784
    if variable=="cluster_CENTER_MAG": mean, std =  7.86581 , 0.360147

    return [mean, std] 



def apply_save_log(x):

    #########
    epsilon = 1e-10
    #########

    minimum = x.min()
    if x.min() <= 0:
        x = x - x.min() + epsilon
    else:
        minimum = 0
        epsilon = 0

    return np.log(x)


def main():

    parser = argparse.ArgumentParser(description='ROOT file to run on')
    parser.add_argument('--step',   dest='step',   type=str, default='', help='train or test')
    args = parser.parse_args()


    feature_branches = [
        'clusterE',   ## 0
        'clusterEta', ## 1
        'cluster_time', ## 2
        'cluster_CENTER_LAMBDA', ## 3
        'cluster_CENTER_MAG', ## 4
        'cluster_ENG_FRAC_EM', ## 5  
        'cluster_FIRST_ENG_DENS', ## 6
        'cluster_LATERAL', ## 7
        'cluster_LONGITUDINAL', ## 8
        'cluster_PTD', ## 9
        'cluster_ISOLATION', ## 10
        'cluster_SECOND_TIME', ## 11
        'cluster_SIGNIFICANCE', ## 12
        'nPrimVtx', ## 13
        'avgMu', ## 14
        'clusterPhi', ## 15
        'diffEta', ## 16
        'zT', 'zL', 'zRel', ## 17,18,19
        'cluster_nCells', ## 20
        # 'jetRawE'
        
    ]  

    label_branch = "labels" 
    tree_name = "JetTree"

    with uproot.open('/data/jmsardain/CalibPU/datasets/pu/JetTree_all_'+args.step+'.root') as f:
        tree = f[tree_name]
        if args.step == "train":
            features = tree.arrays(feature_branches + [label_branch], library="ak")
        if args.step == "test":
            features = tree.arrays(feature_branches + [
                                                        label_branch, 
                                                        "eventNumber", "jetCnt",
                                                        "jetAreaE", "jetAreaPt",
                                                        "jetRawE", "jetRawPt",
                                                        "truthJetE", "truthJetPt",
                                                        "jetCalE", "jetCalPt",
                                                        "cluster_ENG_CALIB_TOT",
                                                        "clusterPt",
                                                     ], 
                                    library="ak")

    nclus = ak.to_numpy(ak.num(features["clusterE"]))

    X_list = []
    for feat in feature_branches:
        X_list.append(ak.to_numpy(ak.flatten(features[feat])))

    X = np.stack(X_list, axis=1)

    if args.step == "test":
        raw_clusterE               = X[:, 0].copy()
        raw_cluster_CENTER_LAMBDA  = X[:, 3].copy()
        raw_cluster_FIRST_ENG_DENS = X[:, 6].copy()
        raw_cluster_SECOND_TIME    = X[:, 11].copy()
        raw_cluster_SIGNIFICANCE   = X[:, 12].copy()
        raw_cluster_CENTER_MAG     = X[:, 4].copy()
        cluster_ENG_CALIB_TOT      = ak.to_numpy(ak.flatten(features["cluster_ENG_CALIB_TOT"]))
        clusterPt                  = ak.to_numpy(ak.flatten(features["clusterPt"]))

    #### Transform 
    ## clusterE
    X[:,0] = (apply_save_log(X[:,0]) - transform("clusterE")[0]) / transform("clusterE")[1]
    ## cluster_CENTER_LAMBDA
    X[:,3] = (apply_save_log(X[:,3]) - transform("cluster_CENTER_LAMBDA")[0]) / transform("cluster_CENTER_LAMBDA")[1]
    ## cluster_FIRST_ENG_DENS
    X[:,6] = (apply_save_log(X[:,6]) - transform("cluster_FIRST_ENG_DENS")[0]) / transform("cluster_FIRST_ENG_DENS")[1]
    ## cluster_SECOND_TIME
    X[:,11] = (apply_save_log(X[:,11]) - transform("cluster_SECOND_TIME")[0]) / transform("cluster_SECOND_TIME")[1]
    ## cluster_SIGNIFICANCE
    X[:,12] = (apply_save_log(X[:,12]) - transform("cluster_SIGNIFICANCE")[0]) / transform("cluster_SIGNIFICANCE")[1]
    ## cluster_CENTER_MAG
    X[:,4] = (apply_save_log(X[:,4]) - transform("cluster_CENTER_MAG")[0]) / transform("cluster_CENTER_MAG")[1]
    y = ak.to_numpy(ak.flatten(features[label_branch]))


    if args.step == "train":
        Xfinal = np.column_stack([y, X])
        np.save("/data/jmsardain/CalibPU/datasets/pu/dataset_"+args.step+".npy", Xfinal)

    if args.step == "test":
        ## add jet-level variables
        eventNumber = np.repeat(ak.to_numpy(features["eventNumber"]), nclus)
        jetCnt      = np.repeat(ak.to_numpy(features["jetCnt"]), nclus)
        jetAreaE    = np.repeat(ak.to_numpy(features["jetAreaE"]), nclus)
        jetAreaPt   = np.repeat(ak.to_numpy(features["jetAreaPt"]), nclus)
        jetRawE     = np.repeat(ak.to_numpy(features["jetRawE"]), nclus)
        jetRawPt    = np.repeat(ak.to_numpy(features["jetRawPt"]), nclus)
        truthJetE   = np.repeat(ak.to_numpy(features["truthJetE"]), nclus)
        truthJetPt  = np.repeat(ak.to_numpy(features["truthJetPt"]), nclus)
        jetCalE     = np.repeat(ak.to_numpy(features["jetCalE"]), nclus)
        jetCalPt    = np.repeat(ak.to_numpy(features["jetCalPt"]), nclus)
        ## add cluster level variables 

        Xfinal = np.column_stack([
                                 eventNumber, jetCnt, 
                                 jetAreaE, jetAreaPt, 
                                 jetRawE, jetRawPt, truthJetE, truthJetPt, jetCalE, jetCalPt, 
                                 cluster_ENG_CALIB_TOT,
                                 raw_clusterE, raw_cluster_CENTER_LAMBDA, raw_cluster_FIRST_ENG_DENS, raw_cluster_SECOND_TIME, raw_cluster_SIGNIFICANCE, raw_cluster_CENTER_MAG,
                                 clusterPt,
                                 y, X
                                 ])
        np.save("/data/jmsardain/CalibPU/datasets/pu/dataset_"+args.step+".npy", Xfinal)

    return



# Main function call.
if __name__ == '__main__':
    main()
    pass
