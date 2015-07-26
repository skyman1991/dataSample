import sys
import socketserver as ss
import threading

class ThreadedTCPRequestHandler(ss.BaseRequestHandler):
	def handle(self):
		data = str(self.request.recv(1024),'ascii')
		cur_thread = threading.current_thread()
		response = bytes("{}:{}".format(cur_thread.name,dta),'ascii')
		self.request.sendall(response)

class ThreadedTCPServer(ss.ThreadingMixIn,ss.TCPServer):
	pass


if __name__ == "__main__":
	HOST,PORT = "localhost",8888

	server = ThreadedTCPServer((HOST,PORT),ThreadedTCPRequestHandler)
	ip,port = server.server_address

	server_thread = threading.Thread(target=server.serve_forever)
	server_thread.daemon = True
	server_thread.start()
	print("Server loop running in thread",server_thread.name)
	try:
		while(True):
			pass
	except KeyboardInterrupt:
		server.shutdown()
		print("server quit")
