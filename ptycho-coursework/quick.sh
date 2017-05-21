#!/bin/bash

targetObj="data/cameraman.tif"
phaseObj="data/westconcordorthphoto.bmp"
pupil="data/complex-pupil.npy"
genOutput="data/lowres.npy"

phaseOption="--phase ${phaseObj}"
# phaseOption="--no-phase"

loops=15
resultOutput="tmp.png"

method=$2
[[ -z $method ]] && method="fp"


case $method in
	"fp" | "adaptive-fp")
		cmdGen="./generator.py ${targetObj} ${phaseOption} --output-file ${genOutput} --objective-save ${pupil} --show-low-img 112"
		cmdRec="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --real-img ${targetObj} --show-images --method=${method} --loops ${loops}"
		;;
	"epry-fp")
		cmdGen="./generator.py ${targetObj} ${phaseOption} --objective=complex --objective-attrs z=100e-6 --output-file ${genOutput} --objective-save ${pupil} --show-pupil --show-low-img 112"
		cmdRec="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --loops ${loops} --real-img ${targetObj} --real-phase ${phaseObj} --real-pupil ${pupil} --method=${method} --show-images"
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
		$cmdRec
		;;
	*)
		echo "Choose the mode: gen/rec"
		exit 1
		;;
esac
