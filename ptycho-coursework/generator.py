#!/usr/bin/python3

"""Module for low resolutions images generation."""

from sys import argv
from argparse import ArgumentParser
from time import time

from optics import load_image, pack_image, Objectives
from fp import Generators, LEDSystem
from settings import *
from numpy import arange, array, meshgrid, mean, save as np_save, load as np_load, any as np_any


# Objects factories
OBJECTIVES = Objectives()
GENERATORS = Generators()
LED_SYSTEMS = LEDSystem()


def check_with_file(leds, ampls, filename):
	i = len(leds) // 2
	ampl1 = low_ampls[i]
	ampl2 = load_image(filename.format(id=i), 'A')
	diff = abs(ampl2 - ampl1)
	print(ampl1.max(), ampl1.min(), ampl2.max(), ampl2.min())
	print(diff.max(), diff.min())


def main(args):
	args.led_attrs.append(K)
	leds = LED_SYSTEMS.create(
			args.led_system,
			*args.led_attrs
	)
	leds_images_generator = GENERATORS.create(
			name = args.generator_name,
			leds = leds,
			wavelen = WAVELEN,
			sample_size = SAMPSIZE,
			quality = QUALITY,
			objective = OBJECTIVES.get(args.objective),
			NA = NA,
	)

	# for led in leds.items():
	# 	print(led)

	# Add phase to objective if 'no-phase' flag was not specified.
	phase = load_image(args.phase_src, 'A') if not args.no_phase else None
	src_ampl = load_image(args.target_src, 'A')
	low_size = tuple(int(i * QUALITY) for i in src_ampl.shape)
	
	print("Generation process started ...")
	low_ampls = leds_images_generator.run(src_ampl, phase)
	leds_images_generator.print_run_duration()
	# leds_images_generator.run.print_last_duration()
	print("{} low resolution images were generated.".format(low_ampls.shape[0]))
	print(leds_images_generator.k)
	# print("Shapes:\n[{}]".format("\n".join("{}: {}".format(led, data.shape) for (led, data) in zip(leds.items(), low_ampls))))

	if not args.destination_name:
		# low_images = [pack_image(get_intensity(data), low_size) for data in low_ampls]
		low_images = [pack_image(data, low_size, norm=True) for data in low_ampls]
		filename = join(args.destination_dir, DEFAULT_LOWRES_FORMAT)
		for (i, img) in enumerate(low_images):
			img.save(filename.format(id=i))
		print("Generated pictures were saved into {} directory by LED id.".format(args.destination_dir))

	else:
		filename = args.destination_name
		np_save(filename, low_ampls)
		print("Generated amplitudes were saved into {} file.".format(args.destination_name))

	if args.show_low_img is not None:		
		img_id = args.show_low_img
		# img = pack_image(low_ampls[img_id], low_size, norm=True)
		img = pack_image(low_ampls[img_id], low_size, norm=True)
		img.show()



def build_parser(add_help=True):
	parser = ArgumentParser(description=__doc__, add_help=add_help)
	parser.add_argument(
			dest = "target_src",
			metavar = "FILENAME",
			type = str,
			help = "a path to image file to be shown as a target object",
	)

	dest_grp = parser.add_mutually_exclusive_group()
	dest_grp.add_argument(
			"--output-dir",
			dest = "destination_dir",
			metavar = "DIRNAME",
			type = str,
			default = DEFAULT_LOWRES_DIR,
			help = "a path to image file to be shown as a target object (default: %(default)s)",
	)
	dest_grp.add_argument(
			"--output-file",
			dest = "destination_name",
			metavar = "FILENAME",
			type = str,
			default = None,
			help = "a path to file where numpy arrays data (low resolution images of target) will be saved",
	)

	phase_grp = parser.add_mutually_exclusive_group()
	phase_grp.add_argument(
			"--phase",
			dest = "phase_src",
			metavar = "FILENAME",
			type = str,
			default = DEFAULT_PHASE_PATH,
			required = False,
			help = "a path to image file to be added as a phase object (default: %(default)s)",
	)
	phase_grp.add_argument(
			"--no-phase",
			dest = "no_phase",
			action = "store_true",
			default = False,
			required = False,
			help = "don't add phase object to the target object image",
	)

	parser.add_argument(
			"--method",
			dest = "generator_name",
			metavar = "NAME",
			choices = GENERATORS.keys(),
			default = 'simple-lowres-generator',
			help = "choose the transfer function for pupil: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--objective",
			dest = "objective",
			metavar = "NAME",
			choices = OBJECTIVES.keys(),
			default = 'simple',
			help = "choose the transfer function for pupil: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--show-low-img",
			dest = "show_low_img",
			metavar = "N",
			type = int,
			default = None,
			help = "show generated low resolution images according to LEDs' id.",
	)
	parser.add_argument(
			"--led-system",
			dest = "led_system",
			metavar = "NAME",
			choices = LED_SYSTEMS.keys(),
			default = 'grid',
			help = "choose LED system for lighting the target: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--led-attrs",
			dest = "led_attrs",
			metavar = "ARG",
			nargs = '*',
			type = int,
			default = [LEDS_WIDTH, LEDS_GAP, LEDS_HEIGHT],
			help = "customize LED system",
	)

	return parser


if __name__ == '__main__':
	parser = build_parser()
	args = parser.parse_args(argv[1:])
	main(args)