import socket
import threading
import os

HOST = "127.0.0.1"
PORT = 8080

Active_Clients = []  # list of tuples (username, conn)
Rooms = {}
UDP_MAP = {}         # username -> (ip, udp_port)

# read exactly one header line terminated by '\n'
def read_line(sock):
    data = b""
    while True:
        ch = sock.recv(1)
        if not ch:
            break
        data += ch
        if ch == b"\n":
            break
    try:
        return data.decode().strip()
    except:
        return data.decode('latin-1', errors='ignore').strip()

def recvall(sock, size):
    data = b""
    while len(data) < size:
        chunk = sock.recv(size - len(data))
        if not chunk:
            break
        data += chunk
    return data

def send_to_client(conn, msg):
    try:
        conn.sendall(msg.encode())
    except:
        pass

def broadcast_to_all(msg, exclude=""):
    for (username, conn) in Active_Clients:
        if username != exclude:
            send_to_client(conn, msg)

def broadcast_file_to_all(header, filedata, exclude=""):
    for (username, conn) in Active_Clients:
        if username != exclude:
            try:
                conn.sendall((header + "\n").encode())
                conn.sendall(filedata)
            except:
                pass

def broadcast_to_room(room, msg, exclude=""):
    if room not in Rooms:
        return
    for (username, conn) in Rooms[room]:
        if username != exclude:
            send_to_client(conn, msg)

def broadcast_file_to_room(room, header, filedata, exclude=""):
    if room not in Rooms:
        return
    for (username, conn) in Rooms[room]:
        if username != exclude:
            try:
                conn.sendall((header + "\n").encode())
                conn.sendall(filedata)
            except:
                pass

def private_message(target, msg):
    for (username, conn) in Active_Clients:
        if username == target:
            send_to_client(conn, msg)
            return

def send_file_to_user(target_user, sender, filename, filesize, filedata):
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

def join_room(username, conn, room):
    if room not in Rooms:
        Rooms[room] = []
    if (username, conn) not in Rooms[room]:
        Rooms[room].append((username, conn))
    send_to_client(conn, f"You joined room: {room}\n")

def leave_room(username, conn):
    for room in list(Rooms.keys()):
        if (username, conn) in Rooms[room]:
            Rooms[room].remove((username, conn))
            send_to_client(conn, "You left the room.\n")
            return

def get_user_list():
    names = [u for (u, c) in Active_Clients]
    return "Online Users: " + ", ".join(names)

def get_rooms_detailed():
    lines = []
    for r in Rooms:
        count = len(Rooms[r])
        lines.append(f"- {r} ({count} user{'s' if count != 1 else ''})")
    if not lines:
        return "Rooms: (none)\n"
    return "Rooms:\n" + "\n".join(lines) + "\n"

def client_handler(conn, addr):
    try:
        username = conn.recv(1024).decode()
    except:
        conn.close()
        return

    Active_Clients.append((username, conn))
    print(f"{username} connected from {addr}")
    broadcast_to_all(f"*** {username} joined the chat ***\n")
    send_to_client(conn, get_user_list() + "\n")

    while True:
        try:
            header_or_cmd = read_line(conn)
            if not header_or_cmd:
                break

            # handle udpport registration from client
            if header_or_cmd.startswith("/udpport"):
                # /udpport <port>
                parts = header_or_cmd.split()
                if len(parts) >= 2:
                    try:
                        udp_port = int(parts[1])
                        client_ip = conn.getpeername()[0]
                        UDP_MAP[username] = (client_ip, udp_port)
                        send_to_client(conn, "[UDP REGISTERED]\n")
                    except:
                        send_to_client(conn, "Invalid UDP port\n")
                continue

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

            # other commands (text)
            text = header_or_cmd

            # Show users
            if text.startswith("/users"):
                send_to_client(conn, get_user_list() + "\n")
                continue

            # Show rooms (detailed - format B)
            if text.startswith("/rooms"):
                send_to_client(conn, get_rooms_detailed())
                continue

            # Private message
            if text.startswith("/pm"):
                _, target, msg = text.split("~", 2)
                private_message(target, f"[PM from {username}]: {msg}\n")
                continue

            # Join room
            if text.startswith("/join"):
                _, room = text.split("~", 1)
                join_room(username, conn, room)
                continue

            # Create room
            if text.startswith("/createroom"):
                _, room = text.split("~", 1)
                if room not in Rooms:
                    Rooms[room] = []
                send_to_client(conn, f"Room {room} created.\n")
                continue

            # Leave room
            if text.startswith("/leave"):
                leave_room(username, conn)
                continue

            # Room message: /roommsg <room> <msg>
            if text.startswith("/roommsg"):
                try:
                    _, room, msg = text.split("~", 2)
                except:
                    send_to_client(conn, "Invalid room message format.\n")
                    continue
                if room in Rooms:
                    broadcast_to_room(room, f"{username}: {msg}\n", username)
                else:
                    send_to_client(conn, f"Room {room} does not exist.\n")
                continue

            # CALL: incoming request (signaling)
            # client sends: /callreq <target>
            if text.startswith("/callreq"):
                try:
                    _, target = text.split("~", 1)
                except:
                    send_to_client(conn, "Invalid call request.\n")
                    continue

                # get caller UDP info
                caller_ip, caller_udp = UDP_MAP.get(username, (None, None))
                if caller_ip is None:
                    send_to_client(conn, "Your UDP port not registered.\n")
                    continue

                # find target conn and forward incomingcall
                found = False
                for (u, c) in Active_Clients:
                    if u == target:
                        # send /incomingcall caller caller_ip caller_udp
                        c.sendall(f"/incomingcall {username} {caller_ip} {caller_udp}\n".encode())
                        found = True
                        break
                if not found:
                    send_to_client(conn, "User not found.\n")
                continue

            # CALL RESPONSE: /callresp <caller> <accept|reject>
            if text.startswith("/callresp"):
                parts = text.split("~")
                if len(parts) < 3:
                    send_to_client(conn, "Invalid call response.\n")
                    continue
                _, caller, response = parts[:3]
                # get callee udp info
                callee_ip, callee_udp = UDP_MAP.get(username, (None, None))

                # forward response to caller (and include callee ip/port)
                for (u, c) in Active_Clients:
                    if u == caller:
                        # send /callresponse callee accept/reject callee_ip callee_udp
                        c.sendall(f"/callresponse {username} {response} {callee_ip} {callee_udp}\n".encode())
                        break

                # If accepted -> send /startcall to both peers with the peer info
                if response.lower() == "accept":
                    # need both parties udp info
                    caller_info = UDP_MAP.get(caller, (None, None))
                    callee_info = UDP_MAP.get(username, (None, None))
                    if caller_info[0] is None or callee_info[0] is None:
                        send_to_client(conn, "Peer UDP info missing.\n")
                        continue

                    # find connections and send /startcall <peer_ip> <peer_udp>
                    for (u, c) in Active_Clients:
                        if u == caller:
                            # send callee info to caller
                            c.sendall(f"/startcall {callee_info[0]} {callee_info[1]}\n".encode())
                        if u == username:
                            # send caller info to callee
                            c.sendall(f"/startcall {caller_info[0]} {caller_info[1]}\n".encode())
                    continue

                continue

            # End call
            if text.startswith("/endcall"):
                # /endcall <target>
                parts = text.split(" ")
                if len(parts) >= 2:
                    target = parts[1]
                    for (u, c) in Active_Clients:
                        if u == target:
                            c.sendall(f"/endcall {username}\n".encode())
                            break
                continue

            # broadcast to room or global
            sent = False
            for room in Rooms:
                if (username, conn) in Rooms[room]:
                    broadcast_to_room(room, f"{username}: {text}\n", username)
                    sent = True
                    break

            if not sent:
                broadcast_to_all(f"{username}: {text}\n", username)

        except Exception as e:
            print("ERR:", e)
            break

    try:
        Active_Clients.remove((username, conn))
    except:
        pass
    broadcast_to_all(f"*** {username} left the chat ***\n")
    print(f"{username} disconnected")
    try:
        conn.close()
    except:
        pass

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen()
    print(f"Server running on port {PORT}")
    while True:
        conn, addr = s.accept()
        threading.Thread(target=client_handler, args=(conn, addr), daemon=True).start()

if __name__ == "__main__":
    main()
