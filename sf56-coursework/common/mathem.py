from numpy import matrix
from numpy.linalg import det as determinant


class Polinom:
	def __init__(self, *cords):
		"""Solve linear equation system for polinom indices."""
		main_mtrx = matrix(
			[[co[0]**p for p in xrange(len(cords)-1, -1, -1)]
			for co in cords]
		)
		main_det = determinant(main_mtrx)
		
		matrices_dets = []
		for i in xrange(len(cords)):
			m = main_mtrx.copy()
			for j in xrange(len(cords)):
				m[j, i] = cords[j][1]
			 
			matrices_dets.append(determinant(m))
		
		self.indices = tuple(m_det / main_det for m_det in matrices_dets) if main_det else None
		self.length = len(self.indices) if self.indices else 0

	def value(self, x):
		return sum(self.indices[-i-1] * x**i
				for i in xrange(self.length-1, -1, -1)
		) if self.indices else None


def get_spectrum_polinom(spectrum, *indices):
	cords = []
	for i in indices:
		co = spectrum.get_xy(i)
		if co:
			cords._append(co)
	
	return Polinom(*cords)
