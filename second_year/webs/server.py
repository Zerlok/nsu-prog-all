# -*- coding: utf-8 -*-
from os import mkdir
from os.path import join, exists, basename, split as pathsplit
from socket import socket, gethostname, error as SocketError
from time import sleep


HOST = gethostname()
PORT = 1717
UPLOAD_DIR = 'uploads'


class Server:
	def __init__(self, host=HOST, port=PORT):
		self.host = host
		self.port = int(port)
		self.socket = socket()
		self.connection = None
		self.byteat = 1024
		
		if not exists(UPLOAD_DIR):
			mkdir(UPLOAD_DIR)

	def run(self):
		print "Running server on {}:{}, press 'Ctrl+C' to stop".format(
				self.host,
				self.port
		)
		self.socket.bind((self.host, self.port))

		try:
			self.socket.listen(5)
			while True:
				self.connection, address = self.socket.accept()
				print "{}:{} connected to server".format(*address)
				
				msg_fileheader = self.recieve_message() or []

				if (len(msg_fileheader) == 3
						and msg_fileheader[0] == 'recv'):
					self.send_message("ready")
					result = self.download_file(msg_fileheader[1], msg_fileheader[2])
					self.send_message("success" if result else "fail")

				self.connection.close()

		except KeyboardInterrupt:
			print "\nStopped!"

	def recieve_message(self):
		if not self.connection:
			return None

		body = self.connection.recv(self.byteat)

		if body.startswith("msg:"):
			return body[4:].split("|")

		else:
			print "Got unknown message: {}".format(body)
			return None

	def send_message(self, body):
		if self.connection:
			self.connection.send("msg:{}".format(body))

	def download_file(self, filename, file_size):
		if not self.connection:
			return None

		valid_filename = pathsplit(filename)[1]
		bytes_left = int(file_size)
		byteat = self.byteat

		if not valid_filename:
			return False

		print "Start receiving the file {} bytes".format(file_size),
		
		with open(join(UPLOAD_DIR, valid_filename), 'wb') as file:
			while bytes_left > 0:
				# Check how many bytes left.
				if byteat > bytes_left:
					byteat = bytes_left

				data = self.connection.recv(byteat)
				file.write(data)
				bytes_left -= byteat
				# print ".",

		print "done."
		return True


if __name__ == '__main__':
	server = Server()
	server.run()
