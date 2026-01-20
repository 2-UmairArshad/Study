import socket
HOST = 'localhost'
PORT = 9090
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((HOST, PORT))
print("UDP Server listening on port 9090...")
while True:
    data, addr = server_socket.recvfrom(1024)
    message = data.decode()
    print(f"Received from {addr}: {message}")
    ack = f"ACK: {message}"
    server_socket.sendto(ack.encode(), addr)
    