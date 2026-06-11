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


Xfinal_out_only = np.load('/data/dsmith/trainings/total_predictions_only.npy')

infile   = "/data/dsmith/data_for_test/user.cdelitzs.45207441._000199.mltree_cluster_calo.root"
outfile  = "/data/dsmith/trainings/final.root"
treename = "ClusterTree"  


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