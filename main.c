/*!
 * \file main.c
 * \brief Fichier principal permettant l'exécution de toute les méthodes du projet.
 * \author Salma BENCHELKHA - Mouncif LEKMITI - Farah MANOUBI
 * \version 1.0
 * \date 2 avril 2021
 * 
 * Ce fichier permet le test de tout les fonctions crées.
 */
#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"
#include "include/liste.h"
#include "include/utilitaire.h"

Liste memoireLibre, memoireAllouee;

/*!
 * \brief Fonction principale.
 * \return Renvoie 0.
 */
int main(){
	// Test de la libération de la mémoire avant l'initialisation de la mémoire.
	printf("Test de la liberation de la memoire lorsque celle-ci n'a pas encore ete initialisee.\n");
	printf("Attendu : Echec.\n");

	int liberation1 = freeMemory();
	if(liberation1 == -1)
		printf("Resultat : Liberation de %d bytes de la memoire echouee.\n",liberation1);
	else 
		printf("Resultat : Liberation de %d bytes de la memoire reussie.\n",liberation1);

	// Test de l'allocation de mémoire avant l'initialisation de la mémoire.
	printf("Test de l'allocation de memoire avant l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int nbBytes = 200;
	void* allocation = myalloc(nbBytes);

	if(allocation != NULL)
		printf("Allocation de %d bytes reussie.\n",allocation);
	else
		printf("Allocation de %d bytes echouee.\n",allocation);
	
	// Test de la désallocation de mémoire avant l'initialisation de la mémoire.
	printf("Test de la désallocation de mémoire avant l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int desallocation = myfree(allocation);
	
	if(desallocation == -1)
		printf("Desallocation de %d bytes non-reussie.\n",desallocation);
	else
		printf("Desallocation de %d bytes reussie.\n",desallocation);

	// Test de l'initialisation de la mémoire.
	printf("Test de l'initialisation de la mémoire de 1000 bytes.\n");
	printf("Attendu : Reussite.\n");
	int nbByte = 1000;
	int initialisation = initMemory(nbByte);

	if(initialisation == 0)
		printf("Initialisation de %d bytes echouee.\n",nbByte);
	else
		printf("Initialisation de %d bytes reussie.\n",nbByte);

	// Test de l'allocation de mémoire de 500 bytes après l'initialisation de la mémoire.
	printf("Test de l'allocation de memoire de 500 bytes après l'initialisation de la memoire.\n");
	printf("Attendu : Reussite.\n");
	int nbInferieur = 500;
	void* allocationInf = myalloc(nbInferieur);

	if(allocationInf != NULL)
		printf("Allocation de %d bytes reussie.\n",nbInferieur);
	else
		printf("Allocation de %d bytes echouee.\n",nbInferieur);
	
	// Test de l'allocation de mémoire de 1200 bytes après l'initialisation de la mémoire.
	printf("Test de l'allocation de memoire de 1200 bytes après l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int nbSuperieur = 1200;
	void* allocationSup = myalloc(nbSuperieur);
	
	if(allocationSup != NULL)
		printf("Allocation de %d bytes reussie.\n",nbSuperieur);
	else
		printf("Allocation de %d bytes echouee.\n",nbSuperieur);
	
	// Test de la désallocation de mémoire de 500 bytes après l'initialisation de la memoire.
	printf("Test de la désallocation de mémoire de 500 bytes après l'initialisation de la memoire.\n");
	printf("Attendu : Reussite.\n");
	int desallocationInf = myfree(allocationInf);
	
	if(desallocationInf == -1)
		printf("Desallocation de %d bits non-reussie.\n",desallocationInf);
	else
		printf("Desallocation de %d bits reussie.\n",desallocationInf);
	
	// Test de la désallocation de mémoire de 1200 bytes après l'initialisation de la memoire.
	printf("Test de la désallocation de mémoire de 1200 bytes après l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int desallocationSup = myfree(allocationSup);

	if(desallocationSup == -1)
		printf("Desallocation de %d bits non-reussie.\n",desallocationSup);
	else
		printf("Desallocation de %d bits reussie.\n",desallocationSup);

	// Test de l'état actuel de l'espace alloué après avoir éffectué tout ces tests.
	printf("Test de l'état actuel de l'espace alloué après avoir éffectué tout ces tests.\n");
	printf("Espace alloue : ");
	while(memoireAllouee != NULL){
		printf("%d bytes ",memoireAllouee->blocMemoire.nbBytes);
		memoireAllouee = memoireAllouee->suivant;
	}
	printf("---------------------------\n");

	// Test de l'état actuel de l'espace libre après avoir éffectué tout ces tests.
	printf("Test de l'etat actuel de l'espace libre après avoir effectue tout ces tests.\n");
	printf("Espace libre : \n");
	while(memoireLibre != NULL){
		printf("%d bits \n",memoireLibre->blocMemoire.nbBytes);
		memoireLibre = memoireLibre->suivant;
	}
	printf("---------------------------\n");

	// Test de la libération de la mémoire.
	printf("Test de la liberation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int recuperation = freeMemory();
	if(recuperation == -1)
		printf("Liberation de la memoire non-reussie.\n");
	else 
		printf("Liberation de %d bytes de la memoire reussie.\n",recuperation);

	// Test de l'état actuel de l'espace alloué après avoir libéré la mémoire.
	printf("Espace alloue : \n");
	while(memoireAllouee != NULL){
		printf("%d bits \n",memoireAllouee->blocMemoire.nbBytes);
		memoireAllouee = memoireAllouee->suivant;
	}

	// Test de l'état actuel de l'espace libre après avoir libérée la mémoire.
	printf("Espace libre : \n");
	while(memoireLibre != NULL){
		printf("%d bits \n",memoireLibre->blocMemoire.nbBytes);
		memoireLibre = memoireLibre->suivant;
	}
	printf("---------------------------\n");

	// Test de l'allocation de mémoire après avoir libéré la mémoire.
	int nbBytes = 1000;
	void* allocation = myalloc(nbBytes);

	if(allocation != NULL)
		printf("Allocation de %d bytes reussie.\n",nbBytes);
	else
		printf("Allocation de %d bytes echouee.\n",nbBytes);

	printf("Fin du programme.\n");
	return 0;
 }