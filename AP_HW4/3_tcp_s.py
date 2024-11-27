import socket  # Import the socket module

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Create a TCP socket
server_ip = ''  # get all clients ip
server_port = 12345  # Server's port
server.bind((server_ip, server_port))  # Bind the socket to the specified IP and port
server.listen(5)  # Start listening for incoming connections with a backlog of 5

while True:  # Enter an infinite loop to continuously accept and handle connections
    client_socket, client_address = server.accept()  # Accept a new client connection
    print('Connection from: ', client_address)  # Print client address
    data = client_socket.recv(1024)  # Receive up to 1024 bytes of data from the client
    while not data.decode('utf-8') == '':  # Continue reading data until the client
        # disconnects or sends an empty message
        print('Received: ', data.decode('utf-8'))  # Decode and print the received message
        client_socket.send(data.upper())  # Send the received message back to the client in uppercase
        data = client_socket.recv(1024)  # Wait for more data from the client

    print('Client disconnected')  # Notify that the client has disconnected
    client_socket.close()  # Close the client's socket
