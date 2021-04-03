/*!
 * \file utilitaire.c
 * \brief Fichier contenant toutes les fonctions utiles à la manipulation de la mémoire.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 * \struct utilitaire.h
 * 
 * Ce fichier contient l'implémentation des fonctions d'initialisation, d'allocation, 
 * de désallocation et de libération de la mémoire. Elle contient également une 
 * une fonction permettant la défragmentation de l'espace mémoire.
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
 * 		  Elle initialise la liste de mémoire libre avec le nombre de bytes passé en paramètre et
 * 		  l'adresse de la mémoire initilisée. Elle initialise également la liste de mémoire allouée à NULL.
 * \param [in,out] nbBytes Nombre de byte à initialiser. Type int.  
 * \return Le nombre de byte alloué.
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
 * \return Le nombre de byte récupéré ou -1 en cas d'echec.
 */
int freeMemory(){  
    int nbBytesRecupere = 0;
	// Tant que la liste de mémoire allouée n'est pas vide, on libère toutes
	// les adresses allouées grâce à la fonction myfree().
    while(memoireAllouee != NULL){
		int result = myfree(memoireAllouee->blocMemoire.adresse);
		if(result == -1){
			return -1;
		}
    }
	// Tant que la liste de mémoire libre n'est pas vide, on effectue la somme des bytes 
	// qui seront récupérés. On supprime ensuite la liste.
    while(memoireLibre != NULL){
		nbBytesRecupere += memoireLibre->blocMemoire.nbBytes;
        memoireLibre = suppTete(memoireLibre);
    }
	// En cas d'erreur, le nombre de bytes récupéré est placé à -1.
    if(nbBytesRecupere == 0)
        nbBytesRecupere = -1;
    return nbBytesRecupere;
}

/*!
 * \brief Fonction permettant l'allocation dynamique d'espace dans la zone de travail.
 * \param [in] nbBytes Nombre de byte à alloué. Type int.  
 * \return L'adresse allouée ou NULL en cas d'erreur.
 */
void* myalloc(int nbBytes){
	void* addresseAllouee = NULL;
	Liste liste = NULL;
	// Si le nombre de bytes est supérieur à 0, on recherche dans la mémoire libre 
	// un bloc mémoire avec le nombre de bytes passé en paramètre.
    if(nbBytes > 0)
        liste = rechercheElement(memoireLibre,nbBytes);
	if(liste != NULL){
		// Si le nombre de bytes d'un bloc mémoire de la mémoire libre est égale au nombre de bytes 
		// passé en paramètre, l'adresse allouée devient l'adresse contenue dans le bloc mémoire.
		// On supprime ensuite ce bloc de la mémoire libre et on l'ajoute à la mémoire allouée.
		if(liste->blocMemoire.nbBytes == nbBytes){
			addresseAllouee = liste->blocMemoire.adresse;
			memoireAllouee = inserTete(memoireAllouee,nbBytes, liste->blocMemoire.adresse);
			memoireLibre = suppListe(memoireLibre, liste);
		}
		// Si le nombre de bytes d'un bloc mémoire de la mémoire libre est supérieur au nombre de bytes.
		else{
			// On ajoute un nouveau bloc avec le nombre de bytes passé en paramètre et l'adresse alloué.
			memoireAllouee = inserTete(memoireAllouee,nbBytes, liste->blocMemoire.adresse);
			addresseAllouee = liste->blocMemoire.adresse;
			
			// On ajoute ensuite dans la mémoire libre un nouveau bloc mémoire avec :
			// Pour adresse, l'adresse du bloc alloué additionné au nombre de bytes alloué à ce dernier.
			// Pour nombre de bytes, le nombre de bytes initial soustrait avec le nombre de bytes alloué.
			int nbBytesRestant = liste->blocMemoire.nbBytes - nbBytes;
			if(nbBytesRestant > 0){
				void* adresse = liste->blocMemoire.adresse + nbBytes;
				memoireLibre = inserTete(memoireLibre,nbBytesRestant,adresse);
			}
			// On supprime ensuite ce bloc de la mémoire libre.
			memoireLibre = suppListe(memoireLibre, liste);
		}        	
    }
    return addresseAllouee;
}

/*!
 * \brief Fonction permettant la désallocation dynamique d'espace dans une zone adressée par un pointeur.
 * \param [in] p pointeur vers l'adresse mémoire recherchée. Type void*.
 * \return Le nombre de bytes récupéré ou -1 en cas d'erreur.
 */
 int myfree(void* p){
    int nbBytes = -1;
	// On recherche un bloc mémoire dans la mémoire allouée avec le pointeur passé en paramètre.
	Liste liste = rechercheBlocMemoire(memoireAllouee, p);
	// Si le pointeur vers l'adresse mémoire recherchée n'est pas NULL et qu'un bloc mémoire correspondant 
	// à ce pointeur est trouvé, on insère le bloc mémoire, trouvé précédemment, dans la mémoire libre.
	// On supprime ensuite ce bloc mémoire de la mémoire allouée.
	if(p != NULL && liste != NULL ){
		nbBytes = liste->blocMemoire.nbBytes;
		memoireLibre = inserTete(memoireLibre,nbBytes,liste->blocMemoire.adresse);
		memoireAllouee = suppListe(memoireAllouee,liste);
		memoireLibre = defragmentation(memoireLibre);
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
	 	printf("Initialisation de la zone de travail echouee (%d bytes).\n",nbBytes);
    else    
		printf("Initialisation de la zone de travail reussie (%d bytes).\n",nbBytes);
}

/*!
 * \brief Fonction permettant l'affichage des messages concernant la récuperation de la mémoire.
 * \param [in] nbBytesRecupere Nombre de byte récupéré du bloc mémoire. Type int. 
 */
void freeMemoryMessage(int nbBytesRecupere){
	if(nbBytesRecupere == -1)
		printf("Recuperation de la zone memoire initialisee pour le programme echouee.\n");
	else
		printf("Recuperation de la zone memoire initialisee pour le programme reussie %d bytes recupere.\n",nbBytesRecupere);
}

/*!
 * \brief Fonction permettant l'affichage des messages concernant l'allocation de mémoire.
 * \param [in] p pointeur vers l'adresse mémoire allouée. Type void*.
 * \param [in] nbBytes Nombre de byte alloué. Type int. 
 */
void myallocMessage(void* p,int nbBytes){
	if(p != NULL){
		printf("Allocation de memoire dans la zone de travail reussi (%d bytes).\n",nbBytes);
		printf("L'adresse allouee est %p\n",p);
	}
	else
		printf("Allocation de memoire dans la zone de travail echouee (%d bytes).\n",nbBytes);
}

/*!
 * \brief Fonction permettant l'affichage des messages concernant la désallocation de la mémoire.
 * \param [in] nbBytesRecupere Nombre de byte récupéré. Type int. 
 */
void myfreeMessage(int nbBytesRecupere){
	if(nbBytesRecupere == -1)
		printf("Desallocation de memoire dans la zone de travail echouee.\n");
	else
		printf("Desallocation de memoire dans la zone de travail reussi %d bytes recupere.\n",nbBytesRecupere);
}

/*!
 * \brief Fonction permettant la défragmentation de la mémoire libre.
 * \param [in, out] liste espace mémoire libre à défragmenter. Type Liste.
 * \return Une liste d'espace mémoire libre défragmentée.
 */
Liste defragmentation(Liste liste){ 
    Liste listeTemp = liste;
    // Création d'un booleen permettant de connaitre l'état de la défragmentation.
    int defragmente = 0;
    
    while(listeTemp != NULL && defragmente == 0){
        Liste listeCourante = listeTemp;
        // Tant que la liste courante n'est pas égale à nulle 
        while (listeCourante != NULL){
			// Et que l'adresse du bloc mémoire de la liste temporaire additionée de son nombre de byte est égal
			//  à l'adresse du bloc mémoire de la liste courante :
            if(listeTemp->blocMemoire.adresse+listeTemp->blocMemoire.nbBytes == listeCourante->blocMemoire.adresse){
				// on associe à un entier le nombre de bytes de la liste temporaire additionnée du nombre 
        		// de bytes de la liste courante.
                int nbBytes = listeTemp->blocMemoire.nbBytes + listeCourante->blocMemoire.nbBytes;

                // On effectue ensuite une insertion en tête de la liste d'espace libre avec l'adresse mémoire de la
				// liste temporaire et le nombre de bytes additionné précedemment.
                liste = inserTete(liste,nbBytes,listeTemp->blocMemoire.adresse);
				
				// On supprime ensuite les deux blocs mémoires précedents de la liste de mémoire libre
                liste = suppListe(liste, listeTemp);
                liste = suppListe(liste, listeCourante);

                // Et on affecte au bouleen "defragmente" la valeur 1.
                // Cela afin d'indiquer que la liste a été défragmentée.
                defragmente = 1;
                break;
            }
			// Et que l'adresse du bloc mémoire de la liste courante additionée de son nombre de byte est égal
			//  à l'adresse du bloc mémoire de la liste temporaire :
            else if(listeCourante->blocMemoire.adresse+listeCourante->blocMemoire.nbBytes == listeTemp->blocMemoire.adresse){
				// on associe à un entier le nombre de bytes de la liste temporaire additionnée du nombre 
        		// de bytes de la liste courante.
                int nbBytes = listeTemp->blocMemoire.nbBytes + listeCourante->blocMemoire.nbBytes;

                // On effectue ensuite une insertion en tête de la liste d'espace libre avec l'adresse mémoire de la
				// liste courante et le nombre de bytes additionné précedemment.
                liste = inserTete(liste,nbBytes,listeCourante->blocMemoire.adresse);

				// On supprime ensuite les deux blocs mémoires précedents de la liste de mémoire libre
                liste = suppListe(liste, listeTemp);
                liste = suppListe(liste, listeCourante);
                
				// Et on affecte au bouleen "defragmentate" la valeur 1.
                // Cela afin d'indiquer que la liste a été défragmentée.
                defragmente = 1;
                break;
            }
            listeCourante = listeCourante->suivant;
        }
        listeTemp = listeTemp->suivant;     
    }
    // Si l'entier "defragmente" est égal à 1, on défragmente la nouvelle liste.
    if(defragmente)
        liste = defragmentation(liste);
    return liste;
}

/*!
 * \brief Fonction permettant de remplir un tableau à partir d'un fichier.
 * \param [in] filename Chemin du fichier. Type char*.
 * \param [in] longMaxMot Entier représentant la taille de la longueur maximal d'un mot. Type int.
 * \param [in, out] tailleTableau Entier où sera stocker la taille du tableau. Type int*.
 * \return Un tableau contenant les mots du fichier passé en paramètre.
 */
char** fileToTab(char* filename,int longMaxMot,int* tailleTableau){
	FILE *fichier;
    int nbMots,nbCar = 0;
    char** mots;
    char caractere;

	// Ouverture du fichier en mode lecture grâce au chemin passé en paramètre.
	fichier = fopen(filename,"r");
    FILE *f2 = fopen(filename,"r");

    // Tant que le fichier n'est pas arriver à sa fin,
	// on incrémente le nombre de mot afin de connaitre le nombre de caractère.
    while((caractere=fgetc(f2)) != EOF){
        nbCar++;
		// Si les caractères sont égaux à un espace, un \t, un \n ou un \0, le nombre de mot est incrémenté.
		// Cela afin d'initialiser un tableau de mots.
		if (caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\0')
            nbMots++;
    }

    // On incrémente le nombre de mot de 1 afin de prendre en compte le dernier mot du fichier.
    if(nbCar>0)
        nbMots++;

    // On alloue la mémoire pour le tableau de mots.
    mots = (char**)malloc(sizeof(char*)*nbMots);
    for(int i=0;i<nbMots;i++){
        mots[i] = (char*)malloc(sizeof(char)*longMaxMot);
    }

    // On remplit le tableau de mots.
    int i = 0;
    int j = 0;
    while((caractere=fgetc(fichier)) != EOF){
        if (caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\0'){
			// On remplit le tableau du mot avec des cases vides si toute la place n'est pas utilisée.
            while(j<20){
                mots[i][j] = '\0';
                j++;
            }
            i++;
            j=0;
        }
        else{
            mots[i][j] = caractere;
            j++;
        }
    }
    // On remplit le tableau du dernier mot avec des cases vides si toute la place n'est pas utilisée.
    while(j<20){
        mots[i][j] = '\0';
        j++;
    }

	//On affecte la taille du tableau de mots au pointeur tailleTableau
	*tailleTableau = nbMots;

	// Puis on ferme le fichier.
    fclose(fichier);
    fclose(f2);
	return mots;
}

