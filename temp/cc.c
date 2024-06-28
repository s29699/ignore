#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6969
#define MAXLINE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    char query[MAXLINE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation failed\n");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        printf("Invalid address or Address not supported\n");
        return -1;
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // Read initial server message
    int n = read(sockfd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("Server: %s", buffer);

    // Enter employee ID
    fgets(query, MAXLINE, stdin);
    query[strcspn(query, "\n")] = 0;  // Remove newline character
    write(sockfd, query, strlen(query) + 1);

    // Read server response, including the validation and some queries
    n = read(sockfd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    printf("Server: %s", buffer);

    // Communicate with the server
    while (1) {
        printf("You: ");
        fgets(query, MAXLINE, stdin);
        query[strcspn(query, "\n")] = 0;  // Remove newline character
        write(sockfd, query, strlen(query) + 1);

        n = read(sockfd, buffer, sizeof(buffer));
        if (n <= 0) {
            printf("Server disconnected\n");
            break;
        }
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);

        if (strcasecmp(query, "bye") == 0) {
            printf("Connection closed by server\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}


