/*!
 * \file utilitaire.c
 * \brief Fichier d'implémentation des fonctions d'allocation et de désallocation de la mémoire.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 * \struct utilitaire.h
 * 
 * Ce fichier contient toutes les fonctions utiles à la manipulation de la mémoire.
 */

#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"
#include "include/liste.h"
#include "include/espaceMemoire.h"
#include "include/utilitaire.h"

/*!
 * \brief Fonction permettant l'initialisation de la mémoire de la zone de travail.
 *        Elle permet d'allouer de la mémoire à l'aide du nombre de bytes passé en paramètre.
 * 		  Elle permet également de mettre à nul le nombre de bytes alloue, la mémoire allouée et la mémoire libre.
 * 		  Enfin, si l'adresse n'est pas égale à nul, elle effectue une insertion en tête en A REVOIR.
 * \param [in,out] nbBytes Nombre de byte du bloc mémoire. Type int.  
 * \return Un nombre de byte alloué.
 */
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

/*!
 * \brief Fonction permettant la récupération de la mémoire de la zone initialement réservée.
 * \return Le nombre de byte récupéré.
 */
int freeMemory(){  
    int nbBytesRecupere = 0;
    Liste liste;
	// Elle permet, tant que la mémoire allouée n'est pas égale à nulle, de libérer toutes
	// les adresses qu'elles a utilisées et la liste en elles-mêmes.
    while(memoireAllouee != NULL){
        liste = memoireAllouee;
        memoireAllouee = memoireAllouee->suivant;
        myfree(liste->blocMemoire.adresse);
        free(liste);
        liste = NULL;
    }
	// Elle permet, tant que la mémoire libre n'est pas égale à nulle, de récupérer tout 
	// les bytes utilisés dans le bloc mémoire et de libérer la liste.
    while(memoireLibre != NULL){
        liste = memoireLibre;
        memoireLibre = memoireLibre->suivant;
        nbBytesRecupere += liste->blocMemoire.nbBytes;
        free(liste);
        liste = NULL;
    }
	// Elle permet, si le nombre de byte récupéré est égal à 0, de le placer à -1 en cas d'erreur.
	// Par exemple, si la mémoire a déja été libérée.
    if(nbBytesRecupere == 0)
        nbBytesRecupere = -1;
    return nbBytesRecupere;
}

/*!
 * \brief Fonction permettant l'allocation dynamique d'espace dans la mémoire libre.
 * \param [in] nbBytes Nombre de byte du bloc mémoire. Type int.  
 * \return L'adresse allouée.
 */
void* myalloc(int nbBytes){
	void* addresseAllouee = NULL;
	Liste liste = NULL;
	// Si le nombre de bytes est supérieur à 0, elle effectue une recherche d'élément dans la mémoire libre.
    if(nbBytes > 0)
        liste = rechercheElement(memoireLibre,nbBytes);
	// Si la liste n'est pas égal à nulle et si le nombre de bytes d'un bloc mémoire de la mémoire libre
	// est égale au nombre de bytes passé en paramètre, l'adresse de ce bloc mémoire devient l'adresse allouée.
	// La mémoire libre est ensuite attribué à la mémoire allouée.
	if(liste != NULL){
		if(liste->blocMemoire.nbBytes == nbBytes){
			addresseAllouee = liste->blocMemoire.adresse;
			printf("Avant insert : \n");
			Liste z = memoireLibre;
			printf("Memoire libre { ");
			// Tant quand la mémoire allouée n'est pas égale à nulle, 
			// on écrit le nombre de byte de chaque bloc mémoire de la mémoire allouée.
			while(z != NULL){
				printf("%d",z->blocMemoire.nbBytes);
				z = z->suivant;
			}
			printf(" }\n\n");

			memoireAllouee = inserTete(memoireAllouee,nbBytes, liste->blocMemoire.adresse);

			printf("Avant suppr : \n");
			z = memoireLibre;
			printf("Memoire libre { ");
			while(z != NULL){
				printf("%d",z->blocMemoire.nbBytes);
				z = z->suivant;
			}
			printf(" }\n\n");

			memoireLibre = suppListe(memoireLibre, liste);

			printf("Apres suppr : \n");
			z = memoireLibre;
			printf("Memoire libre { ");
			while(z != NULL){
				printf("%d",z->blocMemoire.nbBytes);
				z = z->suivant;
			}
			printf(" }\n\n");
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
			memoireLibre = suppListe(memoireLibre, liste);
		}        	
    }
    return addresseAllouee;
}

/*!
 * \brief Fonction permettant la désallocation dynamique d'espace dans une zone adressée par un pointeur.
 * \param [in] p pointeur vers l'adresse mémoire recherchée. Type void*.
 * \return Un nombre de byte.
 */
 int myfree(void* p){
    int nbBytes = -1;
	// On recherche un bloc mémoire dans la mémoire allouée avec le pointeur passé en paramètre.
	Liste liste = rechercheBlocMemoire(memoireAllouee, p);
	// Si le pointeur vers l'adresse mémoire recherchée et le bloc mémoire trouvé ne sont pas égal à nul,
	// on effectue une insertion en tête de la mémoire libre du bloc mémoire trouvé précédemment.
	// On supprime ensuite ce bloc mémoire de la mémoire allouée.
	if(p != NULL && liste != NULL ){
		nbBytes = liste->blocMemoire.nbBytes;
		memoireLibre = inserTete(memoireLibre,nbBytes,liste->blocMemoire.adresse);
		memoireAllouee = suppListe(memoireAllouee,liste);
		//memoireLibre = defragmentation(memoireLibre); A TESTER
	}
    return nbBytes;
 }

/*!
 * \brief Fonction permettant l'affichage des messages concernant l'initialisation de la mémoire.
 * \param [in] nbBytesAlloue Nombre de byte alloué du bloc mémoire. Type int. 
 * \param [in] nbBytes Nombre de byte du bloc mémoire. Type int.   
 */
 void initMemoryMessage(int nbBytesAlloue,int nbBytes){
	 if(nbBytesAlloue == 0)     
	 	printf("Initialisation de la zone de travail echouee (%d bytes)\n",nbBytes);
    else    
		printf("Initialisation de la zone de travail reussie (%d bytes)\n",nbBytes);
}

/*!
 * \brief Fonction permettant l'affichage des messages concernant la récuperation de la mémoire.
 * \param [in] nbBytesRecupere Nombre de byte récupéré du bloc mémoire. Type int. 
 */
void freeMemoryMessage(int nbBytesRecupere){
	if(nbBytesRecupere == -1)
		printf("Recuperation de la zone memoire initialisee pour le programme echouee\n");
	else
		printf("Recuperation de la zone memoire initialisee pour le programme reussie %d bytes recupere\n",nbBytesRecupere);
}

/*!
 * \brief Fonction permettant l'affichage des messages concernant l'allocation de mémoire.
 * \param [in] p pointeur vers l'adresse mémoire recherchée. Type void*.
 * \param [in] nbBytes Nombre de byte du bloc mémoire. Type int. 
 */
void myallocMessage(void* p,int nbBytes){
	if(p != NULL){
		printf("Allocation de memoire dans la zone de travail reussi (%d bytes)\n",nbBytes);
		printf("L'adresse allouee est %p\n",p);
	}
	else
		printf("Allocation de memoire dans la zone de travail echouee (%d bytes)\n",nbBytes);
}

/*!
 * \brief Fonction permettant l'affichage des messages concernant la récupération de mémoire.
 * \param [in] nbBytesRecupere Nombre de byte récupéré du bloc mémoire. Type int. 
 */
void myfreeMessage(int nbBytesRecupere){
	if(nbBytesRecupere == -1)
		printf("Desallocation de memoire dans la zone de travail echouee\n");
	else
		printf("Desallocation de memoire dans la zone de travail reussi %d bytes recupere\n",nbBytesRecupere);
}

Liste defragmentation(Liste liste){
	Liste listeTemp = liste;
	int defragmente = 0;
	while(listeTemp != NULL && defragmente == 0){
		Liste listeCourante = listeTemp;
		while (listeCourante != NULL){
			if(listeTemp->blocMemoire.adresse+listeTemp->blocMemoire.nbBytes == listeCourante->blocMemoire.adresse){
				int nbBytes = listeTemp->blocMemoire.nbBytes + listeCourante->blocMemoire.nbBytes;
				liste = inserTete(liste,nbBytes,listeTemp->blocMemoire.adresse);
				defragmente = 1;
				break;
			}
			listeCourante = listeCourante->suivant;
		}
		listeTemp = listeTemp->suivant;		
	}
	if(defragmente)
		liste = defragmentation(liste);
	return liste;
}

