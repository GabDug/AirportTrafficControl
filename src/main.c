#include "main.h"
#include "const.h"

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

void addTakeoff(QueueAvion *QueueTakeoff, Cellule_Avion *avion);

void getHourMinuteTime(int t, char *output) {
    // Output a time in the HHMM format from t in minutes.

    int minutes = t % 60;
    int hours = t / 60;
    //printf("%02d%02d ", hours, minutes);
    snprintf(output, sizeof(output), "%02d%02d", hours, minutes);
    output[4]= '\0';
}

int getMinuteTime(char *time) {
    // Return a time in minutes, from HHMM
    return (time[3] - '0') + 10 * (time[2] - '0') + 60 * (time[1] - '0') + 600 * (time[0] - '0');
}

void readCode(char *code, QueueAvion *QueueTakeoff, Compagnie *comp, int t) {
    // Example of code:
    // char code[] = "DLA043-D-1143------";

    if (code[7] == 'D') {
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
        if (getMinuteTime(hour) < t+DELAY)
        {
            printf("[%04d] => Can't add a plane to takeoff in less than five minutes!\n", t);
            return;
        }
        printf("[%04d] Added to Takeoff: %s @ %s\n ", t, id, hour);

        Avion *new_plane = (Avion *) malloc(sizeof(Avion));
        new_plane->identifiant = strdup(id);
        new_plane->carburant = 1000;
        new_plane->consommation = 0; // ATM
        new_plane->heure_decollage = strdup(hour);
        new_plane->compagnie = comp;

        Cellule_Avion *c_avion = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
        c_avion->avion = new_plane;
        c_avion->precedent_compagnie = NULL;
        c_avion->suivant_compagnie = NULL;
        c_avion->suivant_attente = NULL;

        addPlaneCompany(comp, c_avion);
        //addTakeoff(QueueTakeoff, c_avion);
    }
}


void addTakeoff(QueueAvion *QueueTakeoff, Cellule_Avion *avion) {
    pushQueueArray(QueueTakeoff, avion);
}

void displayTakeoff(QueueAvion *QueueTakeoff) {
    displayTakeoffQueueArray(QueueTakeoff);
}



int main() {
    printf("AIRPORT CONTROL SIMULATOR - WIP\n");

    // Loading
    // Creating the company
    Compagnie *comp = (Compagnie *) malloc(sizeof(Compagnie));
    comp->nom = strdup("AyBiCe");
    comp->acronyme = strdup("ABC");
    Liste_avion *liste_avions_comp = (Liste_avion *) malloc(sizeof(Liste_avion));
    comp->avions_compagnie = liste_avions_comp;
    comp->avions_compagnie->first = NULL;
    comp->avions_compagnie->last = NULL;



    Cellule_compagnie *liste_compagnie = (Cellule_compagnie *) malloc(sizeof(Cellule_compagnie));
    // liste_compagnie is actually our first company cell
    liste_compagnie->comp = comp;
    liste_compagnie->suivant = NULL; // No other company yet



    Avion *avion1 = (Avion *) malloc(sizeof(Avion));
    avion1->identifiant = strdup("ABC001");
    avion1->carburant = 1000;
    avion1->consommation = 0; // ATM
    avion1->heure_decollage = strdup("0010");
    avion1->compagnie = comp;

    Cellule_Avion *c_avion1 = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
    c_avion1->avion = avion1;
    c_avion1->precedent_compagnie = NULL;
    c_avion1->suivant_compagnie = NULL;
    c_avion1->suivant_attente = NULL;

    addPlaneCompany(comp, c_avion1);

    //QueueAvion *q_takeoff = (QueueAvion *) malloc(sizeof(Queue));


    // Initializing TakeOff Queue
    QueueAvion *QueueTakeoff = (QueueAvion *) malloc(sizeof(QueueAvion));
    initQueueArray(QueueTakeoff, 20);
    // Adding a plane to TakeOff Queue
    pushQueueArray(QueueTakeoff, c_avion1);



    Avion *avion2 = (Avion *) malloc(sizeof(Avion));
    avion2->identifiant = strdup("ABC004");
    avion2->carburant = 2000;
    avion2->consommation = 20; // ATM
    avion2->heure_decollage = NULL;
    avion2->compagnie = comp;

    Cellule_Avion *c_avion2 = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
    c_avion2->avion = avion2;
    c_avion2->precedent_compagnie = NULL;
    c_avion2->suivant_compagnie = NULL;
    c_avion2->suivant_attente = NULL;


    // Initializing Landing Queue
    ListeLanding *ListLanding = (ListeLanding *) malloc(sizeof(ListeLanding));
    ListLanding->first=NULL;
    addPlaneLanding(ListLanding, c_avion2);

    displayCompanyPlanes(comp);
    displayTakeoffQueueArray(QueueTakeoff);
    displayLanding(ListLanding);


    char formatted_time[] = "0000";

    int t; // time, 0 to 1439 (23:59)
    for (t = 0; t < 1439; t++) {
        getHourMinuteTime(t, formatted_time);
        // printf("[DEBUG] %d / %s\n", t, formatted_time);

        Cellule_Avion *c_avion_tmp = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
        if (!isEmpty(QueueTakeoff)) {
            getQueueArray(QueueTakeoff, c_avion_tmp);
            int next_takeoff_t = -1;
            next_takeoff_t = getMinuteTime(c_avion_tmp->avion->heure_decollage);
            //      printf("[DEBUG] Next takeoff: %d / %s\n", next_takeoff_t, c_avion_tmp->heure_decollage);
            if (t >= next_takeoff_t) {
                if (delQueueArray(QueueTakeoff)) {
                    printf("[%04d] Takeoff %s\n", t, c_avion_tmp->avion->identifiant);
                }
                if (!isEmpty(QueueTakeoff)) {
                    displayTakeoff(QueueTakeoff);
                } else
                    printf("[%04d] No planes in Takeoff Queue\n", t);
            } else {
                //printf("[%04d] No Takeoff, next takeoff: %s\n", t, c_avion_tmp->heure_decollage);
            }
        }

        // User action every 5 minutes
        if (t % 5 == 0) {
            fflush(stdin);
            setbuf(stdin, NULL);
            char code[20];

            // Safe input
            printf("[%s] > ", formatted_time);
            safeInput(code, 20);
            char *p;
            if ((p = strchr(code, '\n')) != NULL)
                *p = '\0';
            if ((p = strchr(code, '\r')) != NULL)
                *p = '\0';

            if (strlen(code) == 19) // CHECK THE TYPE
                readCode(code, QueueTakeoff, comp, t);
            // printf(" [DEBUG] Input: %s", code);


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
