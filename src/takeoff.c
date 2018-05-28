#include "takeoff.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>


int get_plane_takeoff_queue(QueueAvion *queue, Cellule_Avion *popped_plane);

void display_takeoff_queue(QueueAvion *, char *);

void init_takeoff_queue(QueueAvion *queue, int size);

int del_plane_takeoff_queue(QueueAvion *plane);

void add_plane_takeoff_queue(QueueAvion *queue, Cellule_Avion *new_plane);


int del_plane_takeoff_queue(QueueAvion *plane) {
    if (!is_empty_takeoff_queue(plane)) {
        plane->out++;
        return TRUE;
    } else {
        printf(" [DEBUG] Can't pop from empty QueueAvion!\n");
        return FALSE;
    }
}

int get_plane_takeoff_queue(QueueAvion *queue, Cellule_Avion *popped_plane) {
    if (!is_empty_takeoff_queue(queue)) {
        *popped_plane = queue->plane[queue->out];
        //queue->out++;
        return TRUE;
    } else {
        printf(" [DEBUG] No plane to see QueueAvion!\n");
        return FALSE;
    }
}

void display_takeoff_queue(QueueAvion *queue, char *f_t) {
    if (!is_empty_takeoff_queue(queue)) {
        if (f_t != NULL)
            printf("[%s] Takeoff Queue:\n", f_t);
        else
            printf("Takeoff Queue:\n");

        int i;
        for (i = queue->out; i <= queue->in; i++) {
            printf("  %s @ %s\n", queue->plane[i].avion->identifiant, queue->plane[i].avion->heure_decollage);
        }
    } else {
        if (f_t != NULL)
            printf("[%s] No planes waiting to takeoff!\n", f_t);
        else
            printf("No planes waiting to takeoff!\n");
        return;
    }
}

void init_takeoff_queue(QueueAvion *queue, int size) {
    queue->size = size;
    // The size is from 0 so if size is 2 you can put 3 elements.
    queue->in = -1;
    queue->out = 0;
    queue->plane = (Cellule_Avion *) malloc(size * sizeof(Cellule_Avion));
}

void add_plane_takeoff_queue(QueueAvion *queue, Cellule_Avion *new_plane) {
    // Check if FULL
    if (!is_full_takeoff_queue(queue)) {
        queue->in++;
        queue->plane[queue->in] = *new_plane;
    } else {
        printf(" [DEBUG] Can't push in full QueueAvion!\n");
    }

}

int is_empty_takeoff_queue(QueueAvion *queue) {
    if (queue->out <= queue->in)
        return FALSE;
    else
        return TRUE;
}

int is_full_takeoff_queue(QueueAvion *queue) {
    if (queue->in < queue->size)
        return FALSE;
    else
        return TRUE;
}
