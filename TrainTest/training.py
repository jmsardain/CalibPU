import math
import numpy as np
import pandas as pd
import uproot as ur
import datetime, os
from collections import defaultdict

from sklearn.preprocessing import  QuantileTransformer, StandardScaler
from sklearn.utils import class_weight
import argparse

from sklearn.model_selection import train_test_split
from sklearn import ensemble
import matplotlib.pyplot as plt
import uproot
import torch
from torch.utils.data import DataLoader, TensorDataset
from utils import *

parser = argparse.ArgumentParser(description='Perform signal injection test.')
parser.add_argument('--train',    dest='train',    action='store_const', const=True, default=False, help='Train NN  (default: False)')
parser.add_argument('--test',     dest='test',     action='store_const', const=True, default=False, help='Test NN   (default: False)')
parser.add_argument('--merge',    dest='merge',    action='store_const', const=True, default=False, help='Append label and predictions to ROOT test file    (default: False)')
parser.add_argument('--ckpt',     dest='ckpt',     type=str, default='', help='ckpts to use')
parser.add_argument('--outdir',   dest='outdir',   type=str, default='', help='Directory with output is stored')

args = parser.parse_args()
# def build_and_compile_model(X_train, lr):
#     model = keras.Sequential([layers.Flatten(input_shape=(X_train.shape[1],)),
#                                              layers.Dense(256, activation="relu"),
#                                              layers.Dense(128, activation="relu"),
#                                              layers.Dense(64,  activation="relu"),
#                                              layers.Dense(64,   activation="relu"),
#                                              layers.Dense(1,   activation='sigmoid')])
#     model.compile(loss="binary_crossentropy", optimizer=tf.keras.optimizers.Adam(learning_rate=lr), weighted_metrics=[])
#     return model



def main():

    dir_path = args.outdir
    try:
        os.system("mkdir {}".format(dir_path))
    except ImportError:
        print("{} already exists".format(dir_path))
    pass

    path_to_train = '/data/jmsardain/CalibPU/datasets/pu/dataset_train.npy'
    path_to_test  = '/data/jmsardain/CalibPU/datasets/pu/dataset_test.npy'
    
    # features_train = '/data/jmsardain/CalibPU/datasets/pu/features_train.npy'
    # features_test  = '/data/jmsardain/CalibPU/datasets/pu/features_test.npy'
    
    # labels_train = '/data/jmsardain/CalibPU/datasets/pu/labels_train.npy'
    # labels_test  = '/data/jmsardain/CalibPU/datasets/pu/labels_test.npy'

    if args.train: 

        dataset_train = np.load(path_to_train)
        n = len(dataset_train)
        ntrain = int(n * 0.8)

        train_data = dataset_train[:ntrain]
        val_data = dataset_train[ntrain:]

        x_train = train_data[:, 1:]
        y_train = train_data[:, 0]
        # val dataset
        x_val = val_data[:, 1:]
        y_val = val_data[:, 0]

        data_train = np.concatenate([x_train, y_train[:, None]], axis=-1)
        print(f"Training dataset size {y_train.shape[0]}")

        data_val = np.concatenate([x_val, y_val[:, None]], axis=-1)
        print(f"Validation dataset size {y_val.shape[0]}")
        
        ## Get DataLoaders
        train_dataset = TensorDataset(torch.tensor(x_train, dtype=torch.float32), torch.tensor(y_train, dtype=torch.float32))
        train_loader = DataLoader(train_dataset, batch_size=2048, shuffle=True)

        val_dataset = TensorDataset(torch.tensor(x_val, dtype=torch.float32), torch.tensor(y_val, dtype=torch.float32))
        val_loader = DataLoader(val_dataset, batch_size=2048, shuffle=False)


        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        model = PUMitigationModel(x_train.shape[1])
        optimizer = torch.optim.Adam(model.parameters(), lr=0.0001)

        print('Start training')
        train_loss = []
        val_loss   = []

        model.to(device)

        for epoch in range(100):
            print("Epoch:{}".format(epoch+1))
            train_loss.append(train(train_loader, model, device, optimizer))
            val_loss.append(validate(val_loader, model, device))
            print('Epoch: {:03d}, Train Loss: {:.5f}, Val Loss: {:.5f},'.format(epoch, train_loss[epoch], val_loss[epoch]))
            torch.save(model.state_dict(), dir_path+"/DNN_e{:03d}".format(epoch+1) + "_losstrain{:.3f}".format(train_loss[epoch]) + "_lossval{:.3f}".format(val_loss[epoch]) + ".pt")


        metrics = pd.DataFrame({"Train_Loss":train_loss,"Val_Loss":val_loss})
        metrics.to_csv(dir_path+"/metrics.csv", index = False)

        return

    if args.test:
        
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
        dataset_test = np.load(path_to_test)
        x_test = dataset_test[:, 19:]
        y_test = dataset_test[:, 18]
        data_test = np.concatenate([x_test, y_test[:, None]], axis=-1)
        print(f"Test dataset size {y_test.shape[0]}")

        ## Get DataLoaders
        test_dataset = TensorDataset(torch.tensor(x_test, dtype=torch.float32), torch.tensor(y_test, dtype=torch.float32))
        test_loader = DataLoader(test_dataset, batch_size=1024, shuffle=False, pin_memory=True)

        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        model = PUMitigationModel(x_test.shape[1])
        print('I am here 1')
        path_to_ckpt = args.ckpt
        model.load_state_dict(torch.load(path_to_ckpt))
        print('I am here 2')
        # df = test(test_loader, model, device, dir_path)
        labels_test, nodes_out = test(test_loader, model, device, dir_path)

        eventNumber                = dataset_test[:, 0]
        jetCnt                     = dataset_test[:, 1]
        jetAreaE                   = dataset_test[:, 2]
        jetAreaPt                  = dataset_test[:, 3]
        jetRawE                    = dataset_test[:, 4]
        jetRawPt                   = dataset_test[:, 5]
        truthJetE                  = dataset_test[:, 6]
        truthJetPt                 = dataset_test[:, 7]
        jetCalE                    = dataset_test[:, 8]
        jetCalPt                   = dataset_test[:, 9]
        cluster_ENG_CALIB_TOT      = dataset_test[:, 10]
        raw_clusterE               = dataset_test[:, 11]
        raw_cluster_CENTER_LAMBDA  = dataset_test[:, 12]
        raw_cluster_FIRST_ENG_DENS = dataset_test[:, 13]
        raw_cluster_SECOND_TIME    = dataset_test[:, 14]
        raw_cluster_SIGNIFICANCE   = dataset_test[:, 15]
        raw_cluster_CENTER_MAG     = dataset_test[:, 16]
        clusterPt                  = dataset_test[:, 17]

        # Xfinal = np.column_stack([
        #                         eventNumber, jetCnt,
        #                         jetAreaE, jetAreaPt, 
        #                         jetRawE, jetRawPt, truthJetE, truthJetPt, jetCalE, jetCalPt, 
        #                         cluster_ENG_CALIB_TOT,
        #                         raw_clusterE, raw_cluster_CENTER_LAMBDA, raw_cluster_FIRST_ENG_DENS, raw_cluster_SECOND_TIME, raw_cluster_SIGNIFICANCE, raw_cluster_CENTER_MAG,
        #                         clusterPt,
        #                         labels_test, nodes_out, 
        #                         x_test
        #                         ])
        
        # np.save(dir_path+'/total_predictions.npy', Xfinal)

        Xfinal_out_only = np.column_stack([
                                eventNumber, jetCnt,
                                labels_test, nodes_out,
                                ])

        np.save(dir_path+'/total_predictions_only.npy', Xfinal_out_only)
        branches = { 
            "eventNumber":                  Xfinal_out_only[:, 0].astype(np.int64),
            "jetCnt":                       Xfinal_out_only[:, 1].astype(np.int32),
            "label":                        Xfinal_out_only[:, 2].astype(np.float32),
            "prediction":                   Xfinal_out_only[:, 3].astype(np.float32),
        }
        root_path = dir_path + "/total_predictions_only.root"
        with uproot.recreate(root_path) as f:
            f["JetTree"] = branches

        print("Saved ROOT file to:", root_path)

    if args.merge: 
        
        # Xfinal_out_only = np.load(dir_path+'/total_predictions_only.npy')
        Xfinal_out_only = np.load(dir_path+'/total_predictions_only.npy')

        infile   = "/data/jmsardain/CalibPU/datasets/pu/JetTree_all_test.root"
        outfile  = dir_path+"/final.root"
        treename = "JetTree"  


        eventNumber_out  = Xfinal_out_only[:, 0].astype(np.int64)
        jetCnt_out       = Xfinal_out_only[:, 1].astype(np.int64)
        label        = Xfinal_out_only[:, 2].astype(np.float32)
        predictions  = Xfinal_out_only[:, 3].astype(np.float32)

        print(f" NClusters : {len(eventNumber_out)}")

        jet_map_label = defaultdict(list)
        jet_map_pred  = defaultdict(list)

        print("I am here 1")
        for e, j, l, p in zip(eventNumber_out, jetCnt_out, label, predictions):
            jet_map_label[(e,j)].append(l)
            jet_map_pred[(e,j)].append(p)
        
        print("I am here 2")
        for k in jet_map_label:
            jet_map_label[k] = np.array(jet_map_label[k], dtype=np.float32)
            jet_map_pred[k]  = np.array(jet_map_pred[k], dtype=np.float32)
        
        print("I am here 3")
        with uproot.open(infile) as f:
            tree = f[treename]
            arrays = tree.arrays(library="np") 

        eventNumber = arrays["eventNumber"]
        jetCnt      = arrays["jetCnt"]

        labels_branch = np.empty(len(eventNumber), dtype=object)
        nodes_branch  = np.empty(len(eventNumber), dtype=object)

        print("I am here 4")
        for i, (e,j) in enumerate(zip(eventNumber, jetCnt)):
            key = (int(e), int(j))
            labels_branch[i] = jet_map_label[key]
            nodes_branch[i]  = jet_map_pred[key]

        arrays["labels_test"] = labels_branch
        arrays["nodes_out"]   = nodes_branch

        print("I am here 5")
        with uproot.recreate(outfile) as f:
            f[treename] = arrays

        return 


# Main function call.
if __name__ == '__main__':
    main()
    pass

