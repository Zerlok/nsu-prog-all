#!/bin/bash

methods=("fp" "epry-fp" "adaptive-fp")

log="logs/methods.log"
target="data/cameraman.tif"
phase="data/westconcordorthphoto.bmp"

baseGen="./generator.py ${target} --output-file"
baseRec="./recoverer.py tmp.png --real-img ${target} --lowres-file"

start=5
end=10
step=5
valueGrep="grep -oE [0-9]+[.]?[0-9]+"
cmdInputTypeGrep="grep -oE (no[-_]?phase|with[-_]?phase)"


function getLowresFile() {
	local p="no-phase"
	if $2; then
		p="with-phase"
	fi

	echo "data/low-${1}-${p}.npy"
}


function getGenForMethod() {
	local lows=$(getLowresFile $1 $2)

	local phaseOption="--no-phase"
	if $2; then
		phaseOption="--phase ${phase}"
	fi
	
	case $1 in
		"fp" | "adaptive-fp")
			cmd="${baseGen} ${lows} ${phaseOption}"
			;;
		"epry-fp")
			cmd="${baseGen} ${lows} ${phaseOption} --objective complex --objective-attrs z=100e-6"
			;;
	esac
	echo $cmd
}


function getRecForMethod() {
	local lows=$(getLowresFile $1 $2)
	echo "${baseRec} ${lows} --method ${1} --loops ${3}"
}


generators=()
for method in "${methods[@]}"; do
	generators+=("$(getGenForMethod $method false)" "$(getGenForMethod $method true)")
done


for cmd in "${generators[@]}"; do
	echo $cmd
	$cmd
done


# Recover images.
# currDate=$(date +'%T %d.%m.%Y')

echo "Recovery (${methods[@]}) range(${start},${end},${step}), logging into ${log} ..."
echo "Recovery (${methods[@]}) range(${start},${end},${step})" > $log
for (( i = $start; i <= $end; i += $step )); do
	for method in "${methods[@]}"; do
		recoveries=("$(getRecForMethod $method false $i)" "$(getRecForMethod $method true $i)")
		for cmd in "${recoveries[@]}"; do
			inputType=$(echo "${cmd}" | $cmdInputTypeGrep )
			echo "Iteration: ${i} ${method} ${inputType} recovery ..."

			res=$($cmd)
			dur=$(echo -e "${res}" | grep "Duration" | $valueGrep)
			rmse=$(echo -e "${res}" | grep "RMSE" | $valueGrep)
			echo "${i}|${method}|${inputType}|${dur}|${rmse}" >> $log
		done
	done
done
