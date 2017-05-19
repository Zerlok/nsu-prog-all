#!/usr/bin/python3

from PIL import Image as PILImage
from numpy import (
	pi,
	sqrt, sin, arctan, ceil, mean,
	exp, log, real, imag, angle,
	array, arange, random,
	meshgrid,
	fft,
)
from time import time
from abstracts import Factory


IMG_MODE = "L"


def add_noise(data):
	return data + (random.random(data.shape) * 0.6 - 0.3)


def get_amplitude(data, as_matrix=True):
	'''Returns a matrix with the amplitudes of the image, otherwise returns an array.'''
	return array([array([sqrt(val) for val in row]) for row in data]) \
			if as_matrix else \
			array([sqrt(val) for row in data for val in row])


def get_intensity(data, as_matrix=True):
	'''Returns a matrix of the intensities of the data, otherwise returns an array.'''
	return array([array([val*val for val in row]) for row in abs(data)]) \
			if as_matrix else \
			array([val*val for row in abs(data) for val in row])


def normalize(data, val):
	ratio = val / data.max()
	return data * ratio


def load_image(filename, dtype=None):
	'''Returns the image data of specified type.
	* 'amplitude' - image amplitude data matrix
	* 'intensity' - image intensity data matrix
	* otherwise, 'None' by default - image object'''

	img = PILImage.open(filename).convert(mode=IMG_MODE)
	if dtype == 'A' or dtype == 'amplitude':
		return get_amplitude(array(img))
	elif dtype == 'I' or dtype == 'intensity':
		return array(img)
	else:
		return img


def pack_image(data, size, dtype=None, norm=False):
	def color(val):
		return min(max(round(val), 0), 255)

	if dtype == 'A' or dtype == 'amplitude':
		img_data = get_amplitude(data)
	elif dtype == 'I' or dtype == 'intensity':
		img_data = get_intensity(data)
	else:
		img_data = data

	if norm:
		img_data = normalize(img_data, 255)

	img = PILImage.new(IMG_MODE, size)
	img.putdata(
			[color(val) for row in img_data for val in row] \
			if len(data.shape) == 2 else \
			[color(val) for val in img_data]
	)
	return img


@Factory
class Objectives:
	pass


@Objectives.product('simple', default=True)
class Objective:
	def __init__(self, k, k_lim, NA):
		self.k = k
		self.k_lim = k_lim
		self.na = NA
		self.cutoff_freq = self.na * self.k

	def __str__(self):
		return "<Objective NA: {}>".format(self.na)

	def generate_wavevec_array(self, x_step, y_step):
		kx = arange(-self.k_lim, self.k_lim, x_step)
		ky = arange(-self.k_lim, self.k_lim, y_step)
		return meshgrid(kx, ky)

	def generate_pass_mtrx(self, x_step, y_step):
		'''The simple objective (just CTF).'''
		return self.generate_ctf(x_step, y_step)

	def generate_ctf(self, x_step, y_step):
		'''Generate Coherent Transfer Function matrix.'''
		kx_array, ky_array = self.generate_wavevec_array(x_step, y_step)
		return (kx_array*kx_array + ky_array*ky_array) < self.cutoff_freq*self.cutoff_freq
	
	def simulate(self, ampl):
		x_size, y_size = ampl.shape
		mtrx = self.generate_pass_mtrx(
				x_step = 2*self.k_lim/x_size,
				y_step = 2*self.k_lim/y_size,
		)
		ampl_ft = fft.fftshift(fft.fft2(ampl))
		out_ampl_ft = mtrx * ampl_ft
		return fft.ifft2(fft.ifftshift(out_ampl_ft))

	def show(self, x_size, y_size):
		img = pack_image(
				data = self.generate_pass_mtrx(
					x_step = 2*self.k_lim/x_size,
					y_step = 2*self.k_lim/y_size,
				),
				size = (x_size, y_size),
				norm = True,
		)
		img.show()


@Objectives.product('complex')
class PupilObjective(Objective):
	'''A fading out pupil.'''
	def __init__(self, *args, **kwargs):
		self.z = kwargs.pop('z')
		super(Objective, self).__init__(*args, **kwargs)

	def generate_pass_mtrx(self, x_step, y_step):
		kx_array, ky_array = self.generate_wavevec_array(x_step, y_step)
		kz_squared = (kx_array*kx_array + ky_array*ky_array)
		kz_diff_array = sqrt(1j * self.k*self.k - kz_squared)
		v1 = exp(self.z * real(kz_diff_array))
		v2 = exp(-self.z * abs(imag(kz_diff_array)))
		return v1 * v2 * (kz_squared < self.cutoff_freq*self.cutoff_freq)


class System:
	def __init__(self, wavelen, sample_size, quality, objective, NA):
		self.wavelen = wavelen
		self.k = 2 * pi / self.wavelen
		self.sample_size = sample_size
		self.pixel_size = self.sample_size * quality
		self.quality = quality
		self.set_objective(
				objective,
				NA = NA,
		)

	def __str__(self):
		return "<OpticSystem with {} objective>".format(self.objective)

	def _start(self):
		self._started_at = time()

	def _finish(self):
		self._finished_at = time()

	def print_run_duration(self):
		print("Duration is: {:.3f}ms".format((self._finished_at - self._started_at) * 1000))

	def get_wavevec_steps(self, img_x_size, img_y_size):
		'''Returns wavevec x and y steps for specified image size.'''
		return (
				2 * pi / (self.pixel_size * img_x_size),
				2 * pi / (self.pixel_size * img_y_size)
		)

	def set_objective(self, ObjCls, *args, **kwargs):
		kwargs.update({
				'k': self.k,
				'k_lim': pi / self.sample_size,
		})
		self.objective = ObjCls(*args, **kwargs)

	def get_phase(self, ampl=None):
		if ampl is None:
			return 1.0

		mx = ampl.max()
		return exp(1j * pi * ampl / mx)

	def run(self, ampl, phase=None):
		self._start()
		result = self.objective.simulate(ampl * self.get_phase(phase))
		self._finish()
		return {
				'amplitude': result,
		}
