#include <stdio.h>
#include "main.h"
#include "QueueArray.c"
#include "struct.h"
#include "struct.c"
#include "QueueArray.h"
#include <stdlib.h>
#include <string.h>
#include "utility.c"

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

void addTakeoff(QueueAvion *QueueTakeoff, Avion *avion );

void getHourTime(int t, char *output) {

    // next_takeoff = (avion_tmp->heure_decollage[3] - '0') + 10*(avion_tmp->heure_decollage[2] - '0')+60*(avion_tmp->heure_decollage[1] - '0') + 600*(avion_tmp->heure_decollage[0] - '0') ;
    int minutes = t % 60;
    int hours = t / 60;
    printf("%02d%02d ", hours, minutes);
    snprintf(output, sizeof(output), "%02d%02d ", hours, minutes);
}

void readCode(char *code, QueueAvion *QueueTakeoff, Compagnie *comp) {
    //char code[] = "DLA043-D-1143------";
    //printf("[DEBUG] Code: %s\n", code);
    if (code[7] == 'D') {
        //char *id = (char *) malloc(6 * sizeof(char));
        char id[6];
        for (int i = 0; i < 6; i++) {
            id[i] = code[i];
        }
        id[6] = '\0';

        char hour[4];
        for (int i = 0; i < 4; i++) {
            hour[i] = code[i + 9];
        }
        hour[4] = '\0';
        printf(" [DEBUG] TAKEOFF ID: %s | HOUR: %s\n ", id, hour);

        Avion *new_plane = (Avion *) malloc(sizeof(Avion));
        new_plane->identifiant = strdup(id);
        new_plane->carburant = 1000;
        new_plane->consommation = 0; // ATM
        new_plane->heure_decollage = strdup(hour);
        new_plane->compagnie = comp;

        addTakeoff(QueueTakeoff, new_plane);
    }
}


void addTakeoff(QueueAvion *QueueTakeoff, Avion *avion) {
    pushQueueArray(QueueTakeoff, avion);
    displayQueueArray(QueueTakeoff);

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
    avion1->heure_decollage = strdup("0010");
    avion1->compagnie = comp;

    //QueueAvion *q_takeoff = (QueueAvion *) malloc(sizeof(Queue));

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

        // User action every 5 minutes
        if (t % 5 == 0) {
            fflush(stdin);
            setbuf(stdin, NULL);
            char code[20];
            // Safe input
            printf("> ");
            safeInput(code, 20);
            char *p;
            if ((p = strchr(code, '\n')) != NULL)
                *p = '\0';
            if ((p = strchr(code, '\r')) != NULL)
                *p = '\0';
            printf("CODE BUGG: %s\n ", code);
            if (strlen(code) == 19)
                readCode(code, QueueTakeoff, comp);
            //printf(" [DEBUG] Input: %s", code);


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
    }

    printf("[%04d] Exiting...\n", t);
    return 0;
}
