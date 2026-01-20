import socket
import threading

HOST = '127.0.0.1'
PORT = 8080

print_lock = threading.Lock()

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
        print("q) Quit")

def listen_for_messages(client_socket, username):
    """Listen for incoming text messages from server"""
    while True:
        try:
            data = client_socket.recv(4096)
            if not data:
                safe_print("\n[SERVER DISCONNECTED]")
                break

            # Decode text message
            text = data.decode(errors="ignore").strip()
            safe_print("\n" + text)

        except Exception as e:
            safe_print(f"\n[Receiver error:] {e}")
            break

def handle_menu(client_socket, username):
    """Handle user menu choices for text communication"""
    current_room = None

    while True:
        menu()
        choice = input("Select option: ").strip()

        if choice == "q":
            try:
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

    # Start TCP listener thread for incoming messages
    threading.Thread(target=listen_for_messages, args=(client_socket, username), daemon=True).start()

    # Show menu and handle user input
    handle_menu(client_socket, username)

if __name__ == "__main__":
    main()