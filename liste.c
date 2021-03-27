#include <stdio.h>
#include <stdlib.h>
#include <include/liste.h>

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
    Liste listeTmp = liste ;
    liste = liste -> suivant ;
    free(listeTmp) ;
    listeTmp = NULL ;
    return liste ;
}

void suppListe(Liste liste, Liste listeAsupp){
	while(liste != NULL && liste != listeAsupp)
        liste = liste->suivant;

	if(liste != NULL)
        liste = suppTete(liste);
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