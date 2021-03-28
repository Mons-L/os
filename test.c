#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "include/structure.h"
#include "include/liste.h"
#include "include/espaceMemoire.h"
#include "include/utilitaire.h"

extern char *optarg;
Liste memoireLibre, memoireAllouee;

void afficherOptions(){
    printf("1 : Initialiser la zone de travail pour le programme [initMemory()]\n");
    printf("2 : Allouer de la memoire dans la zone de travail [myalloc(int nbBytes)]\n");
    printf("3 : Desallouer une zone adressee par un pointeur dans la zone de travail [myfree(void* p)]\n");
    printf("4 : Recuperer la zone de travail initialement reserve au programme [freeMemory()]\n");
    printf("5 : Quitter le programme\n\n");
}

int main(int argc, char *argv[]){
    /*printf("%d\n",argc);
    for(int i=0; i<argc; i++){
        printf("arg%d=%s\n",i,argv[i]);
    }*/

    
    if(argv[1][0] == '-' && argv[1][1] == 'i'){
        //Gerer le mode interactif
        printf("\nBienvenue dans le mode interactif du programme\n");
        int choix = -1;
        int nbBytes = 0;
        void* adresse = NULL;
        do{
            printf("\nQue souhaitez-vous faire ?\n");
            afficherOptions();
            printf("Votre choix : ");
            scanf("%d",&choix);
            printf("Vous avez choisis %d\n",choix);
            switch (choix){
                case 1:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    if(initMemory(nbBytes) == 0)     printf("Initialisation de la zone de travail echouee (%d bytes)\n",nbBytes);
                    else    printf("Initialisation de la zone de travail reussie (%d bytes)\n",nbBytes);
                    break;

                case 2:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    if(myalloc(5) != NULL)    printf("Allocation de memoire dans la zone de travail reussi (%d bytes)\n",nbBytes);
                    else    printf("Allocation de memoire dans la zone de travail echouee (%d bytes)\n",nbBytes);
                    //printf("%p",adresse);
                    break;

                case 3:
                    printf("Desallocation de memoire dans la zone de travail\n");
                    break;

                case 4:
                    printf("Recuperation de la zone memoire initialisee\n");
                    break;

                case 5:
                    printf("arret du programme\n");
                    choix = 5;
                    break;

                default:
                    printf("Votre choix n'a pas ete reconnue, veuillez choisir un nombre entre 1 et 5");
                    break;
            }
            sleep(2);
        }while(choix != 5);

    }
    else if(argv[1][0] == '-' && argv[1][1] == 'f'){
        printf("C'est le mode batch\n\n");

        //Faire le mode batch
        FILE *fichier;
        char caractere;
        char* filename;
        getopt(argc,argv,":if:lrx");
        filename = optarg;

        printf("Voici le contenu du fichier %s : \n",optarg);

        fichier = fopen(filename,"r");

        while((caractere=fgetc(fichier)) != EOF){
            printf("%c",caractere);
        }

        fclose(fichier);
    }    
   /* else{
        printf("Option non reconnue.\n");
        printf("%s\n",argv[1]);
    }*/
    
    else{
        printf("C'est le mode CLI\n");
        //Faire la ligne de commande
        int getopt();
        int test;
        while ((test = getopt(argc, argv, "m:a:f:"))!= -1){
            switch(test){
                case 'm':
                printf("Initialisation de la memoire: %s \n",optarg);
                int init = atoi(optarg);
                if(init==0){
                    printf("allocation impossible. \n", init);
                }
                initMemory(init);
                break;
                
                case 'a':
                printf("Allocation de la memoire: %s \n", optarg);
                int alloc = atoi(optarg);
                myalloc(alloc);
                break;

                case 'f':
                printf("Desallocation de la memoire: %s \n", optarg);
                void* p1 = myalloc(alloc);
                myfree(p1);
                break;


            }
        }
    }
    return 0;
}

