#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"
#include "include/liste.h"
#include "include/espaceMemoire.h"
#include "include/utilitaire.h"


Liste memoireLibre, memoireAllouee;

int main(){

	int nbBits = 500;
	int init = initMemory(nbBits);

	if(init == 0)
		printf("Impossible d'initialiser %d bits pour le programme.\n",nbBits);
	else
		printf("Initialisation de %d bits pour le programme reussi.\n",nbBits);

	int nbByte1 = 600;
	int nbByte2 = 10;
	void* p1 = myalloc(nbByte1);
	void* p2 = myalloc(nbByte2);
	int recup1 = myfree(p1);
	int recup2 = myfree(p2);

	if(p1 != NULL)
		printf("Allocation de %d bits reussie.\n",nbByte1);
	
	if(p2 != NULL)
		printf("Allocation de %d bits reussie.\n",nbByte2);

	if(recup1 != -1)
		printf("Desallocation de %d bits reussi\n",recup1);

	if(recup2 != -1)
		printf("Desallocation de %d bits reussi\n",recup2);
	
	printf("Espace alloue : \n");
	while(memoireAllouee != NULL){
		printf("%d bits \n",memoireAllouee->blocMemoire.nbBytes);
		memoireAllouee = memoireAllouee->suivant;
	}

	printf("Espace libre : \n");
	while(memoireLibre != NULL){
		printf("%d bits \n",memoireLibre->blocMemoire.nbBytes);
		memoireLibre = memoireLibre->suivant;
	}

	freeMemory();
	printf("Espace alloue : \n");
	while(memoireAllouee != NULL){
		printf("%d bits \n",memoireAllouee->blocMemoire.nbBytes);
		memoireAllouee = memoireAllouee->suivant;
	}

	printf("Espace libre : \n");
	while(memoireLibre != NULL){
		printf("%d bits \n",memoireLibre->blocMemoire.nbBytes);
		memoireLibre = memoireLibre->suivant;
	}
	
	printf("Fin du programme.\n");
	return 0;
 }