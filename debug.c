#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"
#include "include/liste.h"


int main(){

	Liste l = initListe();
    l->blocMemoire.adresse = NULL;
    l->blocMemoire.nbBytes = 5;

    
    l = inserTete(l,10,NULL);
    l = inserTete(l,20,NULL);
    l = inserTete(l,30,NULL);

Liste z = l;
    while (z != NULL)
    {
        printf("%d\n",z->blocMemoire.nbBytes);
        z = z->suivant;
    }
    printf("Apres : \n\n");
    suppListe(l->suivant,l);
    z=l;
    while (z != NULL)
    {
        printf("%d\n",z->blocMemoire.nbBytes);
        z = z->suivant;
    }
    printf("Fin\n");
	return 0;
 }