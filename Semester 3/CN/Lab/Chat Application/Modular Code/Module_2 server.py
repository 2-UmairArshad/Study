"""
MODULE 2: FILE TRANSFER SUBSYSTEM - Server Side
Member B should add these functions to the server.py from Module 1
"""

# ADD THIS CONSTANT AT THE TOP OF THE FILE (after imports)
CHUNK_SIZE = 64 * 1024  # 64 KB

def recvall(sock, size):
    """Receive exactly 'size' bytes from socket"""
    data = b""
    while len(data) < size:
        chunk = sock.recv(size - len(data))
        if not chunk:
            break
        data += chunk
    return data

def send_file_to_user(target_user, sender, filename, filesize, filedata):
    """Send file to a specific user"""
    for (username, conn) in Active_Clients:
        if username == target_user:
            header = f"/file {sender} {filename} {filesize}"
            try:
                conn.sendall((header + "\n").encode())
                conn.sendall(filedata)
                return True
            except:
                return False
    return False

def broadcast_file_to_all(header, filedata, exclude=""):
    """Send file to all connected users except sender"""
    for (username, conn) in Active_Clients:
        if username != exclude:
            try:
                conn.sendall((header + "\n").encode())
                conn.sendall(filedata)
            except:
                pass

def broadcast_file_to_room(room, header, filedata, exclude=""):
    """Send file to all users in a specific room"""
    if room not in Rooms:
        return
    for (username, conn) in Rooms[room]:
        if username != exclude:
            try:
                conn.sendall((header + "\n").encode())
                conn.sendall(filedata)
            except:
                pass

"""
ADD THESE HANDLERS INSIDE client_handler() function, 
after the read_line() call and before text command handling:

            # FILE: user
            if header_or_cmd.startswith("/fileuser"):
                parts = header_or_cmd.split("~")
                if len(parts) < 5:
                    send_to_client(conn, "Invalid file header\n")
                    continue
                target = parts[1]
                sender = parts[2]
                filesize = int(parts[-1])
                filename = " ".join(parts[3:-1])

                filedata = recvall(conn, filesize)

                ok = send_file_to_user(target, sender, filename, filesize, filedata)
                send_to_client(conn, "[FILE DELIVERED]\n" if ok else "User not found.\n")
                continue

            # FILE: room
            if header_or_cmd.startswith("/fileroom"):
                parts = header_or_cmd.split("~")
                if len(parts) < 5:
                    send_to_client(conn, "Invalid file header\n")
                    continue
                room = parts[1]
                sender = parts[2]
                filesize = int(parts[-1])
                filename = " ".join(parts[3:-1])

                filedata = recvall(conn, filesize)
                header = f"/file {sender} {filename} {filesize}"
                broadcast_file_to_room(room, header, filedata, sender)
                send_to_client(conn, "[FILE SENT TO ROOM]\n")
                continue

            # FILE: all
            if header_or_cmd.startswith("/fileall"):
                parts = header_or_cmd.split("~")
                if len(parts) < 4:
                    send_to_client(conn, "Invalid file header\n")
                    continue
                sender = parts[1]
                filesize = int(parts[-1])
                filename = " ".join(parts[2:-1])

                filedata = recvall(conn, filesize)
                header = f"/file {sender} {filename} {filesize}"
                broadcast_file_to_all(header, filedata, sender)
                send_to_client(conn, "[FILE SENT TO ALL]\n")
                continue
"""