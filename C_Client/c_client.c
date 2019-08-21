#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "C_Helper/c_helper.h"

int main(int argc, char* argv[]){
    if(argc < 3){
        print_msg("No port supplied. Usage: ./c_client SERVER_ADDR PORT_NUMBER");
        return -EINVAL;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); // Create IP Socket. AF_INET: Internet Socket, SOCK_STREAM: TCP, IPPROTO_IP: IP Protocol.
    if (sockfd < 0){
        error("Can't open socket");
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; // IP Addresses
    unsigned short portno = atoi(argv[2]);
    server_addr.sin_port = htons(portno); // Make sure to use network byte order (Big Endian)
    int status = inet_pton(AF_INET, argv[1], &server_addr.sin_addr); // Convert text IP to binary uint32_t form.
    if (status < 0){
        print_msg("IP Invalid. *.*.*.*, *:[0, 255]");
        return -EINVAL;
    }
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        error("Socket connection failed");
    }
    char req[1024] = {0};
    sprintf(req ,"GET / HTTP/1.1\nHost: %s\nConnection: close", argv[1]); // Create HTTP Request
    status = send_data(sockfd, req, strlen(req)); // Send request
    if(status != strlen(req)){
        print_msg("Error sending request");
        return -EIO;
    }
    close(sockfd);
    return 0;
}