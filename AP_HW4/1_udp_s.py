from socket import socket, AF_INET, SOCK_DGRAM  # Import the files of socket from the library

# socket: Used to create socket objects
# AF_INET: Specifies the address family for IPv4
# SOCK_DGRAM: Specifies the socket type as datagram for UDP
s = socket(AF_INET, SOCK_DGRAM)  # make a UDP IPv4 socket type object

src_ip = ''  # Bind the socket to all available network interfaces
src_port = 12345  # set the server port
s.bind((src_ip, src_port))  # Bind the socket to the specified IP and port

while True:  # infinite loop
    data, sender_info = s.recvfrom(2048)  # Wait for a message from a client
    print(data.decode('utf-8'))  # Decode the received data to a string and print it
    print(sender_info)  # Print the sender's address (IP and port)

    s.sendto(data.upper(), sender_info)  # Send the received message back to the client in uppercase
