#!/usr/bin/python3

from argparse import Action
from numpy import (
	pi,
	sin, cos, radians, arctan, exp, angle, conjugate, sqrt,
	array, zeros, ones,
	mean,
	fft
)
import optics as o
from abstracts import Factory


class LED:
	def __init__(self, lid, pos, k):
		self.id = lid
		self.pos = pos
		self.k = k

	def __str__(self):
		return "<LED#{:03}: {} ({:.2f}, {:.2f})>".format(
				self.id,
				self.pos,
				*self.k,
		)

	def get_wavevec_slice(self, sizes, steps, lims):
		'''Returns slice of amplitude FT frequency range for specified led.'''
		# Center wavevecs.
		kxc = lims[0]/2.0 + self.k[0]/steps[0]
		kyc = lims[1]/2.0 + self.k[1]/steps[1]
		# Safe slices for x and y (lowest wavevec, highest wavevec, step)
		return (
				slice(
					max(int(round(kxc - sizes[0]/2.0)), 0),
					min(int(round(kxc + sizes[0]/2.0)), lims[0]),
					1
				),
				slice(
					max(int(round(kyc - sizes[1]/2.0)), 0),
					min(int(round(kyc + sizes[1]/2.0)), lims[1]),
					1
				)
		)
		# Unsafe slices (no limits used).
		# (
		# 		slice(
		# 			int(round(kxc - sizes[0]/2.0)),
		# 			int(round(kxc + sizes[0]/2.0)),
		# 			1
		# 		),
		# 		slice(
		# 			int(round(kyc - sizes[1]/2.0)),
		# 			int(round(kyc + sizes[1]/2.0)),
		# 			1
		# 		)
		# )


@Factory
class LEDSystems:
	'''LEDs systems....'''
	pass


@LEDSystems.product('grid', default=True, kwargs_types={'num': int, 'gap': int, 'height': int})
class LEDGrid:
	'''A lighting LED grid for Fourier Ptychography purposes.'''
	def __init__(self, num, gap, height, wavevec):
		self.num = num
		self.gap = gap
		self.height = height
		self.width = (num-1) * gap
		hw = self.width / 2.0

		self.mtrx = [
				[LED(
					lid = col + row * num,
					pos = (x, y),
					k = (
						-wavevec*sin(arctan((x*gap - hw) / height)),
						-wavevec*sin(arctan((y*gap - hw) / height))
					)) for (col, x) in enumerate(range(num))
				]
				for (row, y) in enumerate(range(num))
		]

	def __len__(self):
		return self.num * self.num

	def __iter__(self):
		return (led for row in self.mtrx for led in row)

	def walk(self):
		'''Walk through leds from central to border in spin'''
		hn = self.num // 2
		x, y = hn, hn
		yield self.at(x, y)
		
		# Directions of steps.
		dirs = ((0, 1), (-1, 0), (0, -1), (1, 0)) # Down, Left, Up, Right
		dn = int(self.num % 2 == 0)
		turn = 0
		steps_to_take = 1
		steps_left = steps_to_take

		for i in range(1, len(self)):
			if steps_left: # Just make a step
				steps_left -= 1

			else: # Make step and turn
				dn += 1
				turn += 1
				steps_to_take += int(turn % 2 == 0)
				steps_left = steps_to_take-1
			
			# Get step direction and new coordinates
			d = dirs[dn % 4]
			x, y = x+d[0], y+d[1]
			yield self.at(x, y)

	def at(self, column, row):
		'''Returns LED at specified grid location.'''
		return self.mtrx[column][row]


@LEDSystems.product('sphere', args_types=[int, int, int])
class LEDSphere:
	'''A lighting LED sphere for Reflective Fourier Ptychography.'''
	def __init__(self, start, end, step, wavevec):
		psy_step = step
		self.ring_len = int(360 / psy_step)
		self.sphere = [
				[LED(
					lid = (i + j * self.ring_len),
					pos = (psy, phi),
					k = (
						-wavevec*sin(radians(phi))*cos(radians(psy)),
						-wavevec*sin(radians(phi))*sin(radians(psy))
					)) for (i, psy) in enumerate(range(360, 0, -psy_step)) # ClockWise
				] for (j, phi) in enumerate(range(start, end+step, step))
		]

	def __len__(self):
		return len(sphere) * self.ring_len

	def __iter__(self):
		return (led for ring in self.sphere for led in ring)

	def walk(self):
		'''Walk through leds in spin.'''
		return iter(self)

	def at(self, ring, hr):
		'''Returns LED at specified ring (from central to border) and hour ().'''
		return self.sphere[ring][hr]


class FourierPtychographySystem(o.System):
	def __init__(self, leds, *args, **kwargs):
		super(FourierPtychographySystem, self).__init__(*args, **kwargs)
		self.leds = leds

	@classmethod
	def count_RMSE(cls, ampl1, ampl2):
		diff = abs(ampl1 - ampl2)
		return sqrt(mean(diff * diff))


@Factory
class Generators:
	pass


@Generators.product('simple-lowres-generator', default=True)
class LEDGenerator(FourierPtychographySystem):
	def run(self, ampl, phase=None):
		'''Creates a bundle of low resolution images data for each LED on grid.
		Returns an array with matrices (amplitude values).'''
		q2 = self.quality*self.quality
		x_step, y_step = wavevec_steps = self.get_wavevec_steps(*ampl.shape)
		low_size = tuple(int(self.quality * i) for i in ampl.shape)
		
		self._start()
		ampl_ft = fft.fftshift(fft.fft2(ampl * self.get_phase(phase)))
		ampl_slices = (
				led.get_wavevec_slice(
					sizes = low_size,
					steps = wavevec_steps,
					lims = ampl.shape
				)
				for led in self.leds
		)
		pupil = self.objective.generate_pass_mtrx(x_step, y_step)
		seq = array([
				abs(fft.ifft2(fft.ifftshift(q2 * ampl_ft[y_slice, x_slice] * pupil)))
				# abs(ampl_ft[y_slice, x_slice])
				for (x_slice, y_slice) in ampl_slices
		])
		self._finish()

		return seq


@Factory
class RecoveryMethods:
	pass


@RecoveryMethods.product('fp', default=True)
class FPRecovery(FourierPtychographySystem):
	'''A simple Fourier Ptychography high resolution image recovery.'''
	def __init__(self, *args, **kwargs):
		super(FPRecovery, self).__init__(*args, **kwargs)
		self.q2 = self.quality * self.quality
		self.q_2 = 1.0 / self.q2

	def run(self, ampls, loops):
		self._start()
		params = self.get_iteration_params(ampls)
		for i in range(loops):
			for led in self.leds.walk():
				self.update_for_led(led, params)
		
		result = self.exclude_highres_data(params)
		self._finish()

		return result

	def get_iteration_params(self, ampls_sequence):
		lowres_size = ampls_sequence[0].shape
		highres_size = tuple(int(i / self.quality) for i in lowres_size)
		steps = self.get_wavevec_steps(*highres_size)
		ctf = self.objective.generate_ctf(*steps)
		return {
				'lowres_size': lowres_size,
				'steps': steps,
				'ctf': ctf,
				'ictf': 1.0 - ctf,
				'measured': ampls_sequence,
				'highres_ft': fft.fftshift(fft.fft2(ones(highres_size))),
				'highres_size': highres_size,
		}

	def update_for_led(self, led, total_params):
		'''Step by step FP recovery flow for single led.'''
		led_params = self.build_led_params(led, total_params)
		self.get_lowres_ft(led_params, total_params)
		self.get_lowres_ampl(led_params, total_params)
		self.get_measured_ft(led_params, total_params)
		self.get_enhanced_highres_ft_part(led_params, total_params)
		self.update_total_params(led_params, total_params)

	def exclude_highres_data(self, params):
		highres_data = fft.ifft2(fft.ifftshift(params['highres_ft']))
		return {
				'amplitude': abs(highres_data),
				'phase': angle(highres_data),
		}

	def build_led_params(self, led, total_params):
		return {
				'led': led,
				'old_highres_ft_part': None,
				'lowres': None,
				'measured_ft': None,
				'new_highres_ft_part': None,
				'slice': led.get_wavevec_slice(
					sizes = total_params['lowres_size'],
					steps = total_params['steps'],
					lims = total_params['highres_size'],
				),
		}

	def get_lowres_ft(self, led_params, total_params):
		'''Get highres FT part for current led.'''
		x_slice, y_slice = led_params['slice']
		led_params['old_highres_ft_part'] = total_params['highres_ft'][y_slice, x_slice]
		led_params['old_lowres_ft'] = self.q2 * led_params['old_highres_ft_part'] * total_params['ctf']

	def get_lowres_ampl(self, led_params, total_params):
		'''Build the I_li (low-res amplitude).'''
		led_params['lowres'] = fft.ifft2(fft.ifftshift(led_params['old_lowres_ft']))

	def get_measured_ft(self, led_params, total_params):
		'''Build the FT of I_mi with the known phase of I_li.'''
		lowres_phase = exp(1j * angle(led_params['lowres']))
		led_id = led_params['led'].id
		measured_ampl = total_params['measured'][led_id]
		led_params['measured_ft'] = fft.fftshift(fft.fft2(self.q_2 * measured_ampl * lowres_phase))

	def get_enhanced_highres_ft_part(self, led_params, total_params):
		'''Add new FT of I_hi to the old one.'''
		led_params['new_highres_ft_part'] = \
				total_params['ictf'] * led_params['old_highres_ft_part'] \
				+ total_params['ctf'] * led_params['measured_ft']

	def update_total_params(self, led_params, total_params):
		'''Update highres FT part with measures of current led.'''
		x_slice, y_slice = led_params['slice']
		total_params['highres_ft'][y_slice, x_slice] = led_params['new_highres_ft_part']


@RecoveryMethods.product('epry-fp')
class EPRYRecovery(FPRecovery):
	'''Embded pupil function recovery.'''
	def get_iteration_params(self, *args, **kwargs):
		params = super(EPRYRecovery, self).get_iteration_params(*args, **kwargs)
		params['pupil'] = ones(params['highres_size'], dtype=complex)
		return params

	def get_lowres_ft(self, led_params, total_params):
		super(EPRYRecovery, self).get_lowres_ft(led_params, total_params)
		led_params['old_lowres_ft'] *= total_params['pupil']

	# def get_measured_ft(self, led_params, total_params):
	# 	measured_ft = super(EPRYRecovery, self).get_measured_ft(led_params, total_params)
	# 	return measured_ft * toal_params['ctf'] / total_params['pupil']

	def get_enhanced_highres_ft_part(self, led_params, total_params):
		pupil = total_params['ctf'] * toal_params['pupil']
		mx_sq_pupil = (abs(pupil)**2).max()
		led_params['ft_difference'] = led_params['measured_ft'] - led_params['old_lowres_ft']
		led_params['new_highres_ft_part'] = \
				led_params['old_highres_ft_part'] \
				+ conjugate(pupil) / mx_sq_pupil * led_params['ft_difference']

	def update_total_params(self, led_params, total_params):
		super(EPRYRecovery, self).update_total_params(led_params, total_params)
		self.update_pupil(led_params, total_params)

	def update_pupil(self, led_params, total_params):
		new_ampl_ft = led_params['new_highres_ft_part']
		mx_sq_new_highres = (abs(new_ampl_ft)**2).max()
		total_params['pupil'] += conjugate(new_ampl_ft) / mx_sq_new_highres * led_params['ft_difference']

	def exclude_highres_data(self, params):
		data = super(EPRYRecovery, self).exclude_highres_data(params)
		data.update({
				'pupil': total_params['pupil'],
		})
		return data
