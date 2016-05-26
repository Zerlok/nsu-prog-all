# -*- coding: utf-8 -*-
from sympy import exp, pi, symbols
from sf56spectrum import read_sf, show_spectrums
from plotter import Chart, show_charts
from formulas import TRFormulasGenerator, count_values_for, to_intensity
from common.decorators import show_duration
from src.optics import build_absorption_chart


@show_duration()
def generate_T_R_values(tr, ref, x_values):
	def to_value(x):
		return float(to_intensity(x)) * 100
	
	return (
		count_values_for(tr, 'w', x_values, to_value),
		count_values_for(ref, 'w', x_values, to_value)
	)	


def linear_values(sx, ex, sy, ey, step=1):
	k = (ey - sy) / (ex - sx)
	b = ey - k * ex
	return [k*x + b for x in xrange(sx, ex, step)]


def get_linear_eq(sx, ex, sy, ey, arg):
	k = (ey - sy) / (ex - sx)
	b = ey - k * ex
	return (arg * k) + b


@show_duration()
def main(argus):
	w = symbols("w")
	wave_step = 10
	T, R = TRFormulasGenerator.get_expanded()
	g = lambda x: float(1-x)*100
	
	wavelens = [x*10**-9 for x in xrange(300, 500, wave_step)]
	k = get_linear_eq(300*10**-9, 500*10**-9, 0.25, 0, w)
	tr_args = argus.copy()
	tr_args['N2'] = argus['N2'] + k
	ref_args = tr_args.copy()
	ref_args['phi'] = pi/20
# 	absorb_formula = exp(-4*pi*argus['h']*k/w)
	tr_formula = T.subs(tr_args.items())
	ref_formula = R.subs(ref_args.items())
	tr_values1, ref_values1 = generate_T_R_values(tr_formula, ref_formula, wavelens)
# 	absorption1 = count_values_for(absorb_formula, 'w', wavelens, g)
	
	wavelens = [x*10**-9 for x in xrange(500, 800, wave_step)]
	k = 0
	tr_formula = T.subs(tr_args.items())
	ref_formula = R.subs(ref_args.items())
	tr_values2, ref_values2 = generate_T_R_values(tr_formula, ref_formula, wavelens)
# 	absorption2 = count_values_for(absorb_formula, 'w', wavelens, g)
	
	wavelens = [x*10**-9 for x in xrange(800, 1100, wave_step)]
	k = get_linear_eq(800*10**-9, 1100*10**-9, 0, 0.1, w)
	tr_formula = T.subs(tr_args.items())
	ref_formula = R.subs(ref_args.items())
	tr_values3, ref_values3 = generate_T_R_values(tr_formula, ref_formula, wavelens)
# 	absorption3 = count_values_for(absorb_formula, 'w', wavelens, g)
 	
	wavelens = [x*10**-9 for x in xrange(300, 1100, wave_step)]
	tr_chart = Chart(name=u"T", x=wavelens, y=tr_values1 + tr_values2 + tr_values3)
	ref_chart = Chart(name=u"R", x=wavelens, y=ref_values1 + ref_values2 + ref_values3)
# 	absorption_chart = Chart(name=u"A", x=wavelens, y=absorption1 + absorption2 + absorption3)
	return tr_chart, ref_chart, None
	
	
if __name__ == '__main__':
	argus = {'N1': 1, 'N2': 2.05, 'N3': 1.5, 'phi': 0, 'h': 210*10**-9}
	tr_chart, ref_chart, abs_chart = main(argus)
	summ = build_absorption_chart(tr_chart, ref_chart)
# 	title = "T(0) R(9) formulas, N1:{N1} N2:{N2}+k N3:{N3}, thickness: {h}m".format(**argus)
	show_spectrums(tr_chart, ref_chart, abs_chart, summ)
# 	exp_tr_chart = read_sf('data/ITO_T1.sf')
# 	exp_ref_chart = read_sf('data/ITO_R1_09deg_real.sf')
# 	show_charts(tr_chart, ref_chart, abs_chart, exp_tr_chart, exp_ref_chart, title=title, y_range=(0, 100))
