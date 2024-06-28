// utils.c
#include "utils.h"
#include <stdio.h>

void log_message(const char *level, const char *message) {
    printf("[%s] %s\n", level, message);
}

