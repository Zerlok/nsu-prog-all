"""Calculates complex refractive index of material on it's transmitted and
reflected spectrums."""


from sys import argv
from sf56spectrum import get_x_range_intersection, read_sf, Chart
from plotter import show_charts


def get_absorption_spectrum(transmit, reflect):
	x_range = get_x_range_intersection(transmit, reflect)
	transmit.set_x_range(x_range)
	reflect.set_x_range(x_range)
	
	absorption = Chart("absorption spectrum")
	
	for i in xrange(len(transmit)):
		tr_co = transmit.get_xy(i)
		ref_co = reflect.get_xy(i)
		absorption._append(tr_co[0], 100 - tr_co[1] - ref_co[1])
	
	return absorption


if __name__ == '__main__':
	if (len(argv) != 3):
		print __doc__
		print "Usage: %s [FILE1] [FILE2]" % __file__
		print "FILE1 - sf spectrum of transmitted intensity."
		print "FILE2 - sf spectrum of reflected intensity."
	
	tr = read_sf(argv[1])
	ref = read_sf(argv[2])
	show_charts(tr, ref, get_absorption_spectrum(tr, ref))
