from common import load_image, amplitude, count
from numpy import ndarray, sqrt, mean
import matplotlib.pyplot as plt


class ArrayErrors:
	SINGLE_VALUE_KEYS = ['min', 'med', 'max', 'low_rmsd', 'high_rmsd', 'mean_rmsd']

	def __init__(self, base_data, low_prcnt=30, high_prcnt=5):
		if not isinstance(base_data, ndarray):
			raise TypeError("a numpy array class as data required!")

		self.base_data = base_data
		self.low_limit = int(self.base_data.size / 100 * low_prcnt)
		self.high_limit = int(self.base_data.size / 100 * high_prcnt)
		self.half_len = base_data.size // 2

	def get_errors(self, data, *counters, procents=False):
		sorted_sq_diffs = sorted(val * val \
				for row in (self.base_data - data) \
				for val in row
			) if len(self.base_data.shape) == 2 else \
				sorted(val * val \
					for val in (self.base_data - data)
		)
		
		return {
				'min': sqrt(sorted_sq_diffs[0]),
				'med': sqrt(sorted_sq_diffs[self.half_len]),
				'max': sqrt(sorted_sq_diffs[-1]),
				'low_rmsd': sqrt(mean(sorted_sq_diffs[ : self.low_limit])),
				'high_rmsd': sqrt(mean(sorted_sq_diffs[-self.high_limit : ])),
				'mean_rmsd': sqrt(mean(sorted_sq_diffs)),
				'counters': [count(crit, sorted_sq_diffs) for crit in counters],
				'differences': sorted_sq_diffs,
		}

ERR_OUTPUT = """\
Compression: {}
Max error: {max:.2%}
Median error: {med:.2%}
The root mean squared error: {mean_rmsd:.2%}
Lowest {lp}% errors mean: {low_rmsd:.2%}
Highest {hp}% errors mean: {high_rmsd:.2%}
"""


def main():
	name = "jpeg/cameraman-low{}.jpg"
	low_res_indices = [5, 10, 15, 20, 25, 30, 40, 50, 70]
	# low_res_indices = [5, 25, 70]

	ampl1 = amplitude(load_image("jpeg/cameraman.jpg"))
	ampl_lows = [(i, amplitude(load_image(name.format(i)))) for i in low_res_indices]
	eps = 0.0001
	ampl1err = ArrayErrors(ampl1)

	msg_format = "{:02}	{:.5f}	{:.5f}	{:.5f}	{:.5f}	{:.5f}	{:.5f}"

	for (i, ampl2) in ampl_lows:
		errs = ampl1err.get_errors(ampl2, lambda x: sqrt(x) < eps)
		for key in ampl1err.SINGLE_VALUE_KEYS:
			errs[key] /= 255.0

		print(ERR_OUTPUT.format(i, lp=30, hp=5, **errs))
		# plt.semilogy(errs['differences'])

	# plt.grid(True)
	# plt.show()


if __name__ == '__main__':
	main()
