#include <stdio.h>
#include <stdlib.h>
#include <include/liste.h>
#include <include/espaceMemoire.h>

/* initialisation de la zone de travail*/
int initMemory(int nbBytes){
	void* adresse = malloc(nbBytes);
	int nbBytesAlloue = 0;
	memoireAllouee = NULL;
	memoireLibre = NULL;
	if(adresse != NULL){
		memoireLibre = inserTete(memoireLibre,nbBytes,adresse);
		nbBytesAlloue = nbBytes;
	}
	return nbBytesAlloue;
}

/* recuperation  de la zone initialement réservée*/
int freeMemory(){  
    int nbBytesRecupere = 0;
    Liste liste;
    while(memoireAllouee != NULL){
        liste = memoireAllouee;
        memoireAllouee = memoireAllouee->suivant;
        myfree(liste->blocMemoire.adresse);
        free(liste);
        liste = NULL;
    }
    while(memoireLibre != NULL){
        liste = memoireLibre;
        memoireLibre = memoireLibre->suivant;
        nbBytesRecupere += liste->blocMemoire.nbBytes;
        free(liste);
        liste = NULL;
    }
    if(nbBytesRecupere == 0)
        nbBytesRecupere = -1;
    return nbBytesRecupere;
}

/*allocation dynamique d'espace dans la zone*/
void* myalloc(int nbBytes){
	void* addresseAllouee = NULL;
	Liste liste = NULL;
    if(nbBytes > 0)
        rechercheElement(memoireLibre,nbBytes);
	if(liste != NULL){
		if(liste->blocMemoire.nbBytes == nbBytes){
			addresseAllouee = liste->blocMemoire.adresse;
			memoireAllouee = inserTete(memoireAllouee,nbBytes, liste->blocMemoire.adresse);
			suppElt(memoireLibre, liste);
		}
		else{
			//la liste1 correspond au nbre de bytes
			memoireAllouee = inserTete(memoireAllouee,nbBytes, liste->blocMemoire.adresse);
			addresseAllouee = liste->blocMemoire.adresse;
			
			//la liste2 correspond a l'element precdent -nbBytes
			int nbBytesRestant = liste->blocMemoire.nbBytes - nbBytes;
			if(nbBytesRestant > 0){
				void* adresse = liste->blocMemoire.adresse + nbBytes - 1;
				memoireLibre = inserTete(memoireLibre,nbBytesRestant,adresse);
			}
			memoireLibre = suppElt(memoireLibre, liste);
		}        	
    }
    return addresseAllouee;
}

 /*désallocation d'une zone adressée par un pointeur */
 int myfree(void *p){
    int nbBytes = -1;
	Liste liste = trouveElt(memoireAllouee, p);
	if(p != NULL && liste != NULL ){
		nbBytes = liste->blocMemoire.nbBytes;
		memoireLibre = inserTete(memoireLibre,nbBytes,liste->blocMemoire.adresse);
		suppElt(memoireAllouee,liste);
	}
    return nbBytes;
 }