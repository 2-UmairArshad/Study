import socket
HOST = 'localhost'
PORT = 9090
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
messages = ["Message 1", "Message 2", "Message 3"]
for msg in messages:
    client_socket.sendto(msg.encode(), (HOST, PORT))
    data, _ = client_socket.recvfrom(1024)
    print(f"Sent: {msg} | Received: {data.decode()}")
client_socket.close()