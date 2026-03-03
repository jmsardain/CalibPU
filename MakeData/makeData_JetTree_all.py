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


def transform_calib(variable):
    '''
    Taken from Isabel's code: https://gitlab.cern.ch/issainzs/nn-topocluster-calibration/-/blob/master/dnn-hgm/configs/config_hgm_mc20.yaml?ref_type=heads
    '''
    mean, std = 0, 0
    if variable=="clusterE":                 mean, std =  0.6347346839702431 , 0.7385571482973289
    if variable=="clusterEta":               mean, std =  0.010181442396798685, 1.0730789413750401
    if variable=="cluster_SIGNIFICANCE":     mean, std =  0.8866835528437869, 0.5548024471260036
    if variable=="cluster_time":             mean, std =  256.52423095703125, 0
    if variable=="cluster_SECOND_TIME":      mean, std =  -0.8385087991536135, 3.5133484230525402 
    if variable=="cluster_CENTER_LAMBDA":    mean, std =  2.454458464238727, 0.455548085569537
    if variable=="cluster_CENTER_MAG":       mean, std =  2901.331867871424, 1056.6397559178897
    if variable=="cluster_ENG_FRAC_EM_INCL": mean, std =  -2882.9208984375, 15179.9755859375
    if variable=="cluster_FIRST_ENG_DENS":   mean, std =  -6.154656057568099, 0.6910824492265635
    if variable=="cluster_LONGITUDINAL":     mean, std =  0.7223626116469644, 0.20625686889852246
    if variable=="cluster_LATERAL":          mean, std =  0.7833833900325896, 0.18259941395116977
    if variable=="cluster_PTD":              mean, std =  0.34957693080870894, 0.14286381130028875
    if variable=="cluster_ISOLATION":        mean, std =  0.6027900102955646, 0.2512761803141686
    if variable=="nPrimVtx":                 mean, std =  20.90668211764706, 7.262609335567245
    if variable=="avgMu":                    mean, std =  34.505480862450824, 12.350157368609814
    return [mean, std] 

def transform_pu(variable):
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

    parser = argparse.ArgumentParser(description='Make data from ROOT files')
    parser.add_argument('--step',   dest='step',   type=str, default='', help='train or test')
    parser.add_argument('--train',    dest='train',    action='store_const', const=True, default=False, help='Train dataset  (default: False)')
    parser.add_argument('--test',     dest='test',     action='store_const', const=True, default=False, help='Test dataset   (default: False)')

    args = parser.parse_args()




    feature_branches_calib = [
        'clusterE',  ## 0 
        'clusterEta', ## 1
        'cluster_SIGNIFICANCE', ## 2
        'cluster_time', ## 3
        'cluster_SECOND_TIME', ## 4
        'cluster_CENTER_LAMBDA', ## 5
        'cluster_CENTER_MAG', ## 6
        'cluster_ENG_FRAC_EM_INCL', ## 7
        'cluster_FIRST_ENG_DENS', ## 8
        'cluster_LONGITUDINAL', ## 9
        'cluster_LATERAL', ## 10
        'cluster_PTD', ## 11
        'cluster_ISOLATION', ## 12 
        'nPrimVtx', ## 13
        'avgMu', ## 14
    ]


    feature_branches_pu = [
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

    label_branch_calib = "r_e_calculated" 
    label_branch_pu = "labels"

    if args.step == "calib":
        label_branch = label_branch_calib
        feature_branches = feature_branches_calib
    if args.step == "pu":
        label_branch = label_branch_pu
        feature_branches = feature_branches_pu

    tree_name = "JetTree"
    path_to_file = ''
    if args.train: path_to_file = '/data/jmsardain/CalibPU/datasets/pu/JetTree_all_train.root'
    if args.test: path_to_file = '/data/jmsardain/CalibPU/datasets/pu/JetTree_all_test.root'
    
    with uproot.open(path_to_file) as f:
        tree = f[tree_name]
        if args.train:
            features = tree.arrays(feature_branches + [label_branch], library="ak")
        if args.test:
            features = tree.arrays(feature_branches + [label_branch, 
                                                        "eventNumber", "jetCnt",
                                                     ], 
                                    library="ak")

    nclus = ak.to_numpy(ak.num(features["clusterE"]))

    X_list = []
    for feat in feature_branches:
        X_list.append(ak.to_numpy(ak.flatten(features[feat])))

    if args.step == "calib":
        if args.train:
            mask = (features["clusterE"] >= 0.3) & (features["r_e_calculated"] > 0) # & (features["r_e_calculated"] != -999)

            masked_clusterE = features["clusterE"][mask]
            nclus           = ak.to_numpy(ak.num(masked_clusterE))

            X = np.stack([
                     ak.to_numpy(ak.flatten(features[feat][mask])) for feat in feature_branches
                     ], axis=1)
        
            y = ak.to_numpy(ak.flatten(features[label_branch][mask]))
        
        if args.test: ## If i am doing test, i do not want to mask anything, i want all clusters. 
            masked_clusterE = features["clusterE"]
            nclus           = ak.to_numpy(ak.num(masked_clusterE))

            X = np.stack([ 
                            ak.to_numpy(ak.flatten(features[feat])) for feat in feature_branches
                         ], axis=1)
        
            y = ak.to_numpy(ak.flatten(features[label_branch]))

    if args.step == "pu":
        X = np.stack(X_list, axis=1)
    

    #### Transform
    if args.step == "calib":
        ## clusterE, LogTenStandard
        X[:,0] = (apply_save_log(X[:,0]) - transform_calib("clusterE")[0]) / transform_calib("clusterE")[1]
        ## clusterEta, Standard
        X[:,1] = (X[:,1] - transform_calib("clusterEta")[0]) / transform_calib("clusterEta")[1]
        ## cluster_SIGNIFICANCE, LogTenStandard
        X[:,2] = (apply_save_log(X[:,2]) - transform_calib("cluster_SIGNIFICANCE")[0]) / transform_calib("cluster_SIGNIFICANCE")[1]
        ## cluster_time, MaxAbsolute is just x = x / max(x) and max(x) is stored
        X[:,3] = (X[:,3] / transform_calib("cluster_time")[0])
        ## cluster_SECOND_TIME, LogTenStandard
        X[:,4] = (apply_save_log(X[:,4]) - transform_calib("cluster_SECOND_TIME")[0]) / transform_calib("cluster_SECOND_TIME")[1]
        ## cluster_CENTER_LAMBDA, LogTenStandard
        X[:,5] = (apply_save_log(X[:,5]) - transform_calib("cluster_CENTER_LAMBDA")[0]) / transform_calib("cluster_CENTER_LAMBDA")[1]
        ## cluster_CENTER_MAG, Standard
        X[:,6] = (X[:,6] - transform_calib("cluster_CENTER_MAG")[0]) / transform_calib("cluster_CENTER_MAG")[1]
        ## cluster_ENG_FRAC_EM_INCL, MinMaxNorm
        X[:,7] = (X[:,7] -  transform_calib("cluster_ENG_FRAC_EM_INCL")[0]) / (X[:,7] - transform_calib("cluster_ENG_FRAC_EM_INCL")[1])
        ## cluster_FIRST_ENG_DENS, LogTenStandard
        X[:,8] = (apply_save_log(X[:,8]) - transform_calib("cluster_FIRST_ENG_DENS")[0]) / transform_calib("cluster_FIRST_ENG_DENS")[1]
        ## cluster_LONGITUDINAL, Standard
        X[:,9] = (X[:,9] - transform_calib("cluster_LONGITUDINAL")[0]) / transform_calib("cluster_LONGITUDINAL")[1]
        ## cluster_LATERAL, Standard
        X[:,10] = (X[:,10] - transform_calib("cluster_LATERAL")[0]) / transform_calib("cluster_LATERAL")[1]
        ## cluster_PTD, Standard
        X[:,11] = (X[:,11] - transform_calib("cluster_PTD")[0]) / transform_calib("cluster_PTD")[1]
        ## cluster_ISOLATION, Standard
        X[:,12] = (X[:,12] - transform_calib("cluster_ISOLATION")[0]) / transform_calib("cluster_ISOLATION")[1]
        ## nPrimVtx, Standard
        X[:,13] = (X[:,13] - transform_calib("nPrimVtx")[0]) / transform_calib("nPrimVtx")[1]
        ## avgMu, Standard
        X[:,14] = (X[:,14] - transform_calib("avgMu")[0]) / transform_calib("avgMu")[1]

        ## Reponse should be logged 
        y = apply_save_log(y)

    if args.step == "pu": 
        ## clusterE
        X[:,0] = (apply_save_log(X[:,0]) - transform_pu("clusterE")[0]) / transform_pu("clusterE")[1]
        ## cluster_CENTER_LAMBDA
        X[:,3] = (apply_save_log(X[:,3]) - transform_pu("cluster_CENTER_LAMBDA")[0]) / transform_pu("cluster_CENTER_LAMBDA")[1]
        ## cluster_FIRST_ENG_DENS
        X[:,6] = (apply_save_log(X[:,6]) - transform_pu("cluster_FIRST_ENG_DENS")[0]) / transform_pu("cluster_FIRST_ENG_DENS")[1]
        ## cluster_SECOND_TIME
        X[:,11] = (apply_save_log(X[:,11]) - transform_pu("cluster_SECOND_TIME")[0]) / transform_pu("cluster_SECOND_TIME")[1]
        ## cluster_SIGNIFICANCE
        X[:,12] = (apply_save_log(X[:,12]) - transform_pu("cluster_SIGNIFICANCE")[0]) / transform_pu("cluster_SIGNIFICANCE")[1]
        ## cluster_CENTER_MAG
        X[:,4] = (apply_save_log(X[:,4]) - transform_pu("cluster_CENTER_MAG")[0]) / transform_pu("cluster_CENTER_MAG")[1]
        y = ak.to_numpy(ak.flatten(features[label_branch]))


    if args.train:
        Xfinal = np.column_stack([y, X])
        np.save("/data/jmsardain/CalibPU/datasets/pu/dataset_"+args.step+"_train.npy", Xfinal)

    if args.test:
        ## add jet-level variables
        eventNumber = np.repeat(ak.to_numpy(features["eventNumber"]), nclus)
        jetCnt      = np.repeat(ak.to_numpy(features["jetCnt"]), nclus)
        
        ## add cluster level variables 

        Xfinal = np.column_stack([
                                 eventNumber, jetCnt, 
                                 y, X
                                 ])
        np.save("/data/jmsardain/CalibPU/datasets/pu/dataset_"+args.step+"_test.npy", Xfinal)

    return



# Main function call.
if __name__ == '__main__':
    main()
    pass
