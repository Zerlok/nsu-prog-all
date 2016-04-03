"""Python module to work with SF-56 spectrum files."""

from os.path import exists, isfile, basename
from re import compile as reg_compile, split as reg_split
from bisect import bisect

from spectrummath import Polinom
from operator import __mul__, __div__


SF_COMMENT='//'
SF_EXTENSION='.sf'
SF_SEPARATOR_PTRN=reg_compile(r'\s+')


class SpectrumsDifferentLengths(Exception):
	def __init__(self, errors=None):
		super(SpectrumsDifferentLengths, self).__init__("Spectrums have different lengths!")
		self.errors = errors


class Spectrum:
	"""SF-56 spectrum class."""
	def __init__(self, name='', x=None, y=None):
		self.name = name
		self.axis_x = x or []
		self.axis_y = y or []
		self.length = len(self.axis_x)

	def __div__(self, s):
		div_spectrum = Spectrum(
				name = "{}-div-{}".format(self.name, s),
				x = list(self.axis_x),
		)
		
		if isinstance(s, int):
			div_spectrum.axis_y = [y / s for y in self.axis_y]
			return div_spectrum
		
		elif not isinstance(s, Spectrum):
			return None
		
		if len(self) != len(s):
			raise SpectrumsDifferentLengths({
					'a': len(self),
					'b': len(s),
			})
		
		div_spectrum.axis_y = map(__div__, self.axis_y, s.axis_y)
		return div_spectrum
		
	def __len__(self):
		return self.length
	
	def __mul__(self, s):
		mul_spectrum = Spectrum(
				name = "{}-mul-{}".format(self.name, s),
				x = list(self.axis_x),
		)
		
		if isinstance(s, int):
			mul_spectrum.axis_y = [y * s for y in self.axis_y]
			
		elif not isinstance(s, Spectrum):
			return None
		
		if len(self) != len(s):
			raise SpectrumsDifferentLengths({
					'a': len(self),
					'b': len(s),
			})
		
		mul_spectrum.axis_y = map(__mul__, self.axis_y, s.axis_y)
		return mul_spectrum
	
	def __str__(self):
		return self.name
	
	def append(self, x, y):
		'''Adds x and y back to spectrum.
		NOTE: x must be greater than all other x in spectrum!'''
		self.axis_x.append(x)
		self.axis_y.append(y)
		self.length += 1
		
	def copy(self):
		return Spectrum(self.name, list(self.axis_x), list(self.axis_y))
	
	def differentiate(self):
		diff = Spectrum("%s-diff" % self.name)
		diff.append(self.axis_x[0], 0)
		
		for i in xrange(1, len(self)):
			diff.append(self.axis_x[i], self.axis_y[i] - self.axis_y[i - 1])
		
		return diff
	
	def get_co(self, idx):
		return (self.axis_x[idx], self.axis_y[idx]) if -self.length <= idx < self.length else None
	
	def get_x(self, idx):
		return self.axis_x[idx] if -self.length <= idx < self.length else None
	
	def get_y(self, x):
		return self.axis_y[self.axis_x.index(x)] if x in self.axis_x else None
	
	def insert(self, x, y):
		'''Inserts x and y into sorted spectrum.'''
		idx = bisect(self.axis_x, x)
		self.axis_x.insert(idx, x)
		self.axis_y.insert(idx, y)
		self.length += 1
	
	def set_x_range(self, x_range):
		'''Rebuilds spectrum with new x_range. NOTE: x_range must be sorted!'''
		old_axis_x, self.axis_x = self.axis_x, []
		old_axis_y, self.axis_y = self.axis_y, []
		self.length = 0
		
		for x in x_range:
			# x not in old_spectrum.axis_x, because x out of old_spectrum.axis_x range
			if x < old_axis_x[0]:
				self.append(x, old_axis_y[0])
			elif x > old_axis_x[-1]:
				self.append(x, old_axis_y[-1])
			
			# old_spectrum.axis_x[0] <= x <= old_spectrum.axis_x[-1]
			elif x in old_axis_x:
				self.append(x, old_axis_y[old_axis_x.index(x)])
			
			# x not in old_spectrum.axis_x
			else:
				idx = bisect(old_axis_x, x)
				# [idx-2, idx-1, *new*, idx, idx+1] == range(idx-2, idx+2)
				self.append(x, Polinom(*[(old_axis_x[i], old_axis_y[i]) for i in xrange(idx-2, idx+2)]).value(x))


def get_x_range_intersection(*spectrums):
	'''Returns the common range of x axis in given spectrums.'''
	def _get_begin_and_end_of_x_range_intersection(*spectrums):
		total_min_x = spectrums[0].axis_x[0]
		total_max_x = spectrums[0].axis_x[-1]
		
		for spectrum in spectrums[1:]:
			min_x = spectrum.axis_x[0]
			max_x = spectrum.axis_x[-1]
			
			if min_x > total_min_x:
				total_min_x = min_x
			
			if max_x < total_max_x:
				total_max_x = max_x
			
			if total_max_x < total_min_x:
				break
		
		return (total_min_x, total_max_x) if (total_max_x >= total_min_x) else None

	min_x, max_x = _get_begin_and_end_of_x_range_intersection(spectrums) or (0, 0)
	x_range = set(spectrums[0].axis_x)

	for spectrum in spectrums[1:]:
		x_range.update([x for x in spectrum.axis_x if min_x < x < max_x])
		
	x_range = sorted(x_range)
	x_range.insert(0, min_x)
	x_range.append(max_x)
	
	return x_range


def read_sf(filename):
	'''Reads spectrum file into dictionary.
	Note for sf files: first column value must be UNIQUE!'''
	
	spectrum = Spectrum(basename(filename))
	with open(filename, 'r') as sf_file:
		for row in sf_file:
			row = validate_sf_row(row)
			if row:
				columns = reg_split(SF_SEPARATOR_PTRN, row)
				spectrum.insert(float(columns[0]), float(columns[1]))
	
	return spectrum


def validate_sf_files(filenames):
	'''Vaidates given files for existance and .sf extension. If invalid file found
	returns False, else everything is ok - True.'''
	for filename in filenames:
		if not exists(filename):
			print "Input error: %s file not found!" % filename
			return False

		elif not isfile(filename):
			print "Input error: %s is not a file!" % filename
			return False
		
		elif not filename.endswith(SF_EXTENSION):
			print "Input error: %s is not a .sf file!" % filename
			return False
	
	return True


def validate_sf_row(row):
	'''Clears spaces chars and replaces commas to dots if given row is not a comment.'''
	return row.strip().replace(',', '.') if not row.startswith(SF_COMMENT) else None


def write_sf(spectrum, filename):
	with open(filename, 'w') as sf_file:
		for i in xrange(len(spectrum)):
			sf_file.write("{}\t{}\n".format(*spectrum.get_co(i)))
