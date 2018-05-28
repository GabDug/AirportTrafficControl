

void addPlaneLanding(ListeLanding *l, Cellule_Avion *nelt);
void displayLanding(ListeLanding *l);

void addPlaneLanding(ListeLanding *l, Cellule_Avion *nelt) {
    Cellule_Avion *first = l->first;

    if (l->first == NULL)
    {
        l->first = nelt;
        nelt->suivant_attente=NULL;
        return;
    }

    int t_remaining = nelt->avion->carburant / nelt->avion->consommation;

    Cellule_Avion *cur = l->first;
    Cellule_Avion *save = NULL;

    while(cur->avion->carburant / nelt->avion->consommation < t_remaining) {
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

void displayLanding(ListeLanding *l) {
    Cellule_Avion *plane;
    plane = l->first;
    printf("Landing Queue:\n");
    while (plane != NULL) {
        printf("  %s (Fuel time left: %d)\n", plane->avion->identifiant, plane->avion->carburant / plane->avion->consommation);

        plane = plane->suivant_attente;
    }

}



