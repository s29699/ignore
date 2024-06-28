// server.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

// Define a structure for our chatbot's responses
typedef struct {
    char *query;
    char *response;
} Response;

Response responses[] = {
    {"hello", "Hi there! How can I assist you today?"},
    {"info", "I can provide information about our college for freshers. What would you like to know?"},
    {"courses", "We offer a variety of courses including Computer Science, Mechanical Engineering, and Civil Engineering."},
    {"admission", "Our admission process is online. Please visit our website for more details."},
    {"bye", "Goodbye! Have a great day!"},
    {NULL, NULL}
};

void handle_client(int new_socket) {
    char buffer[MAXLINE];
    int n;

    // Read the client's query
    n = read(new_socket, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("read");
        close(new_socket);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';

    // Search for a matching response
    for (int i = 0; responses[i].query != NULL; i++) {
        if (strcmp(buffer, responses[i].query) == 0) {
            write(new_socket, responses[i].response, strlen(responses[i].response));
            close(new_socket);
            return;
        }
    }

    // Default response if no match is found
    char *default_response = "I'm sorry, I don't understand that query.";
    write(new_socket, default_response, strlen(default_response));
    close(new_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept and handle incoming connections
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) >= 0) {
        handle_client(new_socket);
    }

    if (new_socket < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}
