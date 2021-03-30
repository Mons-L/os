#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <unistd.h>
#include "include/structure.h"
#include "include/liste.h"
#include "include/espaceMemoire.h"
#include "include/utilitaire.h"

#define MAX 20
#define CHOIX_INIT_MEMORY "Initialiser la zone de travail pour le programme [initMemory()]"
#define CHOIX_FREE_MEMORY "Recuperer la zone de travail initialement reserve au programme [freeMemory()]"
#define CHOIX_MYALLOC "Allouer de la memoire dans la zone de travail [myalloc(int nbBytes)]"
#define CHOIX_MYFREE "Desallouer une zone adressee par un pointeur dans la zone de travail [myfree(void* p)]"
#define CHOIX_QUITTER "Quitter le programme"
char* choixString[5] = {CHOIX_INIT_MEMORY,CHOIX_FREE_MEMORY,CHOIX_MYALLOC,CHOIX_MYFREE,CHOIX_QUITTER};

extern char *optarg;
Liste memoireLibre, memoireAllouee;

void afficherOptions(){
    printf("\nQue souhaitez-vous faire ?\n");
    printf("1 : %s\n",CHOIX_INIT_MEMORY);
    printf("2 : %s\n",CHOIX_FREE_MEMORY);
    printf("3 : %s\n",CHOIX_MYALLOC);
    printf("4 : %s\n",CHOIX_MYFREE);
    printf("5 : %s\n\n",CHOIX_QUITTER);
}

void recupererChoix(int* choix){
    printf("Votre choix : ");
    scanf("%d",choix);
    printf("\nVous avez choisis : %s\n",choixString[*choix]);
}

void gestionModeInteractif(){
    printf("\nBienvenue dans le mode interactif du programme\n");
        int choix = -1;
        int nbBytes = 0;
        void* adresse = NULL;
        do{
            afficherOptions();
            recupererChoix(&choix);
            switch (choix){
                case 1:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    initMemoryMessage(initMemory(nbBytes),nbBytes);
                    break;

                case 2:
                    freeMemoryMessage(freeMemory());
                    break;

                case 3:
                    printf("Combien de bytes ?\t");
                    scanf("%d",&nbBytes);
                    myallocMessage(myalloc(nbBytes),nbBytes);
                    break;

                case 4:
                    printf("Quel est l'adresse memoire ?\t");
                    scanf("%p",&adresse);
                    myfreeMessage(myfree(adresse));
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

void gestionModeBatch(char* filename){
    printf("\nBienvenue dans le mode batch du programme\n\n");
    char** mots = fileToTab(filename,MAX); 
    int nbMots = sizeof(mots)+1;
    
    //effectue le traitement en fonction de ce qui a été lue
    for(int i=0;i<nbMots;i++){
        if(strcmp(mots[i],"InitMemory") == 0){
            i++;
            int nbBytes = atoi(mots[i]);
            int longueurInt = log10(nbBytes) + 1;
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier\n",mots[i]);
                printf("Interruption du programme\n");
                exit(EXIT_FAILURE);
            }
            else{
                int status = initMemory(nbBytes);
                initMemoryMessage(status,nbBytes);
                if(status == 0) exit(EXIT_FAILURE);
                printf("\n");
            }
        }
        
        else if(strcmp(mots[i],"FreeMemory") == 0){
            int nbBytesRecupere = freeMemory();
            freeMemoryMessage(nbBytesRecupere);
            if(nbBytesRecupere == -1)   exit(EXIT_FAILURE);
        }

        else if(strcmp(mots[i],"Allocation") == 0){
            i++;
            int nbBytes = atoi(mots[i]);
            int longueurInt = log10(nbBytes) + 1;
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier\n",mots[i]);
                printf("Interruption du programme\n");
                exit(EXIT_FAILURE);
            }
            else{
                void* p = myalloc(nbBytes);
                myallocMessage(p,nbBytes);
                if(p == NULL) exit(EXIT_FAILURE);
                printf("\n");
            }
        }
        

        else if(strcmp(mots[i],"Desallocation") == 0){
            i++;
            int indice = atoi(mots[i]);
            int longueurInt = log10(indice) + 1;
            if(longueurInt != strlen(mots[i])){
                printf("Erreur dans la syntaxe du fichier sur le mot : %s, attendu : entier\n",mots[i]);
                printf("Interruption du programme\n");
                exit(EXIT_FAILURE);
            }
            else{
                int listeSize = tailleListe(memoireAllouee);
                if(listeSize >= indice){
                    Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-indice); 
                    int nbBytesRecupere = myfree(listeAdesalloue->blocMemoire.adresse);
                    myfreeMessage(nbBytesRecupere);
                    if(nbBytesRecupere == -1) exit(EXIT_FAILURE);
                    printf("\n");
                }
                else{
                    printf("Erreur l'indice %d de l'element a desallouer est superieur au nombre d'element alloue\n",indice);
                    printf("Interruption du programme\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        else{
            printf("Erreur dans la syntaxe du fichier sur le mot : %s\n",mots[i]);
            printf("Interruption du programme\n");
            exit(EXIT_FAILURE);
        }
    }
}

void gestionModeCli(int argc, char*argv[]){
    printf("C'est le mode CLI\n");
    //Faire la ligne de commande
    // int getopt();
    int test;
    while ((test = getopt(argc, argv, "m:a:d:l"))!= -1){
        int nbBytes,status,longueurInt,selectionne, listeSize;
        void* p = NULL;
        switch(test){
            case 'm':
                nbBytes = 0;
                nbBytes = atoi(optarg);
                longueurInt = log10(nbBytes) + 1;
                if(nbBytes == 0 || longueurInt != strlen(optarg)){
                    printf("Initialisation de la memoire: impossible, argument '%s' incorrect\n",optarg); 
                    exit(EXIT_FAILURE);
                }
                status = initMemory(nbBytes);
                initMemoryMessage(status,nbBytes);
                if(status == 0) exit(EXIT_FAILURE);
                printf("\n");
                break;
            
            case 'a':
                nbBytes = 0;
                nbBytes = atoi(optarg);
                longueurInt = log10(nbBytes) + 1;
                if(nbBytes == 0 || longueurInt != strlen(optarg)){
                    printf("Allocation memoire : impossible, argument '%s' incorrect\n",optarg); 
                    exit(EXIT_FAILURE);
                }
                p = myalloc(nbBytes);
                myallocMessage(p,nbBytes);
                if(p == NULL) exit(EXIT_FAILURE);
                printf("\n");;
                break;

            case 'd':
                selectionne = 0;
                selectionne = atoi(optarg);
                longueurInt = log10(selectionne) + 1;
                listeSize = tailleListe(memoireAllouee);
                if(selectionne == 0 || longueurInt != strlen(optarg) || listeSize < selectionne){
                    printf("Desallocation memoire : impossible, argument '%s' incorrect\n",optarg); 
                    exit(EXIT_FAILURE);
                }
                Liste listeAdesalloue = rechercheParIndice(memoireAllouee,listeSize-selectionne);
                nbBytes = myfree(listeAdesalloue->blocMemoire.adresse);
                myfreeMessage(nbBytes);
                if(nbBytes == -1) exit(EXIT_FAILURE);
                printf("\n");;
                break;

            case 'l':
                nbBytes = freeMemory();
                freeMemoryMessage(nbBytes);
                if(nbBytes == -1) exit(EXIT_FAILURE);
                break;
        }
    }
}

int main(int argc, char *argv[]){

    if(argv[1][0] == '-' && argv[1][1] == 'i'){
        gestionModeInteractif();
    }
    else if(argv[1][0] == '-' && argv[1][1] == 'f'){
        getopt(argc,argv,":if:lrx");
        char* filename = optarg;
        gestionModeBatch(filename);
    }    
    else{
        gestionModeCli(argc,argv);
    }
    
    return 0;
}

