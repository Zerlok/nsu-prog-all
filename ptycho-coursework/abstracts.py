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

	class RepeatingRegistration(Exception):
		'''Exception for secondary try to register the product with the existing name.'''
		def __init__(self, factory, product):
			super(Factory.RepeatingRegistration, self).__init__(
					"'{}' factory has '{}' registered product already.".format(
						factory.__name__,
						product,
					)
			)
			self.factory = factory
			self.product = product

	def __init__(self, factory_cls):
		'''Make 'factory_cls' a factory using the ConcreteFactory class.'''
		class ConcreteFactory(factory_cls): # Create a new ConcreteFactory class definition at each __init__.
			'''A subclass of user's factory class. It will hold all registered products.'''
			__products__ = {} # Dict of registered products classes.
			__default_product_name__ = None

			class Product:
				'''A product class of user's product.'''
				def __init__(self, cls, description=None, args_types=None, kwargs_types=None):
					# print("Registering: {} {} {}".format(cls.__name__, args_types, kwargs_types))
					self.cls = cls
					self.args_types = args_types or []
					self.kwargs_types = kwargs_types or {}
					self.description = description or "{c} requires: ({sign})".format(
							c = cls.__doc__ or "<class {}>".format(cls.__name__),
							sign = ", ".join([
								*[a.__name__ for a in self.args_types],
								*["({}){}".format(val.__name__, key) for (key, val) in self.kwargs_types.items()],
							]) if self.args_types or self.kwargs_types else "nothing"
					)

				def validate_args(self, args):
					if not self.args_types:
						return args

					lim = len(self.args_types)
					return [
							self.args_types[i](arg) if i < lim else arg
							for (i, arg) in enumerate(args)
					]

				def validate_kwargs(self, kwargs):
					if not self.kwargs_types:
						return kwargs

					return {
							key: self.kwargs_types[key](value) \
								if key in self.kwargs_types else \
								value
							for (key, value) in kwargs.items()
					}

				def build(self, *args, **kwargs):
					'''Call __init__ of product's class with given arguments.'''
					# print("Building the {} with {} {}".format(self.cls.__name__, args, kwargs))
					return self.cls(*self.validate_args(args), **self.validate_kwargs(kwargs))

			@classmethod
			def registrate(cls, name, prod, **kwargs):
				'''Places prod class into the factory.'''
				if name not in cls.__products__:
					cls.__products__[name] = cls.Product(prod, **kwargs)
				else:
					raise Factory.RepeatingRegistration(self.__class__.__base__, name)

			@classmethod
			def set_default(cls, name):
				if not cls.__default_product_name__ and name in cls.__products__:
					cls.__default_product_name__ = name

			def names(self):
				'''Get all registered products.'''
				return self.__products__.keys()

			def default_name(self):
				'''Returns the default factory's product name.'''
				return self.__default_product_name__

			def has(self, name):
				'''Check if class was registered.'''
				return name in self.__products__

			def get(self, name=None):
				'''Return the product class if registered, otherwise throw an exception.'''
				try:
					return self.__products__[name or self.__default_product_name__]
				except KeyError:
					raise Factory.UnregisteredProduct(self.__class__.__base__, name)

			def get_creator(self, name, **current_kwargs):
				'''Return the product creator with extra arguments.'''
				product = self.get(name)
				def inner(*args, **kwargs):
					kwargs.update(current_kwargs)
					return product.build(*args, **kwargs)
				return inner

			def create(self, name, *args, **kwargs):
				'''Create a product object from factory.'''
				return self.get(name).build(*args, **kwargs)

			def describe(self, name):
				'''Get description of product.'''
				return self.get(name).description

			def describe_all(self, separator=" "):
				'''Get the desciptions of each product.'''
				return separator.join(
						"'{}' - {}".format(
							name,
							self.get(name).description,
						)
						for name in self.__products__
				)

		self.cls = ConcreteFactory

	def __call__(self, *args, **kwargs):
		'''Create a ConcreteFactory instance.'''
		return self.cls(*args, **kwargs)

	def product(self, name=None, default=False, **kwargs):
		'''Registrate the product into ConcreteFactory class.'''
		def inner(prod_cls):
			self.cls.registrate(
					name = name or prod_cls.__name__,
					prod = prod_cls,
					**kwargs
			)
			if default:
				self.cls.set_default(name)
			return prod_cls

		return inner
