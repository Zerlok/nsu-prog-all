#!/usr/bin/python3

"""A simple Fourier Ptychography recovery."""

from sys import argv
from argparse import ArgumentParser
from time import time

from optics import load_image, pack_image, Objective, get_intensity
from fp import RecoveryMethods, LEDSystem, FourierPtychographySystem as FP
from settings import *
import generator as gen
from numpy import array, load as np_load


# Objects factories
METHODS = RecoveryMethods()
LED_SYSTEMS = LEDSystem()

ERR_OUTPUT = """\
Max error: {max:.2%}
Median error: {med:.2%}
The root mean squared error: {mean_rmsd:.2%}
Lowest {lp:%} errors mean: {low_rmsd:.2%}
Highest {hp:%} errors mean: {high_rmsd:.2%}"""


def check_lowres(leds, low_data):
	ldat = low_data[len(leds) // 2]
	limg = pack_image(ldat, ldat.shape, 'I')
	limg.show()


def load_low_resolution_images(leds, dirname):
	filename = join(dirname, DEFAULT_LOWRES_FORMAT)
	return [load_image(filename.format(id=led.id), 'I') for led in leds]


def main(args):
	args.led_attrs.append(K)
	leds = LED_SYSTEMS.create(
			args.led_system,
			*args.led_attrs
	)
	recoverer = METHODS.create(
			name = args.recovery_method,
			leds = leds,
			wavelen = WAVELEN,
			sample_size = SAMPSIZE,
			quality = QUALITY,
			objective = Objective,
			NA = NA,
	)
	
	low_data = load_low_resolution_images(leds, args.sources_dir) \
			if not args.source_name else np_load(args.source_name)
	
	# check_lowres(leds, low_data)

	img_size = tuple(int(i / QUALITY) for i in low_data[0].shape)
	print("Recovery process started ...")
	data = recoverer.run(low_data, args.recover_loops)
	recoverer.print_run_duration()
	
	img = pack_image(data['amplitude'], img_size, 'I')
	img.save(args.destination_real)
	print("Result image was saved into {} file.".format(args.destination_real))

	if args.show_images:
		img.show()
		pack_image(data['phase'], img_size, norm=True).show()
		recoverer.objective.show(*img_size)

	if args.real_name:
		real_inten = load_image(args.real_name, 'I')
		result_inen = get_intensity(data['amplitude'])
		print("RMSE: {}".format(FP.count_RMSE(real_inten, result_inen)))
		diff_img = pack_image(abs(real_inten - result_inen), real_inten.shape, norm=True)
		diff_img.show()

	# if args.print_error:
	# 	target_errors = ArrayErrors(o.get_amplitude(target))
	# 	errs = target_errors.get_errors(abs(recoveried_data))
	# 	for key in target_errors.SINGLE_VALUE_KEYS:
	#		errs[key] /= 255.0
	# 	print(ERR_OUTPUT.format(lp=30, hp=5, **errs))


def build_parser():
	parser = ArgumentParser(description=__doc__)
	parser.add_argument(
			dest = "destination_real",
			metavar = "FILENAME",
			type = str,
			default = None,
			help = "a path to file where numpy arrays data (low resolution images of target) will be saved",
	)
	
	src_grp = parser.add_mutually_exclusive_group()
	src_grp.add_argument(
			"--lowres-dir",
			dest = "sources_dir",
			metavar = "DIRNAME",
			type = str,
			default = DEFAULT_LOWRES_DIR,
			help = "a path to dir with low resolution images",
	)
	src_grp.add_argument(
			"--lowres-file",
			dest = "source_name",
			metavar = "FILENAME",
			type = str,
			default = None,
			help = "a path to image file to be shown as a target object",
	)
	parser.add_argument(
			"--led-system",
			dest = "led_system",
			metavar = "NAME",
			choices = LED_SYSTEMS.keys(),
			default = LED_SYSTEMS.default_key(),
			help = "choose LED system for lighting the target: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--led-attrs",
			dest = "led_attrs",
			metavar = "ARG",
			nargs = '*',
			type = int,
			default = [LEDS_WIDTH, LEDS_GAP, LEDS_HEIGHT],
			help = "setup LEDs by size, gap between each LED and distance between LED matrix and target plate",
	)
	parser.add_argument(
			"--method",
			dest = "recovery_method",
			metavar = "NAME",
			choices = METHODS.keys(),
			default = METHODS.default_key(),
			help = "choose the FP recover method: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--loops",
			dest = "recover_loops",
			metavar = "N",
			type = int,
			default = 3,
			help = "set loops value for recovering (default: %(default)s)",
	)
	parser.add_argument(
			"--show-images",
			dest = "show_images",
			action = "store_true",
			default = False,
			help = "show images for debug",
	)

	check_grp = parser.add_argument_group(
			title = "Quick check arguments",
			description = "Arguments to check the result with real data",
	)
	check_grp.add_argument(
			"--real-img",
			dest = "real_name",
			metavar = "FILENAME",
			default = None,
			help = "check recovery result with real image",
	)

	return parser


if __name__ == '__main__':
	parser = build_parser()
	args = parser.parse_args(argv[1:])
	main(args)
