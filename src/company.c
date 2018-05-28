#include "main.h"

void addPlaneCompany(Compagnie *comp, Cellule_Avion *cplane);

void displayCompanyPlanes(Compagnie *comp);

void displayCompanyPlanes(Compagnie *comp) {
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

void addPlaneCompany(Compagnie *comp, Cellule_Avion *cplane) {
    if (comp->avions_compagnie->first == NULL && comp->avions_compagnie->last == NULL) {
        printf("  [DEBUG] First plane added\n");
        comp->avions_compagnie->first = cplane;
        comp->avions_compagnie->last = cplane;
        return;
    }

    cplane->suivant_compagnie = NULL;
    if (comp->avions_compagnie->first == NULL)
        comp->avions_compagnie->first = cplane;
    if (comp->avions_compagnie->last != NULL) {
        //    printf("%s\n", comp->avions_compagnie->last->avion->identifiant);
        comp->avions_compagnie->last->suivant_compagnie = cplane;
    }
    comp->avions_compagnie->last = cplane;
    displayCompanyPlanes(comp);
}
