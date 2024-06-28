// server.c
#include "server.h"

pthread_mutex_t lock;

void start_server() {
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    loadDatabase();
    loadEmployeeIDs();

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        log_message("FATAL", "Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        log_message("FATAL", "Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) == -1) {
        log_message("FATAL", "Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    log_message("INFO", "Server listening on port 8080");

    while (1) {
        len = sizeof(cliaddr);
        if ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) == -1) {
            log_message("WARNING", "Accept failed");
            continue;
        }

        pthread_mutex_lock(&lock);
        ClientInfo *clientInfo = malloc(sizeof(ClientInfo));
        if (clientInfo == NULL) {
            log_message("ERROR", "Memory allocation failed for client info");
            close(newsockfd);
            continue;
        }
        clientInfo->sockfd = newsockfd;
        clientInfo->clientaddr = cliaddr;
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, (void *)clientInfo);
    }

    close(sockfd);
}

void *handle_client(void *arg) {
    ClientInfo *clientInfo = (ClientInfo *)arg;
    int sockfd = clientInfo->sockfd;
    struct sockaddr_in cliaddr = clientInfo->clientaddr;
    free(clientInfo);

    char buffer[MAXLINE];
    char response[MAXLINE];
    char employeeID[100];
    char employeeDetails[MAXLINE];
    int validEmployee = 0;

    pthread_mutex_unlock(&lock);

    // Ask for employee ID and validate
    write(sockfd, "Enter your employee ID: ", strlen("Enter your employee ID: "));
    memset(employeeID, 0, sizeof(employeeID));
    int n = read(sockfd, employeeID, sizeof(employeeID));
    if (n <= 0) {
        close(sockfd);
        log_message("INFO", "Client disconnected during employee ID input");
        return NULL;
    }
    employeeID[strcspn(employeeID, "\n")] = '\0';  // Remove newline character
    log_message("DEBUG", employeeID);  // Log the received employee ID

    // Validate employee ID
    if (validateEmployeeID(employeeID)) {
        validEmployee = 1;
        write(sockfd, "Employee ID validated. How can I help you?\n", strlen("Employee ID validated. How can I help you?\n"));
        log_message("INFO", "Employee ID validated.");
    } else {
        write(sockfd, "Invalid ID. Please enter your details: ", strlen("Invalid ID. Please enter your details: "));
        memset(employeeDetails, 0, sizeof(employeeDetails));
        n = read(sockfd, employeeDetails, sizeof(employeeDetails));
        if (n <= 0) {
            close(sockfd);
            log_message("INFO", "Client disconnected during employee details input");
            return NULL;
        }
        employeeDetails[strcspn(employeeDetails, "\n")] = '\0';  // Remove newline character
        log_message("INFO", "Received new employee details");
        write(sockfd, "Details received. How can I help you?\n", strlen("Details received. How can I help you?\n"));
    }

    while (1) {
        memset(buffer, 0, MAXLINE);
        n = read(sockfd, buffer, sizeof(buffer));
        if (n <= 0) {
            close(sockfd);
            log_message("INFO", "Client disconnected");
            return NULL;
        }

        buffer[n] = '\0';
        log_message("DEBUG", buffer);

        if (strcasecmp(buffer, "bye") == 0) {
            write(sockfd, "Goodbye!\n", strlen("Goodbye!\n"));
            close(sockfd);
            log_message("INFO", "Client disconnected");
            return NULL;
        }

        processQuery(buffer, response);
        write(sockfd, response, strlen(response));
        log_message("INFO", "Response sent to client");
    }

    return NULL;
}

