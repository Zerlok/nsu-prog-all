#!/usr/bin/python3

"""Module for low resolutions images generation."""

from sys import argv
from argparse import ArgumentParser
from time import time

from optics import load_image, pack_image, Objectives
from fp import Generators, LEDSystems
from settings import *
from common import InnerArgumentsParsing
from numpy import save as np_save


# Objects factories
OBJECTIVES = Objectives()
GENERATORS = Generators()
LED_SYSTEMS = LEDSystems()


def check_with_file(leds, ampls, filename):
	i = len(leds) // 2
	ampl1 = low_ampls[i]
	ampl2 = load_image(filename.format(id=i), 'A')
	diff = abs(ampl2 - ampl1)
	print(ampl1.max(), ampl1.min(), ampl2.max(), ampl2.min())
	print(diff.max(), diff.min())


def main(args):
	leds = LED_SYSTEMS.create(
			name = args.led_system,
			wavevec = K,
			**args.led_attrs
	)
	leds_images_generator = GENERATORS.create(
			name = args.generator_name,
			leds = leds,
			wavelen = WAVELEN,
			sample_size = SAMPSIZE,
			quality = QUALITY,
			objective = OBJECTIVES.get_creator(
				name = args.objective_name,
				**args.objective_attrs,
			),
			NA = NA,
	)

	# Add phase to objective if 'no-phase' flag was not specified.
	phase = load_image(args.phase_filename, 'A') if not args.no_phase else None
	src_ampl = load_image(args.target_filename, 'A')
	low_size = tuple(int(i * QUALITY) for i in src_ampl.shape)

	# Checks...
	print("LED system overlap: {:.2%}".format(leds_images_generator.count_leds_overlap()))
	ft_borders_ok = leds_images_generator.check_fourier_space_borders(low_size, src_ampl.shape)
	if not ft_borders_ok:
		print("Invalid leds setup, exiting!")
		return
	
	# Start to generate the low resolution images.
	print("Generation process started ...")
	low_ampls = leds_images_generator.run(src_ampl, phase)
	print(DURATION_FORMAT.format(leds_images_generator.duration))
	print("{} low resolution images were generated.".format(low_ampls.shape[0]))
	
	# print(leds_images_generator.k)
	# print("Shapes:\n[{}]".format("\n".join("{}: {}".format(led, data.shape) for (led, data) in zip(leds, low_ampls))))

	if not args.destination_filename:
		print("WARNING: generated amplitudes will be saved into image files and will loose some quality!")
		# low_images = [pack_image(get_intensity(data), low_size) for data in low_ampls]
		low_images = [pack_image(data, low_size, norm=True) for data in low_ampls]
		filename = join(args.destination_dir, DEFAULT_LOWRES_FORMAT)
		for (i, img) in enumerate(low_images):
			img.save(filename.format(id=i))
		print("Generated pictures were saved into {} directory by LED id.".format(args.destination_dir))

	else:
		np_save(args.destination_filename, low_ampls)
		print("Generated amplitudes were saved into {} file.".format(args.destination_filename))

	if args.show_low_img is not None:		
		img_id = args.show_low_img
		img = pack_image(low_ampls[img_id], low_size, norm=True)
		img.show()

	if args.objective_filename:
		leds_images_generator.objective.save(args.objective_filename, *low_size)
		print("Generated pupil was save into {} file.".format(args.objective_filename))

	if args.show_pupil:
		leds_images_generator.objective.show(*low_size)


def build_parser():
	parser = ArgumentParser(description=__doc__)
	parser.add_argument(
			dest = "target_filename",
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
			dest = "destination_filename",
			metavar = "FILENAME",
			type = str,
			default = None,
			help = "a path to file where numpy arrays data (low resolution images of target) will be saved",
	)

	phase_grp = parser.add_mutually_exclusive_group()
	phase_grp.add_argument(
			"--phase",
			dest = "phase_filename",
			metavar = "FILENAME",
			default = DEFAULT_PHASE_PATH,
			type = str,
			help = "a path to image file to be added as a phase object (default: %(default)s)",
	)
	phase_grp.add_argument(
			"--no-phase",
			dest = "no_phase",
			action = "store_true",
			default = False,
			help = "don't add phase object to the target object image",
	)

	parser.add_argument(
			"--method",
			dest = "generator_name",
			metavar = "NAME",
			choices = GENERATORS.names(),
			default = GENERATORS.default_name(),
			type = str,
			help = "choose the transfer function for pupil: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--objective",
			dest = "objective_name",
			metavar = "NAME",
			choices = OBJECTIVES.names(),
			default = OBJECTIVES.default_name(),
			type = str,
			help = "choose the objective for optical system: [%(choices)s], (default: %(default)s)",
	)
	parser.add_argument(
			"--objective-attrs",
			dest = "objective_attrs",
			action = InnerArgumentsParsing,
			metavar = "VAL",
			nargs = '*',
			default = {},
			help = "extra settings of the objectives: {}".format(OBJECTIVES.describe_all()),
	)
	parser.add_argument(
			"--objective-save",
			dest = "objective_filename",
			metavar = "FILENAME",
			type = str,
			default = None,
			help = "save the generated objective into numpy file.",
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
			type = str,
			help = "choose LED system for lighting the target: [%(choices)s], (default: %(default)s)",
	)
	led_grp.add_argument(
			"--led-attrs",
			dest = "led_attrs",
			action = InnerArgumentsParsing,
			metavar = "VAL",
			nargs = '*',
			default = DEFAULT_LEDS_ATTRS,
			help = "setup LED system:\n{}".format(LED_SYSTEMS.describe_all()),
	)
	
	check_grp = parser.add_argument_group(
			title = "Quick check arguments",
			description = "Arguments to check the result with real data.",
	)
	check_grp.add_argument(
			"--show-low-img",
			dest = "show_low_img",
			metavar = "N",
			type = int,
			default = None,
			help = "show generated low resolution images according to LEDs' id.",
	)
	check_grp.add_argument(
			"--show-pupil",
			dest = "show_pupil",
			action = "store_true",
			default = False,
			help = "show generated pupil.",
	)

	return parser


if __name__ == '__main__':
	parser = build_parser()
	args = parser.parse_args(argv[1:])
	main(args)
