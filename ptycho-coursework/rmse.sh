#!/bin/bash


log="logs/methods.log"
target="data/cameraman.tif"
phase="data/westconcordorthphoto.bmp"
pupil="data/rmse/pupil-epry-fp.npy"
outTmp="data/rmse/tmp.png"
ledsAttrs="height=90 num=15 gap=4"

noPhaseMethod="clean"
methods=($noPhaseMethod "fp" "epry-fp" "adaptive-fp")
# methods=("adaptive-fp")

start=5
end=100
step=5

valueGrep="grep -oE [0-9]+[.]?[0-9]+"


function getLowresFile() {
	echo "data/rmse/low-${1}.npy"
}


function getGenForMethod() {
	local base="./generator.py ${target} --led-attrs ${ledsAttrs} --output-file"
	local lows=$(getLowresFile $1)
	
	case $1 in
		$noPhaseMethod)
			cmd="${base} ${lows} --no-phase"
			;;
		"fp")
			cmd="${base} ${lows} --phase ${phase}"
			;;
		"adaptive-fp" | "epry-fp")
			cmd="${base} ${lows} --phase ${phase} --objective complex --objective-attrs z=100e-6 --objective-save ${pupil}"
			;;
	esac

	echo $cmd
}


function getRecForMethod() {
	local base="./recoverer.py ${outTmp} --led-attrs ${ledsAttrs} --real-img ${target} --lowres-file"
	local lows=$(getLowresFile $1)
	local m=$1
	[[ "${m}" == "${noPhaseMethod}" ]] && m="fp"

	case $m in
		"epry-fp")
			echo "${base} ${lows} --method ${m} --loops ${2} --real-pupil ${pupil}"
			;;
		*)
			echo "${base} ${lows} --method ${m} --loops ${2}"
			;;
	esac
}


for method in "${methods[@]}"; do
	cmd=$(getGenForMethod $method)
	echo $cmd
	$cmd
	echo "done."
	echo
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
		echo -n "Iteration: ${i} ${method} recovery ... "

		res=$($cmd)
		dur=$(echo -e "${res}" | grep "Duration" | $valueGrep)
		err=$(echo -e "${res}" | grep "Object RMSE" | $valueGrep)

		pupErr=$(echo -e "${res}" | grep "Pupil RMSE" | $valueGrep)
		if [[ ! -z $pupErr ]]; then
			err="${err}+${pupErr}"
		fi

		durs+=($dur)
		errs+=($err)

		echo "${dur} ms, ${err}"
	done
	
	errs=$(printf "|%s" "${errs[@]}")
	durs=$(printf "|%s" "${durs[@]}")
	echo "${i}|${errs:1}|${durs:1}" >> $log
done
