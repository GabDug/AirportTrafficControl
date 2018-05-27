//
// Created by Gabriel DUGNY on 24/05/2018.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell_io.h"


void purge();

void purge() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {}
}

void clean(char *str) {
    char *p = strchr(str, '\n');

    if (p) {
        *p = 0;
    } else {
        purge();
    }
}

int safeInput(char *str, int length) {
    char *endPosition = NULL;

    if (fgets(str, length, stdin) != NULL) {
        endPosition = strchr(str, '\n');
        if (endPosition != NULL) {
            *endPosition = '\0';
        }
        clean(str);
        return 1;
    } else {
        return 0;
    }
}

