#include "main.h"

void add_plane_to_company(Compagnie *comp, Cellule_Avion *c_plane);

void display_planes_company(Compagnie *comp);

void display_planes_company(Compagnie *comp) {
    Cellule_Avion *el;
    el = comp->avions_compagnie->first;
    if (el == NULL) {
        printf("Can't print empty queue!\n");
        return;
    }
    printf("List of Planes for %s (%s)\n", comp->nom, comp->acronyme);
    while (el != NULL) {
        printf("  %s\n", el->avion->identifiant);
        el = el->suivant_compagnie;
    }
}

void add_plane_to_company(Compagnie *comp, Cellule_Avion *c_plane) {
    if (comp->avions_compagnie->first == NULL && comp->avions_compagnie->last == NULL) {
        comp->avions_compagnie->first = c_plane;
        comp->avions_compagnie->last = c_plane;
        return;
    }

    c_plane->suivant_compagnie = NULL;
    if (comp->avions_compagnie->first == NULL)
        comp->avions_compagnie->first = c_plane;
    if (comp->avions_compagnie->last != NULL) {
        comp->avions_compagnie->last->suivant_compagnie = c_plane;
    }
    comp->avions_compagnie->last = c_plane;
    // display_planes_company(comp);
}
