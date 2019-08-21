#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "C_Helper/c_helper.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("%s", "Not port supplied. Usage: ./c_server PORT_NUMBER");
        exit(1);
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); // Create IP Socket. AF_INET: Internet Socket, SOCK_STREAM: TCP, IPPROTO_IP: IP Protocol.
    if (sockfd < 0){
        error("Can't open socket");
    }
    char buffer[256] = {0};
    struct sockaddr_in server_addr, client_addr;
    unsigned short portno = atoi(argv[1]);
    server_addr.sin_family = AF_INET; // IP Addresses
    server_addr.sin_port = htons(portno); // Make sure to use network byte order (Big Endian)
    server_addr.sin_addr.s_addr = INADDR_ANY;
    return 0;
}