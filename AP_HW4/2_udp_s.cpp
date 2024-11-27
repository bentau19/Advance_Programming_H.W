#include <iostream>             // For input/output operations
#include <sys/socket.h>     // For socket functions
#include <stdio.h>           // For standard I/O functions like perror
#include <netinet/in.h>      // For sockaddr_in structure
#include <arpa/inet.h>       // For inet_addr function
#include <unistd.h>          // For close function
#include <string.h>          // For memset and string operations

using namespace std;

int main() {

    const int server_port = 5555;// The port number of the server

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Make new UDP socket
    if (sock < 0) {// Check if the socket was created successfully
        perror("error creating socket");// Print an error message and exit if the socket creation fails
    }

    struct sockaddr_in sin; // Define the server's address structure

    memset(&sin, 0, sizeof(sin));          // Zero out the structure

    sin.sin_family = AF_INET;              // Set the address family to IPv4
    sin.sin_addr.s_addr = INADDR_ANY;      // Bind to all available network interfaces
    sin.sin_port = htons(server_port);     // Set the port number, converting to network byte order


    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {    // Bind the socket to the specified address and port
        perror("error binding to socket");  // Print an error message if binding fails
    }

    struct sockaddr_in from;     // Define the structure to hold the client's address
    unsigned int from_len = sizeof(struct sockaddr_in);// Length of the client's address structure
    char buffer[4096];// Buffer to hold received data
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);    // Receive data from a client
    if (bytes < 0) {
        perror("error reading from socket");    // Print an error message if receiving fails
    }

    cout << "The client sent: " << buffer << endl; // Display the received message

    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from)); // Send the received message back to the client
    if (sent_bytes < 0) {
        perror("error writing to socket");  // Print an error message if sending fails
    }

    close(sock);    // Close the socket to free resources

    return 0;
}