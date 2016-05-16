"""Calculates complex refractive index of material on it's transmitted and
reflected spectrums."""


from sys import argv
from sf56spectrum import read_sf
from plotter import Chart, show_charts
from common.decorators import show_duration
from sympy import exp, symbols
from math import log, pi


def build_absorption_chart(tr_chart, ref_chart):
	absorption = 100 - (tr + ref)
	absorption.name = "Absorption spectrum"
	return absorption


def build_cri_index_chart(absorption_chart, depth):
	# A = exp(-alpha * d)			alpha = -ln(1 - A/100) / d
	# alpha = 4 * pi * k / lambda	k = alpha * lambda / (4 * pi)
	absorption_ratio = absorption_chart.copy()
	absorption_ratio.name += " (A ratio)"
	for i in xrange(len(absorption_ratio)):
		absorption_ratio.axis_y[i] =  -log(1 - absorption_chart.axis_y[i]/100) * absorption_chart.axis_x[i] / (4 * pi * depth)
	
	return absorption_ratio


def build_absorption_chart_from_sf_files(tr_filename, ref_filename):
	tr = read_sf(tr_filename)
	ref = read_sf(ref_filename)
	absorption = 100 - (tr + ref)
	absorption.name = "Absorption spectrum"
	
	return absorption


@show_duration()
def build_theoretical_cri_chart(wavelens):
	w = symbols("w")
	k_formula = {
		0: (-1250000*w + 0.625),
		500: 0*w,
		900: (250000*w - 0.225),
	}
	
	values = []
	for w in wavelens:
		k_ratio = k_formula[900] if w > 900*10**-9 else k_formula[500] if w > 500*10**-9 else k_formula[0]
		values.append(float(k_ratio.evalf(subs={'w': w})))		
	
	return Chart(name=u"Theory Absorption ratio", x=wavelens, y=values)


@show_duration()
def build_absorption_chart_from_cri(cri_chart, depth):
	k, w = symbols("k w")
	alpha_formula = 1 - exp(-4 * pi * depth * k / w)
	values = [float(alpha_formula.evalf(subs={'k': cri_chart.axis_y[i], 'w': cri_chart.axis_x[i]}))*100
			for i in xrange(len(cri_chart))]
	
	return Chart(name="Theory Absorption spectrum", x=cri_chart.axis_x, y=values)


if __name__ == '__main__':
	if (len(argv) != 3):
		print __doc__
		print "Usage: %s [FILE1] [FILE2]" % __file__
		print "FILE1 - sf spectrum of transmitted intensity."
		print "FILE2 - sf spectrum of reflected intensity."
	
	tr = read_sf(argv[1])
	ref = read_sf(argv[2])
	show_charts(tr, ref, build_absorption_chart(tr, ref))
