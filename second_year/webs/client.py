# -*- coding: utf-8 -*-

from os.path import basename, getsize, exists, isfile
from server import HOST, PORT
from socket import SHUT_WR, create_connection
from sys import argv


class Client:
	def __init__(self, filename, host=HOST, port=PORT):
		self.host = host
		self.port = int(port)
		self.socket = None
		self.connection = False
		self.filename = filename if isfile(filename) else None
		self.filesize = getsize(filename) if exists(filename) else 0
		self.byteat = 1024
		
	def run(self):
		if not self.filename:
			print "Is not a file."
			return None
		
		elif not self.filesize:
			print "No such file or directory: {}".format(self.filename)
			return None

		self.connect()
		self.send_message(body="recv|{}|{}".format(
				self.filename,
				self.filesize,
		))
		
		msg_accept = self.recieve_message()
		if msg_accept and msg_accept[0] == "ready":
			self.send_file()
		
		msg_result = self.recieve_message() if msg_accept else None
		if msg_result:
			print msg_result[0]

		self.close()

	def connect(self):
		print "Connecting to server {}:{}".format(
				self.host,
				self.port
		)

		try:
			self.socket = create_connection((self.host, self.port))
			self.connection = True
			print "Connection established."

		except:
			print "Connection failed."

	def recieve_message(self):
		if not self.connection:
			return None
		
		body = self.socket.recv(self.byteat)
		# print "Recieved message '{}'".format(body)
		
		if body.startswith("msg:"):
			return body[4:].split("|")

		else:
			print "Got unknown message: {}".format(body)
			return None

	def send_message(self, body):
		# print "Sending message 'msg:{}'".format(body)
		if self.connection:
			self.socket.send("msg:{}".format(body))

	def send_file(self):
		if not self.connection:
			return None

		print "Sending the file {}".format(self.filename)
		
		with open(self.filename, 'rb') as file:
			data = file.read(self.byteat)
			
			while data:
				self.socket.send(data)
				data = file.read(self.byteat)
				# print ".",
		
		print "done."

	def close(self):
		if self.connection:
			self.socket.close()
			self.connection = False


if __name__ == '__main__':
	if len(argv) == 2:
		client = Client(argv[1])
		client.run()
