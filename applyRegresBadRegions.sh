#!/bin/bash

# Specify whether you want to apply electron or photon regression as an argument
# Ele for electrons and Pho for photons

reg_type=$1

pt_range=(
	15to30
	30to50
	50to80
	80to120
	120to170
	170to300
	300to470
	470to600
	600to800
	800to1000
	1000to1400
	1400to1800
	1800to2400
	2400to3200
	3200toInf
)
base_location="/home/hep/wrtabb/Egamma/results/2016AllExt/"
for index in ${!pt_range[*]}; do
	input_tree="/home/hep/wrtabb/input_trees/2016ULQCD/QCD_${pt_range[$index]}.root"
	output_tree="appliedResults/QCD_${reg_type}/QCD_2016UL_${pt_range[$index]}.root"
	script_type="scripts/apply${reg_type}Regression.py"
	ideal_location="${base_location}reg${reg_type}Ecal2016UL_IdealIC_IdealTraining_stdVar_stdCuts_{region}_ntrees1500_results.root"
	real_location="${base_location}reg${reg_type}Ecal2016UL_RealIC_RealTraining_stdVar_stdCuts_{region}_ntrees1500_results.root"
	ecaltrk_location="${base_location}reg${reg_type}EcalTrk2016UL_RealIC_stdVar_stdCuts_{region}_ntrees1500_results.root"

	if [ $reg_type = Ele ]
	then
		python $script_type --ideal $ideal_location --real $real_location --ecaltrk $ecaltrk_location $input_tree $output_tree
	else
		python $script_type --ideal $ideal_location --real $real_location $input_tree $output_tree
	fi
done
