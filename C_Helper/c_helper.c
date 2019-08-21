#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "c_helper.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void print_msg(char* msg)
{
    printf("%s\n", msg);
}

int send_data(int sockfd, const char* msg, size_t size){
    size_t sent = 0;
    int bytes = 0;
    int ret = 0;
    while (sent < size){
        bytes = write(sockfd, msg+sent, size-sent);
        if (bytes < 0){
            ret = bytes;
            break;
        }
        if (bytes == 0){
            break;
        }
        sent+=bytes;
    }
    if (bytes >= 0){
        return size;
    }
    return ret;
}