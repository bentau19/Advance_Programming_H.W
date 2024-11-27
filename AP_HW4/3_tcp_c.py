import socket  # Import the socket module

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a TCP socket
dest_ip = '127.0.0.1'  # Server's ip
dest_port = 12345  # Server's port
s.connect((dest_ip, dest_port))  # Establish a connection to the server

msg = input("Message to send: ")  # Prompt the user to input a message to send to the server
while not msg == 'quit':  # As long as the user not input "quit"
    s.send(bytes(msg, 'utf-8'))  # Send the message to server
    data = s.recv(4096)  # Receive the data from server
    print("Server sent: ", data.decode('utf-8'))  # Print the data from server
    msg = input("Message to send: ")  # Get another input for the loop

s.close()  # Close the socket
