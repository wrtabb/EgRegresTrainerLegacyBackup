#!/bin/bash

# SampleTL150 + ThrTL150 + Regr_STL150_ThrTL150 vs  SampleTL150 + ThrMixed + Regr_STL150_ThrMixed
# SampleTL180 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL180 + ThrMixed + Regr_STL150_ThrMixed ( I am adding this one today since the ntuples are existing)
# SampleTL150 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL150 + ThrTL150 + Regr_STL150_ThrTL150
# SampleTL235 + ThrTL180 + Regr_STL180_ThrTL180 vs  SampleTL235 + ThrTL235 + Regr_STL235_ThrTL235


# Script to use to do the application
applier="scripts/applySCRegression.py"
# Location of root file to apply regression to
input_location="/home/hep/wrtabb/Egamma/input_trees/ThreshForECAL/TL150/"
# root file to apply regression to
input_tree="${input_location}DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"
# Location of regression results
result_location="/home/hep/wrtabb/Egamma/results/ThreshForECAL/"
# Save file after regression is applied
output_tree=${result_location}"scReg_TL150_ThrTL180_RegTL180TL180.root"
# root file containing regression to apply to input_tree
regression_to_apply="${result_location}scRegTL180_IdealIC_IdealTraining_stdVar_stdCuts_{region}_ntrees1500_results.root"

python $applier --ideal $regression_to_apply $input_tree $output_tree


# Output naming conventions
# scReg_luminositySample_thresholdConditions_regressionApplied
