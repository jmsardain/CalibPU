#!/bin/bash

# setupATLAS
# lsetup "root 6.36.02-x86_64-el9-gcc14-opt"
COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)
echo $COMPILER $FLAGS

$COMPILER $FLAGS -I/cvmfs/sft.cern.ch/lcg/releases/LCG_107a_ATLAS_2/vdt/0.4.4/x86_64-el9-gcc13-opt/include -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./slimROOT.cc -Iinclude -o slimROOT
#$COMPILER $FLAGS -I/cvmfs/sft.cern.ch/lcg/releases/LCG_107a_ATLAS_2/vdt/0.4.4/x86_64-el9-gcc13-opt/include -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./makeJetTree.cc -Iinclude -o makeJetTree

# g++ makeJetTree.cc `root-config --cflags --libs` -O2 -o makeJetTree
# ./makeJetTree clusters.root jets.root
