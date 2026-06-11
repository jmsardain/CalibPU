#!/bin/bash

# setupATLAS
# lsetup "root 6.36.02-x86_64-el9-gcc14-opt"

COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)
echo $COMPILER $FLAGS

$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./data_hist/doDataHist.cc ./data_hist/dataHist.C -I. -o ./run/doDataHist
$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./mc_hist/doMcHist.cc ./mc_hist/mcHist.C -I. -o ./run/doMcHist

$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doDataWeights.cc ./ApplyWeights.C -I. -o ./run/doWeights

./run/doDataHist
./run/doMcHist
./run/doWeights

# g++ Randomize.cc `root-config --cflags --libs` -O2 -o Randomize
