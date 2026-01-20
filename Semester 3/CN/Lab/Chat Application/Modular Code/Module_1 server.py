import socket
import threading

HOST = "127.0.0.1"
PORT = 8080

Active_Clients = []  # list of tuples (username, conn)
Rooms = {}

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

def send_to_client(conn, msg):
    try:
        conn.sendall(msg.encode())
    except:
        pass

def broadcast_to_all(msg, exclude=""):
    for (username, conn) in Active_Clients:
        if username != exclude:
            send_to_client(conn, msg)

def private_message(target, msg):
    for (username, conn) in Active_Clients:
        if username == target:
            send_to_client(conn, msg)
            return

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

            text = header_or_cmd

            # Show users
            if text.startswith("/users"):
                send_to_client(conn, get_user_list() + "\n")
                continue

            # Show rooms (detailed)
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
                    # broadcast to room (exclude sender)
                    for (u, c) in Rooms[room]:
                        if u != username:
                            send_to_client(c, f"{username}: {msg}\n")
                else:
                    send_to_client(conn, f"Room {room} does not exist.\n")
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
                    # broadcast to room
                    for (u, c) in Rooms[room]:
                        if u != username:
                            send_to_client(c, f"{username}: {msg}\n")
                else:
                    send_to_client(conn, f"Room {room} does not exist.\n")
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

            # Room message
            if text.startswith("/roommsg"):
                try:
                    _, room, msg = text.split("~", 2)
                except:
                    send_to_client(conn, "Invalid room message format.\n")
                    continue
                if room in Rooms:
                    # broadcast to room members
                    for (u, c) in Rooms[room]:
                        if u != username:
                            send_to_client(c, f"{username}: {msg}\n")
                else:
                    send_to_client(conn, f"Room {room} does not exist.\n")
                continue

            # broadcast to room or global
            sent = False
            for room in Rooms:
                if (username, conn) in Rooms[room]:
                    for (u, c) in Rooms[room]:
                        if u != username:
                            send_to_client(c, f"{username}: {text}\n")
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