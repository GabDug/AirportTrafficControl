#include <inttypes.h>
#include "main.h"
#include "const.h"


int read_code(char *code, QueueAvion *takeoff_queue, ListeLanding *landing_list, Compagnie *comp, int t) {
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
        if (get_minute_time(hour) < t + DELAY) {
            printf("[%04d] => Can't add a plane to takeoff in less than five minutes!\n", t);
            return FALSE;
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

        add_plane_to_company(comp, c_avion);
        add_plane_takeoff_queue(takeoff_queue, c_avion);
        return TRUE;
    }
    if (code[7] == 'A') {
        char id[6];
        for (int i = 0; i < 6; i++) {
            id[i] = code[i];
        }
        id[6] = '\0';

        char fuel[2];
        for (int i = 0; i < 2; i++) {
            fuel[i] = code[i + 14];
        }
        fuel[2] = '\0';

        /*char consumption[2];
        for (int i = 0; i < 2; i++) {
            consumption[2] = code[i + 17];
        }
        consumption[2] = '\0';
*/

        Avion *new_plane = (Avion *) malloc(sizeof(Avion));
        new_plane->identifiant = strdup(id);
        new_plane->carburant = (int) atoi(fuel);
        new_plane->consommation = (int) 1;
        new_plane->heure_decollage = NULL;
        new_plane->compagnie = comp;
        printf("[%04d] Added to landing: %s (Fuel time left: %d)\n", t, id, new_plane->carburant);

        Cellule_Avion *c_avion = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
        c_avion->avion = new_plane;
        c_avion->precedent_compagnie = NULL;
        c_avion->suivant_compagnie = NULL;
        c_avion->suivant_attente = NULL;

        add_plane_to_company(comp, c_avion);
        add_plane_landing(landing_list, c_avion);
        display_landing(landing_list, NULL);
        return TRUE;
    }
}


int main() {
    printf("AIRPORT CONTROL SIMULATOR - WIP\n\n");

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

    add_plane_to_company(comp, c_avion1);


    // Initializing TakeOff Queue
    QueueAvion *takeoff_queue = (QueueAvion *) malloc(sizeof(QueueAvion));
    init_takeoff_queue(takeoff_queue, 20);
    // Adding a plane to TakeOff Queue
    add_plane_takeoff_queue(takeoff_queue, c_avion1);


    Avion *avion2 = (Avion *) malloc(sizeof(Avion));
    avion2->identifiant = strdup("ABC004");
    avion2->carburant = 99;
    avion2->consommation = 20; // ATM
    avion2->heure_decollage = NULL;
    avion2->compagnie = comp;

    Cellule_Avion *c_avion2 = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
    c_avion2->avion = avion2;
    c_avion2->precedent_compagnie = NULL;
    c_avion2->suivant_compagnie = NULL;
    c_avion2->suivant_attente = NULL;


    // Initializing Landing Queue
    ListeLanding *landing_list = (ListeLanding *) malloc(sizeof(ListeLanding));
    landing_list->first = NULL;
    add_plane_landing(landing_list, c_avion2);
    add_plane_to_company(comp, c_avion2);


    printf("[0000] Initial planes:\n");
    display_planes_company(comp);
    display_takeoff_queue(takeoff_queue, NULL);
    display_landing(landing_list, NULL);
    printf("\n[0000] Commands:\n"
           "         'takeoff' too see next takeoffs\n"
           "         'landing' too see next landings\n"
           "         'exit' to exit the program\n"
           "         Formatted codes to add planes\n"
           "         Enter to skip\n");
    printf("[0000] Beginning the simulation:\n");



    char f_t[] = "0000";

    int t; // t, 0 to 1439 (23:59)
    for (t = 0; t < 1439; t++) {
        get_hour_minute_time(t, f_t);

        // Landing
        if (!is_empty_landing(landing_list)) {
            Cellule_Avion *c_avion_tmp = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
            pop_plane_landing(landing_list, c_avion_tmp);

            printf("[%s] Landing %s\n", f_t, c_avion_tmp->avion->identifiant);
            Log(f_t, c_avion_tmp->avion->identifiant, 'a', c_avion_tmp->avion->carburant,
                c_avion_tmp->avion->consommation);

            if (!is_empty_landing(landing_list)) {
                display_landing(landing_list, f_t);
            } else
                printf("[%04d] No more planes waiting for landing.\n", t);

            free(c_avion_tmp);
        }


        // Takeoff
        if (!is_empty_takeoff_queue(takeoff_queue)) {
            Cellule_Avion *c_avion_tmp = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
            get_plane_takeoff_queue(takeoff_queue, c_avion_tmp);
            int next_takeoff_t = -1;
            next_takeoff_t = get_minute_time(c_avion_tmp->avion->heure_decollage);
            //      printf("[DEBUG] Next takeoff: %d / %s\n", next_takeoff_t, c_avion_tmp->heure_decollage);
            if (t >= next_takeoff_t) {
                if (del_plane_takeoff_queue(takeoff_queue)) {
                    printf("[%04d] Takeoff %s\n", t, c_avion_tmp->avion->identifiant);
                    Log(f_t, c_avion_tmp->avion->identifiant, 'd', c_avion_tmp->avion->carburant,
                        c_avion_tmp->avion->consommation);

                    free(c_avion_tmp);
                }
                if (!is_empty_takeoff_queue(takeoff_queue)) {
                    display_takeoff_queue(takeoff_queue, f_t);
                } else
                    printf("[%04d] No more planes waiting for takeoff.\n", t);
            } else {
                //printf("[%04d] No Takeoff, next takeoff: %s\n", t, c_avion_tmp->heure_decollage);
            }

        }

        // User action every 5 minutes
        if (t % 5 == 0) {
            while (TRUE) {
                fflush(stdin);
                setbuf(stdin, NULL);
                char code[20];

                // Safe input
                printf("[%s] > ", f_t);

                safe_input(code, 20);
                char *p;
                if ((p = strchr(code, '\n')) != NULL)
                    *p = '\0';
                if ((p = strchr(code, '\r')) != NULL)
                    *p = '\0';

                if (strlen(code) == 19) {
                    if (code[6] == '-' && code[8] == '-' && code[13] == '-' && code[16] == '-') {
                        if (read_code(code, takeoff_queue, landing_list, comp, t)) {
                            break;
                        }
                    }
                } else {
                    if (strcmp("takeoff", code) == 0) {
                        display_takeoff_queue(takeoff_queue, f_t);
                        break;
                    }
                    if (strcmp("landing", code) == 0) {
                        display_landing(landing_list, f_t);
                        break;
                    }
                    if (strcmp("exit", code) == 0) {
                        exit(1);
                    }
                    if (strcmp("companies", code) == 0) {
                        // Not implemented
                        printf("NOT IMPLEMENTED YET");
                        break;
                    }
                    if (strcmp("", code) == 0) {
                        // Pass
                        break;
                    }
                }
                printf("Invalid input!\n");
            }
        }
        update_fuel_landing(landing_list, f_t);
    }

    printf("[%04d] Exiting...\n", t);
    return 0;
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
