#!/bin/bash

log="rmse.log"
target="data/cameraman.tif"
lowNoPhase="data/low-no-phase.npy"
lowWithPhase="data/low-with-phase.npy"

baseGen="./generator.py ${target} --output-file"
noPhaseGen="${baseGen} ${lowNoPhase} --no-phase"
phaseGen="${baseGen} ${lowWithPhase}"
generation=("${noPhaseGen}" "${phaseGen}")

tmpImg="tmp.png"
[[ -f $tmpImg ]] && echo "${tmpImg} already exists!" && exit 1

baseRec="./recoverer.py ${tmpImg} --real-img ${target} --lowres-file"
noPhaseRec="${baseRec} ${lowNoPhase} --loops"
phaseRec="${baseRec} ${lowWithPhase} --loops"
recovery=("${noPhaseRec}" "${phaseRec}")

start=2
end=2
step=2
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

echo "Recovery range(${start},${end},${step})" > $log
for (( i = $start; i < $end; i += $step )); do
	for cmd in "${recovery[@]}"; do
		inputType=$(echo "${cmd}" | $cmdInputTypeGrep )
		echo "Iteration: ${i} ${inputType} recovery ..."

		res=$($cmd $i)
		dur=$(echo -e "${res}" | grep "Duration" | $valueGrep)
		rmse=$(echo -e "${res}" | grep "RMSE" | $valueGrep)
		echo "${i}|${dur}|${rmse}|${inputType}" >> $log
	done
done

[[ -f $tmpImg ]] && rm $tmpImg
