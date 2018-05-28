
#ifndef AIRPORT_LOG_H
#define AIRPORT_LOG_H

#include "const.h"

#define LOGFILE "airport.log"

void Log(char *f_t, char *plane_code, char operation, int fuel, int consumption);

#endif //AIRPORT_LOG_H
