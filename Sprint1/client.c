// Client Code: client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int client_socket;
char alias[50];

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        printf("%s\n", buffer);
    }

    return NULL;
}

void *send_messages(void *arg) {
    char message[BUFFER_SIZE];

    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character
        send(client_socket, message, strlen(message), 0);
    }

    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t send_thread, receive_thread;

    printf("Enter your alias: ");
    fgets(alias, 50, stdin);
    alias[strcspn(alias, "\n")] = '\0'; // Remove newline character

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    send(client_socket, alias, strlen(alias), 0);

    if (pthread_create(&receive_thread, NULL, receive_messages, NULL) != 0) {
        perror("Could not create receive thread");
        return 1;
    }

    if (pthread_create(&send_thread, NULL, send_messages, NULL) != 0) {
        perror("Could not create send thread");
        return 1;
    }

    pthread_join(receive_thread, NULL);
    pthread_join(send_thread, NULL);

    close(client_socket);
    return 0;
}

