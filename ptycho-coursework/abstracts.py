#!/usr/bin/python3

class Factory:
	'''The abstract factory class. Can be used as a decorator, to define the new factory class.'''
	class UnregisteredProduct(Exception):
		'''Exception for unregistered products creation.'''
		def __init__(self, factory, product):
			super(Factory.UnregisteredProduct, self).__init__(
					"'{}' factory has no '{}' product.".format(
						factory.__name__,
						product,
					)
			)
			self.factory = factory
			self.product = product

	def __init__(self, fact_cls):
		'''Make 'fact_cls' a factory using the ConcreteFactory class.'''
		# Create a new ConcreteFactory class definition at each __init__.
		class ConcreteFactory(fact_cls):
			'''A subclass of user's factory class. It will hold all registered products.'''
			# Dict of registered products classes.
			__products__ = {}

			class Product:
				'''A product class of user's product.'''
				pass

			def keys(self):
				'''Get all registered products.'''
				return self.__products__.keys()

			def has(self, name):
				'''Check if class was registered.'''
				return name in self.__products__

			def get(self, name):
				'''Return the product class if registered, otherwise throw an exception.'''
				if self.has(name):
					return self.__products__[name]
				else:
					raise Factory.UnregisteredProduct(self.__class__.__base__, name)

			def create(self, name, *args, **kwargs):
				return self.get(name)(*args, **kwargs)

			def describe(self, name=None):
				return self.get(name).__doc__ if name else self.__class__.__doc__

		self.cls = ConcreteFactory

	def __call__(self, *args, **kwargs):
		'''Create a ConcreteFactory instance.'''
		return self.cls(*args, **kwargs)

	def product(self, name=None):
		'''Registrate the product into ConcreteFactory class.'''
		def inner(cls):
			self.cls.__products__[name] = cls
			return cls

		return inner
