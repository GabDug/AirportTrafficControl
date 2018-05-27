#include <stdlib.h>
#include <stdio.h>
#include "log.h"


// Log adapted from http://www.falloutsoftware.com/tutorials/c/c1.htm

int LogCreated = FALSE;

void Log(char *message) {
    FILE *file;

    if (!LogCreated) {
        file = fopen(LOGFILE, "w");
        LogCreated = TRUE;
    } else
        file = fopen(LOGFILE, "a");

    if (file == NULL) {
        if (LogCreated)
            LogCreated = FALSE;
        return;
    } else {
        fputs(message, file);
        fclose(file);
    }

    if (file)
        fclose(file);
}
