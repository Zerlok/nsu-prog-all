#!/usr/bin/python3

from optics import load_image, pack_image, Objective
from fp import LEDGrid, LEDGenerator
from settings import *


HIGH_SIZE = (256, 256)
LOW_SIZE = tuple(int(i * QUALITY) for i in HIGH_SIZE)


def main():
	sizes = (10, 15, 20)
	gaps = (2, 3, 3.5, 4, 4.4, 5)
	
	generator = LEDGenerator(
			leds = None,
			wavelen = WAVELEN,
			sample_size = SAMPSIZE,
			quality = QUALITY,
			objective = Objective,
			NA = NA,
	)

	for n in sizes:
		for g in gaps:
			generator.leds = LEDGrid(
					wavevec = K,
					height = LEDS_HEIGHT,
					num = n,
					gap = g,
			)
			if not generator.check_fourier_space_borders(LOW_SIZE, HIGH_SIZE):
				print("Invalid leds setup: {}".format(generator.leds))
				continue

			print("LED system: {0}x{0} {1}mm".format(n, g))
			print("LED system overlap: {:.2%}".format(generator.count_leds_overlap()))
			print("LED system Fourier space coverage: {:.2%}".format(generator.count_total_coverage()))
			
			img_leds = generator.get_leds_look(HIGH_SIZE, brightfield=True, darkfield=True)
			img_coverage = generator.get_leds_look(HIGH_SIZE, overlaps=True)
			
			posname = 'leds-{0}x{0}-{1}mm-positions.png'.format(n, g)
			covname = 'leds-{0}x{0}-{1}mm-coverage.png'.format(n, g)
			
			img_leds.save(join(join(DATA_DIR, 'systems'), posname))
			img_coverage.save(join(join(DATA_DIR, 'systems'), covname))


if __name__ == '__main__':
	main()