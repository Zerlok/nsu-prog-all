#!/bin/bash


log="logs/methods.log"
target="data/cameraman.tif"
phase="data/westconcordorthphoto.bmp"
ledsAttrs="height=90 num=15 gap=4"

noPhaseMethod="clean"
methods=($noPhaseMethod "fp" "epry-fp" "adaptive-fp")

start=5
end=100
step=5

valueGrep="grep -oE [0-9]+[.]?[0-9]+"


function getLowresFile() {
	echo "data/low-${1}.npy"
}


function getGenForMethod() {
	local base="./generator.py ${target} --led-attrs ${ledsAttrs} --output-file"
	local lows=$(getLowresFile $1)
	
	case $1 in
		$noPhaseMethod)
			cmd="${base} ${lows} --no-phase"
			;;
		"fp" | "adaptive-fp")
			cmd="${base} ${lows} --phase ${phase}"
			;;
		"epry-fp")
			cmd="${base} ${lows} --phase ${phase} --objective complex --objective-attrs z=100e-6"
			;;
	esac

	echo $cmd
}


function getRecForMethod() {
	local base="./recoverer.py tmp.png --led-attrs ${ledsAttrs} --real-img ${target} --lowres-file"
	local lows=$(getLowresFile $1)
	local m=$1
	[[ "${1}" == "${noPhaseMethod}" ]] && m="fp"

	echo "${base} ${lows} --method ${m} --loops ${2}"
}


for method in "${methods[@]}"; do
	cmd=$(getGenForMethod $method)
	echo $cmd
	$cmd
done


# Recover images.
# currDate=$(date +'%T %d.%m.%Y')

echo "Recovery (${methods[@]}) range(${start},${end},${step}), logging into ${log} ..."
echo "Recovery (${methods[@]}) range(${start},${end},${step})" > $log
for (( i = $start; i <= $end; i += $step )); do
	errs=()
	durs=()

	for method in "${methods[@]}"; do
		cmd=$(getRecForMethod $method $i)
		echo "Iteration: ${i} ${method} recovery ..."

		res=$($cmd)
		durs+=($(echo -e "${res}" | grep "Duration" | $valueGrep))
		errs+=($(echo -e "${res}" | grep "RMSE" | $valueGrep))
	done
	
	errs=$(printf "|%s" "${errs[@]}")
	durs=$(printf "|%s" "${durs[@]}")
	echo "${i}|${errs:1}|${durs:1}" >> $log
done
