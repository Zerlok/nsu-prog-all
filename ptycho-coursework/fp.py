#!/usr/bin/python3

from argparse import Action
from numpy import (
	pi,
	sin, cos, radians, arctan, arccos, exp, angle, conjugate, sqrt, conj,
	array, zeros, ones, meshgrid, arange,
	mean, any as np_any, sum as np_sum, std,
	fft,
	save as np_save,
)
import optics as o
from abstracts import Factory
from os.path import join as path_join
from settings import DEFAULT_LOWRES_FORMAT
		

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

	def draw(self, data, steps, radius):
		pos = tuple(int(p) for p in self.get_center_wavevec(steps, data.shape))
		hw = radius.shape[0]//2
		data[pos[1]-hw : pos[1]+hw, pos[0]-hw : pos[0]+hw] += radius

	def get_center_wavevec(self, steps, lims):
		# Center wavevecs.
		return (
				lims[0]/2.0 + self.k[0]/steps[0],
				lims[1]/2.0 + self.k[1]/steps[1]
		)

	def get_wavevec_slice(self, sizes, steps, lims):
		'''Returns slice of amplitude FT frequency range for specified led.'''
		kxc, kyc = self.get_center_wavevec(steps, lims)
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


class LEDSystem:
	def walk(self):
		raise NotImplementedError

	def at(self, i, j):
		raise NotImplementedError


@LEDSystems.product('grid', default=True, kwargs_types={'num': int, 'gap': float, 'height': float})
class LEDGrid(LEDSystem):
	'''A lighting LED grid for Fourier Ptychography purposes.'''
	def __init__(self, num, gap, height, wavevec):
		self.num = num
		self.gap = gap
		self.height = height
		self.width = (num-1) * gap
		hw = self.width / 2.0

		self.mtrx = [
				LED(
					lid = col + row * num,
					pos = (col, row),
					k = (
						-wavevec * sin(arctan((col*gap - hw) / height)),
						-wavevec * sin(arctan((row*gap - hw) / height))
					)
				)
				for row in range(num)
				for col in range(num)
		]

	def __len__(self):
		return self.num * self.num

	def __str__(self):
		return "<LED matrix {}x{}, gap {}, height {}>".format(
				self.num,
				self.num,
				self.gap,
				self.height,
		)

	def __iter__(self):
		return iter(self.mtrx)

	def get_radius(self, na):
		return na * sqrt(self.gap**2 + self.height**2) / self.gap

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
		return self.mtrx[row * self.num + column]


@LEDSystems.product('sphere', kwargs_types={'start': int, 'end': int, 'step': int})
class LEDSphere(LEDSystem):
	'''A lighting LED sphere for Reflective Fourier Ptychography.'''
	def __init__(self, start, end, step, wavevec):
		self.step = step
		self.ring_len = 360 // step

		self.sphere = [
				LED(
					lid = i + j * self.ring_len,
					pos = (psy, phi),
					k = (
						-wavevec * sin(radians(phi)) * cos(radians(psy)),
						-wavevec * sin(radians(phi)) * sin(radians(psy))
					)
				)
				for (j, phi) in enumerate(range(start, end+step, step))
				for (i, psy) in enumerate(range(360, 0, -step)) # ClockWise
		]

	def __len__(self):
		return len(self.sphere) * self.ring_len

	def __str__(self):
		return "<LED sphere (reflection) phi: {} -> {} by {}, total {}>".format(
				self.sphere[0].pos[1],
				self.sphere[-1].pos[1],
				self.step,
				len(self),
		)

	def __iter__(self):
		return iter(self.sphere)

	def get_radius(self, na):
		return na / sin(radians(self.step))

	def walk(self):
		'''Walk through leds in spin.'''
		return iter(self)

	def at(self, ring, hr):
		'''Returns LED at specified ring (from central to border) and hour ().'''
		return self.sphere[ring *self.ring_len + hr]


class FourierPtychographySystem(o.System):
	def __init__(self, leds, *args, **kwargs):
		super(FourierPtychographySystem, self).__init__(*args, **kwargs)
		self.leds = leds

	def count_leds_overlap(self):
		'''Returns the LEDs overlaping factor in Fourier space.'''
		r = self.leds.get_radius(self.objective.na)
		return (2.0*arccos(1.0/(2.0*r)) - sqrt(1.0 - (1.0/(2.0*r))**2) / r) / pi

	def count_total_coverage(self, size=(256, 256)):
		wavevec_steps = self.get_wavevec_steps(*size)
		radius = self.objective.generate_ctf(*wavevec_steps)
		data = zeros(size, dtype=bool)
		for led in self.leds:
			led.draw(data, wavevec_steps, radius)

		return np_sum(data) / (size[0] * size[1])

	def check_fourier_space_borders(self, low_size, high_size):
		'''Checks if all wavevector slices are inside the image size in the Fourier space.'''
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

	def get_leds_look(self, size, brightfield=False, darkfield=False, overlaps=False, factor=255):
		'''Returns the image of LEDs look as from microscope.'''
		wavevec_steps = self.get_wavevec_steps(*size)
		radius = array([[1, 1], [1, 1]]) \
				if not overlaps else \
				self.objective.generate_ctf(*wavevec_steps) * 1
		
		data = zeros(size, dtype=int)
		for led in self.leds:
			led.draw(data, wavevec_steps, radius)

		cut = zeros(size, dtype=float)
		steps = self.objective.generate_wavevec_steps(*size)
		if brightfield or overlaps:
			cut += self.objective.generate_ctf(*steps) * 1.0
		if darkfield or overlaps:
			cut += (1 - self.objective.generate_ctf(*steps)) * 0.5

		return o.pack_image(data*cut*factor, size)


@Factory
class Generators:
	'''Simulators of low resolution images obtaining as from optical microscope system.'''
	pass


class LowresGenerator(FourierPtychographySystem):
	def save_into_dir(self, result, dirname):
		print("WARNING: amplitudes will be saved into image files and will loose some quality!")
		low_images = [o.pack_image(data, result['size'], norm=True) for data in result['amplitudes']]
		filename = path_join(dirname, DEFAULT_LOWRES_FORMAT)
		for (i, img) in enumerate(low_images):
			img.save(filename.format(id=i))

	def save_into_npy(self, result, filename):
		np_save(filename, result['amplitudes'])


@Generators.product('simple')
class SimpleObjectiveView(LowresGenerator):
	'''Simple objective view generator.'''
	def __init__(self, *args, **kwargs):
		super(SimpleObjectiveView, self).__init__(*args, **kwargs)

	def _inner_run(self, ampl):
		result = super(SimpleObjectiveView, self)._inner_run(ampl)
		return {
				'ft': fft.fftshift(fft.fft2(ampl)),
				'slices': None,
				'lows_ft': None,
				'amplitudes': result['amplitude'],
				'size': result['amplitude'].shape,
				'len': 1,
		}

	def save_into_dir(self, result, dirname):
		img = o.pack_image(result['amplitudes'], result['size'], norm=True)
		img.save(path_join(dirname, "result.png"))


@Generators.product('lowres-generator', default=True)
class LEDGenerator(LowresGenerator):
	def _inner_run(self, ampl):
		'''Creates a bundle of low resolution images data for each LED on grid.
		Returns an array with matrices (amplitude values).'''
		q2 = self.quality*self.quality
		x_step, y_step = wavevec_steps = self.get_wavevec_steps(*ampl.shape)
		low_size = tuple(int(i * self.quality) for i in ampl.shape)
		
		# pupil = self.objective.generate_pass_mtrx(*self.objective.generate_wavevec_steps(*ampl.shape))
		pupil = self.objective.generate_pass_mtrx(x_step, y_step)
		ampl_ft = fft.fftshift(fft.fft2(ampl))
		slices = [
				led.get_wavevec_slice(
					sizes = low_size,
					steps = wavevec_steps,
					lims = ampl.shape
				)
				for led in self.leds
		]
		lows_ft = array([
				q2 * ampl_ft[y_slice, x_slice] * pupil
				for (x_slice, y_slice) in slices
		])
		ampls = array([
				abs(fft.ifft2(fft.ifftshift(low)))
				# abs(ampl_ft[y_slice, x_slice])
				for low in lows_ft
		])

		return {
				'ft': ampl_ft,
				'slices': slices,
				'lows_ft': lows_ft,
				'amplitudes': ampls,
				'size': low_size,
				'len': ampls.shape[0],
		}


@Factory
class RecoveryMethods:
	'''Fourier-Ptychography high resolution images recovery methods.'''
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
				'ft': self._params['highres_ft'],
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
				'ft': self._params['highres_ft'],
				'amplitude': abs(highres_data),
				'phase': angle(highres_data),
				'pupil': self._params['pupil'],
		}


@RecoveryMethods.product('adaptive-fp')
class AdaptiveFPRecovery(FPRecovery):
	def _init_recovery_iteration(self, iter_num):
		self._params['i'] = iter_num

	def _recover_for_led(self, led):
		x_slice, y_slice = self._params['slices'][led.id]
		old_highres_ft_part = self._params['highres_ft'][y_slice, x_slice]
		old_lowres_ft = self.q2 * old_highres_ft_part * self._params['ctf']
		old_lowres_ampl = fft.ifft2(fft.ifftshift(old_lowres_ft))
		
		# Measured I correction.
		measured_ampl = self._params['measured'][led.id]
		if self._params['i']:
			measured_ampl *= np_sum(abs(old_lowres_ampl)) / np_sum(measured_ampl)
		
		new_lowres_ampl = self.q_2 * measured_ampl * exp(1j * angle(old_lowres_ampl))
		new_lowres_ft = fft.fftshift(fft.fft2(new_lowres_ampl))

		self._params['highres_ft'][y_slice, x_slice] = \
				self._params['ictf'] * old_highres_ft_part \
				+ self._params['ctf'] * new_lowres_ft

	def _finish_recovery_iteration(self, iter_num):
		print("CI = {} at {} step.".format(self.count_convergence(), iter_num))
		pass

	def count_convergence(self):
		'''Count convergence index (measure the recovery goodness).'''
		conv = 0.0
		for led in self.leds:
			x_slice, y_slice = self._params['slices'][led.id]
			lowres_ampl = self._params['highres_ft'][y_slice, x_slice]
			measured_ampl = self._params['measured'][led.id]
			conv += mean(measured_ampl) / np_sum(abs(lowres_ampl - measured_ampl))

		return conv
