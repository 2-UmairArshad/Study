import socket
import os
SERVER_IP = "192.168.137.109"
SERVER_PORT = 12345
BUFFER_SIZE = 1024
OUTPUT_FILE = "received_file.txt"
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((SERVER_IP, SERVER_PORT))
print(f"UDP Server listening on port {SERVER_PORT}...")
while True:
    data, client_address = server_socket.recvfrom(BUFFER_SIZE)
    message = data.decode()
    if message == "ping":
        server_socket.sendto("pong".encode(), client_address)
        continue

    if message.startswith("START_FILE_TRANSFER"):
        print(f"Receiving file from {client_address}...")
        with open(OUTPUT_FILE, "w") as f:
            while True:
                chunk, addr = server_socket.recvfrom(BUFFER_SIZE)
                if chunk.decode() == "END_FILE_TRANSFER":
                    break
                f.write(chunk.decode())
        print(f"File saved as {OUTPUT_FILE}")
        server_socket.sendto("File received successfully.".encode(), client_address)