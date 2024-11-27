from socket import socket, AF_INET, SOCK_DGRAM  # Import the files of socket from the library
# socket: Used to create socket objects
# AF_INET: Specifies the address family for IPv4
# SOCK_DGRAM: Specifies the socket type as datagram for UDP

s = socket(AF_INET, SOCK_DGRAM)  # make a UDP IPv4 socket type object

dst_ip = '127.0.0.1'  # set the server ip
dst_port = 12345  # set the server port

s.sendto(b'Hello', (dst_ip, dst_port))  # send a "hello" message to server in udp format
# (because the type of the socket)

data, sender_info = s.recvfrom(2048)  # get the answer from the server
print(data.decode('utf-8'))  # decode the answer in UTF-8 format and print it
print(sender_info)  # Print the sender's address and port

s.close()  # close the socket
