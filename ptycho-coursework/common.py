"""A python module with common funcitons"""


from PIL import Image
from numpy import array, sqrt, ceil


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


def load_image(filename):
	return Image.open(filename).convert(mode="L")


def as_image(data, size, mode="L", to_intensity=True):
	img = Image.new(mode, size)

	if to_intensity:
		img_data = intensity(data, axis=1)
	elif len(data.shape) == 2:
		img_data = array([val for row in data for val in row])
	else:
		img_data = data

	img.putdata(img_data)
	return img


def amplitude(img, axis=2):
	if axis == 2:
		return array([array([sqrt(val) for val in row]) for row in array(img)])
	else:
		return array([sqrt(val) for row in array(img) for val in row])


def intensity(data, axis=1, width=0):
	if len(data.shape) == 2:
		return array([abs(val)**2 for row in data for val in row]) \
				if axis == 1 else \
				array([array([abs(val)**2 for val in row]) for row in data])
	else:
		return array([abs(val)**2 for val in data]) \
				if not width else \
				array([array(row) for row in windowby(width, data)])
