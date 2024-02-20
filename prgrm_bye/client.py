import socket

def start_client():
    host = '127.0.0.1'
    port = 1234

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    try:
        while True:
            message = input("Enter a message (type 'exit' to quit): ")
            client_socket.sendall(message.encode())

            if message.lower() == 'exit':
                break

            data = client_socket.recv(1024)
            received_message = data.decode('utf-8')
            print(f"Received from server: {received_message}")

    except Exception as e:
        print(f"Error in client: {str(e)}")
    finally:
        client_socket.close()

if __name__ == "__main__":
    start_client()