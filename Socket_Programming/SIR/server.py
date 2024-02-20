# Python program for SOCKET to terminate client connection on receiving 'BYE' message at server.
# =================================================================================================
# Server.py

import socket
from _thread import *

host = '127.0.0.1'
port = 1234
ThreadCount = 0

def client_handler(connection):
    connection.sendall('You are now connected to the reply server...Type BYE to stop'.encode())
    while True:
        try:
            data = connection.recv(2048)
            if not data:
                break
            message = data.decode('utf-8')
            if message == 'BYE':
                break
            reply = f'Server: {message}'
            connection.sendall(reply.encode())
        except ConnectionResetError:
            break
    connection.close()

def accept_connections(ServerSocket):
    Client, address = ServerSocket.accept()
    print('Connected to: ' + address[0] + ':' + str(address[1]))
    start_new_thread(client_handler, (Client, ))

def start_server(host, port):
    with socket.socket() as ServerSocket:
        try:
            ServerSocket.bind((host, port))
        except socket.error as e:
            print(str(e))
            return

        print(f'Server is listening on port {port}...')
        ServerSocket.listen()

        while True:
            accept_connections(ServerSocket)

start_server(host, port)
