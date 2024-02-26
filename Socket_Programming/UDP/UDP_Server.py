import socket

localIP = "localhost"
localPort = 8080
bufferSize = 2048

msgFromServer = "hello udp clinet"

bytesToSend = str.encode(msgFromServer)

#create a datagram socket
UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

#bind to address and ip
UDPServerSocket.bind((localIP, localPort))

print("udp server up and listening")

#listen for imcomming datagrams
while(True):
    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
    message = bytesAddressPair[0]
    address = bytesAddressPair[1]

    clientMsg = "Message from client:{}".format(message)
    clientIP = "Client IP address:{}".format(address)

    print(clientMsg)
    print(clientIP)

    #sending a reply to client
    UDPServerSocket.sendto(bytesToSend, address)
