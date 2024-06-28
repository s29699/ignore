#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 2001
#define MAXLINE 1024
#define MAXCLIENTS 100
#define MAXEMPLOYEES 100

typedef struct {
    char query[100];
    char response[1000];
} ChatBotDB;

typedef struct {
    int sockfd;
    struct sockaddr_in clientaddr;
} ClientInfo;

pthread_mutex_t lock;
ChatBotDB database[MAXCLIENTS];
char employeeIDs[MAXEMPLOYEES][20];
char employeeNames[MAXEMPLOYEES][100];
int dbSize = 0;
int empSize = 0;

void log_message(const char *level, const char *message) {
    printf("[%s] %s\n", level, message);
}

void processQuery(char *query, char *response) {
    for (int i = 0; i < dbSize; i++) {
        if (strcasecmp(query, database[i].query) == 0) {
            strcpy(response, database[i].response);
            return;
        }
    }
    strcpy(response, "I'm sorry, I don't understand your query.\n");
    for (int i = 0; i < dbSize; i++) {  // Sending first 5 queries as an example
        char queryMessage[MAXLINE];
        snprintf(queryMessage, sizeof(queryMessage), "%s %s\n", "- ", database[i].query);
        strncat(response, queryMessage, sizeof(response) - strlen(response) - 1);
    }
    strncat(response, "Select from the listed queries\n", sizeof(response) - strlen(response) - 1);

    log_message("INFO", "Queries sent to the client");
}

void loadDatabase() {
    FILE *file = fopen("database.txt", "r");
    if (!file) {
        log_message("FATAL", "Failed to open database file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %[^\n]", database[dbSize].query, database[dbSize].response) != EOF) {
        dbSize++;
    }

    fclose(file);
    log_message("INFO", "Database loaded successfully");
}

void loadEmployeeIDs() {
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        log_message("FATAL", "Failed to open employee IDs file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s %s", employeeIDs[empSize], employeeNames[empSize]) != EOF) {
        empSize++;
    }

    fclose(file);
    log_message("INFO", "Employee IDs loaded successfully");
}

int validateEmployeeID(char *employeeID) {
    for (int i = 0; i < empSize; i++) {
        if (strcasecmp(employeeID, employeeIDs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int checkEmployeeDetails(char *name, char *employeeID) {
    for (int i = 0; i < empSize; i++) {
        if (strcasecmp(name, employeeNames[i]) == 0) {
            strncpy(employeeID, employeeIDs[i], sizeof(employeeIDs[i]) - 1);
            employeeID[sizeof(employeeIDs[i]) - 1] = '\0';
            return 1;
        }
    }
    return 0;
}

void handleClient(void *arg) {
    ClientInfo clientInfo = *(ClientInfo *)arg;
    int sockfd = clientInfo.sockfd;
    char buffer[MAXLINE];
    char response[MAXLINE];
    char employeeID[100];
    char employeeDetails[100];
    char message[MAXLINE * 4];  // Buffer to hold the validation message and queries
    int validEmployee = 0;

    pthread_mutex_unlock(&lock);

    // Ask for employee ID and validate
    write(sockfd, "Enter your employee ID: ", strlen("Enter your employee ID: "));
    memset(employeeID, 0, sizeof(employeeID));
    int n = read(sockfd, employeeID, sizeof(employeeID));
    if (n <= 0) {
        close(sockfd);
        log_message("INFO", "Client disconnected during employee ID input");
        return;
    }
    employeeID[strcspn(employeeID, "\n")] = 0;  // Remove newline character
    log_message("DEBUG", employeeID);  // Log the received employee ID

    // Validate employee ID
    if (validateEmployeeID(employeeID)) {
        validEmployee = 1;

        // Prepare validation message along with some database queries
        snprintf(message, sizeof(message), "Employee ID validated. Here are some queries you can ask:\n");

        for (int i = 0; i < dbSize; i++) {  // Sending first 5 queries as an example
            char queryMessage[MAXLINE];
            snprintf(queryMessage, sizeof(queryMessage), "%s %s\n", "- ", database[i].query);
            strncat(message, queryMessage, sizeof(message) - strlen(message) - 1);
        }
        strncat(message, "How can I help you?\n", sizeof(message) - strlen(message) - 1);

        write(sockfd, message, strlen(message));
        log_message("INFO", "Employee ID validated and queries sent.");
    } else {
        write(sockfd, "Invalid ID. Please enter your name: ", strlen("Invalid ID. Please enter your name: \n"));
        memset(employeeDetails, 0, sizeof(employeeDetails));
        n = read(sockfd, employeeDetails, sizeof(employeeDetails));
        if (n <= 0) {
            write(sockfd, "Client Disconnected", strlen("Client Disconnected"));
            close(sockfd);
            log_message("INFO", "Client disconnected during employee details input");
            return;
        }
        employeeDetails[strcspn(employeeDetails, "\n")] = '\0';  // Remove newline character
        log_message("INFO", "Received new employee details");

        if(checkEmployeeDetails(employeeDetails, employeeID)) {
                validEmployee = 1;
        //char msg[MAXLINE];
        snprintf(message, sizeof(message), "Hi %s! Your Employee ID is %s.  Here are some queries you can ask:\n", employeeDetails, employeeID);
        //write(sockfd, msg, strlen(msg));

        for (int i = 0; i < dbSize; i++) {  // Sending first 5 queries as an example
            char queryMessage[MAXLINE];
            snprintf(queryMessage, sizeof(queryMessage), "%s %s\n", "- ", database[i].query);
            strncat(message, queryMessage, sizeof(message) - strlen(message) - 1);
        }
        strncat(message, "How can I help you?\n", sizeof(message) - strlen(message) - 1);

        write(sockfd, message, strlen(message));
        log_message("INFO", "Employee ID validated and queries sent.");

        }else{
                write(sockfd, "Employee not found. Client Disconnected", strlen("Employee not found. Client Disconnected"));
            close(sockfd);
            log_message("INFO", "Client disconnected during employee details input");
            return;
        }
    }

    while (1) {
        memset(buffer, 0, MAXLINE);
        n = read(sockfd, buffer, sizeof(buffer));
        if (n <= 0) {
            close(sockfd);
            log_message("INFO", "Client disconnected");
            return;
        }

        buffer[n] = '\0';
        log_message("DEBUG", buffer);

        if (strcasecmp(buffer, "bye") == 0) {
            write(sockfd, "Goodbye!\n", strlen("Goodbye!\n"));
            close(sockfd);
            log_message("INFO", "Client disconnected");
            return;
        }

        processQuery(buffer, response);
        write(sockfd, response, strlen(response));
        log_message("INFO", "Response sent to client");
    }
}


int main() {
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

    char msg[MAXLINE];
    snprintf(msg, sizeof(msg), "Server listening on port %d", PORT);
    log_message("INFO", msg);

    while (1) {
        len = sizeof(cliaddr);
        if ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) == -1) {
            log_message("WARNING", "Accept failed");
            continue;
        }

        pthread_mutex_lock(&lock);
        ClientInfo clientInfo = {newsockfd, cliaddr};
        pthread_t tid;
        pthread_create(&tid, NULL, (void *)handleClient, (void *)&clientInfo);
    }

    close(sockfd);
    return 0;
}

