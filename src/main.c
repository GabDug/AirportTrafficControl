#include <stdio.h>
#include "main.h"
#include "QueueArray.c"
#include "struct.h"
#include "struct.c"
#include "QueueArray.h"
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
int check_alphanum(int length) {
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
}*/

void getHourTime(int t, char *output) {

    // next_takeoff = (avion_tmp->heure_decollage[3] - '0') + 10*(avion_tmp->heure_decollage[2] - '0')+60*(avion_tmp->heure_decollage[1] - '0') + 600*(avion_tmp->heure_decollage[0] - '0') ;
    int minutes = t % 60;
    int hours = t / 60;
    printf("%02d%02d ", hours, minutes);
    snprintf(output, sizeof(output), "%02d%02d ", hours, minutes);
}


void addTakeoff(){



}

int main() {
    printf("AIRPORT CONTROL SIMULATOR - WIP\n");

    // Loading


    // Creating the company
    Compagnie *comp = (Compagnie *) malloc(sizeof(Compagnie));
    comp->nom = strdup("AyBiCe");
    comp->acronyme = strdup("ABC");


    Cellule_compagnie *c_comp = (Cellule_compagnie *) malloc(sizeof(Cellule_compagnie));
    c_comp->comp = comp;
    c_comp->suivant = NULL;
    // UNUSED ATM simple_insertTop(mylist, e1);

    Avion *avion1 = (Avion *) malloc(sizeof(Avion));
    avion1->identifiant = strdup("ABC001");
    avion1->carburant = 1000;
    avion1->consommation = 0; // ATM
    avion1->heure_decollage = strdup("0100");
    avion1->compagnie = comp;

    QueueAvion *q_takeoff = (QueueAvion *) malloc(sizeof(Queue));

    QueueAvion *QueueTakeoff = (QueueAvion *) malloc(sizeof(QueueAvion));
    initQueueArray(QueueTakeoff, 20);
    pushQueueArray(QueueTakeoff, avion1);
    displayQueueArray(QueueTakeoff);

    char formatted_time[] = "0000";

    int t; // time, 0 to 1439 (23:59)
    for (t = 0; t < 1439; t++) {
        getHourTime(t, formatted_time);
        printf("[DEBUG] %d / %s\n", t, formatted_time);

        Avion *avion_tmp = (Avion *) malloc(sizeof(Avion));
        if (!isEmpty(QueueTakeoff)) {
            getQueueArray(QueueTakeoff, avion_tmp);
            int next_takeoff = -1;
            next_takeoff = (avion_tmp->heure_decollage[3] - '0') + 10 * (avion_tmp->heure_decollage[2] - '0') +
                           60 * (avion_tmp->heure_decollage[1] - '0') + 600 * (avion_tmp->heure_decollage[0] - '0');
            printf("[DEBUG] Next takeoff: %d / %s\n", next_takeoff, avion_tmp->heure_decollage);
            if (t >= next_takeoff) {
                if (delQueueArray(QueueTakeoff)) {
                    printf("[%04d] Takeoff\n", t);
                }
                if (!isEmpty(QueueTakeoff)) {
                    displayQueueArray(QueueTakeoff);
                }
            } else {
                printf("[%04d] No Takeoff, next takeoff: %s\n", t, avion_tmp->heure_decollage);
            }
        }

        char code[20];
        // Safe input
        printf("> ");

        char *id =(char*) malloc(4);
        strncpy(id, code, 2);
        char *hour = (char*) malloc(4);
        strncpy(id, code+9, 13);
        scanf("%4s-%c-%4s",id, NULL, hour);
        printf("  ALORS %s | %s\n", id, hour);
        fgets(code, 20, stdin);
        printf(" [DEBUG] Input: %s", code);
        if (code[7] == 'D') {
            char *id =(char*) malloc(4);
            strncpy(id, code, 2);
            char *hour = (char*) malloc(4);
            strncpy(id, code+9, 13);
            printf("  ALORS %s | %s\n", id, hour);

        }

/*
        // Check the event code
        if (!checkCode(code)){
            printf("Incorrect code");
            continue;
        }
*/

        //
        //printf("[%04d] RAS\n", t);

    }

    printf("[%04d] Exiting...\n", t);
    return 0;
}
