
#ifndef AIRPORT_STRUCT_H
#define AIRPORT_STRUCT_H


typedef struct cellule_avion {
    int avion;
    struct cellule_avion *suivant_compagnie;
    struct cellule_avion *precedent_compagnie;
    struct cellule_avion *suivant_attente;
} Cellule_Avion;

typedef struct dll {
    Cellule_Avion *first;
    Cellule_Avion *last;
} Liste_avion;

/* UNUSED ATM
typedef struct ll {
    Cellule_Avion *first;
} Liste_companie;*/

typedef struct avion Avion ;
typedef struct compagnie Compagnie ;
typedef struct cellule_compagnie Cellule_compagnie ;


struct avion{
    char* identifiant;
    int carburant;
    int consommation;
    char* heure_decollage;
    Compagnie* compagnie;
   // int compagnie;
};


struct compagnie{
    char* nom;
    char* acronyme;
    Liste_avion avions_compagnie;
};

typedef struct cellule_compagnie{
    Compagnie *comp;
    struct cellule_compagnie* suivant;
} Cellule_compagnie;

/*
typedef struct queue{
    Liste_avion premier;
    Liste_avion dernier;
}Queue;*/

typedef struct dll_op {
    Cellule_Avion *first;
    Cellule_Avion *last;
} Queue;

#endif //AIRPORT_STRUCT_H
