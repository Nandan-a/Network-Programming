import socket

host = "localhost"
port = 1233

def start_client():
    with socket.socket() as client_socket:
        try:
            client_socket.connect((host,port))
            print("Connected to the server. Enter 'Bye' to exit.")

            while True:
                message = input("Enter a message:")
                client_socket.sendall(message.encode())

                if message.upper()=="BYE":
                    print("Exiting client.")
                    break
                    
                data = client_socket.recv(2048)
                print(data.decode("utf-8"))
        
        except Exception as e:
            print(f"Error: {str(e)}")
        finally:
            print("Closing the client")

if __name__ == "__main__":
    start_client()