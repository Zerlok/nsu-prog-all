from datetime import datetime


def show_duration(show_args_kwargs=False):
	def wrapper(function):
		def inner(*args, **kwargs):
			print function.__name__, "started."
			if show_args_kwargs and args:
				print "  agrs num: ", len(args)
			if show_args_kwargs and kwargs:
				print "  kwargs:   ", kwargs.keys()
			
			start = datetime.now()
			result = function(*args, **kwargs)
			end = datetime.now()
			print function.__name__, "duration: %f s." % (end-start).total_seconds()
			
			return result
		
		return inner
	return wrapper