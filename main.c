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

 void afficheEspaceMemoire();


/*!
 * \brief Fonction principale.
 * \return Renvoie 0.
 */
int main(){
	// Test de la libération de la mémoire avant l'initialisation de la mémoire.
	printf("\nFonction : freeMemory()\n");
	printf("Test de la liberation de la memoire lorsque celle-ci n'a pas encore ete initialisee.\n");
	printf("Attendu : Echec.\n");

	int liberation1 = freeMemory();
	if(liberation1 == -1)
		printf("Resultat : Liberation de la memoire echouee.\n",liberation1);
	else 
		printf("Resultat : Liberation de %d bytes de la memoire reussie.\n",liberation1);
	afficheEspaceMemoire();

	// Test de l'allocation de mémoire avant l'initialisation de la mémoire.
	printf("\nFonction : myalloc(nbBytes)\n");
	printf("Test de l'allocation de memoire avant l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int nbBytes = 200;
	void* allocation = myalloc(nbBytes);

	if(allocation != NULL)
		printf("Resultat : Allocation de %d bytes reussie.\n",nbBytes);
	else
		printf("Resultat : Allocation de %d bytes echouee.\n",nbBytes);
	afficheEspaceMemoire();
	
	// Test de la désallocation de mémoire avant l'initialisation de la mémoire.
	printf("\nFonction : myfree(p)\n");
	printf("Test de la desallocation de memoire avant l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int desallocation = myfree(allocation);
	
	if(desallocation == -1)
		printf("Resultat : Desallocation de %d bytes echouee.\n",nbBytes);
	else
		printf("Resultat : Desallocation de %d bytes reussie.\n",nbBytes);
	afficheEspaceMemoire();

	// Test de l'initialisation de la mémoire.
	printf("\nFonction : initMemory(nbBytes)\n");
	printf("Test de l'initialisation de la memoire avec 1000 bytes.\n");
	printf("Attendu : Reussite.\n");
	int nbByte = 600;
	int initialisation = initMemory(nbByte);

	if(initialisation == 0)
		printf("Resultat : Initialisation de %d bytes echouee.\n",nbByte);
	else
		printf("Resultat : Initialisation de %d bytes reussie.\n",nbByte);
	afficheEspaceMemoire();

	// Test de l'allocation de mémoire de 500 bytes après l'initialisation de la mémoire.
	printf("\nFonction : myalloc(nbBytes)\n");
	printf("Test de l'allocation de memoire de 500 bytes apres l'initialisation de la memoire.\n");
	printf("Attendu : Reussite.\n");
	int nbInferieur = 500;
	void* allocationInf = myalloc(nbInferieur);

	if(allocationInf != NULL)
		printf("Resultat : Allocation de %d bytes reussie.\n",nbInferieur);
	else
		printf("Resultat : Allocation de %d bytes echouee.\n",nbInferieur);
	afficheEspaceMemoire();

	// Test de l'allocation de mémoire de 40 bytes après l'initialisation de la mémoire.
	printf("\nFonction : myalloc(nbBytes)\n");
	printf("Test de l'allocation de memoire de 40 bytes apres l'initialisation de la memoire.\n");
	printf("Attendu : Reussite.\n");
	int nbIntermediaire = 40;
	void* allocationInter = myalloc(nbIntermediaire);

	if(allocationInter != NULL)
		printf("Resultat : Allocation de %d bytes reussie.\n",nbIntermediaire);
	else
		printf("Resultat : Allocation de %d bytes echouee.\n",nbIntermediaire);
	afficheEspaceMemoire();
	
	// Test de l'allocation de mémoire de 1200 bytes après l'initialisation de la mémoire.
	printf("\nFonction : myalloc(nbBytes)\n");
	printf("Test de l'allocation de memoire de 1200 bytes apres l'initialisation de la memoire.\n");
	printf("Attendu : Echec.\n");
	int nbSuperieur = 1200;
	void* allocationSup = myalloc(nbSuperieur);
	
	if(allocationSup != NULL)
		printf("Resultat : Allocation de %d bytes reussie.\n",nbSuperieur);
	else
		printf("Resultat : Allocation de %d bytes echouee.\n",nbSuperieur);
	afficheEspaceMemoire();
	
	// Test de la désallocation de mémoire de 500 bytes après l'initialisation de la memoire.
	printf("\nFonction : myfree(p)\n");
	printf("Test de la desallocation memoire de l'allocation precedente de 500 bytes.\n");
	printf("Attendu : Reussite.\n");
	int desallocationInf = myfree(allocationInf);
	
	if(desallocationInf == -1)
		printf("Resultat : Desallocation de %d bytes echouee.\n",nbInferieur);
	else
		printf("Resultat : Desallocation de %d bits reussie.\n",desallocationInf);
	afficheEspaceMemoire();
	
	// Test de la désallocation de mémoire de 1200 bytes après l'initialisation de la memoire.
	printf("\nFonction : myfree(p)\n");
	printf("Test de la desallocation memoire de l'allocation precedente de 1200 bytes.\n");
	printf("Attendu : Echec.\n");
	int desallocationSup = myfree(allocationSup);

	if(desallocationSup == -1)
		printf("Resultat : Desallocation de %d bytes echouee.\n",nbSuperieur);
	else
		printf("Resultat : Desallocation de %d bits reussie.\n",desallocationSup);
	afficheEspaceMemoire();

	// Test de la libération de la mémoire.
	printf("\nFonction : freeMemory()\n");
	printf("Test de la liberation de la memoire.\n");
	printf("Attendu : Reussite.\n");
	int recuperation = freeMemory();
	if(recuperation == -1)
		printf("Resultat : Liberation de la memoire echouee.\n");
	else 
		printf("Resultat : Liberation de %d bytes de la memoire reussie.\n",recuperation);
	afficheEspaceMemoire();

	// Test de l'allocation de mémoire après avoir libéré la mémoire.
	printf("\nFonction : myalloc(nbBytes)\n");
	printf("Test de l'allocation de memoire de 1000 bytes apres la liberation de la memoire.\n");
	printf("Attendu : Echec.\n");
	nbBytes = 1000;
	allocation = myalloc(nbBytes);

	if(allocation != NULL)
		printf("Resultat : Allocation de %d bytes reussie.\n",nbBytes);
	else
		printf("Resultat : Allocation de %d bytes echouee.\n",nbBytes);
	afficheEspaceMemoire();

	printf("\nFin du programme.\n");
	return 0;
 }

 void afficheEspaceMemoire(){
	 // Affichage de l'état actuel de l'espace alloué.
	printf("Affichage de l'etat actuel de l'espace alloue.\n");
	printf("Espace alloue {");
	Liste lAllouee = memoireAllouee;
	while(lAllouee != NULL){
		printf("%d bytes, ",lAllouee->blocMemoire.nbBytes);
		lAllouee = lAllouee->suivant;
	}
	printf("}\n");

	// Affichage de l'état actuel de l'espace libre.
	printf("Affichage de l'etat actuel de l'espace libre.\n");
	printf("Espace libre {");
	Liste lLibre = memoireLibre;
	while(lLibre != NULL){
		printf("%dbytes, ",lLibre->blocMemoire.nbBytes);
		lLibre = lLibre->suivant;
	}
	printf("}\n\n");
	printf("---------------------------\n");
 }