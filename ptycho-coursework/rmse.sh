#!/bin/bash


# Consts.
log="logs/methods.log"
size=256
# target="data/cameraman.tif"
target="data/cameraman${size}.png"
phase="data/concord${size}.png"
pupil="data/rmse/pupil-epry-fp.npy"
outTmp="data/rmse/tmp.png"

# LEDs setup.
ledsNum=15
ledsGap=4
ledsAttrs="height=90 num=${ledsNum} gap=${ledsGap}"

# Recovery methods.
noPhaseMethod="clean"
# methods=($noPhaseMethod "fp" "epry-fp" "adaptive-fp")
# methods=("adaptive-fp")
methods=("fp" "epry-fp")

# Loops (for errors calculation).
start=5
end=100
step=5
loops=(10 20 40 80) # For result images.

valueGrep="grep -oE [0-9]+[.]?[0-9]+"


# Functions.

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
	local m=$1
	[[ "${m}" == "${noPhaseMethod}" ]] && m="fp"
	
	local out=$3
	[[ -z $out ]] && out=$outTmp
	
	local lows="$(getLowresFile $1)"
	local base="./recoverer.py ${out} --lowres-file ${lows} --led-attrs ${ledsAttrs} --real-img ${target} --method ${m} --loops ${2}"
	
	if [[ "${m}" == "epry-fp" ]]; then
		base="${base} --real-pupil ${pupil}"
	fi

	echo "${base}"
}


# Main.
[[ -z $1 ]] && echo "Choose option: errors/images" && exit 1


# Generate low-res images.
for method in "${methods[@]}"; do
	cmd=$(getGenForMethod $method)
	echo $cmd
	$cmd
	echo "done."
	echo
done


# Recover images.
case $1 in
	"errors")
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
		;;

	"images")
		echo "Generating recovery images for methods (${methods[@]}) and loops (${loops[@]}) ..."
		for i in ${loops[@]}; do
			for method in "${methods[@]}"; do
				output="data/results/px${size}/hr-${method}-${ledsNum}x${ledsNum}-${ledsGap}mm-${i}.png"
				cmd=$(getRecForMethod $method $i $output)
				echo "Iteration: ${i} ${method} recovery to file ${output} ... "
				$cmd
			done
		done
		;;

	*)
		echo "Choose option: errors/images"
		exit 1
		;;
esac


echo "done."
