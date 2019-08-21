#pragma once
#include <stddef.h>

void error(char *msg);
void print_msg(char* msg);
int send_data(int sockfd, const char* data, size_t size);