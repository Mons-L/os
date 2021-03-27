#include <stdio.h>
#include <stdlib.h>
#include <include/liste.h>
#include <include/espaceMemoire.h>

Liste memoireLibre, memoireAllouee;

int main(){
	 int bits = 500;
	 int init = initMemory(bits);
	 if(init == 0){
		 printf("Impossible d'initialiser %d bits pour le programme\n",bits);
	 }
	 else{
		 printf("Initialisation de %d bits pour le programme reussi\n", bits);
	 }
	 int nbByte = 600;
	 int nbByte2 = 10;
	 void* p = myalloc(nbByte);
	 if( p !=NULL){
		printf("Allocation de %d bits reussi\n",nbByte);
	 }

	 void* p2 = myalloc(nbByte2);
	 if(p2 !=NULL){
		 printf("Allocation de %d bits reussi\n",nbByte2);
	 }

	 int recup = myfree(p);
	 if(recup != -1){
		printf("Desallocation de %d bits reussi\n",recup);
	 }

	  int recup2 = myfree(p2);
	 if(recup2 != -1){
		printf("Desallocation de %d bits reussi\n",recup);
	 }
/*
	 if(myalloc(90) !=NULL){
		 printf("Allocation de %d bits reussi\n",nbByte2);
	 }*/

	 printf("Espace alloue {\n");
	 while(memoireAllouee != NULL){
		printf("%d bits \n",memoireAllouee->blocMemoire.nbBytes);
		memoireAllouee = memoireAllouee->suivant;
	 }
	 printf("}\n");

	 printf("Espace libre {\n");
	 while(memoireLibre != NULL){
		printf("%d bits \n",memoireLibre->blocMemoire.nbBytes);
		memoireLibre = memoireLibre->suivant;
		
	 }
	 printf("}\n");
	
	 freeMemory();
	 printf("Espace alloue {\n");
	 while(memoireAllouee != NULL){
		printf("%d bits \n",memoireAllouee->blocMemoire.nbBytes);
		memoireAllouee = memoireAllouee->suivant;
	 }
	 printf("}\n");

	 printf("Espace libre {\n");
	 while(memoireLibre != NULL){
		printf("%d bits \n",memoireLibre->blocMemoire.nbBytes);
		memoireLibre = memoireLibre->suivant;
	 }
	 printf("}\n");
	 printf("Fin du programme\n");
	 return 0;
 }