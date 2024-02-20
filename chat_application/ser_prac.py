import socket
from _thread import *

host="127.0.0.1"
port=1177
threadcount=0
val =0

def Client_handler(connection):
    connection.sendall(str.encode("you are now connected to the replay server... type bye to stop"))
    while True:
        try:
            data=connection.recv(2048)
            print(str(data.decode()))
            if not data:
                break
            message=data.decode("utf-8")
            if message == "bye":
                break
            # reply=f'server:{message}'
            data=input('->')
            connection.sendall(str.encode(data))
        except ConnectionResetError:
            break
    connection.close()

def accept_connection(serversocket,i):
    print(i)

    Client, address=serversocket.accept()
    # print(Client)
    # print(address)
    print("connected to: " + address[0] + ":" + str(address[1]))
    start_new_thread(Client_handler,(Client,))
    

def start_server(host,port,val):
    
    serversocket=socket.socket()
    try:
        serversocket.bind((host,port))
    except socket.error as e:
        print(str(e))
        return
    
    print(f"Servcer is listening on port {port}...")
    serversocket.listen()

    # while True:
    for i in range(3):
        if(i < 3):
            accept_connection(serversocket,i)
      
            

        
start_server(host,port,val)#0