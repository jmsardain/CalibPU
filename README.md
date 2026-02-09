# Calibration + PU Tagging framework 

Overview of the code for calibration and pu tagging: [ANA-JETM-2026-01](https://atlas-glance.cern.ch/atlas/analysis/analyses/details?ref_code=ANA-JETM-2026-01)

1. RDataFrame run to add response and labels and other variables needed 
2. Make jets from ClusterTree, i.e. jet per entry, vector of cluster variables.
3. Randomize jets and split into train/test 
4. Run ROOT macro to get the transformations needed, and save them to a file 
5. Using uproot and awkward arrays, get clusters from JetTree 
6. Run training and testing
7. Append results to test ROOT file, add response, uncertainty, labels, scores, to the JetTree test
