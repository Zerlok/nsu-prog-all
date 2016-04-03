"""Calculates complex refractive index of material on it's transmitted and
reflected spectrums."""


from sys import argv
from sf56spectrum import get_x_range_intersection, set_x_range, read_sf, create_spectrum


def calculate_N(transmit, reflect):
	x_range = get_x_range_intersection(transmit, reflect)
	transmit = set_x_range(transmit, x_range)
	reflect = set_x_range(reflect, x_range)
	
	absorption = create_spectrum()
	absorption['x'] = x_range
	
	for i in xrange(transmit['len']):
		absorption['y'] = 100 - transmit['y'][i] - reflect['y'][i]
	
	return absorption


if __name__ == '__main__':
	if (len(argv) != 3):
		print __doc__
		print "Usage: %s [FILE1] [FILE2]" % __file__
		print "FILE1 - sf spectrum of transmitted intensity."
		print "FILE2 - sf spectrum of reflected intensity."
	
	calculate_N(read_sf(argv[1]), read_sf(argv[2]))