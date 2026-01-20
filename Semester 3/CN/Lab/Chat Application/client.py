import socket
import threading
import os
import time

# Optional: import pyaudio for audio streaming
try:
    import pyaudio
    PYAUDIO_AVAILABLE = True
except Exception as e:
    PYAUDIO_AVAILABLE = False

HOST = '127.0.0.1'
PORT = 8080

DOWNLOAD_DIR = "Downloads"
os.makedirs(DOWNLOAD_DIR, exist_ok=True)

CHUNK_SIZE = 64 * 1024  # 64 KB for file chunks
AUDIO_FRAMES_PER_BUFFER = 1024
AUDIO_RATE = 16000  # 16 kHz
AUDIO_CHANNELS = 1
AUDIO_FORMAT = pyaudio.paInt16 if PYAUDIO_AVAILABLE else None

print_lock = threading.Lock()

# UDP socket and call state
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_sock.bind(("0.0.0.0", 0))  # OS picks free port
MY_UDP_PORT = udp_sock.getsockname()[1]

# call control
in_call = threading.Event()
call_threads = []  # hold (thread_sender, thread_receiver)
current_peer = None  # (peer_ip, peer_port)

def recvall(sock, size):
    data = b''
    while len(data) < size:
        packet = sock.recv(min(size - len(data), CHUNK_SIZE))
        if not packet:
            break
        data += packet
    return data

def safe_print(*args, **kwargs):
    with print_lock:
        print(*args, **kwargs)

def menu():
    with print_lock:
        print("\n--- MENU ---")
        print("1) Broadcast message (all)")
        print("2) Private message")
        print("3) Create/Join room")
        print("4) Leave room")
        print("5) Send message to room")
        print("6) Show active users & rooms")
        print("7) Send file (private / room / all)")
        print("8) Simulate call request to user")
        print("9) Respond to call (accept/reject)")
        print("q) Quit")

def send_file_in_chunks(sock, filepath):
    with open(filepath, "rb") as f:
        while True:
            chunk = f.read(CHUNK_SIZE)
            if not chunk:
                break
            sock.sendall(chunk)

# AUDIO THREADS
def audio_sender_thread(peer_ip, peer_port):
    if not PYAUDIO_AVAILABLE:
        safe_print("[Audio sender] pyaudio not available; cannot send audio.")
        return
    pa = pyaudio.PyAudio()
    try:
        stream = pa.open(format=AUDIO_FORMAT,
                         channels=AUDIO_CHANNELS,
                         rate=AUDIO_RATE,
                         input=True,
                         frames_per_buffer=AUDIO_FRAMES_PER_BUFFER)
    except Exception as e:
        safe_print("[Audio sender] cannot open microphone:", e)
        return

    safe_print("[Call] Audio sender started.")
    try:
        while in_call.is_set():
            try:
                data = stream.read(AUDIO_FRAMES_PER_BUFFER, exception_on_overflow=False)
            except Exception:
                # keep going on overflow
                continue
            try:
                udp_sock.sendto(data, (peer_ip, peer_port))
            except Exception:
                pass
    finally:
        try:
            stream.stop_stream()
            stream.close()
            pa.terminate()
        except:
            pass
        safe_print("[Call] Audio sender stopped.")

def audio_receiver_thread():
    if not PYAUDIO_AVAILABLE:
        safe_print("[Audio receiver] pyaudio not available; cannot play audio.")
        return
    pa = pyaudio.PyAudio()
    try:
        stream = pa.open(format=AUDIO_FORMAT,
                         channels=AUDIO_CHANNELS,
                         rate=AUDIO_RATE,
                         output=True,
                         frames_per_buffer=AUDIO_FRAMES_PER_BUFFER)
    except Exception as e:
        safe_print("[Audio receiver] cannot open speaker:", e)
        return

    safe_print("[Call] Audio receiver started.")
    try:
        while in_call.is_set():
            try:
                data, addr = udp_sock.recvfrom(4096)
                if not data:
                    continue
                stream.write(data)
            except Exception:
                # ignore transient UDP errors
                continue
    finally:
        try:
            stream.stop_stream()
            stream.close()
            pa.terminate()
        except:
            pass
        safe_print("[Call] Audio receiver stopped.")

def start_call_with(peer_ip, peer_port):
    global call_threads, current_peer
    if in_call.is_set():
        safe_print("[Call] Already in a call.")
        return
    current_peer = (peer_ip, int(peer_port))
    in_call.set()
    # start sender and receiver threads
    def delayed_start():
        time.sleep(0.5)
        audio_sender_thread(peer_ip, int(peer_port))

    t_sender = threading.Thread(target=delayed_start, daemon=True)
    t_receiver = threading.Thread(target=audio_receiver_thread, daemon=True)
    call_threads = [t_sender, t_receiver]
    t_receiver.start()
    t_sender.start()

    safe_print("[Call] Call started with", peer_ip, peer_port)

def end_call():
    global call_threads, current_peer
    if not in_call.is_set():
        return
    in_call.clear()
    current_peer = None
    # give threads time to finish
    for t in call_threads:
        if t.is_alive():
            t.join(timeout=0.5)
    call_threads = []
    safe_print("[Call] Call ended.")

# TCP listener for incoming messages and signaling
def listen_for_messages(client_socket, username, pending_calls):
    while True:
        try:
            data = client_socket.recv(4096)
            if not data:
                safe_print("\n[SERVER DISCONNECTED]")
                break

            # FILE header handling starts with "/file"
            if data.startswith(b"/file"):
                header_bytes = data
                while b"\n" not in header_bytes:
                    more = client_socket.recv(4096)
                    if not more:
                        break
                    header_bytes += more

                header_line, sep, rest = header_bytes.partition(b"\n")
                try:
                    header_text = header_line.decode('utf-8', errors='replace').strip()
                except:
                    header_text = header_line.decode('latin-1', errors='replace').strip()

                parts = header_text.split(" ")
                if len(parts) >= 4 and parts[0] == "/file":
                    sender = parts[1]
                    filesize = int(parts[-1])
                    filename = " ".join(parts[2:-1])

                    file_bytes = rest
                    if len(file_bytes) < filesize:
                        file_bytes += recvall(client_socket, filesize - len(file_bytes))

                    savepath = os.path.join(DOWNLOAD_DIR, filename)
                    with open(savepath, "wb") as f:
                        f.write(file_bytes)

                    safe_print(f"\n[FILE RECEIVED] {filename} from {sender}")
                else:
                    safe_print("\n[Malformed file header received]")
                    try:
                        safe_print(header_text)
                    except:
                        pass
                continue

            # ---- Signaling: incomingcall, callresponse, startcall, endcall ----
            text = data.decode(errors="ignore").strip()

            if text.startswith("/incomingcall"):
                # /incomingcall <caller> <caller_ip> <caller_udp_port>
                parts = text.split(" ")
                if len(parts) >= 4:
                    caller = parts[1]
                    caller_ip = parts[2]
                    caller_udp = parts[3]
                    pending_calls[caller] = (caller_ip, caller_udp)
                    safe_print(f"\n[Incoming call] from {caller} ({caller_ip}:{caller_udp}). Use option 9 to respond.")
                    continue

            if text.startswith("/callresponse"):
                # /callresponse <callee> <accept|reject> <callee_ip> <callee_udp>
                parts = text.split(" ")
                if len(parts) >= 5:
                    callee = parts[1]
                    response = parts[2]
                    callee_ip = parts[3]
                    callee_udp = parts[4]
                    safe_print(f"\n[Call response] {callee} -> {response}")
                    if response.lower() == "accept":
                        safe_print(f"[Negotiation] callee at {callee_ip}:{callee_udp}")
                    continue

            if text.startswith("/startcall"):
                # /startcall <peer_ip> <peer_udp_port>
                parts = text.split(" ")
                if len(parts) >= 3:
                    peer_ip = parts[1]
                    peer_port = parts[2]
                    safe_print(f"\n[Signaling] starting call with {peer_ip}:{peer_port}")
                    # start UDP audio threads
                    start_call_with(peer_ip, peer_port)
                    continue

            if text.startswith("/endcall"):
                # /endcall <peer>
                safe_print("\n[Call ended by peer]")
                end_call()
                continue

            # otherwise normal text message or server notification
            safe_print("\n" + text)

        except Exception as e:
            safe_print(f"\n[Receiver error:] {e}")
            break

def handle_menu(client_socket, username, pending_calls):
    current_room = None

    while True:
        menu()
        choice = input("Select option: ").strip()

        if choice == "q":
            try:
                # ensure call threads stopped and inform peer if in call
                if in_call.is_set() and current_peer:
                    peer_name = ""  # not tracking peer username; send generic endcall
                    client_socket.sendall(f"/endcall \n".encode())
                    end_call()
                client_socket.close()
            except:
                pass
            break

        elif choice == "1":
            msg = input("Message: ")
            client_socket.sendall((msg + "\n").encode())

        elif choice == "2":
            to = input("Send to user: ")
            msg = input("Message: ")
            client_socket.sendall(f"/pm~{to}~{msg}\n".encode())

        elif choice == "3":
            room = input("Room name: ")
            action = input("(c=create, j=join): ")
            if action == "c":
                client_socket.sendall(f"/createroom~{room}\n".encode())
            else:
                client_socket.sendall(f"/join~{room}\n".encode())
            current_room = room

        elif choice == "4":
            client_socket.sendall("/leave\n".encode())
            current_room = None

        elif choice == "5":
            if not current_room:
                safe_print("You are not in a room.")
                continue
            msg = input("Message: ")
            client_socket.sendall(f"/roommsg~{current_room}~{msg}\n".encode())

        elif choice == "6":
            client_socket.sendall("/users\n".encode())
            client_socket.sendall("/rooms\n".encode())

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

        elif choice == "8":
            target = input("Call which user? ").strip()
            # send call request to server, server will forward with your UDP info
            client_socket.sendall(f"/callreq~{target}\n".encode())
            safe_print(f"[Call] request sent to {target} (await response).")

        elif choice == "9":
            # Respond to incoming call - user must enter caller username and accept/reject
            if not pending_calls:
                safe_print("No incoming calls pending.")
                continue
            # Show pending calls
            safe_print("Pending calls:")
            for idx, k in enumerate(list(pending_calls.keys()), start=1):
                cinfo = pending_calls[k]
                safe_print(f"{idx}) {k} at {cinfo[0]}:{cinfo[1]}")
            caller = input("Caller username to respond: ").strip()
            if caller not in pending_calls:
                safe_print("Invalid caller.")
                continue
            resp = input("accept/reject: ").strip().lower()
            # send response to server (server will forward to caller)
            client_socket.sendall(f"/callresp~{caller}~{resp}\n".encode())
            safe_print(f"[Call] you responded {resp} to {caller}")
            if resp == "accept":
                # we will receive /startcall from server with peer info; clear pending
                pending_calls.pop(caller, None)
            else:
                pending_calls.pop(caller, None)

        else:
            safe_print("Invalid choice!")

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((HOST, PORT))
    except Exception as e:
        safe_print("Could not connect to server.", e)
        return

    username = input("Enter username: ").strip()
    client_socket.sendall(username.encode())

    # register our UDP port with server for P2P calls
    # send /udpport <port>
    client_socket.sendall(f"/udpport {MY_UDP_PORT}\n".encode())

    pending_calls = {}  # caller -> (ip, udp_port)

    # start TCP listener thread
    threading.Thread(target=listen_for_messages, args=(client_socket, username, pending_calls), daemon=True).start()

    # show menu and handle user
    handle_menu(client_socket, username, pending_calls)

if __name__ == "__main__":
    main()
