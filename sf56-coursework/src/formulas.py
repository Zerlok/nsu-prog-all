from sf56spectrum import Spectrum
from plotter import show_spectrums
from sympy import symbols, sqrt, sin, cos, I, pi, exp, re
from datetime import datetime
now = datetime.now


def notifyer(show_args_kwargs=False):
	def wrapper(function):
		def inner(*args, **kwargs):
			print function.__name__, "started."
			if show_args_kwargs and args:
				print "  agrs num: ", len(args)
			if show_args_kwargs and kwargs:
				print "  kwargs:   ", kwargs.keys()
			
			start = now()
			result = function(*args, **kwargs)
			print function.__name__, "duration: %f s." % (now()-start).total_seconds()
			
			return result
		
		return inner
	return wrapper


def to_intensity(value):
	# Using re in case of the imaginary part in multiplying.
	# It's not zero value, because of the sympy calculation accuracy is not so good.
	return float(re(value*value.conjugate()))


@notifyer()
def count_for_arguments(formula, arguments, valuetion=None):
	result = [formula.evalf(subs={'x': x}) for x in arguments]
	if not valuetion:
		return result
	
	return map(valuetion, result)


@notifyer()
def get_T_R_formulas():
	# Known arguments.
	N1, N3, phi, wavelen, height = symbols("N1 N3 phi x h")
	# Unknown arguments.
	N2, phi2, phi3, r12, r23, t12, t23, delta = symbols("N2 phi2 phi3 r12 r23 t12 t23 delta")
	# Expressions.
	cos_phi2 = cos(phi2)
	cos_phi3 = cos(phi3)
	cos_phi2_1 = sqrt(N2**2 - N1**2 * sin(phi)**2) / N2
	cos_phi3_1 = sqrt(N3**2 - N1**2 * sin(phi)**2) / N3

	versions = {
		# clean
		'clean': {
			'r12': r12,
			'r23': r23,
			't12': t12,
			't23': t23,
			'phid': delta,
		},
		'default': {
			'r12': (N2*cos(phi) - N1*cos_phi2) / (N2*cos(phi) + N1*cos_phi2),
			'r23': (N3*cos_phi2 - N2*cos_phi3) / (N3*cos_phi2 + N2*cos_phi3),
			't12': (2*N1*cos(phi)) / (N2*cos(phi) + N1*cos_phi2),
			't23': (2*N2*cos_phi2) / (N3*cos_phi2 + N2*cos_phi3),
			'phid': (4*pi / wavelen) * height * N2 * cos_phi2,
		},
		'expanded': {
			'r12': (-N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi))/(N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi)),
			't12': 2*N1*N2*cos(phi)/(N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi)),
			'r23': (-N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2))/(N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2)),
			't23': 2*N2*N3*sqrt(-N1**2*sin(phi)**2 + N2**2)/(N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2)),
			'phid': (4*pi / wavelen) * height * N2 * cos_phi2_1,
		},
	}
	
	for v in versions.values():
		d = v['phid']
# 		v['T'] = (v['t12']*v['t23']*exp(I*d/2)) / (1 - (1 + v['t12'])*(1 - v['t23'])*exp(I*d))		# T from book
		v['T'] = (v['t12']*v['t23']*exp(I*d/2)) / (1 + v['r12']*v['r23']*exp(I*d))					# T new mine
# 		v['T'] = (v['t12']*v['t23']*exp(I*d/2)) / (1 + (1 - v['t12'])*(1 - v['t23'])*exp(I*d))		# T from book UPDATED!
# 		v['R'] = (v['r12'] + v['r23']*exp(I*d)) / (1 + v['r12']*v['r23']*exp(I*d))					# R from book
		v['R'] = v['r12'] + (v['t12']**2 * v['r23']*exp(I*d)) / (1 + v['r12']*v['r23']*exp(I*d))	# R new mine
		
	versions['subs'] = [(cos_phi3, cos_phi3_1), (cos_phi2, cos_phi2_1)]
	return versions


@notifyer()
def build_T_R_plots(tr, ref, x_values):
	# T
	t_values = count_for_arguments(tr, x_values, to_intensity)
	t_plot = Spectrum(x=x_values, y=t_values)
	t_plot *= 100
	t_plot.name = 'T formula'

	# R
	r_values = count_for_arguments(ref, x_values, to_intensity)
	r_plot = Spectrum(x=x_values, y=r_values)
	r_plot *= 100
	r_plot.name = 'R formula'
	
	return t_plot, r_plot


def show_T_R_plots(N1, N2, N3, phi, h, min_wave, max_wave, step):
	x_values = [x*10**-9 for x in xrange(min_wave, max_wave+step, step)]
	arguments = {'N1': N1, 'N2': N2, 'N3': N3, 'phi': phi, 'h': h}

	versions = get_T_R_formulas()
	version = versions['expanded']
	tr = version['T'].subs(arguments.items())
	ref = version['R'].subs(arguments.items())

	tr_plot, ref_plot = build_T_R_plots(tr, ref, x_values)
	summ = tr_plot + ref_plot
# 	expected = 100 - ref_plot
# 	expected.name = 'T expected formula'

	show_spectrums(ref_plot, tr_plot, summ)


if __name__ == '__main__':
	arguments = {
			'N1': 1,
			'N2': 2,
			'N3': 1.5,
			'phi': 0,
# 			'phi': pi*9/20,	# 9 degrees.
# 			'phi': pi/4,	# 45 degrees.
			'h': 100*10**-9,
			'min_wave': 200,
			'max_wave': 6000,
			'step': 100,
	}
	show_T_R_plots(**arguments)
