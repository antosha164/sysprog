import socket

f = open('text.txt', 'rb')
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 5555))
sock.send(f.read())
print('MD5 checksum is:', sock.recv(1024).hex())
