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
	Liste listeTmpAllouee = memoireAllouee;
    while(listeTmpAllouee != NULL){
		myfree(listeTmpAllouee->blocMemoire.adresse);
        listeTmpAllouee = suppTete(listeTmpAllouee);
    }
	// Elle permet, tant que la mémoire libre n'est pas égale à nulle, de récupérer tout 
	// les bytes utilisés dans le bloc mémoire et de libérer la liste.
	Liste listeTmpLibre = memoireLibre;
    while(listeTmpLibre != NULL){
		nbBytesRecupere += listeTmpLibre->blocMemoire.nbBytes;
        listeTmpLibre = suppTete(listeTmpLibre);
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

/*!
 * \brief Fonction permettant la défragmentation d'une liste
 * \param [in, out] liste Liste à défragmenter. Type Liste.
 * \return Une liste défragmentée.
 */
Liste defragmentation(Liste liste){
	// Création d'une liste temporaire.
	Liste listeTemp = liste;
	// Création d'un entier permettant de connaitre l'état de la défragmentation.
	int defragmente = 0;
	
	// Tant que la liste temporaire n'est pas égal à nulle et que la défragmentation est égale à 0
	// La liste temporaire est égale à la liste courante.
	while(listeTemp != NULL && defragmente == 0){
		Liste listeCourante = listeTemp;
		// Tant que la liste courante n'est pas égale à nulle et que l'adresse de la liste 
		// temporaire additionée de son nombre de byte est égal à l'adresse de la liste courante,
		// on associe à un entier le nombre de bytes de la liste temporaire additionnée du nombre 
		// de bytes de la liste courante.
		while (listeCourante != NULL){
			if(listeTemp->blocMemoire.adresse+listeTemp->blocMemoire.nbBytes == listeCourante->blocMemoire.adresse){
				int nbBytes = listeTemp->blocMemoire.nbBytes + listeCourante->blocMemoire.nbBytes;
				// On effectue ensuite une insertion en tête de la liste A REVOIR
				liste = inserTete(liste,nbBytes,listeTemp->blocMemoire.adresse);
				// Et on associe à l'entier "defragmentate" la valeur 1.
				// Cela afin d'indiquer que la liste a été défragmentée.
				defragmente = 1;
				break;
			}
			// On effectue ces mêmes opérations à la liste suivant la liste courante.
			// Cela afin de parcourir toute la liste initiale.
			listeCourante = listeCourante->suivant;
		}
		listeTemp = listeTemp->suivant;		
	}
	// Si l'entier "defragmente" est égal à 1, on défragmente une seconde fois la liste défragmentée.
	if(defragmente)
		liste = defragmentation(liste);
	return liste;
}

/*!
 * \brief Fonction permettant de remplir un tableau à partir d'un fichier.
 * \param [in] filename Caractère du chemin où se trouve le chemin. Type char.
 * \param [in] longMaxMot Entier représentant la taille de la longueur maximal d'un mot. Type int.
 * \return Les caractères d'un fichier.
 */
char** fileToTab(char* filename,int longMaxMot){
	FILE *fichier;
    int nbMots,nbCar = 0;
    char** mots;
    char caractere;

	// Ouverture du fichier grâce au chemin passé en paramètre.
	fichier = fopen(filename,"r");
    FILE *f2 = fopen(filename,"r");

    // Tant que le fichier n'est pas arriver à sa fin,
	// on incrémente le nombre de mot afin de connaitre le nombre de caractère.
    while((caractere=fgetc(f2)) != EOF){
        nbCar++;
		// Si les caractères sont égals à un espace, un \t, un \n ou un \0, le nombre de mot est incrémenté.
		// Cela afin d'initialiser un tableau de mots.
		if (caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\0')
            nbMots++;
    }

    // On incrémente le nombre de mot de 1 afin de prendre en compte le dernier mot du fichier.
    if(nbCar>0)
        nbMots++;

    // On initialise le tableau de mots.
    mots = (char**)malloc(sizeof(char*)*nbMots);
    for(int i=0;i<nbMots;i++){
        mots[i] = (char*)malloc(sizeof(char)*longMaxMot);
    }

    // On remplit le tableau de mots.
    int i = 0;
    int j = 0;
    while((caractere=fgetc(fichier)) != EOF){
        if (caractere == ' ' || caractere == '\t' || caractere == '\n' || caractere == '\0'){
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
    // On remplit le tableau du dernier mot avec des cases vides.
    while(j<20){
        mots[i][j] = '\0';
        j++;
    }

	// Puis on ferme le fichier.
    fclose(fichier);
    fclose(f2);
	return mots;
}

