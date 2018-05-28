#include <stdlib.h>
#include <stdio.h>
#include "log.h"


// Log adapted from http://www.falloutsoftware.com/tutorials/c/c1.htm

int log_created = FALSE;

void Log(char *f_t, char *plane_code, char operation, int fuel, int consumption);

void Log(char *f_t, char *plane_code, char operation, int fuel, int consumption) {
    FILE *file;

    if (!log_created) {
        file = fopen(LOGFILE, "w");
        log_created = TRUE;
    } else
        file = fopen(LOGFILE, "a");

    if (file == NULL) {
        if (log_created)
            log_created = FALSE;
        return;
    } else {
        // Generate a message
        char output[20];
        if (fuel == NULL || consumption == NULL) {
            snprintf(output, sizeof(output), "%6s-%c-%4s-----\n", plane_code, operation, f_t);
        } else if (fuel != NULL && consumption != NULL) {
            snprintf(output, sizeof(output), "%6s-%c-%4s-%02d-%02d\n", plane_code, operation, f_t, fuel, consumption);
        } else
            printf("ERROR LOGGING");

        fputs(output, file);
        fclose(file);
    }

    if (file)
        fclose(file);
}
