#!/bin/bash

# setupATLAS
# lsetup "root 6.32.02-x86_64-el9-gcc13-opt"

COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)
echo $COMPILER $FLAGS

$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doFinal.cc ./DoPlot.C -I. -o doFinal

## To run the codem and assuming there's no error:
## mkdir newplots/
## ./doFinal
