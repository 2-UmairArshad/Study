import socket
import threading

def handle_client(client_socket):
    # Receive request from client
    request = client_socket.recv(4096)
    
    # Parse the request
    first_line = request.split(b'\n')[0]
    url = first_line.split(b' ')[1]
    
    # Find the webserver and port
    http_pos = url.find(b'://')
    if http_pos == -1:
        temp = url
    else:
        temp = url[(http_pos+3):]
    
    port_pos = temp.find(b':')
    webserver_pos = temp.find(b'/')
    
    if webserver_pos == -1:
        webserver_pos = len(temp)
    
    webserver = ""
    port = -1
    
    if port_pos == -1 or webserver_pos < port_pos:
        port = 80
        webserver = temp[:webserver_pos]
    else:
        port = int((temp[(port_pos+1):])[:webserver_pos-port_pos-1])
        webserver = temp[:port_pos]
    
    try:
        # Create socket to connect to webserver
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((webserver.decode(), port))
        s.send(request)
        
        while True:
            # Receive data from webserver
            data = s.recv(4096)
            if len(data) > 0:
                # Send to client
                client_socket.send(data)
            else:
                break
        s.close()
        client_socket.close()
    except Exception as e:
        print(f"Error: {e}")
        client_socket.close()

def start_proxy(port=8888):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('localhost', port))
    server.listen(5)
    print(f"[*] Proxy server listening on localhost:{port}")
    
    while True:
        client_socket, addr = server.accept()
        print(f"[*] Accepted connection from {addr[0]}:{addr[1]}")
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == '__main__':
    start_proxy()
