import socket

def client(ip,port,message):
	sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	sock.connect((ip,port))
	try:
		sock.sendall(bytes(message,'ascii'))
		response = str(sock.recv(1024),'ascii')
		print("Received:{}".format(response))
	finally:
		sock.close()

if __name__ == "__main__":
	client("localhost",8888,"hello world1")
	client("localhost",8888,"hello world2")
	client("localhost",8888,"hello world3")
