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

int send_get_request(int sockfd, char* ip, char* location){
    char req[1024] = {0};
    sprintf(req ,"GET %s HTTP/1.1\nHost: %s\nConnection: close", location, ip); // Create HTTP Request
    int status = send_data(sockfd, req, strlen(req)); // Send request
    if(status != strlen(req)){
        print_msg("Error sending request");
        return -EIO;
    }
    return 0;
}
int connect_to_server(int sockfd, char* ip, unsigned short portno){
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; // IP Addresses
    server_addr.sin_port = htons(portno); // Make sure to use network byte order (Big Endian)
    int status = inet_pton(AF_INET, ip, &server_addr.sin_addr); // Convert text IP to binary uint32_t form.
    if (status < 0){
        print_msg("IP Invalid. *.*.*.*, *:[0, 255]");
        return -EINVAL;
    }
    status = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(status < 0){
        return -errno;
    }
}

int main(int argc, char* argv[]){
    if(argc < 3){
        print_msg("No port supplied. Usage: ./c_client SERVER_ADDR PORT_NUMBER");
        return -EINVAL;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP); // Create IP Socket. AF_INET: Internet Socket, SOCK_STREAM: TCP, IPPROTO_IP: IP Protocol.
    if (sockfd < 0){
        error("Can't open socket");
    }

    unsigned short portno = atoi(argv[2]);
    int status = connect_to_server(sockfd, argv[1], portno);
    if (status != -EINVAL && status < 0){
        return status;
    }
    else if(status == -EINVAL){
        return status;
    }

    status = send_get_request(sockfd, argv[1], "/");
    if(status < 0){
        return status;
    }
    close(sockfd);
    return 0;
}