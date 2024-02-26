import socket

Host = "127.0.0.1"
port = 65432

with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as s:
    s.connect((Host,port))
    send_data = input().encode()
    s.sendall(send_data)
    data = s.recv (1024)

print("Sended data")