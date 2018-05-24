#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>


int safeinput(char *str, int length) {
    char *endPosition = NULL;

    if (fgets(str, length, stdin) != NULL) {
        endPosition = strchr(str, '\n');
        if (endPosition != NULL) {
            *endPosition = '\0';
        }
        return 1;
    } else {
        return 0;
    }
}

/*
int check_alphanum(char s[19], int length) {
    for (i = 0; i < length; i++) {
        int valid = false;

        valid |= s[i] >= 'a' && s[i] <= 'z';
        valid |= s[i] >= 'A' && s[i] <= 'Z';
        valid |= s[i] >= '0' && s[i] <= '9';
        valid |= s[i] == '-';

        if (!valid) {
            return 0;
        }
    }
    return 1;
}


int checkCode(int length) {
    for (i = 0; i < length; i++) {
        int valid = false;

        valid |= check_alphanum();

        if (!valid) {
            return 0;
        }

    }
    return 1;
}
*/

int main() {
    printf("AIRPORT CONTROL SIMULATOR - WIP\n");


    // Loading


    int t; // time
    for (t = 0; t < 1439; t++) {
        t = 0;

        char code[20];
        // Safe input
        fgets(code, 20, stdin);
        // printf("%s",code);


        // Check the event code
       /* if (!checkCode(code)){
            printf("Incorrect code");
            continue;
        }*/






            //
        return 0;

    }
}
