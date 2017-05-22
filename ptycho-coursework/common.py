"""A python module with common funcitons"""


from argparse import Action as ParseAction


class InnerArgumentsParsing(ParseAction):
	def __init__(self, option_strings, dest, nargs=None, **kwargs):
		super(InnerArgumentsParsing, self).__init__(option_strings, dest, nargs, **kwargs)

	def __call__(self, parser, namespace, values, option_string=None, first=[True]):
		setattr(namespace, self.dest, dict(value.split('=')[:2] for value in values))


def count(func, iterable):
	cntr = 0
	for x in iterable:
		if func(x):
			cntr += 1
	return cntr


def clamp(val, min_val, max_val):
	return min(max(val, min_val), max_val)


def windowby(size, iterable):
	times = int(ceil(len(iterable) / size))
	return (iterable[i*size : (i+1)*size] for i in range(times))
