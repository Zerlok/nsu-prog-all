from numpy import (
	pi,
	sin, cos, radians, arctan, arccos, exp, angle, conjugate, sqrt, conj,
	array, zeros, ones,
	mean, sum as np_sum, std,
	fft
)
from .base import FPRecovery, RecoveryMethods


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
