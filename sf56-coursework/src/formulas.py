from sympy import symbols, sqrt, sin, cos, I, pi, exp, re

from common.decorators import show_duration
from plotter import Chart, show_charts


class TRFormulasGenerator:
	@staticmethod
	def get_clean(self):
		r12, r23, t12, t23, d = symbols("r12 r23 t12 t23 d")
# 		tr = (t12*t23*exp(I*d/2)) / (1 + (1 - t12)*(1 - t23)*exp(I*d))		# T from book UPDATED!
# 		tr = (t12*t23*exp(I*d/2)) / (1 - (1 + t12)*(1 - t23)*exp(I*d))		# T from book
# 		ref = r12 + (t12**2 * r23*exp(I*d)) / (1 + r12*r23*exp(I*d))		# R mine
		tr = ((t12*t23*exp(I*d/2)) / (1 + r12*r23*exp(I*d)))				# T mine
		ref = ((r12 + r23*exp(I*d)) / (1 + r12*r23*exp(I*d)))				# R from book
		return tr, ref
	
	@staticmethod
	def get_default(self):
		N1, N2, N3, wavelen, height = symbols("N1 N2 N3 w h")
		phi, phi2, phi3 = symbols("phi phi2 phi3")
		
		r12 = (N2*cos(phi) - N1*cos(phi2)) / (N2*cos(phi) + N1*cos(phi2))
		r23 = (N3*cos(phi2) - N2*cos(phi3)) / (N3*cos(phi2) + N2*cos(phi3))
		t12 = (2*N1*cos(phi)) / (N2*cos(phi) + N1*cos(phi2))
		t23 = (2*N2*cos(phi2)) / (N3*cos(phi2) + N2*cos(phi3))
		delta = (4*pi / wavelen) * height * N2 * cos(phi2)
		
		tr = ((t12*t23*exp(I*delta/2)) / (1 + r12*r23*exp(I*delta)))
		ref = ((r12 + r23*exp(I*delta)) / (1 + r12*r23*exp(I*delta)))
		return tr, ref
	
	@staticmethod
	@show_duration()
	def get_expanded():
		N1, N2, N3, wavelen, height, phi = symbols("N1 N2 N3 w h phi")
		
		r12 = ((-N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi))/(N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi)))
		t12 = (2*N1*N2*cos(phi)/(N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi)))
		r23 = ((-N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2))/(N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2)))
		t23 = (2*N2*N3*sqrt(-N1**2*sin(phi)**2 + N2**2)/(N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2)))
		delta = (4*pi / wavelen) * height * sqrt(N2**2 - N1**2 * sin(phi)**2)
		
		tr = ((t12*t23*exp(I*delta/2)) / (1 + r12*r23*exp(I*delta)))
		ref = ((r12 + r23*exp(I*delta)) / (1 + r12*r23*exp(I*delta)))
		return tr, ref
	
	@staticmethod
	@show_duration()
	def get_for_arguments(N1, N2, N3, wavelen, height, phi):
		r12 = ((-N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi))/(N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi)))
		t12 = (2*N1*N2*cos(phi)/(N1*sqrt(-N1**2*sin(phi)**2 + N2**2) + N2**2*cos(phi)))
		r23 = ((-N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2))/(N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2)))
		t23 = (2*N2*N3*sqrt(-N1**2*sin(phi)**2 + N2**2)/(N2**2*sqrt(-N1**2*sin(phi)**2 + N3**2) + N3**2*sqrt(-N1**2*sin(phi)**2 + N2**2)))
		delta = (4*pi / wavelen) * height * sqrt(N2**2 - N1**2 * sin(phi)**2)
		
		tr = ((t12*t23*exp(I*delta/2)) / (1 + r12*r23*exp(I*delta)))
		ref = ((r12 + r23*exp(I*delta)) / (1 + r12*r23*exp(I*delta)))
		return tr, ref


def to_intensity(amplitude):
	# Using re in case of the imaginary part in multiplying.
	# It's not zero value, because of the sympy calculation accuracy is not so good.
	return re(amplitude * amplitude.conjugate())


@show_duration()
def count_values_for(formula, key, x_arguments, valf=None):
	val = valf or (lambda x: x)
	result = [val(formula.evalf(subs={key: x})) for x in x_arguments]
	return result


@show_duration()
def build_T_R_charts(tr, ref, x_values):
	def to_value(x):
		return float(to_intensity(x)) * 100
	
	return (
		Chart(name='T', x=x_values, y=count_values_for(tr, 'w', x_values, to_value)),
		Chart(name='R', x=x_values, y=count_values_for(ref, 'w', x_values, to_value))
	)		


def show_T_R_charts(N1, N2, N3, phi, h, min_wave, max_wave, step):
	x_values = [x*10**-9 for x in xrange(min_wave, max_wave+step, step)]
	arguments = {'N1': N1, 'N2': N2, 'N3': N3, 'phi': phi, 'h': h}

	T, R = TRFormulasGenerator.get_expanded()
	tr = T.subs(arguments.items())
	ref = R.subs(arguments.items())

	tr_plot, ref_plot = build_T_R_charts(tr, ref, x_values)
	summ = tr_plot + ref_plot
	summ.name = "T + R"
	pointing1 = ref_plot + (tr_plot * N3)
	pointing1.name = "T + R*N3"
	pointing2 = ref_plot + (tr_plot * (N3 / N2))
	pointing2.name = "T + R*(N3/N2)"	
	title = "T R formulas for {phi} angle, N1:{N1} N2:{N2} N3:{N3}, plate thickness: {h}m".format(**arguments)
	show_charts(ref_plot, tr_plot, summ, pointing1, pointing2, title=title, y_range=(0, 100))


if __name__ == '__main__':
	arguments = {
			'N1': 1,
			'N2': 2,
			'N3': 1,
			'phi': 0,		#  0 degree.
# 			'phi': pi/4,	# 45 degree.
# 			'phi': pi*9/20,	# 81 degree.
			'h': 100*10**-9,
			'min_wave': 200,
			'max_wave': 6000,
			'step': 100,
	}
	show_T_R_charts(**arguments)
