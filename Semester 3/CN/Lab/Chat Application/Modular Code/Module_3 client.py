"""
MODULE 3: P2P VOICE COMMUNICATION (UDP) - Client Side
Member C should add these functions to the client.py from Module 1

This module handles real-time audio streaming using PyAudio and UDP sockets.
"""

import socket
import threading
import time

# ADD PYAUDIO IMPORT WITH ERROR HANDLING AT TOP
try:
    import pyaudio
    PYAUDIO_AVAILABLE = True
except Exception as e:
    PYAUDIO_AVAILABLE = False
    print("[WARNING] PyAudio not available. Voice calls will not work.")

# ADD THESE CONSTANTS AT THE TOP
AUDIO_FRAMES_PER_BUFFER = 1024
AUDIO_RATE = 16000  # 16 kHz
AUDIO_CHANNELS = 1
AUDIO_FORMAT = pyaudio.paInt16 if PYAUDIO_AVAILABLE else None

# ADD THESE GLOBAL VARIABLES
# UDP socket for voice communication
udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_sock.bind(("0.0.0.0", 0))  # OS picks a free port
MY_UDP_PORT = udp_sock.getsockname()[1]

# Call control variables
in_call = threading.Event()
call_threads = []  # holds (thread_sender, thread_receiver)
current_peer = None  # (peer_ip, peer_port)

def audio_sender_thread(peer_ip, peer_port):
    """Captures audio from microphone and sends via UDP"""
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
                # Continue on overflow
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
    """Receives audio via UDP and plays through speakers"""
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
                # Ignore transient UDP errors
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
    """Start a voice call with a peer"""
    global call_threads, current_peer
    if in_call.is_set():
        safe_print("[Call] Already in a call.")
        return
    
    current_peer = (peer_ip, int(peer_port))
    in_call.set()
    
    # Start sender and receiver threads
    def delayed_start():
        time.sleep(0.5)
        audio_sender_thread(peer_ip, int(peer_port))

    t_sender = threading.Thread(target=delayed_start, daemon=True)
    t_receiver = threading.Thread(target=audio_receiver_thread, daemon=True)
    call_threads = [t_sender, t_receiver]
    t_receiver.start()
    t_sender.start()

    safe_print(f"[Call] Call started with {peer_ip}:{peer_port}")

def end_call():
    """End the current voice call"""
    global call_threads, current_peer
    if not in_call.is_set():
        return
    
    in_call.clear()
    current_peer = None
    
    # Give threads time to finish
    for t in call_threads:
        if t.is_alive():
            t.join(timeout=0.5)
    call_threads = []
    safe_print("[Call] Call ended.")

"""
MODIFY listen_for_messages() to handle call signaling.
ADD THIS CODE before the text decoding part:

            # ---- Call Signaling Messages ----
            text = data.decode(errors="ignore").strip()

            # Incoming call notification
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

            # Call response from callee
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

            # Start call (from server after both parties accepted)
            if text.startswith("/startcall"):
                # /startcall <peer_ip> <peer_udp_port>
                parts = text.split(" ")
                if len(parts) >= 3:
                    peer_ip = parts[1]
                    peer_port = parts[2]
                    safe_print(f"\n[Signaling] starting call with {peer_ip}:{peer_port}")
                    # Start UDP audio threads
                    start_call_with(peer_ip, peer_port)
                    continue

            # End call notification
            if text.startswith("/endcall"):
                # /endcall <peer>
                safe_print("\n[Call ended by peer]")
                end_call()
                continue
"""

"""
ADD THESE MENU OPTIONS to handle_menu():
Add "8) Simulate call request to user" and "9) Respond to call (accept/reject)" to menu

Add this parameter: pending_calls = {}  # Pass this dictionary to track incoming calls

        elif choice == "8":
            target = input("Call which user? ").strip()
            # Send call request to server
            client_socket.sendall(f"/callreq~{target}\n".encode())
            safe_print(f"[Call] request sent to {target} (await response).")

        elif choice == "9":
            # Respond to incoming call
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
            # Send response to server
            client_socket.sendall(f"/callresp~{caller}~{resp}\n".encode())
            safe_print(f"[Call] you responded {resp} to {caller}")
            
            if resp == "accept":
                # We will receive /startcall from server with peer info
                pending_calls.pop(caller, None)
            else:
                pending_calls.pop(caller, None)
"""

"""
IN main() function, ADD:
1. After connecting, register UDP port:
   client_socket.sendall(f"/udpport {MY_UDP_PORT}\n".encode())

2. Create pending_calls dictionary:
   pending_calls = {}

3. Pass it to listen thread:
   threading.Thread(target=listen_for_messages, 
                    args=(client_socket, username, pending_calls), 
                    daemon=True).start()

4. Pass it to handle_menu:
   handle_menu(client_socket, username, pending_calls)

5. On quit (choice == "q"), end call if in progress:
   if in_call.is_set() and current_peer:
       client_socket.sendall(f"/endcall \n".encode())
       end_call()
"""