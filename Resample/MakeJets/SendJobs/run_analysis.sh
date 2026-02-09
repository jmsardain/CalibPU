#!/bin/bash
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
export ALRB_localConfigDir=$HOME/localConfig
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

lsetup "root 6.36.02-x86_64-el9-gcc14-opt"

cd /home/jmsardain/CalibPU/Resample/MakeJets
./doAnal all 