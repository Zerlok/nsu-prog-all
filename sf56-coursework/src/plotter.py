# -*-coding: utf-8-*-

import pyqtgraph as pyg
from pyqtgraph.Qt import QtGui, QtCore
from sys import flags as sysflags
from bisect import bisect

from common.mathem import Polinom
from operator import __add__, __sub__, __mul__, __div__


WINDOW_TITLE = "Charts View"
DEFAULT_PALETTE = (
	(55, 0, 173),
	(173, 31, 0),
	(66, 173, 0),
	(0, 173, 60),
	(133, 127, 0),
	(173, 0, 40),
	(0, 133, 61),
	(50, 133, 0),
	(0, 116, 133),
	(173, 147, 0),
)
DEFAULT_STYLES = (
	QtCore.Qt.SolidLine,
	QtCore.Qt.DashLine,
	QtCore.Qt.DotLine,
	QtCore.Qt.DashDotLine,
	QtCore.Qt.DashDotDotLine,
)


#===============================================================================
# Chart class definition, exceptions and extra functions.
#===============================================================================

class ChartInstanceRequired(Exception):
	def __init__(self, obj=None):
		super(ChartInstanceRequired, self).__init__("The chart instance required! '{}' is not a Chart!".format(obj))


class ChartsDifferentXRanges(Exception):
	def __init__(self, errors=None):
		super(ChartsDifferentXRanges, self).__init__("Charts have different X-range!")
		self.errors = errors


class Chart:
	"""Simple X-Y chart."""
	operand_values_types = (int, float)
	
	def __init__(self, name='', x=None, y=None):
		self.name = name
		self.axis_x = x or []
		self.axis_y = y or []
		self.length = len(self.axis_x)

	def __add__(self, s):
		add_chart = Chart(
				name = "{} + {}".format(self.name, s),
				x = list(self.axis_x),
		)
		
		if isinstance(s, self.operand_values_types):
			add_chart.axis_y = [y + s for y in self.axis_y]
			return add_chart
		
		if not isinstance(s, Chart):
			raise ChartInstanceRequired(s)
		
		if (len(self) != len(s)):
			raise ChartsDifferentXRanges({
					'a': len(self),
					'b': len(s),
			})
		
		add_chart.axis_y = map(__add__, self.axis_y, s.axis_y)
		return add_chart

	def __div__(self, s):
		div_chart = Chart(
				name = "{} / {}".format(self.name, s),
				x = list(self.axis_x),
		)
		
		if isinstance(s, self.operand_values_types):
			div_chart.axis_y = [y / s for y in self.axis_y]
			return div_chart
		
		elif not isinstance(s, Chart):
			raise ChartInstanceRequired(s)
		
		if len(self) != len(s):
			raise ChartsDifferentXRanges({
					'a': len(self),
					'b': len(s),
			})
		
		div_chart.axis_y = map(__div__, self.axis_y, s.axis_y)
		return div_chart
		
	def __len__(self):
		return self.length
	
	def __mul__(self, s):
		mul_chart = Chart(
				name = "{} * {}".format(self.name, s),
				x = list(self.axis_x),
		)
		
		if isinstance(s, self.operand_values_types):
			mul_chart.axis_y = [y * s for y in self.axis_y]
			return mul_chart
			
		if not isinstance(s, Chart):
			raise ChartInstanceRequired(s)
		
		if len(self) != len(s):
			raise ChartsDifferentXRanges({
					'a': len(self),
					'b': len(s),
			})
		
		mul_chart.axis_y = map(__mul__, self.axis_y, s.axis_y)
		return mul_chart
	
	def __rsub__(self, s):
		return Chart(
				name = "{} - {}".format(s, self.name),
				x = list(self.axis_x),
				y = [s - y for y in self.axis_y],
		)
	
	def __str__(self):
		return self.name

	def __sub__(self, s):
		sub_chart = Chart(
				name = "{} - {}".format(self, s),
				x = list(self.x),
		)
		
		if isinstance(s, self.operand_values_types):
			sub_chart.axis_y = [y - s for y in self.axis_y]
			return sub_chart
		
		if not isinstance(s, Chart):
			raise ChartInstanceRequired(s)
		
		if (len(self) != len(s)):
			raise ChartsDifferentXRanges({
					'a': len(self),
					'b': len(s),
			})
		
		sub_chart.axis_y = map(__sub__, self.axis_y, s.axis_y)
		return sub_chart

	def _append(self, x, y):
		'''Adds x and y back to chart.
		NOTE: x must be greater than all other x in spectrum!'''
		self.axis_x.append(x)
		self.axis_y.append(y)
		self.length += 1
		
	def copy(self):
		return Chart(self.name, list(self.axis_x), list(self.axis_y))
	
	def differentiate(self):
		diff = Chart("%s'" % self.name)
		diff._append(self.axis_x[0], 0)
		
		for i in xrange(1, len(self)):
			diff._append(self.axis_x[i], (self.axis_y[i] - self.axis_y[i - 1]) / (self.axis_x[i] - self.axis_x[i - 1]))
		
		return diff
	
	def get_xy(self, idx):
		return (self.axis_x[idx], self.axis_y[idx]) if -self.length <= idx < self.length else None
	
	def get_x(self, idx):
		return self.axis_x[idx] if -self.length <= idx < self.length else None
	
	def get_y(self, x):
		return self.axis_y[self.axis_x.index(x)] if x in self.axis_x else None
	
	def get_x_range(self):
		if not len(self):
			return (0, 0)
		
		return self.axis_x[0], self.axis_x[-1]
	
	def items(self):
		return [(self.axis_x[i], self.axis_y[i]) for i in xrange(len(self))]
	
	def insert(self, x, y):
		'''Inserts x and y into sorted by X value chart.'''
		idx = bisect(self.axis_x, x)
		self.axis_x.insert(idx, x)
		self.axis_y.insert(idx, y)
		self.length += 1
		
	def merge(self, another):
		self.axis_x.extend(another.axis_x)
		self.axis_y.extend(another.axis_y)
		self.length += another.length
	
	def set_x_range(self, x_range):
		'''Rebuilds chart with new x_range. NOTE: x_range must be sorted!'''
		old_axis_x, self.axis_x = self.axis_x, []
		old_axis_y, self.axis_y = self.axis_y, []
		self.length = 0
		
		for x in x_range:
			# x not in old_axis_x, because x out of old_axis_x range
			if x < old_axis_x[0]:
				self._append(x, old_axis_y[0])
			elif x > old_axis_x[-1]:
				self._append(x, old_axis_y[-1])
			
			# x is in old_axis_x range
			# old_axis_x[0] <= x <= old_axis_x[-1]
			elif x in old_axis_x:
				self._append(x, old_axis_y[old_axis_x.index(x)])
			
			# x not in old_axis_x list
			else:
				idx = bisect(old_axis_x, x)
				# range(idx-2, idx+2) == [idx-2, idx-1, *new*, idx, idx+1]
				known_y_values = [(old_axis_x[i], old_axis_y[i]) for i in xrange(idx-2, idx+2) if 0 <= i < len(old_axis_x)]
				# Approximate unknown y value by using the polinom of degree 4
				p = Polinom(*known_y_values)
				self._append(x, p.value(x))
		
		return self


def get_x_range_intersection(*charts):
	'''Returns the common range of X axis in given charts.'''
	def _get_maximal_min_and_minimal_max(*charts):
		maximal_min_x, minimal_max_x = charts[0].get_x_range()
		
		for chart in charts[1:]:
			min_x = chart.axis_x[0]
			max_x = chart.axis_x[-1]
			
			if min_x > maximal_min_x:
				maximal_min_x = min_x
			
			if max_x < minimal_max_x:
				minimal_max_x = max_x
			
			if minimal_max_x < maximal_min_x:
				break
		return (maximal_min_x, minimal_max_x) if (maximal_min_x <= minimal_max_x) else (0, 0)

	min_x, max_x = _get_maximal_min_and_minimal_max(*charts)
	x_range = set(charts[0].axis_x)

	for chart in charts[1:]:
		x_range.update([x for x in chart.axis_x if min_x < x < max_x])
		
	x_range = sorted(x_range)
	x_range.insert(0, min_x)
	x_range._append(max_x)
	
	return x_range


#===============================================================================
# PyQtGraph functions. 
#===============================================================================


def generate_palette(n):
	'''Generates n RGB palettes.'''
	if n <= len(DEFAULT_PALETTE):
		return DEFAULT_PALETTE[:n]
	
	p_size = 256
	p_max = 250
	p_min = 0
	p_step = (p_max - p_min) / n
	
	return [((p_size/n*17 - x) % p_size, (x + p_size/n*31) % p_size, (x + p_size/n*43) % p_size)
			for x in xrange(p_min, p_max, p_step)]


def pyqtgraph_app():
	'''Wraps the given funciton into Qt appliation. Gives created window to
	inner function.'''
	def _wrapper(function):
		def _inner(*args, **kwargs):
			# Taken from pyqtgraph module examples how to run Qt app.
			if (sysflags.interactive == 1) and hasattr(QtCore, 'PYQT_VERSION'):
				print "Can't run the application: unknown error!"
				print "Interactive: %s" % sysflags.interactive
				print "QtCore: %s" % QtCore
				return
			
			# Create a Qt application and show the charts.
			app = QtGui.QApplication([])

			# Setup pyqtgraph.
			pyg.setConfigOptions(antialias=True)
			pyg.setConfigOption('background', 'w')
			pyg.setConfigOption('foreground', 'k')

			# Create the plot window.
			qt_window = pyg.GraphicsWindow(title=WINDOW_TITLE)
			qt_window.resize(800, 500)
			function(qt_window, *args, **kwargs)
		
			# Run Qt app.
			print "Running %s function in Qt application..." % function.__name__ 
			app.exec_()
		
		return _inner
	return _wrapper


@pyqtgraph_app()
def show_charts(
			qt_window,
			*charts,
			**kwargs
):
	"""Shows given charts in Qt application (using pyqtgraph).
	charts are instances of Chart class.
	kwargs:
		title = "Plot"
		legend = True
		x_name = "X"
		y_name = "Y"
		x_units = None
		y_units = None
		x_range = None
		y_range = None
		palette = None"""
	# Get arguments from kwargs.
	title = kwargs.get('title')
	is_legend_on = kwargs.get('legend', True)
	x_axis_name = kwargs.get('x_name', "X")
	y_axis_name = kwargs.get('y_name', "Y")
	x_axis_units = kwargs.get('x_units')
	y_axis_units = kwargs.get('y_units')
	x_axis_range = kwargs.get('x_range')
	y_axis_range = kwargs.get('y_range')
	
	# Setup plot view.
	cssstyle = {'color': 'black'}
	plot_view = qt_window.addPlot(title=title)
	plot_view.showGrid(x=True, y=True)
	plot_view.setLabel('bottom', x_axis_name, units=x_axis_units, **cssstyle)
	plot_view.setLabel('left', y_axis_name, units=y_axis_units, **cssstyle)
	if is_legend_on:
		plot_view.addLegend()
	if x_axis_range:
		plot_view.setXRange(x_axis_range[0], x_axis_range[-1], padding=0)
	if y_axis_range:
		plot_view.setYRange(y_axis_range[0], y_axis_range[-1], padding=0)	

	# Add each chart to plot view.
	for i in xrange(len(charts)):
		if isinstance(charts[i], Chart):
			plot_view.plot(
					name = charts[i].name,
					x = charts[i].axis_x,
					y = charts[i].axis_y,
					pen = pyg.mkPen('k', width=1.5, style=DEFAULT_STYLES[i]),
			)
		else:
			print "Not Chart instance received:", charts[i]
