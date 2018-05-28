#ifndef C_QUEUEARRAY_H
#define C_QUEUEARRAY_H

#define TRUE 1
#define FALSE 0

#include "struct.h"

typedef struct {
    Cellule_Avion *plane;
    int size;
    int in;
    int out;
} QueueAvion;


int is_empty_takeoff_queue(QueueAvion *queue);

int is_full_takeoff_queue(QueueAvion *queue);

#endif //C_QUEUEARRAY_H
