from sf56spectrum import read_sf, Spectrum
from plotter import show_spectrums
from spectrummath import Polinom, get_spectrum_polinom


# s = create_spectrum('name', 10, x=range(-10, 1), y=[-x*9 for x in range(-10, 1)])
s = read_sf('data/si_ref_09deg.sf')
p = read_sf('data/ITO_ref_19om_09deg.sf')
# polinoms = [get_spectrum_polinom(s, *range(8, m)) for m in range(12, 16)]

# xies = [x for x in xrange(200, 250)]
# f = [create_spectrum(
# 			name = 'pol-%s' % len(p.indecies),
# 			length = len(xies),
# 			x = xies,
# 			y=[p.value(x) for x in xies])
# 	for p in polinoms
# ]
# show_spectrums(s, *f)

s1 = s.copy()
s1.set_x_range(p.axis_x)
s1.name = "%s-smooth" % s.name

p1 = p * s1 / 100
p1.name = "%s-real" % p.name

show_spectrums(s, p, p1)
