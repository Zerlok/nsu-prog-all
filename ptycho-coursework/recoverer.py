#!/usr/bin/python3

"""A simple Fourier Ptychography recovery."""

from sys import argv
from argparse import ArgumentParser
from time import time

from optics import load_image, pack_image, Objective, get_intensity, normalize
from fp import RecoveryMethods, LEDSystems, FourierPtychographySystem as FP
from settings import *
from common import InnerArgumentsParsing
from numpy import array, load as np_load


# Factories.
METHODS = RecoveryMethods()
LED_SYSTEMS = LEDSystems()

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


def main(args):
	leds = LED_SYSTEMS.create(
			name = args.led_system,
			wavevec = K,
			**args.led_attrs
	)
	recoverer = METHODS.create(
			name = args.recovery_method,
			leds = leds,
			loops = args.recover_loops,
			wavelen = WAVELEN,
			sample_size = SAMPSIZE,
			quality = QUALITY,
			objective = Objective,
			NA = NA,
	)
	
	low_data = load_low_resolution_images(leds, args.sources_dir) \
			if not args.source_name else np_load(args.source_name)
	
	# check_lowres(leds, low_data)

	low_size = low_data[0].shape
	img_size = tuple(int(i / QUALITY) for i in low_data[0].shape)
	print("Recovery process started ...")
	data = recoverer.run(low_data)
	print(DURATION_FORMAT.format(recoverer.duration))
	
	# print(data['amplitude'].max())
	img = pack_image(data['amplitude'], img_size, 'I', norm=True)
	img.save(args.destination_real)
	print("Result image was saved into {} file.".format(args.destination_real))

	if args.show_images:
		print("Showing recovered object and phase")
		img.show()
		if 'pupil' in data:
			pack_image(data['pupil'], low_size, norm=True).show()

	if args.real_object_filename:
		real_inten = load_image(args.real_object_filename, 'I')
		# result_inten = get_intensity(data['amplitude'])
		result_inten = array(img)
		print("Object RMSE: {:.3f}".format(
				FP.count_RMSE(real_inten, result_inten),
		))
		if args.show_images:
			diff_img = pack_image(abs(real_inten - result_inten), real_inten.shape, norm=True)
			diff_img.show()

	if args.real_pupil_filename and 'pupil' in data:
		real_inten = np_load(args.real_pupil_filename)
		print("Pupil RMSE: {:.3f}".format(
				FP.count_RMSE(real_inten, data['pupil']),
		))
		if args.show_images:
			diff_img = pack_image(abs(real_inten - data['pupil']), real_inten.shape, norm=True)
			diff_img.show()
	elif args.real_pupil_filename and 'pupil' not in data:
		print("Use another method to recover pupil.")


def build_parser():
	parser = ArgumentParser(description=__doc__)
	parser.add_argument(
			dest = "destination_real",
			metavar = "FILENAME",
			type = str,
			default = None,
			help = "a path to file where numpy arrays data (low resolution images of target) will be saved",
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
			"--method",
			dest = "recovery_method",
			metavar = "NAME",
			choices = METHODS.names(),
			default = METHODS.default_name(),
			help = "choose the FP recover method: [%(choices)s], (default: %(default)s)",
	)
	
	src_grp = parser.add_mutually_exclusive_group()
	src_grp.add_argument(
			"--lowres-file",
			dest = "source_name",
			metavar = "FILENAME",
			type = str,
			default = DEFAULT_LOWRES_FILE,
			help = "a path to image file to be shown as a target object",
	)
	src_grp.add_argument(
			"--lowres-dir",
			dest = "sources_dir",
			metavar = "DIRNAME",
			type = str,
			default = None,
			help = "a path to dir with low resolution images",
	)

	led_grp = parser.add_argument_group(
			title = "LED arguments",
			description = "Arguments to customize the LED lighting system.",
	)
	led_grp.add_argument(
			"--led-system",
			dest = "led_system",
			metavar = "NAME",
			choices = LED_SYSTEMS.names(),
			default = LED_SYSTEMS.default_name(),
			help = "choose LED system for lighting the target: [%(choices)s], (default: %(default)s)",
	)
	led_grp.add_argument(
			"--led-attrs",
			dest = "led_attrs",
			action = InnerArgumentsParsing,
			metavar = "ARG",
			nargs = '*',
			default = DEFAULT_LEDS_ATTRS,
			help = "setup LED system:\n{}".format(LED_SYSTEMS.describe_all()),
	)

	check_grp = parser.add_argument_group(
			title = "Quick check arguments",
			description = "Arguments to check the result with real data.",
	)
	check_grp.add_argument(
			"--real-img",
			dest = "real_object_filename",
			metavar = "FILENAME",
			default = None,
			help = "check recovery result with real object image",
	)
	check_grp.add_argument(
			"--real-phase",
			dest = "real_phase_filename",
			metavar = "FILENAME",
			default = None,
			help = "check recovery result with real phase image",
	)
	check_grp.add_argument(
			"--real-pupil",
			dest = "real_pupil_filename",
			metavar = "FILENAME",
			default = None,
			help = "check recovery result with real pupil",
	)
	check_grp.add_argument(
			"--show-images",
			dest = "show_images",
			action = "store_true",
			default = False,
			help = "show images for debug",
	)

	return parser


if __name__ == '__main__':
	parser = build_parser()
	args = parser.parse_args(argv[1:])
	main(args)
