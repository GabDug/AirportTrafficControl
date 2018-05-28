#include "main.h"

void add_plane_landing(ListeLanding *l, Cellule_Avion *nelt);

void display_landing(ListeLanding *l, char *);

void update_fuel_landing(ListeLanding *l, char *);

int is_empty_landing(ListeLanding *l);

void add_plane_landing(ListeLanding *l, Cellule_Avion *nelt) {
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
    save = cur->suivant_attente;
    cur->suivant_attente = nelt;
    nelt->suivant_attente = save;
}

void pop_plane_landing(ListeLanding *l, Cellule_Avion *save) {
    if (!is_empty_landing(l)) {
        *save = *l->first;
        l->first = l->first->suivant_attente;
    }
}

void display_landing(ListeLanding *l, char *f_t) {
    if (!is_empty_landing(l)) {
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
    } else {
        if (f_t != NULL)
            printf("[%s] No planes waiting for landing!\n", f_t);
        else
            printf("No planes waiting for landing!\n");
        return;
    }
}

void update_fuel_landing(ListeLanding *l, char *f_t) {
    if (!is_empty_landing(l)) {
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

int is_empty_landing(ListeLanding *l) {
    if (l->first == NULL)
        return TRUE;
    else
        return FALSE;
}



// void crashLanding(ListeLanding *l, )

// void sortLanding()




