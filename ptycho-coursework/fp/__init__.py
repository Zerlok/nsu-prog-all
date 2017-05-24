from os import listdir
from os.path import dirname, basename, isfile, join
from abstracts import Factory


def _load_inner_modules(dirname):
	VALID_MODULES = ('py', 'pyc', 'pyo')

	def module_name(filename):
		return filename[:filename.rfind('.')]

	def module_tail(filename):
		return filename[filename.rfind('.')+1:]

	return [
			module_name(basename(name))
			for name in listdir(dirname)
			if isfile(join(dirname, name))
				and not name == '__init__.py'
				and module_tail(name) in VALID_MODULES
	]


__all__ = _load_inner_modules(dirname(__file__))


@Factory
class RecoveryMethods:
	pass


from . import *
# print(__all__)
print("Hi!")
