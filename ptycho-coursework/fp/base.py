#!/usr/bin/python3

from numpy import (
	pi,
	sin, cos, radians, arctan, arccos, exp, angle, conjugate, sqrt, conj,
	array, zeros, ones,
	mean, sum as np_sum, std,
	fft
)
from optics import System as OpticalSystem
from abstracts import Factory


class LED:
	def __init__(self, lid, pos, k):
		self.id = lid
		self.pos = pos
		self.k = k

	def __str__(self):
		return "<LED#{:03}: pos={} k=({:.2f}, {:.2f})>".format(
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


@LEDSystems.product('grid', default=True, kwargs_types={'num': int, 'gap': float, 'height': float})
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
					pos = (col, row),
					k = (
						-wavevec * sin(arctan((col*gap - hw) / height)),
						-wavevec * sin(arctan((row*gap - hw) / height))
					)) for col in range(num)
				]
				for row in range(num)
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
						-wavevec * sin(radians(phi)) * cos(radians(psy)),
						-wavevec * sin(radians(phi)) * sin(radians(psy))
					))
					for (i, psy) in enumerate(range(360, 0, -psy_step)) # ClockWise
				]
				for (j, phi) in enumerate(range(start, end+step, step))
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


class FourierPtychographySystem(OpticalSystem):
	def __init__(self, leds, *args, **kwargs):
		super(FourierPtychographySystem, self).__init__(*args, **kwargs)
		self.leds = leds

	def count_leds_overlap(self):
		r = self.objective.na * sqrt(self.leds.gap**2 + self.leds.height**2) / self.leds.gap
		r_1 = 1.0 / r
		r2_1 = 0.5 * r_1
		r2_2 = r2_1 * r2_1
		# print("R_led={:.3f}, NA={:.3f}".format(r, self.objective.na))
		return (2*arccos(r2_1) - r_1 * sqrt(1 - r2_2)) / pi

	def check_fourier_space_borders(self, low_size, high_size):
		steps = self.get_wavevec_steps(*high_size)
		for led in self.leds.walk():
			sl = led.get_wavevec_slice(
					sizes = low_size,
					steps = steps,
					lims = high_size,
			)
			sl = tuple(int(round(s.stop - s.start) / s.step) for s in sl)
			if sl != low_size:
				print("Failed to get FT slice for led: {}, images: low {}, high {}, slice {}".format(
						led,
						low_size,
						high_size,
						sl,
				))
				return False

		return True


@Factory
class Generators:
	pass


@Generators.product('simple-lowres-generator', default=True)
class LEDGenerator(FourierPtychographySystem):
	def _inner_run(self, ampl):
		'''Creates a bundle of low resolution images data for each LED on grid.
		Returns an array with matrices (amplitude values).'''
		q2 = self.quality*self.quality
		x_step, y_step = wavevec_steps = self.get_wavevec_steps(*ampl.shape)
		low_size = tuple(int(i * self.quality) for i in ampl.shape)
		
		ampl_ft = fft.fftshift(fft.fft2(ampl))
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

		return seq


@Factory
class RecoveryMethods:
	pass


@RecoveryMethods.product('fp', default=True, kwargs_types={'loops': int})
class FPRecovery(FourierPtychographySystem):
	'''A simple Fourier Ptychography high resolution image recovery.'''
	def __init__(self, loops, *args, **kwargs):
		super(FPRecovery, self).__init__(*args, **kwargs)
		self.loops = loops
		self.q2 = self.quality * self.quality
		self.q_2 = 1.0 / self.q2

	def _inner_run(self, ampls):
		self._init_recovery(ampls)
		for i in range(self.loops):
			self._init_recovery_iteration(i)
			for led in self.leds.walk():
				self._recover_for_led(led)
			self._finish_recovery_iteration(i)

		return self._finish_recovery()

	def _init_recovery(self, ampls):
		'''Initial method to build FP data before process started.'''
		lowres_size = ampls[0].shape
		highres_size = tuple(int(i / self.quality) for i in lowres_size)
		steps = self.get_wavevec_steps(*highres_size)
		ctf = self.objective.generate_ctf(*steps)
		self._params = {
				'lowres_size': lowres_size,
				'steps': steps,
				'ctf': ctf,
				'ictf': 1.0 - ctf,
				'measured': ampls,
				'highres_ft': fft.fftshift(fft.fft2(ones(highres_size))),
				'highres_size': highres_size,
				'slices': [
					led.get_wavevec_slice(
						sizes = lowres_size,
						steps = steps,
						lims = highres_size,
					)
					for led in self.leds
				]
		}

	def _init_recovery_iteration(self, iter_num):
		'''Initial method to build FP iteration data (for every loop).'''
		pass

	def _recover_for_led(self, led):
		'''4 steps of FP recovery flow for single led.'''
		# 1st - Get highres FT part for current led.
		x_slice, y_slice = self._params['slices'][led.id]
		old_highres_ft_part = self._params['highres_ft'][y_slice, x_slice]
		old_lowres_ft = self.q2 * old_highres_ft_part * self._params['ctf']

		# 2nd - Build the I_li (low-res amplitude).
		old_lowres_ampl = fft.ifft2(fft.ifftshift(old_lowres_ft))
		
		# 3rd - Build the FT of I_mi with the known phase of I_li.
		new_lowres_ampl = self.q_2 * self._params['measured'][led.id] * exp(1j * angle(old_lowres_ampl))
		new_lowres_ft = fft.fftshift(fft.fft2(new_lowres_ampl))

		# 4th - Add new FT of I_hi to the old one.
		self._params['highres_ft'][y_slice, x_slice] = \
				self._params['ictf'] * old_highres_ft_part \
				+ self._params['ctf'] * new_lowres_ft

	def _finish_recovery_iteration(self, iter_num):
		'''Finish FP recovery iteration.'''
		pass

	def _finish_recovery(self):
		'''Last method of the FP recovery to build final data.'''
		highres_data = fft.ifft2(fft.ifftshift(self._params['highres_ft']))
		return {
				'amplitude': abs(highres_data),
				'phase': angle(highres_data),
		}


@RecoveryMethods.product('epry-fp')
class EPRYRec(FPRecovery):
	def __init__(self, *args, **kwargs):
		super(EPRYRec, self).__init__(*args, **kwargs)
		self.alpha = 1.0
		self.beta = 1.0

	def _init_recovery(self, ampls):
		super(EPRYRec, self)._init_recovery(ampls)
		self._params['pupil'] = ones(self._params['lowres_size'], dtype=complex)

	def _recover_for_led(self, led):
		transfer = self._params['ctf'] * self._params['pupil']

		x_slice, y_slice = self._params['slices'][led.id]
		old_highres_ft_part = self._params['highres_ft'][y_slice, x_slice]
		old_lowres_ft = old_highres_ft_part * transfer;
		old_lowres_ampl = fft.ifft2(fft.ifftshift(old_lowres_ft));
		
		new_lowres_ampl = self.q_2 * self._params['measured'][led.id] * exp(1j * angle(old_lowres_ampl));
		new_lowres_ft = fft.fftshift(fft.fft2(new_lowres_ampl));
		
		ft_diff = (new_lowres_ft - old_lowres_ft)
		new_highres_ft_part = old_highres_ft_part \
				+ self.alpha * (conj(transfer) / (abs(transfer)**2).max()) * ft_diff;
		self._params['highres_ft'][y_slice, x_slice] = new_highres_ft_part
		self._params['pupil'] \
				+= self.beta * (conj(new_highres_ft_part) / (abs(new_highres_ft_part)**2).max()) * ft_diff;

	def _finish_recovery(self):
		'''Last method of the FP recovery to build the final data.'''
		highres_data = fft.ifft2(fft.ifftshift(self._params['highres_ft']))
		return {
				'amplitude': abs(highres_data),
				'phase': angle(highres_data),
				'pupil': self._params['pupil'],
		}
