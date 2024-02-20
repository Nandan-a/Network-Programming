import socket
from _thread import *

host = "localhost"
port = 1233
ThreadCount = 0

def client_handler(connection):
    connection.send(str.encode("You are now connected to the replay server...Type BYE to stop"))
    while True:
        try:
            data = connection.recv(2048)
            if not data:
                break
            message = data.decode("utf-8")
            if message == "BYE":
                break
            reply = f"Server: {message}"
            connection.sendall(str.encode(reply))
        except ConnectionResetError:
            break
    
    connection.close()

def accept_connections(ServerSocket):
    Client,address = ServerSocket.accept()
    print("Connected to: "+ address[0]+ ":" + str(address[1]))
    start_new_thread(client_handler,(Client,))

def start_server(host,port):
    ServerSocket = socket.socket()
    try:
        ServerSocket.bind((host,port))
    
    except socket.error as e:
        print(str(e))
        return
    print(f"Server is listening on port {port}...")
    ServerSocket.listen()

    while True:
        accept_connections(ServerSocket)

start_server(host,port)