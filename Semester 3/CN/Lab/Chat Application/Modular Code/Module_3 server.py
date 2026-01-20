"""
MODULE 3: P2P VOICE COMMUNICATION (UDP) - Server Side
Member C should add these functions to the server.py from Module 1

The server only handles SIGNALING for voice calls, not the audio itself.
The actual voice communication happens peer-to-peer using UDP.
"""

# ADD THIS GLOBAL VARIABLE AT THE TOP (with other globals)
UDP_MAP = {}  # username -> (ip, udp_port)

"""
ADD THESE HANDLERS INSIDE client_handler() function,
after the read_line() call and before text command handling:

            # Handle UDP port registration from client
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

            # CALL REQUEST: client sends /callreq~<target>
            if header_or_cmd.startswith("/callreq"):
                try:
                    _, target = header_or_cmd.split("~", 1)
                except:
                    send_to_client(conn, "Invalid call request.\n")
                    continue

                # Get caller's UDP info
                caller_ip, caller_udp = UDP_MAP.get(username, (None, None))
                if caller_ip is None:
                    send_to_client(conn, "Your UDP port not registered.\n")
                    continue

                # Find target connection and forward incoming call notification
                found = False
                for (u, c) in Active_Clients:
                    if u == target:
                        # Send /incomingcall <caller> <caller_ip> <caller_udp>
                        c.sendall(f"/incomingcall {username} {caller_ip} {caller_udp}\n".encode())
                        found = True
                        break
                if not found:
                    send_to_client(conn, "User not found.\n")
                continue

            # CALL RESPONSE: /callresp~<caller>~<accept|reject>
            if header_or_cmd.startswith("/callresp"):
                parts = header_or_cmd.split("~")
                if len(parts) < 3:
                    send_to_client(conn, "Invalid call response.\n")
                    continue
                _, caller, response = parts[:3]
                
                # Get callee's UDP info
                callee_ip, callee_udp = UDP_MAP.get(username, (None, None))

                # Forward response to caller (include callee's IP/port)
                for (u, c) in Active_Clients:
                    if u == caller:
                        # Send /callresponse <callee> <accept/reject> <callee_ip> <callee_udp>
                        c.sendall(f"/callresponse {username} {response} {callee_ip} {callee_udp}\n".encode())
                        break

                # If accepted, send /startcall to both peers with peer info
                if response.lower() == "accept":
                    # Need both parties' UDP info
                    caller_info = UDP_MAP.get(caller, (None, None))
                    callee_info = UDP_MAP.get(username, (None, None))
                    if caller_info[0] is None or callee_info[0] is None:
                        send_to_client(conn, "Peer UDP info missing.\n")
                        continue

                    # Send /startcall <peer_ip> <peer_udp> to both parties
                    for (u, c) in Active_Clients:
                        if u == caller:
                            # Send callee info to caller
                            c.sendall(f"/startcall {callee_info[0]} {callee_info[1]}\n".encode())
                        if u == username:
                            # Send caller info to callee
                            c.sendall(f"/startcall {caller_info[0]} {caller_info[1]}\n".encode())
                continue

            # END CALL: /endcall <target>
            if header_or_cmd.startswith("/endcall"):
                parts = header_or_cmd.split(" ")
                if len(parts) >= 2:
                    target = parts[1]
                    for (u, c) in Active_Clients:
                        if u == target:
                            c.sendall(f"/endcall {username}\n".encode())
                            break
                continue
"""