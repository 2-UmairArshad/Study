import socket
HOST = '127.0.0.1'
PORT = 8080
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)
print("Server listening on port 8080...")
while True:
    connection, address = server_socket.accept()
    print("Connected to:", address)
    while True:
        data = connection.recv(4096).decode()
        if not data:
            break
        print(f"Received: {data}")
        connection.sendall(data.encode())
    connection.close()