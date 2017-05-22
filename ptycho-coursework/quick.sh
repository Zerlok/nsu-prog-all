#!/bin/bash

targetObj="data/cameraman.tif"
phaseObj="data/westconcordorthphoto.bmp"
pupil="data/complex-pupil.npy"
genOutput="data/lowres.npy"
resultOutput="tmp.png"

# phaseOption="--no-phase"
phaseOption="--phase ${phaseObj}"
ledsAttrs="height=90 num=20 gap=3"


method=$2
[[ -z $method ]] && method="fp"

loops=$3
[[ -z $loops ]] && loops=30


case $method in
	"fp" | "adaptive-fp")
		cmdGen="./generator.py ${targetObj} ${phaseOption} --output-file ${genOutput} --led-attrs ${ledsAttrs} --objective-save ${pupil} --show-low-img 112"
		cmdRec="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --led-attrs ${ledsAttrs} --real-img ${targetObj} --show-images --method=${method} --loops ${loops}"
		;;
	"epry-fp")
		cmdGen="./generator.py ${targetObj} ${phaseOption} --objective=complex --objective-attrs z=100e-6 --output-file ${genOutput} --objective-save ${pupil}  --led-attrs ${ledsAttrs} --show-pupil --show-low-img 112"
		cmdRec="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --led-attrs ${ledsAttrs} --real-img ${targetObj} --real-pupil ${pupil} --show-images --method=${method} --loops ${loops}"
		;;
	*)
		echo "Unknown recovery method: ${method}!"
		exit 1
		;;
esac


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
	*)
		echo "Choose the mode: gen/rec/all"
		exit 1
		;;
esac
