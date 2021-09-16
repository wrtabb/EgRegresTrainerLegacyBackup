#!/bin/bash

export PATH=$PATH:./bin/$SCRAM_ARCH
export PYTHON27PATH=$PYTHON27PATH:python
export PYTHONPATH=$PYTHONPATH:python
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$PWD/include

# use argument to specify regression applied from standard variables (Std) or extended (Ext)

reg_type="Ele"
region_trained=$1 # this should be 'Bad' or 'All'
var_used=$2 # this should be 'Ext' or 'Std'

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
echo "Begin applying regression for ${region_trained} regions with ${var_used} variables."
base_location="/home/hep/wrtabb/Egamma/results/2016_${region_trained}${var_used}/"
for index in ${!pt_range[*]}; do
	input_tree="/home/hep/wrtabb/Egamma/input_trees/2016ULQCD/QCD_${pt_range[$index]}.root"
	echo "Starting input: ${input_tree}"
	output_tree="/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/Fakes/QCD_${reg_type}/${region_trained}${var_used}/QCD_2016UL_${pt_range[$index]}.root"
	script_type="/home/hep/wrtabb/Egamma/EgRegresTrainerLegacy/scripts/applyEleBadStd.py"
	ideal_location="${base_location}reg${reg_type}Ecal2016UL_IdealIC_IdealTraining_stdVar_stdCuts_{region}_ntrees1500_results.root"

	if [ $reg_type = Ele ]
	then
		python $script_type --ideal $ideal_location $input_tree $output_tree
	else
		echo "reg_type must be Ele"
	fi
	echo "Finished: output file = ${output_tree}"
	echo ""
done
