#!/bin/bash

log="logs/epry-rmse.log"
target="data/cameraman.tif"
phase="data/westconcordorthphoto.bmp"
lowNoPhase="data/low-complex-no-phase.npy"
lowWithPhase="data/low-complex-with-phase.npy"

baseGen="./generator.py ${target} --objective complex --objective-attrs z=100e-6 --output-file"
noPhaseGen="${baseGen} ${lowNoPhase} --no-phase"
phaseGen="${baseGen} ${lowWithPhase}"
generation=("${noPhaseGen}" "${phaseGen}")

tmpImg="tmp.png"
[[ -f $tmpImg ]] && echo "${tmpImg} already exists!" && exit 1

method="epry-fp"
prog="./recoverer.py"
baseRec="--real-img ${target} --method ${method} --lowres-file"
noPhaseRec="${baseRec} ${lowNoPhase} --loops"
phaseRec="${baseRec} ${lowWithPhase} --loops"
recovery=("${noPhaseRec}" "${phaseRec}")

start=10
end=10
step=5
valueGrep="grep -oE [0-9]+[.]?[0-9]+"
cmdInputTypeGrep="grep -oE (no[-_]?phase|with[-_]?phase)"


# Gen images.
# durations=()
for cmd in "${generation[@]}"; do
	$cmd
	echo
done


# Recover images.
# currDate=$(date +'%T %d.%m.%Y')

echo "Recovery (${method}) range(${start},${end},${step}), logging into ${log} ..."
echo "Recovery (${method}) range(${start},${end},${step})" > $log
for (( i = $start; i <= $end; i += $step )); do
	for cmd in "${recovery[@]}"; do
		inputType=$(echo "${cmd}" | $cmdInputTypeGrep )
		echo "Iteration: ${i} ${inputType} recovery (${cmd}) ..."

		dooo="${prog} data/highres/hr-${method}-${i}-${inputType}.png ${cmd} ${i}"
		res=$($dooo)
		dur=$(echo -e "${res}" | grep "Duration" | $valueGrep)
		rmse=$(echo -e "${res}" | grep "RMSE" | $valueGrep)
		echo "${i}|${dur}|${rmse}|${inputType}" >> $log
	done
done

# [[ -f $tmpImg ]] && rm $tmpImg
