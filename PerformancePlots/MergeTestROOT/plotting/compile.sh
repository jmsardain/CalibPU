#!/bin/bash
# setupATLAS
# lsetup "root 6.32.02-x86_64-el9-gcc13-opt"

COMPILER=$(root-config --cxx)
FLAGS=$(root-config --cflags --libs)
echo $COMPILER $FLAGS

$COMPILER $FLAGS -g -O3 -Wall -Wextra -Wpedantic -fopenmp ./doPlot.cc ./AtlasStyle.C ./AtlasUtils.C ./AtlasLabels.C -I. -o doPlot
