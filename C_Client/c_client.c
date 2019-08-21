#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "C_Helper/c_helper.h"

int main(int argc, char* argv[]){
    if(argc < 3){
        error("No port supplied. Usage: ./c_client SERVER_ADDR PORT_NUMBER");
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); // Create IP Socket. AF_INET: Internet Socket, SOCK_STREAM: TCP, IPPROTO_IP: IP Protocol.
    if (sockfd < 0){
        error("Can't open socket");
    }
    char buffer[256] = {0};
    struct sockaddr_in server_addr;
    u_short portno = atoi(argv[2]);
    server_addr.sin_family = AF_INET; // IP Addresses
    server_addr.sin_port = htons(portno); // Make sure to use network byte order (Big Endian)
    
    return 0;
}