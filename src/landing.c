#include "main.h"

void addPlaneLanding(ListeLanding *l, Cellule_Avion *nelt);

void displayLanding(ListeLanding *l, char *);

void updateFuelLanding(ListeLanding *l, char *);

int isEmptyLanding(ListeLanding *l);

void addPlaneLanding(ListeLanding *l, Cellule_Avion *nelt) {
    Cellule_Avion *first = l->first;

    if (l->first == NULL) {
        l->first = nelt;
        nelt->suivant_attente = NULL;
        return;
    }

    int t_remaining = nelt->avion->carburant / nelt->avion->consommation;

    Cellule_Avion *cur = l->first;
    Cellule_Avion *save = NULL;

    while (cur->avion->carburant / nelt->avion->consommation < t_remaining) {
        if (cur->suivant_attente == NULL) {
            cur->suivant_attente = nelt;
            nelt->suivant_attente = NULL;
            return;
        }
        cur = cur->suivant_attente;
    }
    save = cur->suivant_attente; // Temp is N+1 element
    cur->suivant_attente = nelt;
    nelt->suivant_attente = save;
}

void popLanding(ListeLanding *l, Cellule_Avion *save) {
    if (!isEmptyLanding(l)) {
        *save = *l->first;
        l->first = l->first->suivant_attente;
    }
}

void displayLanding(ListeLanding *l, char *f_t) {
    Cellule_Avion *plane;
    plane = l->first;
    if (f_t != NULL)
        printf("[%s] Landing Queue:\n", f_t);
    else
        printf("Landing Queue:\n");
    while (plane != NULL) {
        printf("  %s (Fuel time left: %d)\n", plane->avion->identifiant,
               plane->avion->carburant / plane->avion->consommation);

        plane = plane->suivant_attente;
    }
}

void updateFuelLanding(ListeLanding *l, char *f_t) {
    if (!isEmptyLanding(l)) {
        Cellule_Avion *plane;
        plane = l->first;
        printf("[%s] Updating Fuel:\n", f_t);
        while (plane != NULL) {
            plane->avion->carburant = plane->avion->carburant - plane->avion->consommation;
            printf("  %s (Fuel left: %d)\n", plane->avion->identifiant,
                   plane->avion->carburant / plane->avion->consommation);

            plane = plane->suivant_attente;
        }
    }
}

int isEmptyLanding(ListeLanding *l) {
    if (l->first == NULL)
        return TRUE;
    else
        return FALSE;
}



// void crashLanding(ListeLanding *l, )

// void sortLanding()




