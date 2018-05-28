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
}QueueAvion;


int isEmpty(QueueAvion *qu);
int isFull(QueueAvion *qu);

#endif //C_QUEUEARRAY_H
