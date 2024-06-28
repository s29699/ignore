// database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include "utils.h"

typedef struct {
    char query[100];
    char response[100];
} ChatBotDB;

extern ChatBotDB database[MAXCLIENTS];
extern int dbSize;

void loadDatabase();

void processQuery(char *query, char *response);

#endif /* DATABASE_H */

