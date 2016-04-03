from sf56spectrum import read_sf, write_sf
from plotter import show_spectrums


# s0 = read_sf('data/si_ref_09deg.sf')
s = read_sf('data/si_ref_09deg.sf')
p = read_sf('data/ITO_R1_09deg.sf')

s1 = s.copy()
s1.set_x_range(p.axis_x)
s1.name = "%s-smooth" % s.name

p1 = p * s1 / 100
p1.name = "%s-real" % p.name

show_spectrums(s, s1, p, p1)
# write_sf(p1, 'data/ITO_R1_09deg_real.sf')
