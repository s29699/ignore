// Server Code: server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8000
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

int client_sockets[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    char *keyword;
    char *response;
} KeywordResponse;

KeywordResponse keyword_responses[] = {
    {"hello", "Server: Hello! How can I help you?"},
    {"bye", "Server: Goodbye! Have a great day!"},
    {"help", "Server: How can I assist you?"},
    {"thanks", "Server: You're welcome!"},
    {"time", "Server: I am just a server, but you can check your system's clock."},
    {"name", "Server: I am a simple chat server."}
};

int keyword_count = sizeof(keyword_responses) / sizeof(keyword_responses[0]);

void broadcast_message(char *message, int exclude_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (client_sockets[i] != exclude_socket) {
            if (send(client_sockets[i], message, strlen(message), 0) < 0) {
                perror("Error sending message");
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void send_message_to_client(char *message, int client_socket) {
    if (send(client_socket, message, strlen(message), 0) < 0) {
        perror("Error sending message");
    }
}

void check_keywords_and_respond(char *message, int client_socket) {
    for (int i = 0; i < keyword_count; i++) {
        if (strstr(message, keyword_responses[i].keyword) != NULL) {
            send_message_to_client(keyword_responses[i].response, client_socket);
            break;
        }
    }
}

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[BUFFER_SIZE];
    int read_size;

    // Receive alias from the client
    if ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        char welcome_message[BUFFER_SIZE];
        sprintf(welcome_message, "%s has joined the chat!\n", buffer);
        broadcast_message(welcome_message, client_socket);
    }

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';
        broadcast_message(buffer, client_socket);
        check_keywords_and_respond(buffer, client_socket);
    }

    // Client disconnected
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (client_sockets[i] == client_socket) {
            for (int j = i; j < client_count - 1; j++) {
                client_sockets[j] = client_sockets[j + 1];
            }
            break;
        }
    }
    client_count--;
    pthread_mutex_unlock(&clients_mutex);

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t tid;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len))) {
        pthread_mutex_lock(&clients_mutex);
        client_sockets[client_count++] = client_socket;
        pthread_mutex_unlock(&clients_mutex);

        if (pthread_create(&tid, NULL, handle_client, (void *)&client_socket) != 0) {
            perror("Could not create thread");
            return 1;
        }
    }

    if (client_socket < 0) {
        perror("Accept failed");
        close(server_socket);
        return 1;
    }

    close(server_socket);
    return 0;
}
