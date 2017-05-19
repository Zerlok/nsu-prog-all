#!/bin/bash

targetObj="data/cameraman.tif"
phaseObj="data/westconcordorthphoto.bmp"
pupil="data/complex-pupil.npy"
genOutput="data/lowres-complex.npy"

# phaseOption="--phase ${phaseObj}"
phaseOption="--no-phase"

loops=25
resultOutput="tmp.png"
method="epry-fp-corrected"


case $1 in
	"gen")
		cmd="./generator.py ${targetObj} ${phaseOption} --objective=complex --objective-attrs z=100e-6 --output-file ${genOutput} --objective-save ${pupil} --show-pupil --show-low-img 112"
		;;
	"recover")
		cmd="./recoverer.py ${resultOutput} --lowres-file ${genOutput} --loops ${loops} --real-img ${targetObj} --real-phase ${phaseObj} --real-pupil ${pupil} --method=${method} --show-images"
		;;
	*)
		echo "Choose the mode: gen/recover"
		;;
esac


echo -e "Executing:\n${cmd}\n"
$cmd
