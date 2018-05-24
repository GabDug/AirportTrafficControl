#include "struct.h"
#include <stdio.h>
#include <stdlib.h>



int insertTop(Liste_avion *l, Cellule_Avion *suivant_compagnie);

void displayAscending(Liste_avion *mylist);
/*
int main() {
    Liste_avion *mylist;
    mylist = (Liste_avion *) malloc(sizeof(Liste_avion));
    mylist->first = NULL;
    mylist->last = NULL;

    //mylist->first->avion = 1;
    Cellule_Avion *e1 = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
    e1->avion = 0;
    e1->suivant_compagnie = NULL;
    e1->precedent_compagnie = NULL;
    insertTop(mylist, e1);

    Cellule_Avion *e2 = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
    e2->avion = 1;
    e2->suivant_compagnie = NULL;
    e2->precedent_compagnie = NULL;
    insertTop(mylist, e2);

    Cellule_Avion *e3 = (Cellule_Avion *) malloc(sizeof(Cellule_Avion));
    e3->avion = 2;
    e3->suivant_compagnie = NULL;
    e3->precedent_compagnie = NULL;
    insertTop(mylist, e3);

    printf("List:\n");
    displayAscending(mylist);

    printf("Reversed List:\n");
    reverse(mylist);
    displayAscending(mylist);

    free(e1);
    free(e2);
    free(e3);
    free(mylist);
    return 0;
}*/


void displayNext(Cellule_Avion *el) {
    while (el != NULL) {
        printf("%d\n", el->avion);
        el = el->suivant_compagnie;
    }
}

void displayPrev(Cellule_Avion *el) {
    while (el != NULL) {
        printf("%d\n", el->avion);
        el = el->precedent_compagnie;
    }
}

/*
int insertTop(Liste_avion *list, int avion) {
    Cellule_Avion *new = (Cellule_Avion *) malloc(sizeof(Cellule_Avion)); // Create a new element (node)
    Cellule_Avion *save = list->first;

    list->first = new; // set first element of list as the new one
    new->avion = avion;

    new->precedent_compagnie = NULL;
    new->suivant_compagnie = save;

}*/

// Correction

int insertTop(Liste_avion *l, Cellule_Avion *suivant_compagnie) {
    Cellule_Avion *f = l->first;

    suivant_compagnie->suivant_compagnie = f;
    suivant_compagnie->precedent_compagnie = NULL;

    l->first = suivant_compagnie; // set first element of list as the new one

    if (f != NULL)
        f->precedent_compagnie = suivant_compagnie;
    else
        l->last = suivant_compagnie;
}

/* UNUSED ATM
int simple_insertTop(Liste_avion *l, Cellule_Avion *suivant_compagnie) {
    Cellule_Avion *f = l->first;

    suivant_compagnie->suivant_compagnie = f;
    suivant_compagnie->precedent_compagnie = NULL;

    l->first = suivant_compagnie; // set first element of list as the new one

    if (f != NULL)
        f->precedent_compagnie = suivant_compagnie;
    else
        l->last = suivant_compagnie;
}*/

void displayAscending(Liste_avion *mylist) {
    Cellule_Avion *el;
    el = mylist->first;
    while (el != NULL) {
        printf("%d\n", el->avion);
        el = el->suivant_compagnie;
    }
}


void addLast(Liste_avion *l, Cellule_Avion *nelt) {
    Cellule_Avion *last = l->last;
    nelt->precedent_compagnie = last;
    nelt->suivant_compagnie = NULL;
    l->last = nelt;
    if (last != NULL)
        last->suivant_compagnie = nelt;
    else
        l->first = nelt;
}

int addNth(Liste_avion *l, Cellule_Avion *nelt, int n) {
    Cellule_Avion *first = l->first;

    int i = 0;
    Cellule_Avion *cur = l->first;
    Cellule_Avion *save = NULL;

    // If add first
    if (n == 0) {
        return -1;
        //return DeleteFirst(l);
    }

    for (i = 0; i < n - 1; i++) {
        if (cur->suivant_compagnie == NULL) {
            // If we reach the end of the linked list before n elements
            return -1;
        }
        cur = cur->suivant_compagnie;
    }

    save = cur->suivant_compagnie; // Temp is N+1 element
    cur->suivant_compagnie = save->suivant_compagnie; // Cur is not in the list anymore
    return 0;
/*
    nelt->precedent_compagnie = last;
    nelt->suivant_compagnie = NULL;
    l->last = nelt;
    if (last != NULL)
        last->suivant_compagnie = nelt;
    else
        l->first = nelt;
*/}

// Correction
void insertPos(Liste_avion *l, Cellule_Avion *nelt, int x) {
    Cellule_Avion *cur = l->first;
    Cellule_Avion *save = NULL;
    int count = 1;
    if (x == 1) {//AddFirst
    } else {
        while (cur != NULL && count != x) {
            save = cur;
            cur = cur->suivant_compagnie;
            count++;
        }
        if (x == count) {
            save->suivant_compagnie = nelt;
            nelt->precedent_compagnie = save;
            nelt->suivant_compagnie = cur;
            if (cur == NULL)
                l->last = nelt;
            else
                cur->precedent_compagnie = nelt;
        }
    }
}

void reverse(Liste_avion *list) {
    Cellule_Avion *save = NULL;
    Cellule_Avion *cur = list->first;

    while (cur != NULL) {
        save = cur->precedent_compagnie;
        cur->precedent_compagnie = cur->suivant_compagnie;
        cur->suivant_compagnie = save;
        cur = cur->precedent_compagnie;
    }
    list->first = save->precedent_compagnie;
}     
