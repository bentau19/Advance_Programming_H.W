#include <iostream>          // For input/output operations
#include <sys/socket.h>      // For socket functions
#include <stdio.h>           // For standard I/O functions like perror
#include <netinet/in.h>      // For sockaddr_in structure
#include <arpa/inet.h>       // For inet_addr function
#include <unistd.h>          // For close function
#include <string.h>          // For memset and string operations

using namespace std;

int main() {

    const char* ip_address = "127.0.0.1";  // The IP address of the server
    const int port_no = 5555;              // The port number of the server


    int sock = socket(AF_INET, SOCK_STREAM, 0);// Make new TCP socket
     if (sock < 0) {  // Check if the socket was created successfully
        perror("error creating socket");  // Print an error message and exit if the socket creation fails
    }

    struct sockaddr_in sin; // Define the server address structure
    memset(&sin, 0, sizeof(sin));   // Zero out the structure
    sin.sin_family = AF_INET;                     // Set the address family to IPv4
    sin.sin_addr.s_addr = inet_addr(ip_address);  // Convert the IP address string to a binary format
    sin.sin_port = htons(port_no);                // Convert the port number to network byte order

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { // Connect to the server using the socket and the server address defined earlier
        perror("error connecting to server");// If the connection fails, print an error message
    }

    char data_addr[] = "Im a message";// Define the message to send to the server
    int data_len = strlen(data_addr);// Calculate the length of the message
    int sent_bytes = send(sock, data_addr, data_len, 0);// Send the message to the server using the socket

    if (sent_bytes < 0) {// Check if there was an error sending the message
    // error
    }

    char buffer[4096];  // Define a buffer to store the server's response
    int expected_data_len = sizeof(buffer);  // Get the size of the buffer for receiving data
    int read_bytes = recv(sock, buffer, expected_data_len, 0);// Receive data from the server and store it in the buffer
    if (read_bytes == 0) {  // Check if the server closed the connection
    // connection is closed
    }
    else if (read_bytes < 0) {  // Check for any error while receiving data
    // error
    }
    else {  // If data was successfully received
        cout << buffer;  // Print the received data to the console
    }

    close(sock);  // Close the socket connection to the server


    return 0;
}