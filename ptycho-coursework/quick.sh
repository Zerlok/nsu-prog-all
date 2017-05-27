#!/bin/bash

size=256
targetObj="data/cameraman${size}.png"
phaseObj="data/concord${size}.png"
pupil="data/complex-pupil.npy"
genOutput="data/lowres.npy"
resultOutput="tmp.png"

# phaseOption="--no-phase"
phaseOption="--phase ${phaseObj}"
# ledsSystem="grid"
# ledsAttrs="height=90 num=15 gap=4"
ledsSystem="sphere"
ledsAttrs="start=33 end=75 step=3 radius=1"


method=$2
[[ -z $method ]] && method="fp"

loops=$3
[[ -z $loops ]] && loops=30


case $method in
	"fp" | "adaptive-fp")
		cmdGen="./generator.py ${targetObj} ${phaseOption} --output-file ${genOutput} --led-system ${ledsSystem} --led-attrs ${ledsAttrs} --objective-save ${pupil} --show-low-img 112"
		cmdRec="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --led-system ${ledsSystem} --led-attrs ${ledsAttrs} --real-img ${targetObj} --show-images --method=${method} --loops ${loops}"
		;;
	"epry-fp")
		cmdGen="./generator.py ${targetObj} ${phaseOption} --objective=complex --objective-attrs z=100e-6 --output-file ${genOutput} --objective-save ${pupil} --led-system ${ledsSystem} --led-attrs ${ledsAttrs} --show-pupil --show-low-img 112"
		cmdRec="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --led-system ${ledsSystem} --led-attrs ${ledsAttrs} --real-img ${targetObj} --real-pupil ${pupil} --show-images --method=${method} --loops ${loops}"
		;;
	*)
		echo "Unknown recovery method: ${method}!"
		exit 1
		;;
esac


echo "Method: ${method}, Loops: ${loops}"
case $1 in
	"gen")
		$cmdGen
		;;
	"rec")
		$cmdRec
		;;
	"all")
		$cmdGen
		echo
		$cmdRec
		;;
	# "leds")
	# 	for n in (10 15 20); do
	# 		cmd="./generator.py ${targetObj} ${phaseOption} --output-file ${genOutput} --show-fourier --show-leds brightfield --led-system ${ledsSystem}"
	# 		for i in words; do
	# 			cmd="${cmd} --led-attrs height=90 num=${n} "
	# 			#statements
	# 		done
	# 	done
	# 	;;
	*)
		echo "Choose the mode: gen/rec/all"
		exit 1
		;;
esac
