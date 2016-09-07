#!/usr/bin/python

"""lab2 - file transffering.

Usage:
	--server [*host] [*port] - start the server.
	--client [path/to/file] [*host] [*port] - start the client.

	* - optional flag
"""

from client import Client
from server import Server
from sys import argv


if __name__ == '__main__':
	if '--server' in argv:
		server = Server(*argv[2:])
		server.run()
	
	elif '--client' in argv and len(argv) > 2:
		client = Client(*argv[2:])
		client.run()

	else:
		print __doc__
