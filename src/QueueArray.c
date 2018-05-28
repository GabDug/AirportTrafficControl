#include "QueueArray.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>


void initQueueArray(QueueAvion *plane, int size) {
    plane->size = size;
    // The size is from 0 so if size is 2 you can put 3 elements.
    plane->in = -1;
    plane->out = 0;
    plane->plane = (Cellule_Avion*) malloc(size * sizeof(Cellule_Avion));
}

void pushQueueArray(QueueAvion *plane, Cellule_Avion *new_plane) {
    // Check if FULL
    if (!isFull(plane)) {
        plane->in++;
        plane->plane[plane->in] = *new_plane;
    } else {
        printf(" [DEBUG] Can't push in full QueueAvion!\n");
    }

}

//int popQueueArray(QueueAvion *plane, Avion *popped_plane) {
int popQueueArray(QueueAvion *plane, Cellule_Avion *popped_plane) {
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

int getQueueArray(QueueAvion *plane, Cellule_Avion *popped_plane) {
    if (!isEmpty(plane)) {
        *popped_plane = plane->plane[plane->out];
        //plane->out++;
        return TRUE;
    } else {
        printf(" [DEBUG] No plane to see QueueAvion!\n");
        return FALSE;
    }
}

void displayTakeoffQueueArray(QueueAvion *plane) {
    if (!isEmpty(plane)) {
        printf("Takeoff Queue:\n");
        int i;
        for (i = plane->out; i <= plane->in; i++) {
            printf("  %s @ %s\n", plane->plane[i].avion->identifiant, plane->plane[i].avion->heure_decollage);
        }
    } else {
        printf(" [DEBUG] Can't print empty Takeoff Queue!\n");
        return;
    }
}

void displayQueueArray(QueueAvion *plane) {
    if (!isEmpty(plane)) {
        int i;
        for (i = plane->out; i <= plane->in; i++) {
            printf("%s\n", plane->plane[i].avion->identifiant);
        }
    } else {
        printf(" [DEBUG] Can't print empty Takeoff Queue!\n");
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
    displayTakeoffQueueArray(QueueAvion);

    return 0;
}*/