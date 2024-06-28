// server.h
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "database.h"
#include "employee.h"
#include "utils.h"

#define PORT 6969
#define MAXLINE 1024
#define MAXCLIENTS 100

typedef struct {
    int sockfd;
    struct sockaddr_in clientaddr;
} ClientInfo;

void start_server();

void *handle_client(void *arg);

#endif /* SERVER_H */

