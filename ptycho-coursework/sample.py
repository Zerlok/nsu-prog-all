#!/usr/bin/python3


from optics import *
from settings import *


def main():
	s = System(
			wavelen = WAVELEN,
			sample_size = SAMPSIZE,
			quality = QUALITY,
			objective = Objective,
			NA = NA,
	)
	img0 = load_image('data/cameraman256.png', 'A')
	phase = load_image('data/concord256.png', 'A')
	
	result = s.run(img0, phase=None)
	img1 = pack_image(result['amplitude'], result['size'], 'I', norm=True)
	img1.show()


if __name__ == '__main__':
	main()