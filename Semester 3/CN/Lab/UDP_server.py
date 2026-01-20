import socket
import time
import os
SERVER_IP = "127.0.0.1"  
SERVER_PORT = 12345
FILE_TO_SEND = "file_to_send.txt"
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_socket.settimeout(5)
start_time = time.time()
client_socket.sendto("ping".encode(), (SERVER_IP, SERVER_PORT))
data, _ = client_socket.recvfrom(1024)
end_time = time.time()
if data.decode() == "pong":
    rtt = (end_time - start_time) * 1000
    print(f"Ping successful! RTT = {rtt:.2f} ms")
client_socket.sendto("START_FILE_TRANSFER".encode(), (SERVER_IP, SERVER_PORT))
print("Sending file...")
with open(FILE_TO_SEND, "r") as f:
    for line in f:
        client_socket.sendto(line.encode(), (SERVER_IP, SERVER_PORT))
client_socket.sendto("END_FILE_TRANSFER".encode(), (SERVER_IP, SERVER_PORT))
ack, _ = client_socket.recvfrom(1024)
print("Server:", ack.decode())
client_socket.close()