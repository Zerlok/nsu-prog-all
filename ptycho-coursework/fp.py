#!/usr/bin/python3

from numpy import (
	pi,
	sin, arctan, exp, angle, conjugate, sqrt,
	array, zeros, ones,
	fft
)
import optics as o
from abstracts import Factory


class LED:
	def __init__(self, lid, pos, k):
		self.id = lid
		self.pod = pos
		self.k = k

	def get_wavevec_slice(self, x_size, y_size, x_step, y_step, x_lim, y_lim):
		'''Returns slice of amplitude FT frequency range for specified led.'''
		# Center wavevecs.
		kxc = x_lim/2.0 + self.k[0]/x_step
		kyc = y_lim/2.0 + self.k[1]/y_step
		# Slices for x and y (lowest wavevec, highest wavevec, step)
		return (
				slice(
					max(round(kxc - x_size/2.0), 0),
					min(round(kxc + x_size/2.0), x_lim),
					1
				),
				slice(
					max(round(kyc - y_size/2.0), 0),
					min(round(kyc + y_size/2.0), y_lim),
					1
				)
		)


class LEDSphere:
	'''A lighting LED sphere for Reflective Fourier Ptychography.'''
	def __init__(self, begin_phi, end_phi, radius, wavevec):
		self.num = num
		self.gap = gap
		self.radius = radius
		self.width = (num-1) * gap

		hw = self.width / 2.0
		self.relative_k = [
				[(-wavevec*sin(arctan((x*gap - hw) / radius)), -wavevec*sin(arctan((y*gap - hw) / radius)))
					for x in range(num)
				] for y in range(num)
		]

	def __len__(self):
		return self.num * self.num

	def items(self):
		'''Iterator through every LED in grid (from top left to bottom right row by row).'''
		return (self.at(i, j) for j in range(self.num) for i in range(self.num))

	def walk(self):
		'''Walk through leds from central to border in spin'''
		hn = self.num // 2
		x, y = hn, hn
		yield self.at(x, y)
		
		dirs = ((0, 1), (-1, 0), (0, -1), (1, 0)) # Down, Left, Up, Right
		dn = 1 if (self.num % 2 == 0) else 0
		turn = 0
		steps_to_take = 1
		steps_left = steps_to_take

		for i in range(1, len(self)):
			if steps_left:
				steps_left -= 1
			else:
				dn += 1
				turn += 1
				steps_to_take += 1 if (turn % 2 == 0) else 0
				steps_left = steps_to_take-1
			
			d = dirs[dn % 4]
			x, y = x+d[0], y+d[1]
			yield self.at(x, y)

	def at(self, i, j):
		'''Returns params of specified LED.'''
		k = self.relative_k[i][j]
		return {
			'id': i + j*self.num,
			'col': i,
			'row': j,
			'kx': k[0],
			'ky': k[1],
		}


class LEDGrid:
	'''A lighting LED grid for Fourier Ptychography purposes.'''
	def __init__(self, num, gap, height, wavevec):
		self.num = num
		self.gap = gap
		self.height = height
		self.width = (num-1) * gap

		hw = self.width / 2.0
		self.relative_k = [
				[(-wavevec*sin(arctan((x*gap - hw) / height)), -wavevec*sin(arctan((y*gap - hw) / height)))
					for x in range(num)
				] for y in range(num)
		]

	def __len__(self):
		return self.num * self.num

	def items(self):
		'''Iterator through every LED in grid (from top left to bottom right row by row).'''
		return (self.at(i, j) for j in range(self.num) for i in range(self.num))

	def walk(self):
		'''Walk through leds from central to border in spin'''
		hn = self.num // 2
		x, y = hn, hn
		yield self.at(x, y)
		
		dirs = ((0, 1), (-1, 0), (0, -1), (1, 0)) # Down, Left, Up, Right
		dn = 1 if (self.num % 2 == 0) else 0
		turn = 0
		steps_to_take = 1
		steps_left = steps_to_take

		for i in range(1, len(self)):
			if steps_left:
				steps_left -= 1
			else:
				dn += 1
				turn += 1
				steps_to_take += 1 if (turn % 2 == 0) else 0
				steps_left = steps_to_take-1
			
			d = dirs[dn % 4]
			x, y = x+d[0], y+d[1]
			yield self.at(x, y)

	def at(self, i, j):
		'''Returns params of specified LED.'''
		k = self.relative_k[i][j]
		return {
			'id': i + j*self.num,
			'col': i,
			'row': j,
			'kx': k[0],
			'ky': k[1],
		}


class FourierPtychographySystem(o.System):
	def __init__(self, leds, *args, **kwargs):
		super(FourierPtychographySystem, self).__init__(*args, **kwargs)
		self.leds = leds

	def get_frequency_slice(self, led, x_size, y_size, x_step, y_step):
		'''Returns slice of amplitude FT frequency range for specified led.'''
		# Center wavevecs.
		kxc = x_size/2.0 + led['kx']/x_step
		kyc = y_size/2.0 + led['ky']/y_step
		# Slices for x and y (lowest wavevec, highest wavevec, step)
		return (
				slice(
					max(int(kxc - x_size*self.quality/2.0), 0),
					min(int(kxc + x_size*self.quality/2.0), x_size),
					1
				),
				slice(
					max(int(kyc - y_size*self.quality/2.0), 0),
					min(int(kyc + y_size*self.quality/2.0), y_size),
					1
				)
		)


@Factory
class Generators:
	pass


@Generators.product('simple-led-generator')
class LEDGenerator(FourierPtychographySystem):
	def run(self, ampl, phase=None):
		'''Creates a bundle of low resolution images data for each LED on grid.
		Returns an array with matrices (amplitude values).'''
		cols, rows = ampl.shape
		q2 = self.quality*self.quality
		x_step, y_step = self.get_wavevec_steps(cols, rows)
		
		self._start()
		ampl_ft = fft.fftshift(fft.fft2(ampl * self.get_phase(phase)))
		slices = (
				self.get_frequency_slice(led, cols, rows, x_step, y_step)
				for led in self.leds.items()
		)
		pupil = self.objective.generate_pass_mtrx(x_step, y_step)
		seq = array([
				abs(fft.ifft2(fft.ifftshift(q2 * ampl_ft[y_slice, x_slice] * pupil)))
				for (x_slice, y_slice) in slices
		])
		self._finish()

		return seq


@Factory
class RecoveryMethods:
	pass


@RecoveryMethods.product('fp')
class FPRecovery(FourierPtychographySystem):
	'''A simple Fourier Ptychography high resolution image recovery.'''
	def __init__(self, *args, **kwargs):
		super(FPRecovery, self).__init__(*args, **kwargs)
		self.q2 = self.quality * self.quality
		self.q_2 = 1.0 / self.q2

	def run(self, ampls, loops):
		cols, rows = (int(i / self.quality) for i in ampls[0].shape)
		params = self.get_iteration_params(cols, rows, ampls)

		self._start()
		for i in range(loops):
			for led in self.leds.walk():
				self.update_for_led(led, params)
		
		result = self.exclude_highres_data(params)
		self._finish()

		return result

	def get_iteration_params(self, x_img_size, y_img_size, ampls_sequence):
		x_step, y_step = self.get_wavevec_steps(x_img_size, y_img_size)
		ctf = self.objective.generate_ctf(x_step, y_step)
		return {
				'x_size': x_img_size,
				'y_size': y_img_size,
				'x_step': x_step,
				'y_step': y_step,
				'ctf': ctf,
				'ictf': 1.0 - ctf,
				'measured': ampls_sequence,
				'highres_ft': fft.fftshift(fft.fft2(ones((x_img_size, y_img_size)))),
		}

	def update_for_led(self, led, total_params):
		'''Step by step FP recovery flow for single led.'''
		led_params = self.build_led_params(led, total_params)
		led_params['old_lowres_ft'] = self.get_lowres_ft(led_params, total_params)
		led_params['lowres'] = self.get_lowres_ampl(led_params, total_params)
		led_params['measured_ft'] = self.get_measured_ft(led_params, total_params)
		led_params['new_highres_ft_part'] = self.get_enhanced_highres_ft_part(led_params, total_params)
		self.update_total_params(led_params, total_params)

	def exclude_highres_data(self, params):
		highres_data = fft.ifft2(fft.ifftshift(params['highres_ft']))
		return {
				'amplitude': abs(highres_data),
				'phase': angle(highres_data),
		}

	def build_led_params(self, led, total_params):
		x_slice, y_slice = self.get_frequency_slice(
				led = led,
				x_size = total_params['x_size'],
				y_size = total_params['y_size'],
				x_step = total_params['x_step'],
				y_step = total_params['y_step'],
		)
		return {
				'led': led,
				'x_slice': x_slice,
				'y_slice': y_slice,
				'old_highres_ft_part': None,
				'lowres': None,
				'measured_ft': None,
				'new_highres_ft_part': None,
		}

	def get_lowres_ft(self, led_params, total_params):
		'''Get highres FT part for current led.'''
		x_slice = led_params['x_slice']
		y_slice = led_params['y_slice']
		led_params['old_highres_ft_part'] = total_params['highres_ft'][y_slice, x_slice]
		return self.q2 * led_params['old_highres_ft_part'] * total_params['ctf']

	def get_lowres_ampl(self, led_params, total_params):
		'''Build the I_li (low-res amplitude).'''
		return fft.ifft2(fft.ifftshift(led_params['old_lowres_ft']))

	def get_measured_ft(self, led_params, total_params):
		'''Build the FT of I_mi with the known phase of I_li.'''
		lowres_phase = exp(1j * angle(led_params['lowres']))
		led_id = led_params['led']['id']
		measured_ampl = total_params['measured'][led_id]
		return fft.fftshift(fft.fft2(self.q_2 * measured_ampl * lowres_phase))

	def get_enhanced_highres_ft_part(self, led_params, total_params):
		'''Add new FT of I_hi to the old one.'''
		return total_params['ictf'] * led_params['old_highres_ft_part'] \
				+ total_params['ctf'] * led_params['measured_ft']

	def update_total_params(self, led_params, total_params):
		'''Update highres FT part with measures of current led.'''
		x_slice = led_params['x_slice']
		y_slice = led_params['y_slice']
		total_params['highres_ft'][y_slice, x_slice] = led_params['new_highres_ft_part']


@RecoveryMethods.product('epry-fp')
class EPRYRecovery(FPRecovery):
	'''Embded pupil function recovery.'''
	def get_iteration_params(self, *args, **kwargs):
		params = super(EPRYRecovery, self).get_iteration_params(*args, **kwargs)
		params['pupil'] = ones((params['x_size'], params['y_size']), dtype=complex)
		return params

	def get_lowres_ft(self, led_params, total_params):
		lowres_ft = super(EPRYRecovery, self).get_lowres_ft(led_params, total_params)
		return lowres_ft * total_params['pupil']

	def get_measured_ft(self, led_params, total_params):
		measured_ft = super(EPRYRecovery, self).get_measured_ft(led_params, total_params)
		return measured_ft * toal_params['ctf'] / total_params['pupil']

	def get_enhanced_highres_ft_part(self, led_params, total_params):
		mx_sq_pupil = (abs(toal_params['pupil'])**2).max()
		led_params['ft_difference'] = led_params['measured_ft'] - led_params['old_highres_ft_part']
		return led_params['old_highres_ft_part'] \
				+ conjugate(total_params['pupil']) / mx_sq_pupil * led_params['ft_difference']

	def update_total_params(self, led_params, total_params):
		super(EPRYRecovery, self).update_total_params(led_params, total_params)
		new_ampl_ft = led_params['new_highres_ft_part']
		mx_sq_new_highres = (abs(new_ampl_ft)**2).max()
		total_params['pupil'] += conjugate(new_ampl_ft) / mx_sq_new_highres * led_params['ft_difference']

	def exclude_highres_data(self, params):
		data = super(EPRYRecovery, self).exclude_highres_data(params)
		data['pupil'] = total_params['pupil']
		return data
