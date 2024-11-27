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

    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Make new UDP socket
    if (sock < 0) {  // Check if the socket was created successfully
        perror("error creating socket");  // Print an error message and exit if the socket creation fails
    }

    struct sockaddr_in sin; // Define the server address structure
    memset(&sin, 0, sizeof(sin));   // Zero out the structure
    sin.sin_family = AF_INET;                     // Set the address family to IPv4
    sin.sin_addr.s_addr = inet_addr(ip_address);  // Convert the IP address string to a binary format
    sin.sin_port = htons(port_no);                // Convert the port number to network byte order

    char data[] = "hello";  // The message to send
    int data_len = sizeof(data);  // Get the length of the message

    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin)); // Send the data to the server
    if (sent_bytes < 0) {  // Check if the data was sent successfully
        perror("error writing to socket");  // Print an error message and exit if the sending fails
        close(sock);
        return 1;
    }

    struct sockaddr_in from;                      // Define a structure to store the sender's information
    unsigned int from_len = sizeof(struct sockaddr_in);  // Length of the sender's address structure
    char buffer[4096];                            // Buffer to store the response
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);  //get the data from server
    if (bytes < 0) {  // Check if data was received successfully
        perror("error reading from socket");  // Print an error message and exit if the receiving fails
        close(sock);
        return 1;
    }

    
    cout << "The server sent: " << buffer << endl; // Print the server's response

    
    close(sock); // Close the socket to free resources

    return 0;
}