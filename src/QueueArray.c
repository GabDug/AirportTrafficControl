//
// Created by gabri on 05/04/2018.
//

#include "QueueArray.h"
#include <stdio.h>
#include <stdlib.h>


void initQueueArray(QueueAvion *plane, int size) {
    plane->size = size;
    // The size is from 0 so if size is 2 you can put 3 elements.
    plane->in = -1;
    plane->out = 0;
    plane->plane = (Avion *) malloc(size * sizeof(Avion));
}

void pushQueueArray(QueueAvion *plane, Avion *new_plane) {
    // Check if FULL
    if (!isFull(plane)) {
        plane->in++;
        plane->plane[plane->in] = *new_plane;
    } else {
        printf(" [DEBUG] Can't push in full QueueAvion!\n");
    }

}

//int popQueueArray(QueueAvion *plane, Avion *popped_plane) {
int popQueueArray(QueueAvion *plane, Avion *popped_plane) {
    if (!isEmpty(plane)) {
        *popped_plane = plane->plane[plane->out];
        plane->out++;
        return TRUE;
    } else {
        printf(" [DEBUG] Can't pop from empty QueueAvion!\n");
        return FALSE;
    }
}

int delQueueArray(QueueAvion *plane) {
    if (!isEmpty(plane)) {
        plane->out++;
        return TRUE;
    } else {
        printf(" [DEBUG] Can't pop from empty QueueAvion!\n");
        return FALSE;
    }
}

int getQueueArray(QueueAvion *plane, Avion *popped_plane) {
    if (!isEmpty(plane)) {
        *popped_plane = plane->plane[plane->out];
        //plane->out++;
        return TRUE;
    } else {
        printf(" [DEBUG] No plane to see QueueAvion!\n");
        return FALSE;
    }
}

void displayQueueArray(QueueAvion *plane) {
    if (!isEmpty(plane)) {
        printf("Printing QueueAvion:\n");
        int i;
        for (i = plane->out; i <= plane->in; i++) {
            printf("%s\n", plane->plane[i].identifiant);
        }
    } else {
        printf(" [DEBUG] Can't print empty QueueAvion!\n");
        return;
    }
}


int isEmpty(QueueAvion *plane) {
    if (plane->out <= plane->in)
        return FALSE;
    else
        return TRUE;
}

int isFull(QueueAvion *plane) {
    if (plane->in < plane->size)
        return FALSE;
    else
        return TRUE;
}
/*
int main() {
    QueueAvion *QueueAvion = (QueueAvion *) malloc(sizeof(QueueAvion));
    initQueueArray(QueueAvion, 1000);
    displayQueueArray(QueueAvion);

    pushQueueArray(QueueAvion, 10);
    pushQueueArray(QueueAvion, 20);
    pushQueueArray(QueueAvion, 30);
    pushQueueArray(QueueAvion, 40);
    pushQueueArray(QueueAvion, 50);
    pushQueueArray(QueueAvion, 60);
    displayQueueArray(QueueAvion);

    int data;

    if (popQueueArray(QueueAvion, &data)) {
        printf("Value: %d\n", data);
    }
    displayQueueArray(QueueAvion);

    return 0;
}*/