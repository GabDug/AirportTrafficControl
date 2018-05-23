#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

typedef struct avion Avion ;
typedef struct compagnie Compagnie ;
typedef struct cellule_compagnie Cellule_compagnie ;
typedef Cellule_compagnie *Liste_compagnie ;
typedef struct cellule_avion Cellule_avion ;
typedef Cellule_avion *Liste_avions ;


struct avion{
    char identifiant[7];
    int carburant;
    int consommation;
    char heure_decollage[4];
    Compagnie* compagnie;
};


struct compagnie{
    char* nom;
    char acronyme[3];
    Liste_avions avions_compagnie;
};


struct cellule_avion{
    Avion avion;
    struct cellule_avion* suivant_compagnie; /* pointeur sur l'avion suivant dans la liste des
avions de la compagnie */
    struct cellule_avion* precedent_compagnie;/* pointeur sur l'avion precedent dans la liste des
avions de la compagnie */
    struct cellule_avion* suivant_attente; /* avion suivant dans la liste de decollage ou
d'atterrissage */
}Cellule_avion;


typedef struct queue{
    Liste_avions premier;/*pointe sur le premier*/
    Liste_avions dernier;/*pointe sur le dernier*/
}Queue;