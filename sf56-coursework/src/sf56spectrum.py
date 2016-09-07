# -*-coding: utf-8-*-
"""Python module to work with SF-56 spectrum files."""

from os.path import exists, isfile, basename
from re import compile as reg_compile, split as reg_split

from plotter import Chart, show_charts


SF_COMMENT='//'
SF_EXTENSION='.sf'
SF_SEPARATOR_PTRN=reg_compile(r'\s+')


def read_sf(filename, name=None):
	'''Reads spectrum file into dictionary.
	Note for sf files: first column value must be UNIQUE!'''
	spectrum = Chart(name or basename(filename))
	with open(filename, 'r') as sf_file:
		for row in sf_file:
			row = validate_sf_row(row)
			if row:
				columns = reg_split(SF_SEPARATOR_PTRN, row)
				spectrum.insert(float(columns[0])*10**-9, float(columns[1]))
	
	return spectrum


def validate_sf_row(row):
	'''Clears spaces chars and replaces commas to dots if given row is not a comment.'''
	return row.strip().replace(',', '.') if not row.startswith(SF_COMMENT) else None


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
		# TODO: Insert direct check for sf file (check some value or file type - text file).
	
	return True


def write_sf(spectrum, filename):
	'''Writes spectum into given file.'''
	with open(filename, 'w') as sf_file:
		for (x, y) in spectrum.items():
			sf_file.write("{}\t{}\n".format(x, y))


def show_spectrums(*spectrums, **kwargs):
	show_charts(*spectrums,
			x_name = u"\u03BB",
			x_units = u"м",
			y_name = u"I(\u03BB)",
			y_units = u"%",
			y_range = (-1, 101),
			**kwargs)