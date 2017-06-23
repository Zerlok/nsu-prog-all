#!/usr/bin/python3

from PIL import Image as PILImage
from numpy import (
	pi,
	sqrt, sin, arctan, ceil, mean, std,
	exp, log, real, imag, angle,
	array, arange, random,
	meshgrid,
	fft,
	save as np_save
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
	* 'A' or 'amplitude' - image amplitude data matrix
	* 'I' or 'intensity' - image intensity data matrix
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
	'''A simple basic objective.'''
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

	def generate_wavevec_steps(self, x_size, y_size):
		return (
				2.0 * self.k_lim / x_size,
				2.0 * self.k_lim / y_size,
		)

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
				*self.generate_wavevec_steps(x_size, y_size)
		)
		ampl_ft = fft.fftshift(fft.fft2(ampl))
		out_ampl_ft = mtrx * ampl_ft
		return fft.ifft2(fft.ifftshift(out_ampl_ft))

	def show(self, x_size, y_size):
		img = pack_image(
				data = self.generate_pass_mtrx(
					*self.generate_wavevec_steps(x_size, y_size)
				),
				size = (x_size, y_size),
				norm = True,
		)
		img.show()

	def save(self, filename, x_size, y_size):
		np_save(filename, self.generate_pass_mtrx(
				*self.generate_wavevec_steps(x_size, y_size)
		))


@Objectives.product('complex', kwargs_types={'z': float})
class PupilObjective(Objective):
	'''A fading out pupil.'''
	def __init__(self, z, *args, **kwargs):
		super(PupilObjective, self).__init__(*args, **kwargs)
		self.z = z

	def generate_pass_mtrx(self, x_step, y_step):
		kx_array, ky_array = self.generate_wavevec_array(x_step, y_step)
		kz_squared = (kx_array*kx_array + ky_array*ky_array)
		kz_diff_array = sqrt(self.k*self.k - kz_squared)
		v1 = exp(1j * self.z * real(kz_diff_array))
		v2 = exp(-self.z * abs(imag(kz_diff_array)))
		return v1 * v2 * (kz_squared < self.cutoff_freq*self.cutoff_freq)
		# return v1 * v2 * self.generate_ctf(x_step, y_step)
		# return v1 * v2


class System:
	@classmethod
	def standardize(cls, data):
		return (data - mean(data)) / std(data)

	@classmethod
	def count_RMSE(cls, data1, data2, do_std=True):
		if do_std:
			data1 = cls.standardize(data1)
			data2 = cls.standardize(data2)

		diff = abs(data1 - data2)
		return sqrt(mean(diff * diff))

	@classmethod
	def count_NRMSE(cls, data1, data2):
		diff = abs(data1 - data2)
		mn, mx = diff.min(), diff.max()
		return sqrt(mean(diff * diff)) / (mx - mn)

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
		return "<OpticalSystem with {} objective>".format(self.objective)

	def get_wavevec_steps(self, img_x_size, img_y_size):
		'''Returns wavevec x and y steps for specified image size.'''
		return (
				2.0 * pi / (self.pixel_size * img_x_size),
				2.0 * pi / (self.pixel_size * img_y_size)
		)

	def set_objective(self, cls, *args, **kwargs):
		kwargs.update({
				'k': self.k,
				'k_lim': pi / self.sample_size,
		})
		self.objective = cls(*args, **kwargs)

	def get_phase(self, ampl=None):
		if ampl is None:
			return 1.0

		mx = ampl.max()
		return exp(1j * pi * ampl / mx)

	def run(self, ampl, phase=None):
		ampl = ampl * self.get_phase(phase)
		start = time()
		result = self._inner_run(ampl)
		self.duration = (time() - start) * 1000 # ms
		return result

	def _inner_run(self, ampl):
		return {
				'amplitude': self.objective.simulate(ampl),
				'size': ampl.shape,
		}
