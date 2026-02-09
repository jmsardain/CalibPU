#!/bin/bash

# setupATLAS
# lsetup "root 6.36.02-x86_64-el9-gcc14-opt"

COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)
echo $COMPILER $FLAGS

$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doJets.cc ./MakeJets.C -I. -o doJets
$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doRandom.cc ./Randomize.C -I. -o doRandom

# g++ Randomize.cc `root-config --cflags --libs` -O2 -o Randomize
