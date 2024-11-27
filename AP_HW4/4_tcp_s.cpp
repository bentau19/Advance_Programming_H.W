#include <iostream>          // For input/output operations
#include <sys/socket.h>      // For socket functions
#include <stdio.h>           // For standard I/O functions like perror
#include <netinet/in.h>      // For sockaddr_in structure
#include <arpa/inet.h>       // For inet_addr function
#include <unistd.h>          // For close function
#include <string.h>          // For memset and string operations

using namespace std;

int main() {

    const int server_port = 5555;              // The port number of the server

    int sock = socket(AF_INET, SOCK_STREAM, 0);// Make new TCP socket
    if (sock < 0) { // Check if the socket was created successfully
        perror("error creating socket"); // Print an error message and exit if the socket creation fails
    }

    struct sockaddr_in sin; // Define the server address structure
    memset(&sin, 0, sizeof(sin));   // Zero out the structure
    sin.sin_family = AF_INET;  // Set the address family to AF_INET (IPv4)
    sin.sin_addr.s_addr = INADDR_ANY;  // Set the IP address to INADDR_ANY, which means the server will accept connections on any of the machine's IP addresses
    sin.sin_port = htons(server_port);  // Set the port number to the specified server port, converting it to network byte order

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {// Bind the socket to the specified address
        perror("error binding socket");// If binding fails, print an error message
    }

    if (listen(sock, 5) < 0) {// Start listening for incoming connections, with a backlog of 5 connections
        perror("error listening to a socket");// Start listening for incoming connections, with a backlog of 5 connections
    }

    struct sockaddr_in client_sin;  // Define the client address structure for accepting connections
    unsigned int addr_len = sizeof(client_sin);  // Define the size of the client address structure
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len); // Accept an incoming client connection

    if (client_sock < 0) {  // If accepting the client connection fails
        perror("error accepting client"); // Print an error message
    }

    char buffer[4096]; // Define a buffer to store the received data
    int expected_data_len = sizeof(buffer); // Get the size of the buffer (in bytes) for receiving data
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);    // Receive data from the client and store it in the buffer
    if (read_bytes == 0) {  // Check if the client closed the connection
    // connection is closed
    }
    else if (read_bytes < 0) {  // Check for any error while receiving data
    // error
    }
    else {  // If data was successfully received
        cout << buffer;
    }

    int sent_bytes = send(client_sock, buffer, read_bytes, 0);// Send the received data back to the client

    if (sent_bytes < 0) {// Check if sending data to the client failed
        perror("error sending to client"); // Print an error message
    }

    close(client_sock);// Close the client socket after communication
    close(sock);// Close the server socket



    return 0;
}