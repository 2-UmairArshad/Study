import socket
HOST = '127.0.0.1'
PORT = 8080
messages = ["Hello Server", "This is message 2", "Goodbye"]
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))
print("Connected to server")
print('Select Option:')
print('1. Send Messages')
print('2. Exit')
option = input('Enter option: ')
if option == '1':
    print('Enter The Messages to Send:')
    msg=input()
    client_socket.sendall(msg.encode())
    data = client_socket.recv(4096).decode() 
    print(f"Received from server: {data}")
elif option == '2':
    client_socket.close()
print("Connection closed")
