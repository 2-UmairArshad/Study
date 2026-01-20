"""
MODULE 2: FILE TRANSFER SUBSYSTEM - Client Side
Member B should add these functions to the client.py from Module 1
"""

import os

# ADD THESE CONSTANTS AT THE TOP (after imports)
DOWNLOAD_DIR = "Downloads"
os.makedirs(DOWNLOAD_DIR, exist_ok=True)
CHUNK_SIZE = 64 * 1024  # 64 KB

def recvall(sock, size):
    """Receive exactly 'size' bytes from socket"""
    data = b''
    while len(data) < size:
        packet = sock.recv(min(size - len(data), CHUNK_SIZE))
        if not packet:
            break
        data += packet
    return data

def send_file_in_chunks(sock, filepath):
    """Read file and send it in chunks over the socket"""
    with open(filepath, "rb") as f:
        while True:
            chunk = f.read(CHUNK_SIZE)
            if not chunk:
                break
            sock.sendall(chunk)

"""
MODIFY listen_for_messages() to handle file reception.
ADD THIS CODE at the beginning of the while loop, before text decoding:

            # FILE header handling starts with "/file"
            if data.startswith(b"/file"):
                header_bytes = data
                # Read until we find the newline that ends the header
                while b"\n" not in header_bytes:
                    more = client_socket.recv(4096)
                    if not more:
                        break
                    header_bytes += more

                # Split header from any file data that came with it
                header_line, sep, rest = header_bytes.partition(b"\n")
                try:
                    header_text = header_line.decode('utf-8', errors='replace').strip()
                except:
                    header_text = header_line.decode('latin-1', errors='replace').strip()

                # Parse header: /file <sender> <filename> <filesize>
                parts = header_text.split(" ")
                if len(parts) >= 4 and parts[0] == "/file":
                    sender = parts[1]
                    filesize = int(parts[-1])
                    filename = " ".join(parts[2:-1])

                    # Collect file bytes
                    file_bytes = rest
                    if len(file_bytes) < filesize:
                        file_bytes += recvall(client_socket, filesize - len(file_bytes))

                    # Save to Downloads folder
                    savepath = os.path.join(DOWNLOAD_DIR, filename)
                    with open(savepath, "wb") as f:
                        f.write(file_bytes)

                    safe_print(f"\n[FILE RECEIVED] {filename} from {sender}")
                else:
                    safe_print("\n[Malformed file header received]")
                continue
"""

"""
ADD THIS MENU OPTION to handle_menu() function:
Add "7) Send file (private / room / all)" to the menu

        elif choice == "7":
            target_type = input("1=user, 2=room, 3=all: ").strip()
            filepath = input("File path: ").strip().replace("\\", "/")
            if not os.path.exists(filepath):
                safe_print("File not found.")
                continue

            filename = os.path.basename(filepath)
            filesize = os.path.getsize(filepath)

            if target_type == "1":
                to = input("Send to user: ").strip()
                header = f"/fileuser~{to}~{username}~{filename}~{filesize}\n"
                client_socket.sendall(header.encode())
            elif target_type == "2":
                room = input("Room name: ").strip()
                header = f"/fileroom~{room}~{username}~{filename}~{filesize}\n"
                client_socket.sendall(header.encode())
            else:
                header = f"/fileall~{username}~{filename}~{filesize}\n"
                client_socket.sendall(header.encode())

            try:
                send_file_in_chunks(client_socket, filepath)
                safe_print("[FILE SENT]")
            except Exception as e:
                safe_print("[FILE SEND ERROR]", e)
"""