import sys
import socketserver as ss
import threading

class ThreadedTCPRequestHandler(ss.BaseRequestHandler):
	def handle(self):
		addr = self.request.getpeername()
		print("Got connect from",addr)
		res = bytes("Thanks",'ascii')
		data1 = 2
		self.request.send(res)
		print("Thread: ",data1)

class ThreadedTCPServer(ss.ThreadingMixIn,ss.TCPServer):
	pass


if __name__ == "__main__":
	HOST,PORT = "localhost",8888

	server = ThreadedTCPServer((HOST,PORT),ThreadedTCPRequestHandler)
	ip,port = server.server_address
	data1 = 0

	server_thread = threading.Thread(target=server.serve_forever)
	server_thread.daemon = True
	server_thread.start()
	print("mainloop:",data1)
	print("Server loop running in thread",server_thread.name)
	try:
		while(True):
			pass
	except KeyboardInterrupt:
		server.shutdown()
		print("end: ",data1)
		print("server quit")
