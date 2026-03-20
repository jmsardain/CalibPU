#!/bin/bash

# setupATLAS
# lsetup "root 6.36.02-x86_64-el9-gcc14-opt"

COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)
echo $COMPILER $FLAGS

$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doDataPlots.cc ./dataCompare.C -I. -o doDataPlots
$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doMCPlots.cc ./mcCompare.C -I. -o doMCPlots

#./doMCPlots "/data/dsmith/mc_for_test/MC20d_JZ*.root"
#./doDataPlots "/data/dsmith/data_for_test/user.cdelitzs.45207441._000199.mltree_cluster_calo.root"

# g++ Randomize.cc `root-config --cflags --libs` -O2 -o Randomize
