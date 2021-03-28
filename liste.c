#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"
#include "include/liste.h"

Liste initListe(){
    Liste liste = malloc(sizeof(int));
    liste->suivant = NULL;
    return liste;
}

Liste inserTete(Liste liste, int nbBytes, void* adresse){
	Liste listeTmp = initListe();
	listeTmp->blocMemoire.nbBytes = nbBytes;
	listeTmp->blocMemoire.adresse = adresse;
    listeTmp->suivant = liste;
	return listeTmp;
}

Liste suppTete(Liste liste) {
    if(liste != NULL){
        Liste listeTmp = liste ;
        liste = liste->suivant ;
        free(listeTmp) ;
        listeTmp = NULL ;
    }
    return liste ;
}

Liste suppListe(Liste liste, Liste listeAsupp){
    Liste listeTemp = liste;
    if(liste == listeAsupp){
        liste = suppTete(listeAsupp);
    }
    else{
        Liste precedentListe = NULL;
        while(listeTemp != NULL && listeTemp != listeAsupp){
            precedentListe = listeTemp;
            listeTemp = listeTemp->suivant;
        }
        listeTemp = suppTete(listeTemp);
        if(precedentListe != NULL)
            precedentListe->suivant = listeTemp;
    }
    return liste;
}

Liste rechercheElement(Liste liste, int nbBytes) {
    while(liste != NULL) {
        if(liste->blocMemoire.nbBytes >= nbBytes)
            break;
        liste = liste->suivant;
    }
	return liste;
}

Liste rechercheBlocMemoire(Liste liste, void* p){
	while(liste !=NULL && liste->blocMemoire.adresse != p){
		liste = liste->suivant;
	}
	return liste;
}